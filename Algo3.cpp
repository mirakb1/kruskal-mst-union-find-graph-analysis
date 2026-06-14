#include <iostream>
#include <cstdlib>

using namespace std;
int* parent;

class Edge {
public:
    int vertix1;
    int vertix2;
    int weight;

    Edge() {
        vertix1 = 0;
        vertix2 = 0;
        weight = 0;
    }

    Edge(int a, int b, int w) {
        vertix1 = a;
        vertix2 = b;
        weight = w;
    }
};

int findMinEdge(Edge arr[], int start, int n) {
    int minIndex = start;

    for (int i = start + 1; i < n; i++) {
        if (arr[i].weight < arr[minIndex].weight) {
            minIndex = i;
        }
    }

    return minIndex;
}

void selectionSortEdges(Edge arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = findMinEdge(arr, i, n);

        Edge temp = arr[i];
        arr[i] = arr[minIndex];
        arr[minIndex] = temp;
    }
}


void MakeSet(int V) {
    for (int i = 1; i <= V; i++) {
        parent[i] = -1;
    }
}

int FindSet(int x) {
    int r, s, t;
    r = x;

    while (parent[r] > 0) {
        r = parent[r];
    }

    s = x;
    while (s != r) {
        t = s;
        s = parent[s];
        parent[t] = r;
    }

    return r;
}

bool Union(int i, int j) {
    int x = FindSet(i);
    int y = FindSet(j);

    if (x == y) {
        return false;
    }

    if (abs(parent[x]) >= abs(parent[y])) {
        parent[x] = parent[x] + parent[y];
        parent[y] = x;
    }
    else {
        parent[y] = parent[x] + parent[y];
        parent[x] = y;
    }
    return true;
}

void PrintSets(int V, int step) {
    cout << "Step" << step << ": ";

    for (int i = 1; i <= V; i++) {

        if (FindSet(i) == i) {
            cout << "{";

            bool first = true;

            for (int j = 1; j <= V; j++) {
                if (FindSet(j) == i) {
                    if (!first) {
                        cout << ", ";
                    }

                    cout << j;
                    first = false;
                }
            }

            cout << "} ";
        }
    }

    cout << endl;
}


bool FindPathDFS(int current, int destination, int V, int** graph, bool visited[], int path[], int& pathLength) {

    visited[current] = true;
    path[pathLength] = current;
    pathLength++;

    if (current == destination) {
        return true;
    }

    for (int i = V; i >= 1; i--) {
        if (graph[current][i] == 1 && !visited[i]) {
            if (FindPathDFS(i, destination, V, graph, visited, path, pathLength)) {
                return true;
            }
        }
    }

    pathLength--;
    return false;
}

int main() {

    int V, E;

    cout << "Please enter the number of nodes: ";
    cin >> V;

    cout << "Please enter the number of edges: ";
    cin >> E;

    Edge* edgeList = new Edge[E];

    for (int i = 0; i < E; i++) {
        int u, v, w;

        cout << "Please enter edge " << i + 1
            << " and its weight in the order (vertex1 vertex2 weight): ";

        cin >> u >> v >> w;

        edgeList[i] = Edge(u, v, w);
    }

    int** graph = new int* [V + 1];
    for (int r = 0; r <= V; r++) {
        graph[r] = new int[V + 1];
    }

    for (int r = 0; r <= V; r++) {
        for (int c = 0; c <= V; c++) {
            graph[r][c] = 0;
        }
    }

    for (int j = 0; j < E; j++) {
        graph[edgeList[j].vertix1][edgeList[j].vertix2] = 1;
        graph[edgeList[j].vertix2][edgeList[j].vertix1] = 1;
    }

    selectionSortEdges(edgeList, E);

    parent = new int[V + 1];
    MakeSet(V);

    Edge* MST = new Edge[V - 1];

    int mstWeight = 0;
    int count = 0;
    int i = 0;
    bool hasCycle = false;

    while (count < V - 1 && i < E) {

        if (FindSet(edgeList[i].vertix1) != FindSet(edgeList[i].vertix2)) {

            MST[count] = edgeList[i];

            mstWeight = mstWeight + edgeList[i].weight;

            count = count + 1;

            Union(edgeList[i].vertix1, edgeList[i].vertix2);
        }
        else {
            hasCycle = true;
        }

        i = i + 1;
    }

    int components = 0;

    for (int j = 1; j <= V; j++) {
        if (parent[j] < 0) {
            components++;
        }
    }

    if (components == 1) {
        cout << "the graph is connected, it has one connected componentt" << endl;

        MakeSet(V);

        mstWeight = 0;
        count = 0;
        i = 0;
        hasCycle = false;

        cout << "The sets:" << endl;

        int step = 1;
        PrintSets(V, step);

        while (i < E) {

            if (FindSet(edgeList[i].vertix1) != FindSet(edgeList[i].vertix2)) {

                MST[count] = edgeList[i];

                mstWeight = mstWeight + edgeList[i].weight;

                count = count + 1;

                Union(edgeList[i].vertix1, edgeList[i].vertix2);

                step = step + 1;
                PrintSets(V, step);
            }
            else {
                hasCycle = true;
            }

            i = i + 1;
        }

        cout << "the final parent array: ";
        for (int j = 1; j <= V; j++) {
            cout << parent[j];
            if (j != V) {
                cout << ", ";
            }
        }
        cout << endl;

        cout << "the MST edges: ";
        for (int j = 0; j < count; j++) {
            cout << "(" << MST[j].vertix1 << "," << MST[j].vertix2 << ")";
            if (j != count - 1) {
                cout << ", ";
            }
        }
        cout << endl;

        cout << "the weight of the MST is: " << mstWeight << endl;
    }
    else {
        cout << "the graph is not connected, it has " << components << " connected components" << endl;
        cout << "the graph does not have a spanning tree because it is not connected" << endl;
    }

    if (hasCycle) {
        cout << "the graph has cycles " << endl;
    }
    else {
        cout << "the graph is acyclic" << endl;
    }

    int start, end;

    while (true) {
        cout << "enter two nodes to find a path between them or enter -1 to exit" << endl;
        cin >> start;

        if (start == -1) {
            cout << "Goodbye!" << endl;
            break;
        }

        cin >> end;

        if (start < 1 || start > V || end < 1 || end > V) {
            cout << "Invalid nodes" << endl;
            continue;
        }

        bool* visited = new bool[V + 1];
        int* path = new int[V + 1];

        for (int j = 1; j <= V; j++) {
            visited[j] = false;
        }

        int pathLength = 0;

        if (FindPathDFS(start, end, V, graph, visited, path, pathLength)) {
            cout << "output: ";
            for (int j = 0; j < pathLength; j++) {
                cout << path[j];
                if (j != pathLength - 1) {
                    cout << ", ";
                }
            }
            cout << endl;
        }
        else {
            cout << "output: no path exists" << endl;
        }

        delete[] visited;
        delete[] path;
    }

    for (int r = 0; r <= V; r++) {
        delete[] graph[r];
    }
    delete[] graph;

    delete[] MST;
    delete[] parent;
    delete[] edgeList;
}