#ifndef PISTONE_H
#define PISTONE_H

#include <string>
#include "svg.h"

/*
 * Libreria C per costruire figure in SVG
*/

/** Struttura che rappresenta le coordinate da cui viene costruito il pistone 
 * 
 * 
**/
struct Posizione{
    unsigned int x;
    unsigned int y;
};

/** Struttura che rappresenta le dimensioni del pistone 
 * 
 *  
**/
struct Pistone {
    unsigned int base;                 // lunghezza di base del pistone
    unsigned int altezza;              // altezza del pistone
    unsigned int deltaS;               // larghezza della scanalatura del pistone
    unsigned int deltaH;               // altezza della scanalatura del pistone
    Posizione pos;                     // posizione del pistone nell'immagine
};

/** Funzione che inizializza il pistone richiedendo le lunghezze di base e la posizione 
 * 
 *  @param base lunghezza di base del pistone 
 * 
 *  @param x coordinata x del pistone
 * 
 *  @param y coordinata y del pistone
 * 
 *  @return struttura contenente i dati del pistone
 */
Pistone* pist_init( int base, int x,  int y);

/** Funzione che crea una stringa svg contenente l'immagine del pisone 
 * 
 *  @param pistone struttura contenente i dati del pistone
 * 
 *  @return stringa che contiene i dati in svg del pistone
 */
std::string pist_svg(Pistone* pistone, bool misure);

/** Funzione che legge una stringa svg contenente l'immagine del pisone 
 *  e ne costruisce un nuova struct Pistone
 *  
 *  @param file stringa contenente il testo letto da un file svg
 * 
 *  @return struttura pistone contenente i dati trovati all'interno del file
 */
Pistone*  pist_new(std::string file);

/** 
 *  Funzione che libera lo spazio di memoria occupato dalla struttura pistone
 *  
 *  @param pistone spazio di memoria da liberare
 */
void  pist_del(Pistone* pistone);

#endif //PISTONE_H