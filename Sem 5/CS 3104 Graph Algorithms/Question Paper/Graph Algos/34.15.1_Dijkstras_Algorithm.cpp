#include <iostream>
#include <vector>
#include <set>
using namespace std;

class UndirectedWeightedGraph
{
    // first index, source, then vector of {dest, edgeWeight}
    vector<vector<pair<int, int>>> weightedAdjacencyList;

public:
    UndirectedWeightedGraph();
    void printAdjacencyList();
    vector<int> dijkstra(int initialNode);
};

UndirectedWeightedGraph::UndirectedWeightedGraph()
{
    int numNodes;
    int numEdges;
    cin >> numNodes >> numEdges;

    for (int i = 0; i < numNodes; i++)
        weightedAdjacencyList.push_back(vector<pair<int, int>>());

    int source, dest, weight;
    for (int i = 0; i < numEdges; i++)
    {
        cin >> source >> dest >> weight;
        // as the graph is undirected and values are assumed 0 indexed
        weightedAdjacencyList[source].push_back({dest, weight});
        // weightedAdjacencyList[dest].push_back({source, weight});
    }
}

void UndirectedWeightedGraph::printAdjacencyList()
{
    for (int i = 0; i < weightedAdjacencyList.size(); i++)
    {
        cout << i << ": ";
        for (int j = 0; j < weightedAdjacencyList[i].size(); j++)
            cout << weightedAdjacencyList[i][j].first << " ";
        cout << "\n";
    }
}

vector<int> UndirectedWeightedGraph::dijkstra(int initialNode)
{
    vector<int> minPathToNode(weightedAdjacencyList.size(), INT32_MAX);

    //{weight, dest}
    set<pair<int, int>> possibleEdges;

    possibleEdges.insert({0, initialNode});
    minPathToNode[initialNode] = 0;

    while (!possibleEdges.empty())
    {
        auto minCostNode = *(possibleEdges.begin());
        possibleEdges.erase(minCostNode);

        for (auto edge : weightedAdjacencyList[minCostNode.second])
        {
            if (minPathToNode[minCostNode.second] + edge.second < minPathToNode[edge.first])
            {
                cout << "dest: " << edge.first << " update:" << minPathToNode[minCostNode.second] + edge.second << "\n";
                possibleEdges.erase({minPathToNode[edge.first], edge.first});
                minPathToNode[edge.first] = minPathToNode[minCostNode.second] + edge.second;
                possibleEdges.insert({minPathToNode[edge.first], edge.first});
            }
        }

        for (auto i : minPathToNode)
            if (i == INT32_MAX)
                cout << "INF ";
            else
                cout << i << " ";
        cout << endl;
    }

    for (int i = 0; i < minPathToNode.size(); i++)
    {
        if (minPathToNode[i] == INT32_MAX)
            minPathToNode[i] = -1;
    }

    return minPathToNode;
}

int main()
{
    UndirectedWeightedGraph uwg;
    vector<int> minPathToNode = uwg.dijkstra(0);

    for (auto i : minPathToNode)
        cout << i << " ";
}