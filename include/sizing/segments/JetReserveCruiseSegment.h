#ifndef JETRESERVECRUISESEGMENT_H
#define JETRESERVECRUISESEGMENT_H

#include <string>

#include "sizing/segments/ReserveCruiseSegment.h"

class JetReserveCruiseSegment : public ReserveCruiseSegment {
public:
    JetReserveCruiseSegment(
        double reserveTime_h,
        double liftToDragRatio,
        double specificFuelConsumption
    );

    ~JetReserveCruiseSegment() override = default;

    std::string getName() const override;

    double weightFraction() const override;
};

#endif