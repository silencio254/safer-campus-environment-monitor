// 1. PIN CONFIGURATION
const byte MQ2_PIN = A0;
const byte THERMISTOR_PIN = A1;
const byte GREEN_LED = 5;
const byte YELLOW_LED = 6;
const byte RED_LED = 7;
const byte BUZZER_PIN = 8;

// 2. SENSOR CONFIGURATION
const float SERIES_RESISTOR = 10000.0;
const float NOMINAL_RESISTANCE = 10000.0;
const float NOMINAL_TEMPERATURE = 25.0;
const float BETA_VALUE = 3950.0;

// 3. THRESHOLD CONFIGURATION
const int GAS_WARNING = 300;
const int GAS_CRITICAL = 450;
const float TEMP_WARNING = 35.0;
const float TEMP_CRITICAL = 45.0;

// 4. SYSTEM VARIABLES
int gasValue = 0;
float temperature = 0.0;
enum EnvironmentState {
  NORMAL,
  WARNING,
  CRITICAL
};

EnvironmentState currentState = NORMAL;

// 5. TIMING
unsigned long previousReadTime = 0;
const unsigned long SENSOR_INTERVAL = 500;

// 6. TEMPERATURE CALCULATION
float readTemperature() {
  int adcValue = analogRead(THERMISTOR_PIN);

  if (adcValue <= 0 || adcValue >= 1023) {
    return -999.0;
  }

  float resistance =
    SERIES_RESISTOR *
    ((float)adcValue / (1023.0 - adcValue));

  float steinhart =
    resistance / NOMINAL_RESISTANCE;

  steinhart = log(steinhart);

  steinhart /= BETA_VALUE;

  steinhart +=
    1.0 / (NOMINAL_TEMPERATURE + 273.15);

  steinhart = 1.0 / steinhart;

  return steinhart - 273.15;
}

// 7. SENSOR READING
void readSensors() {
  gasValue = analogRead(MQ2_PIN);
  temperature = readTemperature();

}

// 8. ENVIRONMENT EVALUATION
void evaluateEnvironment() {
  if (temperature == -999.0) {

    currentState = CRITICAL;
    return;
  }

  if (gasValue >= GAS_CRITICAL ||
      temperature >= TEMP_CRITICAL) {

    currentState = CRITICAL;
  }

  else if (gasValue >= GAS_WARNING ||
           temperature >= TEMP_WARNING) {

    currentState = WARNING;
  }

  else {

    currentState = NORMAL;
  }
}

// 10. OUTPUT CONTROL
void updateOutputs() {
  switch (currentState) {
    case NORMAL:
      setNormalIndicators();
      break;
    case WARNING:
      setWarningIndicators();
      break;
    case CRITICAL:
      setCriticalIndicators();
      break;
  }
}

// 11. NORMAL INDICATION
void setNormalIndicators() {
  digitalWrite(GREEN_LED, HIGH);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(RED_LED, LOW);
  noTone(BUZZER_PIN);
}

// 12. WARNING INDICATION
void setWarningIndicators() {
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(YELLOW_LED, HIGH);
  digitalWrite(RED_LED, LOW);
  noTone(BUZZER_PIN);
}

// 13. CRITICAL INDICATION
void setCriticalIndicators() {
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(RED_LED, HIGH);
  tone(BUZZER_PIN, 2000);
}

// 14. SERIAL MONITOR
void displayReadings() {
  Serial.print("Gas ADC: ");
  Serial.print(gasValue);
  Serial.print(" | Temperature: ");

  if (temperature == -999.0) {
    Serial.print("Sensor Error");
  } else {
    Serial.print(temperature);
    Serial.print(" C");
  }
  Serial.print(" | Status: ");
  switch (currentState) {
    case NORMAL:
      Serial.println("NORMAL");
      break;
    case WARNING:
      Serial.println("WARNING");
      break;
    case CRITICAL:
      Serial.println("CRITICAL");
      break;
  }
}

// 15. SETUP
void setup() {

  pinMode(GREEN_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  Serial.begin(9600);
  Serial.println("Environment Monitor Started");
  setNormalIndicators();
}

void loop() {
  if (millis() - previousReadTime >= SENSOR_INTERVAL) {
    previousReadTime = millis();
    readSensors();
    evaluateEnvironment();
    updateOutputs();
    displayReadings();
  }
}
