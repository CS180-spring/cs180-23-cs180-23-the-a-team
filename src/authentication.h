#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H

#include <random>
#include <sstream>
#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;
class authentication
{
    public:
            authentication();
            bool createAccount();
            int login_user(string username, string password);
            bool forgot_password(string username);
    private:
    unordered_map<string, pair<string, string> > user_map;
           string Hashing(string salt, string password);
           string SaltGenerator();
           bool CheckPassword(string password);
           bool storeuser(string username, string hash, string salt);
           bool edituser(string username, string hash, string salt);

};

#endif

