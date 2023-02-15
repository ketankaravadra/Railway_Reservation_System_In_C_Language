
#include"trains.h"



//user linkedlist to store user details
typedef struct userList
{
    int type;          //user type, 1 for admin and 2 for user
    long int phone;    // Stores the phone number
    char username[20]; // Stores username
    int userid;        //unique user id of user
    char password[20]; // Stores the password
    char address[50];  // Stores the address
    struct userList *next;  //pointer to next node
}unode;





//function to read users from txt file
unode* readUsers();
//registration function to register new user
void registration();
//password validation function
bool passwordcheck(char *);
//phone validation function
bool phonecheck(long int);
// credential function to check credentials
int credential(int);
//calculate total users in file
int totalUsers(unode*);

