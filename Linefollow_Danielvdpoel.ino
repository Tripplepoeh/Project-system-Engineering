#include <Wire.h>
#include <Zumo32U4.h>

Zumo32U4LineSensors lineSensors;
Zumo32U4ButtonA buttonA;
Zumo32U4Motors motors;

// waarden sensor output
unsigned int sensorWaarde[5];

// toewijzen constanten (deze moeten nog getest worden, met de huidge waarden zal het nog niet perfect werken)
const int maxVermogen = 200; // hiermee kan snelheid gelimiteerd worden
const int error_offset = 2000; // moet getest worden, 2000 volgensmij standaard
const int diff_constant_int = 0.1; // range 0.01 - 1
const int diff_constant_afg = 6; // range 0 - ???
const int diff_constant_error = 1; // range 1 - ???

// initiele waarde
int lastError = 0; // initele waarde geven aan lastError anders werkt algoritme niet


void setup()
{
    // Wacht op button zodat de robot niet uit zichzelf gaat bewegen
    buttonA.waitForButton();
    // Initialiseer de lijnsensors
    lineSensors.initFiveSensors();
    // Roep de funcite aan die de sensors calibreert
    calibrateSensors();
    // Wacht 1 seconde
    delay(1000);
}

void calibrateSensors()
{
    // Wacht 3 seconden en draai dan over de lijn heen 
    delay(3000);
    // Deze for loop zorgt er voor dat de robot eerst naar links draait en dan naar rechts
    for(int i = 0; i < 120; i++)
    {
        if (i > 30 && i <= 90) {
            motors.setSpeeds(-200, 200);
        }
        else {
            motors.setSpeeds(200, -200);
        }

        lineSensors.calibrate(); // Moet nog een manier vinden om dit ook daadwerkelijk inzichtelijk te maken, ben er mee bezig
        }

// Motors stoppen
motors.setSpeeds(0, 0);
}

void sensor_translatie()
{
    // Om de error te kunnen berekenen hebben wij de waarde nodig
    // van de sensor, deze word zelf niet aangeroepen maar wel gebruikt 
    // voor het berekenen van de rest van de waardes.
    int error = lineSensors.readLine(sensorWaarde);

    // De error_afstand is de afstand tot het midden van de lijn, deze wordt
    // berekend door de afgelezen waarde van de sensor en de error_offset hier 
    // van af te trekken. Dit geeft dan een exacte waarde van de afstand tot het 
    // midden van de lijn.
    int error_afstand = error - error_offset;

    // Voor het PID algoritme gaan we naast de error_afstand nog 2 extra waarden gebruiken,
    // allereerst gaan we Derivative (afgeleide) berekenen door de vorige error af te trekken van de huidige error,
    // hierdoor krijg je een delta tussen de errors en deze zorgt er vervolgens voor dat de mate van 
    // correctie naar het midden van de lijn af gaat nemen.
    int error_afg = error_afstand - lastError

    // voor de 3e term van het PID deel tellen we de huidige error op bij de laatste error, dit is dan de "integraal".
    float error_integral += error_afstand

    // Hier voegen we alle delen bij elkaar, elk onderdeel heeft zijn eigen gewicht wat aangepast kan worden met de 
    // constanten die boven aan de code staan. Dit geeft de mogelijkheid om het volgen van de lijn te fine-tunen.
    int error_output = (error_afstand * diff_constant_error) + (error_integral * diff_constant_int) + (diff_constant_afg * error_afg);



    lastError = error_afstand; // lastError schuift door zodat de loop blijft updaten.

    int vermogen_links = maxVermogen + error_output;
    int vermogen_rechts = maxVermogen - error_output;

    motors.setSpeeds(vermogen_links, vermogen_rechts);
}


void loop()
{
    sensor_translatie();
    delay(500);
}
