#include "rotary.h"

void method_Rotary_moveWheel(Rotary *self, int a) {
    self->wheelpos += a;
    self->indicator->setState(self->indicator, a != 0);
}
