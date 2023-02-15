#include"trains_header.h"
#include"passengers.h"
#include"bookings.h"
#include"users.h"




/*view train function that takes trains LL, source and destination
as input and displays trains that are running from entered source and destination*/
void view_trains(tnode *trains, char *source, char *destination)
{
    tnode *thead = trains;
    while (thead != NULL)
    {
        if (strcmp(source, thead->source) == 0 && strcmp(destination, thead->destination) == 0)
        {
            printf("Train ID: %d\n", thead->trainid);
            printf("Train name: %s\n", thead->train_name);
            printf("Total class1 seats: %d\n", thead->class1_seats);
			printf("Available class1 seats: %d\n", thead->class1_available);
            printf("Class 1 fare: %d\n", thead->class1_fare);
            printf("Total class2 seats: %d\n", thead->class2_seats);
			printf("Available class2 seats: %d\n", thead->class2_available);
            printf("Class 2 fare: %d\n", thead->class2_fare);
            printf("Source: %s\n", thead->source);
            printf("Enter destination: %s\n", thead->destination);
            printf("Arrival time(in hhmm format): %d\n", thead->arrival_time);
            printf("Departure time(in hhmm format): %d\n", thead->departure_time);
        }
        thead =thead->next;
    }
}



/*availableBookings function that takes trains LL, source, destination, class
and number of passengers required as input and displays trains that are running
from entered source and destination and have seats available for number of passengers entered*/
void availableBookings(tnode *trains, char *source, char *destination, int no_of_seats, int choiceclass)
{
    tnode *thead = trains;
    while (thead != NULL)
    {
        if (strcmp(source, thead->source) == 0 && strcmp(destination, thead->destination) == 0)
        {
                if(choiceclass==1 && thead->class1_available>=no_of_seats)
                {
                    printf("\nTrain ID: %d\n", thead->trainid);
                    printf("Train name: %s\n", thead->train_name);
                    printf("Total class1 seats: %d\n", thead->class1_seats);
                    printf("Available class1 seats: %d\n", thead->class1_available);
                    printf("Class 1 fare: %d\n", thead->class1_fare);
                    printf("Source: %s\n", thead->source);
                    printf("Enter destination: %s\n", thead->destination);
                    printf("Arrival time(in hhmm format): %d\n", thead->arrival_time);
                    printf("Departure time(in hhmm format): %d\n", thead->departure_time);
                }
                else if(choiceclass==2 && thead->class2_available>=no_of_seats)
                {
                    printf("\nTrain ID: %d\n", thead->trainid);
                    printf("Train name: %s\n", thead->train_name);
                    printf("Total class2 seats: %d\n", thead->class2_seats);
                    printf("Available class2 seats: %d\n", thead->class2_available);
                    printf("Class 2 fare: %d\n", thead->class2_fare);
                    printf("Source: %s\n", thead->source);
                    printf("Enter destination: %s\n", thead->destination);
                    printf("Arrival time(in hhmm format): %d\n", thead->arrival_time);
                    printf("Departure time(in hhmm format): %d\n", thead->departure_time);
                } 
        }   
        thead = thead->next;         
    }  
}




/*function to count total bookings in LL
it'll take pointer to first node of LL and count total nodes 
i.e. total bookings and return count i.e.int value*/
int totalBookings(bnode *bookings)
{
    bnode *bhead = bookings;
    int count = 1;
    

    while (bhead->next != NULL)
    {
        bhead = bhead->next;
        count++;
    }

    return count;
}




/*displaySingleTrain function takes train LL and trainID and displays 
train with that trainID*/
void displaySingleTrain(tnode *trains, int trainid)
{
    tnode* thead =trains;
    while (thead != NULL)
    {
        if (trainid==thead->trainid)
        {
            printf("Train ID: %d\n", thead->trainid);
            printf("Train name: %s\n", thead->train_name);
            printf("Total class1 seats: %d\n", thead->class1_seats);
            printf("Class 1 fare: %d\n", thead->class1_fare);
            printf("Total class2 seats: %d\n", thead->class2_seats);
            printf("Class 2 fare: %d\n", thead->class2_fare);
            printf("Source: %s\n", thead->source);
            printf("Enter destination: %s\n", thead->destination);
            printf("Arrival time(in hhmm format): %d\n", thead->arrival_time);
            printf("Departure time(in hhmm format): %d\n", thead->departure_time);
            break;
        }       
        thead = thead->next;
    }
}

