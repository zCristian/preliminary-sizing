#include "sizing/segments/LandingSegment.h"

#include <stdexcept>

LandingSegment::LandingSegment(double landingFraction)
    : landingFraction(landingFraction)
{
    if (landingFraction < 0.99 || landingFraction > 1.0) {
        throw std::invalid_argument(
            "Landing weight fraction must be between 0.99 and 1.00."
        );
    }
}

std::string LandingSegment::getName() const
{
    return "Landing and Shutdown";
}

double LandingSegment::weightFraction() const
{
    return landingFraction;
}