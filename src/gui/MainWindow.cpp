#include "sizing/Mission.h"
#include "sizing/WeightEstimator.h"
#include "sizing/gui/MainWindow.h"
#include "sizing/segments/TaxiTakeoffSegment.h"
#include "sizing/segments/ClimbSegment.h"
#include "sizing/segments/JetCruiseRangeSegment.h"
#include "sizing/segments/PropellerCruiseRangeSegment.h"
#include "sizing/segments/DescentSegment.h"
#include "sizing/segments/JetReserveCruiseSegment.h"
#include "sizing/segments/PropellerReserveCruiseSegment.h"
#include "sizing/segments/LandingSegment.h"

#include <QIcon>
#include <QGroupBox>
#include <QWidget>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QString>
#include <QRadioButton>
#include <QButtonGroup>
#include <QHBoxLayout>
#include <QGridLayout>
#include <exception>



MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    setupInterface();
    setWindowIcon(
        QIcon(":/icons/assets/aircraft-icon.png")
    );
}

void MainWindow::setupInterface()
{
    QWidget* central = new QWidget(this);
    QVBoxLayout* mainLayout = new QVBoxLayout(central);
    QFormLayout* formLayout = new QFormLayout();

    aircraftClassComboBox = new QComboBox(this);

    aircraftClassComboBox->addItem(
        "Sailplane",
        static_cast<int>(AircraftClassId::Sailplane)
    );

    aircraftClassComboBox->addItem(
        "Powered Sailplane",
        static_cast<int>(AircraftClassId::PoweredSailplane)
    );

    aircraftClassComboBox->addItem(
        "LSA Land",
        static_cast<int>(AircraftClassId::LsaLand)
    );

    aircraftClassComboBox->addItem(
        "LSA Amphibious",
        static_cast<int>(AircraftClassId::LsaAmphibious)
    );

    aircraftClassComboBox->addItem(
        "GA Single Engine",
        static_cast<int>(AircraftClassId::GaSingleEngine)
    );

    aircraftClassComboBox->addItem(
        "GA Twin Piston",
        static_cast<int>(AircraftClassId::GaTwinPiston)
    );

    aircraftClassComboBox->addItem(
        "GA Twin Turboprop",
        static_cast<int>(AircraftClassId::GaTwinTurboprop)
    );

    aircraftClassComboBox->addItem(
        "Agricultural",
        static_cast<int>(AircraftClassId::Agricultural)
    );

    aircraftClassComboBox->addItem(
        "Business Jet",
        static_cast<int>(AircraftClassId::BusinessJet)
    );

    
    //Propulsion Type
    jetRadioButton = new QRadioButton("Jet", this);
    propellerRadioButton = new QRadioButton("Propeller", this);
    propellerRadioButton->setChecked(true);

    propulsionButtonGroup = new QButtonGroup(this);
    propulsionButtonGroup->addButton(jetRadioButton);
    propulsionButtonGroup->addButton(propellerRadioButton);

    connect(
        jetRadioButton,
        &QRadioButton::toggled,
        this,
        &MainWindow::updateCruiseFieldsState
    );

    connect(
        propellerRadioButton,
        &QRadioButton::toggled,
        this,
        &MainWindow::updateCruiseFieldsState
    );

    QHBoxLayout* propulsionLayout = new QHBoxLayout();
    propulsionLayout->addWidget(jetRadioButton);
    propulsionLayout->addWidget(propellerRadioButton);

    //Weight Input
    payloadInput = new QLineEdit(this);
    crewInput = new QLineEdit(this);
    initialGuessInput = new QLineEdit(this);

    //Taxi and TO Section
    QGroupBox* taxiGroupBox = new QGroupBox("Taxi and Take-off", this);
    QFormLayout* taxiLayout = new QFormLayout(taxiGroupBox);

    taxiTimeInput = new QLineEdit(this);
    maxPowerTimeInput = new QLineEdit(this);
    taxiIdleRatioInput = new QLineEdit(this);
    taxiMaxRatioInput = new QLineEdit(this);
    taxiSfcInput = new QLineEdit(this);

    taxiLayout->addRow("Taxi time [min]:", taxiTimeInput);
    taxiLayout->addRow("Max-power time [s]:", maxPowerTimeInput);
    taxiLayout->addRow("Idle ratio:", taxiIdleRatioInput);
    taxiLayout->addRow("Max ratio:", taxiMaxRatioInput);
    taxiLayout->addRow("SFC:", taxiSfcInput);

    //Climb Section
    QGroupBox* climbGroupBox = new QGroupBox("Climb", this);
    QFormLayout* climbLayout = new QFormLayout(climbGroupBox);

    climbAltitudeInput = new QLineEdit(this);
    climbRateInput = new QLineEdit(this);
    climbRatioInput = new QLineEdit(this);
    climbSfcInput = new QLineEdit(this);

    climbLayout->addRow("Altitude change [ft]:", climbAltitudeInput);
    climbLayout->addRow("Average ROC [ft/min]:", climbRateInput);
    climbLayout->addRow("Climb ratio:", climbRatioInput);
    climbLayout->addRow("SFC:", climbSfcInput);

    //Cruise Section
    QGroupBox* cruiseGroupBox = new QGroupBox("Cruise Range", this);
    QFormLayout* cruiseLayout = new QFormLayout(cruiseGroupBox);

    cruiseRangeInput = new QLineEdit(this);
    cruiseSpeedInput = new QLineEdit(this);
    cruiseLiftToDragInput = new QLineEdit(this);
    cruiseSfcInput = new QLineEdit(this);
    propellerEfficiencyInput = new QLineEdit(this);
    cruiseLayout->addRow("Range [nm]:", cruiseRangeInput);
    cruiseLayout->addRow("Speed [KTAS]:", cruiseSpeedInput);
    cruiseLayout->addRow("L/D:", cruiseLiftToDragInput);
    cruiseLayout->addRow("SFC:", cruiseSfcInput);
    cruiseLayout->addRow("Propeller efficiency:", propellerEfficiencyInput);

    //Descent Section
    QGroupBox* descentGroupBox = new QGroupBox("Descent", this);

    QFormLayout* descentLayout = new QFormLayout(descentGroupBox);

    descentAltitudeInput = new QLineEdit(this);
    descentRateInput = new QLineEdit(this);
    descentRatioInput = new QLineEdit(this);
    descentSfcInput = new QLineEdit(this);

    descentLayout->addRow("Altitude change [ft]:", descentAltitudeInput);
    descentLayout->addRow("Average ROD [ft/min]:", descentRateInput);
    descentLayout->addRow("Descent ratio:", descentRatioInput);
    descentLayout->addRow("SFC:", descentSfcInput);

    // Reserve Cruise Section
    QGroupBox* reserveGroupBox =
        new QGroupBox("Reserve Cruise", this);

    QFormLayout* reserveLayout =
        new QFormLayout(reserveGroupBox);

    reserveTimeInput = new QLineEdit(this);
    reserveSpeedInput = new QLineEdit(this);
    reserveLiftToDragInput = new QLineEdit(this);
    reserveSfcInput = new QLineEdit(this);
    reservePropellerEfficiencyInput = new QLineEdit(this);

    updateCruiseFieldsState();

    reserveLayout->addRow("Reserve time [h]:", reserveTimeInput);
    reserveLayout->addRow("Speed [KTAS]:", reserveSpeedInput);
    reserveLayout->addRow("L/D:", reserveLiftToDragInput);
    reserveLayout->addRow("SFC:", reserveSfcInput);
    reserveLayout->addRow(
        "Propeller efficiency:",
        reservePropellerEfficiencyInput
    );

    // Landing Section
    QGroupBox* landingGroupBox =
        new QGroupBox("Landing and Shutdown", this);

    QFormLayout* landingLayout =
        new QFormLayout(landingGroupBox);

    landingFractionInput = new QLineEdit(this);

    landingLayout->addRow(
        "Landing weight fraction:",
        landingFractionInput
    );

    calculateButton = new QPushButton("Calcular", this);

    outputText = new QTextEdit(this);
    outputText->setReadOnly(true);

    formLayout->addRow("Aircraft Class:", aircraftClassComboBox);
    formLayout->addRow("Propulsion:", propulsionLayout);
    formLayout->addRow("Payload [lbf]:", payloadInput);
    formLayout->addRow("Crew [lbf]:", crewInput);
    formLayout->addRow("Initital Guess W0 [lbf]:", initialGuessInput);
    
    QGridLayout* missionLayout = new QGridLayout();

    missionLayout->addWidget(taxiGroupBox,    0, 0);
    missionLayout->addWidget(climbGroupBox,   0, 1);

    missionLayout->addWidget(cruiseGroupBox,  1, 0);
    missionLayout->addWidget(descentGroupBox, 1, 1);

    missionLayout->addWidget(reserveGroupBox, 2, 0);
    missionLayout->addWidget(landingGroupBox, 2, 1);

    mainLayout->addLayout(formLayout);
    mainLayout->addLayout(missionLayout);
    mainLayout->addWidget(calculateButton);
    mainLayout->addWidget(outputText);

    setCentralWidget(central);
    setWindowTitle("Preliminary Sizing");

    connect(
        calculateButton,
        &QPushButton::clicked,
        this,
        &MainWindow::calculateWeight
    );
}

