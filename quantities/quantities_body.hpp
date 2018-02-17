﻿
#pragma once

#include "quantities/quantities.hpp"

#include <cmath>
#include <cstdio>
#include <limits>
#include <string>

#include "base/macros.hpp"
#include "base/not_constructible.hpp"

namespace principia {
namespace quantities {
namespace internal_quantities {

using base::not_constructible;

template<typename Q>
struct Collapse : not_constructible {
  using Type = Q;
};
template<>
struct Collapse<Quantity<NoDimensions>> : not_constructible {
  using Type = double;
};
template<typename Left, typename Right>
struct ProductGenerator : not_constructible {
  enum {
    Length            = Left::Dimensions::Length + Right::Dimensions::Length,
    Mass              = Left::Dimensions::Mass + Right::Dimensions::Mass,
    Time              = Left::Dimensions::Time + Right::Dimensions::Time,
    Current           = Left::Dimensions::Current + Right::Dimensions::Current,
    Temperature       = Left::Dimensions::Temperature +
                        Right::Dimensions::Temperature,
    Amount            = Left::Dimensions::Amount + Right::Dimensions::Amount,
    LuminousIntensity = Left::Dimensions::LuminousIntensity +
                        Right:: Dimensions::LuminousIntensity,
    Angle             = Left::Dimensions::Angle + Right::Dimensions::Angle,
  };
  using Type = typename Collapse<
      Quantity<Dimensions<Length, Mass, Time, Current, Temperature, Amount,
                          LuminousIntensity, Angle>>>::Type;
};
template<typename Left>
struct ProductGenerator<Left, double> : not_constructible {
  using Type = Left;
};
template<typename Right>
struct ProductGenerator<double, Right> : not_constructible {
  using Type = Right;
};
template<>
struct ProductGenerator<double, double> : not_constructible {
  using Type = double;
};
template<typename Left, typename Right>
struct QuotientGenerator : not_constructible {
  enum {
    Length            = Left::Dimensions::Length - Right::Dimensions::Length,
    Mass              = Left::Dimensions::Mass - Right::Dimensions::Mass,
    Time              = Left::Dimensions::Time - Right::Dimensions::Time,
    Current           = Left::Dimensions::Current - Right::Dimensions::Current,
    Temperature       = Left::Dimensions::Temperature -
                        Right::Dimensions::Temperature,
    Amount            = Left::Dimensions::Amount - Right::Dimensions::Amount,
    LuminousIntensity = Left::Dimensions::LuminousIntensity -
                        Right:: Dimensions::LuminousIntensity,
    Angle             = Left::Dimensions::Angle - Right::Dimensions::Angle,
  };
  using Type = typename Collapse<
      Quantity<Dimensions<Length, Mass, Time, Current, Temperature, Amount,
                          LuminousIntensity, Angle>>>::Type;
};
template<typename Left>
struct QuotientGenerator<Left, double> : not_constructible {
  using Type = Left;
};
template<>
struct QuotientGenerator<double, double> : not_constructible {
  using Type = double;
};
template<typename Right>
struct QuotientGenerator<double, Right> : not_constructible {
  enum {
    Length            = -Right::Dimensions::Length,
    Mass              = -Right::Dimensions::Mass,
    Time              = -Right::Dimensions::Time,
    Current           = -Right::Dimensions::Current,
    Temperature       = -Right::Dimensions::Temperature,
    Amount            = -Right::Dimensions::Amount,
    LuminousIntensity = -Right::Dimensions::LuminousIntensity,
    Angle             = -Right::Dimensions::Angle,
  };
  using Type = Quantity<
      Dimensions<Length, Mass, Time, Current, Temperature, Amount,
                 LuminousIntensity, Angle>>;
};

template<typename T, int exponent>
struct ExponentiationGenerator<T, exponent, std::enable_if_t<(exponent > 1)>> {
  using Type = Product<typename ExponentiationGenerator<T, exponent - 1>::Type,
                       T>;
};

template<typename T, int exponent>
struct ExponentiationGenerator<T, exponent, std::enable_if_t<(exponent < 1)>>{
  using Type = Quotient<typename ExponentiationGenerator<T, exponent + 1>::Type,
                        T>;
};

template<typename T, int exponent>
struct ExponentiationGenerator<T, exponent, std::enable_if_t<(exponent == 1)>>{
  using Type = T;
};

// NOTE(phl): We use |is_arithmetic| here, not |double|, to make it possible to
// write something like |Sqrt(2)|.  We could use |is_arithmetic| in more places
// but it would make the template magic even harder to follow, so let's not do
// that until we have a good reason.
template<int n, typename Q>
struct NthRootGenerator<n, Q, std::enable_if_t<std::is_arithmetic<Q>::value>> {
  using Type = double;
};

template<int n, typename Q>
struct NthRootGenerator<
    n,
    Q,
    std::enable_if_t<(Q::Dimensions::Length % n) == 0 &&
                     (Q::Dimensions::Mass % n) == 0 &&
                     (Q::Dimensions::Time % n) == 0 &&
                     (Q::Dimensions::Current % n) == 0 &&
                     (Q::Dimensions::Temperature % n) == 0 &&
                     (Q::Dimensions::Amount % n) == 0 &&
                     (Q::Dimensions::LuminousIntensity % n) == 0 &&
                     (Q::Dimensions::Angle % n) == 0>> {
  enum {
    Length            = Q::Dimensions::Length / n,
    Mass              = Q::Dimensions::Mass / n,
    Time              = Q::Dimensions::Time / n,
    Current           = Q::Dimensions::Current / n,
    Temperature       = Q::Dimensions::Temperature / n,
    Amount            = Q::Dimensions::Amount / n,
    LuminousIntensity = Q::Dimensions::LuminousIntensity / n,
    Angle             = Q::Dimensions::Angle / n,
  };
  using Type = Quantity<Dimensions<Length, Mass, Time, Current, Temperature,
                                   Amount, LuminousIntensity, Angle>>;
};

template<typename D>
constexpr Quantity<D>::Quantity() : magnitude_(0) {}

template<typename D>
constexpr Quantity<D>::Quantity(double const magnitude)
    : magnitude_(magnitude) {}

template<typename D>
Quantity<D>& Quantity<D>::operator+=(Quantity const& right) {
  magnitude_ += right.magnitude_;
  return *this;
}

template<typename D>
Quantity<D>& Quantity<D>::operator-=(Quantity const& right) {
  magnitude_ -= right.magnitude_;
  return *this;
}

template<typename D>
Quantity<D>& Quantity<D>::operator*=(double const right) {
  magnitude_ *= right;
  return *this;
}

template<typename D>
Quantity<D>& Quantity<D>::operator/=(double const right) {
  magnitude_ /= right;
  return *this;
}

// Additive group

template<typename D>
constexpr Quantity<D> Quantity<D>::operator+() const {
  return *this;
}

template<typename D>
constexpr Quantity<D> Quantity<D>::operator-() const {
  return Quantity(-magnitude_);
}

template<typename D>
FORCE_INLINE(constexpr) Quantity<D> Quantity<D>::operator+(
    Quantity const& right) const {
  return Quantity(magnitude_ + right.magnitude_);
}

template<typename D>
FORCE_INLINE(constexpr) Quantity<D> Quantity<D>::operator-(
    Quantity const& right) const {
  return Quantity(magnitude_ - right.magnitude_);
}

// Comparison operators

template<typename D>
constexpr bool Quantity<D>::operator>(Quantity const& right) const {
  return magnitude_ > right.magnitude_;
}

template<typename D>
constexpr bool Quantity<D>::operator<(Quantity const& right) const {
  return magnitude_ < right.magnitude_;
}

template<typename D>
constexpr bool Quantity<D>::operator>=(Quantity const& right) const {
  return magnitude_ >= right.magnitude_;
}

template<typename D>
constexpr bool Quantity<D>::operator<=(Quantity const& right) const {
  return magnitude_ <= right.magnitude_;
}

template<typename D>
constexpr bool Quantity<D>::operator==(Quantity const& right) const {
  return magnitude_ == right.magnitude_;
}

template<typename D>
constexpr bool Quantity<D>::operator!=(Quantity const& right) const {
  return magnitude_ != right.magnitude_;
}

template<typename D>
void Quantity<D>::WriteToMessage(
    not_null<serialization::Quantity*> const message) const {
  message->set_dimensions(D::representation);
  message->set_magnitude(magnitude_);
}

template<typename D>
Quantity<D> Quantity<D>::ReadFromMessage(
    serialization::Quantity const& message) {
  CHECK_EQ(D::representation, message.dimensions());
  return Quantity(message.magnitude());
}

// Multiplicative group

template<typename D>
constexpr Quantity<D> Quantity<D>::operator/(double const right) const {
  return Quantity(magnitude_ / right);
}

template<typename D>
constexpr Quantity<D> Quantity<D>::operator*(double const right) const {
  return Quantity(magnitude_ * right);
}

template<typename LDimensions, typename RDimensions>
FORCE_INLINE(constexpr) Product<Quantity<LDimensions>, Quantity<RDimensions>>
operator*(Quantity<LDimensions> const& left,
          Quantity<RDimensions> const& right) {
  return Product<Quantity<LDimensions>,
                 Quantity<RDimensions>>(left.magnitude_ * right.magnitude_);
}

template<typename LDimensions, typename RDimensions>
constexpr Quotient<Quantity<LDimensions>, Quantity<RDimensions>>
operator/(Quantity<LDimensions> const& left,
          Quantity<RDimensions> const& right) {
  return Quotient<Quantity<LDimensions>,
                  Quantity<RDimensions>>(left.magnitude_ / right.magnitude_);
}

template<typename RDimensions>
FORCE_INLINE(constexpr) Quantity<RDimensions> operator*(
    double const left,
    Quantity<RDimensions> const& right) {
  return Quantity<RDimensions>(left * right.magnitude_);
}

template<typename RDimensions>
constexpr typename Quantity<RDimensions>::Inverse operator/(
    double const left,
    Quantity<RDimensions> const& right) {
  return typename Quantity<RDimensions>::Inverse(left / right.magnitude_);
}

template<typename Q>
constexpr Q SIUnit() {
  return Q(1);
}

template<>
constexpr double SIUnit<double>() {
  return 1;
}

template<typename Q>
Q FromM128D(__m128d const x) {
  return Q(_mm_cvtsd_f64(x));
}

template<typename Q>
__m128d ToM128D(Q const x) {
  return _mm_set1_pd(x.magnitude_);
}

template<>
inline double FromM128D(__m128d const x) {
  return _mm_cvtsd_f64(x);
}

template<>
inline __m128d ToM128D(double const x) {
  return _mm_set1_pd(x);
}

template<typename Q, typename>
constexpr Q Infinity() {
  return SIUnit<Q>() * std::numeric_limits<double>::infinity();
}

template<typename Q, typename>
constexpr bool IsFinite(Q const& x) {
  return std::isfinite(x / SIUnit<Q>());
}

template<typename Q, typename>
constexpr Q NaN() {
  return SIUnit<Q>() * std::numeric_limits<double>::quiet_NaN();
}

inline std::string FormatUnit(std::string const& name, int const exponent) {
  switch (exponent) {
    case 0:
      return "";
      break;
    case 1:
      return " " + name;
    default:
      return " " + name + "^" + std::to_string(exponent);
  }
}

inline std::string DebugString(double const number, int const precision) {
  char result[50];
#if OS_WIN && PRINCIPIA_COMPILER_MSVC && (_MSC_VER < 1900)
  unsigned int old_exponent_format = _set_output_format(_TWO_DIGIT_EXPONENT);
  int const size = sprintf_s(result,
                             ("%+." + std::to_string(precision) + "e").c_str(),
                             number);
  _set_output_format(old_exponent_format);
#else
  int const size = snprintf(result, sizeof(result),
                            ("%+." + std::to_string(precision) + "e").c_str(),
                            number);
#endif
  CHECK_LE(0, size);
  return std::string(result, size);
}

template<typename D>
std::string DebugString(Quantity<D> const& quantity, int const precision) {
  return DebugString(quantity / SIUnit<Quantity<D>>(), precision) +
      FormatUnit("m", D::Length) + FormatUnit("kg", D::Mass) +
      FormatUnit("s", D::Time) + FormatUnit("A", D::Current) +
      FormatUnit("K", D::Temperature) + FormatUnit("mol", D::Amount) +
      FormatUnit("cd", D::LuminousIntensity) + FormatUnit("rad", D::Angle);
}

template<typename D>
std::ostream& operator<<(std::ostream& out, Quantity<D> const& quantity) {
  return out << DebugString(quantity);
}

}  // namespace internal_quantities
}  // namespace quantities
}  // namespace principia
