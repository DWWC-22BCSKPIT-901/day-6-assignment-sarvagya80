#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
using namespace std;

class Solution {
public:
    int countPossibleRoots(int n, vector<vector<int>>& edges, vector<vector<int>>& guesses, int k) {
        // Adjacency list representation of the tree
        vector<vector<int>> tree(n);
        for (const auto& edge : edges) {
            tree[edge[0]].push_back(edge[1]);
            tree[edge[1]].push_back(edge[0]);
        }

        // Store guesses as a set for quick lookup
        unordered_set<string> guessSet;
        for (const auto& guess : guesses) {
            guessSet.insert(to_string(guess[0]) + "," + to_string(guess[1]));
        }

        // Step 1: Calculate the number of correct guesses assuming node 0 is the root
        int initialCorrectGuesses = 0;
        dfs(0, -1, tree, guessSet, initialCorrectGuesses);

        // Step 2: Use rerooting to calculate correct guesses for other possible roots
        int possibleRoots = 0;
        reroot(0, -1, tree, guessSet, initialCorrectGuesses, k, possibleRoots);

        return possibleRoots;
    }

private:
    void dfs(int node, int parent, vector<vector<int>>& tree, unordered_set<string>& guessSet, int& correctGuesses) {
        for (int neighbor : tree[node]) {
            if (neighbor == parent) continue;
            if (guessSet.count(to_string(node) + "," + to_string(neighbor))) {
                correctGuesses++;
            }
            dfs(neighbor, node, tree, guessSet, correctGuesses);
        }
    }

    void reroot(int node, int parent, vector<vector<int>>& tree, unordered_set<string>& guessSet, int currentCorrectGuesses, int k, int& possibleRoots) {
        // Check if the current node satisfies the condition
        if (currentCorrectGuesses >= k) {
            possibleRoots++;
        }

        // Reroot the tree
        for (int neighbor : tree[node]) {
            if (neighbor == parent) continue;

            // Adjust the count of correct guesses for rerooting
            int newCorrectGuesses = currentCorrectGuesses;
            if (guessSet.count(to_string(node) + "," + to_string(neighbor))) {
                newCorrectGuesses--;
            }
            if (guessSet.count(to_string(neighbor) + "," + to_string(node))) {
                newCorrectGuesses++;
            }

            reroot(neighbor, node, tree, guessSet, newCorrectGuesses, k, possibleRoots);
        }
    }
};

int main() {
    Solution solution;

    // Example 1
    vector<vector<int>> edges = {{0, 1}, {1, 2}, {1, 3}};
    vector<vector<int>> guesses = {{1, 2}, {2, 3}};
    int k = 1;

    int result = solution.countPossibleRoots(4, edges, guesses, k);
    cout << "Number of possible roots: " << result << endl;

    return 0;
}
