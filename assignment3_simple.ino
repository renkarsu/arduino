const int LED_PIN = 9;
const int INPUT_PIN = 2;
const int VOLUME_PIN = A0;

volatile int led_state = HIGH;
int volume = 0;

volatile int interruption_count = 0;

unsigned long last_debounce_time = 0;
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
  volume = analogRead(VOLUME_PIN);
  curr_time = millis();

  digitalWrite(LED_PIN, led_state);

  if(curr_time - ten_seconds_ago > 10000){
    Serial.println("volume");
    Serial.println(volume);
    Serial.println("interruption_count");
    Serial.println(interruption_count);
    ten_seconds_ago = curr_time;
  }
}

void interrupt(){
  led_state = !led_state;
  ++interruption_count;
}
