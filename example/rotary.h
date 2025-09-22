#ifndef __CLASS_H
#include "light.h"
#include "../reclass.h"
#endif

// __CLASS_FILE__ path is relative to class.h itself
#define __CLASS_FILE__ "example/rotary.h"
#include "../class.h"

// A rotary input, with a position, and an indicator light.
// The indicator light will be ON when the position is nonzero, and off when the position is 0.
// The position can be negative or positive.
CLASS(Rotary)
    MEMBER_CLEANUP(Light *, indicator,, new_Light(), delete_Light(self->indicator))
    MEMBER(int, wheelpos,, {0})
    MEMBERC(int, data,[12],
        for(int i = 0; i < 12; i++) {
            self->data[i] = 0;
        })
    METHOD(Rotary, void, moveWheel, ,int)
ENDCLASS(Rotary)
