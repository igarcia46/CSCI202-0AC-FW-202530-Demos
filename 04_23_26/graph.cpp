#include "graph.h"
// graph viz online https://dreampuf.github.io/GraphvizOnline/

std::regex graphType::nameRegex{R"([[:alpha:]]+\s[[:alpha:]]+)"};

graphType::graphType(int size)
{
    if (size >= 0)
    {
        maxSize = size;
    }
    else
    {
        maxSize = 0;
    }
    if (maxSize > 0)
    {
        graph.resize(maxSize);
    }
}

graphType::graphType(const graphType &graphToCopy)
{
    maxSize = 0;
    copyGraph(graphToCopy);
}

graphType::~graphType()
{
    clearGraph();
}

const graphType &graphType::operator=(const graphType &graphToCopy)
{
    if (this != &graphToCopy)
    {
        copyGraph(graphToCopy);
    }
    return *this;
}

bool graphType::isEmpty() const
{
    return graph.empty();
}

void graphType::createGraph(std::string filename)
{
    std::ifstream fin(filename);
    int index = 0;
    int vertex = 0;
    int adjcentVertex = 0;
    if (!isEmpty())
    {
        clearGraph();
    }
    if (!fin.is_open())
    {
        throw std::runtime_error("Cannot open input file");
    }
    while (!fin.eof())
    {
        std::string name;
        getline(fin, name);
        if (std::regex_match(name, nameRegex))
        {
            names.push_back(name);
        }
        else
        {
            if (maxSize < name.size())
            {
                maxSize = name.size();
                graph.resize(maxSize);
            }
            std::istringstream sin(name);
            sin >> vertex;
            sin >> adjcentVertex;
            while (adjcentVertex != -999 && sin)
            {
                graph[vertex].insert(adjcentVertex);
                sin >> adjcentVertex;
            }
        }
    }
    fin.close();
}

void graphType::clearGraph()
{
    for (int i = 0; i < graph.size(); i++)
    {
        graph[i].destroyList();
    }
    graph.clear();
    names.clear();
    maxSize = 0;
}

std::string graphType::printGraph()
{
    std::ostringstream out;
    out << "digraph {" << std::endl; // graphviz output
    for (int i = 0; i < graph.size(); i++)
    {
        /*  out << i << " ";
         graph[i].print(out);
         out << std::endl; //python program output */
        for (linkedListIterator<int> graphIt = graph[i].begin(); graphIt != graph[i].end(); ++graphIt)
        {
            out << i << "->" << **graphIt << ";" << std::endl;
        }
    }
    out << std::endl; // graphViz output
    out << "}";

    return out.str();
}

std::string graphType::depthFirstTraversal()
{
    bool *visited;
    visited = new bool[graph.size()];
    std::string output = "";
    for (int i = 0; i < graph.size(); i++)
    {
        visited[i] = false;
    }
    for (int i = 0; i < graph.size(); i++)
    {
        if (!visited[i])
        {
            dft(i, visited, output);
        }
    }
    delete[] visited;
    return output;
}

std::string graphType::dftAtVertex(int vertex)
{
    bool *visited;
    visited = new bool[graph.size()];
    std::string output = "";
    for (int i = 0; i < graph.size(); i++)
    {
        visited[i] = false;
    }
    dft(vertex, visited, output);
    delete[] visited;
    return output;
}

std::string graphType::breadthFirstTraversal()
{
    linkedQueue<int> queue;
    std::vector<bool> visited(graph.size(), false);
    std::string out = "";
    for (int i = 0; i < graph.size(); i++)
    {
        if (!visited[i])
        {
            queue.enqueue(i);

            while (!queue.isEmptyQueue())
            {
                int u = queue.dequeue();
                if (!visited[u])
                {

                    visited[u] = true;
                    if (out.empty())
                    {
                        out = std::to_string(u);
                    }
                    else
                    {
                        out += " " + std::to_string(u);
                    }
                }
                for (auto graphIt = graph[u].begin(); graphIt != graph[u].end(); ++graphIt)
                {
                    int w = **graphIt;
                    if (!visited[w])
                    {
                        queue.enqueue(w);
                    }
                }
            }
        }
    }
    return out;
}

void graphType::copyGraph(const graphType &graphToCopy)
{
    if (!this->isEmpty())
    {
        this->clearGraph();
    }
    this->maxSize = graphToCopy.maxSize;
    this->graph.resize(this->maxSize);
    for (int i = 0; i < graphToCopy.graph.size(); i++)
    {
        this->graph[i] = graphToCopy.graph[i];
    }
}

void graphType::dft(int v, bool visited[], std::string &output)
{
    visited[v] = true;
    if (output.empty())
    {
        output = names[v];
    }
    else
    {
        output = output + " --> " + names[v] + " ";
    }
    linkedListIterator<int> graphIt;
    for (graphIt = graph[v].begin(); graphIt != graph[v].end(); ++graphIt)
    {
        int w = **graphIt; // linked list iterator returns a pointer the extra * dereferences it to an int
        if (!visited[w])
        {
            dft(w, visited, output);
        }
    }
}
