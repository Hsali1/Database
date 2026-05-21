#pragma once

// #define _GNU_SOURCE

#include <unistd.h>

#include <cassert>
#include <cerrno> 
#include <iostream>
#include <string>
#include <variant>

#define TagRoot         1 /* 00 01 */
#define TagNode         2 /* 00 10 */
#define TagLeaf         4 /* 01 00 */

#define find_last(x)    find_last_linear(x)

using Tag = unsigned char;

struct Node;
struct Leaf;

// Tree can contain either Node or Leaf
using Tree = std::variant<Node, Leaf>;

struct Node {
    Tag tag;

    Node* north; // parent unless root, then itself
    Node* west;
    Leaf* east; // link to the first leaf

    std::string path;
};

struct Leaf {
    Tag tag;

    Tree* west; // left can be node or leaf
    Leaf* east; // right cannot have a node

    std::string key;
    std::string value;
};