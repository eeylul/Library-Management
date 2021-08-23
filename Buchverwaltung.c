#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <conio.h>
#include "buch.h"
#include "bool.h"
#include "datum.h"
#include "global.h"

struct bucher_link *bhead = NULL;
struct bucher_link *bcurr = NULL;
struct bucher_link *btemp = NULL;

int action_selb = 2;
unsigned int maxIndex;
int numBucher;

BUCH a_buch;
BUCH new_buch;

int listBucher() {
	system("cls");
	bucherHeader(102);
	bucherList();

	struct bucher_link *ptr = bhead;

	BUCH buch_val;

	printf("+====+========================================+========================================+====+==================+====+==========+==========+\n");
	printf("| ID |              BuchName                  |                 AutorName              |EJah|       ISBN       |A.ID|Ausleihen |Rückkehr  |\n");
	printf("+====+========================================+========================================+====+==================+====+==========+==========+\n");

	char b_name[40] = "";   //Zeichenbeschränkung, die eingegeben werden kann
	char b_auth[40] = "";   //Zeichenbeschränkung, die eingegeben werden kann
	char b_isbn[18] = "";   //Zeichenbeschränkung, die eingegeben werden kann

	while(ptr != NULL) {
			buch_val = ptr->val;

			for (int i = 0; (i <= 40 && buch_val.buchName[i] != '\n'); ++i) {
				b_name[i] = buch_val.buchName[i];
			    }
			for (int i = 0; (i <= 40 && buch_val.autoren[i] != '\n'); ++i) {
				b_auth[i] = buch_val.autoren[i];
			    }
			for (int i = 0; (i <= 18 && buch_val.ISBN[i] != '\n'); ++i) {  //Bedingungen für die Registrierung des Buches
				b_isbn[i] = buch_val.ISBN[i];
			    }

			printf("|%4d|%-40.40s|%-40.40s|%4d|%-18.18s|%4d|%02d/%02d/%04d|%02d/%02d/%04d|\n",
							buch_val.buchId, b_name, b_auth, buch_val.erscheinungYear,
							b_isbn, buch_val.ausleiherId,
							buch_val.ausleihenDate.day, buch_val.ausleihenDate.month, buch_val.ausleihenDate.year,
							buch_val.ruckkehrDate.day, buch_val.ruckkehrDate.month, buch_val.ruckkehrDate.year);
			printf("+----+----------------------------------------+----------------------------------------+----+------------------+----+----------+----------+\n");
			ptr = ptr->next;
	}

	printf("\nMöchten Sie zum Menü zurückkehren? (J/N)");
	char ch;
	scanf("%s", &ch);

	if (ch == 'j' || ch == 'J') {
		return 1;
//		processMenuSelection(1);
	}else {
		listBucher();
	}

	return 1;
}

////////////////////
int createBucher() {
	bucherHeader(101);
	bucherList();

	BUCH node_value;
	char ch;
	char buch_adi[50];
	char autor_adi[50];
	char buch_ISBN[20];
	char ersch_Jahre[5];

	fgets(buch_adi, sizeof(buch_adi), stdin);
	printf(" Was ist Buch name? ");
	fgets(buch_adi, sizeof(buch_adi), stdin);
	printf(" Was ist Autoren name? ");
	fgets(autor_adi, sizeof(autor_adi), stdin);
	printf(" Was ist Buch ISBN? ");
	fgets(buch_ISBN, sizeof(buch_ISBN), stdin);
	printf(" Was ist Erscheinungsdatum? ");
	scanf("%4s", ersch_Jahre);                  //hier wird die Informationen des Buches gefragt, das Sie speichern möchten

	new_buch.erscheinungYear = atoi(ersch_Jahre);

	for (int i = 0; buch_adi[i] != '\n'; ++i) {
		new_buch.buchName[i] = buch_adi[i];
	}
	for (int i = 0; autor_adi[i] != '\n'; ++i) {
		new_buch.autoren[i] = autor_adi[i];
	}
	for (int i = 0; buch_ISBN[i] != '\n'; ++i) {
		new_buch.ISBN[i] = buch_ISBN[i];
	}

	new_buch.ausleiherId = 0;

	new_buch.ausleihenDate.day = 0;
	new_buch.ausleihenDate.month = 0;
	new_buch.ausleihenDate.year = 0;

	new_buch.ruckkehrDate.day = 0;
	new_buch.ruckkehrDate.month = 0;
	new_buch.ruckkehrDate.year = 0;

	new_buch.buchId = ++maxIndex;

	printf("\nMöchten Sie sich registrieren? (J/N)");   //wenn Sie Buch speichern möchten
	scanf("%s", &ch);
	if (ch != 'j' && ch != 'J')
    {
		return Back;
    }
	btemp = add_to_listb(new_buch, 1);
	struct bucher_link *ptr = bhead;

	FILE *datFile;
	datFile = fopen(BUCHER_DAT, "w+b");

	if (datFile == NULL) {
		fprintf(stderr, "\nError to open the file BUCHER_DAT\n");
		exit(EXIT_FAILURE);
	}
	else {
		while(ptr != NULL)
		{
			node_value = ptr->val;
			fwrite(&node_value, sizeof(BUCH), 1, datFile);

			ptr = ptr->next;
		}
		fclose(datFile);
	}

	printf("\nMöchten Sie die Registrierung fortsetzen? (J/N)");   //wenn Sie andere weitere Bücher speichern möchten
	scanf("%s", &ch);
	if (ch == 'j' || ch == 'J') {
		createBucher();
    } else {
    	return Back;
    }
	return Back;
}

