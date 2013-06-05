#ifndef GRAPH_H
#define GRAPH_H
#include <vector>
#include <stack>
#include <fstream>
#include <iostream>

class Graph
{
public:
    Graph();
    bool topological_sort();
    bool dfs(unsigned int v);
    bool init();
    void print();
private:
    std::vector <unsigned int> Color;                  // — массив, в котором хранятся цвета вершин (0 — белый, 1 — серый, 2 — черный).
    unsigned int N;                                    // — количество вершин.
    std::vector <std::vector <unsigned int>* > Edges;     // — массив списков смежных вершин.
    std::vector <unsigned int> Numbers;                // — массив, в котором сохраняются новые номера вершин.
    std::stack <unsigned int> Stack;                   // — стек, в котором складываются вершины после их обработки.
};

#endif // GRAPH_H
