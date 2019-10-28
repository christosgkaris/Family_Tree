/*******************************************************************************
File: record.c
Author: Christos Garis
Target: Record Implemantation File
*******************************************************************************/ 

#include <stdio.h>
#include <stdlib.h>
#include "record.h"

typedef struct Record_Node{
   int id;  //(1)
   char name[20];  //(2)
   int parent_id;  //(3)
   int date_of_birth;  //(4)
   char place_of_birth[20];  //(5)
   int spouse_id;  //(6)
   int no_of_children;  //(7)
   int* children_ids;  //(8)         
}Record_Node;

/* Function Definitions */

Record create_record()
{
   int i;    
   Record record = (Record)malloc(sizeof(Record_Node));
   /*Initialization*/
   record->id = -1;  //(1)
   for(i=0;i<20;i++)
      record->name[i] = ' ';  //(2)
   record->parent_id = -1;  //(3)
   record->date_of_birth = -1;  //(4) 
   for(i=0;i<20;i++)
      record->place_of_birth[i] = ' ';  //(5)
   record->spouse_id = -1;  //(6)
   record->no_of_children = 0;  //(7)
   record->children_ids = NULL;  //(8)    The allocation will be done in another function, 
                                // because we don't know how many children the record has. 
   return record;   
}


void set_record(Record* record, int id, char* name, int parent_id, int date_of_birth, 
        char* place_of_birth, int spouse_id, int no_of_children, int* children_ids)
{
   int i;  
   (*record)->id = id;  //(1)   
   for(i=0;i<20;i++)
      (*record)->name[i] = name[i];  //(2)
   (*record)->parent_id = parent_id;  //(3)
   (*record)->date_of_birth = date_of_birth;  //(4)
   for(i=0;i<20;i++)
      (*record)->place_of_birth[i] = place_of_birth[i];  //(5)
   (*record)->spouse_id = spouse_id;  //(6)
   (*record)->no_of_children = no_of_children;  //(7)
   
   (*record)->children_ids = (int*)malloc(((*record)->no_of_children) * sizeof(int));
   for(i=0;i<no_of_children;i++)
      (*record)->children_ids[i] = children_ids[i];  //(8)
}


int get_record_id(Record record)
{
   return record->id; 
}


char* get_record_name(Record record)
{
   return record->name;   
}


int get_record_parent_id(Record record)
{
   return record->parent_id; 
}


int get_record_date_of_birth(Record record)
{
   return record->date_of_birth; 
}


char* get_record_place_of_birth(Record record)
{
   return record->place_of_birth;   
}


int get_record_spouse_id(Record record)
{
   return record->spouse_id; 
}


int get_record_no_of_children(Record record)
{
   return record->no_of_children;
}


int* get_record_children_ids(Record record)
{
   return record->children_ids;
}


void print_record(Record record)
{
   int i;  
   printf("\n"); 
   printf("id is: %d\n", record->id);  //(1) 
   printf("name is: %s\n", record->name);  //(2)
   printf("parent_id is: %d\n", record->parent_id);  //(3)
   printf("date_of_birth is: %d\n", record->date_of_birth);  //(4)
   printf("place_of_birth is: %s\n",record->place_of_birth);  //(5)
   printf("spouse_id is: %d\n", record->spouse_id);  //(6) 
   printf("no_of_children is: %d\n", record->no_of_children);  //(7) 
   for(i=0;i<record->no_of_children;i++)
      printf("child_id is: %d\n", record->children_ids[i]);  //(8) 
}
