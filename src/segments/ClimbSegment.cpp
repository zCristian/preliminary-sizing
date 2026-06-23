#include "sizing/segments/ClimbSegment.h"

#include <stdexcept>

ClimbSegment::ClimbSegment(
    PropulsionType propulsionType,
    double altitudeChange_ft,
    double rateOfClimb_fpm,
    double powerOrThrustRatio,
    double specificFuelConsumption
)
    : propulsionType(propulsionType),
      altitudeChange_ft(altitudeChange_ft),
      rateOfClimb_fpm(rateOfClimb_fpm),
      powerOrThrustRatio(powerOrThrustRatio),
      specificFuelConsumption(specificFuelConsumption)
{
    if (altitudeChange_ft < 0.0) {
        throw std::invalid_argument(
            "Altitude change cannot be negative."
        );
    }

    if (rateOfClimb_fpm <= 0.0) {
        throw std::invalid_argument(
            "Rate of climb must be greater than zero."
        );
    }

    if (powerOrThrustRatio < 0.0) {
        throw std::invalid_argument(
            "Power or thrust ratio cannot be negative."
        );
    }

    if (specificFuelConsumption < 0.0) {
        throw std::invalid_argument(
            "Specific fuel consumption cannot be negative."
        );
    }
}

std::string ClimbSegment::getName() const
{
    if (propulsionType == PropulsionType::Jet) {
        return "Climb - Jet";
    }

    return "Climb - Propeller";
}

double ClimbSegment::weightFraction() const
{
    const double fuelFraction =
        (
            altitudeChange_ft *
            specificFuelConsumption *
            powerOrThrustRatio
        )
        /
        (
            60.0 *
            rateOfClimb_fpm
        );

    const double fraction = 1.0 - fuelFraction;

    if (fraction <= 0.0 || fraction > 1.0) {
        throw std::domain_error(
            "Invalid climb weight fraction."
        );
    }

    return fraction;
}