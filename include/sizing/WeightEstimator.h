#ifndef WEIGHTESTIMATOR_H
#define WEIGHTESTIMATOR_H

#include "sizing/AircraftClass.h"
#include "sizing/Mission.h"

class WeightEstimator {
private:
    const AircraftClass& aircraftClass;
    const Mission& mission;

    double crewWeight_lbf;
    double payloadWeight_lbf;

public:
    WeightEstimator(
        const AircraftClass& aircraftClass,
        const Mission& mission,
        double crewWeight_lbf,
        double payloadWeight_lbf
    );

    ~WeightEstimator() = default;

    double residual(double grossWeight_lbf) const;

    double estimateGrossWeight(
        double initialGuess_lbf,
        double tolerance = 1.0e-6,
        unsigned int maxIterations = 100
    ) const;
};

#endif