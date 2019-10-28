/*******************************************************************************
File: record.h
Author: Christos Garis
Target: Record Interface File
*******************************************************************************/ 

#ifndef __REC__ 
#define __REC__

typedef struct Record_Node* Record; 

/* Function Declarations */

/* Creates an empty record */
Record create_record();

/* Sets a record */
void set_record(Record* record, int id, char* name, int parent_id, int date_of_birth, 
         char* place_of_birth, int spouse_id, int no_of_children, int* children_ids);        
        
/* Gets a record */
int get_record_id(Record record);
char* get_record_name(Record record);
int get_record_parent_id(Record record);
int get_record_date_of_birth(Record record);
char* get_record_place_of_birth(Record record);
int get_record_spouse_id(Record record);
int get_record_no_of_children(Record record);
int* get_record_children_ids(Record record);

/* Prints a record */
void print_record(Record record);

#endif 
