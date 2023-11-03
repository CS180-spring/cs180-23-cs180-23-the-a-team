#include "collection.h"

namespace fs = std::filesystem;
using namespace std;

    Collection::Collection()
    {
        
    }

    Collection::Collection(string name)
    {
        //this->name = name;
        AddCollection(name);
    }

    void Collection::addcolName(string name)
    {
        collectionName = name;
    }

    string Collection::getColName()
    {
        return collectionName;
    }

    void Collection::AddCollection(string name)
    {
        if(!verifyCollectionExist(name))
        {
            string dname = "Database/" + name;
            const char* d = dname.c_str();
            fs::create_directories(d);
        }
        else{
            cout << "Collection exists" << endl;
        }
    }

    void Collection::DeleteCollection(string name)
    {
        if(verifyCollectionExist(name) == true)
        {
            string dname = "Database/" + name;
            uintmax_t deletefolder=  fs::remove_all(dname);
            cout << "Deletion Successful" << endl;
        }
        else
        {
            cout << "Deletion Failed" << endl;
        }
        
    }

    void Collection::DeleteFile(string colname, string filename)
    {
        if(verifyFileExist(colname, filename))
        {
            string dname = "Database/" + colname + "/" + filename;
            uintmax_t deletefolder=  fs::remove_all(dname);
            cout << "Deletion Successful" << endl;
        }
        else
        {
            cout << "Deletion Failed" << endl;
        }
        
    }

    void Collection::ViewCollection(string name)
    {
        DIR *directory;
        struct dirent* dent;
        string d = "Database/" + name;
        const char* cname = d.c_str();
        directory=opendir(cname); 
        do 
        {
            dent = readdir(directory);
            if (dent && (dent->d_name[0] != '.') )
            {
                if(checkIFFolder(dent->d_name))
                {
                    cout << "Collection: " << dent->d_name<< endl;
                }
                else
                {
                    cout << "File: " << dent->d_name << endl;
                }
            }
        } while (dent);
        closedir(directory);
    }

    void Collection::ViewAllCollections()
    {
        DIR *directory;
        struct dirent* dent;
        directory=opendir("Database/"); 
        do 
        {
            dent = readdir(directory);
            if (dent && (dent->d_name[0] != '.') )
            {
                if(checkIFFolder(dent->d_name))
                {
                    cout << "Collection: " << dent->d_name<< endl;
                }
                else
                {
                    //cout << "File: " << dent->d_name << endl;
                }
            }
        } while (dent);
        closedir(directory);   
    }

    vector<string> Collection::return_folders()
    {
        vector<string> collections;
        DIR *directory;
        struct dirent* dent;
        directory=opendir("Database/"); 
        do 
        {
            dent = readdir(directory);
            if (dent && (dent->d_name[0] != '.') )
            {
                if(checkIFFolder(dent->d_name))
                {
                    collections.push_back(dent->d_name);
                }
            }
        } while (dent);
        closedir(directory);

        return collections;
    }

    vector<string> Collection::return_files()  //called by encryption
    {
        vector<string> folders = return_folders();
        vector<string> directories;
        string temp;
        DIR *directory;
        struct dirent* dent;
        for(int i = 0; i < folders.size(); i++)
        {
            temp = "Database/" + folders[i];
            directory=opendir(temp.c_str()); 
            do 
            {
                dent = readdir(directory);
                if (dent && (dent->d_name[0] != '.') )
                {
                    if(!checkIFFolder(dent->d_name))
                    {
                        directories.push_back(temp+"/"+dent->d_name);
                    }
                }
            } while (dent);
            closedir(directory);
        }
        return directories;
    }
    
    bool Collection::checkIFFolder(string s)
    {
        for(int i = 0; i < s.length(); i++)
        {
            if(s[i] == '.')
            {
                return false;
            }
        }
        return true;
    }

    bool Collection::verifyCollectionExist(string name)
    {
        DIR *directory;
        struct dirent* dent;
        string n = "Database/";
        const char* d = n.c_str();
        directory=opendir(d);
        do 
        {
            dent = readdir(directory);
            if (dent && (dent->d_name[0] != '.') )
            {
                if(checkIFFolder(dent->d_name) && (dent->d_name == name))
                {
                    return true;
                }
            }
        } while (dent);
        closedir(directory);
        return false;
    }

     bool Collection::verifyFileExist(string collection, string name)
     {
        DIR *directory;
        struct dirent* dent;
        string n = "Database/" + collection;
        const char* d = n.c_str();
        directory=opendir(d);
        do 
        {
            dent = readdir(directory);
            if (dent && (dent->d_name[0] != '.') )
            {
                if(dent->d_name == name)
                {
                    return true;
                }
            }
        } while (dent);
        closedir(directory);
        return false;
     }



