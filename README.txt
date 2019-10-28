Details:

--------------------------------------------------------------------------------

1) main.c
Once the program starts, main prints:

Choose one of the operations below:
initialize
insert <ID><name><ParentID><DOB><BirthPlace><SpouceID><k> <kidID> ... <kidID>
load <file>
lookup <ID> || <name>
print <ID> || <name>
allchildren <ID> || <name>
gchildren <ID> || <name>
gKchildren <ID1> <ID2>
anscestry <ID>
Kcousins ??<ID1> <ID2>
avgOffspring <ID1> || <name>
exit

and the user has to select a word from the following:

initialize
insert
load
lookup
print
allchildren
gKchildren
anscestry
Kcousins
avgOffspring
exit

then the following message is printed:

You chose operation 'operation_name'

Then main gives instructions on how the user should proceed according to the 
operation. As soon as exit is chosen, the program ends.

--------------------------------------------------------------------------------

2) list.c
It is the list implementation file. To see the list type assumption, see file 
"list.gif". It's a double linked list, containing the following fields:

typedef struct List_Node {
   int NoOfPersons;
   Record person1;
   Record person2;
   List next;
   List prev;
   List person1_parents_ptr;
   List children_ptrs [10];
} List_Node;

The list consists of nodes that contain married people and non-married 
people of the pedigree tree. The algorithm to insert people in the list 
is the following:

Check the id
If id == - 1, then either the person belongs to the root of the tree, or 
it is a person married to a family member
   If parent_id == - 1
      then the person belongs to the root. The person is stored at the root 
      and at the end on the list are created as many nodes as the number of
      children that the person has.
   Otherwise
      the person has been married to a family member, and from the beginning 
      of the list, we are looking for spouse_id == id, which means that we must
      find who the person is married to. When found, the person is stored there.
Otherwise, it is a person belonging to the family, but not the root.
   From the beginning of the list, check that the id is equal to the parent_id
   of the current node, if yes, we found the father, and then must look at the 
   table children_ptrs to find the right node to store the record in, if not,
   check the next of the current node, and so on. When we find the suitable node,
   we must create at the of the list as many nodes as the number of children 
   that the person has.

Since we have entered the records in the tree, each node representes a married 
couple, has a pointer to the father of one of the spouses, pointers at the 
nodes where the children are, pointer to the previous and to the next node and 
an int that indicates how many people are in the node.

Based on the above structure, it is possible to implement the following 
operations.

--------------------------------------------------------------------------------

3) record.c
It is the record implementation file. It has the following fields:

typedef struct Record_Node {
   int id; // (1)
   char name [20]; // (2)
   int parent_id; // (3)
   int date_of_birth; // (4)
   char place_of_birth [20]; // (5)
   int spouse_id; // (6)
   int no_of_children; // (7)
   int * children_ids; // (8)
} Record_Node;

children_ids is a pointer to the table containing the childrens' ids.
It includes a record creation function, a write value assignment function,
a function to retrieve record values and a function to print record fields.

--------------------------------------------------------------------------------

4) list.h
It is the list interface file.

--------------------------------------------------------------------------------

5) record.h
It is the recording interface file.

--------------------------------------------------------------------------------

6) README.txt
This file.

--------------------------------------------------------------------------------

7) list.gif
Visual representation of the structure of the list.

--------------------------------------------------------------------------------

-To Execute:

a) For immediate compiling, give the following command:

 % gcc -o exe main.c list.c record.c
 % ./exe

b) For separate compilation:
 % gcc -c main.c
 % gcc -c list.c
 % gcc -c record.c
The object files (.o) are now created. Then:
 % gcc -o exe main.o list.o record.o
Exe executable file created:
 % ./exe