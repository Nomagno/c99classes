#if !defined(__CLASS_H) && !defined(__BOX_H)
#define __CLASS_FILE__ "example/box.h"
#include "../class.h"
#elif defined(__CLASS_H)

// A box that contains an int value with getter and setter
CLASS(Box)
    MEMBER(int, value, 0)
    METHOD(Box, void, setValue, ,int)
    METHOD(Box, int, getValue,)
ENDCLASS(Box)

#define __BOX_H
#endif
#include "../endclass.h"
