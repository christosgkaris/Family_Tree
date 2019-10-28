/*******************************************************************************
File: list.h
Author: Christos Garis
Target: List Interface File
*******************************************************************************/ 

#ifndef __LIST__ 
#define __LIST__
#include "record.h" 

typedef struct List_Node* List;

/* Function Declarations */

/* Initializes an empty list */
void CreateList(List* list);

/* Deletes a list */
void DeleteList(List* list);      

/* Inserts an empty code at the end of the list */
void InsertEmptyNodeAtEnd(List* list);         
     
/* Inserts a record in a list */         
void InsertPersonToList(List* list, int id, char* name, int parent_id, int date_of_birth, 
             char* place_of_birth, int spouse_id, int no_of_children, int* children_ids);      
             
/* Ignores character, if character = ' ' or '\n'  */                          
void ignore_ch(FILE*);

/* Prints the record with the required information */
void lookup(List list, int id, char* name);

/* Prints the record amd the relative records */
void print(List list, int id, char* name);

/* Prints the children */
void allchildren(List list, int id, char* name);

/* Prints the gchildren */
void gchildren(List list, int id, char* name);

/* Prints if ID1 is K-grandparent of ID2 */
void gKchildren(List list, int id1, int id2);

/* Prints the anscestors */
void anscestry(List list, int id);

/* Prints if ID1 is K-cousin of ID2 */
void Kcousins(List list, int id1, int id2);

/* Prints avgOffspring */
void avgOffspring(List list, int id, char* name);

/* Prints the whole list */
void print_all(List list);

#endif 
