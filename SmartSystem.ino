// Smart Home Mini Controller

// Pin Definitions
const int pirPin = 2;          // PIR motion sensor
const int ldrPin = A0;         // Light sensor
const int tempPin = A1;        // Temperature sensor - LM35
const int buttonPin = 3;       // Push button
const int ledAuto = 9;         // Auto mode indicator LED
const int ledDevice = 10;      // Device active LED
const int buzzer = 11;         // Buzzer alert

// Variables
bool autoMode = true;          // System starts in auto mode
bool deviceActive = false;
int buttonState = 0;//used for detecting button press
int lastButtonState = 0;//used for detecting button press
unsigned long lastDebounceTime = 0;//stores last time the button changed state
unsigned long debounceDelay = 50; // Debounce delay (ms)

// Thresholds: above thresholds values, do actions
const int tempThreshold = 30;      // Temperature threshold in °C - If temperature > 30°C → buzzer alert
const int ldrThreshold = 500;      // LDR threshold (0–1023) - If lightLevel < 500 → LED ON (it's dark)

// Setup function
void setup() {  
  pinMode(pirPin, INPUT);
  pinMode(ldrPin, INPUT);
  pinMode(tempPin, INPUT);
  pinMode(buttonPin, INPUT_PULLUP); // internal pull-up resistor for button - gives the button a default HIGH value
  pinMode(ledAuto, OUTPUT);
  pinMode(ledDevice, OUTPUT);
  pinMode(buzzer, OUTPUT);

  Serial.begin(9600); // Start serial communication for monitoring : Baud Rate - 9600  
}

// Main loop
void loop() {
  // --- Read sensors ---
  int motion = digitalRead(pirPin);         // Motion detection
  int lightLevel = analogRead(ldrPin);      // Ambient light
  int tempValue = analogRead(tempPin);      // Temperature sensor
  float temperature = (tempValue * 5.0 * 100.0) / 1023; // Convert LM35 analog value to °C

  // --- Read button with debounce ---
  int reading = digitalRead(buttonPin);
  if (reading != lastButtonState) {
    //millis() returns the number of milliseconds since the Arduino started
    lastDebounceTime = millis(); // reset timer if button changed
  }
  if ((millis() - lastDebounceTime) > debounceDelay) { //If button stable for >50 ms → accept reading
    if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == LOW) {  // button pressed
        autoMode = !autoMode;    // toggle auto/manual mode
      }
    }
  }
  lastButtonState = reading;

  // --- Update auto mode LED ---
  digitalWrite(ledAuto, autoMode ? HIGH : LOW);

  // --- Device control ---
  deviceActive = false; // reset device state

  if (autoMode) {
    // Motion detection
    if (motion == HIGH) {
      digitalWrite(buzzer, HIGH);
      deviceActive = true;
    } else {
    digitalWrite(buzzer, LOW);
  }

  ```
  // Light control
  if (lightLevel < ldrThreshold) {
    digitalWrite(ledDevice, HIGH);
    deviceActive = true;
  } else {
    digitalWrite(ledDevice, LOW);
  }

  // Temperature check
  if (temperature > tempThreshold) {
    digitalWrite(buzzer, HIGH);
    deviceActive = true;
  }

  } else {
    // Manual mode → turn off devices initially
    digitalWrite(ledDevice, LOW);
    digitalWrite(buzzer, LOW);
  }

  // Update LED2 to reflect any active device
  digitalWrite(ledDevice, deviceActive ? HIGH : LOW);

  // --- Serial monitor for debugging ---
  Serial.print("Motion: "); Serial.print(motion);
  Serial.print(" | Light: "); Serial.print(lightLevel);
  Serial.print(" | Temp: "); Serial.println(temperature);

  delay(200); // Small delay for stability
}
