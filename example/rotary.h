#if !defined(__CLASS_H) && !defined(__ROTARY_H)

// Your includes here
#include "light.h"
#include "box.h"

#define __CLASS_FILE__ "example/rotary.h"
#include "../class.h"
#elif defined(__CLASS_H)

// MEMBER(__type, __name, __type2, __init, ... /*optional cleanup code*/)
// METHOD(__class, __in, __name, __args, ...  /*implementation*/)
// METHOD_STATIC(__class, __in, __name, __args, ... /*implementation*/)
// STARTUP(... /*code to append to constructor*/)
// CLEANUP(... /*code to append to destructor*/)

// A rotary input, with a position, and an indicator light.
// The indicator light will be ON when the position is nonzero, and off when the position is 0.
// The position can be negative or positive.
// The indicator light is made with an explicit constructor that overrides its default value so that it is 1
#ifndef __CLASS_INHERIT
CLASS(Rotary)
#endif
    #define __PARENT "example/light.h"
    #include "../inherit.h"
    MEMBER(Box *, some_unused_box,, =new_Box(0), delete_Box(self->some_unused_box))
    MEMBER(int, wheelpos,, =0)
    MEMBER(int, data,[12], ; BLOCK(for(int i = 0; i < 12; i++){ self->data[i] = 0; }) )
    METHOD(Rotary, void, moveWheel, int a,
                {
                    self->wheelpos += a;
                    self->setState((Light *)self, self->wheelpos != 0);
                }
          )
    STARTUP(self->state = 1;)
#ifndef __CLASS_INHERIT
ENDCLASS(Rotary)
#endif

#define __ROTARY_H
#endif
#include "../endclass.h"
