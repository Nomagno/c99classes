#if !defined(__CLASS_H) && !defined(__LIGHT_H)
#define __CLASS_FILE__ "example/light.h"
#include "../class.h"
#elif defined(__CLASS_H)

// A light that can have intensity zero (OFF) or nonzero (ON)
CLASS(Light)
    MEMBER(unsigned, state, {0})
    METHOD(Light, void, setState, ,int)
ENDCLASS(Light)

#define __LIGHT_H
#endif
#include "../endclass.h"
