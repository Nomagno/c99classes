// __CLASS_FILE__ path is relative to class.h itself
#define __CLASS_FILE__ "example/light.h"
#include "../class.h"

// A light that can have intensity zero (OFF) or nonzero (ON)
CLASS(Light)
    MEMBER(unsigned, state,, {0})
    METHOD(Light, void, setState, ,int)
ENDCLASS(Light)
