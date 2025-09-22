#include <stdio.h>
#include "rotary.h"

int main(void) {
    Rotary *myrotary = construct_Rotary();

    printf("LIGHT %s, POS %d\n", myrotary->indicator->state ? "ON" : "OFF", myrotary->wheelpos);
    myrotary->moveWheel(myrotary, 4);
    printf("LIGHT %s, POS %d\n", myrotary->indicator->state ? "ON" : "OFF", myrotary->wheelpos);
}
