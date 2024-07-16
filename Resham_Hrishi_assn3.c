/*
Author: Hrishi Resham
Date: June 20, 2024
Description: Main file for Assignment 2 Rotor Machine Encryption/Decryption.
Usage: C/C++
*/


#include "rotorMachine.h" // Include the header file for rotor machine functions
#include <stdio.h>        // Include standard I/O library
#include <stdlib.h>       // Include standard library for memory allocation, conversion, etc.
#include <string.h>       // Include string handling library

// Function to print usage instructions
void printUsage() {
    printf("Usage:\n");
    printf("./exe -i <configuration file>\n");
    printf("./exe -e <in file> <out file> -r <rotor 1 start> <rotor 2 start>\n");
    printf("./exe -d <in file> <out file> -r <rotor 1 start> <rotor 2 start>\n");
    printf("./exe -e <in file> <out file> -r <rotor 1 start> <rotor 2 start> -i <config file>\n");
    printf("./exe -d <in file> <out file> -r <rotor 1 start> <rotor 2 start> -i <config file>\n");
}

// Main function
int main(int argc, char *argv[]) {
    // Check if the number of arguments is less than 3
    if (argc < 3) {
        printUsage();
        return EXIT_FAILURE;
    }

    int rotor1[ROTOR_SIZE]; // Array to hold the first rotor
    int rotor2[ROTOR_SIZE]; // Array to hold the second rotor

    // Check if the first argument is "-i" for initializing configuration
    if (strcmp(argv[1], "-i") == 0) {
        if (argc != 3) { // Ensure the correct number of arguments
            printUsage();
            return EXIT_FAILURE;
        }
        buildIni(argv[2]); // Build initial configuration
        return EXIT_SUCCESS;
    }

    // Validate the arguments for encryption/decryption
    if (argc < 6 || (strcmp(argv[1], "-e") != 0 && strcmp(argv[1], "-d") != 0) || strcmp(argv[4], "-r") != 0) {
        printUsage();
        return EXIT_FAILURE;
    }

    int r1 = atoi(argv[5]); // Convert rotor 1 start position to integer
    int r2 = atoi(argv[6]); // Convert rotor 2 start position to integer
    // Check if configuration file is provided
    if (argc == 9 && strcmp(argv[7], "-i") == 0) {
        buildIni(argv[8]); // Build initial configuration from file
    }

    buildRotors(rotor1, rotor2); // Build the rotors
    setRotor1(rotor1, r1);       // Set the starting position of rotor 1
    setRotor2(rotor2, r2);       // Set the starting position of rotor 2

    FILE *infile = fopen(argv[2], "r");   // Open input file for reading
    FILE *outfile = fopen(argv[3], "w");  // Open output file for writing
    // Check if files were opened successfully
    if (infile == NULL || outfile == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    // Check if the mode is encryption
    if (strcmp(argv[1], "-e") == 0) {
        perror("Step 1x");
        encryptFile(infile, outfile, rotor1, rotor2); // Encrypt the file
    } 
    // Check if the mode is decryption
    else if (strcmp(argv[1], "-d") == 0) {
        decryptFile(infile, outfile, rotor1, rotor2); // Decrypt the file
    } else {
        printUsage();
        fclose(infile);
        fclose(outfile);
        return EXIT_FAILURE;
    }

    // Close the input and output files
    fclose(infile);
    fclose(outfile);
    return EXIT_SUCCESS; // Return success
}