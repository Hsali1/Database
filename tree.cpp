#include "tree.h"
#include <string_view>
#include <bitset>

Tree root = Node {
        .tag = (TagRoot | TagNode),
        .north = nullptr,
        .west = nullptr,
        .east = nullptr,
        .path = "/"
};

Node* create_node(Node* parent, std::string_view path){
    assert(parent);
    Node* n = new Node{};
    parent->west = n;
    n->tag = TagNode;
    n->north = parent;
    n->path = path;
    return n;
}

Leaf* find_last_linear(Node* parent){
    assert(parent);
    if (parent->east == nullptr) return nullptr;
    Leaf* l = parent->east;
    while(l->east){
        l = l->east;
    }
    return l;
}

Leaf* create_leaf(Node* parent, std::string_view key, std::string_view value){
    assert(parent);

    Leaf* l, *new_leaf;
    l = find_last(parent);

    new_leaf = new Leaf{};
    assert(new_leaf);

    if (l == nullptr){
        parent->east = new_leaf;
        // directly connected
    } else {
        // l is a leaf
        l->east = new_leaf;
    }

    // set values
    new_leaf->tag = TagLeaf;
    new_leaf->west = (!l) ? parent : l;
    new_leaf->key = key;
    new_leaf->value = value;

    return new_leaf;

}

int main(int argc, char * argv[]){

    Node& rootNode = std::get<Node>(root);
    // &root : 0x590d68a94160
    std::cout << "&root : " << &root << std::endl;
    // &n : 0x590d68a94160
    std::cout << "&rootNode : " << &rootNode << std::endl;
    // &n.tag : 00000011
    std::cout << "&rootNode.tag : " << std::bitset<8>(static_cast<int>(rootNode.tag)) << std::endl;
    // &n.path : /
    std::cout << "&rootNode.path : " << rootNode.path << std::endl;

    // Creating node
    Node* users = create_node(&rootNode, "/Users");
    assert(users);
    Node* login  = create_node(users, "/Users/login");
    assert(login);

    std::cout << "&users : " << users << std::endl;
    std::cout << "&login : " << login << std::endl;

    delete login;
    delete users;

    return 0;
}