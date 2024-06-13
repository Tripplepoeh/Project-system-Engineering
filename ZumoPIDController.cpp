#include "ZumoPIDController.h"

ZumoPIDController::ZumoPIDController(int maxVermogen, int error_offset, float diff_constant_int, float diff_constant_afg, float diff_constant_error)
    : maxVermogen(maxVermogen), error_offset(error_offset), diff_constant_int(diff_constant_int), diff_constant_afg(diff_constant_afg), diff_constant_error(diff_constant_error), lastError(0), error_integral(0) {}

void ZumoPIDController::excecute(int error, Zumo32U4Motors& motors) {
    int16_t error_afstand = error - error_offset;
    int16_t error_afg = error_afstand - lastError;
    error_integral += error_afstand;
    int16_t error_output = (error_afstand * diff_constant_error) + (error_integral * diff_constant_int) + (diff_constant_afg * error_afg);

    lastError = error_afstand;

    int16_t vermogen_links = maxVermogen + error_output;
    int16_t vermogen_rechts = maxVermogen - error_output;

    vermogen_links = constrain(vermogen_links, 0, maxVermogen);
    vermogen_rechts = constrain(vermogen_rechts, 0, maxVermogen);

    motors.setSpeeds(vermogen_links, vermogen_rechts);
    //Serial.println(error);
}