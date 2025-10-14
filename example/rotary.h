#if !defined(__CLASS_H) && !defined(__ROTARY_H)

// Your includes here
#include "light.h"
#include "box.h"

#define __CLASS_FILE__ "example/rotary.h"
#include "../class.h"
#elif defined(__CLASS_H)

// A rotary input, with a position, and an indicator light.
// The indicator light will be ON when the position is nonzero, and off when the position is 0.
// The position can be negative or positive.
// The indicator light is made with an explicit constructor that overrides its default value so that it is 1
#ifndef __CLASS_INHERIT
CLASS(Rotary)
#endif
    #define __PARENT "example/light.h"
    #include "../inherit.h"
    MEMBER_CLEANUP(Box *, some_unused_box, new_Box(), delete_Box(self->some_unused_box))
    MEMBER_CLEANUP(Light *, indicator, new_Light_explicit(1), delete_Light(self->indicator))
    MEMBER(int, wheelpos, {0})
    MEMBERC(int, data,[12],
        for(int i = 0; i < 12; i++) {
            self->data[i] = 0;
        })
    METHOD(Rotary, void, moveWheel, int)
#ifndef __CLASS_INHERIT
ENDCLASS(Rotary)
#endif

#define __ROTARY_H
#endif
#include "../endclass.h"
