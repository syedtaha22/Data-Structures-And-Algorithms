/*
    Directed Eulerian cycle:
        A directed Eulerian cycle is a directed cycle that contains each edge
        exactly once. Write a digraph client that find a directed Eulerian cycle
        or reports that no such cycle exists.

        If an Eulerian cycle is found then print it out in order of the traversal
        of vertices. So for an Eulerian cycle with nodes A,B,C, and D the output
        should also print this:
                A>B>C>D>A

        Hint: Prove that a digraph G has a directed Eulerian cycle if and only
        if vertex in G has its indegree equal to its outdegree and all vertices
        with nonzero degree belong to the same strong component.

    Approach:
        1) What is an Eulerian cycle?
            An eulerian cycle is a path, that visits each edge exactly once and returns to the starting vertex.

        2) How do we know if a directed graph has an Eulerian cycle?
            A directed graph has an Eulerian cycle if and only if the following conditions are met:
                a) The graph is strongly connected
                b) The in-degree of each vertex is equal to the out-degree of each vertex

            a) Strong Connectivity:
                A directed graph is strongly connected if there is a path from each vertex to every
                other vertex.
                To check if a directed graph is strongly connected, we can perform a DFS from each vertex
                and check if all vertices are reachable from that vertex.

            b) In-degree equals Out-degree:
                The in-degree of a vertex is the number of edges coming into the vertex.
                The out-degree of a vertex is the number of edges going out of the vertex.
                To check if the in-degree equals the out-degree for each vertex, we can maintain two arrays
                indegree[] and outdegree[] to store the in-degree and out-degree of each vertex respectively.
                Then, we can iterate over all vertices and check if indegree[i] equals outdegree[i] for each vertex i.

        3) How to find the Eulerian cycle?
            If the above conditions are met, we can find the Eulerian cycle using Hierholzer's algorithm.
            The algorithm is as follows:
                a) Start at any vertex
                b) Follow a trail of edges from that vertex until returning to the vertex
                c) It is not possible to get stuck at any vertex other than the starting vertex
                d) Keep track of the vertices in a stack
                e) If all edges are visited, then the cycle is complete
                f) If the cycle is not complete, pick a vertex from the stack and repeat the process
                g) Print the vertices in the stack to get the Eulerian cycle

        4) Implementation:
            We can create a Digraph class to represent the directed graph.
            The Digraph class can have functions to add edges, print the graph, check if the graph is strongly
            connected, and check if the in-degree equals the out-degree for each vertex.

            We can then create a Client class that takes a Digraph as input and checks if the graph has an
            Eulerian cycle. The Client class can use the Digraph class to check if the graph is strongly
            connected and if the in-degree equals the out-degree for each vertex. If these conditions are met,
            the Client class can find the Eulerian cycle using Hierholzer's algorithm.
*/


#include <iostream>
#include <vector>
#include <stack>
#include <cstring>

class Digraph {
    std::vector<std::vector<int>> adjList;
    int vertices;
    int edges;

    // Function to perform DFS from a vertex
    void DFS(int v, std::vector<bool>& visited) {
        visited[v] = true;
        for (int w : adjList[v]) {
            if (!visited[w]) {
                DFS(w, visited);
            }
        }
    }

    // Function to check if in-degree equals out-degree for each vertex
    bool IndegreeEqualsOutdegree() {
        std::vector<int> indegree(vertices, 0);
        std::vector<int> outdegree(vertices, 0);

        for (int v = 0; v < vertices; v++) {
            outdegree[v] = adjList[v].size();
            for (int w : adjList[v]) {
                indegree[w]++;
            }
        }

        for (int i = 0; i < vertices; i++) {
            if (indegree[i] != outdegree[i]) {
                return false;
            }
        }
        return true;
    }

    // Function to check if the graph is strongly connected
    bool isStronglyConnected() {
        for (int v = 0; v < vertices; v++) {
            std::vector<bool> visited(vertices, false);
            DFS(v, visited);
            for (bool visit : visited) {
                if (!visit) {
                    return false;
                }
            }
        }
        return true;
    }

public:
    Digraph(int V) {
        this->vertices = V;
        this->edges = 0;
        adjList.resize(V);
    }

    void addEdge(int v, int w) {
        // Check i the vertices are valid
        if (v < 0 || v >= vertices || w < 0 || w >= vertices) {
            std::cout << "Invalid vertices" << std::endl;
            return;
        }
        adjList[v].push_back(w);
        edges++;
    }

    void printGraph() {
        for (int v = 0; v < vertices; v++) {
            std::cout << v << " -> ";
            for (int w : adjList[v]) {
                std::cout << w << " ";
            }
            std::cout << std::endl;
        }
    }

