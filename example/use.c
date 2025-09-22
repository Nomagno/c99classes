#include <stdio.h>

#ifndef __CLASS_H
#include "rotary.h"
#endif

int main(void) {
    Rotary *myrotary = new_Rotary();

    printf("LIGHT %s, POS %d\n", myrotary->indicator->state ? "ON" : "OFF", myrotary->wheelpos);
    myrotary->moveWheel(myrotary, 4);
    printf("LIGHT %s, POS %d\n", myrotary->indicator->state ? "ON" : "OFF", myrotary->wheelpos);

    delete_Rotary(myrotary);
}
