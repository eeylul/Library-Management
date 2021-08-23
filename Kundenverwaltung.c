/*
Dies sind unsere Header Dateien. Sie beastehen aus
der <stdio.h> und <conio.h> Dateien, die zur Bereitstellung der Konsoleingabe/-ausgabe verwendet wird,
der Standard Library Header Datei, btw. <stdlib.h>,
der <string.h> Datei, die enhält Funktions-, Dtentyp- und Makrodefiniton für Zeichenfolgen,
der anderen header Dateien, die wir schon mal gechrieben haben.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <conio.h>
#include "kunden.h"
#include "bool.h"
#include "datum.h"
#include "global.h"

struct kunden_link *head = NULL;
struct kunden_link *curr = NULL;
struct kunden_link *temp = NULL;

struct kunden_link *temp_head = NULL;

int actMenu = 2;
int action_sel = 2;
unsigned int maxIndex;
int numKunden;

KUNDEN a_kunden;
KUNDEN new_kunden;

/*
Im Vergleich zum Hotelmanagement-Programm haben wir hier Linked-List und Knoten verwendet.
Der Hauptgrund dafür ist, dass Arrays eine statische Datenstruktur sind und ihre Länge im Laufe der Zeit nicht geändert werden kann.
Auf der anderen Seite ist Linked List eine dynamische Datenstruktur.
Elemente btw. Knoten können an einer beliebigen Position gehalten werden, aber sie können miteinander verbinden.
Wir die Linked-List bevorzugt, weil wir noch nicht wissen, wie viele Datenvolumen in diesem Bibliothekprogramm gespeichern werden können.
 */

int showKunden() {
	system("cls");
//	int selection = 2;
	kundensHeader(202);
	kundenList();
	struct kunden_link *ptr = head;
//	if (ptr == NULL) {
//		kundenList();
//		*ptr = head;
//	}

	KUNDEN node_val;

	printf("+=======+=====================+=====================+============+========================================================================+\n");
	printf("|  ID   |     Vorname         |    Familienname     |Geburtsdatum|        Adresse                                                         |\n");
	printf("+=======+=====================+=====================+============+========================================================================+\n");

	while(ptr != NULL)
	{
		node_val = ptr->val;

		char substr[200] = "";
		for (int i = 0; node_val.address[i] != '\n'; ++i) {
			substr[i] = node_val.address[i];
		    }

		printf("| %5d |%-20.20s |%-20.20s | %2d/%2d/%4d |%-72.70s|\n",
				node_val.id, node_val.firstName, node_val.lastName, node_val.birthDate.day,
				node_val.birthDate.month, node_val.birthDate.year, substr);
		printf("+-------+---------------------+---------------------+------------+------------------------------------------------------------------------+\n");

		ptr = ptr->next;
	}

	action_sel=2;
	int action = tekrarKunden();
	if (action == Delete) {
//		action_sel=3;
//		action = tekrarKunden();
		showKunden();
	}
	else if (action == List) {
		action_sel=2;
		showKunden();
	}
	return Back;
}

/*
In diesem Abschnitt geben wir den Namen, Nachnamen, Adresse und Geburtstag der Kunden ein, die in unsere Bibliothek kommen.
fgets () - Funktion verwendet, um eine einzelne Zeile aus der Datei zu lesen.
printf () - Funktion wird verwendet, um die gewünschten Daten auf dem Bildschirm zu drucken.
scanf () - Funktion wird für die Dateneingabe verwendet.
 */

