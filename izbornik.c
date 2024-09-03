#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "osoba.h"
#include "functions.h"

void izbornik(const char* const ime) { // 9
	int pocetak;
	do {
		printf("IZBORNIK:\n\n"); // 8
		printf("1: Kreiraj datoteku\n");
		printf("2: Dodavanje osoba\n");
		printf("3: Ucitaj sve osobe\n");
		printf("4: Ispisi podatke o svim osobama\n");
		printf("5: Pretrazivanje osoba po ID-u\n");
		printf("6: Uredivanje osoba\n");
		printf("7: Brisanje osoba\n");
		printf("8: Sortiraj osobe pomocu abecednim redom\n");
		printf("9: Izlaz iz programa\n");

		static OSOBA* pronadenaOsoba = NULL; // 4, 9, 10
		static OSOBA* poljeOsobe = NULL; // 4, 9, 10

		scanf("%d", &pocetak);

		switch (pocetak) {

		case 1:
			kreirajDatoteku(ime); // 4, 10
			break;

		case 2:
			dodajOsobu(ime); // 4, 10
			break;

		case 3:
			if (poljeOsobe != NULL) {
				free(poljeOsobe); // 14
			}

			poljeOsobe = (OSOBA*)ucitajOsobe(ime); // 9

			if (poljeOsobe == NULL) {
				exit(EXIT_FAILURE);
			}
			break;

		case 4:
			if (poljeOsobe != NULL) {
				free(poljeOsobe); // 14
			}

			poljeOsobe = (OSOBA*)ucitajOsobe(ime); // 9, 10
			ispisiSveOsobe(poljeOsobe); // 10
			break;

		case 5:
			pronadenaOsoba = (OSOBA*)pretraziOsobe(poljeOsobe); // 9, 10

			if (pronadenaOsoba != NULL) {
				printf("ID: %d\n", pronadenaOsoba->id);
				printf("Ime: %s\n", pronadenaOsoba->ime);
				printf("Prezime: %s\n", pronadenaOsoba->prezime);
				printf("Godine: %d\n", pronadenaOsoba->godine);
				printf("OIB: %s\n", pronadenaOsoba->oib);
				printf("Adresa: %s\n", pronadenaOsoba->adresa);
			}
			else {
				printf("Osoba s tim ID-em ne postoji!\n");
			}

			break;

		case 6:
			if (poljeOsobe != NULL) {
				free(poljeOsobe); // 14
			}

			poljeOsobe = (OSOBA*)ucitajOsobe(ime); // 9, 10

			uredivanjeOsoba(poljeOsobe, ime); // 10
			break;

		case 7:
			if (poljeOsobe != NULL) {
				free(poljeOsobe); // 14
				poljeOsobe = NULL;
			}

			poljeOsobe = (OSOBA*)ucitajOsobe(ime); // 9, 10

			brisanjeOsoba(poljeOsobe, ime); // 9, 10
			break;

		case 8:
			ispisiAbecednimRedom(poljeOsobe); // 10
			break;

		case 9:
			izlazIzPrograma(poljeOsobe); // 10
			break;
		default:
			break;
		}
	} while (pocetak != 9);

}