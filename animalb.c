/*Raisa Meneses
Tested with Ubuntu 16.04 LTS Desktop 32-bits
Pr5 - Animal binary reader - Header*/

//Extra credit: Appends a new item at the end of the file with a default Small Size
 
/*Issues: Option four. Creates a new struct instead of overriding the existing one. Not sure
What I'm doing wrong in here.. */

#include "animalb.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

/*Prints a String representation 
of the binary file passed as an argument*/
void option1(FILE* fileptr){
  char byte;
  int i, j, size;
  //Take the pointer to the start in case it has been moved in any of the other operations. 
  rewind(fileptr);
  //Determine the size of the file. 
  fseek(fileptr, 0L, SEEK_END);
  size = ftell(fileptr);
  rewind(fileptr);
   //Loop through the file and print every character. If we don't find an ASCII character, then print a space. 
   for (i = 0; i < size; i++) {
        fread(&byte, sizeof(char), 1, fileptr);
        if (byte >= 32 && byte <= 127){
	   printf("%c", byte);
          } else {
           printf(" ");
          }
     }
}
/*Prints the integer representation
of the binary file passed as an argument*/
void option2(FILE* fileptr){
  int byte;
  int i, j, size;
  //Put the pointer at the beg. of the file. 
  rewind(fileptr);
  //Determine the size of the file
  fseek(fileptr, 0L, SEEK_END);
  size = ftell(fileptr) / sizeof(int);
  rewind(fileptr);

   //Loop and print the integer represetation of the file
   for (i = 0; i < size; i++) {
        fread(&byte, sizeof(int), 1, fileptr);
        printf("%d  ", byte);
     }
}

/*Prints selected file to the console. 
Doesn't modify the source file*/
void option3(FILE* fileptr){
  int i, size, idLookUp, result, animalInFile = 0;
  //Rewind and get size:
  rewind(fileptr);
  fseek(fileptr, 0L, SEEK_END);
  size = ftell(fileptr) / sizeof(struct animal);
  rewind(fileptr); 

  printf("\n");
  printf("Which animal record would you like to display on the screen?\n");
  printf("Please enter the Animal ID: \n");  
  scanf("%d",&idLookUp);
  
  for( i = 0; i < size; i++) {
      struct animal record = {0, "", "", ' ', 0};
      result = fread(&record,  sizeof(struct animal), 1,  fileptr);
         if (record.id == idLookUp) {	   
             printAnimal(record);
 	     animalInFile = 1;
         } 
      }
   if (animalInFile == 0) {
      printf("Record not on file. Please try a different id\n");
   }
}

/*Updates only one element of the struct
based on the information given by the user 
in standard input
Pre: File for processing*/
void option4(FILE* fileptr){
  
int i, j, size, idLookUp, result, result2, compare1, compare2,  compare3,  compare4, animalInFile = 0;
short int updateAge;
char updateName[35];
char updateSpecies[35];
char userChoice[30];
char updateSize;

  rewind(fileptr);
  fseek(fileptr, 0L, SEEK_END);
  size = ftell(fileptr) / sizeof(struct animal);
  rewind(fileptr); 

  printf("\n");
  printf("Which animal record would you like to update?\n");
  printf("Please enter the Animal ID: \n"); 
  scanf("%d",&idLookUp);
  
  
  struct animal record = {0, "", "", ' ', 0};
  for( i = 0; i < size; i++) {
      //struct animal record = {0, "", "", ' ', 0};
      result = fread(&record,  sizeof(Animal), 1,  fileptr);
         if (record.id == idLookUp) { 	     
 	     animalInFile = 1;
	     //Capture current name, species.. etc for later update
	     strcpy(updateName, record.name); 
	     strcpy(updateSpecies, record.species);
	     updateSize = record.size;
	     updateAge = record.age;

	     printf("Success. Record found.\n");
	     printf("What would you like to update?\n");
	     printf("Please select one of the following:\n 'n' for Name\n 's' for Species\n 'z' for size\n  or 'a' for Age\n");
	     scanf("%s", userChoice);  	     
	     
	     compare1 = strcmp(userChoice,  "n");
	     compare2 = strcmp(userChoice,  "s");
	     compare3 = strcmp(userChoice,  "z");
	     compare4 = strcmp(userChoice,  "a");

	     if(compare1 == 0 || compare2 == 0 || compare3 == 0 || compare4 == 0) {
	     	printf("\nThank you! Please enter the new information:\n");   		
		//Create a new Animal record and update the next struct:
		if(compare1 == 0){
	           scanf("%s", updateName);
	 	   updateRecord(&record, updateName, updateSpecies, updateSize, updateAge);		   		   
	        } 
	        if(compare2 == 0){
		   scanf("%s", updateSpecies);
	 	   updateRecord(&record, updateName, updateSpecies, updateSize, updateAge);		   
	        } 
		if(compare3 == 0){
		   scanf("%c", &updateSize);	   		   
	 	   updateRecord(&record, updateName, updateSpecies, updateSize, updateAge);
		   
	        } 
		if(compare4 == 0){
		   scanf("%hu", &updateAge);		   
	 	   updateRecord(&record, updateName, updateSpecies, updateSize, updateAge);
                   
	        }
		   fseek(fileptr, -sizeof(Animal), SEEK_SET);
	           fwrite(&record, sizeof(Animal), 1, fileptr);
		   
	     	   printf("\n");
	     	   printf("The record #%u has been updated\n", record.id);
	      	   printf("This is the updated data: \n");
             	   printAnimal(record); 
	      } else {
  		   printf("I'm sorry. You can only update Name, Species, Size or Age.");
		}
	      
	    
         } 
      }


   if (animalInFile == 0) {
      printf("Record not on file. Please try a different id\n");
      }
}

