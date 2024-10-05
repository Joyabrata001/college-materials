#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> UndirectedFloydWarshall(int numVertices, vector<vector<int>> weightedEdges)
{
    vector<vector<int>> distance(numVertices, vector<int>(numVertices, INT16_MAX));

    for (int i = 0; i < numVertices; i++)
        distance[i][i] = 0;

    for (auto i : weightedEdges)
        distance[i[0]][i[1]] = i[2];

    for (int k = 0; k < numVertices; k++)
    {
        for (int i = 0; i < numVertices; i++)
            for (int j = 0; j < numVertices; j++)
                distance[i][j] = min(distance[i][j], distance[i][k] + distance[k][j]);

        for (auto i : distance)
        {
            for (auto j : i)
                if (j == INT16_MAX)
                    cout << "INF\t";
                else
                    cout << j << "\t";

            cout << "\n";
        }
        cout << endl;
    }

    return distance;
}

int main()
{
    int numVertices, numEdges;
    cin >> numVertices >> numEdges;

    vector<vector<int>> weightedEdges(numEdges);

    for (int i = 0; i < weightedEdges.size(); i++)
    {
        weightedEdges[i] = vector<int>(3);
        cin >> weightedEdges[i][0] >> weightedEdges[i][1] >> weightedEdges[i][2];
    }

    int startNode;
    cin >> startNode;

    for (auto i : UndirectedFloydWarshall(numVertices, weightedEdges))
    {
        for (auto j : i)
            if (j == INT16_MAX)
                cout << "INF\t";
            else
                cout << j << "\t";

        cout << "\n";
    }
}