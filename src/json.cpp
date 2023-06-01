#include "json.h"

using namespace std;

Json::Json(string cname, string jname)
{
    collectionName = cname;
    if(verifyCollectionExist(cname)) //parent function
    {
        setDirectoryJson(cname, jname);
    }
    else
    {
        AddCollection(cname); //parent function
        setDirectoryJson(cname, jname);
    }
    
}

void Json::setfullDirectory(string n)
{
    directory = n;
}

void Json::setDirectoryJson(string cname, string jname)
{
    collectionName = cname;
    if( verifyCollectionExist(cname)) //parent function
    {
        directory = "Database/" + cname + "/" + jname;
    }
    else
    {
        AddCollection(cname); //parent function
        directory = "Database/" + cname + "/" + jname;
    }
    cout << "Directory Successful: " << directory << endl;
    //check if directory already exists
}

//Below is test function for hard coded data
/*
//try to use rapidjson
void Json::writeJson() {
     struct Person {
        string id;
        string name;
        int age;
        string college;
    };

    vector<Person> people = {
        {"9873e87e879ueid", "Farnaz", 23, "UC Riverside"},
        {"98e89r8983009id", "Golnaz", 27, "UC Berkely"},
        {"9898378747382id", "Niloofar", 30, "UCLA"},
        {"959067fs9d798id", "Muneeb", 23, "UC Riverside"}
    };
    string filename = "output.json";
    
    ofstream outputFile(filename);
    if (outputFile.is_open()) {
        outputFile << "{\n\t\"people\": [";
        for (size_t i = 0; i < people.size(); ++i) {
            if (i != 0) {
                outputFile << ", ";
            }
            outputFile << "{\n\t\t\"id\": \"" << people[i].id << "\",\n";
            outputFile << "\t\t\"name\": \"" << people[i].name << "\",\n";
            outputFile << "\t\t\"age\": " << people[i].age << ",\n";
            outputFile << "\t\t\"college\": \"" << people[i].college << "\"\n\t}";
        }
        outputFile << "]\n}";
        outputFile.close();
    }
}
*/

//new exportJson 
void Json::writeJson() {
    //vector<pair<string, string>> v = jsondata->get(0);
    //string columns[v.size()];

    ofstream outfile(directory);
    string start = "[\n";
    outfile << start;
    string data;
    for (int k = 0; k < jsondata->size(); k++)
    {
        vector<pair<string, string>> temp = jsondata->get(k);
        data = "{\n";
        for (int j = 0; j < temp.size(); j++)
        {
            data += "\t\"" + temp[j].first + "\": \"" +  temp[j].second + "\"";
            if (j != temp.size() - 1) 
            {
                data += ",\n";
            }
            else 
            {
                data += "\n";
            }
        }
        // data += "  \"id\": \"" + id + "\",\n";
        // data += "  \"Name\": \"" + name + "\",\n";
        // data += "  \"Age\": " + to_string(age) + ",\n";
        // data += "  \"College\": \"" + college + "\"\n";
        if (k != jsondata->size() - 1) { data += "},\n"; }
        else { data += "}\n"; }
        outfile << data;
    }
    string end = "]\n";
    outfile << end;
    outfile.close();
}

void Json::createJson() {
    int entryCount = 0;
    int attributeCount = 0;
    string temp;
    string temp2;
    vector<string> atribList;
    vector<pair <string,string>> v;
    pair<string, string> p;

    cout << "How many entries of data: ";
    cin >> entryCount;
    while(!intChecker(entryCount)){
        cout << "Error: Number has to be greater than 0" << endl;
        cout << "How many entires of data: ";
        cin >> entryCount;
    }
    cout << "How many attributes per entry: ";
    cin >> attributeCount;
    while(!intChecker(attributeCount)){
        cout << "Error: Number has to be greater than 0" << endl;
        cout << "How many entires of data: ";
        cin >> attributeCount;
    }


    cin.ignore(10000, '\n');
    cin.clear();
    for(int i = 1; i <= attributeCount; i++){
        cout << "Enter " << i << " attribute" << endl;
        getline(cin, temp);
        atribList.push_back(temp);
        temp = "";
        
    }
    cout << "0";
    for(int i = 0; i < entryCount; i++){
        cout << "1";
        
        for(int j = 0; j < attributeCount; j++){
            p.first = atribList[j];
            cout << "Enter " << i << " entry Attribute: " << atribList[j] << "'s value" << endl;
            getline(cin, temp);
            p.second = temp;
            v.push_back(p);
        }

        jsondata->insertToRear(v);
        v.clear();
    }
    cout << "Enter collection name: ";
    cin >> temp;
    while(!verifyCollectionExist(temp)){
        cout << "Error: Collection does not exist" << endl;
        cout << "Enter collection name: ";
        cin >> temp;
    }
    cout << "Enter file name: ";
    cin >> temp2;
    temp2 = jsonValidator(temp, temp2);
    
    directory = "Database/" + temp + "/" + temp2;
    cout << directory;
    writeJson();
}

