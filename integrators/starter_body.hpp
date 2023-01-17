#pragma once

#include "integrators/starter.hpp"

namespace principia {
namespace integrators {
namespace internal_starter {

template<typename ODE, typename Step, int order>
Starter<ODE, Step, order>::Starter(
    FixedStepSizeIntegrator<ODE> const& startup_integrator,
    std::int64_t const startup_step_divisor,
    not_null<typename FixedStepSizeIntegrator<ODE>::Instance*> const instance)
    : startup_integrator_(startup_integrator),
      startup_step_divisor_(startup_step_divisor),
      instance_(instance) {
  previous_steps_.emplace_back();
  FillStepFromState(instance_->equation(),
                    instance_->state(),
                    previous_steps_.back());
}

template<typename ODE, typename Step, int order>
void Starter<ODE, Step, order>::StartupSolve(
    typename ODE::IndependentVariable const& s_final) {
  auto const& equation = instance_->equation();
  auto& current_state = instance_->state();
  auto const& step = instance_->step();

  typename ODE::IndependentVariable const startup_step =
      step / startup_step_divisor_;

  CHECK(!previous_steps_.empty());
  CHECK_LT(previous_steps_.size(), order);

  auto const startup_append_state =
      [&current_state, &equation](typename ODE::State const& state) {
        // Stop changing anything once we're done with the startup.  We may be
        // called one more time by the |startup_integrator_|.
        if (previous_steps_.size() < order) {
          current_state = state;
          // The startup integrator has a smaller step.  We do not record all
          // the states it computes, but only those that are a multiple of the
          // main integrator step.
          if (++startup_step_index_ % startup_step_divisor == 0) {
            CHECK_LT(previous_steps_.size(), order);
            previous_steps_.emplace_back();
            FillStepFromState(equation,
                              current_state,
                              previous_steps_.back());
            // This call must happen last for a subtle reason: the callback may
            // want to |Clone| this instance (see |Ephemeris::Checkpoint|) in
            // which cases it is necessary that all the member variables be
            // filled for restartability to work.
            this->append_state_(state);
          }
        }
      };

  auto const startup_instance =
      startup_integrator_.NewInstance({equation, current_state},
                                       startup_append_state,
                                       startup_step);

  startup_instance->Solve(
      std::min(instance_->time().value +
                   (order - previous_steps_.size()) * step + step / 2.0,
               s_final)).IgnoreError();

  CHECK_LE(previous_steps_.size(), order);
}

template<typename ODE, typename Step, int order>
bool Starter<ODE, Step, order>::done() const {
  CHECK_LE(previous_steps_.size(), order);
  return previous_steps_.size() == order;
}

template<typename ODE, typename Step, int order>
std::list<Step> const& Starter<ODE, Step, order>::previous_steps() const {
  CHECK_EQ(previous_steps_.size(), order);
  return previous_steps_;
}

template<typename ODE, typename Step, int order>
template<typename Message>
void Starter<ODE, Step, order>::WriteToMessage(
    not_null<Message*> message) const {
  for (auto const& previous_step : previous_steps_) {
    previous_step.WriteToMessage(message->add_previous_steps());
  }
  message->set_startup_step_index(startup_step_index_);
}

template<typename ODE, typename Step, int order>
template<typename Message>
void Starter<ODE, Step, order>::FillFromMessage(Message const& message) {
  previous_steps_.clear();
  for (auto const& previous_step : message.previous_steps()) {
    previous_steps_.push_back(Step::ReadFromMessage(previous_step));
  }
  startup_step_index_ = message.startup_step_index();
}

}  // namespace internal_starter
}  // namespace integrators
}  // namespace principia
