#include <iostream>
#include <vector>
#include <set>
using namespace std;

class UndirectedWeightedGraph
{
    // first index, source, then vector of {dest, edgeWeight}
    vector<vector<pair<int, int>>> adjacencyList;

public:
    UndirectedWeightedGraph();
    void printAdjacencyList();
    int primMST();
};

UndirectedWeightedGraph::UndirectedWeightedGraph()
{
    int numNodes;
    int numEdges;
    cin >> numNodes >> numEdges;

    for (int i = 0; i < numNodes; i++)
        adjacencyList.push_back(vector<pair<int, int>>());

    int source, dest, weight;
    for (int i = 0; i < numEdges; i++)
    {
        cin >> source >> dest >> weight;
        //as the graph is undirected and values are assumed 0 indexed
        adjacencyList[source].push_back({dest, weight});
        adjacencyList[dest].push_back({source, weight});
    }
}

void UndirectedWeightedGraph::printAdjacencyList()
{
    for (int i = 0; i < adjacencyList.size(); i++)
    {
        cout << i << ": ";
        for (int j = 0; j < adjacencyList[i].size(); j++)
            cout << adjacencyList[i][j].first << " ";
        cout << "\n";
    }
}

//source can be anything between 0 to numberofNodes -1
int UndirectedWeightedGraph::primMST()
{
    srand(time(0));
    int source = rand() % adjacencyList.size();
    cout << "start: " << source << endl;
    //<------------- setup required Data ------------------>
    vector<bool> isVisited(adjacencyList.size(), false);
    vector<int> previousDistanceToNode(adjacencyList.size(), INT32_MAX);

    set<pair<int, int>> possibleEdges;
    // set -> {weight, destNode}
    // set ordering is first by pair.first, then by pair.second;

    int cost = 0;

    possibleEdges.insert({0, source});
    previousDistanceToNode[source] = 0;

    //<---------------- Run Prim Algo------------------>
    while (!possibleEdges.empty())
    {
        //now due to ordering of set, edge with minimum edge weight will come on top
        auto elem = *(possibleEdges.begin());
        possibleEdges.erase(elem);

        cout << "dest node: " << elem.second << "\tweight :" << elem.first << "\n";
        isVisited[elem.second] = true;

        cost += elem.first;

        for (auto i : adjacencyList[elem.second])
        {
            //only add to possibleEdge if the destination node hasn't been included
            if (isVisited[i.first] != true)
            {
                //only update, if new edge found has less cost than previous edge to dest node
                if (previousDistanceToNode[i.first] > i.second)
                {
                    //if no such element is present is set, nothing happens to set
                    possibleEdges.erase({previousDistanceToNode[i.first], i.first});
                    previousDistanceToNode[i.first] = i.second;
                    possibleEdges.insert({previousDistanceToNode[i.first], i.first});
                }
            }
        }
    }

    return cost;
}

int main()
{
    UndirectedWeightedGraph uwg;
    auto ans = uwg.primMST();
    cout << "MST weight: " << ans;
}