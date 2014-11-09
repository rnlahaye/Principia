#include "ksp_plugin/rendering_frame.hpp"

#include "geometry/rotation.hpp"
#include "ksp_plugin/celestial.hpp"
#include "physics/transforms.hpp"
#include "quantities/quantities.hpp"

using principia::quantities::Angle;
using principia::quantities::ArcTan;
using principia::quantities::Time;
using principia::geometry::Bivector;
using principia::geometry::Displacement;
using principia::geometry::InnerProduct;
using principia::geometry::Rotation;
using principia::geometry::Wedge;
using principia::physics::BodyCentredNonRotatingTransformingIterator;

namespace principia {
namespace ksp_plugin {

namespace {

// Returns an iterator for the first entry in |trajectory| with a time greater
// than or equal to |t|.
// TODO(phl): This is O(N), so we might want to expose a more efficient version.
// But then it's likely that we'll just rewrite this class anyway.
Trajectory<Barycentre>::NativeIterator LowerBound(
    Instant const& t, Trajectory<Barycentre> const& trajectory) {
  for (Trajectory<Barycentre>::NativeIterator it = trajectory.first();
       !it.at_end();
       ++it) {
    if (it.time() >= t) {
      return it;
    }
  }
  LOG(FATAL) << t << " not found in trajectory";
  return trajectory.first();
}

}  // namespace

BodyCentredNonRotatingFrame::BodyCentredNonRotatingFrame(
    Celestial<Barycentre> const& body) : body_(body) {}

std::unique_ptr<Trajectory<Barycentre>>
BodyCentredNonRotatingFrame::ApparentTrajectory(
    Trajectory<Barycentre> const& actual_trajectory) const {
  std::unique_ptr<Trajectory<Barycentre>> result =
      std::make_unique<Trajectory<Barycentre>>(actual_trajectory.body());
  // TODO(phl): Should tag the two frames differently.
  auto actual_it =
      BodyCentredNonRotatingTransformingIterator<Barycentre, Barycentre>(
          body_.prolongation(), &actual_trajectory);
  auto body_it = body_.prolongation().on_or_after(actual_it.time());
  for (; !actual_it.at_end(); ++actual_it, ++body_it) {
    // Advance over the bits of the actual trajectory that don't have a matching
    // time in the body trajectory.
    while (actual_it.time() != body_it.time()) {
      ++actual_it;
    }
    result->Append(actual_it.time(), actual_it.degrees_of_freedom());
  }
  return std::move(result);
}

BarycentricRotatingFrame::BarycentricRotatingFrame(
    Celestial<Barycentre> const& primary,
    Celestial<Barycentre> const& secondary)
    : primary_(primary),
      secondary_(secondary) {}

namespace {

// TODO(egg): Move this somewhere more appropriate, wrap it, etc.
struct Matrix {
  geometry::R3Element<double> row_x;
  geometry::R3Element<double> row_y;
  geometry::R3Element<double> row_z;

