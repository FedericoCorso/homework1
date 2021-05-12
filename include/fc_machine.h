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
fc_machine* fc_machine_init(int x, int y, int length, int q1, int base);

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

/**
 * function to set coordinates of the origin of the paantograph
 * @param machine pointer to an existing structure
 * @param x string with x coordinate
 * @param y string with y coordinate
 * @return int value:
 *  - 1 if constraints are violated nor number is given or if the pointer is NULL (no existing structure)
 *  - 0 if constraints are satisfied
*/
int fc_set_origin(fc_machine* machine, string x, string y);

/**
 * Function to change q1 angle hence the height reached by the machine
 * @param machine pointer to an existing structure
 * @param q1 string with the new q1 value
 * @return int value:
 *  - 1 if constraints are violated nor number is given or if the pointer is NULL (no existing structure)
 *  - 0 if constraints are satisfied
*/
int fc_set_q1(fc_machine* machine, string q1);


#endif