AircraftClass MainWindow::getSelectedAircraftClass() const
{
    const int selectedValue =
        aircraftClassComboBox->currentData().toInt();

    const auto selectedClass =
        static_cast<AircraftClassId>(selectedValue);

    switch (selectedClass) {
        case AircraftClassId::Sailplane:
            return AircraftClass::sailplane();

        case AircraftClassId::PoweredSailplane:
            return AircraftClass::poweredSailplane();

        case AircraftClassId::LsaLand:
            return AircraftClass::lsaLand();

        case AircraftClassId::LsaAmphibious:
            return AircraftClass::lsaAmphibious();

        case AircraftClassId::GaSingleEngine:
            return AircraftClass::gaSingleEngine();

        case AircraftClassId::GaTwinPiston:
            return AircraftClass::gaTwinPiston();

        case AircraftClassId::GaTwinTurboprop:
            return AircraftClass::gaTwinTurboprop();

        case AircraftClassId::Agricultural:
            return AircraftClass::agricultural();

        case AircraftClassId::BusinessJet:
            return AircraftClass::businessJet();
    }

    return AircraftClass::gaSingleEngine();
}

PropulsionType MainWindow::getSelectedPropulsionType() const
{
    if (jetRadioButton->isChecked()) {
        return PropulsionType::Jet;
    }

    return PropulsionType::Propeller;
}

