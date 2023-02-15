#include"trains_header.h"







/*start function to start the program
It will show 2 options for user
and ask if user is admin or regular
user and proceed further based on the choice of user*/

void start()
{
    int ch;

    printf("\n----------MENU----------\n1) Admin\n2) User\nENTER YOUR CHOICE: ");
    scanf("%d", &ch);

    switch (ch)
    {
    case ADMIN:      // Admin
        admin(); // admin function
        break;

    case USERMODE: // user mode
        usermode();
        break;

    } // switch
}



/*function for admin to perform operations like
add train, modify train, display train etc.*/

void admin()
{

    int ch;
    
    credential(1);
    

    do
    {
        printf("\n----------MENU---------\n1) Add details of train\n2) Delete train\n3) Display Train\n4) Modify Train details\n9) Logout.\n0) EXIT.\n\nENTER YOUR CHOICE: ");
        scanf("%d", &ch);

        switch (ch)
        {
        case 1:          // addd train
            add_train(); // add_train() function called to accept train details.
            break;

        case 2:             // delete train
            remove_train(); // remove_train() function called to delete train details.
            break;

        case 3: // display train

            display_train(); // display function called to display train details
            break;

        case 4:             // modify train
            modify_train(); // modify_train() function called to modify train details.
            break;

        case LOGOUT: // logout

            admin(); // logout and return back to admin login page
            break;
        case EXIT: // exit
            exit(0);

        }              // switch
    } while (ch != 0); // do_whileuserid


} // admin


/*function for user for options like register, login,
book tocket, view trains, view previous booking etc. */

void usermode()
{

    tnode* thead;
    int ch,choiceclass,no_of_passengers,bookingid,userid;
    char username[10], password[16], source[20],destination[20];
    printf("\n----------MENU----------\n1) Register\n2) Login:\n0) EXIT.\nENTER YOUR CHOICE: ");
    scanf("%d", &ch);

    switch (ch)
    {
    case REGISTRATION: // register
            registration();

    case LOGIN: // login
        userid = credential(2);
        thead=readTrains();//read trains from file and store in LL
        do
        {
            printf("\n----------MENU----------\n1) View trains\n2) View booking available\n3) View previous bookings\n4) Book Tickets\n5) Delete booking\n6) Modify booking\n9) Logout\n0) EXIT.\nENTER YOUR CHOICE: ");
            scanf("%d", &ch);

            switch (ch)
            {
            case 1: //view trains
                    printf("\nEnter the source Place:: ");
                    while (getchar() != '\n');
                    scanf("%[^\n]", source);
                    printf("\nEnter Destination:: ");
                    while (getchar() != '\n');
                    scanf("%[^\n]",destination);
                    printf("\nAVAILABLE TRAINS: \n");
                    view_trains(thead,source,destination);
                    break;
            case 2: // View available bookings
                    printf("\nEnter the source Place:: ");
                    while (getchar() != '\n');
                    scanf("%[^\n]", source);
                    printf("\nEnter Destination:: ");
                    while (getchar() != '\n');
                    scanf("%[^\n]",destination);
                    printf("\nAVAILABLE TRAINS: ");
                    view_trains(thead,source,destination);       
                    printf("\nEnter no of passenger: ");
                    scanf("%d", &no_of_passengers);
                    printf("\nChoose Class(1 or 2): ");
                    scanf("%d", &choiceclass);
                    availableBookings(thead,source,destination,no_of_passengers,choiceclass);
                    break;
            case 3: //View Previous bookings
                    printf("\nYour previous bookings: ");
                    scanf("%d", &bookingid);
                    display_booking(thead,0,userid);
                    break;
            case 4: //book tickets
                    book_ticket(thead,userid);
                    break;
            case 5: //delete booking
                    deleteBooking(userid);
                    break;
            case 6: //modify booking
                    modifyBooking(userid);
                    break;
            case LOGOUT: // logout
                    usermode();
                    break;
            case EXIT: // exit
                    exit(0);            
            default:
                break;
            }//switch

        } while (ch != 0); // do_while

    } // switch for login or register

} // user


/*add_train() function to add details of train
it opens file, asks admin for details of train
and appends the details in the file */

