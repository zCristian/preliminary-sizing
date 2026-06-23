#include "sizing/AircraftClass.h"

#include <cmath>
#include <stdexcept>
AircraftClass::AircraftClass(const std::string& name, double A, double B)
    : name(name), A(A), B(B) {}

std::string AircraftClass::getName() const {
    return name;
}


double AircraftClass::emptyWeightFraction(double grossWeight_lbf) const {
    if (grossWeight_lbf <= 0.0) {
        throw std::invalid_argument(
            "Gross weight must be greater than zero."
        );
    }

    return A + B * std::log(grossWeight_lbf);
}
double AircraftClass::getB() const {
    return B;
}
// Coeficientes em lbf
AircraftClass AircraftClass::sailplane() {
    return AircraftClass("Sailplane", 0.2950, 0.0386);
}

AircraftClass AircraftClass::poweredSailplane() {
    return AircraftClass("Powered Sailplane", 0.3068, 0.0510);
}

AircraftClass AircraftClass::lsaLand() {
    return AircraftClass("LSA Land", 1.5451, -0.1402);
}

AircraftClass AircraftClass::lsaAmphibious() {
    return AircraftClass("LSA Amphibious", 1.6351, -0.1402);
}

AircraftClass AircraftClass::gaSingleEngine() {
    return AircraftClass("GA Single Engine", 0.8841, -0.0333);
}

AircraftClass AircraftClass::gaTwinPiston() {
    return AircraftClass("GA Twin Piston", 0.4074, 0.0253);
}

AircraftClass AircraftClass::gaTwinTurboprop() {
    return AircraftClass("GA Twin Turboprop", 0.5319, 0.0066);
}

AircraftClass AircraftClass::agricultural() {
    return AircraftClass("Agricultural", 1.4029, -0.0995);
}

AircraftClass AircraftClass::businessJet() {
    return AircraftClass("Business Jet", 0.9038, -0.03163);
}