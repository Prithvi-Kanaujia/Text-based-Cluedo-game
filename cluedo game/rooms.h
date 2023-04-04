#include <stdlib.h>
#include <string.h>
#include<stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>

struct Room {
     char *name;
     struct Room* North;
     struct Room* South;
     struct Room* East;
     struct Room* West;
     struct Item* roomItemList;
     char *character;
     int roomNum;
};
 
struct Room* newRoom(char *Name, struct Room* North, struct Room* South, struct Room* East, struct Room* West, struct Item* itemList, char* character, int roomNum);
