#ifndef MISSION_H
#define MISSION_H

#include <memory>
#include <vector>

#include "sizing/segments/MissionSegment.h"

class Mission {
private:
    std::vector<std::unique_ptr<MissionSegment>> segments;

public:
    Mission() = default;
    ~Mission() = default;

    void addSegment(std::unique_ptr<MissionSegment> segment);

    double finalWeightFraction() const;

    std::size_t getNumberOfSegments() const;
};

#endif