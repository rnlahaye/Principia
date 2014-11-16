#pragma once

#include "geometry/named_quantities.hpp"
#include "ksp_plugin/celestial.hpp"
#include "ksp_plugin/frames.hpp"

using principia::geometry::AngularVelocity;

// TODO(egg): the contents of this file make little sense, and the current
// abstractions get in the way of optimizations.  |RenderingFrame| should return
// a |Trajectory| in the rendering frame, rather than in |Barycentric|, so that
// this trajectory may be prolonged as the history is computed, rather than
// computed every time. Since the actual rendering frame is not known at compile
// time, a wrapper (|ApparentTrajectory|?) for the trajectory *and* the
// |RenderingFrame| is needed to operate on the trajectory correctly. While the
// realization of the apparent trajectory in WorldSpace will have to be done at
// every frame, this means we will be able to do the conversion Barycentric ->
// rendering frame incrementally (except when switching reference frames).

namespace principia {
namespace ksp_plugin {

class RenderingFrame {
 public:
  virtual std::unique_ptr<Trajectory<Barycentric>> ApparentTrajectory(
      Trajectory<Barycentric> const& actual_trajectory) const = 0;
};

class BodyCentredNonRotatingFrame : public RenderingFrame {
 public:
  explicit BodyCentredNonRotatingFrame(Celestial<Barycentric> const& body);

  std::unique_ptr<Trajectory<Barycentric>> ApparentTrajectory(
      Trajectory<Barycentric> const& actual_trajectory) const override;

 private:
  Celestial<Barycentric> const& body_;
};

class BodyCentredRotating : public RenderingFrame {
 public:
  BodyCentredRotating(Celestial<Barycentric> const& body,
                      AngularVelocity<Barycentric> const& angular_velocity);

  std::unique_ptr<Trajectory<Barycentric>> ApparentTrajectory(
      Trajectory<Barycentric> const& actual_trajectory) const override;

 private:
  Celestial<Barycentric> const& body_;
  AngularVelocity<Barycentric> const angular_velocity_;
};

class BarycentricRotatingFrame : public RenderingFrame {
 public:
  BarycentricRotatingFrame(Celestial<Barycentric> const& primary,
                           Celestial<Barycentric> const& secondary);

  std::unique_ptr<Trajectory<Barycentric>> ApparentTrajectory(
      Trajectory<Barycentric> const& actual_trajectory) const override;

 private:
  Celestial<Barycentric> const& primary_;
  Celestial<Barycentric> const& secondary_;
};

}  // namespace ksp_plugin
}  // namespace principia
