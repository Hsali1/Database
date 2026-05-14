#pragma once

// #define _GNU_SOURCE

#include <unistd.h>

#include <cassert>
#include <cerrno> 
#include <iostream>
#include <string>

/*
/
    /users/
        /users/login/
            /.../.../.../
    
*/

struct Node {
    Node* parent;
    std::string path; // will contain entire path
    virtual ~Node() = default;
    virtual bool is_leaf() const = 0;
};

struct InternalNode : Node {
    Node* left;
    Node* right;
    bool is_leaf() const override {
        return false;
    }
};

struct LeafNode : Node {
    std::string key;
    std::string value;
    bool is_leaf() const override {
        return true;
    }
};

struct Tree {
    Node* root;
};