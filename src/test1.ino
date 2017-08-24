const int LED_PIN = 5;
const int BUTTON_PIN = 2;

volatile bool output_mode; // Turn on LED when true
long count = 0;

void setup () {
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    pinMode(LED_PIN, OUTPUT);
    output_mode = false;
    attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), toggle_LED, FALLING);
    Serial.begin(9600);
    Serial.println("Serial communication start.");
}

void loop() {
    for (auto i = 0; i < 255; ++i) {
        if (output_mode == true) {
            analogWrite(LED_PIN, i);
        }
        else {
            analogWrite(LED_PIN, 0);
        }
        delay(20);
    }
}

void toggle_LED() {
    output_mode = !output_mode;
    Serial.print("Pressed ");
    Serial.print(++count);
    Serial.println(" times.");
}
