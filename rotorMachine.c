/*
Author: Hrishi Resham
Date: June 20, 2024
Description: Implementation file for Assignment 2.
Usage: C/C++
*/

#include "rotorMachine.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// Build initial config file
void buildIni(char *filename) {
    FILE *configFile = fopen(filename, "r");
    FILE *iniFile = fopen("rotors.ini", "w");
    if (configFile == NULL || iniFile == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    int value;
    while (fscanf(configFile, "%d", &value) == 1) {
        value ^= XOR_KEY; // XOR with key
        fprintf(iniFile, "%d\n", value);
    }

    fclose(configFile);
    fclose(iniFile);
}

// Build rotors from ini file
void buildRotors(int rotor1[], int rotor2[]) {
    FILE *iniFile = fopen("rotors.ini", "r");
    if (iniFile == NULL) {
        fprintf(stderr, "Error: Rotor machine not initialized. Run with -i option and provide an appropriate configuration file.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < ROTOR_SIZE; i++) {
        fscanf(iniFile, "%d", &rotor1[i]);
        rotor1[i] ^= XOR_KEY; // XOR with key
         printf("rotor1[i]: %d", rotor1[i]);
       
    }
    for (int i = 0; i < ROTOR_SIZE; i++) {
        fscanf(iniFile, "%d", &rotor2[i]);
        rotor2[i] ^= XOR_KEY; // XOR with key

        printf("rotor2[i]: %d", rotor2[i]);

    }

    fclose(iniFile);
}

// Rotate rotor to the right
void rotateRotorRight(int rotor[]) {
    int last = rotor[ROTOR_SIZE - 1];
    for (int i = ROTOR_SIZE - 1; i > 0; i--) {
        rotor[i] = rotor[i - 1];
    }
    rotor[0] = last;
}

// Rotate rotor to the left
void rotateRotorLeft(int rotor[]) {
    int first = rotor[0];
    for (int i = 0; i < ROTOR_SIZE - 1; i++) {
        rotor[i] = rotor[i + 1];
    }
    rotor[ROTOR_SIZE - 1] = first;
}

// Set rotor 1 start position
void setRotor1(int rotor[], int rotations) {
    for (int i = 0; i < rotations; i++) {
        rotateRotorRight(rotor);
    }
}

// Set rotor 2 start position
void setRotor2(int rotor[], int rotations) {
    for (int i = 0; i < rotations; i++) {
        rotateRotorLeft(rotor);
    }
}

// Convert char to index
int charToIndex(char convert) {
    convert = toupper(convert);
    
    if (convert >= 'A' && convert <= 'Z') {
        printf("convert-----: %d", convert-'A');
        return convert - 'A';
    } else if (convert == ' ') {
        return 26;
    } else if (convert == '.') {
        return 27;
    } else {
        return -1;
    }
    
}

// Convert index to char
char indexToChar(int convert) {
    if (convert >= 0 && convert <= 25) {
        printf("indexToChar-----: %d", convert+'A');
        return (char)(convert + 'A');
    } else if (convert == 26) {
        return ' ';
    } else if (convert == 27) {
        return '.';
    } else {
        return '?';
    }
    
}



// Encrypt file
void encryptFile(FILE *infile, FILE *outfile, int rotor1[], int rotor2[]) {
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), infile) != NULL) {
        for (int i = 0; buffer[i] != '\0'; i++) {
            int index = charToIndex(buffer[i]);
            
            if (index != -1) {
                int temp = rotor1[index];
                int j;
                for (j=0; j<ROTOR_SIZE; j++){
                    if (rotor2[j] == temp){
                        break;
                    }
                }

                buffer[i] = indexToChar(j);
                
        
                rotateRotorRight(rotor1);
    
                rotateRotorLeft(rotor2);
            }
        }
        fputs(buffer, outfile);
    }
}

// Decrypt file
void decryptFile(FILE *infile, FILE *outfile, int rotor1[], int rotor2[]) {
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), infile) != NULL) {
        for (int i = 0; buffer[i] != '\0'; i++) {
            int index = charToIndex(buffer[i]);
            if (index != -1) {
                int temp = rotor2[index];
                int j;
                for (j = 0; j < ROTOR_SIZE; j++) {
                    if (rotor1[j] == temp) break;
                }
                buffer[i] = indexToChar(j);
                rotateRotorRight(rotor1);
                rotateRotorLeft(rotor2);
            }
        }
        fputs(buffer, outfile);
    }
}