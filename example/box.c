#include "box.h"

void method_Box_setValue(Box *self, int x) {
    self->value = x;
}

int method_Box_getValue(Box *self) {
    return self->value;
}
