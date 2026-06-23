#ifndef RESERVECRUISESEGMENT_H
#define RESERVECRUISESEGMENT_H

#include "sizing/segments/MissionSegment.h"

class ReserveCruiseSegment : public MissionSegment {
protected:
    double reserveTime_h;
    double liftToDragRatio;
    double specificFuelConsumption;

public:
    ReserveCruiseSegment(
        double reserveTime_h,
        double liftToDragRatio,
        double specificFuelConsumption
    );

    ~ReserveCruiseSegment() override = default;
};

#endif