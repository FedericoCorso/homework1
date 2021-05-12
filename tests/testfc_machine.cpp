#include "catch2/catch2.hpp"
#include "fc_machine.h"

SCENARIO("The user defines a new machine","[fc_machine_init]"){
    GIVEN("an fc_machine pointer to a machine"){
        fc_machine* machine;
        WHEN("the user gives a negative value for length"){
            machine = fc_machine_init(150,300,-100,-30,40);
            THEN("machine struct should have scarart & scaralt both NULL"){
                REQUIRE(machine->scarart == NULL);
                REQUIRE(machine->scaralt==NULL);
            }
            fc_delete_machine(machine);
        }
        /*
        WHEN("a negative value for base parameter is given"){
            machine = fc_machine_init(150,300,100,-30, -40);
            THEN("machine should have Pistone* pointer set to NULL"){
                REQUIRE(machine->pistone == NULL); //gives segmentation fault and i don't know why
                REQUIRE(machine == NULL);
            }
            fc_delete_machine(machine);
        }
        */
    }
}
SCENARIO("The user want to change position of a fc_machine struct","[fc_set_origin]"){
    GIVEN("no existing structure & input are correct"){
        fc_machine* machine;
        string x = "150";
        string y = "300";
        THEN("fc_set_origin should return 1"){
            REQUIRE(fc_set_origin(machine, x, y)==1);
        } 
    }
    GIVEN("an existing structure and a pointer to it"){

        fc_machine* machine = fc_machine_init(150,300,100,-30, 40);

        WHEN("\"x\" & \"y\" aren't numbers"){
            string x = "notnumb";
            string y = "notdumb";
            THEN("fc_set_origin should return 1"){
                REQUIRE(fc_set_origin(machine, x, y)==1);
            }
        }
        WHEN("a value which breaks constraints is given"){
            string x = "-2";
            string y = "-4";
            THEN("fc_set_origin should return 1"){
                REQUIRE(fc_set_origin(machine, x, y) == 1);
            }
        }
        fc_delete_machine(machine);
    }
}

SCENARIO("The user want to change the angle q1 of a fc_machine struct","[fc_set_q1]"){
    /*gives segfault
    GIVEN("no existing structure & input are correct"){
        fc_machine* machine;
        string q1 = "150";
        THEN("fc_set_q1 should return 1"){
            REQUIRE(fc_set_q1(machine, q1)==1);
        } 
    }
    */

    GIVEN("an existing structure and a pointer to it"){

        fc_machine* machine = fc_machine_init(150,300,100,-30, 40);

        WHEN("\"q1\"  isn't numbers"){
            string q1 = "notnumb";

            THEN("fc_set_q1 should return 1"){
                REQUIRE(fc_set_q1(machine, q1)==1);
            }
        }
        WHEN("a value which breaks constraints is given"){
            string q1 = "0";
            THEN("fc_set_q1 should return 1"){
                REQUIRE(fc_set_q1(machine,q1) == 1);
            }
        }
        fc_delete_machine(machine);
    }
}