void add_train()
{
    printf("\n");
    tnode *trains,*thead;
    int i = 0,present=0,trainid;

    trains = readTrains();//read trains from file and store in LL
    thead =trains;
    while (getchar() != '\n');
    printf("Enter train ID: ");
    scanf("%d", &trainid);
    
    //check if train with this trainID already exist
    while (i < totalTrains(thead))
    {
        if (trainid == thead->trainid)
        {      
            printf("Present Check.");     
            present=1;
            break;
        } // if
        else
        {
            thead=thead->next;
        } //else
        i++;
    } // while

    if(!present)
    {
        tnode *t;
        t= (tnode*)malloc(sizeof(tnode));
        t->next =NULL;

        t->trainid=trainid;
        printf("Enter train name: ");
        while (getchar() != '\n');
        scanf("%[^\n]", t->train_name);
        printf("Enter total class1 seats: ");
        scanf("%d", &t->class1_seats);
		t->class1_available=t->class1_seats;
        printf("Enter class 1 fare: ");
        scanf("%d", &t->class1_fare);
        printf("Enter total class2 seats: ");
        scanf("%d", &t->class2_seats);
        t->class2_available=t->class2_seats;
        printf("Enter class 2 fare: ");
        scanf("%d", &t->class2_fare);
        printf("Enter source: ");
        while (getchar() != '\n');
        scanf("%[^\n]", t->source);
        printf("Enter destination: ");
        while (getchar() != '\n');
        scanf("%[^\n]", t->destination);
        printf("Enter departure time(in hhmm format only): ");
        scanf("%d", &t->departure_time);
        printf("Enter arrival time(in hhmm format only): ");
        scanf("%d", &t->arrival_time);


        FILE *trainptr;
        trainptr = fopen("trains.txt", "a");
        fprintf(trainptr, "%d,%s,%d,%d,%d,%d,%d,%d,%s,%s,%d,%d\n", t->trainid, t->train_name, t->class1_seats, t->class1_available,t->class1_fare, t->class2_seats,t->class2_available, t->class2_fare, t->source, t->destination, t->arrival_time, t->departure_time); // reading train details
        fclose(trainptr);
    }//if not present
    else
    {
        printf("Train already exists.");
    }// else
} // add_train


/*readTrains function to read data from file
this function takes train pointer as argument
and reads the data from the trains.txt file
and stores in the linkedlist*/

tnode* readTrains(){

    tnode *t,*thead=NULL,*newtnode=NULL,*temp;
    t= (tnode*)malloc(sizeof(tnode));
    t->next =NULL;

    FILE *trainptr;
    trainptr = fopen("trains.txt","r");


    while(fscanf(trainptr,"%d,%[^,],%d,%d,%d,%d,%d,%d,%[^,],%[^,],%d,%d\n",&t->trainid,t->train_name,&t->class1_seats,&t->class1_available,&t->class1_fare,&t->class2_seats,&t->class2_available,&t->class2_fare,t->source,t->destination,&t->arrival_time,&t->departure_time)!=-1)
    {
        newtnode=(tnode*)malloc(sizeof(tnode));
        newtnode->trainid=t->trainid;
        strcpy(newtnode->train_name,t->train_name);
        newtnode->class1_seats=t->class1_seats;
		newtnode->class1_available=t->class1_available;
        newtnode->class1_fare=t->class1_fare;
        newtnode->class2_seats=t->class2_seats;
		newtnode->class2_available=t->class2_available;
        newtnode->class2_fare=t->class2_fare;
        strcpy(newtnode->source,t->source);
        strcpy(newtnode->destination,t->destination);
        newtnode->departure_time=t->departure_time;
        newtnode->arrival_time=t->arrival_time;
        newtnode->next=NULL;

        //if ll is empty
        if (thead==NULL)
        {
            thead=newtnode;
        }//if
        else
        {
            temp = thead;
            while (temp->next!=NULL)
            {
                temp=temp->next;
            }//while
            temp->next=newtnode;
        }//else
    }//while
    free(t);
    fclose(trainptr);
    return thead;

}//readTrains




/*writeTrains function to write data to file
this function takes train pointer as argument
and writes the data to the trains.txt file*/

