#include "Manager.h"

void Manager::run(const char* command) 
{
	fin.open(command);
	flog.open("log.txt", ios::app);
	if(!fin)
	{
		flog << "File Open Error" << endl;
		return;
	}
	while (!fin.eof())
	{
		char* cmd1 = new char[256];		// set cmd1
		fin.getline(cmd1, 256);		// get cmd1
		// if cmd1 is empty, continue
		if (strcmp(cmd1, "") == 0)
			continue;
		char *tok, *name, *codestr, *author, *yearstr, *countstr;		// set tok, name, codestr, author, yearstr, countstr to store token
		tok = strtok(cmd1, "\t");		// get token

		// if tok is LOAD
		if (strcmp(tok, "LOAD") == 0)
		{
			// if bptree is not empty, print error code
			if (bptree->getRoot() != nullptr) {
				printErrorCode(100);
			}
			else {
				if(LOAD())
					printSuccessCode(tok);		// if LOAD is success, print success code
				else
					printErrorCode(100);		// if LOAD is fail, print error code
			}
			
		}
		// if tok is ADD
		else if (strcmp(tok, "ADD") == 0)
		{
			// get name, codestr, author, yearstr
			name = strtok(NULL, "\t");
			codestr = strtok(NULL, "\t");
			author = strtok(NULL, "\t");
			yearstr = strtok(NULL, "\t");

			// if name, codestr, author, yearstr is NULL, print error code
			if (name == NULL || codestr == NULL || author == NULL || yearstr == NULL) {
				printErrorCode(200);
				continue;
			}
			else {
				// if name exists, get countstr
				int code = atoi(codestr);
				int year = atoi(yearstr);

				// if ADD is success, print addition
				if (ADD(name, code, author, year)) {
					flog << "==========" << tok << "==========" << endl;
					flog << name << "/" << codestr << "/" << author << "/" << year << endl;
					flog << "=======================" << endl << endl;
				}
				else
					printErrorCode(200);		// if ADD is fail, print error code
			}
		}
		// if tok is SEARCH_BP
		else if (strcmp(tok, "SEARCH_BP") == 0) {
			name = strtok(NULL, "\t");		// get name
			
			// if name is NULL, print error code
			if (name == NULL) {
				printErrorCode(300);
				continue;
			}
			else {
				char* namerange = strtok(NULL, "\t");		// get namerange
				// if name exists and namerange is NULL, search book
				if (name != NULL && namerange == NULL) {
					if (SEARCH_BP_BOOK(name))
						continue;		// if SEARCH_BP is success, continue
					else
						printErrorCode(300);		// if SEARCH_BP is fail, print error code
				}
				else {
					if (SEARCH_BP_RANGE(name, namerange))
						continue;		// if SEARCH_BP is success, continue
					else
						printErrorCode(300);		// if SEARCH_BP is fail, print error code
				}
			}
		}
		// if tok is PRINT_BP
		else if(strcmp(tok, "PRINT_BP") == 0) {
			if (PRINT_BP())
				continue;		// if PRINT_BP is success, continue
			else printErrorCode(400);
		}
		// if tok is PRINT_ST
		else if (strcmp(tok, "PRINT_ST") == 0) {
			codestr = strtok(NULL, "\t");		// get code
			if (codestr == NULL) {
				printErrorCode(500);		// if code is NULL, print error code
				continue;
			}
			int code = atoi(codestr);		// convert codestr to integer
			printErrorCode(500);
			continue;
		}
		// if tok is DELETE
		else if (strcmp(tok, "DELETE") == 0) {
			printErrorCode(600);
			continue;
		}
		// if tok is EXIT
		else if (strcmp(tok, "EXIT") == 0) {
			printSuccessCode(tok);		// if EXIT is success, print success code
			fin.close();		// close fin
			flog.close();		// close flog
			delete[] cmd1;
			exit(0);		// exit
		}
		else {
			printErrorCode(700);
		}
	}
	return;
}

bool Manager::LOAD()
{
	ifstream inFile;		// set inFile
	inFile.open("loan_book.txt");
	// if inFile does not exist, print error code
    if (!inFile) {
        printErrorCode(100);
        return false;
    }

	// repeat until inFile is empty
    while (!inFile.eof()) {
        inFile.getline(cmd, 256);		// get cmd
		// if cmd is empty, break
		if (strcmp(cmd, "") == 0)
			break;

        char *name, *codestr, *author, *yearstr, *countstr;		// set name, codestr, author, yearstr, countstr to store token
		int code, year, count;		// set code, year, count to store integer

		// get name, codestr, author, yearstr, countstr
        name = strtok(cmd, "\t");
		codestr = strtok(NULL, "\t");
		author = strtok(NULL, "\t");
		yearstr = strtok(NULL, "\t");
		countstr = strtok(NULL, "\t");

		// convert codestr, yearstr, countstr to integer
		code = atoi(codestr);
		year = atoi(yearstr);
		count = atoi(countstr);
		
		LoanBookData* bookData = new LoanBookData();		// create the new bookData
		bookData->setBookData(name, code, author, year, count);		// set bookData
		bptree->Insert(bookData);		// insert bookData to bptree
    }
    inFile.close();		// close inFile
    return true;
}