////////////////////
int deleteBucher() {
	bucherHeader(103);
	bucherList();

	char ch;
	int silindi= 0;
	unsigned int buch_ID;

	printf("\nWas ist Buch ID? ");
	scanf("%u", &buch_ID);

	struct bucher_link *for_delete = search_book_with_BuchID(buch_ID);
	if (for_delete == NULL) {
		printf("\nKeine Bücher mit dieser Buch ID registriert: [%u]", buch_ID);
		printf("\nMöchten Sie mit dem Löschen fortfahren? (J/N)");
		scanf("%s", &ch);
		if (ch == 'j' || ch == 'J') {
			deleteBucher();
		} else {
			return 1;
		}
		return 1;
	}

	printf("\nBuch ID     : [%u]", for_delete->val.buchId);
	printf("\nBuch name   : [%s]", for_delete->val.buchName);
	printf("\nAutoren name: [%s]", for_delete->val.autoren);
	printf("\nBuch ISBN   : [%s]", for_delete->val.ISBN);

	printf("\nMöchten Sie wirklich löschen dieses Buch (J/N)");

	scanf("%s", &ch);
	if (ch != 'j' && ch != 'J') {
		printf("\nMöchten Sie mit dem Löschen fortfahren? (J/N)");
		scanf("%s", &ch);
		if (ch == 'j' || ch == 'J') {
			deleteBucher();
		} else {
			return 1;
		}
		return 1;
	}

	silindi = delete_from_listb(for_delete->val.buchId);
	if (silindi != 0) {
		printf("\nTechnischer Fehler!");
		printf("\nMöchten Sie mit dem Löschen fortfahren? (J/N)");
		scanf("%s", &ch);
		if (ch == 'j' || ch == 'J') {
			deleteBucher();
		} else {
			return 1;
		}
		return 1;
	}

	updateBuchDatFile();

	printf("\nMöchten Sie mit dem Löschen fortfahren? (J/N)");
	scanf("%s", &ch);
	if (ch == 'j' || ch == 'J') {
		deleteBucher();
	} else {
		return 1;
	}
	return 1;
}
/////////////
void bucherHeader(int subMenu) {
	system("cls");
	printf("\t\t\t===========================\n");
	printf("\n\t\t\tWelcome to TAU - Bibliothek\n");
	printf("\n\t\t\t===========================\n");
	if (subMenu == 101)
		printf("\t\t\t  NEUEN BUCH ERSTELLEN    \n");
	else if (subMenu == 102)
		printf("\t\t\t     BUECHER AUFLISTEN     \n");
	else
		printf("\t\t\t    BUECHER LOESEN        \n");
	printf("\t\t\t===========================\n\n\n");

}
/* Linked List wird als ein Set der Bündeln dargestellt, wobei jeder Bündel im Form eines Wertes und eineren Anzeiger organisiert wird. Anzeiger (pointer=ptr).
 Pointer zeigt immer auf das nächste Mitglied der Liste.Wenn der Anzeiger NULL ist, ist er der letzte Bündel (node) in der Liste.
 "Linked list" wird dadurch gehalten, dass die lokale Anzeigervariable auf den ersten Teil der Liste.Wenn dieser Anzeiger ebenfalls NULL ist, wird die Liste als leer betrachtet
 */

////////////////////////
struct bucher_link* search_book_with_BuchID(unsigned int bookid)
{
    struct bucher_link *ptr = bhead;
//    struct bucher_link *tmp = NULL;
    boolean found = false;

//    printf("\n Searching the list for value [%d] \n",val);

    while(ptr != NULL) {
//    	printf("\n Aranan: [%u] Bulunan: [%u] \n",bookid, ptr->val.buchId);

     	if(ptr->val.buchId == bookid) {
    		found = true;
            break;
        }
        else
        {
            ptr = ptr->next;
        }
    }

    if(true == found)
    {
          return ptr;
    }
    else
    {
        return NULL;
    }
}

////////////////////////
struct bucher_link* search_in_listb(unsigned int val, struct bucher_link **prev)
{
    struct bucher_link *ptr = bhead;
    struct bucher_link *tmp = NULL;
    boolean found = false;

//    printf("\n Searching the list for value [%d] \n",val);

