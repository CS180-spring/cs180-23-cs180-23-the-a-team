//source used https://www.tutorialspoint.com/cplusplus-program-to-implement-caesar-cypher
#include "encrypt.h"
using namespace std; 
#include<iostream>
#include<fstream>
#include <random>
#include <sstream>
bool Security::openFile(const string& filename) {

    ifstream file(filename);
    if(!file.is_open()){
        cout << "Error occured while opening " << filename << endl;
        return false;
    }

    return true;
}

char Security::encryptchar(char character){
    //since we are working with ASCII, it is important if the characters are
    //uppercase or lowercase, so it can set the right base value when we are shifting these characters in the string. 
    if(isalpha(character))
    {
        if(isupper(character)){
            base = 'A';
        } else {
            base = 'a';
        }
        //This is the Caesar Cypher algorithm/formula for encryption
        // ch = ch - 'z' + 'a' - 1;
        character = (character - base  + keyShift + 26) % 26 + base;
    }
    return character;
}

string Security::encrypt(string& text)
{
    //here i want to read from a text file line by line and encrypt it.
    string encodedText;
    string encodedline; 
    istringstream iss(text);
    string line;

    while(getline(iss,line))
    {
        for(char character: line)
        {
            encodedline += encryptchar(character); //because I have to encrypt char by char, that's 
                //why i need to break down the texts in the file into characters and then use the encryptchar function 
                //that  i created earlier to encrypt every line. 
        }
        encodedText += encodedline + '\n';
        encodedline.clear();
    }
    return encodedText;

}
int Security::getKeyShift()  {
    return keyShift;
}


string Security::generateFileName()
{   
    
    const int length = 10;
    string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    const int charSize = chars.size();

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(0, charSize - 1);

    for(int i = 0; i < length; i++){
        tempFile += chars[dist(gen)];
    }

    return "random_" + tempFile + ".json"; 
    //return 'random_" + tempFile + ".txt"; //this can also be used if you want .txt extension
}

char Security::decryptchar(char character){
    //since we are working with ASCII, it is important if the characters are
    //uppercase or lowercase, so it can set the right base value when we are shifting these characters in the string. 
    if(isalpha(character))
    {
        if(isupper(character)){
            base = 'A';
        } else {
            base = 'a';
        }
        //This is the Caesar Cypher algorithm/formula for decyrption
        //ch = ch + 'Z' - 'A' + 1;
        character = (character - base  - keyShift + 26) % 26 + base;
    }
    return character;
}


string Security::decrypt(string& ciphertext){

    string decodedTxt;
    string decodedLine;
    istringstream iss(ciphertext);
    string line;
    while (getline(iss, line))
    {
        for (char character : line)
        {
            decodedLine += decryptchar(character); // Use the decryptchar function to decrypt each character
        }
        decodedTxt += decodedLine + '\n';
        decodedLine.clear();
    }

    return decodedTxt;

}
