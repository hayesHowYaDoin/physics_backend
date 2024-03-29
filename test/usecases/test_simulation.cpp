#include <gtest/gtest.h>

#include "common/precision.hpp"
#include "physics_engine/simulation.hpp"
#include "physics_engine/units.hpp"
#include "physics_engine/domain/vector.hpp"

TEST(Simulation, StepIntegrity)
{
    using namespace physics::units;
    using namespace physics::units::literals;

    struct Metadata
    {
        std::string name;
    };

    physics::usecases::Particle<SI> particle {
        .mass {1.0_kg},
        .radius {1.0_m},
        .position {physics::domain::PositionVector2D(0.0_m, 10.0_m)},
        .velocity {physics::domain::VelocityVector2D(0.0_mps, 0.0_mps)},
        .forces {physics::domain::ForceVector2D(0.0_N, -9.81_N)},
        .metadata {Metadata{.name = "metadataString"}}
    };
    std::vector<physics::usecases::Particle<SI>> const particles {particle, particle};

    physics::usecases::Polygon2D<SI::Length> constraint {
        {
            physics::domain::PositionVector2D(0.0_m, 0.0_m),
            physics::domain::PositionVector2D(0.0_m, 10.0_m),
            physics::domain::PositionVector2D(10.0_m, 10.0_m),
            physics::domain::PositionVector2D(10.0_m, 0.0_m)
        }
    };
    auto const updatedParticles {physics::usecases::step(particles, constraint, 1.0_s)};

    EXPECT_TRUE((std::is_same<decltype(particles), decltype(updatedParticles)>::value));
    EXPECT_TRUE(particles.size() == updatedParticles.size());

    auto data {std::any_cast<Metadata>(updatedParticles.at(0).metadata)};
    EXPECT_TRUE(data.name == "metadataString");
}

TEST(Simulation, ResolveMotion)
{
    using namespace physics::units::literals;
    using Mass = physics::units::mass::kilograms<double>;
    using Position = physics::units::length::meters<double>;
    using Velocity = physics::units::velocity::meters_per_second<double>;
    using Force = physics::units::force::newtons<double>;
    using Time = physics::units::time::seconds<double>;

    physics::usecases::Particle<physics::units::SI> const particle {
        .mass {1.0_kg},
        .radius {1.0_m},
        .position {physics::domain::PositionVector2D(0.0_m, 10.0_m)},
        .velocity {physics::domain::VelocityVector2D(0.0_mps, 0.0_mps)},
        .forces {physics::domain::ForceVector2D(0.0_N, -9.81_N)}
    };
    Time const timeStep {1};

    auto const result {physics::usecases::resolveMotion(particle, timeStep)};

    EXPECT_TRUE(physics::domain::Vector2D::compare(
        result.position,
        physics::domain::PositionVector2D(0.0_m, 0.19_m),
        physics::test::REQUIRED_PRECISION));
    EXPECT_TRUE(physics::domain::Vector2D::compare(
        result.velocity,
        physics::domain::VelocityVector2D(0.0_mps, -9.81_mps),
        physics::test::REQUIRED_PRECISION));
    EXPECT_NEAR(result.mass.to<float>(), 1.0f, physics::test::REQUIRED_PRECISION);
}
