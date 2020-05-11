/*
CSCE 315 503
Project 3
Group 17

Abdul Campos
Marshall Hobbs
McLain Johnson
Troy Fulton

MMTree.h - Interface for the Minimax Tree Implementation

This templated Class depends on the Node class and implements a "minimin" tree
(a mimimax tree with all min nodes). It is templated because it takes the
utility function as a template argument so that it can determine the leaf nodes.
*/

#ifndef __MMTREE__        // For #including more than once
#define __MMTREE__

/************************************************
 *  INCLUDES
 ***********************************************/
#include <iostream>
#include <map>
#include "Node.h"
using namespace std;


/************************************************
 * Main Class
 ***********************************************/

template <typename T>
class MMTree {
private:
    Node* root;
    int depth;
    Node* make_tree(T func, int d, int num_children, bool is_minimum, vector<int> path_so_far);
    void printTree(Node* tree_root, int tabs);
public:
    MMTree<T>(T func, int d, int num_children);
    ~MMTree<T>();
    Node* eval();
    void print();
    int bestMove();
};

/* Constructs the tree recursively. Each node has num_cildren - 1 children because
choosing the top pancake is always unwise. Also, the tree stops when a full solution
is found. */
template <typename T>
Node* MMTree<T>::make_tree(T func, int d, int num_children, bool is_minimum, vector<int> path_so_far) {

    // For depth 0, return a terminal node with no children
    if (d == 0) {
        vector<Node*> no_kids;
        return new Node(no_kids, is_minimum, func(path_so_far), path_so_far);
    }

    // Recursively:
    vector<Node*> children;
    for (int i = 0; i < num_children - 1; i++) {
        // Get a copy of the path so far and update for this node
        vector<int> temp_path = path_so_far;
        temp_path.push_back(i);
        if (func(temp_path) == -10) {    // signal meaning the solution ends the game- make a terminal node
            children.push_back(make_tree(func, 0, num_children, is_minimum, temp_path));
        }
        else {
            children.push_back(make_tree(func, d-1, num_children, is_minimum, temp_path));
        }
    }

    // Initialize root to 0 (doesn't matter):
    return new Node(children, is_minimum, 0, path_so_far);
}

template <typename T>
MMTree<T>::MMTree(T func, int d, int num_children) : depth(d) {
    // The root node should always be a min tree:
    vector<int> path_to_track;
    root = make_tree(func, d, num_children, true, path_to_track);
}

template <typename T>
MMTree<T>::~MMTree() {
    // Desctruction done recursively as well
    delete root;
}

template <typename T>
Node* MMTree<T>::eval() {
    return root->eval();
}

template <typename T>
int MMTree<T>::bestMove() {
    // Evaluate the tree to find the best move
    vector<int> best_path = root->eval()->getPath();
    return best_path[0];
}

/* purely for debugging */
template<typename T>
void MMTree<T>::print() {

    cout << "Minimax Tree:" << "\n=============\n\n";

    printTree(root, 0);

    cout << "\n\n=============\n";
}

/* recursive helper for print() */
template <typename T>
void MMTree<T>::printTree(Node* tree_root, int tabs) {
    // Print tabs
    for (int i = 0; i < tabs; i++)
        cout << "\t";
    
    // Print the path
    vector<int> temp_path = tree_root->getPath();
    cout << "[ ";
    for (int step : temp_path)
        cout << step << " ";
    cout << "]\n";

    // Print each of its children with one more tab
    for (Node* child : tree_root->getChildren())
        printTree(child, tabs + 1);
}

#endif