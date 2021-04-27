#include "fc_scara.h"

fc_scara* fc_scara_init (unsigned int thickness, unsigned int length, unsigned int radius, int q1, int q2, int x, int y){
    // check constraints
    /*
        maybe you should check that the svg fle is of the correct dimensions, you can calculate the dimensions of the svg file 
    */
    if (thickness <= 0 || length <= 0 || radius <= 0 || length >= 300){
        return NULL;
    }
    else if (q2 == 0){
        return  NULL;   
    }
    else if (radius >= thickness) {
        return NULL;
    }
    else{

    /* 
        definition of a pointer to the struct scara 
        and initialization of a variable of type fc_scara with 
        dynamic memory allocation
    */
   fc_scara* robot = new fc_scara;

   robot -> thickness = thickness;
   robot -> length = length;
   robot -> radius = radius;
   robot -> q1 = q1;
   robot -> q2 = q2;
   robot -> origin.x = x;
   robot -> origin.y = y;
   robot -> svg_width = (length*2);

   return robot; // returning the pointer to the created structure
   }
}
   string fc_scara_to_svg(fc_scara* scara){
    
       string scara_svg = "<!--this is an svg representation of a SCARA robot -->\n";
        //drawing the svg window:
       scara_svg += "<svg width = \"" + to_string(scara -> svg_width + scara->origin.x) + "\" height = \"" + to_string(scara -> svg_width+scara->origin.y) + "\">\n";
       // creating a group of images
       scara_svg += "<g transform = \"rotate(" + to_string(scara->q1) + " " + to_string(scara->origin.x) + " " + to_string(scara->origin.y) + ") translate("+ to_string(scara->origin.x - scara->radius) + "," + to_string(scara->origin.y - scara->radius)+")\" ";   
       // rectangle style
       scara_svg += "style = \" fill:rgb(128,128,128);stroke-width:3;stroke:rgb(0,0,0)\">\n";
       // drawing the first arm
       scara_svg += "<rect width = \"" + to_string(scara->length) + "\" height = \"" + to_string(scara->thickness)+ "\" />\n";
       //second arm
       scara_svg += "<rect width = \"" + to_string(scara->length) + "\" height = \"" + to_string(scara->thickness)+ "\" ";
       // translation to the position of the frame
       scara_svg += "transform = \"rotate(" + to_string(scara->q2)+ " " + to_string(scara->length - scara->radius) +" "+ to_string(scara->radius) + ") translate(" + to_string(scara->length  - 2* (scara->radius)) + "," + to_string(0)+ ")\"/>\n";
       // second revolute joint
       scara_svg += "<circle cx=\"" + to_string(scara->length - scara->radius) + "\" cy=\"" + to_string(scara->radius) + "\" r=\"" + to_string(scara->radius) + "\" stroke= \" black \" stroke-width=\"3\" fill=\" white \" /> \n";
       //end of the group
       scara_svg += "</g>\n";
       //first revolute joint
       scara_svg += "<circle cx=\"" + to_string(scara->origin.x) + "\" cy=\"" + to_string(scara->origin.y) + "\" r=\"" + to_string(scara->radius) + "\" stroke= \" black \" stroke-width=\"3\" fill=\" white \" /> \n";
       

       //end svg
       scara_svg.append("</svg>\n");

       return scara_svg;
   }

   void delete_robot(fc_scara* robot){
       delete robot;
   }



