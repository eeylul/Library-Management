#ifndef BOOL_H_
#define BOOL_H_

/*"boolean" ist ein Datentyp, der Wahrheit oder L�ge speichern kann.
 *Jeder Wert ungleich Null entspricht "true", w�hrend 0 "false" entspricht*/

typedef enum {false,true} boolean;

void printBoolean(boolean b);

#endif /* BOOL_H_ */
