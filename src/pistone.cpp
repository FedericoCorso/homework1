
#include "pistone.h"
#include <iostream>
#include <cstring>

using namespace std;

Pistone* pist_init(unsigned int base, unsigned int x, unsigned int y){

    // controllo sui valori da inserire nella struttura del pistone
    if (base <= 0){
        throw invalid_argument("La base non puo' avere un valore negativo!");
    } else if (base>300) {
        throw invalid_argument("Il pistone che stai cercando di costruire e` troppo grande"); 
    } else if (x<0 || y-base/2<0 || x+base>800 || y>600) {
        throw invalid_argument("Le coordinate non sono compatibili con l'immagine");
    } else {

    // si crea un nuovo puntatore a struttura
    Pistone* ret = new Pistone;

    // si assegnano i valori nella nuova struttura creata
    ret->base       =   base;
    ret->altezza    =   base/2;
    ret->deltaS     =   base*0.15;
    ret->deltaH     =   ret->altezza*0.3;
    ret->pos.x      =   x;
    ret->pos.y      =   y;
    return ret;

    }     
}

string pist_svg(Pistone* pistone, bool misure){

    // creo un nuovo puntatore a stringa
    string ret, virgola = ",", spazio = " ";

    // creo un commento che indica il pezzo che si sta andando a disegnare e la sua base
    ret = "<!--\n \tPistone \n-->\n";
    
    
    
    // scrivo nella stringa il file svg del pistone
    ret +=   "<polygon points=\"";
    
    // partendo dal punto iniziale si inseriscono i punti per 
    // costruire il pistone. 

    // coordinate del punto 1
    ret = ret + to_string(pistone->pos.x) + virgola + to_string(pistone->pos.y) + spazio;
    
    // coordinate del punto 2
    ret = ret + to_string(pistone->pos.x + pistone->base) + virgola + to_string(pistone->pos.y) + spazio;

    // coordinate del punto 3
    ret = ret + to_string(pistone->pos.x + pistone->base) + virgola + to_string(pistone->pos.y - pistone->altezza) + spazio;

    // coordinate del punto 4
    ret = ret + to_string(pistone->pos.x + pistone->base - pistone->deltaS) + virgola + to_string(pistone->pos.y - pistone->altezza) + spazio;

    // coordinate del punto 5
    ret = ret + to_string(pistone->pos.x + pistone->base - pistone->deltaS) + virgola + to_string(pistone->pos.y - pistone->altezza + pistone->deltaH) + spazio;

    // coordinate del punto 6
    ret = ret + to_string(pistone->pos.x + pistone->deltaS) + virgola + to_string(pistone->pos.y - pistone->altezza + pistone->deltaH) + spazio;

    // coordinate del punto 7
    ret = ret + to_string(pistone->pos.x + pistone->deltaS) + virgola + to_string(pistone->pos.y - pistone->altezza) + spazio;

    // coordinate del punto 8
    ret = ret + to_string(pistone->pos.x) + virgola + to_string(pistone->pos.y - pistone->altezza)+ "\"" + spazio;

    // chiusura della funzione poligono e stile
    ret +=  "style=\"fill:gray;stroke:black;stroke-width:1\" />\n";

    if (misure == true){
        // si inserisce il valore della misura
        ret += "<text x = \"" + to_string(pistone->pos.x+pistone->base/2) + "\" y = \"" + to_string(pistone->pos.y + 20) + "\"  fill=\"black\">";
        ret += to_string(pistone->base) + "</text>";

        // si inserisce la linea di riferimento della misura
        ret += "<line x1=\"" +  to_string(pistone->pos.x) + "\" y1=\"" + to_string(pistone->pos.y + 25) + "\" x2=\"" + to_string(pistone->pos.x + pistone->base) + "\" y2= \"" + to_string(pistone->pos.y + 25);
        ret += "\" style=\"stroke:black;stroke-width:2\" />\n";
    }

    return ret;
}


Pistone*  pist_new(string str){

    // si trova all'interno della stringa acquisita la parola p
    string p = "polygon points=\"";     //16 caratteri
    size_t found = str.find(p)+size(p);
    size_t found2 = str.find(",",found);
    // creo una nuova stringa contenente il valore di x
    string new_str;
    new_str = str.substr(found, found2);
    
    unsigned int a,b,c;
    /* attraverso il comando atoi trasformo la string contenente 
    *  il valore di x in un intero
    */
    a = atoi(new_str.c_str());

    // creo una nuova stringa contenente il valore di y
    found = str.find(" ",found2);
    new_str = str.substr(found2+1, found);
    
    /* attraverso il comando atoi trasformo la string contenente 
    *  il valore di y in un intero
    */
    b = atoi(new_str.c_str());
    
    // creo una nuova stringa contenente il secondo valore di x
    found2 = str.find(",",found);
    new_str = str.substr(found, found2);
    
    /* attraverso il comando atoi trasformo la string contenente 
    *  il secondo valore di x in un intero
    */
    c = atoi(new_str.c_str());

    return pist_init(c-a,a,b);
}

void  pist_del(Pistone* pistone){
    delete pistone;
}