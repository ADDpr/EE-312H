/* 
 * EE312 Simple CRM Project
 *
 * EE 312 Project 4 submission by
 * Anthony Do
 * add3254
 * Slip days used: <0>
 * Spring 2021
 */

#include <stdio.h>
#include <assert.h>
#include "MyString.h"
#include "Invent.h"
#include <string.h>

#define MAX_CUSTOMERS 1000
Customer customers[MAX_CUSTOMERS];
int num_customers = 0;

/* you'll probably need several more global variables */
/* and of course, you have a few functions to write */

Customer storeInventory;

/* clear the inventory and reset the customer database to empty */
void reset(void) {
	storeInventory.bottles = 0;
	storeInventory.rattles = 0;
	storeInventory.diapers = 0;
	for (int i = 0; i < num_customers+1; i++)
	{
		StringDestroy(&(customers[i].name));
	}
	
	memset(customers, 0, sizeof(customers));
	num_customers = 0;
}

void processSummarize() {
	Customer mostBottles;
	Customer mostDiapers;
	Customer mostRattles;
	int maxBottles = 0;
	int maxDiapers = 0;
	int maxRattles = 0;

	for (int i = 0; i < num_customers; i++)
	{
		if(customers[i].bottles > maxBottles){
			maxBottles = customers[i].bottles;
			mostBottles = customers[i];
		}
		if(customers[i].diapers > maxDiapers){
			maxDiapers = customers[i].diapers;
			mostDiapers = customers[i];
		}
		if(customers[i].rattles > maxRattles){
			maxRattles = customers[i].rattles;
			mostRattles = customers[i];
		}
	}
	

	printf("There are %d Bottles %d Diapers and %d Rattles in inventory\n", storeInventory.bottles, storeInventory.diapers, storeInventory.rattles);
	printf("we have had a total of %d different customers\n", num_customers);
	if(maxBottles == 0){
		printf("no one has purchased any Bottles\n");
	}else{
		StringPrint(&(mostBottles.name));
		printf(" has purchased the most Bottles (%d)\n", mostBottles.bottles);
	}
	if(maxDiapers == 0){
		printf("no one has purchased any Diapers\n");
	}else{
		StringPrint(&(mostDiapers.name));
		printf(" has purchased the most Diapers (%d)\n", mostDiapers.diapers);
	}
	if(maxRattles == 0){
		printf("no one has purchased any Rattles");
	}else{
		StringPrint(&(mostRattles.name));
		printf(" has purchased the most Rattles (%d)", mostRattles.rattles);
	}
}

void processPurchase() {
	String bottles = StringCreate("Bottles");
	String rattles = StringCreate("Rattles");
	String diapers = StringCreate("Diapers");
	String name;
	readString(&name);
	String item;
	readString(&item);
	int numItem;
	readNum(&numItem);
	int match = 0;
	if(numItem > 0){ //do not add customers who buy 0 or negative items
		for (int i = 0; i < num_customers; i++)
		{
			if(StringIsEqualTo(&name, &(customers[i].name))){
				match = 1;
				if(StringIsEqualTo(&item, &bottles)){
					if (numItem > storeInventory.bottles)
					{
						printf("Sorry ");
						StringPrint(&name);
						printf(", we only have %d Bottles\n", storeInventory.bottles);
					}else{
						customers[i].bottles += numItem;
						storeInventory.bottles -= numItem;
					}
				}else if(StringIsEqualTo(&item, &rattles)){
					if (numItem > storeInventory.rattles)
					{
						printf("Sorry ");
						StringPrint(&name);
						printf(", we only have %d Rattles\n", storeInventory.rattles);
					}else{
						customers[i].rattles += numItem;
						storeInventory.rattles -= numItem;
					}
				}else if(StringIsEqualTo(&item, &diapers)){
					if (numItem > storeInventory.diapers)
					{
						printf("Sorry ");
						StringPrint(&name);
						printf(", we only have %d Diapers\n", storeInventory.diapers);
					}else{
						customers[i].diapers += numItem;
						storeInventory.diapers -= numItem;
					}
				}
			}
		}
		if (match == 0){
			StringReAssign(&(customers[num_customers].name), &name);
			if(StringIsEqualTo(&item, &bottles)){
				if (numItem > storeInventory.bottles)
				{
					printf("Sorry ");
					StringPrint(&name);
					printf(", we only have %d Bottles\n", storeInventory.bottles);
				}else{
					customers[num_customers].bottles = numItem;
					storeInventory.bottles -= numItem;
					num_customers++;				}
				}else if(StringIsEqualTo(&item, &rattles)){
					if (numItem > storeInventory.rattles)
					{
						printf("Sorry ");
						StringPrint(&name);
						printf(", we only have %d Rattles\n", storeInventory.rattles);
					}else{
						customers[num_customers].rattles = numItem;
						storeInventory.rattles -= numItem;
						num_customers++;
					}
				}else if(StringIsEqualTo(&item, &diapers)){
					if (numItem > storeInventory.diapers)
					{
						printf("Sorry ");
						StringPrint(&name);
						printf(", we only have %d Diapers\n", storeInventory.diapers);
					}else{
						customers[num_customers].diapers = numItem;
						storeInventory.diapers -= numItem;
						num_customers++;
					}
				}
		}
	}
	
	StringDestroy(&name);
	StringDestroy(&item);
	StringDestroy(&bottles);
	StringDestroy(&rattles);
	StringDestroy(&diapers);
}

void processInventory() {
	String bottles = StringCreate("Bottles");
	String rattles = StringCreate("Rattles");
	String diapers = StringCreate("Diapers");
	String next;
	int num;
	readString(&next);
	if(StringIsEqualTo(&next, &bottles)){
		readNum(&num);
		storeInventory.bottles += num;
	}else if(StringIsEqualTo(&next, &rattles)){
		readNum(&num);
		storeInventory.rattles += num;
	}else if(StringIsEqualTo(&next, &diapers)){
		readNum(&num);
		storeInventory.diapers += num;
	}

	StringDestroy(&next);
	StringDestroy(&bottles);
	StringDestroy(&rattles);
	StringDestroy(&diapers);
}
