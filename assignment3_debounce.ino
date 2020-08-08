const int LED_PIN = 9;
const int INPUT_PIN = 2;
const int VOLUME_PIN = A0;

volatile int led_state = HIGH;
volatile int button_state = LOW;
int last_button_state = LOW;
int reading;
int volume = 0;

volatile int interruption_count = 0;

volatile unsigned long last_debounce_time = 0;
unsigned long debounce_delay = 10;

unsigned long ten_seconds_ago = 0;

unsigned long curr_time = 0;

void setup() {
  Serial.begin(9600);
  pinMode(INPUT_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(VOLUME_PIN, INPUT);

  // set initial LED state
  digitalWrite(LED_PIN, led_state);

  // digitalPinToInterrupt(INPUT_PIN) == 0
  attachInterrupt(digitalPinToInterrupt(INPUT_PIN), interrupt, FALLING);
}

void loop() {
  reading = digitalRead(INPUT_PIN);
  volume = analogRead(VOLUME_PIN);
  curr_time = millis();

  digitalWrite(LED_PIN, led_state);

  last_button_state = reading;

  if(millis() - ten_seconds_ago > 10000){
    Serial.println("volume");
    Serial.println(volume);
    Serial.println("interruption_count");
    Serial.println(interruption_count);
    ten_seconds_ago = curr_time;
  }
}

void interrupt(){
  // If the switch changed, due to noise or pressing:
  if (reading != last_button_state) {
    // reset the debouncing timer
    last_debounce_time = curr_time;
  }

  // whatever the reading is at, it's been there for longer than the debounce
  // delay, so take it as the actual current state:
  if ((curr_time - last_debounce_time) > debounce_delay) {
    // if the button state has changed:
    if (reading != button_state) {
      button_state = reading;

      // only toggle the LED if the new button state is HIGH
      if (button_state == HIGH) {
        led_state = !led_state;
        ++interruption_count;
      }
    }
  }
}
