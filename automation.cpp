#include "./automation.h"
#include "./PIPEInstance.h"
#include "./settings.h"

void automation() {
  if (PIPEInstance.light <= MIN_PIPE_LIGHT) {
    PIPEInstance.onBulb();
  }
}
