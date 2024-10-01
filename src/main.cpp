#include <LiquidCrystal_I2C.h>  // Included from pio lib
#include <HCSR04.h>  // Included manually from lib
// TODO: set the 'cmath' library to be included
#include <math.h> // NOLINT(*-deprecated-headers)

UltraSonicDistanceSensor hc(12, 10);
LiquidCrystal_I2C lcd(0x27, 16, 2);

constexpr double TARGET_DISTANCE = 12.5;
constexpr double VASE_DIAMETER = 7;
double resetDistance;

double inline calculateArea(const double diameter) {
    return M_PI * pow(diameter / 2, 2);
}


void setup() {
    lcd.init();
    lcd.backlight();
    Serial.begin(9600);
}

void loop() {
    double distance = hc.measureDistanceCm();
    Serial.println(distance);

    // TODO: set 'TARGET DISTANCE' with the current distance of the vase using 'distance' for the measurements

    if (distance < TARGET_DISTANCE) {
        resetDistance = TARGET_DISTANCE - distance;;
        lcd.clear();

        lcd.setCursor(0, 0);
        lcd.print("Deep");
        lcd.setCursor(0, 1);
        lcd.print(resetDistance);

        lcd.setCursor(8, 0);
        lcd.print("Vol");
        lcd.setCursor(8, 1);
        lcd.print(resetDistance * calculateArea(VASE_DIAMETER));

        Serial.println(resetDistance);  // Optional for watching the reset distance in the serial monitor
        delay(150);
    }
}
