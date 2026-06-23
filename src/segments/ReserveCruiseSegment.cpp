#include "sizing/segments/ReserveCruiseSegment.h"

#include <stdexcept>

ReserveCruiseSegment::ReserveCruiseSegment(
    double reserveTime_h,
    double liftToDragRatio,
    double specificFuelConsumption
)
    : reserveTime_h(reserveTime_h),
      liftToDragRatio(liftToDragRatio),
      specificFuelConsumption(specificFuelConsumption)
{
    if (reserveTime_h < 0.0) {
        throw std::invalid_argument(
            "Reserve time cannot be negative."
        );
    }

    if (liftToDragRatio <= 0.0) {
        throw std::invalid_argument(
            "Lift-to-drag ratio must be greater than zero."
        );
    }

    if (specificFuelConsumption < 0.0) {
        throw std::invalid_argument(
            "Specific fuel consumption cannot be negative."
        );
    }
}