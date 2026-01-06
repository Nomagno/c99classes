#if !defined(__CLASS_H) && !defined(__BOX_H)

// Your includes here

#define __CLASS_FILE__ "example/box.h"
#include "../class.h"
#elif defined(__CLASS_H)

// MEMBER(__type, __name, __type2, __init, ... /*optional cleanup code*/)
// METHOD(__class, __in, __name, __args, ...  /*implementation*/)
// METHOD_STATIC(__class, __in, __name, __args, ... /*implementation*/)
// STARTUP(... /*code to append to constructor*/)
// CLEANUP(... /*code to append to destructor*/)

// A box that contains an int value with getter and setter.
// Also a static method to add 1 to an int and another to return an int, for some reason (for demo purposes).
#ifndef __CLASS_INHERIT
CLASS(Box)
#endif
    MEMBER(int, value,, =0)
    METHOD(Box, void, setValue, int x, { self->value = x; })
    METHOD(Box, int, getValue,, { return self->value; })
    METHOD_STATIC(Box, int, addOne, int a, { return a+1; })
    METHOD_STATIC(Box, int, getSomeConstant,, { return 42; })
#ifndef __CLASS_INHERIT
ENDCLASS(Box)
#endif

#define __BOX_H
#endif
#include "../endclass.h"
