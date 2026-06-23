#include "sizing/WeightEstimator.h"

#include <cmath>
#include <stdexcept>

WeightEstimator::WeightEstimator(
    const AircraftClass& aircraftClass,
    const Mission& mission,
    double crewWeight_lbf,
    double payloadWeight_lbf
)
    : aircraftClass(aircraftClass),
      mission(mission),
      crewWeight_lbf(crewWeight_lbf),
      payloadWeight_lbf(payloadWeight_lbf)
{
    if (crewWeight_lbf < 0.0) {
        throw std::invalid_argument(
            "Crew weight cannot be negative."
        );
    }

    if (payloadWeight_lbf < 0.0) {
        throw std::invalid_argument(
            "Payload weight cannot be negative."
        );
    }

    if (mission.getNumberOfSegments() == 0) {
        throw std::invalid_argument(
            "Mission must contain at least one segment."
        );
    }
}

double WeightEstimator::residual(
    double grossWeight_lbf
) const
{
    if (grossWeight_lbf <= 0.0) {
        throw std::invalid_argument(
            "Gross weight must be greater than zero."
        );
    }

    const double emptyWeightFraction =
        aircraftClass.emptyWeightFraction(
            grossWeight_lbf
        );

    const double finalMissionFraction =
        mission.finalWeightFraction();

    return
        emptyWeightFraction
        +
        (
            crewWeight_lbf +
            payloadWeight_lbf
        )
        /
        grossWeight_lbf
        -
        finalMissionFraction;
}

double WeightEstimator::estimateGrossWeight(
    double initialGuess_lbf,
    double tolerance,
    unsigned int maxIterations
) const
{
    if (initialGuess_lbf <= 0.0) {
        throw std::invalid_argument(
            "Initial gross-weight guess must be greater than zero."
        );
    }

    if (tolerance <= 0.0) {
        throw std::invalid_argument(
            "Tolerance must be greater than zero."
        );
    }

    if (maxIterations == 0) {
        throw std::invalid_argument(
            "Maximum number of iterations must be greater than zero."
        );
    }

    double grossWeight_lbf =
        initialGuess_lbf;

    for (
        unsigned int iteration = 0;
        iteration < maxIterations;
        ++iteration
    ) {
        const double functionValue =
            residual(grossWeight_lbf);

        if (std::abs(functionValue) < tolerance) {
            return grossWeight_lbf;
        }

        const double derivative =
            aircraftClass.getB()
            /
            grossWeight_lbf
            -
            (
                crewWeight_lbf +
                payloadWeight_lbf
            )
            /
            (
                grossWeight_lbf *
                grossWeight_lbf
            );

        if (std::abs(derivative) < 1.0e-12) {
            throw std::runtime_error(
                "Newton-Raphson derivative is too close to zero."
            );
        }

        const double nextGrossWeight_lbf =
            grossWeight_lbf
            -
            functionValue
            /
            derivative;

        if (nextGrossWeight_lbf <= 0.0) {
            throw std::runtime_error(
                "Gross-weight iteration produced a non-positive value."
            );
        }

        grossWeight_lbf =
            nextGrossWeight_lbf;
    }

    throw std::runtime_error(
        "Gross-weight estimation did not converge."
    );
}