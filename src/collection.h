#ifndef COLLECTION_H
#define COLLECTION_H

#include <stdio.h>
#include <dirent.h>
#include <typeinfo>
#include<iostream>
#include <fstream>
#include <string>
#include <bits/stdc++.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <filesystem>
#include "LinkedList.h"

using namespace std;

class Collection
{
    public:
            // void test()
            // {
            //     Node* n = new Node();
            //     std::pair t = std::make_pair(std::string("lightbulbs"),std::string("test"));
            //     jsondata->insertToRear({t});
            // }    
            Collection();
            Collection(string name);
            void addcolName(string name);
            string getColName();
            void AddCollection(string name);
            void DeleteCollection(string name);
            void DeleteFile(string colname, string filename);
            void ViewCollection(string name);
            void ViewAllCollections();
            vector<string> return_files();
            vector<string> return_folders();
            bool checkIFFolder(string s);
            bool verifyCollectionExist(string name);
            bool verifyFileExist(string collection, string name);
            void test()
            {
                Node* n = new Node();
                std::pair t = std::make_pair(std::string("lightbulbs"),std::string("test"));
                jsondata->insertToRear({t});
            }    
    private:
    protected:
            LinkedList* jsondata = new LinkedList();
            string collectionName;
};

#endif
