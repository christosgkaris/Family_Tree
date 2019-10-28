/*******************************************************************************
File: list.c
Author: Christos Garis
Target: List Implementation File
*******************************************************************************/ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

typedef struct List_Node{
   int NoOfPersons;     
   Record person1;
   Record person2;
   List next;  
   List prev;
   List person1_parents_ptr;
   List children_ptrs[10];       
}List_Node;

/* Function Definitions */

void CreateList(List* list)
{
   *list = NULL;  
}


void DeleteList(List* list)
{  
   List* p;   
   int i, finished=0;
   
   if (*list == NULL)
   {
      // do nothing
   }
   else
   {   
      while (finished==0)
      {
         p = list;
         *list = (*list)->next;
         if (*list == NULL)
            finished = 1;
         free(p);
      }
   }  
}
    
    
void InsertEmptyNodeAtEnd(List *list)
{ 
   int i;
   List newnode = (List)malloc(sizeof(List_Node));

   newnode->NoOfPersons = 0;
   /* Initialize the two persons in the node */
   newnode->person1 = create_record();
   newnode->person2 = create_record();
   /* Initialize the pointers */
   newnode->prev = NULL;
   newnode->next = NULL;
   newnode->person1_parents_ptr = NULL;
   for(i=0;i<10;i++)  
      newnode->children_ptrs[i] = NULL;
   
   if (*list == NULL) /* If 1st element */
      *list = newnode;
   else
   {
      /* I find the last node of the list, and I append the new */
      while((*list)->next != NULL)
         *list = (*list)->next;
      /* Now tmp points to the last node of the list, we set the pointers correctly */
      (*list)->next = newnode;
      (newnode)->prev = *list;
      while((*list)->prev != NULL)   /* Go back to the 1st node of the list */
         *list = (*list)->prev;   
   }
}


void InsertPersonToList(List* list, int id, char* name, int parent_id, int date_of_birth, 
             char* place_of_birth, int spouse_id, int no_of_children, int* children_ids)
{
   List tmp = *list;
   List tmp2 = *list;
   List parent_ptr = *list;
   int i, found;
   
   if( (parent_id) == -1 )  
   {
      if (*list == NULL) /*if 1st element*/
      {         
         InsertEmptyNodeAtEnd(list);
         /*we store the record*/
         tmp = *list; 
         set_record(&(tmp->person1), id, name, parent_id, date_of_birth, place_of_birth, 
                                                  spouse_id, no_of_children, children_ids); 
         tmp->NoOfPersons++;   
         tmp->person1_parents_ptr = NULL;   /* set parent */                                   
         
         /*we fix the array of pointers to the clildren of node*/   
         for(i=0;i<no_of_children;i++)
         {                                             
            InsertEmptyNodeAtEnd(list);  
            tmp2 = *list;
            while(tmp2->next != NULL)              
               tmp2 = tmp2->next;   /* go to end of list */    
            tmp2->person1_parents_ptr = tmp;   /* set parent */
            tmp->children_ptrs[i] = tmp2;   /* set child */           
         }
      }
      else
      {  /*if person does not belong to the family, but married a family person*/
         if(id==-1)
            printf("Error...\n"); 
         else
         {   
            tmp = *list;   
            while(spouse_id != get_record_id(tmp->person1))              
               tmp = tmp->next;      
            /*found*/   
            /*we store the record*/      
            set_record(&(tmp->person2), id, name, parent_id, date_of_birth, place_of_birth, 
                                                     spouse_id, no_of_children, children_ids);
            tmp->NoOfPersons++;
         }
      }
   }   
   else   /*if person does belong to the family, and has parent*/
   {
      tmp=*list;    
      while((tmp->NoOfPersons!=0)&&(get_record_id(tmp->person1) != parent_id))                
         tmp = tmp->next;
      parent_ptr = tmp;   /* parent found */ 
      
      /*now, we must find an empty node suitable to store the record*/
      i=0;
      found=0;
      while((i<get_record_no_of_children(parent_ptr->person1))&&(found==0))
      {
         if((parent_ptr->children_ptrs[i]->NoOfPersons==0)&&(parent_ptr->children_ptrs[i]!=NULL))
         {
             found=1;
             tmp=parent_ptr->children_ptrs[i];                                 
         }  
         i++;  
      }
      /*we store the record*/
      set_record(&(tmp->person1), id, name, parent_id, date_of_birth, place_of_birth, 
                                            spouse_id, no_of_children, children_ids);
      tmp->NoOfPersons++;
      
      /*we fix the array of pointers to the clildren of node*/  
      for(i=0;i<no_of_children;i++)
      {                         
         InsertEmptyNodeAtEnd(list);
         tmp2 = *list;
         while(tmp2->next != NULL)
            tmp2 = tmp2->next;
         tmp2->person1_parents_ptr = tmp;
         tmp->children_ptrs[i] = tmp2;
      }          
   }   
}


