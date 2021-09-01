#include "catch2/catch2.hpp"
#include "fc_scara.h"

SCENARIO("initialization with non positive values, non integer values nor numbers and violated constraints","[fc_scara_init]"){
    GIVEN("A structure intitialised with fc_scara_init"){
        fc_scara* scara; // define a pointer to a structure of type scara

        WHEN("negative values are given"){
            scara = fc_scara_init(-20,150,5,30,20,10,20);
            THEN(" fc_scara_init should return NULL"){
                REQUIRE(scara == NULL);
            }
        }
        WHEN("zero values are given"){
            scara = fc_scara_init(0,150,5,30,20,10,20);
            THEN("fc_scara_init should return NULL"){
                REQUIRE(scara == NULL);
                }
        }
        WHEN("too big value is provided"){
            scara = fc_scara_init(10,150,5,3333333333333333,20,10,20);
            THEN("fc_scara_init should return NULL"){
                REQUIRE(scara == NULL);
            }
        }
        fc_delete_robot(scara);
    }
}

SCENARIO("User changing parameters of existing struct" ,"[fc_set_functions]"){
    
    GIVEN("An existing structure"){
        fc_scara* scara = fc_scara_init(10,100,5,30,45,10,30);
        THEN("the structure exists and init is correct"){
            REQUIRE(scara->thickness == 10);
            REQUIRE(scara->length == 100);
            REQUIRE(scara->radius == 5);
            REQUIRE(scara->q1 == 30);
            REQUIRE(scara->q2 == 45);
            REQUIRE(scara->origin.x == 10);
            REQUIRE(scara->origin.y == 30);
            REQUIRE(scara != NULL);
        }
        WHEN("thickness is changed"){
            THEN("a negative value is given"){
                REQUIRE(fc_set_thickness(scara, "-12")==1);
            }
            THEN("A litteral is given"){
                REQUIRE(fc_set_thickness(scara, "due")==1);
            }
            THEN("Constraints on thickness are violated"){
                REQUIRE(fc_set_thickness(scara, "25")==1);
                REQUIRE(fc_set_thickness(scara,"1")==1);
            }
            THEN("change successful"){
                REQUIRE(fc_set_thickness(scara, "20")==0);
            }
        }
        WHEN("length is changed"){
            THEN("a negative value is given"){
                REQUIRE(fc_set_length(scara, "-12")==1);
            }
            THEN("A litteral is given"){
                REQUIRE(fc_set_length(scara, "due")==1);
            }
            THEN("float is given"){
                REQUIRE(fc_set_length(scara, "100.4")==1);
            }
            THEN("Constraints on thickness are violated"){
                REQUIRE(fc_set_length(scara, "300")==1);
                REQUIRE(fc_set_length(scara, "40")==1);
            }
            THEN("change successful"){
                REQUIRE(fc_set_length(scara, "100")==0);
            }
        }
        fc_delete_robot(scara);
    }
}
