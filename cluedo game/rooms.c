#include <stdlib.h>
#include <string.h>
#include<stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>
#include "rooms.h"  

struct Room* newRoom(char *Name, struct Room* North, struct Room* South, struct Room* East, struct Room* West, struct Item* itemList, char* character, int roomNum) {
   struct Room* room = (struct Room*)malloc(sizeof(struct Room));
   if (room == NULL) {
       return NULL;
   }
       room->name = Name;
       room->North = North;
       room->South = South;
       room->East = East;
       room->West = West;
       room->roomItemList = itemList;
       room->character = character;
       room->roomNum=roomNum;
       return room;
}
