# Notes:

### How will I store data
* Binary Trees
```
                Root
                  |
             /usr/
                  |
               user/login
```
```
Root
├── /user (folder)
│   └── /user/login (subfolder)
│
├── folder
├── folder
├── folder
├── folder
└── folder

    ├── file (leafs)
    ├── file
    └── file
```
### What will the tree be
```
struct Tree {
    Node* root;
};
```
### Node
```
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
```
### Leaf
```
struct LeafNode : Node {
    std::string key;
    std::string value;
    boos is_leaf() const override {
        return true;
    }
};
```