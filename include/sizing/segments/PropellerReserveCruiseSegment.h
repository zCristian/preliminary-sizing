#ifndef PROPELLERRESERVECRUISESEGMENT_H
#define PROPELLERRESERVECRUISESEGMENT_H

#include <string>

#include "sizing/segments/ReserveCruiseSegment.h"

class PropellerReserveCruiseSegment : public ReserveCruiseSegment {
private:
    double speed_ktas;
    double propellerEfficiency;

public:
    PropellerReserveCruiseSegment(
        double reserveTime_h,
        double speed_ktas,
        double liftToDragRatio,
        double specificFuelConsumption,
        double propellerEfficiency
    );

    ~PropellerReserveCruiseSegment() override = default;

    std::string getName() const override;

    double weightFraction() const override;
};

#endif