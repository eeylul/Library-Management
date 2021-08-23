#ifndef DATUM_H_
#define DATUM_H_

#include <time.h>

/*Ein "typedef" ist ein Mechanismus zum Deklarieren eines alternativen Namens für einen Typ.
 *Ein "enumerated type" ist ein ganzzahliger Typ mit einem zugehörigen Satz symbolischer Konstanten, die die gültigen Werte dieses Typs darstellen.*/

typedef enum {January=1, Febraury, March, April, May, June, July, August, September, October, November, Dezember} MONTHS;

typedef struct {
	unsigned 	year;
	MONTHS		month;
	unsigned 	day;
} DATUM;

char* monthName(MONTHS);
DATUM  parseDatum(char*);

#endif /* DATUM_H_ */
