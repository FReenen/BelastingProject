#ifndef NOODSTOP_H
#define NOODSTOP_H

#include <stdint.h>

void noodstop_setMaxVermogen(uint8_t value); // set max vermogen
void noodstop_setMaxSnelheid(uint16_t value); // set max snelheid
void noodstop_setMaxTemptratuur(uint8_t value); // set max tempratuur
void noodstop_snelhied(uint16_t snelhied); // geef snelhied door
void noodstop_vermogen(uint8_t vermogen); // geef vermogen door
 
void noodstop_init(); // initaliseer noodstop
void noodstop_start(); // start de noodstop logica
 
uint8_t noodstop_getTempratuur(); // verkrijg temptartuur
void noodstop_activeerNoodstop(); // zet de noodstop pin laag

#endif
