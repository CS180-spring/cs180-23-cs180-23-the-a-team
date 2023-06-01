#include "gui.h"
#include "authentication.h"

using namespace std;
bool user = false;
void gui::main()
{

    welcome();

    do
    {
        if (!user)
        {

            login();
        }

        if (user)
        {
            welcome();
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
    cout << "\n==========================================" << endl;
    cout << "|      1. List all collections           |" << endl;
    cout << "|----------------------------------------|" << endl;
    cout << "|      2. Read a document                |" << endl;
    cout << "|----------------------------------------|" << endl;
    cout << "|      3. Create a document              |" << endl;
    cout << "|----------------------------------------|" << endl;
    cout << "|      4. Update a document              |" << endl;
    cout << "|----------------------------------------|" << endl;
    cout << "|      5. Delete a document              |" << endl;
    cout << "|----------------------------------------|" << endl;
    cout << "|      6. Query documents                |" << endl;
    cout << "|----------------------------------------|" << endl;
    cout << "|      7. Logout                         |" << endl;
    cout << "==========================================" << endl;
    cout << "\nEnter your choice: ";
    int choice;
    choice = validinput();
    switch (choice)
    {
    case 1:
        // listCollections();
        break;
    case 2:
        // readDocument();
        break;
    case 3:
        // createDocument();
        break;
    case 4:
        // updateDocument();
        break;
    case 5:
        // deleteDocument();
        break;
    case 6:
        // queryDocuments();
        break;
    case 7:
        cout << "\n         ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~-   USER SUCCESSFULLY LOGGED OUT   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~-\n"
             << endl;
        user = false;
        break;
    default:
        cout << "\n<<<<<<<<<< INVALID CHOICE, PLEASE TRY AGAIN >>>>>>>>>>\n"
             << endl;
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