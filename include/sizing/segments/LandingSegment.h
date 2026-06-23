#ifndef LANDINGSEGMENT_H
#define LANDINGSEGMENT_H

#include <string>

#include "sizing/segments/MissionSegment.h"

class LandingSegment : public MissionSegment {
private:
    double landingFraction;

public:
    explicit LandingSegment(double landingFraction);

    ~LandingSegment() override = default;

    std::string getName() const override;

    double weightFraction() const override;
};

#endif