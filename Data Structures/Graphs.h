// File: Graphs.h
// Graph library header file for use with Asn#5
/*
 ______________________________________________________________________________________________
 
 This file describes a structure for a weighted undirected graph with a maximum of Vmax = 50
 vertices and Emax = Vmax(Vmax-1)/2 edges. The verices are numbered 0,1,...V-1. The graph is
 assumed to be on a text file in the form of an adjacency matrix. The weights on the edges are
 assumed to be positive integers with zero weight indicating the absence of an edge.
 An edge (u,v,w) existing between nodes (u) and (v) with weight (w) is modeled as a class
 (Edge). When loaded from the text file, the weights are stored in a  2-D
 array (AdjMatrix) representing the adjacency matrix. Another  array (edges) stores
 the non-zero edges in the graph. The functions declared here are needed to implement:
 
 (1) Depth First Search (DFS) algorithm for graph traversal.
 (2) Dijkstra's Algorithm to compute the shortest paths from a given source node to all other
 nodes in the graph.
 _______________________________________________________________________________________________
 */

#ifndef GRAPHS_H
#define GRAPHS_H
#include <string>
#include "Edge.h"
#include <fstream>		// For reading file from disk
#include <iostream>
#include <stack>		// For file name\#include <string.h>		// For file name
#include <queue>		// For file name

#include <iomanip>
#include "Edge.h"		// Deinition of an Edge
using namespace std;

const int Vmax = 50;					// Maximum number of vertices
const int Emax = Vmax*(Vmax-1)/2;		// Maximum number of edges

class Graphs{
public:
    
    //_____________________________________
    // Member Functions
    // Class Constructor & Destructor
    Graphs();
    ~Graphs();
    
    // Function Prototypes___________________
    
    char Vname(const int s) const;		// Map vertex number to a name (character)
    void getGraph(string fname);		// Get Graph from text File (fname)
    void dispGraph() const;			// Display Ajacency Matrix
    int  No_of_Verices() const;		// Get number of vertices (V)
    int  No_of_Edges() const;		// Get Number of Non-zero edges (E)
    void dispEdges() const;         // Display Graph edges
    void DFS(int);				// Depth First Search Traversal (DFS)
    void DFS();				// Depth First Search Traversal (DFS)
    void BFS(int);				// Breadth First Search Traversal (BFS)
    void shPath(int);			// Shortest paths from node (s)
    int dij(int, int);			// Shortest paths from node (s) to node (e)
    void printInfo()const;	// Prints Info about Graph
    bool isUnDirected()const;
    int getDegree()const;
    
    //______________________________________________________________________________________________
    
private:
	   
    int V, E;				// No.of vertices (V) and edges (E)
    weightType AdjMatrix[Vmax][Vmax];	// Adjacency Matrix
    Edge edges[Emax];			// Array of non-zero edges
    weightType distance[Vmax];		// Distance array for shortest paths
    int via[Vmax];			// Via array for shortest paths
    bool processed[Vmax];		// processed array for shortest paths
    int order;				// Order of Visit of a node in the DFS
    int val[Vmax];			// Array holding order of traversal of nodes
    void getEdges();			// Get Non-Zero edges from adjacency matrix
    void printEdge(Edge e) const;	// Output an edge (e)
    void printPath(int s,int i) const;	// Print path from source (s) to destination (i)
    void visit(int k);			// Node Visit Function (needed for DFS)
};


// Constructor
Graphs::Graphs(){
    E = V = order = 0;
}

// Destructor
Graphs::~Graphs(){
}


// Map vertex number (0,1,2,..) to (A,B,C,..)
char Graphs::Vname(const int i) const{
    string cities = "ABCDEFGHIJKLMN";
    return (i<cities.length() && i>=0) ? cities[i] : ' ';
}

// Get Graph from text File (file name is stored in string fname)
// Graph is stored in adjacency matrix
void Graphs::getGraph(string fname){
    // Local data ...
    weightType wi;
    int i = -1;
    ifstream source;
    
    if(!source.fail()){
        source.open(fname.c_str());
        source >> V;	// Read no. of verices (V)
        while (i++,!source.eof()) {
            // get V weights for row [r] from file
            for (int j = 0; j<V; j++) {
                source>>wi;
                // put V weights in adjacency matrix at row [r]
                AdjMatrix[i][j] = wi;
            }
        }
    }else{
        cerr<<"Can't Open File!!"<<endl;
    }

    // close file
    source.close();
    getEdges();
}

// Display Adjacency Matrix
void Graphs::dispGraph() const{
    int i,j;
    cout<<"\n******** Adjacency Matrix *********\n"<<endl;
    for(i=0; i<V; i++){
        for(j=0; j<V; j++)
            cout<< setw(3)<< AdjMatrix[i][j] << " ";
        cout<< endl;
    }
}

// Get Non-Zero edges from adjacency matrix
// and store them in array edges[].
void Graphs::getEdges(){
    int r , c;
    int i = 0;
    weightType weight;
    
    // Only examine weights above the diagonal
    for (r = 0; r <= V-2; r++)
        for (c = r+1; c <= V-1; c++){
            weight = AdjMatrix[r][c];
            if (weight){
                // save (r,c,weight) in edges[i]
                edges[i].u = r;
                edges[i].v = c;
                edges[i].w = weight;
                i++;
            }
        }
    E = i;	// Number of non-zero edges
}

