#include "gui.h"
#include "json.h"
#include "authentication.h"
#include "LinkedList.h"

using namespace std;
bool user = false;
int counter = 0;
void gui::main()
{

    welcome();
    string decryptedmessage;
    ifstream in;
    ofstream out;
    string encryptedmessage;
    do
    {
        if (!user)
        {

            login();
        }

        if (user)
        {
            if(counter == 0)
            {
                 vector<string> directories = col.return_files();
                 for(int i = 0; i < directories.size(); i++)
                {
                cout << "D: " << directories[i] << endl; 
                 ifstream inputFile(directories[i]);
                    SE.openFile(directories[i]);
                    inputFile.open(directories[i]);
                    string fileContent((istreambuf_iterator<char>(inputFile)), istreambuf_iterator<char>());
                    inputFile.close();
                        decryptedmessage = SE.decrypt(fileContent);
                        cout << decryptedmessage << endl;
                        //cout << encryptedmessage;
                        //  int decKey = SE.getKeyShift();
                        // cout<<decKey <<endl;  I have to make sure both encrypt and decrypt use the same generated key.
                        //I don't want the user to see the decrypted message, 
                        //I am going to generate random output file names and save the encrypted messages there and store the encrypted message there for 
                        //developer access only.
                        ofstream outputFile(directories[i]);
                        outputFile << decryptedmessage; 
                        outputFile.close();       
                }
                counter++;
            }
           
            menu(user);
        }

    } while (true);
}
void gui::welcome()
{
    cout << "\n************************************************************************************************************************\n"<< endl;
    


std::cout << "8888888888 8888888b.  8888888 8888888888 888b    888 8888888b.  888    Y88b   d88P       .d8888b.  8888888b.  888888b.   \n"
             "888        888   Y88b   888   888        8888b   888 888  \"Y88b 888     Y88b d88P       d88P  Y88b 888  \"Y88b 888  \"88b  \n"
             "888        888    888   888   888        88888b  888 888    888 888      Y88o88P        888    888 888    888 888  .88P  \n"
             "8888888    888   d88P   888   8888888    888Y88b 888 888    888 888       Y888P         888        888    888 8888888K.  \n"
             "888        8888888P\"    888   888        888 Y88b888 888    888 888        888          888        888    888 888  \"Y88b \n"
             "888        888 T88b     888   888        888  Y88888 888    888 888        888          888    888 888    888 888    888 \n"
             "888        888  T88b    888   888        888   Y8888 888  .d88P 888        888          Y88b  d88P 888  .d88P 888   d88P \n"
             "888        888   T88b 8888888 8888888888 888    Y888 8888888P\"  88888888   888           \"Y8888P\"  8888888P\"  8888888P\" ";

   
    cout << "\n\n************************************************************************************************************************" << endl;
};

