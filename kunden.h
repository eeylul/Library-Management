#ifndef KUNDEN_H_
#define KUNDEN_H_

#include "datum.h"
#include "global.h"

/*"struct" ist eine Sammlung von Variablen (kann von unterschiedlichem Typ sein) unter einem einzigen Namen.
 * "boolean" ist ein Datentyp, der Wahrheit oder Lüge speichern kann.
 * Jeder Wert ungleich Null entspricht "true", während 0 "false" entspricht
 */
struct kunden_link* create_list(KUNDEN);
struct kunden_link* add_to_list(KUNDEN, boolean);

void kundensHeader(int);
void readKundenCSV();
unsigned short tekrarKunden();
void deleteKundenFromDat(int);
int delete_from_list(unsigned int);
struct kunden_link* search_in_list(unsigned int, struct kunden_link**);

#endif /* KUNDEN_H_ */
