#include "graph.h"
#include <iostream>
#include <fstream>

int main()
{
    graphType g;
    g.createGraph("graph.txt");
    std::cout << g.depthFirstTraversal() << std::endl;
    std::cout << g.breadthFirstTraversal() << std::endl;
    std::cout << g.dftAtVertex(6) << std::endl;

    std::ofstream fout("g.txt");
    fout << g.printGraph();
    return 0;
}