#include "fc_scara.h"

bool is_number(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

int* fc_ask_parameters(int p[7]){

    cout << "Enter a value for each parameter: " << endl;
    string inputValue;
    
    do {
    cout << "thickness: ";
    cin >> inputValue;
    } while(!is_number(inputValue));
    
    p[0] = stoi(inputValue);
    
    if (p[0] <= 0){
        return NULL;
    }
    cout << endl;

    do {
    cout << "length: ";
    cin >> inputValue;
    } while(!is_number(inputValue));
    
    p[1] = stoi(inputValue);

    if (4*p[0] >= p[1]|| p[1] <= 0 || p[1] > 200){
        return NULL;
    }
    cout << endl;

    do {
    cout << "radius: ";
    cin >> inputValue;
    } while(!is_number(inputValue));
    
    p[2] = stoi(inputValue);

    if (p[2] <= 0 || 2*p[2] > p[0]){
        return NULL;
    }
    cout << endl;

    do {
    cout << "q1: ";
    cin >> inputValue;
    } while(!is_number(inputValue));
    
    p[3] = stoi(inputValue);
    
    cout << endl;

    do {
    cout << "q2: ";
    cin >> inputValue;
    } while(!is_number(inputValue));
    
    p[4] = stoi(inputValue);
    
    if (p[4] == 180){
        return  NULL;   
    }
    cout << endl;

    do {
    cout << "x: ";
    cin >> inputValue;
    } while(!is_number(inputValue));
    
    p[5] = stoi(inputValue);
    cout << endl;

    do {
    cout << "y: ";
    cin >> inputValue;
    } while(!is_number(inputValue));
    
    p[6] = stoi(inputValue);
    cout << endl;

    //definition of the array of parameters

    return p;
    
}

fc_scara* fc_scara_init (int thickness,int length,int radius,int q1,int q2,int x,int y){
    
    if (thickness <= 0 || thickness > 50){
        return NULL;
    }
    else if (4*thickness >= length|| length <= 0 || length > 200){
        return NULL;
    }
    else if (radius <= 0 || 2*radius > thickness){
        return NULL;
    }
    else if(q1 > 360){
        return NULL;
    }
    else if (q2 == 180 || q2 > 360){
        return  NULL;   
    }
    //else if(2*length > x || 2 * length > y){
        //return NULL;
    //}
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

string fc_svg_scara_init(fc_scara* scara, string device){
    //definition of the string which will contain the svg representation
    string s;

    s += "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?> \n";
    s += "<svg xmlns=\"http://www.w3.org/2000/svg\" width = \"" + to_string(scara -> svg_width + (2 * scara->origin.x)) + "\" height = \"" + to_string(scara -> svg_width+ (2 * scara->origin.y)) + "\">\n";
    
    s += device;    
    return s;
}

string fc_scara_to_svg(fc_scara* scara, bool measures){
    string scara_svg;
    if(measures == false){
    // creating a group of images
    scara_svg += "<g transform = \"rotate(" + to_string(scara->q1) + " " + to_string(scara->origin.x) + " " + to_string(scara->origin.y) + ") translate("+ to_string(scara->origin.x - scara->radius) + "," + to_string(scara->origin.y - (scara->thickness)/2)+")\" ";   
    // rectangle style
    scara_svg += "style =\" fill:rgb(128,128,128);stroke-width:3;stroke:rgb(0,0,0)\">\n";
    // drawing the first arm
    scara_svg += "<rect width = \"" + to_string(scara->length) + "\" height = \"" + to_string(scara->thickness)+ "\" />\n";
    //second arm
    scara_svg += "<rect width =\"" + to_string(scara->length) + "\" height =\"" + to_string(scara->thickness)+ "\" ";
    // translation to the position of the frame
    scara_svg += "transform = \"rotate(" + to_string(scara->q2)+ " " + to_string(scara->length - scara->radius) +" "+ to_string((scara->thickness)/2) + ") translate(" + to_string(scara->length  - 2* (scara->radius)) + "," + to_string(0)+ ")\"/>\n";
    // second revolute joint
    scara_svg += "<circle cx=\"" + to_string(scara->length - scara->radius) + "\" cy=\"" + to_string((scara->thickness)/2) + "\" r=\"" + to_string(scara->radius) + "\" stroke=\" black \" stroke-width=\"3\" fill=\" white \" /> \n";
    //end of the group
    scara_svg += "</g>\n";
    //first revolute joint
    scara_svg += "<circle cx= \"" + to_string(scara->origin.x) + "\" cy= \"" + to_string(scara->origin.y) + "\" r= \"" + to_string(scara->radius) + "\" stroke= \" black \" stroke-width=\"3\" fill=\" white \" /> \n";
    /*
    //end svg
    scara_svg.append("</svg>\n");
    */
    } else{
        // creating a group of images
        scara_svg += "<g transform = \"rotate(" + to_string(scara->q1) + " " + to_string(scara->origin.x) + " " + to_string(scara->origin.y) + ") translate("+ to_string(scara->origin.x - scara->radius) + "," + to_string(scara->origin.y - (scara->thickness)/2)+")\" ";   
        // rectangle style
        scara_svg += "style =\" fill:rgb(128,128,128);stroke-width:3;stroke:rgb(0,0,0)\">\n";
        // drawing the first arm
        scara_svg += "<rect width = \"" + to_string(scara->length) + "\" height = \"" + to_string(scara->thickness)+ "\" />\n";
        scara_svg += "<line x1=\"0\" y1=\""+to_string(scara->thickness*2)+"\" x2=\""+to_string(scara->length)+"\" y2=\""+to_string(scara->thickness*2)+"\" style=\"stroke:rgb(0,0,0);stroke-width:1\" />\n";
        scara_svg += "<text x=\""+to_string(scara->length/2)+"\" y=\""+to_string(scara->thickness*2 + 15)+"\" stroke-width=\"1\" fill=\"black\">"+to_string(scara->length)+"</text>\n";
        //second arm
        scara_svg += "<rect width =\"" + to_string(scara->length) + "\" height =\"" + to_string(scara->thickness)+ "\" ";
        scara_svg += "transform = \"rotate(" + to_string(scara->q2)+ " " + to_string(scara->length - scara->radius) +" "+ to_string((scara->thickness)/2) + ") translate(" + to_string(scara->length  - 2* (scara->radius)) + "," + to_string(0)+ ")\"/>\n";

        scara_svg += "<line x1=\""+to_string(0)+"\" y1=\""+to_string(scara->thickness*2)+"\" x2=\""+to_string(scara->length)+"\" y2=\""+to_string(scara->thickness*2)+"\" style=\"stroke:rgb(0,0,0);stroke-width:1\"";
        scara_svg += " transform = \"rotate(" + to_string(scara->q2)+ " " + to_string(scara->length - scara->radius) +" "+ to_string((scara->thickness)/2) + ") translate(" + to_string(scara->length  - 2* (scara->radius)) + "," + to_string(0)+ ")\"/>\n";

        scara_svg += "<text x=\""+to_string(scara->length/2)+"\" y=\""+to_string(scara->thickness*2 + 15)+"\" stroke-width=\"1\" fill=\"black\" stroke-width=\"1\"";
        // translation to the position of the frame
        scara_svg += " transform = \"rotate(" + to_string(scara->q2)+ " " + to_string(scara->length - scara->radius) +" "+ to_string((scara->thickness)/2) + ") translate(" + to_string(scara->length  - 2* (scara->radius)) + "," + to_string(0)+ ")\">";
        scara_svg += to_string(scara->length)+"</text>\n";
        // second revolute joint
        scara_svg += "<circle cx=\"" + to_string(scara->length - scara->radius) + "\" cy=\"" + to_string((scara->thickness)/2) + "\" r=\"" + to_string(scara->radius) + "\" stroke=\" black \" stroke-width=\"3\" fill=\" white \" /> \n";
        //end of the group
        scara_svg += "</g>\n";
        //first revolute joint
        scara_svg += "<circle cx= \"" + to_string(scara->origin.x) + "\" cy= \"" + to_string(scara->origin.y) + "\" r= \"" + to_string(scara->radius) + "\" stroke= \" black \" stroke-width=\"3\" fill=\" white \" /> \n";
        

        
    }
    return scara_svg;

   }

   int fc_set_thickness(fc_scara* robot, string thickness){

       if(!is_number(thickness)){
           return 1;
       }
       else{
            int new_thickness = stoi(thickness);

            if(new_thickness <= 0|| 4*new_thickness >= robot->length|| new_thickness <= (robot -> radius)*2){
                return 1;
            }
            robot -> thickness = new_thickness;
            return 0;
       }
   }

   int fc_set_length(fc_scara* robot,string length){
       
       if(!is_number(length)){
           return 1;
       }
       else{
           int new_length = stoi(length);

           if (new_length > 200 || new_length <= 0 || new_length <= (robot->thickness)*4){
           return 1;
           }
           robot -> length = new_length;
           return 0;
       }
   }

   int fc_set_radius(fc_scara* robot,string radius){

       if(!is_number(radius)){
           return 1;
       }
       else{
           int new_radius=stoi(radius);
           if (2 * new_radius > (robot -> thickness) || new_radius <= 0){
               return 1;
            }
            robot-> radius = new_radius;
            return 0;
       }
   }

   int fc_set_q1(fc_scara* robot, string q1){
       if(!is_number(q1)){
           return 1;
       }
       else{
           int new_q1 = stoi(q1);
           if(new_q1 > 360){
               return 1;
           }
           robot-> q1 = new_q1;
           return 0;
       }
   }

   int fc_set_q2(fc_scara* robot, string q2){
       if(!is_number(q2)){
           return 1;
       }
       else{
           int new_q2=stoi(q2);
           if (new_q2 == 180){
                return 1;
            }
            robot-> q2 = new_q2;
            return 0;
       }
   }



   int fc_set_frame(fc_scara* robot, string x, string y){
       if(!is_number(x)|| !is_number(y)){
           return 1;
       }
       else{
           int new_x = stoi(x);
           int new_y = stoi(y);
           if(new_x < 0 || new_y < 0){
               return 1;
           }
           robot -> origin.x = new_x;
           robot -> origin.y = new_y;
           return 0;
       }
   }


    fc_scara* fc_svg_to_scara(string content){
    /*
        this function could be implemented in a better way by intriducing some kind of iteration
    */
    // improvement: instead of "= \"" you could search just "\"" -> try

    // some auxiliary strings
    string rotation = "= \"r";
    string space = " ";
    string svg_head = "<g";
    size_t r = strlen("rotate(");
    
    //auxiliary string
    string aux;

    // parameters from transformation of the svg file
    string p = "= \""; // every instruction in the svg starts with this sequence of chars
    size_t found = content.find(svg_head); // skip declaration of svg file
    size_t found1 = content.find(p,found); // find the first occurence in the file of string p startin from group definition <g
    size_t found2 = content.find("\"", found1+3); // find the first occurence of rotation directive
    size_t found3 = content.find(" ", found1 +3); // find the first space starting from found1
    
    string check_str = content.substr(found1, 4);
    
    aux = content.substr(found1 +3, found2 - found1 - 3 ); // maybe this line could be deleted

    // extracting q1
    string aux1 = content.substr(found1 + 3 + r, found3 - found1 -3 -r);
    int q1 = stoi(aux1);
    cout <<"q1: " <<q1 << endl;

    //extracting length
    found1 = content.find(p, found2);
    found2 = content.find("\"", found1+3);
    aux = content.substr(found1 +3, found2 - found1 - 3 );  
    cout << "length: " << aux << endl;
    int length = stoi(aux);

    //extracting thickness
    found1 = content.find(p, found2);
    found2 = content.find("\"", found1+3);
    aux = content.substr(found1 +3, found2 - found1 - 3 );
    cout << "thickness: " << aux << endl;
    int thickness = stoi(aux);

    //extracting q2
    found1 = content.find(p, found2);
    found2 = content.find("\"", found1+3);
    aux1 = content.substr(found1 + 3 + r, found3 - found1 -3 -r);
    int q2 = stoi(aux1);
    cout <<"q2: " <<q2 << endl;

    //extracting frame x coordinate
    found1 = content.find(p, found2);
    found2 = content.find("\"", found1+3);
    aux = content.substr(found1 +3, found2 - found1 - 3 );
    cout << "x_coordinate: " << aux << endl;
    int xc = stoi(aux);

    //extracting frame y coordinate
    found1 = content.find(p, found2);
    found2 = content.find("\"", found1+3);
    aux = content.substr(found1 +3, found2 - found1 - 3 );
    cout << "y_coordinate: " << aux << endl;
    int yc = stoi(aux);
    
    //extracting radius
    found1 = content.find(p, found2);
    found2 = content.find("\"", found1+3);
    aux = content.substr(found1 +3, found2 - found1 - 3 );
    cout << "radius: " << aux << endl;
    int radius = stoi(aux);

    //initializing a new struct

    fc_scara* scara = fc_scara_init(thickness,length,radius,q1,q2,xc,yc);

    return scara;
}
// maybe implement a function which overwrite to a file using the .replace() method? //


void fc_delete_robot(fc_scara* robot){
    delete robot;
}

fc_scara* fc_load_from_file(string filename){
    
    string content = fc_read_svg_device(filename);

    fc_scara* scara = fc_svg_to_scara(content);

    return scara;
}

string fc_scara_save(fc_scara* scara,bool measures){

    string device = fc_scara_to_svg(scara,measures);
    string s = fc_svg_scara_init(scara, device);
    
    s.append("</svg>\n");
    
    return fc_save(s);
}
