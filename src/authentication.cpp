#include "authentication.h"
#include "../rapidjson/include/rapidjson/document.h"
#include "../rapidjson/include/rapidjson/filewritestream.h"
#include "../rapidjson/include/rapidjson/writer.h"
#include "../rapidjson/include/rapidjson/ostreamwrapper.h"
#include "../rapidjson/include/rapidjson/filereadstream.h"
#include "../rapidjson/include/rapidjson/stringbuffer.h"
#include "fstream"
#include "gui.h"

#include <cstdio>
using namespace rapidjson;
authentication::authentication()
{ 
    // Opening file, if doesn't open, print error message

    ifstream file("accounts.json");
    if (!file.is_open())
    {
        cout << "Unable to open file accounts.json" << endl;
    }
    
    // Reading file and storing it as a string object
    string Object_file((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()));
    if(Object_file.empty()){

    return;
}
    Document document;
    // Parsing json document from string object
    document.Parse(Object_file.c_str());


    // finding accounts array in the json document
    const Value &users = document["accounts"];

    // looping through every object in the array
    for (int i = 0; i < users.Size(); ++i)
    {
        // Extracting user object
        const Value &user = users[i];
        string username = user["username"].GetString();
        string hash = user["hash"].GetString();
        string salt = user["salt"].GetString();
        // adding user object to the map
        user_map[username] = make_pair(hash, salt);
    }
};

bool authentication::createAccount()
{
    string username, password;
    cout << "\n         ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~-   CREATING A NEW ACCOUNT   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~-\n"
         << endl;

    cout << "\nEnter your username: ";
    cin >> username;
    if (user_map.count(username) > 0)
    {
        cout << "\n\n<<<<<<<<<< USERNAME ALREADY EXISTS, PLEASE TRY LOGGING-IN >>>>>>>>>>\n"
             << endl;

        return false;
    }
    cout << "\n....................................................." << endl;
    cout << "|Password must meet the following criteria:         | " << endl;
    cout << "|   * At least 8 characters long                    |" << endl;
    cout << "|   * Must contain at least one uppercase letter    |" << endl;
    cout << "|   * Must contain at least one lowercase letter    |" << endl;
    cout << "|   * Must contain at least one digit               |" << endl;
    cout << "|   * Must contain at least one special character   |" << endl;
    cout << "....................................................." << endl;
    cout << "\n\nEnter your password: ";
    cin >> password;

    while (!CheckPassword(password))
    {
        cout << "\n\n........................................................" << endl;
        cout << "|Password doesn't meet the following criteria:         |" << endl;
        cout << "|   * At least 8 characters long                       |" << endl;
        cout << "|   * Must contain at least one uppercase letter       |" << endl;
        cout << "|   * Must contain at least one lowercase letter       |" << endl;
        cout << "|   * Must contain at least one digit                  |" << endl;
        cout << "|   * Must contain at least one special character      |" << endl;
        cout << "........................................................" << endl;
        cout << "\n\nEnter your password again: ";

        cin >> password;
    }
    // confrim your entered password
    string pass2;

    cout << "Confirm password(Re-Enter): ";
    cin >> pass2;
    while (pass2 != password)
    {
        cout << "\n\n<<<<<<<<<< PASSWORDS DON'T MATCH! PLEASE TRY AGAIN! >>>>>>>>>>\n"
             << endl;

        cout << "Confirm password(Re-Enter): ";
        cin >> pass2;
    }

    // At least 12 characters long
    // A combination of uppercase letters, lowercase letters, numbers, and symbols.

    string salt = SaltGenerator();
    string final_hash = Hashing(salt, password);
    storeuser(username, final_hash, salt);
    return true;
};
bool authentication::CheckPassword(string password)
{
    // length of the password must be at least 8 characters long.
    if (password.length() < 8)
    {
        return false;
    }
    // Must contain at least one uppercase letter.
    // for ( range_declaration : range_expression )  loop_statement
    // for (char c : str)

    int lowercase, uppercase, number, special = 0;
    for (char c : password)
    {
        if (islower(c))
        {

            lowercase = 1;
        }
        else if (isupper(c))
        {

            uppercase = 1;
        }
        else if (isdigit(c))
        {

            number = 1;
        }
        else
        {

            special = 1;
        }
    }

    if (lowercase > 0 && uppercase > 0 && number > 0 && special > 0)
    {

        return true;
    }

    return false;
};

string authentication::Hashing(string salt, string password)
{
    // combination of the password with the salt
    string combination = password + salt;
    // creating the hash object

    hash<string> create_hash;
    // calling the hash function to generate the hash
    int hash = create_hash(combination);
    // converting the hash to a hex using stringstream object
    stringstream stream;
    stream << hex << hash;
    // converting the hash to a string
    return stream.str();
};

string authentication::SaltGenerator()
{
    string salt = " ";
    // generating random number between 0 and 255 because we want bytes salt
    random_device rand;
    mt19937 gen(rand());
    uniform_int_distribution<int> number(0, 255);

    for (int i = 0; i < 20; i++)
    { // 20bytesalt

        salt = salt + to_string(number(gen));
    }

    return salt;
};

