#ifndef BUCH_H_
#define BUCH_H_

#include "datum.h"
#include "global.h"

/*void-Funktionen werden wie wertr�ckgebende Funktionen erstellt und verwendet, au�er dass sie nach Ausf�hrung der Funktion keinen Wert zur�ckgeben.
 *Eine void-Funktion f�hrt eine Aufgabe aus, und das Steuerelement kehrt zum Aufrufer zur�ck. Es wird jedoch kein Wert zur�ckgegeben.
*/

void bucherHeader();
void readBucherCSV();

unsigned short tekrarBuch();
struct bucher_link* search_in_listb(unsigned int, struct bucher_link**);
int delete_from_listb(unsigned int);
struct bucher_link* add_to_listb(BUCH, boolean);
struct bucher_link* create_listb(BUCH);

#endif /* BUCH_H_ */
