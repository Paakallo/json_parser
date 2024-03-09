#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <vector>

using namespace std;
enum button { HELP, OPEN, CHECK, DATA, EXIT };
button in_put;
bool open_or_not=false;
bool maydata = false;
char json_line[1000];
int numsymb = -1; //counts all characters in the file
int att = 0; //counts all variables and its values
vector <char> bufor;
struct syntax {
    string name;//name of the variable
    string val_str;
    int val_int;
    float val_float;
    bool val_bool;

    //these conditions check if the value was written to the file
    bool if_str = false, if_int = false, if_float = false, if_bool = false;
};
syntax variable[100];//saves data

void menu() {

    char press;
    cin >> press;
    switch (press) {
    case 'h':
        in_put = HELP;
        break;
    case 'o':
        in_put = OPEN;
        break;
    case 'c':
        in_put = CHECK;
        break;
    case 'p':
        in_put = DATA;
        break;
    case 'e':
        in_put = EXIT;
        break;
    }


}


void openclose2() {
    char p;
    string name;
    cin >> name;
    ifstream yfile;
    yfile.open(name, ios::in);
    if (!yfile) {
        open_or_not = false;
        cerr << "Name of the file is wrong or it doesn't exist \n";
    }
    else {
        open_or_not = true;
    }

    if (open_or_not == true) {

        while (yfile >> p) {
            numsymb += 1;
            json_line[numsymb] = p;
        }

        cout << "The file was opened " << name << endl;

        yfile.close();

    }

}


void check() { //this function doesn't work for lists and vocabularies
    int end = 0;
    bool right = true;
    if (json_line[0] == '{' && json_line[numsymb] == '}') {

        for (int i = 1; i <= numsymb - 1; i++) {
            if (json_line[i] == '"') {
                for (int j = i; j++;) {
                    bufor.push_back(json_line[j]);
                    if (json_line[j + 1] == '"') {
                        end = j + 1;
                        break;
                    }
                }
                string temp_str(bufor.begin(), bufor.end());
                bufor.clear();
                variable[att].name = temp_str;
                i = end + 1;//the value of i is set to the position of :

            }


            if (json_line[i] == ':') {
                if (json_line[i + 1] == '"') {
                    for (int j = i + 1; j++;) {
                        bufor.push_back(json_line[j]);
                        if (json_line[j + 1] == '"') {
                            end = j + 1;
                            break;
                        }
                    }
                    string temp_str(bufor.begin(), bufor.end());
                    bufor.clear();
                    variable[att].val_str = temp_str;
                    variable[att].if_str = true;
                    i = end + 1;//the value of i is set to the position of ,

                }

                
                else {
                    bool what_is_it; //check the type
                    for (int j = i; j++;) {         //
                        bufor.push_back(json_line[j]);
                        if (json_line[j + 1] == ',') {                           
                            end = j + 1;
                            break;
                        }
                        else if (json_line[j + 1] == '}') { 
                            end = j + 1;
                            break;
                        }
                    }

                    string temp_str(bufor.begin(), bufor.end());

                    for (int k = 0; k <= bufor.size(); k++) {
                        if (temp_str[k] == '.') {
                            try {
                                variable[att].val_float = stof(temp_str);
                                variable[att].if_float = true;
                                what_is_it = false;
                                break;
                            }
                            catch (std::invalid_argument& e) {
                                cerr << "Invalid argument" << i << endl;
                                right = false;   
                                break;
                            }
                        }
                        else {
                            what_is_it = true;
                        }
                    }
                    bufor.clear();

                    if (what_is_it == true) {
                        try {
                            variable[att].val_int = stoi(temp_str);
                            variable[att].if_int = true;
                        }
                        catch (std::invalid_argument& e) {
                            if (temp_str == "true") {
                                variable[att].val_bool = true;
                                variable[att].if_bool = true;
                            }
                            else if (temp_str == "false") {
                                variable[att].val_bool = false;
                                variable[att].if_bool = true;
                            }
                            else if (temp_str == "NULL") {
                                variable[att].val_str = "NULL";
                            }
                            else {
                                cout << "Invalid argument" << i << endl;
                                right = false;
                                break;
                            }
                        }
                    }
                    i = end;
                }
            }


            else {
                cout << "Invalid position: " << i <<" there is no \":\""<< endl;
                right = false;
                break;
            }


            if (json_line[i] == ',') { 
                att += 1;
            }
        }

    }


    else {
    if (json_line[0] != '{') {
        cout << "Invalid position:" << 0 << " there is no \"{\"" << endl;
        right = false;
    }
    if (json_line[0] != '}') {
        cout << "Invalid position:" << numsymb << " there is no \"}\"" << endl;
        right = false;
    }
    }


    if (right == true) {
        cout << "The file is a correct JSON" << endl;
    }

}


void data() {
    cout << "variables "<<att<<"first variable "<< variable[0].name << endl;
    string buf1,var_name,buf2;
    cin >> buf1 >>var_name >> buf2;
        if (buf1=="$['") {
            for (int j = 0; j <= att; j++) {
                if (variable[att].name == var_name ) {
                    int buf = 2 + variable[att].name.length() + 1;
                    if (buf2) {
                        if (variable[att].if_str == true) {
                            cout << "The Variable " << variable[att].name << "has value";
                            for (int k = 0; k <= variable[att].val_str.length(); k++) {
                                cout << variable[k].val_str;
                                if (k == 10) {
                                    cout << "...." << endl;
                                    break;
                                }
                            }
                        }

                        else if (variable[att].if_int == true) {
                            cout << variable[att].val_int << endl;
                        }

                        else if (variable[att].if_float == true) {
                            cout << variable[att].val_float << endl;
                        }

                        else if (variable[att].if_bool == true) {
                            cout << variable[att].val_bool << endl;
                        }
                    }
                    else {
                        cout << "Wrong path" << endl;
                        break;
                    }


                }
          }

        }

        else {
            cout << "Wrong path" << endl;
            break;
        }

}


int main()
{
    cout << "This program verifies correctness of JSON format" << endl;
    cout << "h - HELP" << endl;
    while (true) {
        menu();
        if (in_put == HELP) {
            cout << "Created by: Serhii Pyskovatskyi 196662 IBM I rok" << endl;
            cout << " o - opens file \nOperacja c - checks correctness of JSON format \nOperacja h – help";

        }
        if (in_put == OPEN) {
            system("cls");
            openclose2();
        }
        if (in_put == CHECK && open_or_not == true) {
            system("cls");
            check();
            maydata = true;
        }
        if (in_put == DATA && maydata == true) {
            system("cls");
            data();
        }
        if (in_put == EXIT) {
                system("cls");
                bufor.clear();
                for (int i = 0; i <= numsymb; i++) {
                    json_line[i] = ' ';
                }
                for (int i = 0; i <= att; i++) {
                    variable[i].name ="";
                    variable[i].val_int = 0;
                    variable[i].val_float = 0;
                    variable[i].val_str = "";
                    variable[i].val_bool = false;

                    variable[i].if_bool = false;
                    variable[i].if_int = false;
                    variable[i].if_float = false;
                    variable[i].if_str = false;
                }
                numsymb = -1;
                att = 0;
                open_or_not = false;
                maydata = false;
            }
   }
}
