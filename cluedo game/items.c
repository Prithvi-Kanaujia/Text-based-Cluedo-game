
#include <stdlib.h>
#include <string.h>
#include<stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>
#include "items.h"

struct Item* newItem(char *Name, struct Item* next) {
   struct Item* item = (struct Item*)malloc(sizeof(struct Item));
   if(item ==NULL) {return NULL;}
   item->item_name = Name;
   item->next = next;
   return item;
};
