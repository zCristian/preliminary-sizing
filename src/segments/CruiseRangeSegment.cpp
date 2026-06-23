#include "sizing/segments/CruiseRangeSegment.h"

#include <stdexcept>

CruiseRangeSegment::CruiseRangeSegment(
    double range_nm,
    double liftToDragRatio
)
    : range_nm(range_nm),
      liftToDragRatio(liftToDragRatio)
{
    if (range_nm < 0.0) {
        throw std::invalid_argument(
            "Range cannot be negative."
        );
    }

    if (liftToDragRatio <= 0.0) {
        throw std::invalid_argument(
            "Lift-to-drag ratio must be greater than zero."
        );
    }
}