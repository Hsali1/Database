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
union tree{
    struct node n;
    struct leaf l;
}
```
### what is a node
```
struct node {
    struct node* parent;
    struct node* left;
    struct leaf* right;
}
```