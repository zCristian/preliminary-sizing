#include "sizing/segments/JetCruiseRangeSegment.h"

#include <cmath>
#include <stdexcept>

JetCruiseRangeSegment::JetCruiseRangeSegment(
    double range_nm,
    double speed_ktas,
    double liftToDragRatio,
    double specificFuelConsumption
)
    : CruiseRangeSegment(range_nm, liftToDragRatio),
      speed_ktas(speed_ktas),
      specificFuelConsumption(specificFuelConsumption)
{
    if (speed_ktas <= 0.0) {
        throw std::invalid_argument(
            "Cruise speed must be greater than zero."
        );
    }

    if (specificFuelConsumption < 0.0) {
        throw std::invalid_argument(
            "Specific fuel consumption cannot be negative."
        );
    }
}

std::string JetCruiseRangeSegment::getName() const
{
    return "Cruise Range - Jet";
}

double JetCruiseRangeSegment::weightFraction() const
{
    const double exponent =
        -(
            range_nm *
            specificFuelConsumption
        )
        /
        (
            speed_ktas *
            liftToDragRatio
        );

    const double fraction = std::exp(exponent);

    if (fraction <= 0.0 || fraction > 1.0) {
        throw std::domain_error(
            "Invalid jet cruise weight fraction."
        );
    }

    return fraction;
}