    while(ptr != NULL)
    {
        if(ptr->val.buchId == val)
        {
            found = true;
            break;
        }
        else
        {
            tmp = ptr;
            ptr = ptr->next;
        }
    }

    if(true == found)
    {
        if(prev)
            *prev = tmp;
        return ptr;
    }
    else
    {
        return NULL;
    }
}

/////////////////////
int delete_from_listb(unsigned int val)
{
    struct bucher_link *prev = NULL;
    struct bucher_link *del = NULL;

//    printf("\n Deleting value [%d] from list\n",val);

    del = search_in_listb(val,&prev);
    if(del == NULL)
    {
        return -1;
    }

    if(prev != NULL)  prev->next = del->next;

    if(del == bcurr) {
       bcurr = prev;
    }else if(del == bhead) {
        bhead = del->next;
    }

    free(del);
    del = NULL;

    return 0;
}
/////////////////////
struct bucher_link* create_listb(BUCH val)
{
//    printf("\n creating list with headnode as [%d]\n",val);
    struct bucher_link *ptr = (struct bucher_link*)malloc(sizeof(struct bucher_link));
    if(NULL == ptr)
    {
        printf("\n Node creation in 'kunden_link' failed \n");
    	exit(EXIT_FAILURE);
    }
    ptr->val = val;
    ptr->next = NULL;

    bhead = bcurr = ptr;
    return ptr;
}
///////////////////
struct bucher_link* add_to_listb(BUCH val, boolean add_to_end)
{
    if(NULL == bhead)
    {
        return (create_listb(val));
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
        bcurr->next = ptr;
        bcurr = ptr;
    }
    else
    {
        ptr->next = bhead;
        bhead = ptr;
    }
    return ptr;
}

//////////////
void bucherList() {
	if (bhead == NULL) {

		FILE *myFile;
		maxIndex = 0;
		BUCH a_buch;
		myFile = fopen(BUCHER_DAT, "r+b");
		if (myFile == NULL) {
			fprintf(stderr,
					"\n%s existiert noch nicht. Die Daten in %s werden imporitert\n",
					BUCHER_DAT, BUCHER_CSV);
			readBucherCSV();
		}

		myFile = fopen(BUCHER_DAT, "r+b");
		numBucher = 0;

		while (1) {
			fread(&a_buch, sizeof(BUCH), 1, myFile);
			if (feof(myFile)) {
				break;
			}
			numBucher++;
			btemp = add_to_listb(a_buch, 1);

			if (maxIndex < a_buch.buchId) {
				maxIndex = a_buch.buchId;
			}
		}
		fclose(myFile);
	}
}

// Bucher.csv dosyasýndaki kayýtlarla Bucher.dat dosyasýný oluþturur.
void readBucherCSV() {
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
//		if (strcmp(line, "     ")) {
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

				if (numBucher > 5 && numBucher < 10) {
					aBuch.ausleiherId = 5;
					aBuch.ausleihenDate.day = 1;
					aBuch.ausleihenDate.month = 1;
					aBuch.ausleihenDate.year = 2021;

					aBuch.ruckkehrDate.day = 31;
					aBuch.ruckkehrDate.month = 1;
					aBuch.ruckkehrDate.year = 2021;
				}

				aBuch.buchId = numBucher;
				fwrite(&aBuch, sizeof(BUCH), 1, myFile);
			}
		}
//		fclose(myFile);
//		fclose(csvFile);
	}
	fclose(myFile);
	fclose(csvFile);
}
//////////////////////
unsigned short tekrarBuch() {

	if (action_selb == 1) {
		printf("\n\nWollen Sie einen weiteren Buch anlegen (J/N)?");

		char ch;
		scanf("%s", &ch);
		if (ch == 'j' || ch == 'J')
			return 1;
		else
			return Back;
	}
	else if (action_selb == 2) {
//		printf("\n\n\tBuch loeschen\t\t(1)\n\tListe aktualisieren\t(2)\n\tZurueck\t\t\t(0)\nBitte waehlen Sie:");
		printf("\n\n\tListe aktualisieren\t(2)\n\tZurueck\t\t\t(0)\nBitte waehlen Sie:");
		char ch;
		do {
			scanf("%s", &ch);

		} while (ch < '0' && ch > '2');
		if (ch == '1')
			return Delete;
		else if (ch == '2')
			return List;

		return Back;
	}
	return Back;
}

void updateBuchDatFile() {

	BUCH buch_in;

	struct bucher_link *ptr = bhead;

	FILE *dataFile;
	dataFile = fopen(BUCHER_DAT, "w+b");
	ptr = bhead;
	if (dataFile == NULL) {
		fprintf(stderr, "\nError to open the file BUCHER_DAT\n");
		exit(EXIT_FAILURE);
	}
	else {
		while(ptr != NULL) {
			buch_in = ptr->val;
			fwrite(&buch_in, sizeof(BUCH), 1, dataFile);

			ptr = ptr->next;
		}
	}
	fclose(dataFile);
}
///////////////


