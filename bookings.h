#include"trains.h"



//structure to store booking details
typedef struct bookingList
{
  int booking_id;             // Booking id of customer
  int fare;                   // Total paybale fare by customer
  int train_id;               // Train id
  int userid;            // Customer id
  int no_of_passengers;      //number of passengers
  int choiceclass;         //class1 or class2
  struct bookingList *next;//pointer to next node
}bnode;






//total bookings counter
int totalBookings(bnode*);

//view_trains function to search trains between a source and destination
void view_trains(tnode*, char*, char*);

//availablebookings function to search trains between a source and destination that have required seats available
void availableBookings(tnode *, char *, char *, int , int );
//function to update available seats when user books or cancells ticket
void update_available_seats(int , int ,int,int );

//function to display single train using trainID
void displaySingleTrain(tnode* ,int );
//function to view previous booking
void display_booking(tnode* ,int,int);


//function to read bookings from file
bnode *readBookings();
//function to write bookings LL to file
void writeBookings(bnode * );
//function to generate unique bookingID
int booking_id();
//function to get fare for specified class of specified train
int getfare(tnode *, int , int );
//function to book ticket
void book_ticket(tnode *, int );




//function to modify booking
void modifyBooking(int);
//function to cancel booking
void deleteBooking(int);
//function to add booking to cancelled booking file
void addCancel(bnode*);
//function to display csncelled bookings
void display_cancelled_booking(tnode*, int);
//function to read cancelled bookings from file
bnode *readCancelledBookings();