bool Json::intChecker(int value){
    if (value > 0)
        return true;
    else
        return false;
}

bool Json::jsonChecker(string value){

    int counter = 0;

    for(int i = 0; i < value.size(); i++){
        if (value[i] == '.'){
            counter++;
        }
    }

    if (value.length() > 5 && value.substr(value.length() - 5) == ".json" && value.find(".json") != string::npos && counter == 1) {
        return true;
    }
    else 
        return false;
}



void Json::intiializeEMPTYjson(string collectionname, string jsonname)
{
    directory = "Database/" + collectionname + jsonname;
    file.open(directory);
    file.close();
}

//Parser could go under here
void Json::importJson()
{
    //Add string manipulation for getting name automatically
    string d,d2,d3;
    cout << "Please write the path of your input Json: " << endl;
    getline(cin, d);
    cout << "Please enter target collection name(no spaces): ";
    cin >> d2;
    while(!verifyCollectionExist(d2)){
        cout << "Error: Collection does not exist" << endl;
        cout << "Please enter target collection name(no spaces): ";
        cin >> d2;
    }

    cout << "Enter in name of json to be created(no spaces): ";
    cin >> d3;
    jsonValidator(d2, d3);

    setDirectoryJson(d2,d3);
    file.open(d);
    ifstream  From(d, ios::binary);
    ofstream  To(directory, ios::binary);
    To << From.rdbuf();
    
}

string Json::jsonValidator(string col, string temp2){
    bool flag = false;
        do
        {
            while(!jsonChecker(temp2)){
                cout << "Error: File needs to be .json (do not include extra periods)" << endl;
                cout << "Enter file name: ";
                cin >> temp2;
            }
            while (verifyFileExist(col, temp2)){
                cout << "Error: This file already exists" << endl;
                cout << "Enter file name: ";
                cin >> temp2;
            }

            if (verifyFileExist(col, temp2) == false && jsonChecker(temp2)){
                flag = true;
            }
        } while(flag == false);

        return temp2;
}

void Json::view(LinkedList* list)
{
    int choice, viewcount, editchoice;
    int counter = 0;
    vector<pair<string, string>> show;
    cout << "Enter how many entries would you like to view per page (greater than 0): " << endl;
    cin >> viewcount;
    while(viewcount <= 0)
    {
        cout << "Invalid, Please Try Again " << endl;
        cout << "Enter how many entries would you like to view per page (greater than 0): " << endl;
        cin >> viewcount;
    }
    cout << "Use number 1 to 3 to control viewer" << endl;
    cout << "1. Edit" << endl;
    cout << "2. Previous" << endl;
    cout << "3. Next" << endl;
    cout << "99. Exit Viewer" << endl;
    do
    {
        //Show the Node
        for (int c = counter; c < viewcount; c++)
        {
            if(list->size() > c)
            {
                show = list->get(c);
                cout<< c << ". ";
                for(int i = 0; i < show.size() ; i++)
                {
                    cout << "'" << show[i].first << "' : " << show[i].second << endl;
                } 
            }
            
        }
        
        cin >> choice;
        switch(choice)
        {
            case 1:
                cout << "Enter the number associated with the entry you would like to edit" << endl;
                cin >> editchoice;
                show = edit(show);
                list->set(show, editchoice);
                break;
            case 2:
                counter -= viewcount;
                if(counter < 1)
                {
                    counter = 0;
                }
                show.clear();
                //go to previous node
                break;
            case 3:
                if((counter += viewcount) >= list->size())
                {
                    counter += viewcount;
                    show.clear();  
                }
                else
                {
                    cout << "End of List" << endl;
                }
                
                //go to next node
                break;
            case 99:
                break;
            default:    cout << "Error: Invalid option" << endl;
                        cout << "Use number 1 to 3 to control viewer" << endl;
                        cout << "1. Edit" << endl;
                        cout << "2. Previous" << endl;
                        cout << "3. Next" << endl;
                        cout << "99. Exit Viewer" << endl;
                break;
        }
        
    } while (choice != 99);
    
}

