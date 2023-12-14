#include "MatrixGraph.h"
#include <iostream>
#include <vector>
#include <string>

MatrixGraph::MatrixGraph(bool type, int size) : Graph(type, size)
{
    m_Mat = new int*[size];
    for (int i = 0; i < size; i++) {
        m_Mat[i] = new int[size];
    }
}

MatrixGraph::~MatrixGraph()
{
    for (int i = 0; i < m_Size; i++) {
        delete[] m_Mat[i];      // delete m_Mat[i]
    }
    delete[] m_Mat;     // delete m_Mat
}

void MatrixGraph::getAdjacentEdges(int vertex, map<int, int>* m)
{	
    for(int i = 0; i < getSize(); i++) {
        if(m_Mat[vertex - 1][i] != 0) {
            m->insert(pair<int, int>(i + 1, m_Mat[vertex - 1][i]));     // insert to m with vertex of vertex - 1
        }
    }
    for(int i = 0; i < getSize(); i++) {
        if(m_Mat[i][vertex - 1] != 0) {
            m->insert(pair<int, int>(i + 1, m_Mat[i][vertex - 1]));     // insert to m with vertex of i + 1 because of undirected graph
        }
    }
}

void MatrixGraph::getAdjacentEdgesDirect(int vertex, map<int, int>* m)
{
    for(int i = 0; i < getSize(); i++) {
        if(m_Mat[vertex - 1][i] != 0) {
            m->insert(pair<int, int>(i + 1, m_Mat[vertex - 1][i]));     // insert to m with vertex of vertex - 1
        }
    }
}

void MatrixGraph::insertEdge(int from, int to, int weight)
{
    m_Mat[from][to] = weight;       // insert to m_Mat with from and to
}

bool MatrixGraph::printGraph(ofstream *fout)
{
    if(fout->is_open()) {
        *fout << "================ PRINT ================" << endl;
        *fout << "\t  ";
        for (int to = 0; to < m_Size; to++) {
            *fout << " [" << to + 1 << "] ";        // print to with column
        }
        *fout << endl;
        for (int from = 0; from < m_Size; from++) {
            if (from < 9)
                *fout << "[" << from + 1 << "]\t\t";       // print from with row
            else
                *fout << "[" << from + 1 << "]\t";       // print from with row
            for (int to = 0; to < m_Size; to++) {
                if (to < 9)
                    *fout << m_Mat[from][to] << "    ";     // print weight
                else
                    *fout << m_Mat[from][to] << "     ";     // print weight
            }
            *fout << endl;
        }
        *fout << "======================================" << endl << endl;
    }
}