/*display function to display booking details
it takes train LL, bookingID and userID as input and 
displays bookings for that user. Displays all bookings if bookingID ==0*/
void display_booking(tnode* trains,int bookingid, int usrid){
  int userid=usrid;
  tnode* thead = trains;
  int i=0;
  bnode *bookings,*bhead;
  bookings = readBookings();//read bookings from file and store in LL
  bhead=bookings;
  //bhead have username

  while (bhead != NULL && bhead->userid==userid)
      {
        if (bookingid!=0)
        {
          if (bhead->booking_id==bookingid)
          {
            printf("Booking ID: %d\n", bhead->booking_id);
            displaySingleTrain(trains,bhead->train_id);
            displayPassengers(bookingid);
            printf("Class: %d\n",bhead->choiceclass);
            printf("Total fare: %d\n", bhead->fare);
            bhead=bhead->next;
            continue;
          }  //if
        }//if
        else
        {            
            printf("Booking ID: %d\n", bhead->booking_id);
            displaySingleTrain(trains, bhead->train_id);
            displayPassengers(bhead->booking_id);
            printf("Class: %d\n",bhead->choiceclass);
            printf("Totral Seats: %d\n", bhead->no_of_passengers);
            printf("Total fare: %d\n", bhead->fare);
            i++;
        }//else
        bhead=bhead->next;
      }//while
}//display_bookings()




/*readBookings function to read data to file
this function takes bookings pointer as argument
and read the data from the bookings.txt file, store 
the details to LL and returns pointer to first node of LL*/
bnode *readBookings()
{
    bnode *b1, *bhead = NULL, *newbnode = NULL, *btemp;
    
    b1 = (bnode*)malloc(sizeof(bnode));
    b1->next = NULL;

    FILE *bookingptr;
    bookingptr = fopen("bookings.txt", "r");//read mode

    while (fscanf(bookingptr,"%d,%d,%d,%d,%d,%d\n",&b1->booking_id,&b1->userid,&b1->train_id,&b1->no_of_passengers,&b1->fare,&b1->choiceclass)!=-1)
    {
      newbnode = (bnode *)malloc(sizeof(bnode));
      newbnode->booking_id = b1->booking_id;
      newbnode->train_id = b1->train_id;
      newbnode->no_of_passengers = b1->no_of_passengers;
      newbnode->userid=b1->userid;
      newbnode->fare = b1->fare;
      newbnode->next = NULL;

      if (bhead==NULL)
        {
            bhead=newbnode;
        }//if
        else
        {
			btemp = bhead;
            while (btemp->next!=NULL)
            {
                btemp=btemp->next;
            }//while
            btemp->next=newbnode;
        }//else
      
    } //while
    free(b1);    //free memory
    fclose(bookingptr);
    return bhead;
}//read bookings



/*writeBookings function to write data to file
this function takes bookings pointer as argument
and writes the data to the bookings.txt file*/
void writeBookings(bnode * bhead)
{
    bnode *b1 = bhead;

    FILE *bookingptr;

    bookingptr = fopen("bookings.txt", "w"); // opening file in write mode

    //write bookings until last node
    while (b1 != NULL)
    {
        fprintf(bookingptr,"%d,%d,%d,%d,%d,%d\n",b1->booking_id,b1->userid,b1->train_id,b1->no_of_passengers,b1->fare,b1->choiceclass);
        b1 = b1->next;
    } // while
    fclose(bookingptr);
} // writeToFile



/*this function will return unique booking id whenever called*/
int booking_id()
{
    FILE * bookingidptr;
    bookingidptr=fopen("id.txt","r");  
    int bookingid;
    fscanf(bookingidptr,"%d.",&bookingid);
    fclose(bookingidptr);


    bookingidptr=fopen("id.txt","w");  
    fprintf(bookingidptr,"%d.",++bookingid);
    fclose(bookingidptr);

    return bookingid;

}



/*this function will take trains LL, trainID and class
and return fare of that class of the specified train*/

int getfare(tnode *trains, int trainid, int class){
    tnode *thead=trains;

    while (thead != NULL)
    {
        if(thead->trainid==trainid && class==1){
          return thead->class1_fare;
        }
        else if (thead->trainid==trainid && class==2)
        {
          return thead->class2_fare;
        }
        thead = thead->next;
    }//while

}//getfare()



