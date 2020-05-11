/*
CSCE 315 503
Project 3
Group 17

Abdul Campos
Marshall Hobbs
McLain Johnson
Troy Fulton

Node.h - Interface for the Node class of a minimax tree

Meant to be a node in the Minimin tree class. Evaluates the
best move in the tree and keeps track of the smallest value 
in its subtree.
*/

#ifndef __NODE__        // For #including more than once
#define __NODE__

/************************************************
 *  INCLUDES
 ***********************************************/
#include <iostream>
#include <map>
#include <vector>
using namespace std;


/************************************************
 * Main Class
 ***********************************************/

class Node {
private:
    vector<Node*> children;
    bool is_min;
    int value;
    vector<int> path;          // path to the node (moves on the stack)
public:
    Node(vector<Node*> kids, bool im, int init_val, vector<int> curr_path);
    ~Node();
    Node* eval();
    vector<Node*> getChildren();
    int getValue();
    vector<int> getPath();
};

#endif