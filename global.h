#ifndef GLOBAL_H_
#define GLOBAL_H_
/*Um die ganze Arbeit, leichter zu machen, haben wir auch "global Header" dazu benutzt.
 Dieser Header ermöglicht uns, alle wichtige konstante Funktionen auf einmal zu defenieren, zusammenzuknüpfen und mit unserem Code zu verbinden.
 */

#include "bool.h"
#include "datum.h"

/*Nämlich in diesem Header addieren wir alle unsere Listen, damit es für alle Teilen funktionieren wird.*/

#define BUCHER_DAT  "C:\\Users\\Ýstanbul\\eclipse-workspace\\Bibliothek1\\Dat\\Bucherliste.dat"
#define BUCHER_CSV  "C:\\Users\\Ýstanbul\\eclipse-workspace\\Bibliothek1\\Dat\\Bucherliste.csv"
#define KUNDEN_DAT  "C:\\Users\\Ýstanbul\\eclipse-workspace\\Bibliothek1\\Dat\\Kundenliste.dat"
#define KUNDEN_CSV  "C:\\Users\\Ýstanbul\\eclipse-workspace\\Bibliothek1\\Dat\\Kundenliste.csv"

typedef enum {Back, Delete, List} RECORD_ACTION;
/*Die Verwendung von typedef struct führt zu einem saubereren,
 *  besser lesbaren Code und speichert die Tastenanschläge des Programmierers.
 */

typedef struct {
	unsigned int buchId;
	char buchName[50];
    char autoren[50];
    unsigned erscheinungYear;
    char ISBN[20];
	unsigned int ausleiherId;
	DATUM ausleihenDate;
	DATUM ruckkehrDate;
} BUCH;

typedef struct {
	unsigned int id;
	char firstName[30];
    char lastName[30];
    DATUM birthDate;
	char address[100];
} KUNDEN;
/*Diese Teilen gelten für alle Dateien in unserem Projekt.Sie sind mit Hilfe der "Linked List" organisert.
 * Wie Sie hier sehen können, enthält diese Struktur einen Wert "val" und einen Zeiger auf eine Struktur desselben Typs.
 * Der Wert "val" kann ein beliebiger Wert sein, während der Zeiger "next" die Adresse des nächsten Blocks dieser "verknüpften Liste" enthält.
 * Das Durchlaufen verknüpfter Listen wird also durch diese "next" Zeiger ermöglicht, die die Adresse des nächsten Knotens enthalten.
 */

struct bucher_link
{
    BUCH val;
    struct bucher_link *next;
};

struct kunden_link
{
    KUNDEN val;
    struct kunden_link *next;
};

void processMenuSelection(int);
int showKunden();
int createKunden();
//void kundenList();
void kundenList();
int createBucher();
int deleteBucher();
int listBucher();
void bucherList();
int listAusgeliehBucher();
int bucherAusleihen(boolean);
struct bucher_link* search_book_with_BuchID(unsigned int);
struct kunden_link* search_kunden_with_KundenID(unsigned int);
void updateBuchDatFile();

#endif /* GLOBAL_H_ */
