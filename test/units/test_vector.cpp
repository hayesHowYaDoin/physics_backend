#include "physics_backend/units/vector.hpp"

#include <gtest/gtest.h>

static constexpr auto REQUIRED_PRECISION {0.000'001f};

TEST(VectorTest, ConstructFromComponents)
{
    using namespace physics::units::literals;

    constexpr auto vector {physics::units::Vector2D::fromComponents(10.0_N, 10.0_N)};

    auto angle {vector.getAngle<physics::units::angle::degrees<float>>()};
    EXPECT_NEAR(angle.to<float>(), 45.0f, REQUIRED_PRECISION);

    constexpr auto mag {vector.getMagnitude<physics::units::force::newtons<float>>()};
    EXPECT_NEAR(mag.to<float>(), 14.142'136f, REQUIRED_PRECISION);

    constexpr auto x {vector.getX<physics::units::force::newtons<float>>()};
    EXPECT_NEAR(x.to<float>(), 10.0f, REQUIRED_PRECISION);

    constexpr auto y {vector.getY<physics::units::force::newtons<float>>()};
    EXPECT_NEAR(y.to<float>(), 10.0f, REQUIRED_PRECISION);
}

TEST(VectorTest, ConstructFromAngleAndMagnitude)
{
    using namespace physics::units::literals;

    auto vector {physics::units::Vector2D::fromPolar(45.0_deg, 10.0_m)};

    auto angle {vector.getAngle<physics::units::angle::degrees<float>>()};
    EXPECT_NEAR(angle.to<float>(), 45.0f, REQUIRED_PRECISION);

    auto magnitude {vector.getMagnitude<physics::units::length::meters<float>>()};
    EXPECT_NEAR(magnitude.to<float>(), 10.0f, REQUIRED_PRECISION);

    auto x {vector.getX<physics::units::length::meters<float>>()};
    EXPECT_NEAR(x.to<float>(), 7.071'068f, REQUIRED_PRECISION);

    auto y {vector.getY<physics::units::length::meters<float>>()};
    EXPECT_NEAR(y.to<double>(), 7.071'068f, REQUIRED_PRECISION);
}

TEST(VectorTest, ConstructFromAngleAndNegativeMagnitude)
{
    using namespace physics::units::literals;

    EXPECT_THROW(
        physics::units::Vector2D::fromPolar(45.0_deg, -10.0_N),
        std::invalid_argument);
}

TEST(VectorTest, ConstructFromComponentsYieldsPositiveMagnitude)
{
    using namespace units::literals;

    constexpr auto vector {physics::units::Vector2D::fromComponents(10.0_N, -10.0_N)};

    EXPECT_GT(
        vector.getMagnitude<physics::units::force::newtons<float>>().to<float>(),
        0.0f);
}

TEST(VectorTest, MagnitudeTypes)
{
    using namespace physics::units::literals;

    constexpr auto newtons {
        physics::units::Vector2D::fromComponents(10.0_N, 10.0_N)};

    constexpr auto meters {
        physics::units::Vector2D::fromComponents(10.0_m, 10.0_m)};

    constexpr auto metersPerSecond {
        physics::units::Vector2D::fromComponents(10.0_mps, 10.0_mps)};

    constexpr auto metersPerSecondPerSecond {
        physics::units::Vector2D::fromComponents(10.0_mps_sq, 10.0_mps_sq)};
}

TEST(VectorTest, AddVectors)
{
    using namespace physics::units::literals;

    constexpr auto vector1 {physics::units::Vector2D::fromComponents(10.0_N, 10.0_N)};
    constexpr auto vector2 {physics::units::Vector2D::fromComponents(10.0_N, 10.0_N)};

    constexpr auto vector3 {vector1 + vector2};

    constexpr auto x {vector3.getX<physics::units::force::newtons<float>>()};
    EXPECT_NEAR(x.to<float>(), 20.0f, REQUIRED_PRECISION);

    constexpr auto y {vector3.getY<physics::units::force::newtons<float>>()};
    EXPECT_NEAR(y.to<float>(), 20.0f, REQUIRED_PRECISION);
}

TEST(VectorTest, SubtractVectors)
{
    using namespace units::literals;

    constexpr auto vector1 {physics::units::Vector2D::fromComponents(20.0_N, 20.0_N)};
    constexpr auto vector2 {physics::units::Vector2D::fromComponents(10.0_N, 10.0_N)};

    constexpr auto vector3 {vector1 - vector2};

    constexpr auto x {vector3.getX<physics::units::force::newtons<float>>()};
    EXPECT_NEAR(x.to<float>(), 10.0f, REQUIRED_PRECISION);

    constexpr auto y {vector3.getY<physics::units::force::newtons<float>>()};
    EXPECT_NEAR(y.to<float>(), 10.0f, REQUIRED_PRECISION);
}

TEST(VectorTest, MultiplyVectorByScalar)
{
    using namespace physics::units::literals;

    constexpr auto vector1 {physics::units::Vector2D::fromComponents(10.0_N, 10.0_N)};

    constexpr auto vector2 {vector1 * 2.0f};

    constexpr auto x {vector2.getX<physics::units::force::newtons<float>>()};
    EXPECT_NEAR(x.to<float>(), 20.0f, REQUIRED_PRECISION);

    constexpr auto y {vector2.getY<physics::units::force::newtons<float>>()};
    EXPECT_NEAR(y.to<float>(), 20.0f, REQUIRED_PRECISION);
}

TEST(VectorTest, DivideVectorByScalar)
{
    using namespace physics::units::literals;

    constexpr auto vector1 {physics::units::Vector2D::fromComponents(20.0_N, 20.0_N)};

    constexpr auto vector2 {vector1 / 2.0f};

    constexpr auto x {vector2.getX<physics::units::force::newtons<float>>()};
    EXPECT_NEAR(x.to<float>(), 10.0f, REQUIRED_PRECISION);

    constexpr auto y {vector2.getY<units::force::newtons<float>>()};
    EXPECT_NEAR(y.to<float>(), 10.0f, REQUIRED_PRECISION);
}

TEST(VectorTest, DotProduct)
{
    using namespace physics::units::literals;

    constexpr auto vector1 {physics::units::Vector2D::fromComponents(10.0_N, 10.0_N)};
    constexpr auto vector2 {physics::units::Vector2D::fromComponents(10.0_N, 10.0_N)};

    constexpr auto dotProduct {vector1.dot(vector2)};
    EXPECT_NEAR(dotProduct.to<float>(), 200.0f, REQUIRED_PRECISION);
}

TEST(VectorTest, CrossProduct)
{
    using namespace physics::units::literals;

    constexpr auto vector1 {physics::units::Vector2D::fromComponents(10.0_N, 10.0_N)};
    constexpr auto vector2 {physics::units::Vector2D::fromComponents(10.0_N, 10.0_N)};

    constexpr auto crossProduct {vector1.cross(vector2)};
    EXPECT_NEAR(crossProduct.to<float>(), 0.0f, REQUIRED_PRECISION);
}
