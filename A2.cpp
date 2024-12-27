#include <iostream>
#include <queue>
using namespace std;

// Definition for a binary tree node
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// Function to calculate the sum of all nodes
int sumOfNodes(TreeNode* root) {
    if (!root) return 0; // Base case: If the tree is empty, return 0

    int sum = 0;
    queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        TreeNode* node = q.front();
        q.pop();
        sum += node->val; // Add the node's value to the sum

        // Add left and right children to the queue
        if (node->left) q.push(node->left);
        if (node->right) q.push(node->right);
    }
    return sum;
}

// Utility function to create a binary tree for testing
TreeNode* createSampleTree() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2, new TreeNode(4), new TreeNode(5));
    root->right = new TreeNode(3, nullptr, new TreeNode(6));
    return root;
}

int main() {
    TreeNode* root = createSampleTree();
    cout << "Sum of all nodes: " << sumOfNodes(root) << endl;
    return 0;
}
