/*
Author: Hrishi Resham
Date: June 20, 2024
Description: Header file for Assignment 2.
Usage: C/C++
*/



#include <stdio.h> // Standard I/O
#ifndef ROTORMACHINE_H
#define ROTORMACHINE_H

#define ROTOR_SIZE 28 // Size of the rotor
#define XOR_KEY 42    // XOR key for encryption

// Function prototypes
void buildIni(char *filename); // Build initial config from file
void buildRotors(int rotor1[], int rotor2[]); // Initialize rotors
void rotateRotorRight(int rotor[]); // Rotate rotor to the right
void rotateRotorLeft(int rotor[]); // Rotate rotor to the left
void setRotor1(int rotor[], int rotations); // Set rotor 1 position
void setRotor2(int rotor[], int rotations); // Set rotor 2 position
int charToIndex(char convert); // Convert char to index
char indexToChar(int convert); // Convert index to char
void encryptFile(FILE *infile, FILE *outfile, int rotor1[], int rotor2[]); // Encrypt file
void decryptFile(FILE *infile, FILE *outfile, int rotor1[], int rotor2[]); // Decrypt file

#endif // ROTORMACHINE_H