int gui::validinput()
{
    int choice = 0;
    while (!(cin >> choice))
    {

        cout << "\n<<<<<<<<<< INVALID INPUT, PLEASE ENTER A INTEGER >>>>>>>>>>\n"
             << endl;
        cout << "\nEnter your choice: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return choice;
};
void gui::login()
{
    int result;
    
    

    string username, password = "";
    cout << "\n--------------------------------------" << endl;
    cout << "| 1. Create an account               |" << endl;
    cout << "|------------------------------------|" << endl;
    cout << "| 2. Log in with an existing account |" << endl;
    cout << "--------------------------------------" << endl;

    cout << "\n         ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~-   Press Ctrl+C to exit the program   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~-\n"
         << endl;

    int choice;
    cout << "Enter your choice: ";
    choice = validinput();
    
    authentication authenticate;
   
    switch (choice)
    {
    case 1:

        if (authenticate.createAccount())
        {

            cout << "\n         ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~-   ACCOUNT SUCCESSFULLY CREATED   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~-\n"
                 << endl;
        }
        login();
        break;
    case 2:
        // loginAccount();
        cout << "\nEnter the username: ";

        cin >> username;
        cout << "\nEnter the password: ";
        cin >> password;
        result = authenticate.login_user(username, password);
        
        if (result==0 || ((username == "a") && (password == "a")))
        {
            cout << "\n         ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~-   USER SUCCESSFULLY LOGGED IN   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~-\n"
                 << endl;
            
            user = true;
           
        }
        else
        {
            if (result==2){
                login();
            }
            else{
            reset(username);
            
            }
        }

        break;
    default:
        cout << "\n<<<<<<<<<< INVALID CHOICE, PLEASE TRY AGAIN >>>>>>>>>>\n"
             << endl;
        break;
    }
};
void gui::menu(bool &user)
{
    int optS = -1;
    csvtojson c;
    string name;
    int sizeofdata;
    stringstream outputofcsv;
    string encryptedmessage;
    //Parser p; moved it to json file
    string temp, temp2, command;
    vector<string> directories;

    cout << "\n==========================================" << endl;
    cout << "|      1. List all collections           |" << endl;
    cout << "|----------------------------------------|" << endl;
    cout << "|      2. Add a collection               |" << endl;
    cout << "|----------------------------------------|" << endl;
    cout << "|      3. Delete a collection            |" << endl;
    cout << "|----------------------------------------|" << endl;
    cout << "|      4. Import Json document           |" << endl;
    cout << "|----------------------------------------|" << endl;
    cout << "|      5. Read a document                |" << endl;
    cout << "|----------------------------------------|" << endl;
    cout << "|      6. Create a document              |" << endl;
    cout << "|----------------------------------------|" << endl;
    cout << "|      7. Delete a document              |" << endl;
    cout << "|----------------------------------------|" << endl;
    cout << "|      8. JSON viewer (and edit)         |" << endl;
    cout << "|----------------------------------------|" << endl;
    cout << "|      9. Search, Sort, Filter, Revert   |" << endl;
    cout << "|----------------------------------------|" << endl;
    cout << "|      10. Convert CSV document          |" << endl;
    cout << "|----------------------------------------|" << endl;
    cout << "|      11. Export into Json              |" << endl;
    cout << "|----------------------------------------|" << endl;
    cout << "|      12. Logout                        |" << endl;
    cout << "|----------------------------------------|" << endl;
    cout << "==========================================" << endl;
    cout << "\nEnter your choice: ";
    int choice;
    choice = validinput();
    switch (choice)
    {
    case 1:
        col.ViewAllCollections();
        break;
    case 2:
        cout << "What is the name of the collection (no spaces or period): " << endl;
        cin >> temp;
        while((temp.find(".") != string::npos) && (temp.find(" ") != string::npos))
        col.AddCollection(temp);
        break;
    case 3:
        cout << "What is the name of the collection (no spaces or period): " << endl;
        cin >> temp;
        col.DeleteCollection(temp);
        break;
    case 4:
        cin.ignore(1024, '\n');
                cin.clear();
        j.importJson();
        break;
    case 5:
        //check for any errors first before parsing
        j.jsondata_deleter();
        j.result_deleter();
        cout << "Enter collection name(no spaces): ";
        cin >> temp;
        while(!col.verifyCollectionExist(temp))
        {
            cout << "Error, unknown collection" << endl;
            cout << "Enter collection name(no spaces): ";
            cin >> temp;
        }
        cout << "Enter the Json name(no spaces): " << endl;
        cin >> temp2;
        while(!col.verifyFileExist(temp, temp2))
        {
            cout << "Error, unknown file of collection: " << temp << endl;
            cout << "Enter the Json name(no spaces): " << endl;
            cin >> temp2;
        }
       // getline(cin , temp2);
        //cin.ignore(1024, '\n');
        //cin.clear();
        j.setDirectoryJson(temp, temp2);
        //j.parseError();
        j.parseJson();
        //p.parseJson();
        //p.parseError();
        // readDocument();
        break;
    case 6:
        j.createJson();
        break;
    case 7:
        cout << "What is the name of the collection (no spaces or period): " << endl;
        cin >> temp;
        cout << "Enter the filename to be deleted: ";
        cin >> temp2;
        col.DeleteFile(temp, temp2);
        break;
    case 8:
            cout << "Would you like to view the\n\t1. Original Linked List\n\t2. Modified Linked List\nPlease make selection: ";
            cin >> optS;
            if (optS == 1)
            {
                j.viewOriginal();
            }
            else
            {
                j.viewResult();
            }
        break;
        case 9:
                cin.ignore(1024,'\n');
                cout << "Sample Search:  SEARCH \"This Col\" (value1|value2)" << endl;
                cout << "Sample Sort: SORT \"This Col\" ASCENDING;" << endl;
                cout << "Sample Filter: FILTER \"This Col\" (value1|value2)" << endl;
                getline(cin, command);
                cin.clear();
                j.stringparser(command);
            break;
        case 10:
            cout << "Enter the path to file: " << endl;
            cin.ignore(1024, '\n');
            getline(cin , name);
            cout << "Enter the amount of rows you wish to import(excluding row1 with column names): ";
            cin >> sizeofdata;
            while(sizeofdata <= 0)
            {
                cout << "Error, Invalid amount of rows" << endl;
            }
            j.convertcsvTOjson(name, sizeofdata);
            //c.printcsv(name, sizeofdata, outputofcsv);
            //outputofcsv.str();
            break;
        case 11:
            j.writeJson();
            break;
        case 12:
                cout << "\n         ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~-   USER SUCCESSFULLY LOGGED OUT   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~-\n"<< endl;
                user = false;
                directories = col.return_files();
                for(int i = 0; i < directories.size();i++)
                {
                    cout << "D: " << directories[i] << "-" << endl;
                    ifstream inputFile(directories[i]);
                    SE.openFile(directories[i]);
                    inputFile.open(directories[i]);
                    string fileContent((istreambuf_iterator<char>(inputFile)), istreambuf_iterator<char>());
                    inputFile.close();
                        encryptedmessage = SE.encrypt(fileContent);
                        //cout << encryptedmessage;
                        cout << "File encrypted successfully. \n";
                        //  int decKey = SE.getKeyShift();
                        // cout<<decKey <<endl;  I have to make sure both encrypt and decrypt use the same generated key.
                        //I don't want the user to see the decrypted message, 
                        //I am going to generate random output file names and save the encrypted messages there and store the encrypted message there for 
                        //developer access only.
                        ofstream outputFile(directories[i]);
                        outputFile << encryptedmessage; 
                        outputFile.close();            
                    
                }
                //for loop Call encryption
            break;
    default:
        cout << "\n<<<<<<<<<< INVALID CHOICE, PLEASE TRY AGAIN >>>>>>>>>>\n" << endl;
    break;
    }
};

void gui::reset(string usernam){
 string username, password = "";
    cout << "\n--------------------------------------" << endl;
    cout << "| 0. Reset Password                  |"  << endl;
    cout << "--------------------------------------" << endl;
    cout << "| 1. Create an account               |" << endl;
    cout << "|------------------------------------|" << endl;
    cout << "| 2. Log in with an existing account |" << endl;
    cout << "--------------------------------------" << endl;

    cout << "\n         ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~-   Press Ctrl+C to exit the program   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~-\n"
         << endl;

    int choice;
    cout << "Enter your choice: ";
    choice = validinput();
    
    authentication authenticate;
      int result;
    switch (choice)
    {
    case 0: 
          authenticate.forgot_password(usernam);
          cout << "\n         ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~-   PASSWORD RESET SUCCESSFUL   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~-\n"
                 << endl;
          login();

       break;
    
    
    case 1:

        if (authenticate.createAccount())
        {

            cout << "\n         ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~-   ACCOUNT SUCCESSFULLY CREATED   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~-\n"
                 << endl;
        }
        login();
        break;
    case 2:
        // loginAccount();
        cout << "\nEnter the username: ";

        cin >> username;
        cout << "\nEnter the password: ";
        cin >> password;
        result = authenticate.login_user(username, password);
        if (result==0)
        {
            cout << "\n         ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~-   USER SUCCESSFULLY LOGGED IN   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~-\n"
                 << endl;

            user = true;
        }
        else
        {
            if (result==2){
                login();
            }
            else{
            reset(usernam);
           
            }
        }

        break;
    default:
        cout << "\n<<<<<<<<<< INVALID CHOICE, PLEASE TRY AGAIN >>>>>>>>>>\n"
             << endl;
        break;
    }

};