////////////////////
int createKunden() {
	kundensHeader(201);
	kundenList();

	KUNDEN node_value;

	char kunden_adi[30];
	char kunden_sadi[30];
	char kunden_adres[99];

	fgets(kunden_adi, sizeof(kunden_adi), stdin);
	printf("\n Was ist Kunden Vorname? ");
//	scanf("%s", new_kunden.lastName);
	fgets(kunden_adi, sizeof(kunden_adi), stdin);
	printf("\n Was ist Kunden NachName? ");
	fgets(kunden_sadi, sizeof(kunden_sadi), stdin);
	printf("\n Was ist Kunden Addresse? ");
	fgets(kunden_adres, sizeof(kunden_adres), stdin);
	printf("\n Was ist Kunden Geburstdatum - Tag? ");
	scanf("%2u", &new_kunden.birthDate.day);
	printf(" Was ist Kunden Geburstdatum - Monat? ");
	scanf("%2u", &new_kunden.birthDate.month);
	printf(" Was ist Kunden Geburstdatum - Jahr? ");
	scanf("%4u", &new_kunden.birthDate.year);

	for (int i = 0; kunden_adi[i] != '\n'; ++i) {
		new_kunden.firstName[i] = kunden_adi[i];
	}
	for (int i = 0; kunden_sadi[i] != '\n'; ++i) {
		new_kunden.lastName[i] = kunden_sadi[i];
	}
	for (int i = 0; kunden_adres[i] != '\n'; ++i) {
		new_kunden.address[i] = kunden_adres[i];
	}
	strcat(new_kunden.address, "\n");

	new_kunden.id = ++maxIndex;

	temp = add_to_list(new_kunden, 1);
	struct kunden_link *ptr = head;

	FILE *datFile;
	datFile = fopen(KUNDEN_DAT, "w+b");

	if (datFile == NULL) {
		fprintf(stderr, "\nError to open the file KUNDEN_DAT\n");
		exit(EXIT_FAILURE);
	}
	else {
		while(ptr != NULL)
		{
			node_value = ptr->val;
			fwrite(&node_value, sizeof(KUNDEN), 1, datFile);

			ptr = ptr->next;
		}
	}
	fclose(datFile);

	action_sel=1;
	int action = tekrarKunden();
	if (action == Delete) {
//		action_sel=3;
//		action = tekrarKunden();
		showKunden();
	}
	else if (action == List) {
		action_sel=2;
		showKunden();
	}
	return Back;
/*
	printf("\nMöchten Sie zum Menü zurückkehren? (J/N)");
	char ch = getchar();
	scanf("%s", &ch);
	return actMenu;
*/
}
/////////////
void kundensHeader(int subMenu) {
	system("cls");
	printf("\t\t\t===========================\n");
	printf("\n\t\t\tWelcome to TAU - Bibliothek\n");
	printf("\n\t\t\t===========================\n");
	if (subMenu == 201)
		printf("\t\t\t  NEUEN KUNDEN ERSTELLEN    \n");
	else
		printf("\t\t\t     KUNDEN AUFLISTEN     \n");
	printf("\t\t\t===========================\n\n\n");

}
///////////////////// Die Linked-List besteht hier aus zwei Teilen. Wert ist der erste Teil und Next ist zweite Teil.

struct kunden_link* create_list(KUNDEN val)
{
//    printf("\n creating list with headnode as [%d]\n",val);
    struct kunden_link *ptr = (struct kunden_link*)malloc(sizeof(struct kunden_link));
    if(NULL == ptr)
    {
        printf("\n Node creation in 'kunden_link' failed \n");
    	exit(EXIT_FAILURE);
    }
    ptr->val = val;
    ptr->next = NULL;

    head = curr = ptr;
    return ptr;
}
///////////////////
struct kunden_link* add_to_list(KUNDEN val, boolean add_to_end)
{
    if(NULL == head)
    {
        return (create_list(val));
    }

/*
    if(add_to_end)
        printf("\n Adding node to end of list with value [%d]\n",val);
    else
        printf("\n Adding node to beginning of list with value [%d]\n",val);
*/

    struct kunden_link *ptr = (struct kunden_link*)malloc(sizeof(struct kunden_link));
    if(NULL == ptr)
    {
        printf("\n Node creation failed \n");
    	exit(EXIT_FAILURE);
    }
    ptr->val = val;
    ptr->next = NULL;

    if(add_to_end)
    {
        curr->next = ptr;
        curr = ptr;
    }
    else
    {
        ptr->next = head;
        head = ptr;
    }
    return ptr;
}

//////////////
void kundenList() {

	if (head == NULL) {

	FILE *myFile;
	maxIndex = 0;
	KUNDEN a_kunden;
	myFile = fopen(KUNDEN_DAT, "r+b");
	if (myFile == NULL) {
		fprintf(stderr,
				"\n%s existiert noch nicht. Die Daten in %s werden imporitert\n",
				KUNDEN_DAT, KUNDEN_CSV);
		readKundenCSV();
	}
	myFile = fopen(KUNDEN_DAT, "r+b");
	numKunden = 0;

	while (1) {
		fread(&a_kunden, sizeof(KUNDEN), 1, myFile);
		if (feof(myFile)) {
			break;
		}
		numKunden++;
		temp = add_to_list(a_kunden, 1);

		if (maxIndex < a_kunden.id) {
			maxIndex = a_kunden.id;
		}
	}
	fclose(myFile);
	}
}

