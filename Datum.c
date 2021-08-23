#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "datum.h"


//char* asString(DATE aDate) {
//	char string[100] = {'\0'};
//	sprintf (string, "%2d.%s.%4d", aDate.day, monthName(aDate.month), aDate.year);
//
//	return string;
//}

DATUM parseDatum(char *aStr) {
	DATUM retVal;
	retVal.day = atoi(strtok(aStr, "."));
	retVal.month = atoi(strtok(NULL, "."));
	retVal.year = atoi(strtok(NULL, "."));

	return retVal;
}

