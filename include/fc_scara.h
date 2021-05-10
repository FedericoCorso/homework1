#ifndef FC_SCARA_H
#define FC_SCARA_H

#include <iostream>
#include <string>
#include <cstring>
#include <math.h>

#include "fc_svg.h"


using namespace std;
/**
 * coordinates of the frame
*/
struct fc_frame {
    int x;
    int y;
};

/**
 * parameters of the robot:
 * thickness -> arm thickness
 * length -> arm length
 * radius -> revolute joint radius
 * q1 -> angle of 1st arm with respect to the x-axis
 * q2 -> angle of the 2nd arm with respect to the 1st arm
 * origin -> position of the joint connected to the frame 
 * svg_width -> width of the svg window equal to heigth 
 */
struct fc_scara {
    int thickness; 
    int length; 
    int radius;
    int q1; 
    int q2;   
    fc_frame origin; 
    int svg_width; 
};

/**
 * Build the robot asking parameters values to the user & check constraints
 * @param thickness arm thickness
 * @param length arm length
 * @param radius revolute joint radius
 * @param q1 angle of 1st arm with respect to the x-axis
 * @param q2 angle of the 2nd arm with respect to the 1st arm
 * @param x x coordinate of the frame
 * @param y y coordinate of the frame
 * @return fc_scara pointer to a struct containing all dimension of the robot
 * 
 * error signaling C-style:
 *  if thickness <= 0|| 4*thickness >= (length)|| length <= 0 || length > 200 || radius <= 0, returns NULL
 *  if q2 == 180, returns NULL
 *  if 2*radius > thickness, returns NULL
*/
fc_scara* fc_scara_init(int thickness,int length,int radius,int q1,int q2,int x,int y);

/**
 * Delete the dynamic memory for the robot
 * @param robot pointer to an existing fc_scara structure
 * @return void
*/
void fc_delete_robot(fc_scara* robot);

/**
 * Change thickness of an existing fc_scara structure
 * @param robot pointer to an existing fc_scara structure
 * @param thickness value foir new thickness
 * @return int value:
 *     - 1 if constraints are violated
 *     - 0 if constraints are satisfied
*/
int fc_set_thickness(fc_scara* robot, string thickness);
/**
 * Change length of an existing fc_scara structure
 * @param robot pointer to an existing fc_scara structure
 * @param length value for the new length
 * @return int value:
 *     - 1 if constraints are violated nor number is given
 *     - 0 if constraints are satisfied
*/
int fc_set_length(fc_scara* robot,string length);

/**
 * Change radius parameter of an existing fc_scara structure
 * @param robot pointer to an existing fc_scara structure
 * @param radius value for the new radius
 * @return int value:
 *     - 1 if constraints are violated nor number is giver
 *     - 0 if constraints are satisfied
*/
int fc_set_radius(fc_scara* robot,string radius);

/**
 * Change q1 parameter of an existing fc_scara structure
 * @param robot pointer to an existing fc_scara structure
 * @param q1 value for the new q1
 * @return int value:
 *     - 1 if constraints are violated nor number is given
 *     - 0 if constraints are satisfied
*/
int fc_set_q1(fc_scara* robot, string q1);

/**
 * Change q2 parameter of an existing fc_scara structure
 * @param robot pointer to an existing fc_scara structure
 * @param q2 value for the new q2
 * @return int value:
 *     - 1 if constraints are violated
 *     - 0 if constraints are satisfied
*/
int fc_set_q2(fc_scara* robot, string q2);

/**
 * Change the origin parameter of an existing fc_scara structure
 * @param robot pointer to an existing fc_scara structure
 * @param x value for the new x
 * @param y value for the new y
 * @return int value:
 *     - 1 if constraints are violated
 *     - 0 if constraints are satisfied
*/
int fc_set_frame(fc_scara* robot, string x, string y);

/**
 * Function to set dimensions of svg file
 * @param device string with svg representation of scara robot
 * @return string with svg representation
*/
string fc_svg_scara_init(fc_scara* scara, string device);

/**
 * Create a string following svg formatting style 
 * @param scara pointer to fc_scara structure to export
 * @return string with svg representation
*/
string fc_scara_to_svg(fc_scara* scara);

/**
 * read a file and create an fc_scara structure
 * @param content string with file content
 * @return fc_scara* pointer to the new structure
*/
fc_scara* fc_svg_to_scara(string content);

/**
 * Loads an fc_scara structure from a file
 * @param filename string with the name of the file
 * @return fc_scara* pointer to loaded fc_scara struct 
*/
fc_scara* fc_load_from_file(string filename);

/**
 * Save on file the svg representation of a fc_scara structure
 * @param scara fc_scara* pointer to an existing fc_scara struct
 * @return string w\ the filename
*/
string fc_scara_save(fc_scara* scara);

/**
 * Ask parameters to the user
 * @param  int p[7] array of 7 integers, the parameters
 * @return int* pointer to an array of integers
*/
int* fc_ask_parameters(int p[7]);

/**
 * Checks if input string is a number
 * @param  input string
 * @return boolean to identify whether it is a number or not
*/
bool is_number(const std::string& s);

#endif