vector<pair<string, string>> Json::edit(vector<pair<string, string>> &show)
{
    int choice;
    cout << "Enter the number of which attribute, would you like to edit" << endl;
    for(int i = 0; i < show.size(); i++)
    {
        cout << i << ". " << show[i].first << endl;
    }
    cin >> choice;
    while((choice < 0) || (choice >= show.size()))
    {
        cout <<"Invalid option, Try Again!" << endl;
        cout << "Enter the number of which attribute, would you like to edit" << endl;
        for(int i = 0; i < show.size(); i++)
        {
            cout << i << ". " << show[i].first << endl;
        }
        cin >> choice;
    }
    cout << "Enter the new value for this attribute(" << show[choice].first << "): " ;
    cin >> show[choice].second; //later should be getline
    return show;
}

/*
void Json::writeJson() {

    cout << "here";
    string id = "7343d87e623urfd";
    string name = "Muneeb";
    int age = 23;
    string college = "UC Riverside";

    string data = "{\n";
    data += "  \"id\": \"" + id + "\",\n";
    data += "  \"Name\": \"" + name + "\",\n";
    data += "  \"Age\": " + to_string(age) + ",\n";
    data += "  \"College\": \"" + college + "\"\n";
    data += "}\n";

    ofstream outfile("out.json");
    outfile << data;
    outfile.close();

    cout << "\nfinal\n";
}
*/
void Json::parseError()
{
     //handle parsing error
    ifstream file("data.json");
    IStreamWrapper isw(file);
    Document document;
    document.ParseStream(isw);
    if (document.HasParseError()) {
        cout << "Following errors were found: \n" ;
        fprintf(stderr, "\nError(offset %u): %s\n",
        (unsigned)document.GetErrorOffset(),
        GetParseError_En(document.GetParseError()));
    }else{
        cout<<"No errors were found while parsing the file\n";
    }

}
void Json::parseJson()
{
    ifstream file(directory);   
    IStreamWrapper isw(file);
    cout << endl << "RealDirectory: " << directory << endl;
    Document doc;
    doc.ParseStream(isw);
    vector<pair<string, string>> information;
    //struct pairofjson s;
    if (!doc.IsArray()) {
        cout << "Document must be an array" << endl;
    }
    for (auto& itr : doc.GetArray()) {
            for (auto& obj : itr.GetObject()) {
                pair t = make_pair(string(obj.name.GetString()),string(obj.value.GetString()));
                information.push_back(t);
                //jsondata->insertToRear();
                /*
                pair.Jsonkey = obj.name.GetString();
                pair.Jsonval = obj.value.GetString();
                //information.push_back(pair);
                */
            }
        }
    
    string firstentry = information[0].first;
    vector<pair< string, string>> result;
    for(int i = 0; i < information.size(); i++)
    {
        if(information[i].first == firstentry && i != 0)
        {
            jsondata->insertToRear(result);
            result.clear();
        }

        result.push_back(information[i]);
    }
    jsondata->insertToRear(result);
    cout << "Size of LinkedList:" << jsondata->size() << endl;
    view(jsondata);
    /*
    for(const auto& p: information) {
        cout << p.Jsonkey << " : " << p.Jsonval << endl;
    }
    */
}

void Json::searchFunc( string searchby, vector<string> match)
{
    LinkedList* result;
    vector<pair<string, string>> v = jsondata->get(0);
    int findattributeindex;
    for(int i = 0; i < v.size(); i++)
    {
        if(searchby == v[i].first)
        {
            findattributeindex = i;
            for(int j = 0; j < match.size(); j++)
            {
                if( match[0] == v[findattributeindex].second)
                {
                    result->insertToRear(jsondata->get(0));
                }
            }
            
            break;
        }
    }
    cout << "Found attrib:" << v[findattributeindex].first << endl;
    cout << "Match:" << match[0] <<";" << endl;
    cout << "Size: " << jsondata->size() << endl;
    //v.clear();
    for(int i = 0; i < jsondata->size(); i++)
    {
        v = jsondata->get(i);
   
       // for(int j = 0; j < match.size(); j++)
        //{
            if( match[0] == v[findattributeindex].second)
            {
            
                for (int i = 0; i < v.size(); i++)
                {
                    cout << v[i].first << " "<< v[i].second << endl;
                }
                //result->insertToRear(jsondata->get(i));
            
            }
       // }
        
    }

   //view(result);

}

void Json::sortFunc(string attrib, int option)
{
    LinkedList* result = jsondata->sortList(attrib, option);
    result->printList();
}