    // Function to get number of vertices
    int getVertices() {
        return vertices;
    }

    // Function to get adgency list
    std::vector<std::vector<int>> getAdjList() {
        return adjList;
    }

    // Function to check if the graph has an Eulerian cycle
    bool hasEulerianCycle() {
        if (!isStronglyConnected()) {
            return false;
        }
        return IndegreeEqualsOutdegree();
    }
};

// Functor to find the Eulerian cycle
class getEulerianCycle {
    /*
        3) How to find the Eulerian cycle?
            If the above conditions are met, we can find the Eulerian cycle using Hierholzer's algorithm.
            The algorithm is as follows:
                a) Start at any vertex
                b) Follow a trail of edges from that vertex until returning to the vertex
                c) It is not possible to get stuck at any vertex other than the starting vertex
                d) Keep track of the vertices in a stack
                e) If all edges are visited, then the cycle is complete
                f) If the cycle is not complete, pick a vertex from the stack and repeat the process
                g) Print the vertices in the stack to get the Eulerian cycle
    */
public:
    // Overload the () operator to find the Eulerian cycle
    void operator()(const Digraph& graph) {
        // make a copy of the graph
        Digraph G = graph;

        // Check if the graph has an Eulerian cycle
        if (!G.hasEulerianCycle()) {
            std::cout << "No Eulerian cycle exists in the graph." << std::endl;
            return;
        }


        // Get the total number of vertices and the adjacency list
        int V = G.getVertices();
        std::vector<std::vector<int>> adjList = G.getAdjList();

        /*
            a) Start at any vertex
                Start at vertex zero, since the graph is strongly connected
                and has an Eulerian cycle, starting from any vertex, we can
                get the Eulerian cycle.
        */
        int start = 0;

        std::stack<int> stack; // Stack to keep track of vertices that are part of the cycle
        std::vector<int> cycle; // Vector to store the Eulerian cycle

        stack.push(start); // Push the starting vertex to the stack
        int curr = start; // Set the current vertex to the starting vertex

        // While the stack is not empty, meaning there are vertices to visit
        while (!stack.empty()) {
            if (adjList[curr].size() > 0) {
                stack.push(curr); // Push the current vertex to the stack

                // Get the next vertex, from the neighbors of the current vertex
                int next = adjList[curr].back();

                // Remove the neighbor from the adjacency list
                adjList[curr].pop_back();

                curr = next; // Set the neighbor as the current vertex
            }
            // If it does not have neighbors
            else {
                // Add the current vertex to the cycle
                cycle.push_back(curr);
                // Get current vertex from the stack
                curr = stack.top();
                // Remove the vertex from the stack
                stack.pop();
            }
        }

        std::cout << "Eulerian cycle: ";
        for (int i = cycle.size() - 1; i >= 0; i--) {
            std::cout << cycle[i] << " ";
        }
        std::cout << std::endl;
    }

};

int main() {
    /*
        Test Cases:
            1) Create a directed graph with an Eulerian cycle
            2) Create a directed graph without an Eulerian cycle, due to the in-degree not equaling the out-degree
            3) Create a directed graph without an Eulerian cycle, due to the graph not being strongly connected
    */

    // 1) Create a directed graph with an Eulerian cycle
    Digraph G(5);
    G.addEdge(0, 1);
    G.addEdge(1, 2);
    G.addEdge(2, 0);
    G.addEdge(0, 3);
    G.addEdge(3, 4);
    G.addEdge(4, 0);
    std::cout << "Graph with Eulerian cycle:" << std::endl;
    G.printGraph(); // Print the graph 
    getEulerianCycle()(G); // 0 3 4 0 1 2 0

    // 2) Create a directed graph without an Eulerian cycle due to the in-degree not equaling the out-degree
    Digraph G2(4);
    G2.addEdge(0, 1);
    G2.addEdge(1, 2);
    G2.addEdge(2, 0);
    G2.addEdge(0, 3);
    std::cout << "\nGraph without Eulerian cycle due to in-degree not equaling out-degree:" << std::endl;
    G2.printGraph(); // Print the graph
    getEulerianCycle()(G2); // No Eulerian cycle exists in the graph.

    // 3) Create a directed graph without an Eulerian cycle due to the graph not being strongly connected
    Digraph G3(5);
    G3.addEdge(0, 1);
    G3.addEdge(1, 2);
    G3.addEdge(2, 0);
    G3.addEdge(3, 4);
    std::cout << "\nGraph without Eulerian cycle due to graph not being strongly connected:" << std::endl;
    G3.printGraph(); // Print the graph
    getEulerianCycle()(G3); // No Eulerian cycle exists in the graph.

    return 0;
}