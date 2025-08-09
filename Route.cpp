#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <limits>
using namespace std;

const int INF = numeric_limits<int>::max();

void printMatrix(const vector<vector<int>> &matrix) {
    for (const auto &row : matrix) {
        for (const auto &val : row) {
            if (val == INF)
                cout << "INF\t";
            else
                cout << val << "\t";
        }
        cout << endl;
    }
}

void floydWarshall(vector<vector<int>> &dist, vector<vector<int>> &next) {
    int n = dist.size();
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    next[i][j] = next[i][k];
                }
            }
        }
    }
}

vector<int> reconstructPath(int u, int v, const vector<vector<int>> &next) {
    if (next[u][v] == -1)
        return {};

    vector<int> path;
    int current = u;
    while (current != v) {
        path.push_back(current);
        current = next[current][v];
    }
    path.push_back(v);
    return path;
}

void addNode(vector<vector<int>> &dist, vector<vector<int>> &next, map<string, int> &cityToIndex, vector<string> &indexToCity, const string &city) {
    cityToIndex[city] = indexToCity.size();
    indexToCity.push_back(city);

    int n = dist.size();
    for (auto &row : dist) row.push_back(INF);
    for (auto &row : next) row.push_back(-1);

    dist.push_back(vector<int>(n + 1, INF));
    next.push_back(vector<int>(n + 1, -1));

    dist[n][n] = 0;
}

void removeNode(vector<vector<int>> &dist, vector<vector<int>> &next, map<string, int> &cityToIndex, vector<string> &indexToCity, const string &city) {
    int node = cityToIndex[city];
    dist.erase(dist.begin() + node);
    next.erase(next.begin() + node);

    for (auto &row : dist) row.erase(row.begin() + node);
    for (auto &row : next) row.erase(row.begin() + node);

    cityToIndex.erase(city);
    indexToCity.erase(indexToCity.begin() + node);

    for (auto &pair : cityToIndex) {
        if (pair.second > node) pair.second--;
    }
}

void updateEdge(vector<vector<int>> &dist, vector<vector<int>> &next, int u, int v, int weight) {
    dist[u][v] = weight;
    next[u][v] = (weight == INF ? -1 : v);
}

int main() {
    cout << "\t\t\t\t\t WELCOME TO OUR PROJECT \n";
    cout<< "\t\t\t Smart Route Planner Using All-Pair Shortest Path Algorithms!" << endl;
    cout<<endl;
    int n;
    cout << "Enter the number of locations: ";
    cin >> n;

    map<string, int> cityToIndex;
    vector<string> indexToCity;

    cout << "Enter the city names:\n";
    for (int i = 0; i < n; i++) {
        string city;
        cin >> city;
        cityToIndex[city] = i;
        indexToCity.push_back(city);
    }

    vector<vector<int>> dist(n, vector<int>(n, INF));
    vector<vector<int>> next(n, vector<int>(n, -1));

    cout << "Enter the distance matrix (-1 for INF):\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> dist[i][j];
            if (dist[i][j] == -1) {
                dist[i][j] = INF;
            }
            if (i != j && dist[i][j] != INF) {
                next[i][j] = j;
            }
        }
    }

    floydWarshall(dist, next);

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Display shortest path matrix\n";
        cout << "2. Query shortest path between two locations\n";
        cout << "3. Add a new location\n";
        cout << "4. Remove a location\n";
        cout << "5. Update an edge\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;

        if (choice == 1) {
            cout << "Shortest distance matrix:\n";
            printMatrix(dist);
        } else if (choice == 2) {
            string source, destination;
            cout << "Enter the source and destination city names: ";
            cin >> source >> destination;

            if (cityToIndex.count(source) == 0 || cityToIndex.count(destination) == 0) {
                cout << "Invalid city names.\n";
                continue;
            }

            int u = cityToIndex[source], v = cityToIndex[destination];
            if (dist[u][v] == INF) {
                cout << "No path exists between " << source << " and " << destination << ".\n";
            } else {
                vector<int> path = reconstructPath(u, v, next);
                cout << "Shortest path: ";
                for (int i = 0; i < path.size(); i++) {
                    cout << indexToCity[path[i]];
                    if (i != path.size() - 1) cout << " -> ";
                }
                cout << "\nDistance: " << dist[u][v] << endl;
            }
        }
        else if (choice == 3) {
            string city;
            cout << "Enter the new city name: ";
            cin >> city;

            if (cityToIndex.count(city)) {
                cout << "City already exists.\n";
                continue;
            }

            addNode(dist, next, cityToIndex, indexToCity, city);

            cout << "Enter distances from " << city << " to other cities (-1 for INF):\n";
            for (int i = 0; i < dist.size() - 1; i++) {
                int weight;
                cin >> weight;
                if (weight == -1) weight = INF;
                updateEdge(dist, next, dist.size() - 1, i, weight);
            }

            cout << "Enter distances from other cities to " << city << " (-1 for INF):\n";
            for (int i = 0; i < dist.size() - 1; i++) {
                int weight;
                cin >> weight;
                if (weight == -1) weight = INF;
                updateEdge(dist, next, i, dist.size() - 1, weight);
            }

            floydWarshall(dist, next);
            cout << "New location added.\n";
            cout << "Updated Shortest Distance Matrix:\n";
            printMatrix(dist);
        } else if (choice == 4) {
            string city;
            cout << "Enter the city name to remove: ";
            cin >> city;

            if (cityToIndex.count(city) == 0) {
                cout << "City not found.\n";
                continue;
            }

            removeNode(dist, next, cityToIndex, indexToCity, city);
            floydWarshall(dist, next);
            cout << "Location removed.\n";
            cout << "Updated Shortest Distance Matrix:\n";
            printMatrix(dist);
        } else if (choice == 5) {
            string source, destination;
            int weight;
            cout << "Enter the source, destination city names, and weight (-1 for INF): ";
            cin >> source >> destination >> weight;

            if (cityToIndex.count(source) == 0 || cityToIndex.count(destination) == 0) {
                cout << "Invalid city names.\n";
                continue;
            }

            int u = cityToIndex[source], v = cityToIndex[destination];
            if (weight == -1) weight = INF;
            updateEdge(dist, next, u, v, weight);
            floydWarshall(dist, next);
            cout << "Edge updated.\n";
            cout << "Updated Shortest Distance Matrix:\n";
            printMatrix(dist);
        } else if (choice == 6) {
            cout << "\t\t\t-------Thank You-------\n";
            break;
        } else {
            cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}

