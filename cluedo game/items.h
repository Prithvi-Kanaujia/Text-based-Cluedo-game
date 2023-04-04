#include <stdlib.h>
#include <string.h>
#include<stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>


struct Item {
   char *item_name;
   struct Item* next;
};
//struct Item *last = NULL;
 
struct Item* newItem(char *Name, struct Item* next);
