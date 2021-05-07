// SuperStrings <Project1.cpp>
// EE 312 Project 1 submission by
// Anthony Do
// add3254
// Slip days used: <0>
// Spring 2021
// Copy-paste contents of this file at the top of every .c or .h file that you write or modify.

#include <stdio.h> // provides declarations for printf and putchar
#include <stdint.h> // provides declarations for int32_t uint32_t and the other (new) standard C types
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*
All of your code must be in this file. Please no #includes other than standard system headers (ie.., stdio.h, stdint.h)

You must write this function (printSuperStrings). Do not change the way the function is declared (i.e., it has
exactly two parameters, each parameter is a standard (mundane) C string (see Instruction).
*/

/*
Precondition: Takes a pointer to a string and superString
Postcondition: Returns an int true (1) or false (0) if it's a superString
*/
int isSuperString(char *string, char *superString)
{
    int stringPos = 0;
    int superStringLen = strlen(superString);
    int stringLen = strlen(string);
    for(int i = 0; i < superStringLen; i++){
        if(superString[i] == string[stringPos]){ //comparing the characters of superString w/ string in order
            stringPos++; //increment position of compared string
        }
        if(stringPos == stringLen){
            return 1; 
        }
        /*
        if stringPos is the same as string length, 
        then superString chars showed up in the same order as compared string;
        it's a superString
        */  
    }
    return 0;
}

/*
Precondition: Takes two arrays of the same size
Postcondition: Copies char array s to sCopy
*/
void copyArray(char s[], char sCopy[]){
    for(int i = 0; i < strlen(s); i++){
        sCopy[i] = s[i];
    }
}

/*
Precondition: Takes string and superString array
Postcondition: Prints the matching superStrings
*/
void printSuperStrings(char targets[], char candidates[]) {
    for(int i = 0; i < strlen(targets); i++){ //formatting arrays to change any space between chars to spaces
        if(!isalpha(targets[i])){
            targets[i] = ' ';
        }
    }

    for(int i = 0; i < strlen(candidates); i++){ //formatting arrays to change any space between chars to spaces
        if(!isalpha(candidates[i])){
            candidates[i] = ' ';
        }
    }

    char *targetsPointer = targets;
    char candidatesCopy[strlen(candidates)]; //strtok_r modifies the original array so we need a copy

    char *targetsToken, *candidatesToken;
    while(targetsToken = strtok_r(targetsPointer, " ", &targetsPointer)){ //splits the char array into a string at delimiter (space char)
        copyArray(candidates, candidatesCopy); 
        char *candidatesPointer = candidatesCopy;
        while(candidatesToken = strtok_r(candidatesPointer, " ", &candidatesPointer)){
            if(isSuperString(targetsToken, candidatesToken)){
                printf("%s\n", candidatesToken);
            }
        }
    }
}
