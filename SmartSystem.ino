// Smart Home Mini Controller

// Pin Definitions
const int pirPin = 2;          // PIR motion sensor
const int ldrPin = A0;         // Light sensor
const int tempPin = A1;        // Temperature sensor
const int buttonPin = 3;       // Push button
const int ledAuto = 9;         // Auto mode indicator LED
const int ledDevice = 10;      // Device active LED
const int buzzer = 11;         // Buzzer alert

// Variables
bool autoMode = true;          // System starts in auto mode
bool deviceActive = false;
int buttonState = 0;
int lastButtonState = 0;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50; // Debounce delay (ms)

// Thresholds: above thresholds values, do actions
const int tempThreshold = 30;      // Temperature threshold in °C
const int ldrThreshold = 500;      // LDR threshold (0–1023)

// Setup function
void setup() {  
  pinMode(pirPin, INPUT);
  pinMode(ldrPin, INPUT);
  pinMode(tempPin, INPUT);
  pinMode(buttonPin, INPUT_PULLUP); // internal pull-up resistor for button
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
    lastDebounceTime = millis(); // Time passed since Arduino started
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
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
  ```

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
