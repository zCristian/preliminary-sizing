#include "sizing/segments/PropellerReserveCruiseSegment.h"

#include <cmath>
#include <stdexcept>

PropellerReserveCruiseSegment::PropellerReserveCruiseSegment(
    double reserveTime_h,
    double speed_ktas,
    double liftToDragRatio,
    double specificFuelConsumption,
    double propellerEfficiency
)
    : ReserveCruiseSegment(
          reserveTime_h,
          liftToDragRatio,
          specificFuelConsumption
      ),
      speed_ktas(speed_ktas),
      propellerEfficiency(propellerEfficiency)
{
    if (speed_ktas <= 0.0) {
        throw std::invalid_argument(
            "Reserve cruise speed must be greater than zero."
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

std::string PropellerReserveCruiseSegment::getName() const
{
    return "Reserve Cruise - Propeller";
}

double PropellerReserveCruiseSegment::weightFraction() const
{
    const double exponent =
        -(
            speed_ktas *
            reserveTime_h *
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
            "Invalid propeller reserve-cruise weight fraction."
        );
    }

    return fraction;
}