void MainWindow::updateCruiseFieldsState()
{
    const bool isJet =
        jetRadioButton->isChecked();

    cruiseSpeedInput->setEnabled(isJet);
    propellerEfficiencyInput->setEnabled(!isJet);

    reserveSpeedInput->setEnabled(!isJet);
    reservePropellerEfficiencyInput->setEnabled(!isJet);
}

void MainWindow::calculateWeight()
{
    const AircraftClass aircraftClass =
        getSelectedAircraftClass();

    const PropulsionType propulsionType =
        getSelectedPropulsionType();

    bool valuesOk = true;
    bool currentValueOk;

    const double grossWeightInitialGuess_lbf =
        initialGuessInput->text().toDouble(&currentValueOk);

    valuesOk = valuesOk && currentValueOk;

    const double payloadWeight_lbf =
        payloadInput->text().toDouble(&currentValueOk);

    valuesOk = valuesOk && currentValueOk;

    const double crewWeight_lbf =
        crewInput->text().toDouble(&currentValueOk);

    valuesOk = valuesOk && currentValueOk;


    // Taxi and take-off
    const double taxiTime_min =
        taxiTimeInput->text().toDouble(&currentValueOk);

    valuesOk = valuesOk && currentValueOk;

    const double maxPowerTime_s =
        maxPowerTimeInput->text().toDouble(&currentValueOk);

    valuesOk = valuesOk && currentValueOk;

    const double taxiIdleRatio =
        taxiIdleRatioInput->text().toDouble(&currentValueOk);

    valuesOk = valuesOk && currentValueOk;

    const double taxiMaxRatio =
        taxiMaxRatioInput->text().toDouble(&currentValueOk);

    valuesOk = valuesOk && currentValueOk;

    const double taxiSfc =
        taxiSfcInput->text().toDouble(&currentValueOk);

    valuesOk = valuesOk && currentValueOk;

    // Climb
    const double climbAltitude_ft =
        climbAltitudeInput->text().toDouble(&currentValueOk);

    valuesOk = valuesOk && currentValueOk;

    const double climbRate_fpm =
        climbRateInput->text().toDouble(&currentValueOk);

    valuesOk = valuesOk && currentValueOk;

    const double climbRatio =
        climbRatioInput->text().toDouble(&currentValueOk);

    valuesOk = valuesOk && currentValueOk;

    const double climbSfc =
        climbSfcInput->text().toDouble(&currentValueOk);

    valuesOk = valuesOk && currentValueOk;

    // Cruise
    const double cruiseRange_nm =
        cruiseRangeInput->text().toDouble(&currentValueOk);

    valuesOk = valuesOk && currentValueOk;
   
    double cruiseSpeed_ktas = 0.0;
    double propellerEfficiency = 0.0;

    if (propulsionType == PropulsionType::Jet) {
        cruiseSpeed_ktas =
            cruiseSpeedInput->text().toDouble(&currentValueOk);

        valuesOk = valuesOk && currentValueOk;
    }
    else {
        propellerEfficiency =
            propellerEfficiencyInput->text().toDouble(&currentValueOk);

        valuesOk = valuesOk && currentValueOk;
    }

    const double cruiseLiftToDrag =
        cruiseLiftToDragInput->text().toDouble(&currentValueOk);

    valuesOk = valuesOk && currentValueOk;

    const double cruiseSfc =
        cruiseSfcInput->text().toDouble(&currentValueOk);

    valuesOk = valuesOk && currentValueOk;

    

    valuesOk = valuesOk && currentValueOk;

    // Descent
    const double descentAltitude_ft =
        descentAltitudeInput->text().toDouble(&currentValueOk);

    valuesOk = valuesOk && currentValueOk;

    const double descentRate_fpm =
        descentRateInput->text().toDouble(&currentValueOk);

    valuesOk = valuesOk && currentValueOk;

    const double descentRatio =
        descentRatioInput->text().toDouble(&currentValueOk);

    valuesOk = valuesOk && currentValueOk;

    const double descentSfc =
        descentSfcInput->text().toDouble(&currentValueOk);

    valuesOk = valuesOk && currentValueOk;

    // Reserve cruise
    const double reserveTime_h =
        reserveTimeInput->text().toDouble(&currentValueOk);

    valuesOk = valuesOk && currentValueOk;

    const double reserveLiftToDrag =
        reserveLiftToDragInput->text().toDouble(&currentValueOk);

    valuesOk = valuesOk && currentValueOk;

    const double reserveSfc =
        reserveSfcInput->text().toDouble(&currentValueOk);

    valuesOk = valuesOk && currentValueOk;

    double reserveSpeed_ktas = 0.0;
    double reservePropellerEfficiency = 0.0;

    if (propulsionType == PropulsionType::Propeller) {
        reserveSpeed_ktas =
            reserveSpeedInput->text().toDouble(&currentValueOk);

        valuesOk = valuesOk && currentValueOk;

        reservePropellerEfficiency =
            reservePropellerEfficiencyInput
                ->text()
                .toDouble(&currentValueOk);

        valuesOk = valuesOk && currentValueOk;
    }
    // Landing
    const double landingFractionInputValue =
        landingFractionInput->text().toDouble(&currentValueOk);

    valuesOk = valuesOk && currentValueOk;

    if (!valuesOk) {
        outputText->setText(
            "Error: all fields must contain valid numeric values."
        );

        return;
    }

    try {

        Mission mission;

        // Taxi and take-off
        auto taxiTakeoff =
            std::make_unique<TaxiTakeoffSegment>(
                propulsionType,
                taxiTime_min / 60.0,
                maxPowerTime_s / 3600.0,
                taxiIdleRatio,
                taxiMaxRatio,
                taxiSfc
            );

        const double taxiFraction =
            taxiTakeoff->weightFraction();

        mission.addSegment(
            std::move(taxiTakeoff)
        );

        // Climb
        auto climb =
            std::make_unique<ClimbSegment>(
                propulsionType,
                climbAltitude_ft,
                climbRate_fpm,
                climbRatio,
                climbSfc
            );

        const double climbFraction =
            climb->weightFraction();

        mission.addSegment(
            std::move(climb)
        );

        // Cruise
        std::unique_ptr<MissionSegment> cruise;

        if (propulsionType == PropulsionType::Jet) {
            cruise =
                std::make_unique<JetCruiseRangeSegment>(
                    cruiseRange_nm,
                    cruiseSpeed_ktas,
                    cruiseLiftToDrag,
                    cruiseSfc
                );
        }
        else {
            cruise =
                std::make_unique<PropellerCruiseRangeSegment>(
                    cruiseRange_nm,
                    cruiseLiftToDrag,
                    cruiseSfc,
                    propellerEfficiency
                );
        }

        const double cruiseFraction =
            cruise->weightFraction();

        const QString cruiseName =
            QString::fromStdString(
                cruise->getName()
            );

        mission.addSegment(
            std::move(cruise)
        );

        // Descent
        auto descent =
            std::make_unique<DescentSegment>(
                propulsionType,
                descentAltitude_ft,
                descentRate_fpm,
                descentRatio,
                descentSfc
            );

        const double descentFraction =
            descent->weightFraction();

        mission.addSegment(
            std::move(descent)
        );

        // Reserve cruise
        std::unique_ptr<MissionSegment> reserveCruise;

        if (propulsionType == PropulsionType::Jet) {
            reserveCruise =
                std::make_unique<JetReserveCruiseSegment>(
                    reserveTime_h,
                    reserveLiftToDrag,
                    reserveSfc
                );
        }
        else {
            reserveCruise =
                std::make_unique<PropellerReserveCruiseSegment>(
                    reserveTime_h,
                    reserveSpeed_ktas,
                    reserveLiftToDrag,
                    reserveSfc,
                    reservePropellerEfficiency
                );
        }

        const double reserveFraction =
            reserveCruise->weightFraction();

        const QString reserveName =
            QString::fromStdString(
                reserveCruise->getName()
            );

        mission.addSegment(
            std::move(reserveCruise)
        );

        // Landing and shutdown
        auto landing =
            std::make_unique<LandingSegment>(
                landingFractionInputValue
            );

        const double landingFraction =
            landing->weightFraction();

        mission.addSegment(
            std::move(landing)
        );

        // Final mission fraction
        const double missionFraction =mission.finalWeightFraction();

        // Gross-weight estimation
        const WeightEstimator estimator(aircraftClass,mission,crewWeight_lbf,payloadWeight_lbf);

        const double estimatedGrossWeight_lbf =estimator.estimateGrossWeight(grossWeightInitialGuess_lbf);

        const double emptyWeightFraction =aircraftClass.emptyWeightFraction(estimatedGrossWeight_lbf);

        const double emptyWeight_lbf = emptyWeightFraction * estimatedGrossWeight_lbf;

        const double finalMissionWeight_lbf = missionFraction * estimatedGrossWeight_lbf;

        const double fuelWeight_lbf = estimatedGrossWeight_lbf - finalMissionWeight_lbf;

        const double finalResidual = estimator.residual(estimatedGrossWeight_lbf);

        // Output
        QString result;

        result += "Aircraft class: ";
        result += QString::fromStdString(
            aircraftClass.getName()
        );

        result += "\n\nNumber of mission segments: ";
        result += QString::number(
            mission.getNumberOfSegments()
        );

        result += "\n\nFinal mission fraction";
        result += "\nWN/W0: ";
        result += QString::number(
            missionFraction,
            'f',
            6
        );

        result += "\n\nEstimated gross weight";
        result += "\nW0: ";
        result += QString::number(
            estimatedGrossWeight_lbf,
            'f',
            2
        );
        result += " lbf";

        result += "\n\nEstimated empty weight";
        result += "\nWe/W0: ";
        result += QString::number(
            emptyWeightFraction,
            'f',
            6
        );

        result += "\nWe: ";
        result += QString::number(
            emptyWeight_lbf,
            'f',
            2
        );
        result += " lbf";

        result += "\n\nEstimated fuel weight";
        result += "\nWfuel: ";
        result += QString::number(
            fuelWeight_lbf,
            'f',
            2
        );
        result += " lbf";

        result += "\n\nSolver residual";
        result += "\nResidual: ";
        result += QString::number(
            finalResidual,
            'e',
            3
        );

        outputText->setText(result);
    }
    catch (const std::exception& error) {
        outputText->setText(
            "Error: " + QString::fromStdString(error.what())
        );
    }
}