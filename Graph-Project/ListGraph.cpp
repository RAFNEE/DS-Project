#include "ListGraph.h"
#include <iostream>
#include <utility>

ListGraph::ListGraph(bool type, int size) : Graph(type, size)
{
    m_List = new map<int, int>[size];       // Definition of m_List
    kw_graph = new vector<int>(size, 0);        // Definition of kw_graph
}

ListGraph::~ListGraph()
{
	delete[] m_List;        // delete m_List
    delete kw_graph;        // delete kw_graph
}

void ListGraph::getAdjacentEdges(int vertex, map<int, int>* m)	 //Definition of getAdjacentEdges(No Direction == Undirected)
{
    for(int i = 0; i < getSize(); i++) {
        auto iter = m_List[i].begin();      // definition of iter
        while(!(iter == m_List[i].end())) {
            if(iter->first == vertex)
                m -> insert(pair<int, int>(i + 1, iter->second));       // Insert to m with vertex of i + 1
            if(i + 1 == vertex) {
                m -> insert(pair<int, int>(iter->first, iter->second));     // insert to m with vertex of iter->first because of undirected graph
            }
            iter++;
        }
    }

}

void ListGraph::getAdjacentEdgesDirect(int vertex, map<int, int>* m)	//Definition of getAdjacentEdges(Directed graph)
{
    auto iter = m_List[vertex - 1].begin();     // definition of iter
    while(!(iter == m_List[vertex - 1].end())) {
        m->insert(pair<int, int>(iter->first, iter->second));       // insert to m with vertex of iter->first
        iter++;     // iter++
    }
}

void ListGraph::insertEdge(int from, int to, int weight) //Definition of insertEdge
{
    m_List[from].insert(make_pair(to, weight));     // insert to m_List with from and to
    kw_graph->at(from) = to + 1;     // insert to kw_graph with from and to
}

bool ListGraph::printGraph(ofstream *fout)	//Definition of print Graph
{
    if (fout->is_open()) {
        *fout << "================ PRINT ================" << endl;
        for (int from = 0; from < m_Size; from++) {
            *fout << "[" << from + 1 << "] -> ";        // print from
            map<int, int>::iterator iter;
            for (iter = m_List[from].begin(); iter != m_List[from].end(); iter++) {
                *fout << "(" << iter->first << ", " << iter->second << ")";     // print to and weight
                auto iter2 = iter;      // iter2 for check next iter
                iter2++;
                // if iter2 is not end, print " -> "
                if ((iter2) != m_List[from].end()) {
                    *fout << " -> ";
                }
                else {
                    continue;
                }
            }
            *fout << endl;
        }
        *fout << "======================================" << endl << endl;
        return true;
    }
    else {
        return false;
    }
}