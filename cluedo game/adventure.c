#include <stdlib.h>
#include <string.h>
#include<stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>  
#include "items.h"
#include "rooms.h" 




void swap(int *a, int *b) {
   int temp = *a;
   *a = *b;
   *b = temp;
}
 
void randomize(int arr[], int n) {
  
   srand(time(NULL));
   int i;
   for(i = n-1; i > 0; i--) {
       int j = rand() % (i+1);
       swap(&arr[i], &arr[j]);
   }
}





int main() {
  
   struct Item *wrench = NULL;
   struct Item *revolver = NULL;
   struct Item *dagger = NULL;
   struct Item *candle = NULL;
   struct Item *rope = NULL;
   struct Item *pipe = NULL;
 
wrench = newItem("wrench",NULL);
revolver = newItem("revolver",NULL);
dagger = newItem("dagger",NULL);
candle = newItem("candle",NULL);
rope = newItem("rope",NULL);
pipe = newItem("pipe",NULL);
struct Item **inventoryPtr =NULL;
struct Item **headInventoryPtr =NULL;
struct Item *items[6] = {wrench,revolver,rope,pipe,dagger,candle}; // take out

 
int add_to_inventory(char itemToAdd[10]) {
int i =0;
for (i=0;i<6;i++) {
   if (strcmp(items[i]->item_name, itemToAdd) ==0) {// to change itemStr) {
       if (headInventoryPtr == NULL) {
           inventoryPtr = &items[i];
           (*inventoryPtr)->next =NULL;
           headInventoryPtr = inventoryPtr;
       }
       else {
       items[i]->next = (*inventoryPtr);
       inventoryPtr = &items[i];
       //remove from rrom
       }
   }
}
return 0;
}
 
struct Room *room1 = NULL;
struct Room *room2 = NULL;
struct Room *room3 = NULL;
struct Room *room4 = NULL;
struct Room *room5 = NULL;
struct Room *room6 = NULL;
struct Room *room7 = NULL;
struct Room *room8 = NULL;
struct Room *room9 = NULL;
 
room1 = newRoom("kithcen", NULL, room4, room2,NULL,wrench,"bob",1);
room2 = newRoom("hall", NULL,room5,room3,room1,NULL,"frank",2);
room3 = newRoom("ballroom", NULL,room6,NULL,room2,revolver,NULL,3);
room4 = newRoom("conservatory", room1,room7, room5,NULL,rope,NULL,4);
room5 = newRoom("dining room", room2,room8,room6,room4,NULL,"harry",5);
room6 = newRoom("cellar", room3,room9,NULL,room5,dagger,"talia",6);
room7 = newRoom("library", room4,NULL,room8,NULL,NULL,NULL,7);
room8 = newRoom("lounge", room5,NULL,room9,room7,candle,NULL,8);
room9 = newRoom("study", room6,NULL,NULL,room8,pipe,"alicia",9);
//room1 = newRoom("room1", NULL,room4, room2,NULL,NULL,NULL,1);
room1->South = room4;
room1->East = room2;
room2->East = room3;
room2->South = room5;
room3->South = room6;
room4->South = room7;
room4->East = room5;
room5->East = room6;
room5->South = room8;
room6->South = room9;
room7->East = room8;
room8->East = room9;
int arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
int n = sizeof(arr)/ sizeof(arr[0]);

char *itemStrList[] = {"wrench", "rope", "pipe", "dagger", "candle", "revolver"};
char *itemAns;
char *characterStrList[] = {"frank", "bob", "talia", "harry", "alicia"};
char *characterAns;
char *roomStrList[] = {"kitchen", "hall", "conservatory", "dining room", "cellar", "libray", "lounge","study"};
char *roomAns;
randomize (arr, n);
int index = arr[5];
itemAns = itemStrList[index];
randomize (arr, n);
 index = arr[5];
characterAns = characterStrList[index];
randomize (arr, n);
 index = arr[5];
roomAns = roomStrList[index];
 
//---------------------------------------------------------------------------------------
 
bool found_in_room =false;
//printf("%s",room7->East->roomItemList->item_name);
int attempts =0;
bool success =false; 
while (attempts < 10 && success ==false ) {
    char command[10];

    printf("Enter a command to begin\n");
    scanf("%9s",command);

    
    struct Room *roomPtr =room1;
    struct Item *roomItemListPtr;
    roomItemListPtr = roomPtr->roomItemList;
    
    bool valid=false;
    while (strcmp(command,"look") != 0 && strcmp(command,"help") != 0 &&
    strcmp(command,"go") != 0 && strcmp(command,"take") != 0 && strcmp(command,"drop") != 0 &&
    strcmp(command,"inventory") != 0 &&strcmp(command,"list") != 0 && strcmp(command,"clue") != 0) {
        printf("Invalid command. Try again or type help to find a list of commands\n");
        scanf("%9s",command);
    }
    
    if(strcmp(command,"look") ==0) {
        printf("You are in %s \n",roomPtr->name);
        printf("Items in the room: \n");
        
        while (roomItemListPtr !=NULL) {
            printf("%s\n", roomItemListPtr->item_name);
            roomItemListPtr = roomItemListPtr->next;
        }
        roomItemListPtr = roomPtr->roomItemList;
    
        printf("%s is in the North\n", roomPtr->North->name);
        printf("%s is in the South\n", roomPtr->South->name);
        printf("%s is in the East\n", roomPtr->East->name);
        printf("%s is in the West\n", roomPtr->West->name);
        printf("character in the room: \n %s", roomPtr->character);
    }
    if(strcmp(command,"help") ==0) {
        printf("type 'go' and then a compass direction to go to another room\n");
        printf("type 'take' and then an item to pick it up and add it to your inventory \n");
        printf("type 'look' to see everthying in your room\n");
        printf("type 'inventory' to see everthying in your posession\n");
        printf("type 'drop' to remove an item from your inventory \n");
        printf("type 'clue' to make a guess\n");
        printf("type 'list' to see every charcater, room and item in the game\n");
    }
    
        if(strcmp(command,"take") ==0) {
        char itemToAdd[10];
        printf("Enter an item in the room to pick up \n");
        scanf("%9s",itemToAdd);
        while (roomItemListPtr !=NULL) {
            if(strcmp(roomPtr->roomItemList->item_name,itemToAdd)==0) {
                roomPtr->roomItemList = roomPtr->roomItemList->next;
                add_to_inventory(itemToAdd);
                printf("item added\n");
                found_in_room =true;
                roomItemListPtr = roomItemListPtr->next;
            }
            if (strcmp(roomItemListPtr->next->item_name,itemToAdd) != 0) {
                roomItemListPtr = roomItemListPtr->next;
            }
            else {
                add_to_inventory(itemToAdd);
                printf("item added\n");
                found_in_room =true;
                roomItemListPtr->next = roomItemListPtr->next->next;
                //remove from rrom list
            }
        }
        if(!found_in_room) {
            printf("item not in room or does not exist\n");
        }
        roomItemListPtr = roomPtr->roomItemList;
        }
    
    
    
    
    
        if(strcmp(command,"inventory") ==0) {
        inventoryPtr = headInventoryPtr;
        while(inventoryPtr !=NULL) {
            printf("items in possession:\n");
            printf("%s\n",(*inventoryPtr)->item_name);
            inventoryPtr= &((*inventoryPtr)->next);
            }//create inventory
        }
    
        if(strcmp(command,"drop") ==0) {
        char itemToDrop[10];
        printf("Enter an item in the room to drop \n");
        scanf("%9s",itemToDrop);

        bool found_in_inventory =false;
        inventoryPtr = headInventoryPtr;
        struct Item **nextInventoryPtr = &((*inventoryPtr)->next);
        if (strcmp((*headInventoryPtr)->item_name,itemToDrop) == 0) { //if first invenotry is empty
            headInventoryPtr = nextInventoryPtr; // new head= next if item in head
            roomItemListPtr = roomPtr->roomItemList;
            while(roomItemListPtr->next !=NULL) { //iterate to end of room items list
                roomItemListPtr = roomItemListPtr->next;
            }
            if(roomPtr->roomItemList==NULL) { //if  room item list is empty
                roomPtr->roomItemList = (*inventoryPtr); // dropped item becomes room items lists head
                // printf("item dropped");
            }
            else {//if room items lists is not empty
                roomItemListPtr->next = (*inventoryPtr); //add dropped item to the end
                
            }
            found_in_inventory =true;
            printf("item dropped\n");
        }  
        else { // if inventory isnt empty
            while ((*nextInventoryPtr) !=NULL) { //iterate through inventory
                if (strcmp((*nextInventoryPtr)->item_name,itemToDrop) != 0) {
                    inventoryPtr =nextInventoryPtr; //prev = curr
                    nextInventoryPtr = &((*nextInventoryPtr)->next); //curr= curr->next
                }
                else {
                    roomItemListPtr = roomPtr->roomItemList; //initlaise to head
                    while(roomItemListPtr->next !=NULL) { //iternate to end of room itemlist
                        roomItemListPtr = roomItemListPtr->next;
                    }
                    if(roomPtr->roomItemList==NULL){ //if room items lits is empty
                        roomPtr->roomItemList = (*nextInventoryPtr);
                        (*inventoryPtr)->next = ((*nextInventoryPtr)->next);//skip dropped item
                    }
                    else {
                        roomItemListPtr->next = (*nextInventoryPtr);
                        (*inventoryPtr)->next = ((*nextInventoryPtr)->next);
                    }
                    printf("item dropped\n");
                    found_in_inventory =true;
                }
            }
        }
        if(!found_in_inventory) {
            printf("item not in room or does not exist\n");
        }
        }
    
        if(strcmp(command,"list") ==0) {
            printf("Items list: dagger, wrench, revolver, rope, pipe, candle\n");
            printf("Rooms list: kitchen, hall, ball room, dining room, conservatory, cellar, library, lounge,study\n");
            printf("characters list: bob, frank, harry, talia, alicia\n"); 
        }
        
        if(strcmp(command,"go") ==0) {
        bool valid_direction =false;
        printf("Enter a direction (north,south,east,west) \n");
        char direction[7];
        while(!valid_direction) {
            scanf("%9s",direction);

            for(int i = 0; direction[i]; i++){
                direction[i] = tolower(direction[i]);
                }
            if(strcmp(direction,"north") ==0) {
                if (roomPtr->North !=NULL) {
                    valid_direction =true;
                    roomPtr = roomPtr->North;
                }
                printf("You are in the %s\n",roomPtr->name);
                break;
            }
            else if(strcmp(direction,"south") ==0) {
                if (roomPtr->South !=NULL) {
                    valid_direction =true;
                    roomPtr = roomPtr->South;
                }
                printf("You are in the %s\n",roomPtr->name);
                break;
            }
            else if(strcmp(direction,"east") ==0) {
                if (roomPtr->East !=NULL) {
                    valid_direction =true;
                    roomPtr = roomPtr->East;
                }
                printf("You are in the %s \n",roomPtr->name);
                break;
            }
            else if(strcmp(direction,"west") ==0) {
                if (roomPtr->West !=NULL) {
                    valid_direction =true;
                    roomPtr = roomPtr->West;
                }
                printf("You are in the %s\n",roomPtr->name);
                break;
            }
            else {
                printf("Invalid direction. Try again.");
            }
            
        }
        }
    
    
        if(strcmp(command,"clue") ==0) {
        printf("Enter a character's name: \n");
        char character_name[10];
        scanf("%9s",character_name);
        int how_many_correct = 0;
        for(int i = 0; character_name[i]; i++){
            character_name[i] = tolower(character_name[i]);
            }
        // for(int i = 0; character_name[i]; i++){
        //     character_name[i] = tolower(character_name[i]);
        //     }
        while (strcmp(character_name,"frank") != 0 && strcmp(character_name,"bob") != 0 &&
    strcmp(character_name,"talia") != 0 && strcmp(character_name,"harry") != 0 && strcmp(character_name,"alicia") != 0) {
        printf("Invalid character. Try again");
        scanf("%9s",character_name);
        for(int i = 0; character_name[i]; i++) {
            character_name[i] = tolower(character_name[i]);
                }
    }
        //scanf("%9s",character_name);
        // for(int i = 0; character_name[i]; i++) {
        //     character_name[i] = tolower(character_name[i]);
        //         }
        
            
        if(strcmp(character_name,characterAns) ==0) {
            printf("Character Match\n"); 
            how_many_correct += how_many_correct +1;          
        }
        if (strcmp(roomPtr->name,roomAns) ==0) {
            printf("Room Match\n");
            how_many_correct += how_many_correct +1;   
        }
        inventoryPtr = headInventoryPtr;
        while(inventoryPtr!=NULL) {
            if (strcmp((*inventoryPtr)->item_name,itemAns)==0) {
                printf("Item Match");
                how_many_correct += how_many_correct +1;   
            } else {
                inventoryPtr = &(*inventoryPtr)->next;
            }
        }
        roomItemListPtr = roomPtr->roomItemList;
        while(roomItemListPtr!=NULL) {
            if (strcmp(roomItemListPtr->item_name,roomAns)==0) {
                printf("Item Match");
                how_many_correct += how_many_correct +1;   
            }
            roomItemListPtr = roomItemListPtr->next;
            }
        if (how_many_correct ==3) {
            success = true;
        }else {
            attempts += attempts +1;
        }

        }
        if (success) {
            printf("CORRECT!");
        }

}


    free(room1);
    free(room2);
    free(room3);
    free(room4);
    free(room5);
    free(room6);
    free(room7);
    free(room8);
    free(room9);
    free(wrench);
    free(dagger);
    free(pipe);
    free(revolver);
    free(rope);
    free(candle);
 
 return 0;
}
 
 
 
 
 
