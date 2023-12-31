#include "domain/vector.hpp"
#include "core/concepts.hpp"
#include <units.h>

#include <gtest/gtest.h>

static constexpr auto REQUIRED_PRECISION {0.000'001f};

TEST(VectorTest, ConstructFromComponents)
{
    using namespace units::literals;

    constexpr auto vector {domain::Vector2D::fromComponents(10.0_N, 10.0_N)};

    auto angle {vector.getAngle<units::angle::degrees<float>>()};
    EXPECT_NEAR(angle.to<float>(), 45.0f, REQUIRED_PRECISION);

    constexpr auto mag {vector.getMagnitude<units::force::newtons<float>>()};
    EXPECT_NEAR(mag.to<float>(), 14.142'136f, REQUIRED_PRECISION);

    constexpr auto x {vector.getX<units::force::newtons<float>>()};
    EXPECT_NEAR(x.to<float>(), 10.0f, REQUIRED_PRECISION);

    constexpr auto y {vector.getY<units::force::newtons<float>>()};
    EXPECT_NEAR(y.to<float>(), 10.0f, REQUIRED_PRECISION);
}

TEST(VectorTest, ConstructFromAngleAndMagnitude)
{
    using namespace units::literals;

    auto vector {domain::Vector2D::fromPolar(45.0_deg, 10.0_m)};

    auto angle {vector.getAngle<units::angle::degrees<float>>()};
    EXPECT_NEAR(angle.to<float>(), 45.0f, REQUIRED_PRECISION);

    auto magnitude {vector.getMagnitude<units::length::meters<float>>()};
    EXPECT_NEAR(magnitude.to<float>(), 10.0f, REQUIRED_PRECISION);

    auto x {vector.getX<units::length::meters<float>>()};
    EXPECT_NEAR(x.to<float>(), 7.071'068f, REQUIRED_PRECISION);

    auto y {vector.getY<units::length::meters<float>>()};
    EXPECT_NEAR(y.to<double>(), 7.071'068f, REQUIRED_PRECISION);
}

TEST(VectorTest, ConstructFromAngleAndNegativeMagnitude)
{
    using namespace units::literals;

    EXPECT_THROW(
        domain::Vector2D::fromPolar(45.0_deg, -10.0_N),
        std::invalid_argument);
}

TEST(VectorTest, ConstructFromComponentsYieldsPositiveMagnitude)
{
    using namespace units::literals;

    constexpr auto vector {domain::Vector2D::fromComponents(10.0_N, -10.0_N)};

    EXPECT_GT(
        vector.getMagnitude<units::force::newtons<float>>().to<float>(),
        0.0f);
}

TEST(VectorTest, MagnitudeTypes)
{
    using namespace units::literals;

    constexpr auto newtons {
        domain::Vector2D::fromComponents(10.0_N, 10.0_N)};

    constexpr auto meters {
        domain::Vector2D::fromComponents(10.0_m, 10.0_m)};

    constexpr auto metersPerSecond {
        domain::Vector2D::fromComponents(10.0_mps, 10.0_mps)};

    constexpr auto metersPerSecondPerSecond {
        domain::Vector2D::fromComponents(10.0_mps_sq, 10.0_mps_sq)};
}

TEST(VectorTest, AddVectors)
{
    using namespace units::literals;

    constexpr auto vector1 {domain::Vector2D::fromComponents(10.0_N, 10.0_N)};
    constexpr auto vector2 {domain::Vector2D::fromComponents(10.0_N, 10.0_N)};

    constexpr auto vector3 {vector1 + vector2};

    constexpr auto x {vector3.getX<units::force::newtons<float>>()};
    EXPECT_NEAR(x.to<float>(), 20.0f, REQUIRED_PRECISION);

    constexpr auto y {vector3.getY<units::force::newtons<float>>()};
    EXPECT_NEAR(y.to<float>(), 20.0f, REQUIRED_PRECISION);
}

TEST(VectorTest, SubtractVectors)
{
    using namespace units::literals;

    constexpr auto vector1 {domain::Vector2D::fromComponents(20.0_N, 20.0_N)};
    constexpr auto vector2 {domain::Vector2D::fromComponents(10.0_N, 10.0_N)};

    constexpr auto vector3 {vector1 - vector2};

    constexpr auto x {vector3.getX<units::force::newtons<float>>()};
    EXPECT_NEAR(x.to<float>(), 10.0f, REQUIRED_PRECISION);

    constexpr auto y {vector3.getY<units::force::newtons<float>>()};
    EXPECT_NEAR(y.to<float>(), 10.0f, REQUIRED_PRECISION);
}

TEST(VectorTest, MultiplyVectorByScalar)
{
    using namespace units::literals;

    constexpr auto vector1 {domain::Vector2D::fromComponents(10.0_N, 10.0_N)};

    constexpr auto vector2 {vector1 * 2.0f};

    constexpr auto x {vector2.getX<units::force::newtons<float>>()};
    EXPECT_NEAR(x.to<float>(), 20.0f, REQUIRED_PRECISION);

    constexpr auto y {vector2.getY<units::force::newtons<float>>()};
    EXPECT_NEAR(y.to<float>(), 20.0f, REQUIRED_PRECISION);
}

TEST(VectorTest, DivideVectorByScalar)
{
    using namespace units::literals;

    constexpr auto vector1 {domain::Vector2D::fromComponents(20.0_N, 20.0_N)};

    constexpr auto vector2 {vector1 / 2.0f};

    constexpr auto x {vector2.getX<units::force::newtons<float>>()};
    EXPECT_NEAR(x.to<float>(), 10.0f, REQUIRED_PRECISION);

    constexpr auto y {vector2.getY<units::force::newtons<float>>()};
    EXPECT_NEAR(y.to<float>(), 10.0f, REQUIRED_PRECISION);
}

TEST(VectorTest, DotProduct)
{
    using namespace units::literals;

    constexpr auto vector1 {domain::Vector2D::fromComponents(10.0_N, 10.0_N)};
    constexpr auto vector2 {domain::Vector2D::fromComponents(10.0_N, 10.0_N)};

    constexpr auto dotProduct {vector1.dot(vector2)};
    EXPECT_NEAR(dotProduct.to<float>(), 200.0f, REQUIRED_PRECISION);
}

TEST(VectorTest, CrossProduct)
{
    using namespace units::literals;

    constexpr auto vector1 {domain::Vector2D::fromComponents(10.0_N, 10.0_N)};
    constexpr auto vector2 {domain::Vector2D::fromComponents(10.0_N, 10.0_N)};

    constexpr auto crossProduct {vector1.cross(vector2)};
    EXPECT_NEAR(crossProduct.to<float>(), 0.0f, REQUIRED_PRECISION);
}
