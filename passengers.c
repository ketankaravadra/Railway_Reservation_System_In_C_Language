#include"trains_header.h"
#include"passengers.h"
#include"bookings.h"
#include"users.h"




/*display function to display passengers details
it takes bookingID as input and 
displays passengers for that bookingID*/
void displayPassengers(int bookingid){
  int i=1;
  pnode *passengers;
  passengers=readPassengers();//read passengers from file and store in LL
  pnode *phead =passengers;
    while (phead != NULL)
    {
		if (bookingid==phead->booking_id)
    	{

			printf("Passenger: %d. Name: %s, Age: %d, Gender : %s, Category: %s\n",i,phead->passenger_name,phead->age,phead->gen,phead->category);
            i++;
    	}//if 
        phead=phead->next;      
    }//while
}//displaypassengers()


/*readPassengers function will open passengers.txt file,
read and store passengers details in LL and return pointer to 
that LL i.e first node of LL*/
pnode* readPassengers(){
    pnode *p1, *phead = NULL, *newpnode = NULL, *ptemp;
    
    p1 = (pnode *)malloc(sizeof(pnode));
    p1->next = NULL;

    FILE *passengerptr;
    passengerptr = fopen("passengers.txt", "r");   //open file in read mode
    while(fscanf(passengerptr,"%d,%d,%[^,],%[^,],%[^,],%d\n",&p1->booking_id,&p1->no_of_passengers,p1->passenger_name,p1->category,p1->gen,&p1->age)!=-1)
    {
        newpnode=(pnode*)malloc(sizeof(pnode));
        newpnode->age=p1->age;
        newpnode->booking_id=p1->booking_id;
        newpnode->no_of_passengers=p1->no_of_passengers;
		strcpy(newpnode->category,p1->category);
		strcpy(newpnode->passenger_name,p1->passenger_name);
        strcpy(newpnode->gen,p1->gen);
        newpnode->next=NULL;

        //if ll is empty
        if (phead==NULL)
        {
            phead=newpnode;
        }//if
        else
        {
			ptemp = phead;
            while (ptemp->next!=NULL)
            {
                ptemp=ptemp->next;
            }//while
            ptemp->next=newpnode;
        }//else
    }//while

      free(p1);
      fclose(passengerptr);
      return phead;
}//readPassengers()


/*this function will take bookingID and number of seats as input
and adds thst many passengers to the passengers.txt file*/
void add_passengers(int bookingid, int no_of_seats)
{
    int i=1,age;
    char name[15],category[15];
    char gender[6];
    FILE *passengerptr;
    passengerptr=fopen("passengers.txt","a"); //open file in append mode
    
    while(i<=no_of_seats){
      printf("Enter name: ");
      while (getchar() != '\n');
      scanf("%[^\n]",name);
      printf("Enter age: ");
      scanf("%d",&age);
      printf("Enter category: ");
      while (getchar() != '\n');
      scanf("%s",category);
      printf("Enter gender: ");
      while (getchar() != '\n');
      scanf("%s",gender);
      fprintf(passengerptr,"%d,%d,%s,%s,%s,%d\n",bookingid,no_of_seats,name,category,gender,age);
	  i++;
    }//while
    fclose(passengerptr);
}//addpassengers()



/*writePassengers function to write data to file
this function takes passengers pointer as argument
and writes the data to the passengers.txt file*/
void writePassengers(pnode *passengers){
    pnode* p1=passengers;
    FILE *passengerptr;
    passengerptr = fopen("passengers.txt", "w"); // opening file in write mode

    while (p1 != NULL)
    {
        fprintf(passengerptr,"%d,%d,%s,%s,%s,%d\n",p1->booking_id,p1->no_of_passengers,p1->passenger_name,p1->category,p1->gen,p1->age);
        p1 = p1->next;
    } // while
      fclose(passengerptr);
}
