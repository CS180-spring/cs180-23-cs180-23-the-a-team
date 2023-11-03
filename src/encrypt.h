#ifndef ENCRYPT_H
#define ENCRYPT_H
#include <string>
#include <random>
using namespace std;
//SIMPLE FILE ENCRYPTION FOR BACKEND SECURITY USING CAESAR CIPHER ALGORITHM
//WHICH IS A SIMPLE WIDELY KNOWN ENCRYPTION TECHNIQUES.
//MOSTLY USED FOR SMALL PROGRAMS AND TEXT FILES, SUCH AS OUR DATA FILES, SINCE 
//THEY ARE SMALL AND IN FORM OF TEXT/STRING, THIS ALGORITHM WILL PERFECTLY WORK WITH THIS.

class Security
{
    private:
        int keyShift = 4; 
    public:
        string cipherText;
        string tempFile;
        char character; 
        char base;
        string encodedmessage;
    public:
        Security(){ 
            //since I don't want the user know how I am encrypting their
            //information, I can't ask them for key,so I have to use random
            //library and generate a random key everytime. 
            //random_device rd;
           // mt19937 gen(rd());
            //uniform_int_distribution<int> dist(0, 25);
           // keyShift = 4;
        } 
        Security(int keyShift){
            this->keyShift = keyShift;
            }
        bool openFile(const string& filename);
        string generateFileName();
        int getKeyShift();
        string encrypt(string& text); // this encrypys the entire string.
        string decrypt(string& cipherText);
        char encryptchar(char charactert); //this encrypts a single character using the Caesar cipher algorithm
        char decryptchar(char character); 
        //in order to decrypt a full string, we need to decrypt each ascii characters first. 


};

#endif
