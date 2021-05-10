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
    fc_scara* scara; // pointer to a structure

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
        cout << "Type \"7\" to create a machine" << endl;
        cout << "Type \"8\" to end the execution  of the program" << endl;
        cout << endl;

        // store the input 
        cin >> c;

        switch(c){
            case '1': {
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

                            s = fc_scara_to_svg(scara);
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
            case '2':{
                if(scara != NULL){
                    s = fc_scara_to_svg(scara);
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
            case '3': {
                //first check if a structure exist -> need implementation
                if(scara != NULL){
                    cout << "Insert filename: ";
                    cin >> f;
                    cout << endl;
                    
                    scara = fc_load_from_file(f);
                    
                    //show to the terminal the created structure
                    s = fc_scara_to_svg(scara);
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
            case '4': {
                //first check if a structure exist -> need implementation
                if(scara != NULL){
                    f = fc_scara_save(scara);

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
            case '5': {
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
            case '6': {
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
            case '7':{
                int x;
                int y;
                int length;
                int q1;
                int base;

                cout << "x: " << endl;
                cin >> x;
                cout <<"y: " << endl;
                cin >> y;
                cout << "length: " << endl;
                cin >> length;
                cout << "q1: " << endl; 
                cin >> q1;
                cout << "base: " << endl;
                cin >> base;
                
                fc_machine* machine = fc_machine_init(x,y,length,q1,base);

                cout << machine ->scarart << endl;
                cout << machine -> scaralt << endl;
                
                string s = fc_machine_to_svg(machine);
                cout << s << endl;

                fc_delete_machine(machine);
                break;

            }
            case '8':{
                cout << "end of the program" << endl;
                //delete memory if used
                fc_delete_robot(scara);
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
