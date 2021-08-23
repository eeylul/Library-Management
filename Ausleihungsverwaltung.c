#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <conio.h>
#include "ausleih.h"
#include "kunden.h"
#include "bool.h"
#include "datum.h"
#include "global.h"

/*
 * Wir haben entschieden, nicht eine weitere zweidimensionale CSV Datei zu herstellen.
 * Im Gegensatz dazu haben wir gedenkt, Buch- und Kunden Informationen von dem Buch- und Kundenverwaltung herauszuziehen.
 * und unsere Arbeit wird leichter sein. Deswegen wird erstens am Anfang buch- und kunden Linked listen definiert.
 *
 */

struct bucher_link *abhead = NULL;
struct bucher_link *abcurr = NULL;
struct bucher_link *abtemp = NULL;

struct kunden_link *ahead = NULL;
struct kunden_link *acurr = NULL;
struct kunden_link *atemp = NULL;

int anaMenu = 1;
int action_sela = 2;
unsigned int maxIndex;
KUNDEN aa_kunden;  // Als Typ KUNDEN definiert. Es befinden in der global.h
int numBucher;
int numKunden;

int listAusgeliehBucher(boolean fonk) {  // Ausgeleihene Bücher zu erstellen.
	system("cls");

	bucherList_a();

	if (fonk == true) {      //
		ausgeliehHeader(301);   // Falls in dem Tastetur 1 ausdrückt wird, umkehrt (1 + 300)
	}else {
		ausgeliehHeader(302);   // Falls in dem Tastetur 2 ausdrückt wird, umkehrt (2 + 300)
	}

	struct bucher_link *ptr = abhead;   // Kopf von Bücher Linked List

	BUCH ausl_val;

	printf("+====+========================================+========================================+====+==================+====+==========+==========+\n");
	printf("| ID |              BuchName                  |                 AutorName              |EJah|       ISBN       |A.ID|Ausleihen |Rückkehr  |\n");
	printf("+====+========================================+========================================+====+==================+====+==========+==========+\n");

	char b_name[40] = "";
	char b_auth[40] = "";
	char b_isbn[18] = "";

	while(ptr != NULL) {
		ausl_val = ptr->val;
// Wenn Funktion True gekommen wird, um ausgeleihene Bücher zu entschieden, waehlen wir IDs, die unterschiedlich von 0 sind.
		if (fonk == true && ausl_val.ausleiherId != 0) {

			for (int i = 0; (i <= 40 && ausl_val.buchName[i] != '\n'); ++i) {
				b_name[i] = ausl_val.buchName[i];
			    }
			for (int i = 0; (i <= 40 && ausl_val.autoren[i] != '\n'); ++i) {
				b_auth[i] = ausl_val.autoren[i];
			    }
			for (int i = 0; (i <= 18 && ausl_val.ISBN[i] != '\n'); ++i) {
				b_isbn[i] = ausl_val.ISBN[i];
			    }

			printf("|%4d|%-40.40s|%-40.40s|%4d|%-18.18s|%4d|%02d/%02d/%04d|%02d/%02d/%04d|\n",
					ausl_val.buchId, b_name, b_auth, ausl_val.erscheinungYear,
							b_isbn, ausl_val.ausleiherId,
							ausl_val.ausleihenDate.day, ausl_val.ausleihenDate.month, ausl_val.ausleihenDate.year,
							ausl_val.ruckkehrDate.day, ausl_val.ruckkehrDate.month, ausl_val.ruckkehrDate.year);
			printf("+----+----------------------------------------+----------------------------------------+----+------------------+----+----------+----------+\n");
		}
// Wenn Funktion False gekommen wird, um nicht ausgeleihene Bücher (vorhandene Bücher) zu entschieden, waehlen wir IDs, die gleich von 0 sind.
		if (fonk == false && ausl_val.ausleiherId == 0) {
			for (int i = 0; (i <= 40 && ausl_val.buchName[i] != '\n'); ++i) {
				b_name[i] = ausl_val.buchName[i];
			    }
			for (int i = 0; (i <= 40 && ausl_val.autoren[i] != '\n'); ++i) {
				b_auth[i] = ausl_val.autoren[i];
			    }
			for (int i = 0; (i <= 18 && ausl_val.ISBN[i] != '\n'); ++i) {
				b_isbn[i] = ausl_val.ISBN[i];
			    }

			printf("|%4d|%-40.40s|%-40.40s|%4d|%-18.18s|%4d|%02d/%02d/%04d|%02d/%02d/%04d|\n",
					ausl_val.buchId, b_name, b_auth, ausl_val.erscheinungYear,
							b_isbn, ausl_val.ausleiherId,
							ausl_val.ausleihenDate.day, ausl_val.ausleihenDate.month, ausl_val.ausleihenDate.year,
							ausl_val.ruckkehrDate.day, ausl_val.ruckkehrDate.month, ausl_val.ruckkehrDate.year);
			printf("+----+----------------------------------------+----------------------------------------+----+------------------+----+----------+----------+\n");
		}
			ptr = ptr->next;
	}

    printf("\nMöchten Sie zum Menü zurückkehren? (J/N)");
	char ch;
	scanf("%s", &ch);

	if (ch == 'j' || ch == 'J') {
//		return Back;
		processMenuSelection(3);
	}else {
		listBucher();
	}

	return Back;
}
/*  Falls in der Main Menu True gekommen wird, folgendes gearbeitet werden;
 * (3)     - Buch ausleihen
   (4)     - Buchrueckgabe

*/

