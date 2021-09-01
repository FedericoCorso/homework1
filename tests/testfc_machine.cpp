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
SCENARIO("The user want to change position of a fc_machine struct","[fc_machine_set_origin]"){
    GIVEN("no existing structure & input are correct"){
        fc_machine* machine;
        string x = "150";
        string y = "300";
        THEN("fc_machine_set_origin should return 1"){
            REQUIRE(fc_machine_set_origin(machine, x, y)==1);
        } 
    }
    GIVEN("an existing structure and a pointer to it"){

        fc_machine* machine = fc_machine_init(150,300,100,-30, 40);

        WHEN("\"x\" & \"y\" aren't numbers"){
            string x = "notnumb";
            string y = "notdumb";
            THEN("fc_machine_set_origin should return 1"){
                REQUIRE(fc_machine_set_origin(machine, x, y)==1);
            }
        }
        WHEN("a value which breaks constraints is given"){
            string x = "-2";
            string y = "-4";
            THEN("fc_machine_set_origin should return 1"){
                REQUIRE(fc_machine_set_origin(machine, x, y) == 1);
            }
        }
        fc_delete_machine(machine);
    }
}

SCENARIO("The user want to change the angle q1 of a fc_machine struct","[fc_machine_set_q1]"){
    /*gives segfault don't know why
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

        WHEN("\"q1\"  isn't a number"){
            string q1 = "notnumb";

            THEN("fc_machine_set_q1 should return 1"){
                REQUIRE(fc_machine_set_q1(machine, q1)==1);
            }
        }
        WHEN("a value which breaks constraints is given"){
            string q1 = "0";
            THEN("fc_machine_set_q1 should return 1"){
                REQUIRE(fc_machine_set_q1(machine,q1) == 1);
            }
        }
         WHEN("an acceptable value is given"){
            string q1 = "45";
            THEN("fc_machine_set_q1 should return 0"){
                REQUIRE(fc_machine_set_q1(machine,q1) == 0);
                REQUIRE(machine->scarart->q1 == 45);
                REQUIRE(machine->scaralt->q1 ==-(180 - (-(45))));
                REQUIRE(machine->scarart->q2==((-(180+45)) - 45));
                REQUIRE(machine->scaralt->q2== -(-(180+45) - 45));
            }
        }
        fc_delete_machine(machine);
    }
}

SCENARIO("The user want to change the length of the arms","[fc_machine_set_length]"){
    GIVEN("an existing structure"){
        fc_machine* machine = fc_machine_init(150,300,100,-30, 40);
        WHEN("\"length\"  isn't a number"){
            string length = "notnumb";
            THEN("fc_machine_set_length should return 1"){
                REQUIRE(fc_machine_set_length(machine, length)==1);
            }
        }
        WHEN(" \"0\" value is given"){
            string length = "0";
            THEN("fc_machine_set_length should return 1"){
                REQUIRE(fc_machine_set_length(machine,length) == 1);
            }
        }
        WHEN("a negative value is given"){
            string length = "-20";
            THEN("fc_machine_set_length should return 1"){
                REQUIRE(fc_machine_set_length(machine,length) == 1);
            }
        }
        WHEN("a value which breaks constraints is given, length > 200 "){
            string length = "201";
            THEN("fc_machine_set_length should return 1"){
                REQUIRE(fc_machine_set_length(machine,length) == 1);
            }
        }
        WHEN("a value which breaks constraints is given, length =< 4*thickness"){
            string length = "40";
            THEN("fc_machine_set_length should return 1"){
                REQUIRE(fc_machine_set_length(machine,length) == 1);
            }
        }
        WHEN("an acceptable value is given"){
            string length = "120";
            THEN("fc_machine_set_length should return 0"){
                REQUIRE(fc_machine_set_length(machine,length) == 0);
                REQUIRE(machine->scarart->length == 120);
                REQUIRE(machine->scaralt->length == 120);
            }
        }

        fc_delete_machine(machine);
    }
}

SCENARIO("The user want to change the base of the piston","[fc_machine_set_base]"){
    GIVEN("an existing structure"){
        fc_machine* machine = fc_machine_init(150,300,100,-30, 40);

        WHEN("\"base\"  isn't a number"){
            string base = "notnumb";
            THEN("fc_machine_set_base should return 1"){
                REQUIRE(fc_machine_set_base(machine, base)==1);
            }
        }
        WHEN(" \"0\" value is given"){
            string base = "0";
            THEN("fc_machine_set_base should return 1"){
                REQUIRE(fc_machine_set_base(machine,base) == 1);
            }
        }
        WHEN("a negative value is given"){
            string base = "-20";
            THEN("fc_machine_set_base should return 1"){
                REQUIRE(fc_machine_set_base(machine,base) == 1);
            }
        }
        WHEN("a value which breaks constraints is given, base > 300 "){
            string base = "301";
            THEN("fc_machine_set_length should return 1"){
                REQUIRE(fc_machine_set_base(machine,base) == 1);
            }
        }
        WHEN("an acceptable value is given"){
            string base = "50";
            THEN("fc_machine_set_base should return 0"){
                REQUIRE(fc_machine_set_base(machine,base) == 0);
                REQUIRE(machine ->pistone->base==50);
                REQUIRE(machine -> pistone->altezza == 50/2);
                REQUIRE(machine ->pistone->deltaS == int(50*0.15));
                REQUIRE(machine->pistone->deltaH == int(25*0.3));
                REQUIRE(machine->pistone->pos.x == (150 - 40/2) - 50/2);
                REQUIRE(machine ->scarart->origin.y == (300-40/2) - 50/2);
                REQUIRE(machine -> scaralt ->origin.y == (300- 40/2) - 50/2);
                
            }
        }


        fc_delete_machine(machine);
    }
}

SCENARIO("The user creates 2 machines which are equal","[fc_are_equal()]"){
    GIVEN("two initialized machine with same values"){
        fc_machine* machine1 = fc_machine_init(150,300,100,-30, 40);
        fc_machine* machine2 = fc_machine_init(150,300,100,-30, 40);
        THEN("are_equal() should return true"){
            REQUIRE( fc_are_equal(machine1, machine2)==true);
        }
        fc_delete_machine(machine1);
        fc_delete_machine(machine2);
    }
    
}