bool Manager::ADD(string name, int code, string author, int year)
{
	LoanBookData* bookData = new LoanBookData();		// create the new bookData
	// if name does not exist, set bookData
	if (bptree->searchDataNode(name) == nullptr) {
		bookData->setBookData(name, code, author, year, 0);
	}
	else {
		// if name exists, get bookData
		bookData->setName(name);
		bookData->setCode(code);
		bookData->setAuthor(author);
		bookData->setYear(year);
		bookData->updateCount();
	}
	// insert bookData to stree if loan_count is over in each code
	switch (bookData->getCode() % 100) {
	case 0:
		if (bookData->getLoanCount() == 3) {
			stree->Insert(bookData);
		}
		break;
	case 1:
		if (bookData->getLoanCount() == 3) {
			stree->Insert(bookData);
		}
		break;
	case 2:
		if (bookData->getLoanCount() == 3) {
			stree->Insert(bookData);
		}
		break;
	case 3:
		if (bookData->getLoanCount() == 4) {
			stree->Insert(bookData);
		}
		break;
	case 4:
		if (bookData->getLoanCount() == 4) {
			stree->Insert(bookData);
		}
		break;
	case 5:
		if (bookData->getLoanCount() == 2) {
			stree->Insert(bookData);
		}
		break;
	case 6:
		if (bookData->getLoanCount() == 2) {
			stree->Insert(bookData);
		}
		break;
	case 7:
		if (bookData->getLoanCount() == 2) {
			stree->Insert(bookData);
		}
		break;
	default:
		bptree->Insert(bookData);		// insert bookData to bptree
	}
	
	return true;
}

bool Manager::SEARCH_BP_BOOK(string book) {
	// if book exists, print book
    if (bptree->searchBook(book)) {
        BpTreeNode* node = bptree->searchDataNode(book);		// get node
        BpTreeNode* dataNode = node;		// set dataNode

		// if dataNode is not empty and dataNode is not empty, search boot
        if (dataNode != nullptr && !dataNode->getDataMap()->empty()) {
            auto iter = dataNode->getDataMap()->find(book);		// set iter

			// get name, codestr, author, year, count
			string name = iter->second->getName();
			int code = iter->second->getCode();
			string author = iter->second->getAuthor();
			int year = iter->second->getYear();
			int count = iter->second->getLoanCount();
			string codestr;
			if (code == 0) {
				codestr = "000";
			}
			else {
				codestr = to_string(code);
			}

			// store bookdata in log.txt
            if (iter != dataNode->getDataMap()->end()) {
                flog << "========SEARCH_BP========" << endl;
                flog << name << "/" << codestr << "/" << author << "/" << year << "/" << count << endl;
                flog << "=========================" << endl << endl;
                return true;
            }
        }
    }
	return false;
}


bool Manager::SEARCH_BP_RANGE(string start, string end) {
	flog << "========SEARCH_BP========" << endl;
	// if searchRange is success, return true
	if (bptree->searchRange(start, end, flog)) {
		flog << "=========================" << endl << endl;
		return true;
	}
	else {
		printErrorCode(300);		// if searchRange is fail, print error code
	}
	flog << "=========================" << endl << endl;
	return false;
}


bool Manager::PRINT_BP() 
{
	flog << "========PRINT_BP========" << endl;
	BpTreeNode* pCur = bptree->getRoot();		// get pCur from bptree root
	if (pCur == nullptr) return false;		// if pCur is empty, return false

	// repeat until pCur is leaf node
	while (pCur->getMostLeftChild() != nullptr) {
		pCur = pCur->getMostLeftChild();
	}

	// repeat until next of pCur is null
	while (pCur->getNext() != nullptr) {
		auto pData = pCur->getDataMap()->begin();		// set pData

		// repeat until pData is end
		while (pData != pCur->getDataMap()->end()) {
			string name, codestr, author;
			int code, year;

			// get name, codestr, author, year
			name = pData->second->getName();
			code = pData->second->getCode();
			author = pData->second->getAuthor();
			year = pData->second->getYear();

			if (code == 0) codestr = "000";		// if code is 0, set codestr as 000
			else codestr = to_string(code);		// else set codestr as code

			flog << name << "/" << codestr << "/" << author << "/" << year << endl;		// print bookdata in log.txt
			pData++;		// increase pData
		}
		pCur = pCur->getNext();		// move to the next node
	}
	flog << "========================" << endl << endl;

	return true;
}

bool Manager::PRINT_ST() 
{
	return true;
}

bool Manager::DELETE() 
{
	return true;
}

void Manager::printErrorCode(int n) {				//ERROR CODE PRINT
	flog << "==========" << "ERROR" << "==========" << endl;
	flog << n << endl;
	flog << "=========================" << endl << endl;
}

void Manager::printSuccessCode(string cmd) {//SUCCESS CODE PRINT 
	string base = "==========";
    
    string line = base + cmd + base;

    // Print the formatted output
    flog << line << endl;
    flog << "Success" << endl;
    flog << string(line.length(), '=') << endl << endl;
}

