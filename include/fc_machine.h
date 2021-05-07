#ifndef FC_MACHINE_H
#define FC_MACHINE_H

#include <iostream>
#include <math.h>
#include "fc_scara.h"
#include "pistone.h"

//structure for the machine
struct fc_machine{
    fc_scara* scara;
    Pistone* pistone;
};

/**
 * Function to initialize the mechanism
 * 
*/



#endif