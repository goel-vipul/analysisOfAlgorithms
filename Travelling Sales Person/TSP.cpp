#include <iostream>
#include <vector>
#include <climits>
using namespace std;

const int CITY_COUNT = 4;
const int INF = INT_MAX;

int shortestTourCost = INF;  // Stores the minimum path cost found
vector<int> bestRoute;       // Stores the path with minimum cost

// Recursive function to explore all possible city visits
void findShortestRoute(vector<vector<int>> &distances, vector<bool> &visited, vector<int> &currentPath, int currentCity, int level, int currentCost) {
    if (level == CITY_COUNT) {
        // Add cost to return to starting city
        if (distances[currentCity][0] != 0) {
            int totalCost = currentCost + distances[currentCity][0];
            if (totalCost < shortestTourCost) {
                shortestTourCost = totalCost;
                bestRoute = currentPath;
                bestRoute.push_back(0);  // Complete the cycle
            }
        }
        return;
    }

    for (int nextCity = 0; nextCity < CITY_COUNT; nextCity++) {
        // Proceed if the next city hasn't been visited and there's a route
        if (!visited[nextCity] && distances[currentCity][nextCity] != 0) {
            visited[nextCity] = true;
            currentPath.push_back(nextCity);

            findShortestRoute(distances, visited, currentPath, nextCity, level + 1, currentCost + distances[currentCity][nextCity]);

            // Backtrack to try a different route
            visited[nextCity] = false;
            currentPath.pop_back();
        }
    }
}

int main() {
    // Distance matrix where distances[i][j] is the cost to travel from city i to j
    vector<vector<int>> distances = {
        {0, 10, 15, 20},
        {10, 0, 35, 25},
        {15, 35, 0, 30},
        {20, 25, 30, 0}
    };

    vector<bool> visited(CITY_COUNT, false);
    vector<int> currentPath;

    visited[0] = true;          // Start from city 0
    currentPath.push_back(0);   // Start path from city 0

    findShortestRoute(distances, visited, currentPath, 0, 1, 0);

    cout << "Minimum travel cost: " << shortestTourCost << endl;
    cout << "Best route: ";
    for (int city : bestRoute) {
        cout << city << " ";
    }
    cout << endl;

    return 0;
}
