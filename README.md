# Notes: IN PROGRESS

current output from main:

&root : 0x5abb35c79160
&rootNode : 0x5abb35c79160
&rootNode.tag : 00000011
&rootNode.path : /
users.path : /Users
login.path : /Users/login
hassan_leaf.value : abcd895qa1
hassan_leaf.key : Hassan

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
    /
        /users/
        /users/ali (leaf)
        /users/hassan (leaf)
            /users/login/hassan (leaf)
                /.../.../.../
```
### What will the tree be
```
using Tree = std::variant<Node, Leaf>;
```
### Node
```
struct Node {
    Tag tag;

    Node* north; // parent unless root, then itself
    Node* west;
    Leaf* east; // link to the first leaf

    std::string path;
};
```
### Leaf
```
struct Leaf {
    Tag tag;

    Tree* west; // left can be node or leaf
    Leaf* east; // right cannot have a node

    std::string key;
    std::string value;
};
```

