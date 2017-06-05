/*Raisa Meneses
Tested with Ubuntu 16.04 LTS Desktop 32-bits
Pr5 - Animal binary reader - Header

Extra credit - option6 appends at the end of the file with a Small Size*/

#include "animalb.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*This program makes use of all the methods
created in animalb.c*/
int main(void){
  int userChoice = 7; 
  FILE* fileRead;
  FILE* animals_csv; 
  int size;
  
   printf("starting\n");
   //Open the file to read and write: 
   
   animals_csv = fopen("animals.csv", "wb");

   fileRead = fopen("animals.dat", "rb+");
   if (fileRead == 0) {
      perror("Coundn't open file 'animals.dat\n'");
   } else {
     printf("File opened successfully. Begin processing\n");
   }  
   
  
   /*Loop until the user selects the number zero. instructions for each option
     are defined in animalb.h and the implementation is written in animalb.c*/
   while(userChoice != 0) {
      printf("\n");
      printf("Select 1 to print the binary file in String format. 0 to quit\n");
      printf("Select 2 to print the binary file in Integer format. 0 to quit\n");      
      printf("Select 3 to find and display one animal in the screen. 0 to quit\n");      
      printf("Select 4 to upate information about one animal. 0 to quit\n");      
      printf("Select 5 to override an animal record with the last record in file. 0 to quit\n");        
      printf("Select 6 to append a new Animal to the end of the file. 0 to quit\n");
      scanf("%d", &userChoice);
      switch(userChoice) {
         case 1:
            option1(fileRead);
            break;
         case 2:
            option2(fileRead);
            break;
         case 3:
            option3(fileRead);
            break;
         case 4:
            option4(fileRead);
            break;
         case 5:
            option5(fileRead);
            break;
	 case 6:
            option6(fileRead);
            break;
         default :
            printf("File processing numbers are 1, 2, 3, 4 and 5\n");
     }   

  } 

   if (userChoice == 0){
       printf("File closed successfully\n");

       animalToCSV(fileRead, animals_csv);
       printf("Your changes have been stored in the file animals.csv\n");
       
       fclose(fileRead);
       fclose(animals_csv);
 
       
   }

}
