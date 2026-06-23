#ifndef AIRCRAFTCLASS_H
#define AIRCRAFTCLASS_H

#include <string>

class AircraftClass {
private:
    std::string name;
    double A;
    double B;

public:
    AircraftClass(const std::string& name, double A, double B);
   ~AircraftClass() = default;
    std::string getName() const;
    double getB() const;
    double emptyWeightFraction(double grossWeight_lbf) const;

    // Classes históricas 
    static AircraftClass sailplane();
    static AircraftClass poweredSailplane();
    static AircraftClass lsaLand();
    static AircraftClass lsaAmphibious();
    static AircraftClass gaSingleEngine();
    static AircraftClass gaTwinPiston();
    static AircraftClass gaTwinTurboprop();
    static AircraftClass agricultural();
    static AircraftClass businessJet();
};

#endif