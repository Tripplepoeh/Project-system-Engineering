#include "ZumoCalibrator.h"

ZumoCalibrator::ZumoCalibrator(Zumo32U4LineSensors& sensors, Zumo32U4ButtonA& button, Zumo32U4Buzzer& buzz)
    : lineSensors(sensors), buttonA(button), buzzer(buzz), black(0), gray(0), green(0), brown(0) {}

void ZumoCalibrator::calibrateColor() {
    lineSensors.read(sensorWaarde);
    black = sensorWaarde[2];
    buzzer.play(">g32");
    buttonA.waitForButton();
    lineSensors.read(sensorWaarde);
    gray = sensorWaarde[2];
    buzzer.play(">g32");
    buttonA.waitForButton();
    lineSensors.read(sensorWaarde);
    green = sensorWaarde[2];
    buzzer.play(">g32");
    buttonA.waitForButton();
    lineSensors.read(sensorWaarde);
    brown = sensorWaarde[2];
    buzzer.play(">g32");
    buttonA.waitForButton();
}

void ZumoCalibrator::calibrateLineSensors(Zumo32U4Motors& motors) {
    delay(3000);
    for (int i = 0; i < 90; i++) {
        motors.setSpeeds(300, -300);
        lineSensors.calibrate();
        lineSensors.readCalibrated(sensorWaarde);
    }
    motors.setSpeeds(0, 0);
}

int ZumoCalibrator::getColorValue(const char* colorName) {
    if (strcmp(colorName, "black") == 0) return black;
    if (strcmp(colorName, "gray") == 0) return gray;
    if (strcmp(colorName, "green") == 0) return green;
    if (strcmp(colorName, "brown") == 0) return brown;
    return -1;
}