// Get number of vertices (V)
int Graphs::No_of_Verices() const{
    return V;
}

// Get Number of Non-zero edges (E)
int Graphs::No_of_Edges() const{
    return E;
}

// Output an edge (e): Vertex names and weight
void Graphs::printEdge(Edge e) const{
    cout << Vname(e.u) << " " << Vname(e.v) << " " << e.w << endl;
}

// Display Graph Edges
void Graphs::dispEdges() const{
    cout<<"\n******** Graph Edges *********\n"<<endl;
    for (int i = 0; i < E; i++)
        printEdge(edges[i]);
}

void Graphs::printInfo()const{
    cout<<"\n******** Graph Info *********\n"<<endl;
    cout<<"Number of Vertices: "<<V<<endl;
    cout<<"Number of Edges: "<<E<<endl;
}

// Shortest paths from node s
// uses Dijkstra's Algorithm
void Graphs::shPath(int st){
    // Implement the function here
    for (int i = 0; i<V; i++) distance[i] = INT_MAX;
    memset(processed, false, sizeof(processed));
    distance[st] = 0;
    priority_queue<pair<int, int>> pq;
    pq.push(make_pair(0, st));
    while (pq.size()) {
        int v = pq.top().second;
        pq.pop();
        if (processed[v]) continue;
        visit(v);

        for(int j = 0; j<V; j++){
            if (!processed[j] && AdjMatrix[v][j] && distance[v] != INT_MAX){
                if(distance[v]+AdjMatrix[v][j] < distance[j]){
                    distance[j] = distance[v] + AdjMatrix[v][j];
                    pq.push(make_pair(-distance[j],j));
                    via[j] = v;
                }
            }
        }
    }
    
    cout<<"\n******** Shortest Paths from Node "<<Vname(st)<< " *********\n"<<endl;

    for (int i = 0; i<V; i++) {
        //printf("Distance from %c to %c is %d with path of ",Vname(st),Vname(i),distance[i]);
        cout<<setw(10)<<"Cost: "<<distance[i]<<setw(10)<<"Path: ";
        printPath(st, i);
        cout<<endl;
    }
}

int Graphs::dij(int st, int e){
    // Returns Shortest Distance from City St to E or -1 if no path exist
    for (int i = 0; i<V; i++) distance[i] = INT_MAX;
    memset(processed, false, sizeof(processed));
    distance[st] = 0;
    priority_queue<pair<int, int>> pq;
    pq.push(make_pair(0, st));
    while (pq.size()) {
        int v = pq.top().second;
        pq.pop();
        if(v == e) return distance[e];
        if (processed[v]) continue;
        visit(v);
        for(int j = 0; j<V; j++){
            if (!processed[j] && AdjMatrix[v][j]){
                if(distance[v]+AdjMatrix[v][j] < distance[j]){
                    distance[j] = distance[v] + AdjMatrix[v][j];
                    pq.push(make_pair(-distance[j],j));
                    via[j] = v;
                }
            }
        }
    }
    return -1;
}



// Print path (vertex names) from source (s) to destination (i)
void Graphs::printPath(int s, int i) const{
    // Implement the function here
    i == s ? (cout << Vname(s)):(printPath(s,via[i]),cout << Vname(i));
}

// Node Visit Function
void Graphs::visit(int k){
    // Implement the function here
    processed[k] = 1;
}

// Depth First Search Traversal
void Graphs::DFS(int v){
    // Implement the function here
    stack<int>s;
    memset(processed, false, sizeof(processed));
    s.push(v);
    visit(v);
    while (s.size()) {
        int k = s.top();
        cout<<Vname(k)<<" ";
        s.pop();
        for (int i = V; i>=0; i--) {
            if (AdjMatrix[k][i]) {
                if (!processed[i]) {
                    s.push(i);
                    visit(i);
                }
            }
        }
    }
    cout<<endl;
}


void Graphs::DFS(){
    // Implement the function here
    stack<int>s;
    memset(processed, false, sizeof(processed));
    s.push(0);
    visit(0);
    while (s.size()) {
        int k = s.top();
        cout<<Vname(k)<<" ";
        s.pop();
        for (int i = V-1; i>=0; i--) {
            if (AdjMatrix[k][i]) {
                if (!processed[i]) {
                    s.push(i);
                    visit(i);
                }
            }
        }
    }
    cout<<endl;
}

void Graphs::BFS(int v){
    // Implement the function here
    queue<int>q;
    memset(processed, false, sizeof(processed));
    q.push(v);
    visit(v);
    while(q.size()){
        int k = q.front();
        q.pop();
        cout<<Vname(k)<<" ";
        for (int i = 0; i<V; i++) {
            if (AdjMatrix[k][i]) {
                if (!processed[i]) {
                    q.push(i);
                    visit(i);
                }
            }
        }
    }
    cout<<endl;
}


bool Graphs::isUnDirected()const{
    for (int i = 0; i<V; i++) {
        for (int j = 0; j<V; j++) {
            if (AdjMatrix[i][j]!=AdjMatrix[j][i]) {
                return false;
            }
        }
    }
    return true;
}

int Graphs::getDegree()const{
    int max = 0, cnt = 0;
    for (int i = 0; i<V; i++) {
        cnt = 0;
        for (int j = 0; j<V; j++) {
            if (AdjMatrix[i][j]) cnt++;
        }
        if(cnt>max)
            max = cnt;
    }
    return max;
}

#endif // GRAPHS_H

