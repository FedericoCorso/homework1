#ifndef SVG_H
#define SVG_H

#include <string>

/** 
 *  Funzione che aggiunge alla stringa contenente i pezzi in svg il codice per creare il file svg
 *  
 *  @param componenti strigna contenente i componenti in svg
 * 
 *  @return si ritorna una stringa contenente il svg pronto per essere salvato su un file
 */
std::string svg(std::string componenti);

/** 
 *  Funzione che trascrive la stringa contenente il SVG in un file
 *  
 *  @param filename nome del file su cui salvare la stringa
 * 
 *  @param str_svg stringa contenente il svg da salvare sul file
 */
void svg_to_file(std::string filename, std::string str_svg);

/** 
 *  Funzione che trascrive il contenuto di un file svg in una stringa
 *  
 *  @param filename nome del file da leggere
 * 
 *  @return stringa che contiene il svg presente nel file
 */
std::string svg_read(std::string filename);

#endif //SVG_H