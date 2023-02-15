

#include"trains.h"



//struct LL to store passengers details in a bnode
typedef struct passengersList{
    char category[15];      //category of passenger i.e. military,senior citizen, ladies, children and none.
    char passenger_name[20];// name of passenger
    char gen[6];      //gender
    int age;          //age
    int booking_id;   //unique booking ID 
    int no_of_passengers; //number of passengers travelling with this passenger
    struct passengersList *next;//pointer to next node
}pnode;




//function to display passengers using bookingID
void displayPassengers(int );
//function to read passengers from file
pnode* readPassengers();
//function to get passengers details
void add_passengers(int , int );
//function to write passenger LL to file
void writePassengers(pnode *);