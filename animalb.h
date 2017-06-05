/*Raisa Meneses
Tested with Ubuntu 16.04 LTS Desktop 32-bits
Pr5 - Animal binary reader - Header*/
#ifndef ANIMALB_H
#define ANIMALB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct animal {
   unsigned short int id;
   char name[20];
   char species[35];
   char size;
   unsigned short int age;
};
typedef struct animal Animal;

void option1(FILE* fileptr);
void option2(FILE* fileptr);
void option3(FILE* fileptr);
void option4(FILE* fileptr);
void option5(FILE* fileptr);
void printAnimal(Animal currentAnimal);
void updateRecord(Animal *currentAnimal, char* name,  char* species, char size, unsigned short int age);
void animalToCSV(FILE *fileptr, FILE *animals_csv);
void option6(FILE* fileptr);
void createAnimal(Animal *currentAnimal, unsigned short int id, char* name,  char* species, char size, unsigned short int age);
#endif
