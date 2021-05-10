#include "fc_machine.h"

fc_machine* fc_machine_init(int x, int y, int length,int q1, unsigned int base){
    
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
    machine->scarart = fc_scara_init(thickness, length, radius, q1, q21, x, y - machine->pistone->altezza);
    machine->scaralt = fc_scara_init(thickness, length, radius, q12,-q21, x, y - machine->pistone->altezza);

    return machine;
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