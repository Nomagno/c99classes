#if !defined(__CLASS_H) && !defined(__LIGHT_H)

// Your includes here

#define __CLASS_EXPLICIT_CONSTRUCTOR
#define __CLASS_FILE__ "example/light.h"
#include "../class.h"
#elif defined(__CLASS_H)

// MEMBER(__type, __name, __type2, __init, ... /*optional cleanup code*/)
// METHOD(__class, __in, __name, __args, ...  /*implementation*/)
// METHOD_STATIC(__class, __in, __name, __args, ... /*implementation*/)
// STARTUP(... /*code to append to constructor*/)
// CLEANUP(... /*code to append to destructor*/)

// A light that can have intensity zero (OFF) or nonzero (ON)
#ifndef __CLASS_INHERIT
CLASS(Light)
#endif
    MEMBER(unsigned, state,, =0)
    METHOD(Light, void, setState, int a, { self->state = a; })
#ifndef __CLASS_INHERIT
ENDCLASS(Light)
#endif

#define __LIGHT_H
#endif
#include "../endclass.h"
