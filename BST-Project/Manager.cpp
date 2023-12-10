#include "Manager.h"

Manager::Manager()
{
    
}
Manager::~Manager()
{

}

void Manager::run(const char* command)
{
    // Open command & log file
    fcmd.open(command);
    flog.open("log.txt");
    if (!fcmd)
    {
        flog << "Fail to open command file" << endl;
        exit(-1);
    }

    // Run command

    string str;
    string cmd;
    
    // until fcmd is end of file
    while (!fcmd.eof())
    {
        getline(fcmd, str);
        stringstream sstr(str);
        sstr >> cmd;        // similarly string token by stringstream
        if (cmd == "LOAD")
        {
            LOAD();
        }
        else if (cmd == "ADD")
        {
            ADD(str);
        }
        else if (cmd == "QPOP")
        {
            QPOP();
        }
        else if (cmd == "SEARCH")
        {
            SEARCH(str);
        }
        else if (cmd == "PRINT")
        {
            PRINT(str);
        }
        else if (cmd == "DELETE")
        {

        }
        else if (cmd == "EXIT")
        {
            EXIT();
        }
        else
        {
            PrintErrorCode(1000);
        }
    }

    fcmd.close();
    flog.close();
    return;
}

// print success
void Manager::PrintSuccess(const char* cmd)
{
    flog << "===== " << cmd << " =====" << endl;
    flog << "Success" << endl;
    flog << "===============" << endl << endl;
}

// print error
void Manager::PrintErrorCode(int num)
{
    flog << "===== ERROR =====" << endl;
    flog << num << endl;
    flog << "=================" << endl << endl;
}

// calculate expiration date with terms and date
string Manager::ExpirationDate(char terms, string date)
{
    string expirationDate = date;
    int substring[3] = {0, 0, 0};
    string constring;
    stringstream ss(date);
    string token;
    int i = 0;

    // to calculate date with integer
    while (getline(ss, token, '-'))
    {
        substring[i] = stoi(token);
        i++;
    }

    // calculatation cases by terms
    switch (terms)
    {
        case 'A':
            substring[1] = substring[1] + 6;
            if (substring[1] > 12)
            {
                substring[1] = substring[1] % 12;
                substring[0] = substring[0] + 1;
            }
            break;

        case 'B':
            substring[0] = substring[0] + 1;
            break;

        case 'C':
            substring[0] = substring[0] + 2;
            break;

        case 'D':
            substring[0] = substring[0] + 3;
            break;
    }

    // format date in month and day
    if(substring[1]<10 && substring[2]<10)
    {
        expirationDate = to_string(substring[0]) + "-0" + to_string(substring[1]) + "-0" + to_string(substring[2]);
    }
    else if(substring[1]<10 && substring[2]>10)
    {
        expirationDate = to_string(substring[0]) + "-0" + to_string(substring[1]) + "-" + to_string(substring[2]);
    }
    else if(substring[1]>10 && substring[2]<10)
    {
        expirationDate = to_string(substring[0]) + "-" + to_string(substring[1]) + "-0" + to_string(substring[2]);
    }
    else
    {
        expirationDate = to_string(substring[0]) + "-" + to_string(substring[1]) + "-" + to_string(substring[2]);
    }

    return expirationDate;
}


// LOAD
void Manager::LOAD()
{
    ifstream data;
    data.open("data.txt");      // open data file

    //initialize variables
    int cnt = 0;
    string name = "";
    int age = 0;
    string date = "";
    char terms = NULL;
    
    string line;
    while (!data.eof())
    {
        // token every space
        getline(data, line);
        stringstream str(line);
        str >> name >> age >> date >> terms;
        
        if(name == "" && age == 0 && date == "" && terms == NULL)
        {
            continue;
        }
        else if (name == "" || age == 0 || date == "" || terms == NULL)
        {
            PrintErrorCode(100);
            exit(1);
        }

        // push data in queue
        MemQ.push(name, age, date, terms);
        
        if (cnt == 0)
        {
            flog << "=====LOAD=====" << endl;
            cnt++;
        }
        flog << name << "/" << age << "/" << date << "/" << terms << endl;
        
        name = ""; age = 0; date = ""; terms = NULL;
    }
    flog << "==============" << endl << endl;
}

// ADD
void Manager::ADD(string str)
{
    string cmd = "";
    string name = "";
    int age = 0;
    string date = "";
    char terms = NULL;

    stringstream sstr(str);
    
    // token every space
    sstr >> cmd >> name >> age >> date >> terms;
    if (name == "" || age == 0 || date == "" || terms == NULL)
    {
        PrintErrorCode(200);
        exit(1);
    }

    // push data in queue
    MemQ.push(name, age, date, terms);

    flog << "=====ADD=====" << endl;
    flog << name << "/" << age << "/" << date << "/" << terms << endl;
    flog << "=============" << endl << endl;
}
// QPOP
void Manager::QPOP()
{
    if(MemQ.empty())
    {
        PrintErrorCode(300);
        exit(1);
    }

    while (!MemQ.empty())
    {
        MemberQueueNode* node = MemQ.pop();     // return pointer of pop
        
        if (node == nullptr)
        {
            // queue is empty
            break;
        }
        
        // get data in the queue node
        string name = node->getName();
        int age = node->getAge();
        string date = node->getDate();
        char terms = node->getTerms();

        string expiration_date = ExpirationDate(terms, date);       // calculate expiration date
        
        // insert data in each class
        TermL.insert(terms);
        TermB.insert(name, age, date, expiration_date);
        NameB.insert(name, age, date, expiration_date, terms);
    }
    PrintSuccess("QPOP");
}

// SEARCH
void Manager::SEARCH(string n)
{
    string str = "";
    string cmd = "";

    // token command and string
    stringstream ss(n);
    ss >> cmd >> str;

    if(NameB.search(str) == nullptr)
    {
        PrintErrorCode(400);
        exit(1);
    }

    // search data
    NameBSTNode* node = NameB.search(str);
    
    // get data in node
    string name = node->getName();
    int age = node->getAge();
    string date = node->getDate();
    string exd = node->getExpireDate();

    // note data in log
    flog << "=====SEARCH=====" << endl;
    flog << name << "/" << age << "/" << date << "/" << exd << endl;
    flog << "================" << endl << endl;

}

// PRINT
void Manager::PRINT(string str)
{
    string cmd = "";
    string type = "";
    stringstream ss(str);
    ss >> str >> type;
    
    if(type == "A" || type == "B" || type == "C" || type == "D")
    {
        char terms = type[0];
        TermsListNode* node = TermL.search(terms);
        if (node)
        {
            TermsBST* bst = node->getBST();
            // if BST is found
            if (bst)
            {
                // print data sorted by terms
                flog << "=====PRINT=====" << endl << "Term_BST " << terms << endl << endl;
                bst->print(flog);
                flog << "===============" << endl << endl;
            } 
            else
            {
                PrintErrorCode(500); // BST is not found
            }
        }
    }
    else if (type == "NAME")
    {
        if(NameB.getRoot() == nullptr)
        {
            PrintErrorCode(500);
        }
        // print data sorted by name
        flog << "=====PRINT=====" << endl << "Name_BST" << endl << endl;
        NameB.print(flog);
        flog << "===============" << endl << endl;
    }
}
// DELETE

void Manager::EXIT()
{
    PrintSuccess("EXIT");
    exit(1);
}