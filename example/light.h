#if !defined(__CLASS_H) && !defined(__LIGHT_H)

// Your includes here

#define __CLASS_EXPLICIT_CONSTRUCTOR
#define __CLASS_FILE__ "example/light.h"
#include "../class.h"
#elif defined(__CLASS_H)

// A light that can have intensity zero (OFF) or nonzero (ON)
#ifndef __CLASS_INHERIT
CLASS(Light)
#endif
    MEMBER(unsigned, state, {0})
    METHOD(Light, void, setState, ,int)
#ifndef __CLASS_INHERIT
ENDCLASS(Light)
#endif

#define __LIGHT_H
#endif
#include "../endclass.h"
