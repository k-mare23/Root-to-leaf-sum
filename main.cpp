#include <iostream>
#include <sstream>
#include "Queue.h"
using namespace std;
struct treeNode {
    int value;
    int track = 0; //to track if node visited yet or not
    treeNode* left = NULL;
    treeNode* right = NULL;
};
void insert(treeNode*& node, int value) {
    treeNode* n = new treeNode(); //creating our new node
    n->value = value;
    n->left = n->right = NULL;
   
    Queue<treeNode* > q;
    q.insert(node); //insert the root node in front of queue
    
    while (!q.isEmpty()) { //finding a spot to insert our newly created node in
        treeNode* temp = q.firstElement(); //get first item to see if can insert into left or right spot
        q.del();
        if (temp->left == NULL) { //insert as left child
            temp->left = n;
            return;
        }
        else if (temp->right == NULL){ //insert as right child
            temp->right = n;
            return;
        }
        else { //puts left and right children at the end of queue so can work on the next element in queue
            q.insert(temp->left);
            q.insert(temp->right);
        }
    }
}

void postOrder(treeNode* node) { //just to see if tree outputs correctly
    if (node == NULL)
        return;
    postOrder(node->left);
    postOrder(node->right);
    cout << node->value << " ";
}

bool foundPath = false; //variable to keep track of if we find a path or not
int sum = 0; //variable to keep track of the sum of the path so far
void rootToLeaf(treeNode* node, int sumToFind) {
    if (node == NULL || foundPath) {
        return;
    }
    sum += node->value; //adding nodes together on path
    node->track += 1; //updating count of the node; 1 means node has already been visited
    rootToLeaf(node->left, sumToFind); //search all left side
    if ((node->left == NULL && node->right == NULL)) { //reached a leaf or have visited both of the children of the node already
        if (node->right != NULL){
            if (node->right->track == 1) { //if visited all the children nodes already
                sum -= node->value; //subtract parent node value from total sum
            }
        }
        else if (sum == sumToFind) { //found a path that equals the sum from root to leaf
            foundPath = true;
            return;
        }
        else {
            sum -= node->value; //subtract current node's value from sum
        }
    }
    rootToLeaf(node->right, sumToFind); //search right side/subtree 
}
int main() {
    treeNode* root = NULL;
    string valuesList;
    getline(cin, valuesList);
    string value;
    stringstream ss(valuesList);
    int sumToFind;
    cin >> sumToFind;
    while (ss >> value) {
        if (value == "null") { //for NULL values just insert 0
            insert(root, 0);
        }
        else {
            int data = stoi(value);
            if (root == NULL) { //create our root node first
                root = new treeNode();
                root->value = data;
                root->left = root->right = NULL;
            }
            else {
                insert(root, data); //insert rest of values into tree
            }
        }
    }
    //postOrder(root);
    //cout << endl;
    rootToLeaf(root, sumToFind); //find root to leaf path with this function
    if (!foundPath) {
        cout << "0" << endl; //couldn't find a root to leaf path
    }
    else {
        cout << "1" << endl; //found a path
    }
    return 0;
}
