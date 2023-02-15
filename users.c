#include"trains_header.h"
#include"passengers.h"
#include"bookings.h"
#include"users.h"






/*function to count total users in LL
it'll take pointer to first node of LL and count total nodes i.e. total users 
and return count i.e.int value*/
int totalUsers(unode *users)
{
    unode *uhead = users;
    int count = 1;
    

    while (uhead->next != NULL)
    {
        uhead = uhead->next;
        count++;
    }
    return count;
}



/*readUsers function will read details of users from users.txt file and store them in LL
and return the pointer to that Users LL*/
unode* readUsers()
{
    unode *u1=NULL,*uhead=NULL,*newunode=NULL,*utemp;
    
    u1= (unode*)malloc(sizeof(unode));
    u1->next =NULL;

    FILE *userptr;
    userptr = fopen("users.txt","r");  //open file in read mode

    while(fscanf(userptr,"%d,%ld,%[^,],%[^,],%[^,],%d.\n",&u1->userid,&u1->phone,u1->username,u1->address,u1->password,&u1->type)!=-1)
    {
        // creating new node for user detail read from file
        newunode=(unode*)malloc(sizeof(unode));
        newunode->type=u1->type;
        strcpy(newunode->username,u1->username);
        newunode->userid=u1->userid;
        newunode->phone=u1->phone;
        strcpy(newunode->address,u1->address);
        strcpy(newunode->password,u1->password);
        newunode->next=NULL;

        //adding newly read user node to the end of user LL
        //if ll is empty
        if (uhead==NULL)
        {
            uhead=newunode;
        }//if
        else
        {
            utemp = uhead;
            while (utemp->next!=NULL)
            {
                utemp=utemp->next;
            }//while
            utemp->next=newunode;
        }//else
    }//while
    free(u1);          //free up space
    fclose(userptr);   //close the opened file
    return uhead;

}//readUsers



/*registration function to register new user
it'll take */
void registration()
{
    bool phcheck,passcheck,present;
    unode* u1,*users,*uhead;
    int i=0,userid;
    users=readUsers();
    uhead = users;
    u1= (unode*)malloc(sizeof(unode));  //memory allocation
    FILE *userptr;
    fflush(stdin);
    printf("Enter userid(Unique): ");
    scanf("%d",&userid);
    //check if user with userID is already present
    while (i < totalUsers(users))
    {
        if (userid==uhead->userid)
        {      
            printf("Present Check.");     
            present=true;
            break;
        } // if
        else
        {
            uhead=uhead->next;
        } //else
        i++;
    } // while

    //if not already present, then userID is unique
    if (!present)
    {
        printf("\nEnter your name: "); // u1=user
        while (getchar() != '\n');
        scanf("%[^\n]", u1->username);       // It will take username
        printf("\nEnter your phone number: ");
        while(getchar()!='\n');
        scanf("%ld",& u1->phone); // It will take user's phone number
        phcheck = phonecheck(u1->phone);
        while(phcheck==0)
        {
            printf("\nInvalid phone, enter your phone number again: ");
            scanf("%ld",& u1->phone); // It will store phone number
            phcheck = phonecheck(u1->phone);
        }	//while
        printf("\nEnter Address: ");
        while (getchar() != '\n');
        scanf("%[^\n]", u1->address); // It will store user address
        printf("\nEnter your password: ");
        while (getchar() != '\n');
        scanf("%s", u1->password); // It will store the password
        passcheck = passwordcheck(u1->password);
        while(passcheck==0)
        {
            printf("\nInvalid password, enter your new password again: ");
            while (getchar() != '\n');
            scanf("%s", u1->password); // It will store the password
            passcheck = passwordcheck(u1->password);
        }	//while        
        userptr = fopen("users.txt", "a");
        fprintf(userptr,"%d,%ld,%s,%s,%s,%d.\n",userid,u1->phone,u1->username,u1->address,u1->password,2);
        fclose(userptr);    
    }//if

    //if userID not unique
    else
    {
        printf("Userid already exists.");
        registration();
    }// else
    
    
}//registration



/*phone check function to check validity of phone number
takes int (phone number) as input  and checks and returns true if 
phone number is of 10 digits else returns false*/
bool phonecheck(long int phone){
    int count=0;
    do {
        
    phone /= 10;
    ++count;
    } while (phone != 0);

    if (count == 10)
    {
        return true;
    }//if
    
  // if we couldn't invalidate the phone it must be valid
  return false;
}//phonecheck()



/*password check function to check validity of password
takes char pointer(password) as input  and checks and returns true if 
password is of 8 characters or more, contains at least 1 lowercase, atleast 1 uppercase
atleast 1 number and atleast 1 special character else returns false*/
bool passwordcheck(char *password){

	int i;
  int length = strlen(password);
  if (length < 8) return false;
  
  bool has_upper = false;
  bool has_lower = false;
  bool has_digit = false;
  bool has_symbol = false;
  

  for(i = 0; i < length; i++)
  {
    if (isupper(password[i])) has_upper = true;
    if (islower(password[i])) has_lower = true;
    if (isdigit(password[i])) has_digit = true;
    if (ispunct(password[i])) has_symbol = true;
  }//for
  

  if (!has_upper) return false;
  if (!has_lower) return false;
  if (!has_digit) return false;
  if (!has_symbol) return false;
  
  // if we couldn't invalidate the password it must be valid
  return true;

}//passwordcheck()



/*credential() function to check if user entered credentials are correct or not
it will take int (1 for admin credential check and 2 for user credential check) and 
return the userID if correct credentials are entered*/
int credential(int type)
{
    char password[16];
    int userid;

    printf("\nEnter Userid: ");
    scanf("%d", &userid);

    printf("Enter password: ");
    scanf("%s", password);

   unode *uhead, *users;
   users = readUsers(); //read users from file
   uhead=users;   
   while (uhead != NULL){
       if (type == 1)
       {
           if (uhead->type==1 && userid==uhead->userid && strcmp(password, uhead->password) == 0)
           {
               return 1;
           }//if
       }//if
       else if(type==2){
           
           if(uhead->type==2 && userid== uhead->userid && strcmp(password, uhead->password) == 0)
           {
               return uhead->userid;
           }//if
       }//else
       uhead = uhead->next;
   }//while
   free(users);
   printf("Invalid Credentials. Re-enter credentials: ");
   credential(type);
}//credential()

