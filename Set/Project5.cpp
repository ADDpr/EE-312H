// Set <Project5.cpp>
// EE 312 Project 5 submission by
// Anthony Do
// add3254
// Slip days used: <0>
// Fall 2021
// Copy-Paste the above lines at the top of your submitted files.


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Set.h"

/*
 * Several of the required functions have been written already
 * You may use these functions as-is or you may modify them in any way.
 * Please NOTE, you are responsible for ensuring that the functions work correctly in
 * your project solution. Just because the function works correctly in my solution does
 * NOT mean that the function will work correctly in yours.
 */

/*
 * Design NOTES:
 *
 * The design provided in this starter kit assumes
 * (1) empty sets will be represented with length == 0 and elements == nullptr (i.e., address 0)
 * (2) amortized doubling is not used, and capacity is ignored/unused. Functions should assume that
 * the amount of storage available in the elements[] array is equal to length
 */



/* done for you already */
void destroySet(Set* self) {
    free(self->elements);
}

/* done for you already */
void createEmptySet(Set* self) {
    self->len = 0;
    self->elements = nullptr;
}

/* done for you already */
void createSingletonSet(Set* self, int x) {
    self->elements = (int*) malloc(sizeof(int));
    self->elements[0] = x;
    self->len = 1;
}

/* done for you already */
void createCopySet(Set* self, const Set* other) {
    self->elements = (int*) malloc(other->len * sizeof(int));
    for (int k = 0; k < other->len; k += 1) {
        self->elements[k] = other->elements[k];
    }
    self->len = other->len;
}

/* done for you already */
void assignSet(Set* self, const Set* other) {
    if (self == other) { return; }

    destroySet(self);
    createCopySet(self, other);
}

/* return true if x is an element of self */
bool isMemberSet(const Set* self, int x) {
    int r = (self->len-1);
    int l = 0;
    int i = (r+l)/2;
    while(r >= l){
        if(x == self->elements[i]){
            return true;
        }
        else if(x > self->elements[i]){
            l = i+1;
            i = (r+l)/2;
        }
        else if(x < self->elements[i]){
            r = i-1;
            i = (r+l)/2;
        }
    }
    return false;
}

/*
 * add x as a new member to this set.
 * If x is already a member, then self should not be changed
 * Be sure to restore the design invariant property that elemnts[] remains sorted
 * (yes, you can assume it is sorted when the function is called, that's what an invariant is all about)
 */
void insertSet(Set* self, int x) {
    if(self->len == 0){
        self->len++;
        self->elements = (int *)realloc(self->elements, (self->len)*sizeof(int));
        self->elements[0] = x;
    }else{
        int r = (self->len-1);
        int l = 0;
        int i = (r+l)/2;
        while(r >= l){
            if(x == self->elements[i]){
                r = -1; //break from loop
                i = -1; //i is already in the set
            }
            else if(x > self->elements[i]){
                l = i+1;
                i = (r+l)/2;
            }
            else if(x < self->elements[i]){
                r = i-1;
                i = (r+l)/2;
            }
        }
        if(i != -1){ //if i is already in the set, don't do anything
            self->len++;
            self->elements = (int *)realloc(self->elements, (self->len)*sizeof(int));
            int temp = 0;
            int next = 0;
            if(x > self->elements[i]){
                if(i == self->len-2){
                    self->elements[i+1] = x;
                }else{
                    temp = self->elements[i+1];
                    self->elements[i+1] = x;
                    int k = i+1;
                    for(k; k < self->len-2; k++){
                        next = self->elements[k+1];
                        self->elements[k+1] = temp;
                        temp = next;
                    }
                    self->elements[k+1] = temp;
                }
            }
            else if(x < self->elements[i]){
                temp = self->elements[i];
                self->elements[i] = x;
                int m = i+1;
                for(m; m < self->len-1; m++){
                    next = self->elements[m];
                    self->elements[m] = temp;
                    temp = next;
                }
                self->elements[m] = temp;
            }
        }
    }
}


/*
 * don't forget: it is OK to try to remove an element
 * that is NOT in the set.
 * If 'x' is not in the set 'self', then
 * removeSet should do nothing (it's not an error)
 * Otherwise, ('x' IS in the set), remove x. Be sure to update self->length
 * It is not necessary (nor recommended) to call malloc -- if removing an element means the
 * array on the heap is "too big", that's almost certainly OK, and reallocating a smaller array
 * is almost definitely NOT worth the trouble
 */
