#include "fc_machine.h"

fc_machine* fc_machine_init(int x, int y, int length,int q1, int base){
    
    //definition of parameters for the init function of devices:
    int thickness = length/10;
    int radius = thickness/2;
    // angle of the first arm of the 2nd robot with respect to the x-axis
    int q12 = -(180 - (-q1));
    //angle of the 2nd arm of the right robot
    int q21 = q12 - q1;

    //dynamic mem. allocation of a struct fc_machine
    fc_machine* machine = new fc_machine;

    //initialization of the arms
    machine->pistone = pist_init(base,x - base/2, y);
    if(machine->pistone != NULL){
        machine->scarart = fc_scara_init(thickness, length, radius, q1, q21, x, y - machine->pistone->altezza);
        machine->scaralt = fc_scara_init(thickness, length, radius, q12,-q21, x, y - machine->pistone->altezza);
        return machine;
    }else{
        return NULL;
    }
}

void fc_delete_machine(fc_machine* machine){
    delete machine;
}

string fc_machine_to_svg(fc_machine* machine){

    string rightarm = fc_scara_to_svg(machine->scarart);
    string leftarm = fc_scara_to_svg(machine->scaralt);
    string base = pist_svg(machine->pistone, false);

    string mech = base + leftarm + rightarm;

    return mech;
}

int fc_machine_set_origin(fc_machine* machine, string x, string y){
    
    if(!is_number(x)|| !is_number(y)|| machine == NULL){
           return 1;
       }
       else{
           int new_x = stoi(x);
           int new_y = stoi(y);
           //check both constraints for fc_scara_init & pist_init
           if(new_x < 0 || new_y < 0 || new_y - (machine->pistone->base)/2<0 || new_x + (machine->pistone->base)>800 || new_y > 600){
               return 1;
           }
           machine -> pistone->pos.x = new_x;
           machine->pistone-> pos.y = new_y;
           machine ->scarart->origin.x = new_x;
           machine ->scarart->origin.y = (new_y - machine->pistone->altezza);
           machine ->scaralt->origin.x = new_x;
           machine ->scaralt->origin.y = (new_y - machine->pistone->altezza);
           return 0;
       }
}

int fc_machine_set_q1(fc_machine* machine, string q1){
    if(!is_number(q1) || machine == NULL ){
           return 1;
       }
       else{
           int new_q1 = stoi(q1);
           if(new_q1 >= 360 || new_q1 == 0){
               return 1;
           }
           machine ->scarart->q1 = new_q1;
           machine ->scaralt->q1 = -(180 - (-new_q1));
           //updating also q12 and q22
           machine -> scarart ->q2 = (machine->scaralt->q1) - new_q1;
           machine -> scaralt -> q2 = -(machine->scarart->q2);
           return 0;
    }
}

int fc_machine_set_length(fc_machine* machine, string length){
    if (fc_set_length(machine -> scarart, length)==1){
        return 1;
    }
    else{
        int new_length = stoi(length);
        machine->scarart->length = new_length;
        machine->scaralt->length = new_length;
        return 0;
    }
}

int fc_machine_set_base(fc_machine* machine, string base){
    if(!is_number(base)){
           return 1;
       }
       else{
           int new_base = stoi(base);
           if(new_base > 300 || new_base <= 0){
               return 1;
           }
           machine ->pistone->base = new_base;
           machine -> pistone->altezza = new_base/2;
           machine -> pistone -> deltaS = new_base*0.15;
           machine->pistone->deltaH = machine->pistone->altezza*0.3;
           machine->pistone->pos.x = machine->pistone->pos.x - new_base/2;
           machine ->scarart->origin.y = machine->scarart->origin.y - new_base/2;
           machine -> scaralt ->origin.y = machine->scaralt->origin.y - new_base/2;
           
           return 0;
    }

}


