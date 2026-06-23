#ifndef CLIMBSEGMENT_H
#define CLIMBSEGMENT_H

#include <string>

#include "sizing/PropulsionType.h"
#include "sizing/segments/MissionSegment.h"

class ClimbSegment : public MissionSegment {
private:
    PropulsionType propulsionType;

    double altitudeChange_ft;
    double rateOfClimb_fpm;
    double powerOrThrustRatio;
    double specificFuelConsumption;

public:
    ClimbSegment(
        PropulsionType propulsionType,
        double altitudeChange_ft,
        double rateOfClimb_fpm,
        double powerOrThrustRatio,
        double specificFuelConsumption
    );

    ~ClimbSegment() override = default;

    std::string getName() const override;

    double weightFraction() const override;
};

#endif