#include <stdio.h>
#include "rotary.h"
#include "light.h"

int main(void) {
    Rotary *myrotary = new_Rotary(0);

    printf("LIGHT %s, POS %d\n", myrotary->state ? "ON" : "OFF", myrotary->wheelpos);
    MT(myrotary, moveWheel,(4));
    printf("LIGHT %s, POS %d\n", myrotary->state ? "ON" : "OFF", myrotary->wheelpos);
    MT(myrotary, moveWheel,(-4));
    printf("LIGHT %s, POS %d\n", myrotary->state ? "ON" : "OFF", myrotary->wheelpos);
    MT(myrotary, moveWheel,(-3));
    printf("LIGHT %s, POS %d\n", myrotary->state ? "ON" : "OFF", myrotary->wheelpos);

    delete_Rotary(myrotary);
}
