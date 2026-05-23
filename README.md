# Notes: IN PROGRESS
This database sucks

### Future Improvements
*Persistent file storage
*Search functions
*Delete/update operations
*Smart pointer ownership (maybe hehe)
*Interactive shell (maybe)


Example Usage:
```
Tree* users = create_node(root, "/Users");

Tree* login = create_node(users, "/Users/login");

Tree* hassan =
    create_leaf(login,
                "Hassan",
                "abcd895qa1");

Tree* ali =
    create_leaf(login,
                "Ali",
                "aa0983iQkm");
```
current output from main:
```
&root : 0x622f66ae9eb0
&rootNode : 0x622f66ae9eb0
&rootNode.tag : 00000011
&rootNode.path : /
users.path : /Users
login.path : /Users/login
hassan_leaf.value : abcd895qa1
hassan_leaf.key : Hassan
ali_leaf.value : aa0983iQkm
ali_leaf.key : Ali
```

### How will I store data
* Binary Trees
```
    /
        /users/
        /users/ali (leaf)
        /users/hassan (leaf)
            /users/login/hassan (leaf)
                /.../.../.../
```
```
/
└── Users
    └── login
        ├── Hassan : abcd895qa1
        └── Ali : aa0983iQkm
```
### What will the tree be
```
using Tree = std::variant<Node, Leaf>;
```
### Node
```
struct Node {
    Tag tag;

    Tree* north; // parent unless root, then itself
    Tree* west;
    Tree* east; // link to the first leaf

    std::string path;
};
```
### Leaf
```
struct Leaf {
    Tag tag;

    Tree* west; // left can be node or leaf
    Tree* east; // right cannot have a node

    std::string key;
    std::string value;
};
```

