#include "sizing/segments/PropellerCruiseRangeSegment.h"

#include <cmath>
#include <stdexcept>

PropellerCruiseRangeSegment::PropellerCruiseRangeSegment(
    double range_nm,
    double liftToDragRatio,
    double specificFuelConsumption,
    double propellerEfficiency
)
    : CruiseRangeSegment(range_nm, liftToDragRatio),
      specificFuelConsumption(specificFuelConsumption),
      propellerEfficiency(propellerEfficiency)
{
    if (specificFuelConsumption < 0.0) {
        throw std::invalid_argument(
            "Specific fuel consumption cannot be negative."
        );
    }

    if (
        propellerEfficiency <= 0.0 ||
        propellerEfficiency > 1.0
    ) {
        throw std::invalid_argument(
            "Propeller efficiency must be greater than zero "
            "and less than or equal to one."
        );
    }
}

std::string PropellerCruiseRangeSegment::getName() const
{
    return "Cruise Range - Propeller";
}

double PropellerCruiseRangeSegment::weightFraction() const
{
    const double exponent =
        -(
            range_nm *
            specificFuelConsumption
        )
        /
        (
            325.9 *
            propellerEfficiency *
            liftToDragRatio
        );

    const double fraction = std::exp(exponent);

    if (fraction <= 0.0 || fraction > 1.0) {
        throw std::domain_error(
            "Invalid propeller cruise weight fraction."
        );
    }

    return fraction;
}