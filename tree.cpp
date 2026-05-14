#include "tree.h"
#include <string_view>

std::unique_ptr<InternalNode> create_node(InternalNode* parent, std::string_view path){
    auto node = std::make_unique<InternalNode>();
    node->parent = parent;
    node->path = path;
    return node;
}

int main(int argc, char * argv[]){

    // Create root Node
    auto root = std::make_unique<InternalNode>();
    root->parent = nullptr;
    root->path = "/";

    // Create tree
    Tree tree;
    tree.root = std::move(root);
    // std::cout << tree.root.get() << std::endl;

    // Access the actual InternalNode
    InternalNode* root_ptr =
        static_cast<InternalNode*>(tree.root.get());
    // Create node child
    root_ptr->left = create_node(root_ptr, "/Users");
    // root_ptr-> left is of type std::unique_ptr<Node>

    // Access child as InternalNode
    InternalNode* users_ptr = 
        static_cast<InternalNode*>(root_ptr->left.get());
    // Create node grandchild
    users_ptr->left = create_node(users_ptr, "/Users/login");

    std::cout << "My root is : " << tree.root->path << std::endl;
    std::cout << "ls " << tree.root->path << " : " << users_ptr->path << std::endl;
    std::cout << "ls " << users_ptr->path << " : " << users_ptr->left->path << std::endl;

    return 0;
}