int bucherAusleihen(boolean fonk) {
	system("cls");
	char ch;
	bucherList();
	kundenList();

	if (fonk == true) {
		ausgeliehHeader(303);
	}else {
		ausgeliehHeader(304);
	}

	unsigned int buch_ID;
	unsigned int kunden_ID;

	if (fonk == true) {
		printf("\nWas ist Buch ID zum Ausleihen ? ");
		scanf("%u", &buch_ID);
	}
	else {
		printf("\nWas ist Buch ID zur Rücksendung ? ");
		scanf("%u", &buch_ID);
	}

	struct bucher_link *for_ausleih = search_book_with_BuchID(buch_ID);  // Linked List für Ausgeleihtete Bücher
	if (for_ausleih == NULL) {
		printf("\nKeine Bücher mit dieser Buch ID registriert: [%u]", buch_ID);
		printf("\nMöchten Sie mit dem Ausleihen fortfahren? (J/N)");
		scanf("%s", &ch);
		if (ch == 'j' || ch == 'J') {
			bucherAusleihen(fonk);
		} else {
			return 3;
		}
		return 3;
	}

	if (fonk == true) {
		printf("\nWas ist Kunden ID zum Ausleihen ? ");
		scanf("%u", &kunden_ID);
	} else {
		printf("\nWas ist Kunden ID zur Rücksendung ? ");
		scanf("%u", &kunden_ID);
	}
	struct kunden_link *for_ruckkehr = search_kunden_with_KundenID(kunden_ID);  // Linked List für Rückkehrte Bücher
	if (for_ruckkehr == NULL) {
		printf("\nKeine Kunden mit dieser Kunden ID registriert: [%u]", buch_ID);
		printf("\nMöchten Sie mit dem Ausleihen fortfahren? (J/N)");
		scanf("%s", &ch);
		if (ch == 'j' || ch == 'J') {
			bucherAusleihen(fonk);
		} else {
			return 3;
		}
		return 3;
	}

	if (fonk == true)
		printf("\n   Zu leihende Buchinformationen   ");
	else
		printf("\n   Zu sendende Buchinformationen   ");
	printf("\n-----------------------------------");
	printf("\nBuch ID     : [%u]", for_ausleih->val.buchId);
	printf("\nBuch ISBN   : [%s]", for_ausleih->val.ISBN);
	printf("\nBuch name   : [%s]", for_ausleih->val.buchName);
	printf("\nAutoren name: [%s]", for_ausleih->val.autoren);

	if (fonk == true)
			printf("\n\n  Zu leihende Kundeninformationen  ");
		else
			printf("\n  Zu sendende Kundeninformationen  ");
	printf("\n-----------------------------------");

	printf("\nKunden ID   : [%u]", for_ruckkehr->val.id);
	printf("\nKunden Name : [%s %s]", for_ruckkehr->val.firstName, for_ruckkehr->val.lastName);

	if (fonk == true)
		printf("\nStimmen Sie zu, das Buch zu leihen? (J/N)");
	else
		printf("\nGenehmigen Sie den Rückruf? (J/N)");

	scanf("%s", &ch);
	if (ch != 'j' && ch != 'J') {
		bucherAusleihen(fonk);
	} else {
		DATUM aus_date;   // Aus- und Ruckdaten als Typ von DATUM definiert.
		DATUM ruck_date;
		if (fonk == true) {
			time_t rawtime;
			int gun, ay, yil;
			struct tm *info;
			time( &rawtime );
			info = localtime( &rawtime );
		    printf("%d/%d/%d", info->tm_year + 1900,info->tm_mon + 1, info->tm_mday);
		    yil = info->tm_year;
		    ay = info->tm_mon ;
		    gun = info->tm_mday;
		    yil = yil + 1900;
		    ay = ay + 1;
		    aus_date.year = yil;
		    aus_date.month = ay;
		    aus_date.day = gun;
		    ay = ay + 1;
			if (ay > 12) {
				ay = 1;
				yil = yil + 1;
			}

		    if ((gun > 30) && (ay == 4 || ay == 6 || ay == 9 || ay == 11)) {
		    	ay = 30;
		   	}
		    if (gun > 28 && ay == 2) ay = 28;

		    ruck_date.day = gun;
		    ruck_date.month = ay ;
		    ruck_date.year = yil;

			for_ausleih->val.ausleiherId = for_ruckkehr->val.id;
			for_ausleih->val.ausleihenDate = aus_date;
			for_ausleih->val.ruckkehrDate = ruck_date;
		} else {
			for_ausleih->val.ausleiherId = 0;
			aus_date.day = 0;
			aus_date.month =0;
			aus_date.year = 0;
			ruck_date.day =0;
			ruck_date.month = 0;
			ruck_date.year = 0;

			for_ausleih->val.ausleihenDate = aus_date;
			for_ausleih->val.ruckkehrDate = ruck_date;
		}
		updateBuchDatFile();

		struct bucher_link *ptr = abhead;

		while(ptr != NULL) {

			if (ptr->val.buchId == for_ausleih->val.buchId) {
				ptr->val.ausleihenDate = for_ausleih->val.ausleihenDate;
				ptr->val.ruckkehrDate = for_ausleih->val.ruckkehrDate;
				ptr->val.ausleiherId = for_ausleih->val.ausleiherId;
			}
			ptr = ptr->next;
		}
		listAusgeliehBucher(true);
	}

	return 3;
}
////////////////////////
void ausgeliehHeader(int subMenu) {
	system("cls");
  	printf("\t\t\t===========================\n");
    printf("\n\t\t\tWelcome to TAU - Bibliothek\n");
    printf("\n\t\t\t===========================\n");
	if (subMenu == 301)
       printf("\t\t\t AUSGELIEHENE BUCHER LISTE \n");
	else if (subMenu == 302)
	   printf("\t\t\t  VORHANDENE BUCHER LISTE  \n");
	else if (subMenu == 303)
	   printf("\t\t\t       BUCH AUSLEIHEN      \n");
	else if (subMenu == 304)
	   printf("\t\t\t       BUCH RÜCKKEHR       \n");
	printf("\t\t\t===========================\n\n\n");

}
/////////////////////
struct bucher_link* create_listb_a(BUCH val)  // Neue Buecher Liste erschaffen.
{
//    printf("\n creating list with buchId as [%u]\n",val.buchId);
    struct bucher_link *ptr = (struct bucher_link*)malloc(sizeof(struct bucher_link));
    if(NULL == ptr)
    {
        printf("\n Node creation in 'kunden_link' failed \n");
    	exit(EXIT_FAILURE);
    }
    ptr->val = val;
    ptr->next = NULL;

