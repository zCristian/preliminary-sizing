#ifndef MISSIONSEGMENT_H
#define MISSIONSEGMENT_H

#include <string>

class MissionSegment {
public:
    virtual ~MissionSegment() = default;

    virtual std::string getName() const = 0;

    virtual double weightFraction() const = 0;
};

#endif