/*this function takes trains LL and userID as input and will
book ticket for that user */
void book_ticket(tnode *trains, int userid)
{
    tnode *thead = trains;
    char source[20], destination[20];
    int no_of_passengers, trainid, choiceclass,fare,bookingid;
    printf("\nEnter the source Place:: ");
    while (getchar() != '\n');
    scanf("%[^\n]", source);
    printf("\nEnter Destination:: ");
    while (getchar() != '\n');
    scanf("%[^\n]",destination);
    printf("\nEnter no of passenger: ");
    scanf("%d", &no_of_passengers);
    printf("\nChoose Class(1 or 2): ");
    scanf("%d", &choiceclass);

    // Available booking function called
    availableBookings(thead, source, destination, no_of_passengers,choiceclass);

    printf("\nEnter trainID of the train you would like to book: ");
    scanf("%d", &trainid);

    fare=getfare(thead,trainid,choiceclass)*no_of_passengers;
    bookingid= booking_id();
    add_passengers(bookingid,no_of_passengers);
    FILE *bookingptr;
    bookingptr=fopen("bookings.txt","a");    
    fprintf(bookingptr,"%d,%d,%d,%d,%d,%d\n",bookingid,userid,trainid,no_of_passengers,fare,choiceclass);
    fclose(bookingptr);
    
   update_available_seats(trainid,no_of_passengers,choiceclass,1);
}//book_ticket



/*this function will take trainID, class, number of passengers and type
and modify available seats based on the int variable type i.e.
if type==1 means ticket is booked so available seats will be decremented
and vice-versa for type==2*/
void update_available_seats(int trainid, int no_of_passengers,int choiceclass, int type){
	printf("\n");
    tnode *trains,*thead;
    int i = 0;

    trains = readTrains();//read trains from file and store in LL
    thead =trains;
    while (getchar() != '\n');
    while (i < totalTrains(thead))
    {
        if (type==1)//booking ticket
        {
            if (trainid == thead->trainid)
            {
                if(choiceclass==1){
                    thead->class1_available-=no_of_passengers;
                }//if
                else if(choiceclass==2){
                    thead->class2_available-=no_of_passengers;
                }//else
                break;
            } // if
        }//if
        else if (type==0)//cancelling ticket
        {
            if (trainid == thead->trainid)
            {
                if(choiceclass==1){
                    thead->class1_available+=no_of_passengers;
                }//if
                else if(choiceclass==2){
                    thead->class2_available+=no_of_passengers;
                }//else
                break;
            } // if
        }//else
        thead=thead->next;
    } // while

    writeTrains(trains);  //write updated LL fo trains.txt
	
}//update_available_seats


/*deleteBooking function will take userID aSA INPUT and display all bookings for that user and 
ask user to choose which booking to delete and will delete specified booking and add that booking to 
cancelled.txt file*/
void deleteBooking(int userid)
{
    bnode *temp,*bookings,*bhead,*prev;
    int i = 0, bookingid;
    bookings = readBookings();//read bookings from file and store in LL
    bhead=bookings;
    prev=bookings;

    tnode *trains, *thead;
    trains=readTrains();//read trains from file and store in LL
    thead=trains;
    
    printf("\n");
    display_booking(thead,0,userid);
    printf("\nEnter booking ID: ");
    scanf("%d", &bookingid);
    //first node
    if (bookings->booking_id==bookingid && bookings->next != NULL)
    {
        temp=bookings;
        bookings=bookings->next;
        addCancel(temp);
        writeBookings(bookings);
        return;
    }
    //single node only
    if (bookings->booking_id==bookingid && bookings->next == NULL)
    {
        addCancel(bookings);
        writeBookings(NULL);
        return;
    }
    //traverse to last
    while(bhead->next!=NULL){
        prev=bhead;
        bhead=bhead->next;
    }
    //last node
    if (bhead->booking_id==bookingid)
    {
        addCancel(bhead);
        prev->next=NULL;
        writeBookings(bookings);
        return;
    }
    bhead=bookings;
    while(bhead->next!=NULL){
        if (bhead->booking_id==bookingid)
        {
            prev->next=bhead->next;
            addCancel(bhead);
            writeBookings(bookings);
            return;
        }
        prev=bhead;
        bhead=bhead->next;
    }//traverse to last
    writeBookings(bookings);
}//deleteBooking


