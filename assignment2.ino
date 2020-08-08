// Pressing the button, changing brightness of LED
// The brightness of the LED changes depending on the time from pressing to releasing
// turn off in 60s
// 0s is 0%
// Bright of LED changes is 10% per 1s
// Over 10s, 100%

// 9 is a PWM pin. It's connect to LED on breadboard
const int LED_PIN = 9;
// pushSW pin is 2
const int INPUT_PIN = 2;

unsigned long duration = 0;
unsigned duration_sec = 0;
unsigned brightness = 0;

void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  pinMode(INPUT_PIN, INPUT);
}

void loop() {
  // Set a long timeout parameter to ignore the timeout.
  // Start measurement of pressing time by pressing the button.(in microseconds)
  duration = pulseIn(INPUT_PIN, LOW, 987000000);

  // if duration < 40ms, this process is ignored. bounce is happened.
  // This is simple debounce processing.
  if (duration < 40000) {
    duration = 0;
  }

  // convert microseconds to seconds
  // duration_sec is [0,11)
  duration_sec = (unsigned)(duration / 1000000);
  brightness = 255 * duration_sec * 0.1;

  if (brightness < 1) {
    brightness = 0;
  } else if (brightness > 255) {
    brightness = 255;
  }

  Serial.println("duration");
  Serial.println(duration);
  Serial.println("duration_sec");
  Serial.println(duration_sec);
  Serial.println("brightness");
  Serial.println(brightness);

  // grow for 60s
  analogWrite(LED_PIN, brightness);
  if (brightness >= 1) {
    delay(60000);
    analogWrite(LED_PIN, LOW);
  }
}
