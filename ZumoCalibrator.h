#ifndef ZUMO_CALIBRATOR_H
#define ZUMO_CALIBRATOR_H

#include <Wire.h>
#include <Zumo32U4.h>

class ZumoCalibrator {
public:
    ZumoCalibrator(Zumo32U4LineSensors& lineSensors, Zumo32U4ButtonA& buttonA, Zumo32U4Buzzer& buzzer);
    void calibrateColor();
    void calibrateLineSensors(Zumo32U4Motors& motors);
    int getColorValue(const char* colorName);

private:
    Zumo32U4LineSensors& lineSensors;
    Zumo32U4ButtonA& buttonA;
    Zumo32U4Buzzer& buzzer;
    int black, gray, green, brown;
    unsigned int sensorWaarde[5] = {0, 0, 0, 0, 0};
};


#endif // ZUMO_CALIBRATOR_H