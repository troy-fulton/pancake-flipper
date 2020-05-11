/*
CSCE 315 503
Project 3
Group 17

Abdul Campos
Marshall Hobbs
McLain Johnson
Troy Fulton

Node.cpp - Node implementation for holding tree data
*/

#include "Node.h"
#include <iostream>

using namespace std;

Node::Node(vector<Node*> kids, bool im, int init_val, vector<int> curr_path): 
    children(kids), is_min(im), value(init_val), path(curr_path) {}


Node::~Node() {
    for (Node* child: children) {
        delete child;
    }
}

vector<Node*> Node::getChildren() {
    return children;
}

int Node::getValue() {
    return value;
}

vector<int> Node::getPath() {
    return path;
}

/* returns the node which is under the current node in the tree and
contains the smallest path from the current node with the smallest
sortedness value */
Node* Node::eval() {
    // Base Case for leaf nodes
    if (children.size() == 0) {
        return this;
    }

    // Simple linear search will choose the last one with the smallest
    // path and sortedness
    Node* sel_Node = children[0]->eval();
    int sel_val = sel_Node->value;
    int shortest_path = sel_Node->getPath().size();

    // Search for the min or max
    for (int i = 1; i < (int) children.size(); ++i) {
        Node* temp_node = children[i]->eval();
        bool short_enough = ((int) temp_node->getPath().size()) <= shortest_path;
        if (temp_node->value <= sel_val && short_enough) {
            sel_val = temp_node->value;
            sel_Node = temp_node;
            shortest_path = temp_node->getPath().size();
        }
    }
    /*
    What would be done for a max node if it was a minimax tree
    cout << "Max node!!!" << endl;

    for (int i = 1; i < (int) children.size(); ++i) {
        Node* temp_node = children[i]->eval();
        bool short_enough = (int) temp_node->getPath().size() <= shortest_path;
        if (temp_node->value > sel_val && short_enough) {
            sel_val = temp_node->value;
            sel_Node = temp_node;
        }
    }
    */

    this->value = sel_val;
    return sel_Node;
}