#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "global.h"

const int BIBLIOTHEK = 1;
const int WRONG_MENU = 1000;
const int MENU_BACK = 0;

int mainMenu();
int bucherVerwaltung();
int kundenVerwaltung();
int ausleihenVerwaltung();
int makeSelection();

void clearScreen();


int main(void) {
	processMenuSelection(MENU_MAIN);
	return EXIT_SUCCESS;
}

//Das zeigt Am Anfang Seite von Programm und wählst du nächste Seite

int mainMenu() {
	printf("\n\n\t\t\tWelcome to TAU - BIBLIOTHEK\n");
	printf("\t\t\t===========================\n\n\n");
	printf("\t(1)\t- Bucher Verwaltung\n");
	printf("\t(2)\t- Kunden Verwaltung\n");
	printf("\t(3)\t- Ausleihen Verwaltung\n");
	printf("\t(99)\t- Programm beenden\n");
	int selection = makeSelection();
	if ((selection < BIBLIOTHEK || selection > 3) && selection != MENU_EXIT) {
		selection = WRONG_MENU;
	}
	return selection;
}
// Hier kann man alle Möglichkeiten und ihre Funktion sehen.
void processMenuSelection(int sel) {
	clearScreen();
	if (sel > WRONG_MENU) {
		printf("\n%s \n", "Ungueltige Option selektiert. Bitte wiederholen.");
		sel -= WRONG_MENU;
	}
	switch (sel) {
	case MENU_MAIN:
		processMenuSelection(mainMenu());
		break;
	case BUCHER_VERWALTUNG:
		printf("\nOption (%d) \" Bucher verwaltung\" selektiert.\n", sel);
		processMenuSelection(bucherVerwaltung());
		break;
	case BUCH_EINTRAGEN:
		printf("\nOption (%d) \"\"Buch eintragen selektiert.\n", sel);
		processMenuSelection(createBucher());
//		processMenuSelection(bucherVerwaltung());
		break;

	case BUCH_LISTE:
		printf("\nOption (%d) \"Buchliste erstellen\" selektiert.\n", sel);
//		processMenuSelection(bucherVerwaltung());
		processMenuSelection(listBucher());
		break;

	case BUCH_LOESCHEN:
//      printf("\nOption (%d) \"Buch loeschen\" selektiert.\n", sel);
//      processMenuSelection(createBucher());
//		processMenuSelection(bucherVerwaltung());
		processMenuSelection(deleteBucher());
		break;
	case KUNDEN_VERWALTUNG:
		printf("\nOption (%d) \"Kunden verwaltung\" selektiert.\n", sel);
		processMenuSelection(kundenVerwaltung());
		break;
	case NEUEN_KUNDEN:
		printf("\nOption (%d) \"Neuen Kunden erstellen\" selektiert.\n", sel);
//		processMenuSelection(kundenVerwaltung());
		processMenuSelection(createKunden());
		break;
	case KUNDEN_AUFLISTEN:
		printf("\nOption (%d) \"Kunden auflisten\" selektiert.\n", sel);
//		processMenuSelection(kundenVerwaltung());
		processMenuSelection(showKunden());
		break;
	case AUSLEIHEN_VERWALTUNG:
		printf("\nOption (%d) \"Ausleihen verwaltung\" selektiert.\n", sel);
		processMenuSelection(ausleihenVerwaltung());
		break;
	case AUSGELIEHENE_BUCHER:
//		printf("\nOption (%d) \"Ausgeliehene Bucher auflisten\" selektiert.\n", sel);
		processMenuSelection(listAusgeliehBucher(1));
//		processMenuSelection(ausleihenVerwaltung());
		break;
	case VORHANDENE_BUCHER:
//		printf("\nOption (%d) \"Vorhandene Bucher auflisten\" selektiert.\n", sel);
		processMenuSelection(listAusgeliehBucher(0));
//		processMenuSelection(ausleihenVerwaltung());
		break;
	case BUCH_AUSLEIHEN:
//		printf("\nOption (%d) \"Buch ausleihen\" selektiert.\n", sel);
//		processMenuSelection(ausleihenVerwaltung());
		processMenuSelection(bucherAusleihen(1));
		break;
	case BUCH_RUCKKEHREN:
//		printf("\nOption (%d) \"Buch ausleihen\" selektiert.\n", sel);
//		processMenuSelection(ausleihenVerwaltung());
		processMenuSelection(bucherAusleihen(0));
		break;
	case MENU_EXIT:
		printf("\nOption (%d) \"Programm beenden\" selektiert. Bye Bye\n", sel);
		break;
	default:
		printf("\nUngueltige Option selektiert. Bitte wiederholen.\n");
		processMenuSelection(mainMenu());
	}
}
//Erste Seite(BUCHVERWALTUNG) Optionen wählen und ihre zurück werte geben.
int bucherVerwaltung() {
	printf("\n\n\t\t\tWelcome to TAU - BIBLIOTHEK\n");
	printf("\t\t\t======================\n\n\n");
	printf("\t(1)\t- Bucher verwaltung\n");
	printf("\t\t(1)\t- Buch eintragen\n");
	printf("\t\t(2)\t- Bucherliste erstellen\n");
	printf("\t\t(3)\t- Buch loeschen\n");
	printf("\t\t(0)\t- zurueck\n");
	printf("\t(2)\t- Kunden verwaltung\n");
	printf("\t(3)\t- Ausleihen verwaltung\n");
	printf("\t(99)\t- Programm beenden\n");
	int selection = makeSelection();
	if ((selection < 1 || selection > 3) && selection != MENU_EXIT && selection != MENU_BACK) {
		selection = WRONG_MENU + BIBLIOTHEK;
	}
	if (selection == MENU_BACK) {
		selection = MENU_MAIN;
	}
	return selection+100;
}
//Zweite Seite(KUNDENVERWALTUNG) Optionen wählen und ihre zurück werte geben.
int kundenVerwaltung() {
	printf("\n\n\t\t\tWelcome to TAU - BIBLIOTHEK\n");
	printf("\t\t\t======================\n\n\n");
	printf("\t(1)\t- Bucherverwaltung\n");
	printf("\t(2)\t- Kundenverwaltung\n");
	printf("\t\t(1)\t- Neuen Kunden erstellen\n");
	printf("\t\t(2)\t- Kunden auflisten\n");
	printf("\t\t(0)\t- zurueck\n");
	printf("\t(3)\t- Ausleihen verwaltung\n");
	printf("\t(99)\t- Programm beenden\n");
	int selection;
	printf("Bitte waehlen Sie: ");
	scanf("%d", &selection);
	if ((selection < 1 || selection > 3 ) && selection != MENU_EXIT && selection != MENU_BACK) {
		selection = WRONG_MENU + 3;
	}
	if (selection == MENU_BACK) {
		selection = MENU_MAIN;
	}
	return selection+200;
}
//Dritte Seite(AUSLEIHENVERWALTUNG) Optionen wählen und ihre zurück werte geben.
int ausleihenVerwaltung() {
	printf("\n\n\t\t\tWelcome to TAU - BIBLIOTHEK\n");
	printf("\t\t\t======================\n\n\n");
	printf("\t(1)\t- Bucher verwaltung\n");
	printf("\t(2)\t- Kunden verwaltung\n");
	printf("\t(3)\t- Ausleihen verwaltung\n");
	printf("\t\t(1)\t- Ausgeliehene Bucher auflisten\n");
	printf("\t\t(2)\t- Vorhandene Bucher auflisten\n");
	printf("\t\t(3)\t- Buch ausleihen\n");
	printf("\t\t(4)\t- Buchrückgabe\n");
	printf("\t\t(0)\t- zurueck\n");
	printf("\t(99)\t- Programm beenden\n");
	int selection = makeSelection();
	if ((selection < 1 || selection > 4) && selection != MENU_EXIT && selection != MENU_BACK) {
		selection = WRONG_MENU + 4;
	}
	if (selection == MENU_BACK) {
		selection = MENU_MAIN;
	}
	return selection+300;
}

void clearScreen() {
	system("cls");
}

int makeSelection() {
	int selection = 0;
	printf("Bitte waehlen Sie: ");
	scanf("%d", &selection);
	return selection;
}

int confirm(int sel) {
	if (sel == 1) {
		printf("\n\nWollen Sie wirklich dieses tolle Programm beenden (J/N)?");
		char ch = getchar();
		if (ch == 'j' || ch == 'J')
			return 1;
		else
			return 0;
	} else {
		printf("\n\nZum Weitermachen eine Taste druecken...");
		getchar();
		return 0;
	}
}