void removeSet(Set* self, int x) {
    int r = (self->len-1);
    int l = 0;
    int i = (r+l)/2;
    int flag = 0;
    while(r >= l){
        if(x == self->elements[i]){
            r = -1; //break from loop
            flag = 1; //i is in the set
        }
        else if(x > self->elements[i]){
            l = i+1;
            i = (r+l)/2;
        }
        else if(x < self->elements[i]){
            r = i-1;
            i = (r+l)/2;
        }
    }
    if(flag == 1){ //if i is in set, do:
        //int temp = self->elements[i+1];
        int temp;
        int k = 0;
        k = i;
        for(k; k < (self->len)-1; k++){
            temp = self->elements[k+1];
            self->elements[k] = temp;
        }
        self->len--;
    }
}

/* done for you already */
void displaySet(const Set* self) {
    int k;

    printf("{");

    if (self->len == 0) {
        printf("}");
    }
    else {
        for (k = 0; k < self->len; k += 1) {
            if (k < self->len - 1) {
                printf("%d,", self->elements[k]);
            } else {
                printf("%d}", self->elements[k]);
            }
        }
    }
}

/* return true if self and other have exactly the same elements */
bool isEqualToSet(const Set* self, const Set* other) {
    if(self->len != other->len){
        return false;
    }
    //the lengths are equal
    for(int i = 0; i < self->len; i++){
        if(self->elements[i] != other->elements[i]){
            return false;
        }
    }
    return true;
}

/* return true if every element of self is also an element of other */
bool isSubsetOf(const Set* self, const Set* other) {
    if(self->len == 0){
        return true;
    }
    if(self->len > other->len){
        return false;
    }
    int i = 0;
    int j = 0;
    while((i < self->len) && (j < other->len)){
        if(self->elements[i] == other->elements[j]){
            i++;
            j++;
        }
        else if(self->elements[i] < other->elements[j]){
            return false;
        }
        else if(self->elements[i] > other->elements[j]){
            i++;
        }
    }
    if(i < self->len){
        return false;
    }else{
        return true;
    }
    /*Set test;
    createCopySet(&test, other);
    for(int i = 0; i < self->len; i++){
        insertSet(&test, self->elements[i]);
    }
    if(other->len == test.len){
        destroySet(&test);
        return true;
    }
    destroySet(&test);
    return false;*/
}

/* done for you */
bool isEmptySet(const Set* self) {
    return self->len == 0;
}

/* remove all elements from self that are not also elements of other */
void intersectFromSet(Set* self, const Set* other) {
    int i = 0;
    int j = 0;
    int temp;
    int* newSelf = (int*) malloc(self->len*sizeof(int));
    int newSize = 0;
    while((i < self->len) && (j < other->len)){
        if(self->elements[i] == other->elements[j]){
            temp = self->elements[i];
            newSelf[newSize] = temp;
            newSize++;
            i++;
            j++;
        }
        else if(self->elements[i] > other->elements[j]){
            j++;
        }
        else if(self->elements[i] < other->elements[j]){
            i++;
        }
    }
    free(self->elements);
    self->elements = newSelf;
    self->len = newSize;

}

/* remove all elements from self that are also elements of other */
void subtractFromSet(Set* self, const Set* other) {
    if((other->len > 0) && (self->len > 0)){
        int i = 0;
        int j = 0;
        int temp;
        int* newSelf = (int*) malloc(self->len*sizeof(int));
        int newSize = 0;
        while((i < self->len) && (j < other->len)){
            if(self->elements[i] == other->elements[j]){
                i++;
                j++;
            }
            else if(self->elements[i] > other->elements[j]){
                j++;
            }
            else if(self->elements[i] < other->elements[j]){
                temp = self->elements[i];
                newSelf[newSize] = temp;
                newSize++;
                i++;
            }
        }
        while((i < self->len)){
            temp = self->elements[i];
            newSelf[newSize] = temp;
            newSize++;
            i++;
        }
        free(self->elements);
        self->elements = newSelf;
        self->len = newSize;
    }
}

/* add all elements of other to self (obviously, without creating duplicate elements) */
void unionInSet(Set* self, const Set* other) {
    int i = 0;
    int j = 0;
    int temp;
    int* newSelf = (int*) malloc(((self->len)+(other->len))*sizeof(int));
    int newSize = 0;
    while((i < self->len) && (j < other->len)){
        if(self->elements[i] == other->elements[j]){
            temp = self->elements[i];
            newSelf[newSize] = temp;
            newSize++;
            i++;
            j++;
        }
        else if(self->elements[i] > other->elements[j]){
            temp = other->elements[j];
            newSelf[newSize] = temp;
            newSize++;
            j++;
        }
        else if(self->elements[i] < other->elements[j]){
            temp = self->elements[i];
            newSelf[newSize] = temp;
            newSize++;
            i++;
        }
    }
    while((i < self->len)){
        temp = self->elements[i];
        newSelf[newSize] = temp;
        newSize++;
        i++;
    }
    while((j < other->len)){
        temp = other->elements[j];
        newSelf[newSize] = temp;
        newSize++;
        j++;
    }
    free(self->elements);
    self->elements = newSelf;
    self->len = newSize;
}
