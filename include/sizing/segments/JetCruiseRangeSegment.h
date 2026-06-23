#ifndef JETCRUISERANGESEGMENT_H
#define JETCRUISERANGESEGMENT_H

#include <string>

#include "sizing/segments/CruiseRangeSegment.h"

class JetCruiseRangeSegment : public CruiseRangeSegment {
private:
    double speed_ktas;
    double specificFuelConsumption;

public:
    JetCruiseRangeSegment(
        double range_nm,
        double speed_ktas,
        double liftToDragRatio,
        double specificFuelConsumption
    );

    ~JetCruiseRangeSegment() override = default;

    std::string getName() const override;

    double weightFraction() const override;
};

#endif