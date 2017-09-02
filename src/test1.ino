#include <MsTimer2.h>
#include <Wire.h>
#include <ST7032.h>

const int LED_PIN = 5;
const int BUTTON_PIN = 2;
const int PERIOD = 3000;
const int ADT7410_ADDR = 0x48;

volatile bool output_mode; // Turn on LED when true
long count = 0;

ST7032 lcd;

void setup () {
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    pinMode(LED_PIN, OUTPUT);

    output_mode = false;
    attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), toggle_LED, FALLING);
    Serial.begin(9600);
    Serial.println("Serial communication start.");
    MsTimer2::set(PERIOD, print);
    MsTimer2::start();
    // set up the LCD's number of columns and rows:
    lcd.begin(16, 2);
    lcd.setContrast(10);
    lcd.print("hello, world!");
    Wire.begin();
}

void loop() {
    uint16_t temp_u16;
    float temp_f;

    Wire.requestFrom(ADT7410_ADDR, 2);
    temp_u16 = Wire.read() << 8 | Wire.read();
    temp_u16 >>= 3;

    if (temp_u16 & 0x1000) {
        temp_f = temp_u16/16.0 - 512.0;
    }
    else {
        temp_f = temp_u16/16.0;
    }
    lcd.setCursor(0, 1);
    // print the number of seconds since reset:
    lcd.print(temp_f);
    delay(1000);
}

void toggle_LED() {
    output_mode = !output_mode;
    Serial.print("Pressed ");
    Serial.print(++count);
    Serial.println(" times.");
}

void print() {
    Serial.println("3秒経ちました");
}
