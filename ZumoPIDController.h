#ifndef ZUMO_PID_CONTROLLER_H
#define ZUMO_PID_CONTROLLER_H

#include <Wire.h>
#include <Zumo32U4.h>

class ZumoPIDController {
public:
    ZumoPIDController(int maxVermogen, int error_offset, float diff_constant_int, float diff_constant_afg, float diff_constant_error);
    void excecute(int error, Zumo32U4Motors& motors);

private:
    int maxVermogen;
    const int error_offset;
    const float diff_constant_int;
    const float diff_constant_afg;
    const float diff_constant_error;
    int16_t lastError;
    int16_t error_integral;
};

#endif // ZUMO_PID_CONTROLLER_H