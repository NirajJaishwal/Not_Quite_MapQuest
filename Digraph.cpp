
// Digraph.cpp -- directed graph class
// c. 2017 T. O'Neil

#include "Digraph.hpp"
#include "limits" // include for std::numeric_limits

// Function to return the number of vertices in the graph
unsigned int Digraph::noVertices()
{
    return numberOfVertices;
}

// Function to return the number of edges in the graph
unsigned int Digraph::noEdges()
{
    return numberOfEdges;
}

// Function to reset the edge weights in the graph
void Digraph::resetEdges()
{
    distMatrix.clear();
    distMatrix.resize(numberOfVertices, std::vector<int>(numberOfVertices, 0));
}

// Function to add an edge to the graph with the specified weight
void Digraph::addEdge(int source, int dest, int wt)
{
    if (source >= 0 && source < numberOfVertices && dest >= 0 && dest < numberOfVertices)
    {
        distMatrix[source][dest] = wt;
        numberOfEdges++;
    }
}

// Function to delete an edge from the graph
void Digraph::delEdge(int source, int dest)
{
    if(source >= 0 && source < numberOfVertices && dest >= 0 && dest < numberOfVertices)
    {
        distMatrix[source][dest] = 0;
        numberOfEdges--;
    }
}

// Function to check if there is an edge between two vertices and return it's weight
int Digraph::isEdge(int source, int dest)
{
    if (source >= 0 && source < numberOfVertices && dest >= 0 && dest < numberOfVertices)
    {
        return distMatrix[source][dest];
    }
    return 0; //if not a edge, return 0
}

// Dijkstra's algorithm to find the shortest path and distance from source to destination
int Digraph::dijkstra(int source, int dest)
{
    // Initialize vectors to store distance, parents, and visited status of vertices
    std::vector<int> distance(numberOfVertices, std::numeric_limits<int>::max());
    std::vector<int> parent(numberOfVertices, -1);
    std::vector<bool> visited(numberOfVertices, false);

    distance[source] = 0;

    // Iterate through vertices to find the shortest path
    for(int i = 0; i < numberOfVertices - 1; ++i)
    {
        int minDistance = std::numeric_limits<int>::max();
        int minIndex = -1;

        // Find the vertex with the minimum distance among unvisited vertices
        for(int j = 0; j < numberOfVertices; ++j)
        {
            if(!visited[j] && distance[j] <= minDistance)
            {
                minDistance = distance[j];
                minIndex = j;
            }
        }

        // If no unvisited vertex if found, break the loop
        if(minIndex == -1)
            break;

        // Mark the selected vertex as visited
        visited[minIndex] = true;

        // Update distance and parents of adjacent vertices
        for(int v = 0;  v < numberOfVertices; ++v)
        {
            if (!visited[v] && distMatrix[minIndex][v] && distance[minIndex] != std::numeric_limits<int>::max() && distance[minIndex] + distMatrix[minIndex][v] < distance[v])
            {
                distance[v] = distance[minIndex] + distMatrix[minIndex][v];
                parent[v] = minIndex;
            }
        }
    }
    // Print the shortest path and distance
    cout << "Shortest Path from " << vertex[source]->getName() << " to " << vertex[dest]->getName() << ":\n";
    int current = dest;
    std::vector<int> path;
    while (current != -1)
    {
        path.push_back(current);
        current = parent[current];
    }

    // Print the path in reverse order
    cout << "Path: ";
    for (int i = path.size() - 1; i >= 0; --i)
    {
        cout << vertex[path[i]]->getName();
        if (i > 0)
            cout << " -> ";
    }
    cout << "\nDistance: " << distance[dest] << " miles\n";
    return distance[dest];
}
