#pragma once

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "osoba.h"

void izbornik(const char* const);
void kreirajDatoteku(const char* const);
void dodajOsobu(const char* const);
void* ucitajOsobe(const char* const);
void ispisiSveOsobe(const OSOBA* const);
OSOBA* pretraziOsobe(OSOBA* const);
void uredivanjeOsoba(OSOBA*, const char* const);
void brisanjeOsoba(OSOBA* const, const char* const);
void izlazIzPrograma(OSOBA*);
void ispisiAbecednimRedom(OSOBA* const);

#endif
