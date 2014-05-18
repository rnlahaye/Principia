#include <CppUnitTest.h>

#include "geometry/sign.hpp"
#include "TestUtilities/TestUtilities.hpp"

using Microsoft::VisualStudio::CppUnitTestFramework::Assert;

namespace principia {
namespace geometry {

using namespace test_utilities;  // NOLINT(build/namespaces)

TEST_CLASS(SignTests) {
 public:
  TEST_METHOD(Integer) {
    Sign const positive(1);
    Sign const negative(-1);
    AssertTrue(positive.Positive());
    AssertFalse(positive.Negative());
    AssertFalse(negative.Positive());
    AssertTrue(negative.Negative());
  }

  TEST_METHOD(SignMultiplication) {
    Sign const positive(1);
    Sign const negative(-1);
    AssertTrue((positive * positive).Positive());
    AssertTrue((positive * negative).Negative());
    AssertTrue((negative * positive).Negative());
    AssertTrue((negative * negative).Positive());
  }

  TEST_METHOD(ScalarMultiplication) {
    Sign const positive(1);
    Sign const negative(-1);
    Assert::AreEqual(3, positive * 3);
    Assert::AreEqual(-3, positive * -3);
    Assert::AreEqual(-3, negative * 3);
    Assert::AreEqual(3, negative * -3);
  }
};

}  // namespace geometry
}  // namespace principia
