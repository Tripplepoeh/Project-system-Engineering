#include "ZumoLineFollower.h"

ZumoLineFollower::ZumoLineFollower() : 
    calibrator(lineSensors, buttonA, buzzer),
    pidController(maxVermogen, 2000, 1.5, 1.5, 0.5), // maxvermogen, target error, const_int, const_afg, const_error
    maxVermogen(400) {}

void ZumoLineFollower::setup() {
    buttonA.waitForButton();
    lineSensors.initFiveSensors();
    calibrator.calibrateColor();
    calibrator.calibrateLineSensors(motors);
    delay(1000);
    buttonA.waitForButton();
    delay(200);
}

void ZumoLineFollower::checkuitkomst() {
    Serial.print(sensorWaarde[1]);
    Serial.print(" ");
    Serial.print(sensorWaarde[2]);
    Serial.print(" ");
    Serial.print(sensorWaarde[3]);
    Serial.println();
}

void ZumoLineFollower::drive() {
    int green = calibrator.getColorValue("green");
    int brown = calibrator.getColorValue("brown");
    int black = calibrator.getColorValue("black");
    int gray = calibrator.getColorValue("gray");

    if (sensorWaarde[2] > green - 30 && sensorWaarde[2] < green + 30) {
        maxVermogen = 200;
    } else if (sensorWaarde[2] > brown - 30 && sensorWaarde[2] < brown + 30) {
        motors.setSpeeds(0, 0);
        buzzer.play(">g32");
        motors.setSpeeds(100, 100);
        delay(1500);
    } else if (sensorWaarde[2] > black - 30 && sensorWaarde[2] < black + 30) {
        maxVermogen = 350;
    } else if (sensorWaarde[2] > gray - 30 && sensorWaarde[2] < gray + 30) {
        // implementatie van het afslaan naar links of rechts bij grijs detectie
    }
    else if ((sensorWaarde[1] > gray - 30 && sensorWaarde[1] < gray + 30) && (sensorWaarde[3] > gray - 30 && sensorWaarde[3] < gray + 30)) {
        buzzer.play(">g32");
        motors.setSpeeds(0, 0);
        while (getPitch() > 0) {//implementatie van pitch is 0 en dan pas weer verder rijden.
            motors.setSpeeds(0, 0);
        }
        delay(1000);
        motors.setSpeeds(100, 100);
    }
    else {
        proxSensor.actuatesensor();
    return 0;
    }

}

void ZumoLineFollower::loop() {
    lineSensors.read(sensorWaarde);
    drive();
    int error = lineSensors.readLine(sensorWaarde);
    pidController.excecute(error, motors);
}