void ignore_ch(FILE* file)
{
   int ch;
   while( (ch=getc(file)) == ' ' || ch == '\n')
   {
     // do nothing 
   }
   ungetc(ch,file);
}


void lookup(List list, int id, char* name)
{
   List tmp = list;
   int found=0;  
   if(id==-1)
   {
      do
      {
         if(strcmp(name,get_record_name(tmp->person1))==0)
         {
            found=1;               
            print_record(tmp->person1);              
         }    
         else if(strcmp(name,get_record_name(tmp->person2))==0)
         {
            found=1;               
            print_record(tmp->person2);              
         }
         tmp=tmp->next;
      }while((tmp!=NULL)&&(found==0));             
   }
   else
   {
      do
      {
         if(id==get_record_id(tmp->person1))
         {
            found=1;               
            print_record(tmp->person1);              
         }    
         else if(id==get_record_id(tmp->person2))
         {
            found=1;               
            print_record(tmp->person2);              
         }
         tmp=tmp->next;
      }while((tmp!=NULL)&&(found==0)); 
   }
}


void print(List list, int id, char* name)
{
   List tmp = list;   /*points to the top node*/
   List tmp2 = list;   /*points to next, until the end of the list*/
   List tmp3 = list;   /*goes back to ancestor, until found, or until begin of the list*/
   int found=0; 
   if(id==-1)
   {            
      do
      {
         if(strcmp(name,get_record_name(tmp->person1))==0)
            found=1;                                 
         else if(strcmp(name,get_record_name(tmp->person2))==0)
            found=1;  
         else                             
            tmp=tmp->next;
      }while((tmp!=NULL)&&(found==0));    
   }
   else
   {
      do
      {
         if(id==get_record_id(tmp->person1))
            found=1;                                 
         else if(id==get_record_id(tmp->person2))
            found=1;          
         else                     
            tmp=tmp->next;
      }while((tmp!=NULL)&&(found==0));        
   }   
   
   /*we found the record, now we must print the records*/  
   print_record(tmp->person1);
   print_record(tmp->person2);
      
   /*the search for the below nodes*/
   tmp2=tmp;
   tmp2=tmp2->next;
   while(tmp2!=NULL)   /*while tmp2 hasn't reached the end of the list*/
   {
      tmp3=tmp2;
      while((tmp3!=tmp)&&(tmp3!=NULL))   /*while tmp3 hasn't found tmp and hasn't reached the begin of the list*/                 
      {
         tmp3=tmp3->person1_parents_ptr;                                
         if(tmp3==tmp) 
         {                
            print_record(tmp2->person1);
            print_record(tmp2->person2);
         }
      }
      tmp2=tmp2->next;
   } 
}


void allchildren(List list, int id, char* name)
{
   int i;  
   List tmp = list;   /*points to the top node*/
   List tmp2 = list;   /*points to next, until the end of the list*/
   List tmp3 = list;   /*goes back to ancestor, until found, or until begin of the list*/
   int found=0; 
   if(id==-1)
   {           
      do
      {
         if(strcmp(name,get_record_name(tmp->person1))==0)
            found=1;                                 
         else if(strcmp(name,get_record_name(tmp->person2))==0)
            found=1;  
         else                             
            tmp=tmp->next;
      }while((tmp!=NULL)&&(found==0));    
   }
   else
   {
      do
      {
         if(id==get_record_id(tmp->person1))
            found=1;                                 
         else if(id==get_record_id(tmp->person2))
            found=1;          
         else                     
            tmp=tmp->next;
      }while((tmp!=NULL)&&(found==0));        
   }   
   
   /*we found the record, now we must print the records*/  
   for(i=0;i<get_record_no_of_children(tmp->person1);i++)
      print_record(tmp->children_ptrs[i]->person1);                                    
}


