#include "Manager.h"
#include "GraphMethod.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

Manager::Manager()
{
	graph = nullptr;	
	fout.open("log.txt", ios::app);
	load = 0;	//Anything is not loaded
}

Manager::~Manager()
{
	if(load)	//if graph is loaded, delete graph
		delete graph;	
	if(fout.is_open())	//if fout is opened, close file
		fout.close();	//close log.txt File
}

void Manager::run(const char* command_txt)
{
	ifstream fin;	//Command File Input File Stream
	fin.open(command_txt, ios_base::in);//File open with read mode
	
	if(!fin) { //If command File cannot be read, Print error
		fout<<"command file open error"<<endl;
		return;	//Return
	}

	while (!fin.eof()) {
		string str;
		getline(fin, str);		// get line from file
		if (str == "") {		// if line is empty, continue
			if (fin.eof())
				while(!fin.eof())
					getline(fin, str);
					if(str != "")
						continue;
			else
				continue;
		}
		stringstream ss(str);		// make stringstream with str
		string cmd;
		ss >> cmd;		// get command
		string data1;
		int data2, data3;
		if (cmd == "LOAD") {
			ss >> data1;		// get data1
			if (data1[0] == 0)		// if data1 is NULL, print error
				printErrorCode(100);
			else
				if (!LOAD(data1.c_str()))
					printErrorCode(100);		// if LOAD is failed, print error
		}
		else if (cmd == "PRINT") {
			if (load == 0) {		// if graph is not loaded, print error
				printErrorCode(200);
				continue;
			}
			else 
				if (!PRINT())
					printErrorCode(200);		// if PRINT is failed, print error
		}
		else if (cmd == "BFS") {
			if (load == 0) {		// if graph is not loaded, print error
				printErrorCode(300);
				continue;
			}
			ss >> data1 >> data2;		// get data1, data2
			if (data1[0] == 0 || data2 == 0)
				printErrorCode(300);		// if data1 or data2 is NULL, print error
			else
				if (!mBFS(data1[0], data2))
					printErrorCode(300);		// if BFS is failed, print error
		}
		else if (cmd == "DFS") {
			if (load == 0) {		// if graph is not loaded, print error
				printErrorCode(400);
				continue;
			}
			ss >> data1 >> data2;		// get data1, data2
			if (data1[0] == 0 || data2 == 0)
				printErrorCode(400);		// if data1 or data2 is NULL, print error
			else
				if (!mDFS(data1[0], data2))
					printErrorCode(400);		// if DFS is failed, print error
		}
		else if (cmd == "KWANGWOON") {
			if (load == 0) {		// if graph is not loaded, print error
				printErrorCode(500);
				continue;
			}
				if (!mKwangWoon(1))
					printErrorCode(500);		// if KWANGWOON is failed, print error
		}
		else if (cmd == "KRUSKAL") {
			if (load == 0) {		// if graph is not loaded, print error
				printErrorCode(600);
				continue;
			}
			if (!mKRUSKAL())
				printErrorCode(600);		// if KRUSKAL is failed, print error
		}
		else if (cmd == "DIJKSTRA") {
			if (load == 0) {		// if graph is not loaded, print error
				printErrorCode(700);
				continue;
			}
			ss >> data1 >> data2;		// get data1, data2
			if (data1[0] == 0 || data2 == 0)
				printErrorCode(700);		// if data1 or data2 is NULL, print error
			else
				if (!mDIJKSTRA(data1[0], data2))
					printErrorCode(700);		// if DIJKSTRA is failed, print error
		}
		else if (cmd == "BELLMANFORD") {
			if (load == 0) {		// if graph is not loaded, print error
				printErrorCode(800);
				continue;
			}
			ss >> data1 >> data2 >> data3;		// get data1, data2, data3
			if (data1[0] == 0 || data2 == 0 || data3 == 0)
				printErrorCode(800);		// if data1 or data2 or data3 is NULL, print error
			else
				if (!mBELLMANFORD(data1[0], data2, data3))
					printErrorCode(800);		// if BELLMANFORD is failed, print error
		}
		else if (cmd == "FLOYD") {
			if (load == 0) {	// if graph is not loaded, print error
				printErrorCode(900);
				continue;
			}
			ss >> data1;		// get data1
			if (data1[0] == 0)
				printErrorCode(900);		// if data1 is NULL, print error
			else
				if (!mFLOYD(data1[0]))
					printErrorCode(900);		// if FLOYD is failed, print error
		}
		else if (cmd == "EXIT") {
			delete graph;		// delete graph
			if (fin.is_open())
				fin.close();		// close fin file
			if (fout.is_open())
				fout.close();		// close fout file
			break;		// break while loop
		}
		else {
			printErrorCode(1000);		// if command is not exist, print error
		}

	}

	exit(0);		// exit program
	return;
}

