#define _CRT_SECURE_NO_WARNINGS // 6

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "functions.h"
#include "osoba.h"


static int brojOsoba = 0; // 4, 5

void kreirajDatoteku(const char* const ime) {
	FILE* fp = fopen("ime", "w+");
	if (fp == NULL) {
		perror("Greska prilikom kreiranja datoteke: ");
		exit(EXIT_FAILURE);
	}
	else {
		printf("Datoteka uspjesno kreirana!\n");
	}
}


void dodajOsobu(const char* const ime) {

	size_t velicinaDatoteke;
	FILE* fp = fopen(ime, "a+");
	if (fp == NULL) {
		perror("Greska prilikom otvaranja datoteke:"); // 19
		exit(EXIT_FAILURE);
	}

	fseek(fp, 0, SEEK_END);
	velicinaDatoteke = ftell(fp);
	rewind(fp);
	brojOsoba = velicinaDatoteke / sizeof(OSOBA);

	OSOBA temp = { 0 };
	temp.id = brojOsoba + 1;

	printf("Unesite ime osobe: ");
	scanf(" %19[^\n]", temp.ime);

	printf("Unesite prezime osobe: ");
	scanf(" %19[^\n]", temp.prezime);

	printf("Unesite godine osobe: ");
	scanf("%d", &temp.godine);

	printf("Unesite OIB osobe: ");
	scanf(" %10[^\n]", temp.oib);

	printf("Unesite adresu osobe: ");
	scanf(" %29[^\n]", temp.adresa);

	fwrite(&temp, sizeof(OSOBA), 1, fp);
	brojOsoba++;

	printf("Nova osoba uspjesno dodana!\n");
	fclose(fp);
}


void* ucitajOsobe(const char* const ime) {

	size_t velicinaDatoteke;
	FILE* fp = fopen(ime, "r");

	if (fp == NULL) {
		perror("Ucitavanje osoba iz datoteke osobe.txt"); // 19
		exit(EXIT_FAILURE);
	}

	fseek(fp, 0, SEEK_END);
	velicinaDatoteke = ftell(fp);
	rewind(fp);
	brojOsoba = velicinaDatoteke / sizeof(OSOBA);
	printf("Broj osoba: %d\n", brojOsoba);

	OSOBA* poljeOsoba = (OSOBA*)calloc(brojOsoba, sizeof(OSOBA)); // 14

	if (poljeOsoba == NULL) {
		perror("Zauzimanje memorije osoba"); // 19
		exit(EXIT_FAILURE);
	}

	fread(poljeOsoba, sizeof(OSOBA), brojOsoba, fp);
	fclose(fp);

	printf("Osobe uspjesno ucitani!\n");

	return poljeOsoba;
}
void ispisiSveOsobe(const OSOBA* const polje) {

	if (polje == NULL) {
		printf("Polje osoba je prazno!\n");
		return;
	}

	int i;

	for (i = 0; i < brojOsoba; i++) {
		printf("Osoba broj %d\nID: %d\nIme: %s\nPrezime: %s\nGodine: %d\nOIB: %s\nAdresa: %s\n\n",
			i + 1,
			(polje + i)->id,
			(polje + i)->ime,
			(polje + i)->prezime,
			(polje + i)->godine,
			(polje + i)->oib,
			(polje + i)->adresa);
	}
}

int funkcijaPretrazivanja(const void* a, const void* b) {

	OSOBA* osobaA = (OSOBA*)a;
	OSOBA* osobaB = (OSOBA*)b;

	if (osobaA->id < osobaB->id) return -1;
	else if (osobaA->id > osobaB->id) return 1;
	else return 0;

}

OSOBA* pretraziOsobe(OSOBA* const polje) {

	if (polje == NULL) {
		printf("Polje osoba je prazno!\n");
		return NULL;
	}

	int i;

	int trazeniId;

	printf("Unesite ID osobe koje trazite: \n");

	do {
		scanf("%d", &trazeniId);

		if (trazeniId < 1 || trazeniId > brojOsoba) {
			printf("Osoba s unesenim ID-em ne postoji. Unesite ID koji postoji: ");
		}
	} while (trazeniId < 1 || trazeniId > brojOsoba);

	OSOBA trazeni_kontakt = { .id = trazeniId };

	return (OSOBA*)bsearch(&trazeni_kontakt, polje, brojOsoba, sizeof(OSOBA), funkcijaPretrazivanja);

	return NULL;
}

