#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define ADMIN 1
#define USERMODE 2
#define REGISTRATION 1
#define LOGIN 2
#define EXIT 0
#define LOGOUT 9


// train structure linkedlist to store details of trains
typedef struct trainList
{
    int trainid;          	// train id
    char train_name[20];  	// train name
    int class1_seats;     	// total  seats in class 1
	int class1_available;   // available seats in class 1
    int class1_fare;      	// class 1 fare
    int class2_seats;     	// total  seats in class 2
	int class2_available;   // total available seats in class 2
    int class2_fare;      	// class 2 fare
    char source[20];      	// source station of train
    char destination[20]; 	// edestination of train
    int arrival_time;     	// arrival time at destination in hhmm format
    int departure_time;   	// departure time at source in hhmm format

    struct trainList *next;  //pointer to next node
}tnode;



//start function
void start();
//admin function
void admin();
//user functions
void usermode();

//readTrains() to read trains from file into linkedlist
tnode* readTrains();
//writeTrains() to write linkedlist of trains to file
void writeTrains(tnode *);
//add function to add details of train
void add_train();
//modify function to modify details of train
void modify_train();
//remove function to remove train
void remove_train();
//display function to display details of train
void display_train();
//count total trains stored in file
int totalTrains(tnode*);


