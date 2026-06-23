#ifndef TAXITAKEOFFSEGMENT_H
#define TAXITAKEOFFSEGMENT_H

#include <string>

#include "sizing/PropulsionType.h"
#include "sizing/segments/MissionSegment.h"

class TaxiTakeoffSegment : public MissionSegment {
private:
    PropulsionType propulsionType;

    double taxiTime_h;
    double maxPowerTime_h;

    double idleRatio;
    double maxRatio;

    double specificFuelConsumption;

public:
    TaxiTakeoffSegment(
        PropulsionType propulsionType,
        double taxiTime_h,
        double maxPowerTime_h,
        double idleRatio,
        double maxRatio,
        double specificFuelConsumption
    );

    ~TaxiTakeoffSegment() override = default;

    std::string getName() const override;

    double weightFraction() const override;
};

#endif