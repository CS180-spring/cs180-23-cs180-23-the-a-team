#ifndef GUI_H
#define GUI_H
#include <string>
#include <iostream>
#include <fstream>
#include "csvtojson.h"
#include "json.h"
#include <filesystem>
#include "collection.h"
#include "LinkedList.h"
#include "encrypt.h"

using namespace std;

class gui
{
    public:
          void main();
          int validinput();
          
    private:
        
         void welcome();
         void login();
         void menu(bool& user);
         void reset(string username);
         Json j;
         Security SE;
         Collection col;        
};

#endif
