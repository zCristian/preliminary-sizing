#ifndef DESCENTSEGMENT_H
#define DESCENTSEGMENT_H

#include <string>

#include "sizing/PropulsionType.h"
#include "sizing/segments/MissionSegment.h"

class DescentSegment : public MissionSegment {
private:
    PropulsionType propulsionType;

    double altitudeChange_ft;
    double rateOfDescent_fpm;
    double powerOrThrustRatio;
    double specificFuelConsumption;

public:
    DescentSegment(
        PropulsionType propulsionType,
        double altitudeChange_ft,
        double rateOfDescent_fpm,
        double powerOrThrustRatio,
        double specificFuelConsumption
    );

    ~DescentSegment() override = default;

    std::string getName() const override;

    double weightFraction() const override;
};

#endif