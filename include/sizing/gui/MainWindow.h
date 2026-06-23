#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "sizing/AircraftClass.h"
#include "sizing/PropulsionType.h"

#include "sizing/segments/TaxiTakeoffSegment.h"
#include "sizing/segments/LandingSegment.h"
class QComboBox;
class QLineEdit;
class QPushButton;
class QTextEdit;
class QRadioButton;
class QButtonGroup;
class QGroupBox;

class MainWindow : public QMainWindow {
    Q_OBJECT

private:
    enum class AircraftClassId {
        Sailplane,
        PoweredSailplane,
        LsaLand,
        LsaAmphibious,
        GaSingleEngine,
        GaTwinPiston,
        GaTwinTurboprop,
        Agricultural,
        BusinessJet
    };

    QComboBox* aircraftClassComboBox;

    QRadioButton* jetRadioButton;
    QRadioButton* propellerRadioButton;
    QButtonGroup* propulsionButtonGroup;

    //Taxi and TO
    QLineEdit* taxiTimeInput;
    QLineEdit* maxPowerTimeInput;
    QLineEdit* taxiIdleRatioInput;
    QLineEdit* taxiMaxRatioInput;
    QLineEdit* taxiSfcInput;


    // Climb
    QLineEdit* climbAltitudeInput;
    QLineEdit* climbRateInput;
    QLineEdit* climbRatioInput;
    QLineEdit* climbSfcInput;

    //Cruise
    QLineEdit* cruiseRangeInput;
    QLineEdit* cruiseSpeedInput;
    QLineEdit* cruiseLiftToDragInput;
    QLineEdit* cruiseSfcInput;
    QLineEdit* propellerEfficiencyInput;
    

    // Descent
    QLineEdit* descentAltitudeInput;
    QLineEdit* descentRateInput;
    QLineEdit* descentRatioInput;
    QLineEdit* descentSfcInput;
    QLineEdit* payloadInput;
    
    //ReserveCruise
    QLineEdit* reserveTimeInput;
    QLineEdit* reserveSpeedInput;
    QLineEdit* reserveLiftToDragInput;
    QLineEdit* reserveSfcInput;
    QLineEdit* reservePropellerEfficiencyInput;
    
    // Landing
    QLineEdit* landingFractionInput;
    
    QLineEdit* crewInput;
    QLineEdit* initialGuessInput;

    QPushButton* calculateButton;
    QTextEdit* outputText;

    void setupInterface();
    void updateCruiseFieldsState();

    AircraftClass getSelectedAircraftClass() const;
    PropulsionType getSelectedPropulsionType() const;
private slots:
    void calculateWeight();

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() = default;
};

#endif