void uredivanjeOsoba(OSOBA* polje, const char* const ime) {

	if (brojOsoba == 0) {
		printf("Polje kontakata prazno\n");
		return;
	}

	FILE* fp = fopen(ime, "r+");

	if (fp == NULL) {
		perror("Azuriranje osoba");
		exit(EXIT_FAILURE);
	}

	int trazeniId;

	printf("Unesite ID osobe koje zelite azurirati: ");

	do {
		fflush(stdin);
		scanf("%d", &trazeniId);

		if (trazeniId < 0 || trazeniId > brojOsoba) {
			printf("Osoba s unesenim ID-em ne postoji. Unesite ID koji postoji: ");
		}
	} while (trazeniId < 0 || trazeniId > brojOsoba);

	OSOBA temp = { 0 };

	temp.id = trazeniId;

	printf("Unesite ime osobe (trenutno: %s): ", (polje + trazeniId - 1)->ime);
	scanf(" %19[^\n]", temp.ime);

	printf("Unesite prezime osobe (trenutno %s): ", (polje + trazeniId - 1)->prezime);
	scanf(" %19[^\n]", temp.prezime);

	printf("Unesite godine osobe (trenutno %d): ", (polje + trazeniId - 1)->godine);
	scanf(" %d", &temp.godine);

	printf("Unesite adresu osobe (trenutno %s): ", (polje + trazeniId - 1)->adresa);
	scanf(" %29[^\n]", temp.adresa);

	printf("Unesite OIB osobe (trenutno %s): ", (polje + trazeniId - 1)->oib);
	scanf(" %10[^\n]", temp.oib);

	fseek(fp, sizeof(OSOBA) * (trazeniId - 1), SEEK_SET);
	fwrite(&temp, sizeof(OSOBA), 1, fp);

	printf("Kontakt uspjesno azuriran!\n");

	fclose(fp);
}

void brisanjeOsoba(OSOBA* const polje, const char* const ime) {

	if (brojOsoba == 0) {
		printf("Polje osoba je prazno!\n");
		return;
	}
	size_t velicinaDatoteke;
	FILE* fp = fopen(ime, "r+");

	if (fp == NULL) {
		perror("Brisanje osoba");
		exit(EXIT_FAILURE);
	}

	fseek(fp, 0, SEEK_END);
	velicinaDatoteke = ftell(fp);
	rewind(fp);
	brojOsoba = velicinaDatoteke / sizeof(OSOBA);
	printf("Broj osoba: %d\n", brojOsoba);

	int i, trazeniId;

	printf("Unesite ID osobe koje zelite obrisati: ");

	do {
		scanf("%d", &trazeniId);

		if (trazeniId < 1 || trazeniId > brojOsoba) {
			printf("Osoba s unesenim ID-em ne postoji. Unesite ID koji postoji: ");
		}
	} while (trazeniId < 1 || trazeniId > brojOsoba);

	OSOBA* pomocnoPolje = (OSOBA*)calloc(brojOsoba - 1, sizeof(OSOBA));

	if (polje == NULL) {
		perror("Neuspjelo dinamicko zauzimanje memorije");
		exit(EXIT_FAILURE);
	}

	int c = 0;

	for (i = 0; i < brojOsoba; i++) {

		if (trazeniId != (polje + i)->id) {
			*(pomocnoPolje + c) = *(polje + i);

			if ((pomocnoPolje + c)->id > trazeniId) {
				(pomocnoPolje + c)->id -= 1;
			}

			c++;
		}
	}

	fclose(fp);
	fp = fopen(ime, "wb");
	fwrite(pomocnoPolje, sizeof(OSOBA), brojOsoba - 1, fp);

	free(pomocnoPolje); // 14, 15

	fclose(fp);

	printf("Osoba je uspjesno obrisana\n");
}


int funkcijaUsporedbe(const void* a, const void* b) {

	OSOBA* osobaA = (OSOBA*)a;
	OSOBA* osobaB = (OSOBA*)b;

	return strcmp(osobaA->prezime, osobaB->prezime);
}

void ispisiAbecednimRedom(OSOBA* const polje) {

	qsort(polje, brojOsoba, sizeof(OSOBA), funkcijaUsporedbe);

	printf("Sortirane osobe:\n");
	int i;
	for (i = 0; i < brojOsoba; i++) {
		printf("Osoba broj %d\nID: %d\nIme: %s\nPrezime: %s\nGodine: %d\nAdresa: %s\nOIB: %s\n\n",
			i + 1,
			(polje + i)->id,
			(polje + i)->ime,
			(polje + i)->prezime,
			(polje + i)->godine,
			(polje + i)->adresa,
			(polje + i)->oib);
	}
}


void izlazIzPrograma(OSOBA* polje) {

	free(polje);
}