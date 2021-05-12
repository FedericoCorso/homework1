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

int fc_set_origin(fc_machine* machine, string x, string y){
    
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

int fc_set_q1(fc_machine* machine, string q1){
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

