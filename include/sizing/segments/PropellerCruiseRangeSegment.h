#ifndef PROPELLERCRUISERANGESEGMENT_H
#define PROPELLERCRUISERANGESEGMENT_H

#include <string>

#include "sizing/segments/CruiseRangeSegment.h"

class PropellerCruiseRangeSegment : public CruiseRangeSegment {
private:
    double specificFuelConsumption;
    double propellerEfficiency;

public:
    PropellerCruiseRangeSegment(
        double range_nm,
        double liftToDragRatio,
        double specificFuelConsumption,
        double propellerEfficiency
    );

    ~PropellerCruiseRangeSegment() override = default;

    std::string getName() const override;

    double weightFraction() const override;
};

#endif