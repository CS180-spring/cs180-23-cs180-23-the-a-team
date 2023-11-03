#ifndef CSVTOJSON_H
#define CSVTOJSON_H

#include <iostream>
#include <fstream>
#include <string>
#include <fstream>
#include <vector>
#include "json.h"
#include "collection.h"

using namespace std;

class csvtojson
{
    public:
        csvtojson(){}
        void printcsv(string name, int datarows, ostream& output);
    private:

};

#endif