void gchildren(List list, int id, char* name)
{
   int i,j, N=0;  
   char nam[20];
   List tmp = list;   /*points to the top node*/
   List tmp2 = list;   /*points to next, until the end of the list*/
   List tmp3 = list;   /*goes back to ancestor, until found, or until begin of the list*/
   int found=0; 
   if(id==-1)
   {           
      do
      {
         if(strcmp(name,get_record_name(tmp->person1))==0)
            found=1;                                 
         else if(strcmp(name,get_record_name(tmp->person2))==0)
            found=1;  
         else                             
            tmp=tmp->next;
      }while((tmp!=NULL)&&(found==0));    
   }
   else
   {
      do
      {
         if(id==get_record_id(tmp->person1))
            found=1;                                 
         else if(id==get_record_id(tmp->person2))
            found=1;          
         else                     
            tmp=tmp->next;
      }while((tmp!=NULL)&&(found==0));        
   }   
   
   /*we found the record, now we must print the records*/
   for(i=0;i<get_record_no_of_children(tmp->person1);i++)
   {                                                  
      for(j=0;j<get_record_no_of_children(tmp->children_ptrs[i]->person1);j++) 
      {
         N++;
         strcpy(nam,get_record_name(tmp->children_ptrs[i]->children_ptrs[j]->person1));     
         printf("%s\n",nam);                                                           
      }                                                    
   }     
   printf("N=%d grandchildren\n",N);
}


void gKchildren(List list, int id1, int id2)
{
   List tmp1 = list;
   List tmp2 = list;
   List tmp3 = list;
   int error=0;
   int found=0;
   int K=-1;
   
   do
   {
      if(id1==get_record_id(tmp1->person1))
         found=1;             
      else if(id1==get_record_id(tmp1->person2))
         found=1;          
      else                     
         tmp1=tmp1->next;
   }while((tmp1!=NULL)&&(found==0));
   
   while((tmp2->next)!=NULL)
      tmp2=tmp2->next;   /* go to end of the list */    
      
   while((tmp2!=NULL)&&(id2!=get_record_id(tmp2->person1))&&(id2!=get_record_id(tmp2->person2)))  
      tmp2=tmp2->prev;                                    

   if(id2==get_record_id(tmp2->person1))
      found=1;
   else if(get_record_parent_id(tmp2->person2)==-1)
      error=1;
   
   /*now tmp1 points to the node where id1 (K-grandparent) is located, and tmp2 points to the node where id2 (child) is located*/
   if(error==1)
      printf("ID2 does not have ancestors in tree\n");
   else
   {
      tmp3=tmp2;
      while((tmp3!=tmp1)&&(tmp3!=NULL))
      {
         tmp3=tmp3->person1_parents_ptr;                                
         if(tmp3==tmp1)   /*found*/
         {      
            print_record(tmp2->person1);     
            while(tmp2!=tmp1)
            {  
               K++;              
               tmp2=tmp2->person1_parents_ptr;                         
               print_record(tmp2->person1);
               print_record(tmp2->person2);
            }
         }
      }
      printf("K=%d\n",K);
      if(K==-1)
         printf("ID1 is not K-grandparent of ID2\n");
      if(K==0)
         printf("Parent\n");
      if(K==1)
         printf("GrandParent\n");
      if(K==2)
         printf("GreatGrandParent\n");
      if(K==3)
         printf("GreatGreatGrandParent\n");
      if(K==4)
         printf("GreatGreatGreatGrandParent\n");
      if(K==5)
         printf("GreatGrandGreatGreatGreatParent\n");
      if(K==6)
         printf("GreatGrandGreatGreatGreatGreatParent\n");
      if(K==7)
         printf("GreatGrandGreatGreatGreatGreatGreatParent\n");
      if(K==8)
         printf("GreatGrandGreatGreatGreatGreatGreatGreatParent\n");
      if(K==9)
         printf("GreatGrandGreatGreatGreatGreatGreatGreatGreatParent\n");
      if(K==10)
         printf("GreatGrandGreatGreatGreatGreatGreatGreatGreatGreatParent\n");
      if(K==11)
         printf("GreatGrandGreatGreatGreatGreatGreatGreatGreatGreatGreatParent\n");
      if(K==12)
         printf("GreatGrandGreatGreatGreatGreatGreatGreatGreatGreatGreatGreatParent\n"); 
      if(K>12)
         printf("Very old anscestor\n");     
   }
}


void anscestry(List list, int id)
{
   List tmp = list;
   int error=0;
   int found=0;
   
   do
   {
      if(id==get_record_id(tmp->person1))
         found=1;             
      else if(id==get_record_id(tmp->person2))
         error=1;          
      else                     
         tmp=tmp->next;
   }while((tmp->next!=NULL)&&(found==0)&&(error==0));
   /*we found the record*/
   if(error==0)
   {
      while((tmp->person1_parents_ptr)!=NULL)
      {
         tmp=tmp->person1_parents_ptr;
         print_record(tmp->person1); 
         print_record(tmp->person2);              
      }
   }
   else
      printf("ID does not have ancestors in tree\n");
}