  template <typename Scalar>
  geometry::R3Element<Scalar> operator()(
      geometry::R3Element<Scalar> const& right) const {
    return {geometry::Dot(row_x, right),
            geometry::Dot(row_y, right),
            geometry::Dot(row_z, right)};
  }
};

Matrix FromColumns(geometry::R3Element<double> const& column_x,
                   geometry::R3Element<double> const& column_y,
                   geometry::R3Element<double> const& column_z) {
  return {{column_x.x, column_y.x, column_z.x},
          {column_x.y, column_y.y, column_z.y},
          {column_x.z, column_y.z, column_z.z}};
}

Matrix Transpose(Matrix const& m) {
  return FromColumns(m.row_x, m.row_y, m.row_z);
}

}  // namespace

std::unique_ptr<Trajectory<Barycentre>>
BarycentricRotatingFrame::ApparentTrajectory(
    Trajectory<Barycentre> const& actual_trajectory) const {
  std::unique_ptr<Trajectory<Barycentre>> result =
      std::make_unique<Trajectory<Barycentre>>(actual_trajectory.body());
  Trajectory<Barycentre>::NativeIterator actual_it = actual_trajectory.first();
  Trajectory<Barycentre>::NativeIterator primary_it =
      LowerBound(actual_it.time(), primary_.history());
  Trajectory<Barycentre>::NativeIterator secondary_it =
      LowerBound(actual_it.time(), secondary_.history());
  DegreesOfFreedom<Barycentre> const& current_primary_state =
      primary_.prolongation().last().degrees_of_freedom();
  DegreesOfFreedom<Barycentre> const& current_secondary_state =
      secondary_.prolongation().last().degrees_of_freedom();
  Position<Barycentre> const current_barycentre_position =
      geometry::Barycentre<Displacement<Barycentre>, Mass>(
          {current_primary_state.position, current_secondary_state.position},
          {primary_.body().mass(), secondary_.body().mass()});
  Velocity<Barycentre> const current_barycentre_velocity =
      (primary_.body().mass() * current_primary_state.velocity +
           secondary_.body().mass() * current_secondary_state.velocity) /
      (primary_.body().mass() + secondary_.body().mass());
  Matrix from_standard_basis_to_current_barycentric_frame;
  {
    Displacement<Barycentre> reference_direction =
        current_primary_state.position - current_barycentre_position;
    Vector<double, Barycentre> const normalized_reference_direction =
        reference_direction / reference_direction.Norm();
    Velocity<Barycentre> const reference_coplanar =
        current_primary_state.velocity - current_barycentre_velocity;
    Vector<double, Barycentre> const normalized_reference_coplanar =
        reference_coplanar / reference_coplanar.Norm();
    // Modified Gram-Schmidt.
    Vector<double, Barycentre> const reference_normal =
        normalized_reference_coplanar -
            InnerProduct(normalized_reference_coplanar,
                         normalized_reference_direction) *
                normalized_reference_direction;
    // TODO(egg): should we normalize this?
    Bivector<double, Barycentre> const reference_binormal =
        Wedge(normalized_reference_direction, reference_normal);
    from_standard_basis_to_current_barycentric_frame =
        FromColumns(normalized_reference_direction.coordinates(),
                    reference_normal.coordinates(),
                    reference_binormal.coordinates());
  }
  for (; !actual_it.at_end(); ++actual_it) {
    Instant const& t = actual_it.time();
    DegreesOfFreedom<Barycentre> const& actual_state =
        actual_it.degrees_of_freedom();
    while (primary_it.time() < t) {
      ++primary_it;
      ++secondary_it;
    }
    if (primary_it.time() == t) {
      DegreesOfFreedom<Barycentre> const& primary_state =
          primary_it.degrees_of_freedom();
      DegreesOfFreedom<Barycentre> const& secondary_state =
          secondary_it.degrees_of_freedom();
      Position<Barycentre> const barycentre_position =
          geometry::Barycentre<Displacement<Barycentre>, Mass>(
              {primary_state.position, secondary_state.position},
              {primary_.body().mass(), secondary_.body().mass()});
      Velocity<Barycentre> const barycentre_velocity =
          (primary_.body().mass() * primary_state.velocity +
               secondary_.body().mass() * secondary_state.velocity) /
          (primary_.body().mass() + secondary_.body().mass());
      Matrix from_barycentric_frame_to_standard_basis;
      {
        Displacement<Barycentre> reference_direction =
            primary_state.position - barycentre_position;
        Vector<double, Barycentre> const normalized_reference_direction =
            reference_direction / reference_direction.Norm();
        Velocity<Barycentre> const reference_coplanar =
            primary_state.velocity - barycentre_velocity;
        Vector<double, Barycentre> const normalized_reference_coplanar =
            reference_coplanar / reference_coplanar.Norm();
        // Modified Gram-Schmidt.
        Vector<double, Barycentre> const reference_normal =
            normalized_reference_coplanar -
                InnerProduct(normalized_reference_coplanar,
                             normalized_reference_direction) *
                    normalized_reference_direction;
        // TODO(egg): should we normalize this?
        Bivector<double, Barycentre> const reference_binormal =
            Wedge(normalized_reference_direction, reference_normal);
        // Constructed from rows.
        from_barycentric_frame_to_standard_basis =
            {normalized_reference_direction.coordinates(),
             reference_normal.coordinates(),
             reference_binormal.coordinates()};
      }
      // TODO(egg): We should have a vector space structure on
      // |DegreesOfFreedom<Fries>|.
      result->Append(
          t,
          {Displacement<Barycentre>(
               from_standard_basis_to_current_barycentric_frame(
                   from_barycentric_frame_to_standard_basis(
                       (actual_state.position -
                            barycentre_position).coordinates()))) +
               current_barycentre_position,
           Velocity<Barycentre>(
               from_standard_basis_to_current_barycentric_frame(
                   from_barycentric_frame_to_standard_basis(
                       (actual_state.velocity -
                            barycentre_velocity).coordinates())))});
    }
  }
  return std::move(result);
}

}  // namespace ksp_plugin
}  // namespace principia
