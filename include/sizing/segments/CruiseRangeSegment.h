#ifndef CRUISERANGESEGMENT_H
#define CRUISERANGESEGMENT_H

#include "sizing/segments/MissionSegment.h"

class CruiseRangeSegment : public MissionSegment {
protected:
    double range_nm;
    double liftToDragRatio;

public:
    CruiseRangeSegment(
        double range_nm,
        double liftToDragRatio
    );

    ~CruiseRangeSegment() override = default;
};

#endif