#include "./startAutomation.h"
#include "./PIPEInstance.h"
#include "./settings.h"

void startAutomation() {
  if (PIPEInstance.light <= MIN_PIPE_LIGHT) {
    PIPEInstance.onBulb();
  } else {
    PIPEInstance.offBulb();
  }
  if (PIPEInstance.temperature <= MIN_PIPE_TEMPERATURE) {
    PIPEInstance.onFan();
  } else {
    PIPEInstance.offFan();
  }
  if (PIPEInstance.soilHumidity <= MIN_PIPE_HUMIDITY) {
    PIPEInstance.onPump();
  } else {
    PIPEInstance.offPump();
  }
}
