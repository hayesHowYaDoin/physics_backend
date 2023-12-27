#ifndef DOMAIN_CONSTANTS_HPP
#define DOMAIN_CONSTANTS_HPP

#include <units.h>

namespace domain::constants
{

constexpr auto G {units::acceleration::meters_per_second_squared<double> {-9.81}};

} // namespace domain::constants

#endif // DOMAIN_CONSTANTS_HPP