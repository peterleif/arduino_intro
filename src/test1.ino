const int LED_PIN = 5;
const int BUTTON_PIN = 4;

bool output_mode; // Turn on LED when true

void setup () {
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    pinMode(LED_PIN, OUTPUT);
    output_mode = false;
}

void loop() {
    if (digitalRead(BUTTON_PIN) == LOW) {
        output_mode = !output_mode;
    }

    if (output_mode == true) {
        for (auto i = 0; i < 255; ++i) {
            analogWrite(LED_PIN, i);
            delay(20);
        }
    }
    else {
        analogWrite(LED_PIN, 0);
    }
}
