// Press the push switch to switch between blinking and turning off the LED.

const int LED_PIN = 9;
const int INPUT_PIN = 2;

int led_state = HIGH;
// at blink mode, led_sub_state, low if on, high if off.
int led_sub_state = LOW;
int button_state;
int last_button_state = LOW;

unsigned long last_debounce_time = 0;
unsigned long debounce_delay = 50;

unsigned long last_millis = 0;
unsigned long interval = 1000;
unsigned long curr_millis = 0;

void setup() {
  pinMode(INPUT_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);

  // set initial LED state
  digitalWrite(LED_PIN, led_state);
}

void loop() {
  int reading = digitalRead(INPUT_PIN);
  curr_millis = millis();

  // If the switch changed, due to noise or pressing:
  if (reading != last_button_state) {
    // reset the debouncing timer
    last_debounce_time = millis();
  }

  // whatever the reading is at, it's been there for longer than the debounce
  // delay, so take it as the actual current state:
  if ((millis() - last_debounce_time) > debounce_delay) {
    // if the button state has changed:
    if (reading != button_state) {
      button_state = reading;

      // only toggle the LED if the new button state is HIGH
      if (button_state == HIGH) {
        led_state = !led_state;
      }
    }
  }

  // blink mode
  if (led_state == HIGH) {
    if ((curr_millis - last_millis > interval)) {
      if (led_sub_state == LOW) {
        digitalWrite(LED_PIN, HIGH);
        led_sub_state = HIGH;
      } else {
        digitalWrite(LED_PIN, LOW);
        led_sub_state = LOW;
      }
      last_millis = curr_millis;
    }
  }

  // turn off mode
  if (led_state == LOW) {
    digitalWrite(LED_PIN, LOW);
  }

  last_button_state = reading;
}
