/*******************************************************************************
File: main.c
Author: Christos Garis
Target: Shell Implementation File
*******************************************************************************/ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

int main()
{
   int i, ID, ID2, ParentID, DOB, SpouceID, k, *kidID;
   char command[60], name[20], BirthPlace[20], filename[20];
   FILE* Records;
   List gen_tree;
   
   /* 1st output */
   printf("Choose one of the operations below:\n");
   printf("initialize\n");
   printf("insert <ID><name><ParentID><DOB><BirthPlace><SpouceID><k><kidID>...<kidID>\n");
   printf("load <file>\n");
   printf("lookup <ID> || <name>\n");
   printf("print <ID> || <name>\n");
   printf("allchildren <ID> || <name>\n");
   printf("gchildren <ID> || <name>\n");
   printf("gKchildren <ID1><ID2>\n");
   printf("anscestry <ID>\n");
   printf("Kcousins <ID1><ID2>\n");
   printf("avgOffspring <ID1> || <name>\n");
   printf("exit\n"); 
   
   /* Read 1st instruction */                     
   printf("\nOperation: ");
   scanf("%s",command);
   
   /* Loop while command!=exit */
   while(strcmp(command,"exit") != 0 )
   {
      if ( strcmp(command,"initialize") == 0 )
      {   
         printf("You chose operation 'initialize'\n"); 
         CreateList(&gen_tree);
      } 
      
      else if ( strcmp(command,"insert") == 0 )
      {   
         printf("You chose operation 'insert <ID><name><ParentID><DOB><BirthPlace><SpouceID><k><kidID>...<kidID>'\n\n");
         
         printf("Give the <ID>: ");
         scanf("%d",&ID);
         
         printf("Give the <name>: ");
         scanf("%s",name);
         
         printf("Give the <ParentID>: ");
         scanf("%d",&ParentID);
         
         printf("Give the <DOB>: ");
         scanf("%d",&DOB);
         
         printf("Give the <BirthPlace>: ");
         scanf("%s",BirthPlace);
         
         printf("Give the <SpouceID>: ");
         scanf("%d",&SpouceID);
         
         printf("Give the <k>: ");
         scanf("%d",&k);
         
         kidID = (int*)malloc(k * sizeof(int));
         for(i=0;i<k;i++)
         {
            printf("Give the <kidID>: ");
            scanf("%d",&(kidID[i]));  
         }
         
         InsertPersonToList(&gen_tree, ID, name, ParentID, DOB, BirthPlace, SpouceID, k, kidID);  
         print_all(gen_tree);                   
      } 
      
      else if ( strcmp(command,"load") == 0 )
      {   
         printf("You chose operation 'load'\n");  
         printf("Give the name of the file: ");
         scanf("%s",filename);
         if ( (Records=fopen(filename,"rb")) == NULL )
         {
            printf("Error\n");
            return -1;
         } 
         do 
         {
            ignore_ch(Records);
            fscanf(Records,"%d",&ID);
            ignore_ch(Records);
            fscanf(Records,"%s",name);
            ignore_ch(Records);
            fscanf(Records,"%d",&ParentID);
            ignore_ch(Records);
            fscanf(Records,"%d",&DOB);
            ignore_ch(Records);
            fscanf(Records,"%s",BirthPlace);
            ignore_ch(Records);
            fscanf(Records,"%d",&SpouceID);
            ignore_ch(Records);
            fscanf(Records,"%d",&k);
            kidID = (int*)malloc(k * sizeof(int));
            for(i=0;i<k;i++)
            {
               ignore_ch(Records);
               fscanf(Records,"%d",&kidID[i]); 
            }
            InsertPersonToList(&gen_tree, ID, name, ParentID, DOB, BirthPlace, SpouceID, k, kidID);
         }while(!feof(Records));
         fclose(Records);         
         print_all(gen_tree); 
      } 
      
      else if ( strcmp(command,"lookup") == 0 )
      {   
         printf("You chose operation 'lookup <ID> || <name>' \n");
         printf("What are you going to give? Print '<ID>' or '<name>', and then you will be asked to give value\n");
         printf("Operation: ");
         scanf("%s",command);
         if(strcmp(command,"<ID>")==0)
         {
            printf("Give <ID>: ");
            scanf("%d", &ID);        
            lookup(gen_tree, ID, "empty");          
         }
         if(strcmp(command,"<name>")==0)
         {
            printf("Give <name>: ");
            scanf("%s", name);
            lookup(gen_tree, -1, name);                  
         }
      } 
      
      else if ( strcmp(command,"print") == 0 )
      {   
         printf("You chose operation 'print <ID> || <name>' \n");
         printf("What are you going to give? Print '<ID>' or '<name>', and then you will be asked to give value\n");
         printf("Operation: ");
         scanf("%s",command);
         if(strcmp(command,"<ID>")==0)
         {
            printf("Give <ID>: ");
            scanf("%d", &ID);        
            print(gen_tree, ID, "empty");          
         }
         if(strcmp(command,"<name>")==0)
         {
            printf("Give <name>: ");
            scanf("%s", name);
            print(gen_tree, -1, name);                  
         }
      } 
      
      else if ( strcmp(command,"allchildren") == 0 )
      {   
         printf("You chose operation 'allchildren <ID> || <name>' \n");
         printf("What are you going to give? Print '<ID>' or '<name>', and then you will be asked to give value\n");
         printf("Operation: ");
         scanf("%s",command);
         if(strcmp(command,"<ID>")==0)
         {
            printf("Give <ID>: ");
            scanf("%d", &ID);        
            allchildren(gen_tree, ID, "empty");          
         }
         if(strcmp(command,"<name>")==0)
         {
            printf("Give <name>: ");
            scanf("%s", name);
            allchildren(gen_tree, -1, name);                  
         }
      } 
      
      else if ( strcmp(command,"gchildren") == 0 )
      {   
         printf("You chose operation 'gchildren <ID> || <name>' \n");
         printf("What are you going to give? Print '<ID>' or '<name>', and then you will be asked to give value\n");
         printf("Operation: ");
         scanf("%s",command);
         if(strcmp(command,"<ID>")==0)
         {
            printf("Give <ID>: ");
            scanf("%d", &ID);        
            gchildren(gen_tree, ID, "empty");          
         }
         if(strcmp(command,"<name>")==0)
         {
            printf("Give <name>: ");
            scanf("%s", name);
            gchildren(gen_tree, -1, name);                  
         }
      } 
      
      else if ( strcmp(command,"gKchildren") == 0 )
      {   
         printf("You chose operation 'gKchildren <ID1> <ID2>' \n");
         printf("Give <ID1>: ");
         scanf("%d", &ID);    
         printf("Give <ID2>: ");
         scanf("%d", &ID2);    
         gKchildren(gen_tree, ID, ID2);          
      } 
      
      else if ( strcmp(command,"anscestry") == 0 )
      {   
         printf("You chose operation 'anscestry <ID>' \n");
         printf("Give <ID>: ");
         scanf("%d", &ID);    
         anscestry(gen_tree, ID);   
      } 
      
      else if ( strcmp(command,"Kcousins") == 0 )
      {   
         printf("You chose operation 'Kcousins <ID1> <ID2>' \n");
         printf("Give <ID1>: ");
         scanf("%d", &ID);    
         printf("Give <ID2>: ");
         scanf("%d", &ID2);    
         Kcousins(gen_tree, ID, ID2); 
      } 
      
      else if ( strcmp(command,"avgOffspring") == 0 )
      {   
         printf("You chose operation 'avgOffspring <ID1> || <name>' \n");
         printf("What are you going to give? Print '<ID1>' or '<name>', and then you will be asked to give value\n");
         printf("Operation: ");
         scanf("%s",command);
         if(strcmp(command,"<ID1>")==0)
         {
            printf("Give <ID1>: ");
            scanf("%d", &ID);        
            avgOffspring(gen_tree, ID, "empty");          
         }
         if(strcmp(command,"<name>")==0)
         {
            printf("Give <name>: ");
            scanf("%s", name);
            avgOffspring(gen_tree, -1, name);                  
         }
      } 
      
      else 
      {   
         printf("Choose one of the operations below:\n");
         printf("initialize\n");
         printf("insert <ID><name><ParentID><DOB><BirthPlace><SpouceID><k><kidID>...<kidID>\n");
         printf("load <file>\n");
         printf("lookup <ID> || <name>\n");
         printf("print <ID> || <name>\n");
         printf("allchildren <ID> || <name>\n");
         printf("gchildren <ID> || <name>\n");
         printf("gKchildren <ID1><ID2>\n");
         printf("anscestry <ID>\n");
         printf("Kcousins <ID1><ID2>\n");
         printf("avgOffspring <ID1> || <name>\n");
         printf("exit\n"); 
      } 
      /* Read next instruction */                      
      printf("\nOperation: ");
      scanf("%s",command);                              
      /* This will continue, until command=exit */
   }
    
   printf("You exited the program.\n"); 
   DeleteList(&gen_tree); 
    
   return 0;    
}
