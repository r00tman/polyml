Poly Markup Language
======

Compact and fast file format representing an universal tree containing binary data.

Format
======

File consists of nodes.
Every node is full-fledged and can be written in seperate files.

Node consists of 3 fields: 
 - full size in bytes
 - size of children in bytes
 - children (as a continous list of nodes)

Use
======

Library provides one class: pml_node in namespace pml.

For example, if we want to write node with data "hi" to file test.pml we do this thing:
```cpp
pml_node tree;                  // created a node
tree.set_data("hi");            // set data

ofstream out("test.pml", 
             ios_base::binary); // created a file
tree.write(out);                // written the node
out.close();                    // closed the file
```

If we want to add childs with data "1", "2" and "3" we need to add simple block to previous code:
```cpp
pml_node tree;                  // created a node
tree.set_data("hi");            // set data

////////////////////////////////////////////
tree.add_child(new pml_node("1"));
tree.add_child(new pml_node("2"));
tree.add_child(new pml_node("3"));
////////////////////////////////////////////

ofstream out("test.pml", 
             ios_base::binary); // created a file
tree.write(out);                // written the node
out.close();                    // closed the file
```
