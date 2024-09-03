#define _CRT_SECURE_NO_WARNINGS // 6

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "functions.h"
#include "osoba.h"

int main(void) {
	char* datoteka = "osobe.txt"; // 16

	printf("\n");
	izbornik(datoteka); // 8

	printf("Program zavrsen!\n");

	return 0;
}