int authentication::login_user(string username, string password)
{
    /*The C++ function std::unordered_map::find() finds an element associated with key k. If operation succeeds then methods returns iterator pointing to the element otherwise it returns an iterator pointing the map::end().*/
    if (user_map.find(username) == user_map.end())
    {
        cout << "\n\n<<<<<<<<<< USERNAME DOESN'T EXIST, PLEASE TRY AGAIN >>>>>>>>>>\n"
             << endl;
        return 2;
    }
    else
    {
        // Extracting user object and comparing it with the password
        string saltinfile = user_map[username].second;
        string oldhash = user_map[username].first;
        string newhash = Hashing(saltinfile, password);
        if (newhash == oldhash)
        {
            return 0;
        }
        else
        {
            cout << "\n\n<<<<<<<<<< INVALID PASSWORD, UNABLE TO LOG-IN, PLEASE TRY AGAIN >>>>>>>>>>\n"
                 << endl;
    
                

            return 1;
        }
    }

    return -1;
};
bool authentication::storeuser(string username, string hash, string salt)
{

    ifstream file("accounts.json");
    if (!file.is_open())
    {
        cout << "accounts.json didn't open" << endl;
        return 1;
    }

    string Objectfile((istreambuf_iterator<char>(file)), (istreambuf_iterator<char>()));
    Document document;
    if (Objectfile.empty())
    {

        document.SetObject();
        Value users(kArrayType);
        document.AddMember("accounts", users, document.GetAllocator());
    }
    else
    {
        document.Parse(Objectfile.c_str());
    }

    /*Value contact(kObject);
contact.AddMember("name", "Milo", document.GetAllocator());
contact.AddMember("married", true, document.GetAllocator());*/

    Value newuser(kObjectType);
    Value user(username.c_str(), document.GetAllocator());
    Value hashval(hash.c_str(), document.GetAllocator());
    Value saltval(salt.c_str(), document.GetAllocator());
    newuser.AddMember("username", user, document.GetAllocator());
    newuser.AddMember("hash", hashval, document.GetAllocator());
    newuser.AddMember("salt", saltval, document.GetAllocator());

    Value &users = document["accounts"];
    users.PushBack(newuser, document.GetAllocator());

    /*
    ofstream ofs("output.json");
    OStreamWrapper osw(ofs);

    Writer<OStreamWrapper> writer(osw);
    d.Accept(writer);*/

    ofstream ofs("accounts.json");
    if (!ofs.is_open())
    {
        cout << "accounts.json for writing didn't open" << endl;
        return 1;
    }

    OStreamWrapper osw(ofs);

    Writer<OStreamWrapper> writer(osw);
    document.Accept(writer);

    return true;
};


bool authentication::forgot_password(string username){
    string password;
     cout << "\n         ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~-   Reseting Password   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~-\n"
         << endl;

    cout << "\n....................................................." << endl;
    cout << "|Password must meet the following criteria:         | " << endl;
    cout << "|   * At least 8 characters long                    |" << endl;
    cout << "|   * Must contain at least one uppercase letter    |" << endl;
    cout << "|   * Must contain at least one lowercase letter    |" << endl;
    cout << "|   * Must contain at least one digit               |" << endl;
    cout << "|   * Must contain at least one special character   |" << endl;
    cout << "....................................................." << endl;
    cout << "\n\nEnter your password: ";
    cin >> password;

    while (!CheckPassword(password))
    {
        cout << "\n\n........................................................" << endl;
        cout << "|Password doesn't meet the following criteria:         |" << endl;
        cout << "|   * At least 8 characters long                       |" << endl;
        cout << "|   * Must contain at least one uppercase letter       |" << endl;
        cout << "|   * Must contain at least one lowercase letter       |" << endl;
        cout << "|   * Must contain at least one digit                  |" << endl;
        cout << "|   * Must contain at least one special character      |" << endl;
        cout << "........................................................" << endl;
        cout << "\n\nEnter your password again: ";

        cin >> password;
    }
    // confrim your entered password
    string pass2;

    cout << "Confirm password(Re-Enter): ";
    cin >> pass2;
    while (pass2 != password)
    {
        cout << "\n\n<<<<<<<<<< PASSWORDS DON'T MATCH! PLEASE TRY AGAIN! >>>>>>>>>>\n"
             << endl;

        cout << "Confirm password(Re-Enter): ";
        cin >> pass2;
    }

    // At least 12 characters long
    // A combination of uppercase letters, lowercase letters, numbers, and symbols.

    string salt = SaltGenerator();
    string final_hash = Hashing(salt, password);

edituser(username, final_hash, salt);
 
       
    return true;
   
    

};

bool authentication::edituser(string username, string final_hash, string salt){

ifstream file("accounts.json");
    if (!file.is_open())
    {
        cout << "accounts.json didn't open" << endl;
        return 1;
    }

    string Objectfile((istreambuf_iterator<char>(file)), (istreambuf_iterator<char>()));
    Document document;
    if (Objectfile.empty())
    {

        document.SetObject();
        Value users(kArrayType);
        document.AddMember("accounts", users, document.GetAllocator());
    }
    else
    {
        document.Parse(Objectfile.c_str());
    }

     Value& allusers = document["accounts"];
 
    /*Value contact(kObject);
contact.AddMember("name", "Milo", document.GetAllocator());
contact.AddMember("married", true, document.GetAllocator());*/

for (Value::ValueIterator i= allusers.Begin(); i != allusers.End(); ++i) {
        Value& user = *i;
        if (user["username"].GetString() == username) {
            
            Value hashval(final_hash.c_str(), document.GetAllocator());
            Value saltval(salt.c_str(), document.GetAllocator());

            user.RemoveMember("hash");
            user.RemoveMember("salt");
            user.AddMember("hash", hashval, document.GetAllocator());
            user.AddMember("salt", saltval, document.GetAllocator());

            break;
        }
    }


    ofstream ofs("accounts.json");
    if (!ofs.is_open())
    {
        cout << "accounts.json for writing didn't open" << endl;
        return 1;
    }

    OStreamWrapper osw(ofs);

    Writer<OStreamWrapper> writer(osw);
    document.Accept(writer);









return true;
};