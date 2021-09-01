#include "fc_scara.h"
#include "fc_svg.h"
#include "svg.h"
#include "pistone.h"
#include "fc_machine.h"

using namespace std;

int main() {
    //array of int
    int p[7];
    int* pt;
    //variable to control the program flow
    bool ex = true;

    //commandline program to create a structure, load a structure from an existing file and save to a file a new structure
    char c; // choice parameter
    string s; // string to store the svg string of the structure or input from user
    string f; // string to store the name of the file or to store input from user
    int n=0; //intero per memorizzare il numero di machines
    fc_scara* scara = NULL; // pointer to a structure
    fc_machine** mach_arr = NULL; //doppio puntatore per poter istanziare un vettore di puntatori a machines

    // messages for the user
    cout << "Build your scara robot with this program!" << endl;

    cout << endl;

    cout << "Chose an option: "<< endl;

    cout << endl;
    while(ex == true){
        cout << "Type \"1\" to create a new structure."<< endl;
        cout << "Type \"2\" to show the created structure." << endl;
        cout << "Type \"3\" to create a structure from an existing svg file"<< endl;
        cout << "Type \"4\" to save the structure to a new file"<< endl;
        cout << "Type \"5\" to edit an existing structure" << endl;
        cout << "Type \"6\" to delete the created structure" << endl;
        cout << "Type \"7\" to create an array of machines" << endl;
        cout << "Type \"8\" to save the array of machines in a file" << endl;
        cout << "Type \"m\" to modify parameters in the array of machines from an existing svg file"<< endl;
        cout << "Type \"9\" to create an array of machines from an existing svg file"<< endl;
        cout << "Type \"e\" to end the execution  of the program" << endl;
        cout << endl;

        // store the input 
        cin >> c;

        switch(c){
            case '1': { //to create a new structure.
                //first check if a structure exist and if the user wants to overwrite it 
                if (scara != NULL){
                    string answ; // auxiliary string to memorize user's inputs
                    cout << "There's a structure saved, do you want to overwrite it? (Yes) (No): ";
                    cin >> answ; // takes user's input
                    cout << endl;

                    if (answ == "Yes"){

                        cout << "Do you want to check the existing structure before proceding? (Yes) (No): ";
                        cin >> answ;
                        cout << endl;

                        if (answ == "Yes"){

                            s = fc_scara_to_svg(scara,true);
                            cout << "the svg string is: \n \n" + s << endl;

                            cout << "Still want to make changes? (Yes) (No): ";
                            cin >> answ;
                            cout << endl;

                            if (answ == "Yes"){
                                
                                pt = fc_ask_parameters(p);
                                //initialization and save to a file of the new struct:
                                scara = fc_scara_init(pt[0],pt[1],pt[2],pt[3],pt[4],pt[5],pt[6]);
                                
                                break;
                            }
                            else{
                                cout << endl;
                                cout << "Nothing has been changed." << endl;
                                cout << endl;
                                break;
                            }
                            

                        }
                        
                        pt = fc_ask_parameters(p);
                        //initialization and save to a file of the new struct:
                        scara = fc_scara_init(pt[0],pt[1],pt[2],pt[3],pt[4],pt[5],pt[6]);
                        
                        break;
                    }
                    else{
                        cout << endl;
                        cout << "Nothing has been changed." << endl;
                        cout << endl;
                        break;
                    }

                }
                pt = fc_ask_parameters(p);

                if (pt == NULL){
                    cout << endl;
                    cout << "constraint violated, exit from editing" << endl;
                    cout << endl;
                    break;
                }
                else{
                    //initialization and save to a file of the new struct:
                    scara = fc_scara_init(p[0],p[1],p[2],p[3],p[4],p[5],p[6]);
                    cout << endl;
                    cout << "New structure created succesfully!" << endl;
                    cout << endl;
                    break;
                }
        

            }
            case '2': { //to show the created structure.
                if(scara != NULL){
                    s = fc_scara_to_svg(scara,true);
                    cout << "the svg string is: \n \n" + s << endl;
                    break;
                }
                else{
                    cout << endl;
                    cout << "Structure not defined. " << endl;
                    cout << endl;
                    break;
                }


            }
            case '3': { //to create a structure from an existing svg file
                //first check if a structure exist -> need implementation
                if(scara != NULL){
                    cout << "Insert filename: ";
                    cin >> f;
                    cout << endl;
                    
                    scara = fc_load_from_file(f);
                    
                    //show to the terminal the created structure
                    s = fc_scara_to_svg(scara,true);
                    cout << "the svg string is: \n \n" + s << endl;

                    cout << endl;
                    
                    break;
                }
                else{
                    cout << endl;
                    cout << "Structure not defined. " << endl;
                    cout << endl;
                    break;
                }

            }
            case '4': { //to save the structure to a new file
                //first check if a structure exist -> need implementation
                if(scara != NULL){
                    f = fc_scara_save(scara,true);

                    cout << "struct created and saved to: " << f << " file" << endl;
                    
                    cout << endl;

                    break;
                }
                else{
                    cout << "Structure not defined. " << endl;
                    cout << endl;
                    break;
                }

            }
            case '5': { //to edit an existing structure
                if(scara != NULL){

                    cout << "thickness: ";
                    cin >> s;
                    cout << endl;
                    cout << fc_set_thickness(scara,s);
                    cout << endl;

                    cout << "length: ";
                    cin >> s;
                    cout << endl;
                    cout << fc_set_length(scara,s);
                    cout << endl;
                    
                    cout << "radius: ";
                    cin >> s;
                    cout << endl;
                    cout << fc_set_radius(scara,s);
                    cout << endl;

                    cout << "q1: ";
                    cin >> s;
                    cout << endl;
                    cout << fc_set_q1(scara,s);
                    cout << endl;
                    
                    cout << "q2: ";
                    cin >> s;
                    cout << endl;
                    cout << fc_set_q2(scara,s);
                    cout << endl;
                    
                    cout << "x: ";
                    cin >> s;
                    cout << endl;
                    cout << "y: ";
                    cin >> f;
                    cout << endl;

                    cout << fc_set_frame(scara,s,f);
                    cout << endl;
                    
                    cout << endl;
                    break;

                }
                else{
                    cout << endl;
                    cout << "Structure not defined. " << endl;
                    cout << endl;
                    break;
                }
                
            }
            case '6': { //to delete the created structure
                if(scara != NULL){
                    fc_delete_robot(scara);
                    scara = NULL;
                    cout << endl;

                    break;
                }
                else{
                    cout << endl;
                    cout << "Structure not defined. " << endl;
                    cout << endl;
                    break;
                }
                    
            }
            case '7': { //to create machines
                // qui è necessario implementare una procedura che riconosca la violazione dei vincoli !!!
                //variabili ausiliarie
                int x;
                int y;
                int length;
                int q1;
                int base;

                //richiedo all'utente il numero di machines che vuole istanziare
                cout << "Number of machines to create: ";
                cin >> n;
                if(n<0){
                    cout << "# must be positive!" << endl;
                }

                //allocazione dinamica di un vettore di puntatori fc_machines
                mach_arr = new fc_machine*[n]; 
                //richiesta parametri in input dall'utente
                cout << "Parametri per la machine: " << endl;
                cout << "x coordinate of the first machine: " << endl;
                cin >> x;
                if(x <= 0){
                    cout << "x must be positive!" << endl;
                    cout << "constraint violated, end of the program" << endl;
                    break;

                }
                cout <<"y coordinate of the first machine: " << endl;
                cin >> y;
                if(y <= 0){
                    cout << "y must be positive!" << endl;
                    cout << "constraint violated, end of the program" << endl;
                    break;
                }
                cout << "length of arms: " << endl;
                cin >> length;
                if(length > 200 || length <= 0){
                    cout << "lenght must be in (0;200]!" << endl;
                    cout << "constraint violated, end of the program" << endl;
                    break;
                }
                cout << "q1: " << endl; 
                cin >> q1;
                if(q1 > 360){
                    cout << "q1 must be < 360!" << endl;
                    cout << "constraint violated, end of the program" << endl;
                    break;
                }
                cout << "base: " << endl;
                cin >> base;
                if(base > 300 || base <= 0){
                    cout << "base must be in (0;300]!" << endl;
                    cout << "constraint violated, end of the program" << endl;
                    break;
                }
                
                //inizializzazione elementi in array di machines
                for(int i = 0; i < n; i++){
                    mach_arr[i] = fc_machine_init(x,y,length,q1,base);
                    x += length; //in modo da stampare le machine in riga senza sovrapporle
                }
                cout << "machine array created" << endl;
                break;

            }
            case '8': { //to save the array of machine in a file
                if( mach_arr != NULL){
                    //costruisco un svg contenente tutte le machine
                    string ss;
                    for(int i = 0; i < n; i++){
                        ss += fc_machine_to_svg(mach_arr[i]);
                    }
                    ss = fc_svg_scara_init(mach_arr[0]->scaralt,ss);
                    ss.append("</svg>\n");

                    cout << "nome del file in cui vuoi salvare l'array di machine: ";
                    cin >> f;

                    svg_to_file(f,ss);
                    cout << "machine created and saved to: " << f << " file" << endl;
                    
                    cout << endl;

                    break;
                }
                else{
                    cout << "Machine not defined. " << endl;
                    cout << endl;
                    break;
                }
            }
            case '9': { //to create a machine from an existing svg file
                
                if(mach_arr == NULL){
                    cout << "Machines not defined." << endl;
                    cout << "Allocating memory to upload from file" << endl;
                    cout << "how many machines in the file?";
                    cin >> n;
                    if(n <= 0){
                        cout << "n must be positive number" << endl;
                        cout << "end of the program" << endl;
                        break;
                    }else{
                          mach_arr = new fc_machine*[n]; 
                    }
                }
                    cout << "Insert filename: ";
                    cin >> f;
                    cout << endl;
                    
                    string p = fc_read_svg_device(f);
                    
                    cout << p << endl;
                    
                    //analizzo la stringa in p
                    string l = "<polygon";
                    string aux;
                    size_t found[n]; //array in cui memorizzo le ricorrenze nella stringa
                    for(int i = 0; i < n; i++){
                        if(i == 0){ 
                            //memorizzo la posizione della prima occorrenza
                            found[i] = p.find(l);
                            //cout << found[i] << endl;
                            //cout << p.substr(found[0],string::npos) << endl;
                        }else if(i != 0){
                            found[i] = p.find(l,found[i-1]+1);
                            //cout << found[i] << endl;
                            //cout << p.substr(found[i],string::npos)<< endl;
                        }
                    }
                    
                    // ciclo per estrazione parametri ed inizializzazione machine nell'array
                    for(int i = 0; i < n;i++){//dato il vettore found[n] estraggo le porzioni di stringhe associate ad ogni machine
                        if(i < n-1){ //
                            cout << "prova" << endl;
                            aux = p.substr(found[i],found[i+1]-found[i]);
                            cout << aux << endl;
                            fc_delete_machine(mach_arr[i]);
                            mach_arr[i] = fc_svg_to_machine(aux);
                        }else{
                            cout << "n-1" << endl;
                            aux = p.substr(found[i],string::npos-found[i]);
                            cout << aux << endl;
                            fc_delete_machine(mach_arr[i]);
                            mach_arr[i] = fc_svg_to_machine(aux);
                        }   
                    }
                    
                    //show to the terminal the created structures
                    for(int i = 0; i < n; i++){
                        cout << fc_machine_to_svg(mach_arr[i])<<endl;
                    }
                    
                    break;
                

            }
            case 'm':{ //to edit parameters of machines in the array
                //check if the array exists
                if(mach_arr == NULL){
                    cout << "machines not defined!" << endl;
                    cout << "end of the program" << endl;
                    break; 
                }else{ //in memoria c'è una machine
                    cout << "There is an array of " << n << " machines" << endl;
                    cout << "Which one you want to update? (input must be a number <= n)";
                    int m;
                    cin >> m;
                    if(m > n){
                        cout << "out of range" << endl;
                        break;
                    }else if(m <0){
                        cout << "must be positive!" << endl;
                        break;
                    }
                    int j;
                    string t;
                    
                    string k;
        
                    cout << "Update origin: " << endl;
                    cout << "new x: ";
                    cin >> t;
                    cout << endl;
                    cout << "new y: ";
                    cin >> k;
                    j = fc_machine_set_origin(mach_arr[m-1],t,k);
                    if(j == 1){
                        cout << "constraint violated" << endl;
                        break;
                    }
                    

                    cout << "Update length of arms: " << endl;
                    cin >> t;
                    j = fc_machine_set_length(mach_arr[m-1],t);
                    if(j == 1){
                        cout << "constraint violated" << endl;
                        break;
                    }

                    cout << "Update base: " << endl;
                    cin >> t;
                    j = fc_machine_set_base(mach_arr[m-1],t);
                    if(j == 1){
                        cout << "constraint violated" << endl;
                        break;
                    }

                    cout << "Update angle q1: " << endl;
                    cin >> t;
                    j = fc_machine_set_q1(mach_arr[m-1],t);
                    if(j == 1){
                        cout << "constraint violated" << endl;
                        break;
                    }

                    break;

                }

            }
            case 'e': { //to end the execution  of the program
                cout << "end of the program" << endl;
                //delete memory if used
                fc_delete_robot(scara);
                if(n > 0){
                        for(int i = 0; i < n; i++){
                        fc_delete_machine(mach_arr[i]);
                    }
                }

                
                //exit while loop
                ex = false;

                cout << endl;

                break;
            }
            defult: break;
        }
    }

    return 0;
}
