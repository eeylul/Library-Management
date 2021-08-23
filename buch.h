#ifndef BUCH_H_
#define BUCH_H_

#include "datum.h"
#include "global.h"

/*void-Funktionen werden wie wertrückgebende Funktionen erstellt und verwendet, außer dass sie nach Ausführung der Funktion keinen Wert zurückgeben.
 *Eine void-Funktion führt eine Aufgabe aus, und das Steuerelement kehrt zum Aufrufer zurück. Es wird jedoch kein Wert zurückgegeben.
*/

void bucherHeader();
void readBucherCSV();

unsigned short tekrarBuch();
struct bucher_link* search_in_listb(unsigned int, struct bucher_link**);
int delete_from_listb(unsigned int);
struct bucher_link* add_to_listb(BUCH, boolean);
struct bucher_link* create_listb(BUCH);

#endif /* BUCH_H_ */
