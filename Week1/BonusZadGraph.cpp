// Bonus_Zad.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using std::cout;
using std::cin;
using std::endl;
constexpr int MAX_NAME_LENGTH = 10;
struct Edge
{
    char begin[MAX_NAME_LENGTH];
    char end[MAX_NAME_LENGTH];
};
struct Graph {
    unsigned int verticesCount=0;
    unsigned int ribCount=0;
    Edge* edges;

};
void deleteGraph(Graph& graph)
{
    delete[] graph.edges;
}
void printEdge(const Edge& edge)
{
    cout << edge.begin<<" "<<edge.end<<endl;
}
void printGraph(const Graph& g)
{
    cout << "Edges:\n";
    for (int i = 0; i < g.ribCount; i++)
    {
        printEdge(g.edges[i]);
    }
    cout << "\n";
    cout <<"Number Of Vertices: " << g.verticesCount << endl;
}
bool isNewVertex(const Graph& graph, const char* vertice)
{
    for (int i = 0; i < graph.ribCount; i++)
    {
        if (strcmp(graph.edges[i].begin, vertice) == 0
            || strcmp(graph.edges[i].end, vertice) == 0) {
            return false;
        }
        
    }
    return true;
}
bool isValidEdge(const Graph& graph, const Edge& edge)
{
    
    for (int i = 0; i < graph.ribCount; i++)
    {
        if (strcmp(graph.edges[i].begin, edge.begin) == 0
            && strcmp(graph.edges[i].end, edge.end) == 0){
            return false;
        }
            
    }
    return true;
}
bool isValid(const Graph& graph, const Edge& edge)
{
    if (strlen(edge.begin) > 10 || strlen(edge.end) > 10) {
        return false;
    } 
    if (!isValidEdge(graph, edge)) {
        return false;
    }
    if (strcmp(edge.begin, edge.end) == 0) {
        return false;
    }
    return true;
}
bool addEdge(Graph& graph)
{
    Edge edge;
    cin >> edge.begin;
    cin >> edge.end;
    if (!isValid(graph, edge))
    {
        cout << "Incorrect Edge Input Again: " << endl;
        return false;
    }
    int edgesCount = graph.ribCount+1;
    Edge* newEdges = new Edge[edgesCount];
    int i = 0;
    for (; i < edgesCount-1; i++)
    {
        newEdges[i] = graph.edges[i];
    }
    if (isNewVertex(graph, edge.begin))
    {
        graph.verticesCount++;
    }
    if (isNewVertex(graph, edge.end))
    {
        graph.verticesCount++;
    }
    newEdges[i] = edge;
    deleteGraph(graph);
    graph.edges = newEdges;
    graph.ribCount++;
    return true;
}
void swap(Edge& edge1, Edge& edge2)
{
    Edge edge3 = edge1;
    edge1 = edge2;
    edge2 = edge1;
}

void removeEdge(Graph& graph, const Edge edge)
{
    if (isNewVertex(graph, edge.begin) || isNewVertex(graph, edge.end))
    {
        cout << "The Graph dosn't contains this Edge" << endl;
        return;
    }
    for (int i = 0; i < graph.ribCount; i++)
    {
        if (strcmp(graph.edges[i].begin, edge.begin) == 0 || strcmp(graph.edges[i].end, edge.end) == 0)
        {
            swap(graph.edges[i], graph.edges[graph.ribCount - 1]);
            break;
        }
    }
    int newSize = graph.ribCount - 1;
    Edge* edges = new Edge[newSize];
    for (int i = 0; i < newSize; i++)
    {
        edges[i] = graph.edges[i];
    }
    deleteGraph(graph);
    graph.ribCount = newSize;
    graph.edges = edges;
    if (isNewVertex(graph, edge.begin)) 
    {
        graph.verticesCount--;
    }
    if (isNewVertex(graph, edge.end))
    {
        graph.verticesCount--;
    }

}
void initiliazeGraph(Graph& graph,const int m)
{
    for (int i = 0; i < m; i++)
    {
        if (!addEdge(graph))
        {
            i--;
            continue;
        }
    }
    
    printGraph(graph);
}
int findDeg(const Graph& graph, const char* vertice)
{
    int degCounter = 0;
    for (int i = 0; i < graph.ribCount; i++)
    {
        if (strcmp(graph.edges[i].begin, vertice) == 0) {
            degCounter++;
        } 
    }
    return degCounter;
}
bool isGraphFull(const Graph& graph)
{
    for (int i = 0; i < graph.ribCount; i++)
    {
        int degree = findDeg(graph, graph.edges[i].begin);
        if (degree != graph.verticesCount - 1) {
            return false;
        }
    }
    return true;
}
void createGraph(Graph& graph, const int m)
{
    graph.edges = new Edge[m];
}
int main()
{
    constexpr int MAX_COMMAND_SIZE = 20;
    int command;
    int m;
    cout << "Enter Number of Edges: " << endl;
    cin >> m;
    Graph graph;
    createGraph(graph, m);
    //graph.edges = new Edge[m]; // trqbva delete
 
    initiliazeGraph(graph,m);
    while (true)
    {
        cout << "Choose Command:"<<endl;
        cout << "1) - Add" << endl;
        cout << "2) - Find Deg" << endl;
        cout << "3) - Check is Graph Full" << endl;
        cout << "4) - Remove Edge" << endl;
        cout << "9) - Exit" << endl;
        cin >> command;
        if (command == 9) {
            break;
        }
        else if (command == 1) {
            cout << "Enter Edge: " << endl;
            addEdge(graph);
        }
        else if (command == 2){
            char vertice[MAX_NAME_LENGTH]=" ";
            cout << "Enter Vertice Name\n";
            cin >> vertice;
            int degree = findDeg(graph, vertice);
            cout << "Degree of Vertice is: " << degree << endl;
        }
        else if (command == 3){
            bool isFull = isGraphFull(graph);
            if (isFull) {
                cout << "Graph is Full" << endl;
            }
            else {
                cout << "Graph is not Full" << endl;
            }
        }
        else if (command == 4){
            Edge edge;
            cout << "Enter Edge To Remove:\n";
            cin >> edge.begin;
            cin >> edge.end;
            removeEdge(graph, edge);
        }
        printGraph(graph);
    }
    delete[] graph.edges;
}

