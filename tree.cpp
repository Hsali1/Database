#include "tree.h"
#include <string_view>
#include <bitset>

Tree root = Node {
        .tag   = (TagRoot | TagNode),
        .north = nullptr,
        .west  = nullptr,
        .east  = nullptr,
        .path  = "/"
};

Tree* create_node(Tree* parent, std::string_view path){
    assert(parent);
    // Node* n = new Node{};
    // parent->west = n;
    // n->tag = TagNode;
    // n->north = parent;
    // n->path = path;
    Tree* t = new Tree{
        Node{
            .tag   = TagNode,
            .north = parent,
            .west  = nullptr,
            .east  = nullptr,
            .path  = std::string(path)
        }
    };
    Node& p = std::get<Node>(*parent);
    p.west = t;

    return t;
}

Tree* find_last_linear(Tree* parent){
    assert(parent);
    // if (parent->east == nullptr) return nullptr;
    // Leaf* l = parent->east;
    // while(l->east){
    //     l = l->east;
    // }
    Node& parent_node = std::get<Node>(*parent);
    if(parent_node.east == nullptr) return nullptr;

    Tree* current = parent_node.east;

    while(true){
        Leaf& l = std::get<Leaf>(*current);
        if(l.east == nullptr) return current;
        current = l.east;
    }
}

Tree* create_leaf(Tree* parent, std::string_view key, std::string_view value){
    assert(parent);

    Tree* l = find_last(parent);

    // new_leaf = new Leaf{};
    // assert(new_leaf);
    Tree* new_leaf_tree = new Tree{
        Leaf{
            .tag   = TagLeaf,
            .west  = nullptr,
            .east  = nullptr,
            .key   = std::string(key),
            .value = std::string(value)
        }
    };

    Node& parent_node = std::get<Node>(*parent);
    if (l == nullptr){
        // parent->east = new_leaf;
        // directly connected
        parent_node.east = new_leaf_tree;
    } else {
        // l is a leaf
        Leaf& leaf_object = std::get<Leaf>(*l);
        leaf_object.east = new_leaf_tree;
    }

    // set values
    // new_leaf->west = (!l) ? parent : l;
    Leaf& new_leaf_object = std::get<Leaf>(*new_leaf_tree);
    new_leaf_object.west = (!l) ? parent : l;

    return new_leaf_tree;

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
    Tree* users = create_node(&root, "/Users");
    assert(users);
    Tree* login  = create_node(users, "/Users/login");
    assert(login);

    // Get Node objects
    Node& users_node = std::get<Node>(*users);
    Node& login_node = std::get<Node>(*login);

    std::cout << "users.path : " << users_node.path << std::endl;
    std::cout << "login.path : " << login_node.path << std::endl;

    delete login;
    delete users;

    return 0;
}