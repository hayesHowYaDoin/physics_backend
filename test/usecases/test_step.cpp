#include "usecases/euler/resolve.hpp"
#include "usecases/step.hpp"
#include "domain/constants.hpp"

#include <cstdint>
#include <units.h>
#include <gtest/gtest.h>

static constexpr auto REQUIRED_PRECISION {0.000'001f};

TEST(Step, primative)
{
    std::vector<uint16_t> objects {0, 1, 2};

    auto resolveMotion {[](uint16_t const& object) -> uint16_t {
        return object + 1;
    }};

    auto results {usecases::step<uint16_t>(objects, resolveMotion)};
    EXPECT_TRUE(results.size() == 3);

    EXPECT_TRUE(results[0] == 1);
    EXPECT_TRUE(results[1] == 2);
    EXPECT_TRUE(results[2] == 3);
}
