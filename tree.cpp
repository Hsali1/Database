#include "tree.h"
#include <string_view>
#include <bitset>

Tree* root = new Tree{
     Node {
        .tag   = (TagRoot | TagNode),
        .north = nullptr,
        .west  = nullptr,
        .east  = nullptr,
        .path  = "/"
    }
};

Tree* create_node(Tree* parent, std::string_view path){
    assert(parent);

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
        // directly connected
        parent_node.east = new_leaf_tree;
    } else {
        // l is a leaf
        Leaf& leaf_object = std::get<Leaf>(*l);
        leaf_object.east = new_leaf_tree;
    }

    // set values
    Leaf& new_leaf_object = std::get<Leaf>(*new_leaf_tree);
    new_leaf_object.west = (!l) ? parent : l;

    return new_leaf_tree;

}

void destroy_everything(Tree* current){
    if (!current) return;

    // check if current is a Node
    if (std::holds_alternative<Node>(*current)){

        // Get the Node object
        Node& n = std::get<Node>(*current);

        // check if any children Node(s)
        if (n.east) destroy_everything(n.east);
        if (n.west) destroy_everything(n.west);
    } else {

        Leaf& l = std::get<Leaf>(*current);
        if (l.east) destroy_everything(l.east);
    }

    delete current;
}

Tree* find_leaf(Tree* parent, std::string_view key){

    if (!parent) return nullptr;

    Tree* current;

    // check if current is a Node
    if (std::holds_alternative<Node>(*parent)){

        Node& parent_node = std::get<Node>(*parent);

        current = parent_node.east;

        while (current){
            Leaf& n = std::get<Leaf>(*current);

            if (n.key == key) return current;

            current = n.east;
        }
        
        Tree* result = find_leaf(parent_node.west, key);

        if(result) return result;

    } else {
        current = parent;
        while (current){
            Leaf& l = std::get<Leaf>(*current);

            if (l.key == key) return current;

            current = l.east;
        }
    }

    return nullptr;
}

bool delete_leaf(Tree* parent, std::string_view key){

    if (!parent) return false;

    Tree* target_leaf = find_leaf(parent, key);
    if (!target_leaf){
        std::cout << "Leaf does not exist..." << std::endl;
        return false;
    }

    // Get address of previous
    Leaf& target_leaf_object = std::get<Leaf>(*target_leaf);
    Tree* target_leaf_object_previous_tree = target_leaf_object.west;
    Tree* target_leaf_object_next_tree = target_leaf_object.east;

    if (std::holds_alternative<Node>(*target_leaf_object_previous_tree)){
        // Get previous Object
        Node& previous_object = std::get<Node>(*target_leaf_object_previous_tree);
        previous_object.east = target_leaf_object_next_tree;
    } else {
        // It is a leaf, get Leaf object
        Leaf& previous_object = std::get<Leaf>(*target_leaf_object_previous_tree);
        previous_object.east = target_leaf_object_next_tree;
    }

    std::cout << "Deleted record with ";
    std::cout << "key = " << target_leaf_object.key << ", ";
    std::cout << "value = " << target_leaf_object.value << std::endl;

    target_leaf_object.east = nullptr;
    target_leaf_object.west = nullptr;
    delete target_leaf;

    return true;
}

void pretty_print(Tree* current, std::string_view prefix=""){
    if (!current) return;
    if (std::holds_alternative<Node>(*current)){
        // Get Node object
        Node& n = std::get<Node>(*current);
        // Check if this is the last object
        bool is_last = (n.west == nullptr);
        std::cout << prefix;
        std::cout << (is_last ? "└──" : "├──");
        std::cout << n.path << std::endl;
        std::string new_prefix = std::string(prefix) + (is_last ? "   " : "│    ");
        pretty_print(n.east, new_prefix);
        pretty_print(n.west, new_prefix);
    } else {
        // Get Node object
        Leaf& l = std::get<Leaf>(*current);
        // Check if this is the last object
        bool is_last = (l.east == nullptr);
        std::cout << prefix;
        std::cout << (is_last ? "└──" : "├──");
        std::cout << l.key << " : ";
        std::cout << l.value << std::endl;
        std::string new_prefix = std::string(prefix) + (is_last ? "│   " : "    ");
        pretty_print(l.east, new_prefix);
        // pretty_print(l.west);
    }
}

int main(int argc, char * argv[]){

    Node& rootNode = std::get<Node>(*root);
    // &root : 0x590d68a94160
    std::cout << "&root : " << root << std::endl;
    // &n : 0x590d68a94160
    std::cout << "&rootNode : " << &rootNode << std::endl;
    // &n.tag : 00000011
    std::cout << "&rootNode.tag : " << std::bitset<8>(static_cast<int>(rootNode.tag)) << std::endl;
    // &n.path : /
    std::cout << "&rootNode.path : " << rootNode.path << std::endl;

    // Creating node
    Tree* users = create_node(root, "/Users");
    assert(users);
    Tree* login  = create_node(users, "/Users/login");
    assert(login);

    // Get Node objects
    Node& users_node = std::get<Node>(*users);
    Node& login_node = std::get<Node>(*login);

    // Print Node information
    std::cout << "users.path : " << users_node.path << std::endl;
    std::cout << "login.path : " << login_node.path << std::endl;

    // Creating Leafs
    Tree* hassan = create_leaf(login, "Hassan", "abcd895qa1");
    assert(hassan);
    Tree* ali = create_leaf(login, "Ali", "aa0983iQkm");
    assert(ali);
    // Tree* leaf_2;

    // Get Leaf objects
    Leaf& hassan_leaf = std::get<Leaf>(*hassan);
    Leaf& ali_leaf = std::get<Leaf>(*ali);
    
    // Print Leaf information
    std::cout << "hassan_leaf.value : " << hassan_leaf.value << std::endl;
    std::cout << "hassan_leaf.key : " << hassan_leaf.key << std::endl;

    std::cout << "ali_leaf.value : " << ali_leaf.value << std::endl;
    std::cout << "ali_leaf.key : " << ali_leaf.key << std::endl;

    // Find_leaf Function
    Tree* find_data = find_leaf(root, "Hassan");
    if (find_data){
        Leaf& find_data_object = std::get<Leaf>(*find_data);
        std::cout << "Found Leaf : " << find_data_object.key << std::endl;
        std::cout << "Value : " << find_data_object.value << std::endl;
    } else {
        std::cout << "could not find Leaf" << std::endl;
    }


    find_data = find_leaf(root, "Fire");
    if (find_data){
        Leaf& find_data_object = std::get<Leaf>(*find_data);
        std::cout << "Found Leaf : " << find_data_object.key << std::endl;
        std::cout << "Value : " << find_data_object.value << std::endl;
    } else {
        std::cout << "could not find Leaf" << std::endl;
    }

    // Check delete_leaf function
    // delete_leaf(root, "Hassan");
    // delete_leaf(root, "Jimbo");

    // find_data = find_leaf(root, "Hassan");
    // if (find_data){
    //     Leaf& find_data_object = std::get<Leaf>(*find_data);
    //     std::cout << "Found Leaf : " << find_data_object.key << std::endl;
    //     std::cout << "Value : " << find_data_object.value << std::endl;
    // } else {
    //     std::cout << "could not find Leaf" << std::endl;
    // }

    // Check pretty print
    pretty_print(root);

    destroy_everything(root);

    return 0;
}