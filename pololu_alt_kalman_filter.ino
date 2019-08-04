#include <Wire.h>
#include <LPS.h> // https://github.com/pololu/lps-arduino
#include <SimpleKalmanFilter.h> // https://github.com/denyssene/SimpleKalmanFilter

LPS ps;
SimpleKalmanFilter pressureKalmanFilter(1, 1, 0.01);

void setup() {
  Serial.begin(115200);
  Wire.begin();

  if (!ps.init()) {
    Serial.println("Failed to autodetect pressure sensor!");
    while (1);
  }

  ps.enableDefault();
}

void loop() {
  float pressure = ps.readPressureMillibars();
  float altitude = ps.pressureToAltitudeMeters(pressure);
  float estimated_altitude = pressureKalmanFilter.updateEstimate(altitude);

  Serial.println(estimated_altitude);
}
