#pragma once
#include "MemberQueue.h"
#include "TermsList.h"
#include "TermsBST.h"
#include "NameBST.h"
#include <fstream>
#include <string>
#include <sstream>
#include <cstring>

using namespace std;

class Manager
{
private:

	ifstream fcmd;
	ofstream flog;

	MemberQueue MemQ;
	TermsList TermL;
	TermsBST TermB;
	NameBST NameB;


public:
	Manager();
	~Manager();

	void run(const char* command);
	
	void PrintSuccess(const char* cmd);
	void PrintErrorCode(int num);

	string ExpirationDate(char terms, string date);

	// LOAD
	void LOAD();
	// ADD
	void ADD(string str);
	// QPOP
	void QPOP();
	// SEARCH
	void SEARCH(string name);
	// PRINT
	void PRINT(string str);
	// DELETE

	void EXIT();
};
