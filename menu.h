#ifndef MENU_H_
#define MENU_H_

/*define ist eine praktische Anweisung, mit der Sie einer Konstanten einen Namen geben können, bevor das Programm kompiliert wird.
 *Wenn beispielsweise der Name einer Konstante, die mit der Direktive #define angegeben wurde,
 *Wenn im Namen einer anderen Konstante oder Variablen enthalten ist, wird er durch ihren Wert ersetzt.
 */

#define MENU_MAIN  				00
#define MENU_EXIT  				99

#define BUCHER_VERWALTUNG		1
#define BUCH_EINTRAGEN	  		101
#define BUCH_LISTE				102
#define BUCH_LOESCHEN			103
#define KUNDEN_VERWALTUNG  		2
#define NEUEN_KUNDEN	 		201
#define KUNDEN_AUFLISTEN		202
#define AUSLEIHEN_VERWALTUNG	3
#define AUSGELIEHENE_BUCHER		301
#define VORHANDENE_BUCHER		302
#define BUCH_AUSLEIHEN			303
#define BUCH_RUCKKEHREN			304

#endif /* MENU_H_ */
