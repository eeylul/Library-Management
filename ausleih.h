
#ifndef AUSLEIH_H_
#define AUSLEIH_H_

#include "datum.h"
#include "global.h"
#include "bool.h"

int listAusgeliehBucher(boolean);
void ausgeliehHeader(int);
void readBucherCSV_a();
void bucherList_a();
void kundenList_a();
struct bucher_link* add_to_listb_a(BUCH, boolean);
struct bucher_link* create_listb_a(BUCH);
struct kunden_link* search_kunden_with_KundenID(unsigned int);
void clean_buch_list(struct bucher_link*);

#endif /* AUSLEIH_H_ */
