#include "sizing/segments/TaxiTakeoffSegment.h"

#include <stdexcept>

TaxiTakeoffSegment::TaxiTakeoffSegment(
    PropulsionType propulsionType,
    double taxiTime_h,
    double maxPowerTime_h,
    double idleRatio,
    double maxRatio,
    double specificFuelConsumption
)
    : propulsionType(propulsionType),
      taxiTime_h(taxiTime_h),
      maxPowerTime_h(maxPowerTime_h),
      idleRatio(idleRatio),
      maxRatio(maxRatio),
      specificFuelConsumption(specificFuelConsumption)
{
    if (taxiTime_h < 0.0 || maxPowerTime_h < 0.0) {
        throw std::invalid_argument(
            "Taxi and take-off times cannot be negative."
        );
    }

    if (idleRatio < 0.0 || maxRatio < 0.0) {
        throw std::invalid_argument(
            "Power or thrust ratios cannot be negative."
        );
    }

    if (specificFuelConsumption < 0.0) {
        throw std::invalid_argument(
            "Specific fuel consumption cannot be negative."
        );
    }
}

std::string TaxiTakeoffSegment::getName() const
{
    if (propulsionType == PropulsionType::Jet) {
        return "Taxi and Take-off - Jet";
    }

    return "Taxi and Take-off - Propeller";
}

double TaxiTakeoffSegment::weightFraction() const
{
    const double fuelFraction =
        (
            taxiTime_h * idleRatio +
            maxPowerTime_h * maxRatio
        ) * specificFuelConsumption;

    const double fraction = 1.0 - fuelFraction;

    if (fraction <= 0.0 || fraction > 1.0) {
        throw std::domain_error(
            "Invalid taxi and take-off weight fraction."
        );
    }

    return fraction;
}