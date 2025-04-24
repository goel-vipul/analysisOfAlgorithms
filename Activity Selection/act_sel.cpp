#include <bits/stdc++.h>
using namespace std;

struct Task {
    int start, end;
};

// Sort tasks by their ending time
bool endsEarlier(Task t1, Task t2) {
    return t1.end < t2.end;
}

// Greedy approach to select max non-overlapping activities
void selectActivities(vector<Task> tasks) {
    sort(tasks.begin(), tasks.end(), endsEarlier); // sort based on finish time

    cout << "Chosen activities:\n";
    cout << "(" << tasks[0].start << ", " << tasks[0].end << ")\n"; // pick the first one

    int lastEndTime = tasks[0].end;

    for (int i = 1; i < tasks.size(); i++) {
        if (tasks[i].start >= lastEndTime) {
            // No overlap with previous, so we pick it
            cout << "(" << tasks[i].start << ", " << tasks[i].end << ")\n";
            lastEndTime = tasks[i].end;
        }
    }
}

int main() {
    vector<Task> tasks = {
        {1, 3}, {2, 5}, {3, 9}, {0, 6}, {5, 7}, {8, 9}
    };

    selectActivities(tasks);
    return 0;
}
