#include "box.h"

void method_Box_setValue(Box *self, int x) { self->value = x; }
int method_Box_getValue(Box *self) { return self->value; }
int method_Box_addOne(int a) { return a+1; }
int method_Box_getSomeConstant(void) { return 42; }
