#include "HX711.h"

#define calibration_factor -7050.0

#define LOADCELL_DOUT_PIN  6
#define LOADCELL_SCK_PIN  7

HX711 scale;

void initLoadCell() {
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale(calibration_factor);
  scale.tare();

  Serial.println("Readings:");
}

float getWeight() {
  return scale.get_units();
}
