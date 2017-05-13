#pragma once

#include "ksp_plugin/renderer.hpp"

#include "gmock/gmock.h"

namespace principia {
namespace ksp_plugin {
namespace internal_renderer {

class MockRenderer : public Renderer {
 public:
  MockRenderer();

  MOCK_CONST_METHOD0(GetPlottingFrame, not_null<NavigationFrame const*> ());

  not_null<std::unique_ptr<DiscreteTrajectory<World>>>
  RenderBarycentricTrajectoryInWorld(
      Instant const& time,
      DiscreteTrajectory<Barycentric>::Iterator const& begin,
      DiscreteTrajectory<Barycentric>::Iterator const& end,
      Position<World> const& sun_world_position,
      Rotation<Barycentric, AliceSun> const& planetarium_rotation)
      const override;
  MOCK_CONST_METHOD6(
      FillRenderedBarycentricTrajectoryInWorld,
      void(Instant const& time,
           DiscreteTrajectory<Barycentric>::Iterator const& begin,
           DiscreteTrajectory<Barycentric>::Iterator const& end,
           Position<World> const& sun_world_position,
           Rotation<Barycentric, AliceSun> const& planetarium_rotation,
           std::unique_ptr<DiscreteTrajectory<World>>*
               rendered_barycentric_trajectory_in_world));

  MOCK_CONST_METHOD1(
      BarycentricToWorldSun,
      OrthogonalMap<Barycentric, WorldSun>(
          Rotation<Barycentric, AliceSun> const& planetarium_rotation));
};

}  // namespace internal_renderer

using internal_renderer::MockRenderer;

}  // namespace ksp_plugin
}  // namespace principia