fc_machine* fc_svg_to_machine(string content){
    
    // si trova all'interno della stringa acquisita la parola p
    string p = "polygon points=\"";     //16 caratteri
    size_t found = content.find(p)+size(p);
    size_t found2 = content.find(",",found);
    // creo una nuova stringa contenente il valore di x
    string new_str;
    new_str = content.substr(found, found2);
    
    int a,b,c;
    /* attraverso il comando atoi trasformo la string contenente 
    *  il valore di x in un intero
    */
    a = atoi(new_str.c_str());

    // creo una nuova stringa contenente il valore di y
    found = content.find(" ",found2);
    new_str = content.substr(found2+1, found);
    
    /* attraverso il comando atoi trasformo la string contenente 
    *  il valore di y in un intero
    */
    b = atoi(new_str.c_str());
    
    // creo una nuova stringa contenente il secondo valore di x
    found2 = content.find(",",found);
    new_str = content.substr(found, found2);
    
    /* attraverso il comando atoi trasformo la string contenente 
    *  il secondo valore di x in un intero
    */
    c = atoi(new_str.c_str()); 

    // a cout to check the value of "base" parameter
    int base = c-a;
    cout << "base: " << base << endl;
    // define the "y" parrameter
    int y = b;
    cout << "y coordinate: " << y << endl;

    // leggo il file svg cercando info per il robot scara

    // some auxiliary strings
    string rotation = "= \"r";
    string space = " ";
    string svg_head = "<g";
    size_t r = strlen("rotate(");
    
    //auxiliary string
    string aux;

    // parameters from transformation of the svg file
    p = "= \""; // every instruction in the svg starts with this sequence of chars
    found = content.find(svg_head); // skip declaration of svg file
    size_t found1 = content.find(p,found); // find the first occurence in the file of string p startin from group definition <g
    found2 = content.find("\"", found1+3); // find the first occurence of rotation directive
    size_t found3 = content.find(" ", found1 +3); // find the first space starting from found1
    
    string check_str = content.substr(found1, 4);
    
    aux = content.substr(found1 +3, found2 - found1 - 3 ); // maybe this line could be deleted

    // extracting q1
    string aux1 = content.substr(found1 + 3 + r, found3 - found1 -3 -r);
    int q12 = stoi(aux1);
    cout <<"q12: " << q12 << endl;

    // check on q1 angle value
    int q1 = - (q12 + 180);
    cout << "q1: " << q1 << endl; 

    //extracting length
    found1 = content.find(p, found2);
    found2 = content.find("\"", found1+3);
    aux = content.substr(found1 +3, found2 - found1 - 3 );  
    cout << "length: " << aux << endl;
    int length = stoi(aux);

    //extracting thickness
    found1 = content.find(p, found2);
    found2 = content.find("\"", found1+3);
    aux = content.substr(found1 +3, found2 - found1 - 3 );
    // cout << "thickness: " << aux << endl;
    // int thickness = stoi(aux);

    //extracting q2
    found1 = content.find(p, found2);
    found2 = content.find("\"", found1+3);
    aux1 = content.substr(found1 + 3 + r, found3 - found1 -3 -r);
    // int q2 = stoi(aux1);
    // cout <<"q2: " <<q2 << endl;

    //extracting frame x coordinate
    found1 = content.find(p, found2);
    found2 = content.find("\"", found1+3);
    aux = content.substr(found1 +3, found2 - found1 - 3 );
    cout << "x_coordinate: " << aux << endl;
    int xc = stoi(aux);

    //extracting frame y coordinate
    found1 = content.find(p, found2);
    found2 = content.find("\"", found1+3);
    aux = content.substr(found1 +3, found2 - found1 - 3 );
    //cout << "y_coordinate: " << aux << endl;
    //int yc = stoi(aux);
    
    //extracting radius
    found1 = content.find(p, found2);
    found2 = content.find("\"", found1+3);
    aux = content.substr(found1 +3, found2 - found1 - 3 );
    // cout << "radius: " << aux << endl;
    // int radius = stoi(aux);

    //initializing a new struct
    return fc_machine_init(xc,b,length,q1,base);

   
}

string fc_machine_save(fc_machine* machine){
    string mach = fc_machine_to_svg(machine);
    string s = fc_svg_scara_init(machine -> scaralt, mach);
    
    s.append("</svg>\n");
    
    return fc_save(s);
}

fc_machine* fc_machine_load(string filename){
    string content = fc_read_svg_device(filename);
    
    fc_machine* machine = fc_svg_to_machine(content);

    return machine;
}