void writeTrains(tnode *thead)
{
    tnode *temp = thead;
    FILE *trainptr;
    trainptr = fopen("trains.txt", "w");// opening file in write mode


    while (temp != NULL)
    {
        fprintf(trainptr, "%d,%s,%d,%d,%d,%d,%d,%d,%s,%s,%d,%d\n", temp->trainid, temp->train_name, temp->class1_seats,temp->class1_available, temp->class1_fare, temp->class2_seats,temp->class2_available,temp->class2_fare, temp->source, temp->destination, temp->departure_time, temp->arrival_time); // reading train details
        temp = temp->next;
    } // while

    fclose(trainptr);

} // writeTrains


/*modify function to modify details of train
it takes address of file and trainID as input and
takes details of that trains from user and modifies it*/

void modify_train()
{
    printf("\n");
    tnode *trains,*thead;
    int i = 0, trainid;

    trains = readTrains();//read trains from file and store in LL
    thead =trains;
    while (getchar() != '\n');
    printf("Enter train ID: ");
    scanf("%d", &trainid);
    while (i < totalTrains(thead))
    {
        if (trainid == thead->trainid)
        {
            printf("Enter train name: ");
            while (getchar() != '\n');
            scanf("%[^\n]", thead->train_name);
            printf("Enter total class1 seats: ");
            scanf("%d", &thead->class1_seats);
            thead->class1_available=thead->class1_fare;
            printf("Enter class 1 fare: ");
            scanf("%d", &thead->class1_fare);
            printf("Enter total class2 seats: ");
            scanf("%d", &thead->class2_seats);
            thead->class2_available=thead->class2_fare;
            printf("Enter class 2 fare: ");
            scanf("%d", &thead->class2_fare);
            printf("Enter source: ");
            while (getchar() != '\n');
            scanf("%[^\n]", thead->source);
            printf("Enter destination: ");
            while (getchar() != '\n');
            scanf("%[^\n]", thead->destination);
            printf("Enter arrival time(in hhmm format only): ");
            scanf("%d", &thead->arrival_time);
            printf("Enter departure time(in hhmm format only): ");
            scanf("%d", &thead->departure_time);
            break;
        } // if
        thead=thead->next;
    
    } // while

    writeTrains(trains);

} // modify_train()


/*remove function to modify details of train
it takes address of file and trainID as input and
takes details of that trains from user and modifies it*/

void remove_train()
{
    tnode *temp,*trains,*thead,*prev;
    int i = 0, trainid;
    trains = readTrains();//read trains from file and store in LL
    thead=trains;
    printf("\n");

    printf("Enter train ID: ");
    scanf("%d", &trainid);
    if (trains->trainid==trainid && trains->next != NULL)
    {
        temp=trains;
        trains=trains->next;
        free(temp);
        writeTrains(trains);
        return;
    }//first node
    if (trains->trainid==trainid && trains->next == NULL)
    {
        free(trains);
        writeTrains(NULL);
        return;
    }//single node only

    while(thead->next!=NULL){
        prev=thead;
        thead=thead->next;
    }//traverse to last
    if (thead->trainid==trainid)
    {
        free(thead);
        prev->next=NULL;
        writeTrains(trains);
        return;
    }//last node
    
    thead=trains;
    while(thead->next!=NULL){
        if (thead->trainid==trainid)
        {
            prev->next=thead->next;
            free(thead);
            writeTrains(trains);
            return;
        }//last node

        prev=thead;
        thead=thead->next;
    }//traverse to last
    writeTrains(trains);  //write train linkedlist to file
}//remove_train()




/*display function to display details of train
it takes address of structure and number of trains as input and
displays details of trains*/

void display_train()
{
    tnode *trains;
    trains = readTrains();//read trains from file and store in LL

    tnode* thead =trains;
    while (thead != NULL)
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
        thead = thead->next;
        printf("\n");
    }
    
}



/*function takes train pointer as input and
counts and returns number of trains */

int totalTrains(tnode *trains)
{
    tnode *thead = trains;
    int count = 1;
    if (trains==NULL)
        {
            return 0;
        }
        
    while (thead->next != NULL)
    {
        thead = thead->next;
        count++;
    }

    return count;
}


