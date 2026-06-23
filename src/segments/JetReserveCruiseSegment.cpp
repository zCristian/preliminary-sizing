#include "sizing/segments/JetReserveCruiseSegment.h"

#include <cmath>
#include <stdexcept>

JetReserveCruiseSegment::JetReserveCruiseSegment(
    double reserveTime_h,
    double liftToDragRatio,
    double specificFuelConsumption
)
    : ReserveCruiseSegment(
          reserveTime_h,
          liftToDragRatio,
          specificFuelConsumption
      ) {}

std::string JetReserveCruiseSegment::getName() const
{
    return "Reserve Cruise - Jet";
}

double JetReserveCruiseSegment::weightFraction() const
{
    const double exponent =
        -(
            reserveTime_h *
            specificFuelConsumption
        )
        /
        liftToDragRatio;

    const double fraction = std::exp(exponent);

    if (fraction <= 0.0 || fraction > 1.0) {
        throw std::domain_error(
            "Invalid jet reserve-cruise weight fraction."
        );
    }

    return fraction;
}