/*Updates all records in a given Animal
with the information stored in the last element*/
void option5(FILE* fileptr){
   int i, j, k, size, idLookUp, byteSize, result, result2, newSize, animalInFile = 0;   
  
   rewind(fileptr);
   fseek(fileptr, 0L, SEEK_END);
   byteSize = ftell(fileptr);
   size = ftell(fileptr) / sizeof(struct animal);
   rewind(fileptr); 
   //Obtain the information from the last struct in the file
   struct animal record = {0, "", "", ' ', 0};
   for(i = 0; i < size; i++) {       
       result = fread(&record,  sizeof(Animal), 1,  fileptr);
   }
     printf("The Animal you choose will be replaced by the last Animal record:\n");
     printAnimal(record);
     printf("What Animal record would you want to update?\n");
     printf("Please enter an ID\n");
     scanf("%d", &idLookUp);
     printf("We will be updating item # %d\n", idLookUp);
   //Put the information from the last record into the first one. 
   rewind(fileptr);
   struct animal tempRecord = {0, "", "", ' ', 0};
   for(j = 0; j < size; j++) {     
       result2 = fread(&tempRecord,  sizeof(Animal), 1,  fileptr);
         if(idLookUp == tempRecord.id){
	    updateRecord(&tempRecord, record.name,  record.species, record.size, record.age);
 	     fseek(fileptr, -(sizeof(Animal)), SEEK_SET);
	     //put the animal record in the file:		
	     fwrite(&tempRecord, sizeof(Animal), 1, fileptr);
	    break;
        }
   }   
   //Size after shrinking the file 
   printf("Animal record #%d has been updated\n", idLookUp);
   printAnimal(tempRecord);
   //size of the file after truncating the last element. :) 
   newSize = byteSize - sizeof(struct animal);
   //Using System Command and truncate function to shrink the binary file. 
   char command[50];
   snprintf(command, sizeof(command), 
          "truncate -s %d animals.dat", newSize);
   system(command);  
  
}

/*Appends a new item at the end of the file with a default Small Size*/
void option6(FILE* fileptr) {
   int i, size, result;
   short int updateAge, newId, end;
   char updateName[35];
   char updateSpecies[35];
   char updateSize;

   //Obtaining the number of elements in the file. 
   rewind(fileptr);
   fseek(fileptr, 0L, SEEK_END);
   size = ftell(fileptr) / sizeof(struct animal);
   rewind(fileptr); 
   //Determine the last record's ID
   struct animal record = {0, "", "", ' ', 0};
   for(i = 0; i < size; i++) {       
       result = fread(&record,  sizeof(Animal), 1,  fileptr);
       end = record.id;
   }
   rewind(fileptr);
   printf("Please enter the new Animal informtion\n");

   printf("Name:\n");
   scanf("%s", updateName);

   printf("Species:\n");
   scanf("%s", updateSpecies);
   
   printf("Age:\n");
   scanf("%hu", &updateAge);

   //Determine new Id. 
   newId = end+= 2;
   //create an animal and add it to the end of file.
   createAnimal(&record, newId, updateName, updateSpecies, 's', updateAge);
   fseek(fileptr, 0L, SEEK_END);
   fwrite(&record, sizeof(Animal), 1, fileptr);
}

/*Helper method to print an Animal struct. 
It is used to notify the client
on the screen about the changes made to the file. */
void printAnimal(Animal currentAnimal) {
   printf("Id: %u\n", currentAnimal.id);
   printf("Name: %s\n", currentAnimal.name);
   printf("species: %s\n", currentAnimal.species);
   printf("Age: %hu\n", currentAnimal.age);
}

//Helper method to update one Animal 
//It takes the memory address of an Animal
//And the new data to be updated
//and overrides the current data
//This method is later used to update data inside the file. 
void updateRecord(Animal *currentAnimal, char* name,  char* species, char size, unsigned short int age) {
	strcpy(currentAnimal->name, name); 
	strcpy(currentAnimal->species, species);
	currentAnimal->size = size;
	currentAnimal->age = age;	
}

//Helper method to Create a new Animal
void createAnimal(Animal *currentAnimal, unsigned short int id, char* name,  char* species, char size, unsigned short int age) {
        currentAnimal->id = id;
	strcpy(currentAnimal->name, name); 
	strcpy(currentAnimal->species, species);
	currentAnimal->size = size;
	currentAnimal->age = age;	
}

//Helper method to copy all the information from animals.dat to a file called animals.csv
//Pre: a binary file with all records
//a pointer to a File. New CSV record will be created. 
void animalToCSV(FILE *fileptr, FILE *AnimalToCSV) {
 rewind(fileptr);
 int result;
  while(!feof(fileptr)) {
      struct animal record = {0, "", "", ' ', 0};
      result = fread(&record,  sizeof(Animal), 1,  fileptr);
       if (result != 0 && record.id != 0) {
           fprintf(AnimalToCSV, "%hd, %s, %s, %c, %hd\n", record.id, record.name, record.species, record.size, record.age);
     }
   }  
}