    abhead = abcurr = ptr;
    return ptr;
}
///////////////////
struct bucher_link* add_to_listb_a(BUCH val, boolean add_to_end)  // In der Buecher Liste Buch hinzufügen.
{
//	   printf("\n adding to list with buchId as [%u]\n",val.buchId);
    if(NULL == abhead)
    {
        return (create_listb_a(val));
    }

    struct bucher_link *ptr = (struct bucher_link*)malloc(sizeof(struct bucher_link));
    if(NULL == ptr)
    {
        printf("\n Node creation failed \n");
    	exit(EXIT_FAILURE);
    }
    ptr->val = val;
    ptr->next = NULL;

    if(add_to_end)
    {
        abcurr->next = ptr;
        abcurr = ptr;
    }
    else
    {
        ptr->next = abhead;
        abhead = ptr;
    }
    return ptr;
}

//////////////
void bucherList_a() {
	if (abhead == NULL) {

		FILE *myFile;
		maxIndex = 0;
		BUCH a_buch;
		myFile = fopen(BUCHER_DAT, "r+b");
		if (myFile == NULL) {
			fprintf(stderr,
					"\n%s existiert noch nicht. Die Daten in %s werden imporitert\n",
					BUCHER_DAT, BUCHER_CSV);
			readBucherCSV_a();
		}

		myFile = fopen(BUCHER_DAT, "r+b");
		numBucher = 0;

		while (1) {
			fread(&a_buch, sizeof(BUCH), 1, myFile);
			if (feof(myFile)) {
				break;
			}
			numBucher++;
			abtemp = add_to_listb_a(a_buch, 1);

			if (maxIndex < a_buch.buchId) {
				maxIndex = a_buch.buchId;
			}
		}
		fclose(myFile);

	}
}
/////////////////////
// Bucher.csv dosyasýndaki kayýtlarla Bucher.dat dosyasýný oluþturur.
void readBucherCSV_a() {
	FILE *csvFile;
	FILE *myFile;

	csvFile = fopen(BUCHER_CSV, "r");

	if (csvFile == NULL) {
		fprintf(stderr, "\nFehler beim oeffnen der Datei: %s\n", BUCHER_CSV);
		exit(EXIT_FAILURE);
	}

	myFile = fopen(BUCHER_DAT, "w+b");
	if (myFile == NULL) {
		fprintf(stderr, "\nError to open the file\n");
		exit(EXIT_FAILURE);
	}
	char line[200];
	numBucher = 0;
	while (fgets(line, sizeof(line), csvFile)) {

		if (strcmp(line, "     ") != 0) {
			numBucher++;
			BUCH aBuch;
			if (numBucher != 0) {
				char *token;
				token = strtok(line, ";");
				strcpy(aBuch.buchName, token);
				token = strtok(NULL, ";");
				strcpy(aBuch.autoren, token);
				token = strtok(NULL, ";");
				aBuch.erscheinungYear = atoi(token);
				token = strtok(NULL, ";");
				strcpy(aBuch.ISBN, token);
				aBuch.ausleiherId = 0;
				aBuch.ausleihenDate.day = 0;
				aBuch.ausleihenDate.month = 0;
				aBuch.ausleihenDate.year = 0;

				aBuch.ruckkehrDate.day = 0;
				aBuch.ruckkehrDate.month = 0;
				aBuch.ruckkehrDate.year = 0;

				aBuch.buchId = numBucher;
				fwrite(&aBuch, sizeof(BUCH), 1, myFile);
			}
		}

	}
	fclose(myFile);
	fclose(csvFile);
}
/*
void clean_buch_list(struct bucher_link *phead)
{
	 while(phead != NULL) {
	    struct bucher_link *temp = phead;
	    phead = phead->next;
	    free(temp);
	 }
	free(phead);
}
*/

