# TreeDB
A custom hierarchical key-value storage engine written in C++20.

TreeDB started as an experiment to better understand how hierarchical storage systems and databases work internally.

The original goal was simple: create a tree structure that could store data in a way similar to folders and records. As the project grew, I ended up exploring recursive traversal, dynamic memory management, custom data structures, and runtime type handling with C++.

The project uses a custom tree structure built around `Node` and `Leaf` objects and relies on `std::variant` to safely represent different object types at runtime.

I wasn't trying to build a full SQL database. The main purpose of this project was to better understand how hierarchical storage systems work and get more hands-on experience with:

- recursive traversal
- dynamic memory allocation
- memory ownership
- tree structures
- search and deletion algorithms
- C++20 features such as `std::variant`

---

## Current Features

- Dynamic node creation
- Dynamic leaf creation
- Recursive traversal
- Recursive memory cleanup
- Search functionality
- Record deletion
- Pretty tree visualization
- Hierarchical key-value storage
- Runtime-safe type handling using `std::variant`

---

## Example Structure

```text
/
└── Users
    └── login
        ├── Hassan : abcd895qa1
        └── Ali : aa0983iQkm
```

---

## Example Usage

```cpp
Tree* users =
    create_node(root, "/Users");

Tree* login =
    create_node(users, "/Users/login");

Tree* hassan =
    create_leaf(
        login,
        "Hassan",
        "abcd895qa1"
    );

Tree* ali =
    create_leaf(
        login,
        "Ali",
        "aa0983iQkm"
    );
```

---

## Design Overview

The project revolves around a generic Tree object:

```cpp
using Tree = std::variant<Node, Leaf>;
```

Instead of unsafe casts and unions, `std::variant` provides type safety:

- Tree may contain a `Node`
- Tree may contain a `Leaf`
- Access requires explicit extraction using `std::get<>`

Example:

```cpp
Node& n =
    std::get<Node>(*tree_ptr);

Leaf& l =
    std::get<Leaf>(*tree_ptr);
```

---

## Node Structure

Nodes represent directories or hierarchical containers.

```cpp
struct Node {
    Tag tag;

    Tree* north;
    Tree* west;
    Tree* east;

    std::string path;
};
```

Current behavior:

| Member | Purpose |
|----------|----------|
| north | Parent node |
| west | Child node chain |
| east | First leaf |

---

## Leaf Structure

Leaf objects represent stored records.

```cpp
struct Leaf {
    Tag tag;

    Tree* west;
    Tree* east;

    std::string key;
    std::string value;
};
```

Current behavior:

| Member | Purpose |
|----------|----------|
| west | Parent node or previous leaf |
| east | Next leaf |
| key | Record identifier |
| value | Stored value |

---

## Function Breakdown

### create_node()

Creates a new node and connects it to its parent.

Purpose:

- allocate memory
- initialize Node data
- establish parent-child relationships

---

### create_leaf()

Creates a key/value record under a node.

Purpose:

- create new records
- connect leaves together as a linked chain
- maintain parent relationships

---

### find_leaf()

Recursively searches the hierarchy for a leaf matching a key.

Purpose:

- traverse node chains
- traverse linked leaf lists
- return matching record

---

### delete_leaf()

Deletes a record and reconnects neighboring leaves.

Purpose:

- maintain linked structure integrity
- remove orphaned nodes

---

### destroy_everything()

Recursively traverses and frees all allocated memory.

Purpose:

- avoid memory leaks
- recursively clean tree structures

---

### pretty_print()

Recursively visualizes the structure.

Example output:

```text
/
└── Users
    └── login
        ├── Hassan : abcd895qa1
        └── Ali : aa0983iQkm
```

Purpose:

- visualize hierarchy
- debug structure relationships

---

## Design Notes

### Why `std::variant`?

The original implementation idea used unions and casting similar to C.

```cpp
union Tree{
    Node n;
    Leaf l;
};
```

While it worked initially I later had issues because I had std::string and that was having issues with Union's non-trivial constructor stuff.

I also experimented with inheritance and polymorphism:

```cpp
struct Node {
    virtual bool is_leaf() = 0;
};

struct InternalNode : Node {};
struct LeafNode : Node {};
```

The idea was to allow generic pointers:

```cpp
Node* child;
```

While this solved some problems from the union approach, I quickly ran into another issue: I still had to repeatedly determine the actual object type before using it.

This led to patterns such as:

```cpp
LeafNode* l =
    dynamic_cast<LeafNode*>(node);

InternalNode* i =
    dynamic_cast<InternalNode*>(node);
```

The design worked, but it started feeling similar to manually managing tags and casts. I wanted something safer and more explicit, which eventually led me to `std::variant`.

The biggest benefit was avoiding invalid casts and forcing myself to explicitly handle whether a `Tree` object contained a `Node` or `Leaf`.

One downside is that it made the code more verbose because objects frequently need to be extracted:

```cpp
Node& n = std::get<Node>(*tree_ptr);
Leaf& l = std::get<Leaf>(*tree_ptr);
```

Even though this added some extra complexity, it helped me better understand ownership and runtime type handling.

---

### Why raw pointers?

Currently the project intentionally uses raw pointers:

```cpp
Tree*
```

Purpose:

- understand ownership manually
- practice dynamic memory management
- better understand what smart pointers solve

Future versions may transition to:

```cpp
std::unique_ptr<Tree>
```

---

## Known Limitations

Current node relationships behave as linked chains:

```text
root
    ↓
Users
    ↓
login
```

instead of:

```text
root
├── Users
├── Admin
└── Settings
```

Future versions will likely replace:

```cpp
Tree* west;
```

with:

```cpp
std::vector<Tree*> children;
```

to support multiple child nodes.

---

## Future Improvements

- Persistent file storage
- Interactive shell
- Smart pointer ownership
- Better node relationship design
- Multi-child node support
- Record update functionality
- Save/load database state

---

## Build

```bash
make
./TreeDB
```

---

## What I Learned

This project was primarily built as an exploration of:

Working on this project helped me get more comfortable with:

- recursive traversal
- memory ownership
- designing custom data structures
- using `std::variant`
- thinking about design tradeoffs

I also ran into limitations that turned into learning opportunities, such as the current single-child node chain design.