void Kcousins(List list, int id1, int id2)
{
   List tmp1 = list;
   List tmp2 = list;
   List tmp3 = list;
   List tmp4 = list;
   int error1=0;
   int error2=0;
   int found=0;
   int K1=0; 
   int K2=0;
   
   do
   {
      if(id1==get_record_id(tmp1->person1))
      {
         found=1;             
         print_record(tmp1->person1);
      }
      else if(id1==get_record_id(tmp1->person2))
      {
         error1=1;          
         print_record(tmp1->person2);
      }
      else                     
         tmp1=tmp1->next;
   }while((tmp1!=NULL)&&(found==0));
   
   while((tmp2->next)!=NULL)
      tmp2=tmp2->next;   /* go to end of the list */    
      
   while((tmp2!=NULL)&&(id2!=get_record_id(tmp2->person1))&&(id2!=get_record_id(tmp2->person2)))  
      tmp2=tmp2->prev;                                    

   if(id2==get_record_id(tmp2->person1))
   {
      found=1;            
      print_record(tmp2->person1);      
   }
   else if(id2==get_record_id(tmp2->person2))
   {
      error2=1;          
      print_record(tmp2->person2);
   }
   
   /*now tmp1 points to the node where id1 is located, and tmp2 points to the node where id2 is located*/
   if(error1==1)
      printf("ID1 does not have ancestors in tree\n");
   else if(error2==1)
      printf("ID2 does not have ancestors in tree\n");   
   else
   {
      tmp3=tmp1; 
      while((tmp1->person1_parents_ptr)!=NULL)
      {
         tmp1=tmp1->person1_parents_ptr;
         ++K1;
      }
      tmp4=tmp2;    
      while((tmp2->person1_parents_ptr)!=NULL)
      {
         tmp2=tmp2->person1_parents_ptr;
         ++K2;
      }  
      if((K1==K2)&&(tmp3->person1_parents_ptr!=tmp4->person1_parents_ptr))
      {
         printf("\nID1 and ID2 are cousins, with grade= %d\n",K1-1); 
      }
      else
         printf("Not Kcousins\n");
   }     
}


void avgOffspring(List list, int id, char* name)
{
   List tmp = list;  
   List tmp2 = list;  
   List tmp3 = list;  
   int found=0;
   int N=0;
   int S=0; 
   double D=0; 
     
   if(id==-1)
   {           
      do
      {
         if(strcmp(name,get_record_name(tmp->person1))==0)
            found=1;     
         else if(strcmp(name,get_record_name(tmp->person2))==0)
            found=1;                                 
         else                             
            tmp=tmp->next;
      }while((tmp!=NULL)&&(found==0));    
   }
   else
   {
      do
      {
         if(id==get_record_id(tmp->person1))
            found=1; 
         if(id==get_record_id(tmp->person2))
            found=1;                                             
         else                     
            tmp=tmp->next;
      }while((tmp!=NULL)&&(found==0));        
   }   
   /*we found the record*/   
   if(get_record_spouse_id(tmp->person1)==-1) 
      N++;
   else
      N=N+2;
      
   if(get_record_no_of_children(tmp->person1)!=0) 
   {         
      /*the search for the below nodes*/
      tmp2=tmp;
      tmp2=tmp2->next;
      while(tmp2!=NULL)   /*while tmp2 hasn't reached the end of the list*/
      {
         tmp3=tmp2;
         while((tmp3!=tmp)&&(tmp3!=NULL))   /*while tmp3 hasn't found tmp and hasn't reached the begin of the list*/                 
         {
            tmp3=tmp3->person1_parents_ptr;                                
            if(tmp3==tmp) 
            {                
               if(get_record_spouse_id(tmp2->person1)==-1) 
                  N++;
               else
                  N=N+2;
               if(get_record_no_of_children(tmp2->person1)!=0)   
                  S++;
           }
         }
         tmp2=tmp2->next;
      } 
      printf("N=%d\n", N);
      printf("S=%d\n", S);
      D=N/((double)S);
      printf("avgOffspring=%lf\n", D);
   }
   else
      printf("Root has no children\n");
}


void print_all(List list)
{
   List tmp = list;
   List tmp2 = list;
   
   while (tmp2!=NULL)
      tmp2=tmp2->next;
   /*tmp2 points to the last node of the list*/
   while(tmp!=tmp2)
   {
      print_record(tmp->person1);
      print_record(tmp->person2);              
      tmp = tmp->next;             
   }      
}
