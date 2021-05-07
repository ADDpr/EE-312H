// String ADT <Project3.cpp>
// EE 312 Project 3 submission by
// <Anthony Do>
// <add3254>
// Slip days used: <0>
// Spring 2021
// Copy and paste this file at the top of all your submitted source code files.  Do not turn this in by itself.

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "UTString.h"

/*
 * Helper macro to find the signature of a UTString
 * Treat this like a function that takes a UTString*
 * Accesses a uint32_t from where the signature should be located
 */
#define CHECK(s) (*(uint32_t*) ((s)->string + (s)->length + 1))

/*
 * Checks if a UTString is valid or not.
 */
bool isOurs(const UTString* s) {
    if (CHECK(s) == SIGNATURE) { return true; }
    else { return false; }
}

/*
 * Allocate a utstring on the heap.
 * Initialize the string correctly by copying src.
 * Return a pointer to the UTString.
 */
UTString* utstrdup(const char* src) {
    UTString *str = (UTString*)malloc(sizeof(UTString));
    str->length = strlen(src);
    str->capacity = str->length;
    str->string = (char*)malloc(strlen(src) * sizeof(char) + 5);
    //strcpy(str->string, src);
    for(uint32_t i = 0; i <= str->length; i++){
        str->string[i] = src[i];
    }
    CHECK(str) = SIGNATURE;
    return str;
}

/*
 * Returns the length of s.
 *  s must be a valid UTString.
 */
uint32_t utstrlen(const UTString* s) {
    assert(isOurs(s));
    //return strlen(s->string);
    uint32_t i = 0;
    while(s->string[i] != '\0')
    {
        i++;
    }
    return i;
}

/*
 * Append the string suffix to the UTString s.
 *  s must be a valid UTString.
 * Do not allocate any additional storage: only append as many characters
 *  as will actually fit in s.
 * Update the length of s.
 * Return s with the above changes. */
UTString* utstrcat(UTString* s, const char* suffix) {
    assert(isOurs(s));
    int max = s->capacity - s->length;  
    //strncpy(s->string + (s->length*sizeof(char)), suffix, max);
    //s->string = strncat(s->string, suffix, max);
    int i = 0;
    while ((suffix[i] != '\0') && i < max)
    {
        s->string[s->length + i] = suffix[i];
        i++;
    }
    s->string[s->length + i] = '\0';
    s->length += i;
    CHECK(s) = SIGNATURE;
    return s;
}

/*
 * Copy src into dst.
 *  dst must be a valid UTString.
 *  src is an ordinary string.
 * Do not allocate any additional storage: only copy as many characters
 *  as will actually fit in dst.
 * Update the length of dst.
 * Return dst with the above changes.
 */
UTString* utstrcpy(UTString* dst, const char* src) {
    assert(isOurs(dst));
    uint32_t i = 0;
    if(dst->capacity > strlen(src)){
        //strcpy(dst->string, src);
        for(i; i <= strlen(src); i++){
            dst->string[i] = src[i];
        }
    }
    else{
        //strncpy(dst->string, src, dst->capacity);
        for(i; i < dst->capacity; i++){
            dst->string[i] = src[i];
        }
        dst->string[i] = '\0';
    }
    dst->length = i;
    CHECK(dst) = SIGNATURE;
    return dst;
}

/*
 * Free all memory associated with the given UTString.
 */
void utstrfree(UTString* self) {
    free(self->string);
    free(self);
}

/*
 * Make s have at least as much capacity as new_capacity.
 *  s must be a valid UTString.
 * If s has enough capacity already, do nothing.
 * If s does not have enough capacity, then allocate enough capacity,
 *  copy the old string and the null terminator, free the old string,
 *  and update all relevant metadata.
 * Return s with the above changes.
 */
UTString* utstrrealloc(UTString* s, uint32_t new_capacity) {
    assert(isOurs(s));
    if(s->capacity >= new_capacity){
        return s;
    }
    //char* dst = malloc((new_capacity * sizeof(char)) + 5);
    //strcpy(dst, s->string);
    //free(s->string);
    //s->string = dst;
    s->string = (char*)realloc(s->string, (new_capacity * sizeof(char)) + 5);
    s->capacity = new_capacity;
    //s->length = strlen(s->string);
    CHECK(s) = SIGNATURE;
    return s;
}
