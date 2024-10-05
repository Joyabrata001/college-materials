#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class DisjointSetUnion
{
    vector<int> parent;
    vector<int> size;

    int find_set(int x);

public:
    DisjointSetUnion(int numVertices);
    bool setUnion(pair<int, int> &edge);
};

DisjointSetUnion::DisjointSetUnion(int numVertices)
{

    size = vector<int>(numVertices, 1);
    parent = vector<int>(numVertices);

    for (int i = 0; i < parent.size(); i++)
        parent[i] = i;
}

int DisjointSetUnion::find_set(int x)
{
    if (parent[x] != x)
        parent[x] = find_set(parent[x]);

    return parent[x];
}

bool DisjointSetUnion::setUnion(pair<int, int> &edge)
{
    int parX = find_set(edge.first);
    int parY = find_set(edge.second);

    if (parX != parY)
    {
        if (size[edge.first] < size[edge.second])
            swap(edge.first, edge.second);

        // now confirmed edge.first is the bigger tree

        parent[edge.second] = edge.first;
        size[edge.first] += size[edge.second];
        return true;
    }
    return false;
}

bool weightedEdgeComparator(pair<pair<int, int>, int> a, pair<pair<int, int>, int> b)
{
    return a.second < b.second;
}

int kruskalMST(int numVertices, vector<pair<pair<int, int>, int>> &weightedEdges)
{
    sort(weightedEdges.begin(), weightedEdges.end(), weightedEdgeComparator);

    // for(auto i: weightedEdges)
    //     cout<<i.second<<endl;

    DisjointSetUnion dsu(numVertices);
    int cost = 0;

    int numWtEdgeIncluded = 0;

    for (auto wtEdge : weightedEdges)
    {
        if (dsu.setUnion(wtEdge.first) == true)
        {
            cout << "edge taken : " << wtEdge.first.first << " " << wtEdge.first.second << " " << wtEdge.second << endl;
            cost += wtEdge.second;
            numWtEdgeIncluded++;

            if (numWtEdgeIncluded == numVertices - 1)
                break;
        }
    }

    return cost;
}

int main()
{
    int numVertices, numEdges;

    cin >> numVertices >> numEdges;

    // undirected
    // pair: edge, weight; edge: num1,num2
    vector<pair<pair<int, int>, int>> weightedEdges(numEdges);

    int x, y, w;

    for (int i = 0; i < weightedEdges.size(); i++)
    {
        cin >> x >> y >> w;
        weightedEdges[i] = {{x, y}, w};
    }

    auto ans = kruskalMST(numVertices, weightedEdges);
    cout << "Edge Cost: " << ans << endl;
}