bool Manager::LOAD(const char* filename)
{
	ifstream file(filename);		// open file
	int size = 0;		// size of graph
	int from = 0;		// from vertex

	// if file is not opened, Print error
	if (!file.is_open()) {
		return false;		// return false
	}

	// if graph is alread loaded, reload graph
	if (load >= 1) {
		delete graph;		// delete graph
		load = 0;		// set load to 0
	}

	string cmd;
	while (!file.eof()) {
		string str;
		getline(file, str);		// get line from file
		stringstream ss(str);
		string temp;
		ss >> temp;
		if (temp == "")		// if line is empty, continue
			if (file.eof())
				return false;
			else
				continue;
		else if (temp == "L") {
			cmd = temp;
			getline(file, str);
			ss.str(str);
			size = stoi(str);
			graph = new ListGraph(0, size);
				
			if (size == 0) {		// if size is 0, print error
				file.close();		// close file
				return false;		// return false
			}

			break;
		}
		else if (temp == "M") {
			cmd = temp;
			getline(file, str);
			ss.str(str);
			size = stoi(str);
			graph = new MatrixGraph(1, size);
			
			if (size == 0) {		// if size is 0, print error
				file.close();		// close file
				return false;		// return false
			}

			break;
		}
	}

	while (!file.eof()) {
		string str;		// string for getline
		getline(file, str);
		if (cmd == "L") {		// if cmd is L, insert edge to Listgraph
			stringstream ss(str);
			int to = 0;		// to vertex
			int weight = 0;		// weight of edge
			ss >> to >> weight;		// get to and weight
			if (weight != 0 && to != 0) {		// if weight and to is not 0, insert edge to graph
				graph->insertEdge(from - 1, to, weight);		// insert edge to graph
			}
			else {		// if weight or to is 0, set from to to
				from = to;		// set from to to
			}
			
		}
		else if (cmd == "M") {		// if cmd is M, insert edge to Matrixgraph
			stringstream ss(str);
			if (from == size)
				break;
			for (int to = 0; to < size; to++) {
				int weight = 0;		// weight of edge
				ss >> weight;		// get weight
				graph->insertEdge(from, to, weight);		// insert edge to graph
			}
			from++;		// increase from
		}
	}

	fout << "================ LOAD ================" << endl;
	fout << "Success" << endl;
	fout << "======================================" << endl << endl;
	load = 1;		// set load to 1

	file.close();		// close file
	return true;
}

bool Manager::PRINT()
{
	if (load == 0) {		// if graph is not loaded, print error
		return false;		// return false
	}
	else {
		if (graph->printGraph(&fout))		// print graph
			return true;
		else
			return false;
	}
}

bool Manager::mBFS(char option, int vertex)
{
	if (load == 0) {		// if graph is not loaded, print error
		printErrorCode(300);
		return false;		// return false
	}
	else {
		if (BFS(graph, option, vertex))		// run BFS
			return true;
		else
			return false;
	}
}

bool Manager::mDFS(char option, int vertex)
{
	if (load == 0) {		// if graph is not loaded, print error
		printErrorCode(400);
		return false;		// return false
	}
	else {
		if (DFS(graph, option, vertex))		// run DFS
			return true;
		else
			return false;
	}
}

bool Manager::mDIJKSTRA(char option, int vertex)
{
	if (load == 0) {		// if graph is not loaded, print error
		printErrorCode(700);
		return false;		// return false
	}
	else {
		if (Dijkstra(graph, option, vertex))		// run DIJKSTRA
			return true;
		else
			return false;
	}
}

bool Manager::mKRUSKAL()
{
	if (load == 0) {		// if graph is not loaded, print error
		printErrorCode(600);
		return false;		// return false
	}
	else {
		if(Kruskal(graph))		// run KRUSKAL
			return true;
		else
			return false;
	}
}

bool Manager::mBELLMANFORD(char option, int s_vertex, int e_vertex)
{
	if (load == 0) {		// if graph is not loaded, print error
		printErrorCode(800);
		return false;		// return false
	}
	else {
		if(Bellmanford(graph, option, s_vertex, e_vertex))		// run BELLMANFORD
			return true;
		else
			return false;
	}
}

bool Manager::mFLOYD(char option)
{
	if (load == 0) {		// if graph is not loaded, print error
		printErrorCode(900);
		return false;		// return false
	}
	else {
		if(FLOYD(graph, option))		// run FLOYD
			return true;
		else
			return false;
	}
}

bool Manager::mKwangWoon(int vertex)
{
	if (load == 0) {		// if graph is not loaded, print error
		printErrorCode(500);
		return false;		// return false
	}
	else {
		if (KWANGWOON(graph, vertex))		// run KWANGWOON
			return true;
		else
			return false;
	}
}

void Manager::printErrorCode(int n)
{
	fout << "=============== ERROR ===============" << endl;
	fout << n << endl;
	fout << "=====================================" << endl << endl;
}
