#include "sizing/segments/DescentSegment.h"

#include <stdexcept>

DescentSegment::DescentSegment(
    PropulsionType propulsionType,
    double altitudeChange_ft,
    double rateOfDescent_fpm,
    double powerOrThrustRatio,
    double specificFuelConsumption
)
    : propulsionType(propulsionType),
      altitudeChange_ft(altitudeChange_ft),
      rateOfDescent_fpm(rateOfDescent_fpm),
      powerOrThrustRatio(powerOrThrustRatio),
      specificFuelConsumption(specificFuelConsumption)
{
    if (altitudeChange_ft < 0.0) {
        throw std::invalid_argument(
            "Altitude change cannot be negative."
        );
    }

    if (rateOfDescent_fpm <= 0.0) {
        throw std::invalid_argument(
            "Rate of descent must be greater than zero."
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

std::string DescentSegment::getName() const
{
    if (propulsionType == PropulsionType::Jet) {
        return "Descent - Jet";
    }

    return "Descent - Propeller";
}

double DescentSegment::weightFraction() const
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
            rateOfDescent_fpm
        );

    const double fraction = 1.0 - fuelFraction;

    if (fraction <= 0.0 || fraction > 1.0) {
        throw std::domain_error(
            "Invalid descent weight fraction."
        );
    }

    return fraction;
}