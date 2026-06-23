#include "sizing/Mission.h"

#include <stdexcept>
#include <utility>

void Mission::addSegment(
    std::unique_ptr<MissionSegment> segment
)
{
    if (!segment) {
        throw std::invalid_argument(
            "Mission segment cannot be null."
        );
    }

    segments.push_back(std::move(segment));
}

double Mission::finalWeightFraction() const
{
    double finalFraction = 1.0;

    for (const auto& segment : segments) {
        finalFraction *= segment->weightFraction();
    }

    return finalFraction;
}

std::size_t Mission::getNumberOfSegments() const
{
    return segments.size();
}