void Json::filterFunc( string searchby, vector<string> match)
{
    LinkedList* result;
    vector<pair<string, string>> v = jsondata->get(0);
    int findattributeindex;
    for(int i = 0; i < v.size(); i++)
    {
        if(searchby == v[i].first)
        {
            findattributeindex = i;
            // for(int j = 0; j < match.size(); j++)
            // {
            //     if( match[0] == v[findattributeindex].second)
            //     {
            //         result->insertToRear(jsondata->get(0));
            //     }
            // }
            
            break;
        }
    }

    v.clear();
    for(int i = 0; i < jsondata->size(); i++)
    {
        v = jsondata->get(i);
   
       // for(int j = 0; j < match.size(); j++)
        //{
            if( match[0] != v[findattributeindex].second)
            {
            
                for (int i = 0; i < v.size(); i++)
                {
                    cout << v[i].first << " " << v[i].second << endl;
                }
                //result->insertToRear(jsondata->get(i));
            
            }
       // }
        
    }

   //view(result);

}


void Json::stringparser(string command)
{
    cout << "command:" << command << endl;
    deleteChars(command, ' ');

    //Grab first keyword that will be until next space
    vector<string> values;    
    int index = command.find(' ');
    string temp= command.substr(0,index);
    string attrib, value;
    int choice = 0, sortoption;
    if(temp == "SEARCH")
    {
        choice = 1;
        command.erase(command.begin(), command.begin() + index); //delete keyword
        //deleteChars(command, ' ');
        deleteChars(command, '"'); //Delete 1st quotattion symbol
        index = command.find('"');     
        temp = command.substr(0,index);
        attrib = temp; 
        cout << "Attrib:" << attrib << endl;
        command.erase(command.begin(), command.begin() + index + 1);
        deleteChars(command, ' ');
        deleteChars(command, '(');
        index = command.find(')');
        value = command.substr(0,index);
        command.erase(command.begin(), command.begin() + index + 1);
        if((value.find('|') != string::npos) || (value.length() != 0))
        {
            index = value.find('|');
            temp = value.substr(0,index);
            values.push_back(temp);
            value.erase(0,index+1);
        }
        cout << "Here1" << endl;
        if(value.find("|") == string::npos)
        {
            index = value.find(')');
            temp = value.substr(0 ,index);
            values.push_back(temp);
            temp = "";
        }
      
    }
    if(temp == "SORT") 
    {
        choice = 2;
        command.erase(command.begin(), command.begin() + index); //delete keyword
        deleteChars(command, ' ');
        deleteChars(command, '"'); //Delete 1st quotattion symbol
        index = command.find('"');
        temp = command.substr(0,index);
        attrib = temp;
        command.erase(command.begin(), command.begin() + index + 1);
        deleteChars(command, ' ');
        index = command.find(';');
        temp = command.substr(0,index);
        transform(temp.begin(), temp.end(), temp.begin(), ::toupper);
        cout << "Attrib: " << attrib << " temp: " << temp << endl;
        if (temp == "ASCENDING")
        {
            sortoption = 1;
        }
        else if (temp == "DESCENDING")
        {
            sortoption = 2;
        }
    }
    if(temp == "FILTER")
    {
        choice = 3;
        command.erase(command.begin(), command.begin() + index); //delete keyword
        deleteChars(command, ' ');
        deleteChars(command, '"'); //Delete 1st quotattion symbol
        index = command.find('"');     
        temp = command.substr(0,index);
        attrib = temp; 
        cout << "Attrib:" << attrib << endl;
        command.erase(command.begin(), command.begin() + index + 1);
        deleteChars(command, ' ');
        deleteChars(command, '(');
        index = command.find(')');
        value = command.substr(0,index);
        command.erase(command.begin(), command.begin() + index + 1);
        if((value.find('|') != string::npos) || (value.length() != 0))
        {
            index = value.find('|');
            temp = value.substr(0,index);
            values.push_back(temp);
            value.erase(0,index+1);
        }
        if(value.find("|") == string::npos)
        {
            index = value.find(')');
            temp = value.substr(0 ,index);
            values.push_back(temp);
            temp = "";
        }
      
    }
   switch (choice)
   {
        case 1: 
                searchFunc(attrib, values);
                cin.clear();
                //view(result);
            break;
        case 2: //jsondata = jsondata->sortList(attrib, sortoption);
                sortFunc(attrib, sortoption);

                //view(jsondata);
            break;
        case 3:
                filterFunc(attrib, values);
                cin.clear();
        default:
            break;
   }
    
}


void Json::deleteChars(string &command, char t)
{
    //Delete first spaces
    while(command[0] == t)
    {
        command.erase(command.begin());
    }
}

void Json::viewOriginal()
{
    view(jsondata);
}

void Json::viewResult()
{
    view(jsondata);
}

void Json::RevertResult()
{
    result = jsondata;
    viewResult();
}


