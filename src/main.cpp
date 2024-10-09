#include <LiquidCrystal_I2C.h>  // Included from pio lib
#include <HCSR04.h>  // Included manually from lib
// TODO: set the 'cmath' library to be included
#include <math.h> // NOLINT(*-deprecated-headers)

UltraSonicDistanceSensor hc(12, 10);
LiquidCrystal_I2C lcd(0x27, 16, 2);

constexpr double TARGET_DISTANCE = 9.9;
constexpr double VASE_DIAMETER = 6.9;
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

    if (distance < TARGET_DISTANCE) {
        distance == -1 ? distance = TARGET_DISTANCE  : distance;
        resetDistance = TARGET_DISTANCE - distance;
        lcd.clear();

        lcd.setCursor(0, 0);
        lcd.print("Deep");
        if (resetDistance >= 0.2) {
            lcd.setCursor(0, 1);
            lcd.print(resetDistance);
        } else {
            lcd.setCursor(0, 1);
            lcd.print(0.00);
        }        lcd.setCursor(4, 1);
        lcd.print("cm");

        lcd.setCursor(8, 0);
        lcd.print("Vol");
        if (resetDistance >= 0.2) {
            lcd.setCursor(8, 1);
            lcd.print(resetDistance * calculateArea(VASE_DIAMETER));
        } else {
            lcd.setCursor(8, 1);
            lcd.print(0.00);
        }
        lcd.setCursor(13, 1);
        lcd.print("ml");

        Serial.println(resetDistance);  // Optional for watching the reset distance in the serial monitor
        delay(1000);
    }
}
