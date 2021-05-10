#include "fc_svg.h"

string fc_read_svg_device (string filename){
    
    ifstream t(filename);
    stringstream buffer;

    buffer << t.rdbuf();
    string s = buffer.str();

    cout << "Il file " << filename << " e` stato letto" << endl;

    return s;

}

string fc_save(string svg_rep){
    
    string p; // auxiliary string
    //ask for the filename
    cout << "Insert filename: (include \".svg\" extension)" << endl;
    cin >> p ;

    ofstream MyFile(p);

    string content = svg_rep;

    MyFile << content;

    MyFile.close();

    return p;

}

