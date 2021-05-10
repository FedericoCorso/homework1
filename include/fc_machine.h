#ifndef FC_MACHINE_H
#define FC_MACHINE_H

#include <iostream>
#include <math.h>

#include "fc_scara.h"
#include "pistone.h"
#include "fc_svg.h"

/**
 * Structure for the machine
*/
struct fc_machine{
    fc_scara* scarart; // right arm
    fc_scara* scaralt; //left arm
    Pistone* pistone; 
};

/**
 * Function to initialize the machine
 * @param x int, x-coordinate of the arms 
 * @param y int, y-coordinate of the arms
 * @param length int length of the arms
 * @param q1 , angle of the first arm
 * @param base unsigned int base of the piston
 * @return fc_machine ,pointer to a struct of type fc_machine
*/
fc_machine* fc_machine_init(int x, int y, int length, int q1, unsigned int base);

/**
 * Function to free dynamic memory allocated for the machine
 * @param machine , pointer to an existing structure
 * @return void 
*/
void fc_delete_machine(fc_machine* machine);

/**
 * Create a string following svg formatting style
 * @param machine pointer to a struct of type fc_machine
 * @return string with svg representation of the machine
*/
string fc_machine_to_svg(fc_machine* machine);


#endif