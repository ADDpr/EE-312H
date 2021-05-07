// CRM in CPP <CustomerDB.cpp>
// EE 312 Project 7 submission by
// <Anthony Do>
// <add3254>
// Slip days used: <0>
// Spring 2021
#include <iostream>
#include <cassert>
#include "UTString.h"
#include "CustomerDB.h"

using namespace std;

const int default_capacity = 1;

Customer::Customer(UTString name) { // done, please do not edit
    this->bottles = 0;
    this->rattles = 0;
    this->diapers = 0;
    this->name = name;
}

CustomerDB::CustomerDB(void) { // done, please do not edit
    this->capacity = default_capacity;
    this->data = new Customer[this->capacity];
    this->length = 0;
}

int CustomerDB::size(void) { // done, please do not edit
    return this->length;
}

CustomerDB::~CustomerDB(void) { // done, please do not edit
    delete[] this->data;
}



void CustomerDB::clear(void) { // done, please do not edit
    delete[] this->data;
    this->capacity = default_capacity;
    this->data = new Customer[this->capacity];
    this->length = 0;
}

Customer& CustomerDB::operator[](int k) { // done, please do not edit
    assert(k >= 0 && k < this->length);
    return this->data[k];
}
using namespace std;
Customer& CustomerDB::operator[](UTString name) { // not done, your effort goes here
    if(isMember(name) == true){
        for(int i = 0; i < this->length; i++){
        if(name == this->data[i].name){
            return this->data[i];
        }
    }
        /*int r = (this->length-1);
        int l = 0;
        int i = (r+l)/2;
        while(r >= l){
            int x = name.compare(this->data[i].name);
            if(x == 0){
                return this->data[i];
            }
            else if(x > 0){
                l = i+1;
                i = (r+l)/2;
            }
            else if(x < 0){
                r = i-1;
                i = (r+l)/2;
            }
        }doesn't work because string compare*/
    }
    if(this->length + 1 == this->capacity){
        Customer *newDB = new Customer[this->capacity * 2];
        for(int i = 0; i < this->length; i++){
            newDB[i] = this->data[i];
        }
        delete[] this->data;
        this->capacity = this->capacity * 2;
        newDB[this->length] = Customer(name);
        this->data = newDB;
    }
    this->data[this->length] = Customer(name);
    this->length++;
    return this->data[this->length - 1];
}

bool CustomerDB::isMember(UTString name) { // not done, your effort goes here
    /*int r = (this->length-1);
    int l = 0;
    int i = (r+l)/2;
    while(r >= l){
        if(name == this->data[i].name){
            return true;
        }
        else if(name > this->data[i].name){
            l = i+1;
            i = (r+l)/2;
        }
        else if(name < this->data[i].name){
            r = i-1;
            i = (r+l)/2;
        }
    }doesn't work because string compare*/ 
    for(int i = 0; i < this->length; i++){
        if(name == this->data[i].name){
            return true;
        }
    }
    return false;
}