/*modifyBooking function will take userID aSA INPUT and display all bookings for that user and 
ask user to choose which booking to modify and will modify specified booking and 
update that details to file*/
void modifyBooking(int userid)
{
    printf("\n");

    bnode *bookings,*bhead;
    pnode* passengers,*phead;
    tnode* trains,*thead;
    int i = 0,j=0, bookingid;
    char pname[15];

    bookings = readBookings();//read bookings from file and store in LL
    bhead=bookings;
    passengers =readPassengers();//read passengers from file and store in LL
    phead=passengers;
    trains=readTrains();//read trains from file and store in LL
    thead=trains;    
    while (getchar() != '\n');
    
    while (i < totalBookings(bhead))
    {
        if (userid == bhead->userid)
        {
            display_booking(thead,bookingid,userid);
            printf("Enter booking ID: ");
            scanf("%d", &bookingid);
            displayPassengers(bookingid);
            printf("Enter Name of passenger to modify details: ");
            while (getchar() != '\n');
            scanf("%[^\n]", pname);
            while(j<bhead->no_of_passengers){
                if (strcmp(phead->passenger_name,pname)==0)
                {
                    printf("Enter name: ");
                    while (getchar() != '\n');
                    scanf("%[^\n]",phead->passenger_name);
                    printf("Enter age: ");
                    scanf("%d",&phead->age);
                    printf("Enter category: ");
                    while (getchar() != '\n');
                    scanf("%s",phead->category);
                    printf("Enter gender: ");
                    while (getchar() != '\n');
                    scanf("%s",phead->gen);
                    break;
                }//if
                phead=phead->next;
            }//while
            break;
        } // if
        bhead=bhead->next;
    } // while
    writePassengers(passengers);
} // modifyBooking()

/*this function will take booking node and write that node to cancelled.txt file*/
void addCancel(bnode* b1){
    FILE *cancelledptr;
    cancelledptr = fopen("cancelled.txt", "w"); // opening file in write mode
    fprintf(cancelledptr,"%d,%d,%d,%d,%d,%d\n",b1->booking_id,b1->userid,b1->train_id,b1->no_of_passengers,b1->fare,b1->choiceclass);
    update_available_seats(b1->train_id,b1->no_of_passengers,b1->choiceclass,0);
    fclose(cancelledptr);
    free(b1);
}//addCancel



/*display function to display cancelled booking details
it takes train LL, bookingID and userID as input and 
displays cancelled bookings for that user. */
void display_cancelled_booking(tnode* trains, int usrid){
  int userid=usrid;
  tnode* thead = trains;
  bnode *bookings,*bhead;
  bookings = readCancelledBookings();
  bhead=bookings;
  //bhead have username

  while (bhead != NULL && bhead->userid==userid)
      {
         
        printf("Booking ID: %d\n", bhead->booking_id);
        displaySingleTrain(trains, bhead->train_id);
        displayPassengers(bhead->booking_id);
        printf("Class: %d\n",bhead->choiceclass);
        printf("Total Seats: %d\n", bhead->no_of_passengers);
        printf("Total fare: %d\n", bhead->fare);


        bhead=bhead->next;
      }
}


/*readCancelledBookings function to read data to file
this function takes bookings pointer as argument
and read the data from the cancelled.txt file and store to LL 
and return pointer to that LL*/
bnode *readCancelledBookings()
{
    bnode *b1, *bhead = NULL, *newbnode = NULL, *btemp;
    
    b1 = (bnode*)malloc(sizeof(bnode));
    b1->next = NULL;

    FILE *bookingptr;
    bookingptr = fopen("cancelled.txt", "r");


    while (fscanf(bookingptr, "%d,%d,%d,%d,%d,%d\n",&b1->booking_id,&b1->userid,&b1->train_id,&b1->no_of_passengers,&b1->fare,&b1->choiceclass)!=-1)
    {
      newbnode = (bnode *)malloc(sizeof(bnode));
      newbnode->booking_id = b1->booking_id;
      newbnode->train_id = b1->train_id;
      newbnode->no_of_passengers = b1->no_of_passengers;
      newbnode->userid=b1->userid;
      newbnode->fare = b1->fare;
      newbnode->next = NULL;

      if (bhead==NULL)
        {
            bhead=newbnode;
        }
        else
        {
			btemp = bhead;
            while (btemp->next!=NULL)
            {
                btemp=btemp->next;
            }
            btemp->next=newbnode;
        }
      
    } // readFromFile
    free(b1);
    fclose(bookingptr);
    return bhead;
}

