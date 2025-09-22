// __CLASS_FILE__ path is relative to class.h itself
#define __CLASS_FILE__ "example/box.h"
#include "../class.h"

// A box that contains an int value with getter and setter
CLASS(Box)
    MEMBER(int, value, 0)
    METHOD(Box, void, setValue, ,int)
    METHOD(Box, int, getValue,)
ENDCLASS(Box)

#include "../endclass.h"