// Die Datei Customers.dat wird hier mit ihren Datensätzen in der Datei Customers.csv erstellt.
void readKundenCSV() {
	FILE *csvFile;
	FILE *myFile;

	csvFile = fopen(KUNDEN_CSV, "r");

	if (csvFile == NULL) {
		fprintf(stderr, "\nFehler beim oeffnen der Datei: %s\n", KUNDEN_CSV);
		exit(EXIT_FAILURE);
	}

	myFile = fopen(KUNDEN_DAT, "ab");
	if (myFile == NULL) {
		fprintf(stderr, "\nError to open the file\n");
		exit(EXIT_FAILURE);
	}
	else {
		char line[200];
		numKunden = 0;
		char *dateStr;
		while (fgets(line, sizeof(line), csvFile)) {
			if (strcmp(line, "       ")) {
				numKunden++;
				KUNDEN aKunden;
				if (numKunden != 0) {
					char *token;
					token = strtok(line, ";");
					strcpy(aKunden.firstName, token);
					token = strtok(NULL, ";");
					strcpy(aKunden.lastName, token);
					dateStr = strtok(NULL, ";");
					token = strtok(NULL, ";");
					strcpy(aKunden.address, token);
					aKunden.birthDate = parseDatum(dateStr);
					aKunden.id = numKunden;
					fwrite(&aKunden, sizeof(KUNDEN), 1, myFile);
				}
			}
		}
		fclose(myFile);
		fclose(csvFile);
	}
}
//////////////////////
unsigned short tekrarKunden() {
//	KUNDEN kunden_node;
	if (action_sel == 1) {
		printf("\n\nWollen Sie einen weiteren Kunden anlegen (J/N)?");
//		char ch = getchar();
		char ch;
		scanf("%s", &ch);
		if (ch == 'j' || ch == 'J')
			return 1;
		else
			return Back;
	}
	else if (action_sel == 2) {
//		printf("\n\n\tKunden loeschen\t\t(1)\n\tListe aktualisieren\t(2)\n\tZurueck\t\t\t(0)\nBitte waehlen Sie:");
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
	else {
		printf("\n\nGeben Sie die ID des zu loeschenden Kunden ein: ");
		unsigned int toDelete = 0;
		scanf("%u", &toDelete);

		if (delete_from_list(toDelete) == 1) {
			deleteKundenFromDat(toDelete);
			printf("\n\nKundendatensatz mit der ID %u existiert nicht", toDelete);
		} else {
			printf("\n\nKundendatensatz mit der ID %u wird nicht gelöscht.", toDelete);
		}
		return List;
	}
}

void deleteKundenFromDat(int to_Delete) {
	KUNDEN kunden_del;
	KUNDEN kunden_in;

	struct kunden_link *ptr = head;
	struct kunden_link *pptr = NULL;
	while(ptr != NULL)
	{
		kunden_del = ptr->val;
		if (kunden_del.id == to_Delete) {
			if (pptr == NULL) {
				head = ptr->next;
			}else {
				pptr->next = ptr->next;
			}
			break;
		}
		pptr = ptr;
		ptr = ptr->next;
	}

	FILE *dataFile;
	dataFile = fopen(KUNDEN_DAT, "w+b");
	ptr = head;
	if (dataFile == NULL) {
		fprintf(stderr, "\nError to open the file KUNDEN_DAT\n");
		exit(EXIT_FAILURE);
	}
	else {
		while(ptr != NULL)
		{
			kunden_in = ptr->val;
			fwrite(&kunden_in, sizeof(KUNDEN), 1, dataFile);

			ptr = ptr->next;
		}
	}
	fclose(dataFile);
}
///////////////
struct kunden_link* search_in_list(unsigned int valu, struct kunden_link **prev)
{
    struct kunden_link *ptr = head;
    struct kunden_link *tmp = NULL;
    boolean found = false;

//    printf("\n Searching the list for value [%d] \n",val);

    while(ptr != NULL)
    {
        if(ptr->val.id == valu)
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
/////////////////////////////////////
int delete_from_list(unsigned int val)
{
    struct kunden_link *prev = NULL;
    struct kunden_link *del = NULL;

    printf("\n Deleting value [%d] from list\n",val);

    del = search_in_list(val,&prev);
    if(del == NULL)
    {
        return -1;
    }
    else
    {
		printf("\n\nWollen Sie wirklich den Kunden mit der Id %d loeschen (J/N)?\n", val);
//		val, del->val.firstName, del->val.lastName);

		char ch;
		scanf("%s", &ch);
		if (ch != 'j' && ch != 'J') {
			printf("\n Der Kundendatensatz mit der Id %d wurde nicht als Ihre Anfrage gelöscht\n", val);
			return -1;
		}

        if(prev != NULL)
            prev->next = del->next;

        if(del == curr)
        {
            curr = prev;
        }
        else if(del == head)
        {
            head = del->next;
        }
    }

    free(del);
    del = NULL;

    return 0;
}
///////////////////
struct kunden_link* search_kunden_with_KundenID(unsigned int kundenid)
{
    struct kunden_link *ptr = head;
//    struct bucher_link *tmp = NULL;
    boolean found = false;

//    printf("\n Searching the list for value [%d] \n",val);

    while(ptr != NULL) {

     	if(ptr->val.id == kundenid) {
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
