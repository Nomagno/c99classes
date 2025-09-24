#if !defined(__CLASS_H) && !defined(__BOX_H)

// Your includes here

#define __CLASS_FILE__ "example/box.h"
#include "../class.h"
#elif defined(__CLASS_H)

// A box that contains an int value with getter and setter.
// Also a static method to add 1 to an int and another to return an int, for some reason (for demo purposes).
#ifndef __CLASS_INHERIT
CLASS(Box)
#endif
    MEMBER(int, value, 0)
    METHOD(Box, void, setValue, ,int)
    METHOD(Box, int, getValue,)
    METHOD_STATIC(Box, int, addOne, int)
    METHOD_STATIC(Box, int, getSomeConstant, void)
#ifndef __CLASS_INHERIT
ENDCLASS(Box)
#endif

#define __BOX_H
#endif
#include "../endclass.h"
