// ====== CONFIG ======
const int OFFSET_mV = 20;      // calibration offset in millivolts
const uint8_t PIN_SENSOR = A0; // analog input
const uint8_t PIN_RELAY  = 8;  // relay output
const uint8_t PIN_SERVO  = 9;  // servo signal

// Voltage mapping: 0..1023 ADC -> 0..2500 mV (per your original map)
const int ADC_TO_mV_NUM = 2500;  // numerator for scaling
const int ADC_MAX       = 1023;  // 10-bit ADC

// Relay thresholds with hysteresis to prevent rapid toggling
// Example: turn ON above 12.2 V, turn OFF below 11.8 V
const int RELAY_ON_mV  = 12200;
const int RELAY_OFF_mV = 11800;

// Sampling and reporting cadences
const unsigned long SAMPLE_INTERVAL_MS  = 100;   // sensor sample every 100 ms
const unsigned long REPORT_INTERVAL_MS  = 1000;  // print once per second

#include <Servo.h>
Servo servo01; // if you need it later

// ====== STATE ======
unsigned long lastSampleMs = 0;
unsigned long lastReportMs = 0;
bool relayState = true;     // start HIGH as in your setup
long filt_mV = 0;           // filtered voltage in mV (EMA)

void setup() {
  Serial.begin(9600);

  pinMode(PIN_RELAY, OUTPUT);
  digitalWrite(PIN_RELAY, HIGH);

  servo01.attach(PIN_SERVO);      // attached, even if unused now
  // servo01.write(90);            // neutral, if needed

  // Seed filter with first read
  int adc = analogRead(PIN_SENSOR);
  filt_mV = mapADCtoMilliVolts(adc);
}

void loop() {
  unsigned long now = millis();

  // Sample and filter at fixed cadence
  if (now - lastSampleMs >= SAMPLE_INTERVAL_MS) {
    lastSampleMs = now;

    int adc = analogRead(PIN_SENSOR);

    // Integer mapping + offset in mV
    long raw_mV = mapADCtoMilliVolts(adc) + OFFSET_mV;

    // Exponential moving average for stable readings
    // alpha = 0.2 -> EMA = 0.8 * old + 0.2 * new
    filt_mV = ((long)(filt_mV * 8) + (long)(raw_mV * 2)) / 10;

    // Relay control with hysteresis
    if (!relayState && filt_mV >= RELAY_ON_mV) {
      relayState = true;
      digitalWrite(PIN_RELAY, HIGH);
    } else if (relayState && filt_mV <= RELAY_OFF_mV) {
      relayState = false;
      digitalWrite(PIN_RELAY, LOW);
    }
  }

  // Print once per second
  if (now - lastReportMs >= REPORT_INTERVAL_MS) {
    lastReportMs = now;
    // convert to volts only when printing
    float volts = filt_mV / 1000.0f;
    Serial.print("Voltage: ");
    Serial.print(volts, 2);
    Serial.print(" V  | Relay: ");
    Serial.println(relayState ? "ON" : "OFF");
  }
}

// ====== HELPERS ======
inline long mapADCtoMilliVolts(int adc) {
  // integer map: 0..1023 -> 0..2500 mV
  // equivalent to: (adc * 2500L) / 1023
  return (long)adc * ADC_TO_mV_NUM / ADC_MAX;
}

/*
If you later want servo behavior tied to voltage, for example:
void updateServoFromVoltage() {
  // Map, say, 11.0..13.0 V -> 0..180 deg
  int angle = constrain(map((int)filt_mV, 11000, 13000, 0, 180), 0, 180);
  servo01.write(angle);
}
*/
