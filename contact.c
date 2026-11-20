#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h" 

int validate_name(char name[]);
int validate_PhoneNo(AddressBook *addressBook, char phoneno[]);
int validate_Email(char email[]);
int unique_Email(AddressBook *addressBook, char emailid[]);
int Unique_no(AddressBook *addressBook, char phoneno[]);

int SEARCH(AddressBook *addressBook, char str[]);
int SEARCH_PHONE(AddressBook *addressBook, char str[]);
int SEARCH_EMAIL(AddressBook *addressBook, char str[]);

void listContacts(AddressBook *addressBook) 
{

    for(int i=0; i < addressBook->contactCount; i++)
    {
         printf("Name: %s\n",addressBook->contacts[i].name);
         printf("Phone: %s\n",addressBook->contacts[i].phone);
         printf("Email: %s\n",addressBook->contacts[i].email);
    
         printf("\n --------------------------------------------------\n");
    }
}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
   // populateAddressBook(addressBook);
    
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}


void createContact(AddressBook *addressBook)
{
	/* Define the logic to create a Contacts */
   
    int flag;
    int EmailValid;

    
        printf("Enter the  Name:");
	do
	{

		scanf(" %[^\n]",addressBook->contacts[addressBook->contactCount].name);
		flag = validate_name(addressBook->contacts[addressBook->contactCount].name);
		if(flag == 0)
		{
			printf("Invlaid name, please enter correct name :");
		}
	}while(flag == 0);
        
        printf("Enter the  phone no: ");
	do
	{
	
		scanf("%s", addressBook->contacts[addressBook->contactCount].phone);
		flag = validate_PhoneNo(addressBook, addressBook->contacts[addressBook->contactCount].phone);
		if(flag == 1)
		{
			printf("Invalid Number, Re-Enter the phone number : ");
		}
		if(flag == 2)
		{
			printf("Phone number should have 10 digits, please re enter number:");
		}
		if(flag == 3)
		{
			printf("Phone number should be Unique, Please Enter number again : ");
		}
	}while(flag != 0);

	
        printf("Enter the  Email: ");
	  do
        {
                flag = 0;
                scanf(" %[^\n]", addressBook->contacts[addressBook->contactCount].email);
                flag = validate_Email(addressBook->contacts[addressBook->contactCount].email);
                if(flag != 0)
                {
                        printf("Invalid Email, Re-Enter the Email : ");
			continue;
                }

		EmailValid = unique_Email(addressBook, addressBook->contacts[addressBook->contactCount].email);

		if(EmailValid  == 0)
		{
		       printf("Email already Exists, Re-Enter the Email : ");
		       continue;
		}


			break;
		
        }while(1);
  

        addressBook->contactCount++;
        
}

void searchContact(AddressBook *addressBook) 
{
    /* Define the logic for search */
     printf("1. Name\n");
     printf("2.Id\n");
     printf("3. Email Id\n");

     int flag ;
     int found ;
     int Validate ;

     int opt;
     printf("Enter the option\n");
     scanf("%d",&opt);
     char str[30];

     switch(opt)
     {
	     case 1: 
		     printf("ENter the Name you want to search :");
		     scanf(" %[^\n]",str);
		     flag = SEARCH(addressBook, str);

		               if(flag == 0)
		               {
			                 printf("Name not found\n");
		               }
		              else if( flag == 1)
			      {
				      printf("Name FOund sucessfully\n");
				      
		             }
		     break;

	     case 2:
		      printf("ENter the PHONE NUMBER you want to search :");
                     scanf(" %[^\n]",str);
		     Validate = SEARCH_PHONE(addressBook, str);
		     

                                  if(Validate == 0)
                                    {
			                      printf("Phone Number not found\n");
                                              
                                     }
				  else
				  {
					  printf("Phone number found\n");
			          }	  

		     break;
		     
             

	     case 3:
		      printf("ENter the Email Id you want to search :");
                     scanf(" %[^\n]",str);
		     
                       found = SEARCH_EMAIL(addressBook, str);

                          if( found == 0)
                          {
			      printf("Email id not found \n");
                           }
			  else
			  {
				  printf("Email found\n");
			  }
			  break;

		    default:
			  printf("Please ENter Valid option\n");
     }


}

void editContact(AddressBook *addressBook)
{
	/* Define the logic for Editcontact */
        printf("1. Name\n");
	printf("2.Phone No\n");
	printf("3.Email \n");

	char str[50];
	int flag;
	int opt;
	int editopt;
	int uniqueno;
	int uniqueemail;
	int validphone;
	int validemail;
	printf("Enter the Option");
	scanf("%d",&opt);

	switch(opt)
	{
		case 1:
			printf("Enter the Name\n");
			scanf(" %[^\n]",str);


			int index = -1; 
			for(int i = 0; i < addressBook->contactCount; i++) 
			{
			       	if(strcmp(addressBook->contacts[i].name, str) == 0)
			       	{
				       	index = i;
				       	break; 
				}
		       	}
		       	if(index == -1) 
			{
			       	printf("Contact not found\n");
			       	break; 
			}
		       	printf("Contact is Found\n");
                    
			printf("Choose the Option you want to edit :");
		        printf("1.Name\n");
			printf("2.Phone\n");
			printf("3.Email\n");
			
			scanf("%d",&editopt);

				switch (editopt)
				{
					case 1:
						printf("Please Enter the name you want to edit : ");
						scanf(" %[^\n]",str);
                                                flag = validate_name(str);
						if(flag == 1)
						{
							strcpy(addressBook->contacts[index].name, str);
							printf("Name is edited succesfully!!!!");
						}
						else
						{
							printf("Invalid Name\n");
						}
						break;
						/*
						else
						{
							printf("Multiple contacts are with same, Can you enter the Mobile number to confirm :");
							printf("Enter the Mobile Number : ");
							scanf(" %s",str);

							validphone = validate_PhoneNo(addressBook, str);
							if(validphone == 1 && validphone == 2)
							{
							 	printf("It is Valid mobile Number");
								
								name[i] = str;
								printf("Name is Edited and added sucessfuly in the list ");
							}
						}
						*/
						case 2:
						 
							       	printf("Enter the new Phone Number: ");
							       	scanf("%s", str);
							       	validphone = validate_PhoneNo(addressBook, str);
							       	if(validphone == 1)
							       	{
									printf("Invalid Number\n");
									break;
								}
								if (validphone == 2)
								{
									printf("Phone Number should Have 10 Digits\n");
									break;
								}

								 uniqueno = Unique_no(addressBook, str);

                                                                 if(uniqueno == 0)
                                                                 { 
                                                                      printf("Phone number already exists\n");
                                                                 }
                                                                 else
                                                                 {
                                                                          strcpy(addressBook->contacts[index].phone, str);
                                                                          printf("Phone number edited successfully\n");
                                                                 }
								 
							       	break;
						     case 3:
							       printf("Please Enter the new Email: ");
						              scanf(" %[^\n]", str);
					               	      validemail = validate_Email(str); 
						             if(validemail != 0)
						             {
								     printf("Invalid Email\n");
								     break;
							     }
							         uniqueemail = unique_Email(addressBook, str);
							           if(uniqueemail == 0)
							          {
									  printf("Email already Registerd\n");
									  break;
								  }
								   else
								   {
								        strcpy(addressBook->contacts[index].email, str);
								          printf("Email edited successfully\n");
							           }
								   break;
				}
		case 2:
	           {

                              printf("Enter the Phone Number: ");
                              scanf("%s", str);

                                 index = -1; 

                              for(int i = 0; i < addressBook->contactCount; i++)
                              {
                                      if(strcmp(addressBook->contacts[i].phone, str) == 0)
                                       {
                                           index = i;
                                           break;
                                       }
                              }

                            if(index == -1)
                            {
                                    printf("Phone number not found\n");
				    break;
                                     
                            }
			    printf("Contact is found\n");


                               printf("Enter the new Phone Number: ");
                              scanf("%s", str);

                              validphone = validate_PhoneNo(addressBook, str);

                             if(validphone == 1)
                             {
				     printf("Invalid phpne number\n");
				     break;
			     }
			     if(validphone == 2)
			     {
				     printf("Phone number should be 10 digits\n");
				     break;
			     }

			    uniqueno = Unique_no(addressBook, str);
                  
                            if(uniqueno == 0)
                            {
                                    printf("Phone number already exists\n");
                            }
                           else
                           {
                                  strcpy(addressBook->contacts[index].phone, str);
                                  printf("Phone number edited successfully\n");
                           }
			    

                            break;
		   }
	

		     case 3:
		       {

			     printf("Enter the Email: ");
                              scanf(" %[^\n]", str);

                                 index = -1;

                              for(int i = 0; i < addressBook->contactCount; i++)
                              {
                                      if(strcmp(addressBook->contacts[i].email, str) == 0)
                                       {
                                           index = i;
                                           break;
                                       }
                              }

                            if(index == -1)
                            {
                                    printf("EMail not found\n");
                                     break;
                            }

                               printf("Enter the new Email: ");
                              scanf(" %[^\n]", str);

                              validemail = validate_Email( str);

                             if(validemail != 0)
                             {
				     printf("Invalid Email\n");
				     break;
			     }
                                uniqueemail = unique_Email(addressBook, str);

                                 if(uniqueemail == 0)
				 {
					 printf("Email already Exists\n");
					 break;
				 }
				 else
                                 {
					 strcpy(addressBook->contacts[index].email, str);
                                          printf("Email edited successfully\n");
                                 }
                                break; 
		       }
		     default:
			   printf("Please Enter valid choice\n");
	}
}
                                                
		

								

void deleteContact(AddressBook *addressBook)
{
	printf("Please Enter the Option you want to delete");
	printf("1. Name\n");
	printf("2. Phone No\n");
	printf("3. Email\n");

	char str[30];
	int flag;
	char choice;
	int index;
	int opt;
	printf("Ente your Choice:");
	scanf("%d",&opt);

	switch(opt)
	{
		case 1:
			{
	
			   printf("Enter the Name you want to delete : ");
		           scanf(" %[^\n]",str);
		       	   index = -1;

			   for(int i=0; i<addressBook->contactCount; i++)
			   {
				if(strcmp(addressBook->contacts[i].name, str) == 0)
				{
					index = i;
					break;
				}
			   }
			   if(index == -1)
		           {
					printf("Contact Not Found\n");
					break;
			   }
			
			   printf("Do you want to delete, Please confirm(Y/y) :" );
			   scanf(" %c",&choice);
		    	   if(choice =='Y' || choice == 'y')
			   {
                               	for(int i=index ; i<addressBook->contactCount-1; i++)
				{
					addressBook->contacts[i] = addressBook->contacts[i+1];
					
			        }
				  addressBook->contactCount--;
				printf("Deleted Successfully\n");

			   }
			   else
			   {
				printf("Deletion Cancelled\n");
			   }
			   break;
			}
	
		case 2:
		    {
			  printf("Enter the Phone Number you want to delete : ");
                        scanf(" %s",str);
                         index = -1;

                        for(int i=0; i<addressBook->contactCount; i++)
                        {
                                if(strcmp(addressBook->contacts[i].phone, str) == 0)
                                {
                                        index = i;
                                        break;
                                }
                        }
                        if(index == -1)
                        {
                                        printf("Phone number Not Found\n");
                                        break;
                        }

                        printf("Do you want to delete, Please confirm(Y/y) :" );
                        scanf(" %c",&choice);
                        if(choice =='Y' || choice == 'y')
                        {
                                for(int i=index ; i<addressBook->contactCount-1; i++)
                                {
                                        addressBook->contacts[i] = addressBook->contacts[i+1];

                                }
                                  addressBook->contactCount--;
                                printf("Deleted Successfully\n");

                        }
			else
			{
				printf("Deletion Cancelled\n");
			}
			break;
		    }
		case 3:
		    {
			  printf("Enter the Email you want to delete : ");
                        scanf(" %[^\n]",str);
                         index = -1;

                        for(int i=0; i<addressBook->contactCount; i++)
                        {
                                if(strcmp(addressBook->contacts[i].email, str) == 0)
                                {
                                        index = i;
                                        break;
                                }
                        }
                        if(index == -1)
                        {
                                        printf("Email Not Found\n");
                                        break;
                        }

                        printf("Do you want to delete, Please confirm(Y/y) :" );
                        scanf(" %c",&choice);
                        if(choice =='Y' || choice == 'y')
                        {
                                for(int i=index ; i<addressBook->contactCount-1; i++)
                                {
                                        addressBook->contacts[i] = addressBook->contacts[i+1];

                                }
                                  addressBook->contactCount--;
                                printf("Deleted Successfully\n");
			}
			else
			{
				printf("delteion Cancelled\n");

                        }
			break;
		    }
		default:
			printf("Please Enter Valid Choice\n");
	}
}


int  validate_name(char name[])
{
	for(int i=0; name[i] != '\0'; i++)
	{

	   if(!((name[i] >= 'a' && name[i] <= 'z'
           ||name[i] >= 'A' && name[i] <= 'Z'
	   ||name[i] == ' ')))
		 
	   {
		return 0;
           }
	   
       }	    
       return 1;
}
int validate_PhoneNo(AddressBook *addressBook, char phoneno[])
{
	int length = strlen(phoneno);
	

	if(length != 10)
	{
		return 2;
	}
	//CHECK IF PHONENO HAS 10 DIGITS OR NOT
	for(int i=0; i< length; i++)
	{
		if(phoneno[i] < '0' || phoneno[i] > '9')
		{
			return 1;
		}
	
       }
	return 0;
}

int validate_Email(char email[])
{
	int length = strlen(email);
	int count = 0;
	int at = -1;
	int dot =-1;
        for(int i=0; email[i] != '\0'; i++)
        {
                if(email[i] == '@') 
                {
                        at = i;
                }
		if(email[i] == '.')
		{
			dot = i;
		}
        }

	if(at ==- 1 || dot == -1)
	{
		return 1;
	}
        // TO CHECK WHETHER CHARCATER EXISTS BETWEEN @ AND .
	if( dot - at <= 1)
	{
		return 2;
	}

        
	if(dot == length -1)
	{
		return 4;
	}

	for(int i=0; email[i] != '\0'; i++)
	{
		if(email[i] == '@')
		{
			count++;
		}
	}
	if(count > 1)
	{
		return 5;
	}

	return 0;


}

int Unique_no(AddressBook *addressBook, char phoneno[])
{
	for(int i=0; i<addressBook->contactCount; i++)
	{
		if(strcmp(addressBook->contacts[i].phone, phoneno) == 0)
		{
			return 0;
		}
	}
	return 3;
}

int unique_Email(AddressBook *addressBook,char emailid[])
{
	for(int i=0; i<addressBook->contactCount; i++)
	{
		if(strcmp(addressBook->contacts[i].email,emailid) == 0)
		{
			return 0;
		}
	}
	return 3;
}

int SEARCH(AddressBook *addressBook,  char str[])
{
	int count = 0;
	int arr[10];
	for(int i =0;i<addressBook->contactCount; i++)
	{
		if(strcmp(addressBook->contacts[i].name, str) == 0)
		{
			arr[count] = i;
			count++;
		}
	}
	if (count == 0)
	{
		printf("Contact not Found\n");
		return 0;
	}
	else if(count == 1)
	{
		printf("contact found successfully\n");
		printf("%s %s %s",addressBook->contacts[arr[0]].name , addressBook->contacts[arr[0]].phone,  addressBook->contacts[arr[0]].email);
		return 1;
	}
	else
	{
		printf("Multiple Contacts found\n " );
		for(int i=0; i < count; i++)
		{
			printf("%d",count);
                        printf("%s\n %s\n %s\n",addressBook->contacts[arr[i]].name , addressBook->contacts[arr[i]].phone,  addressBook->contacts[arr[i]].email);
		}
		return 2;
	}

}
int SEARCH_PHONE(AddressBook *addressBook, char  str[])
{
        int count = 0;
        int arr[10];
        for(int i =0;i<addressBook->contactCount; i++)
        {
                if(strcmp(addressBook->contacts[i].phone, str) == 0)
                {
                        arr[count] = i;
                        count++;
                }
        }
        if (count == 0)
        {
                printf("Contact not Found\n");
        }
        else if(count == 1)
        {
                printf("phone number found successfully\n");
                printf("%s %s %s",addressBook->contacts[arr[0]].name , addressBook->contacts[arr[0]].phone,  addressBook->contacts[arr[0]].email);
                return 1;
        }
        else
        {
                printf("Multiple Contacts found\n " );
                for(int i=0; i < count; i++)
                {
                        printf("%d",count);
                        printf("%s\n %s\n %s\n",addressBook->contacts[arr[i]].name , addressBook->contacts[arr[i]].phone,  addressBook->contacts[arr[i]].email);
                }
                return 1;
        }


}
int SEARCH_EMAIL(AddressBook *addressBook,  char str[])
{
        int count = 0;
        int arr[10];
        for(int i =0;i<addressBook->contactCount; i++)
        {
                if(strcmp(addressBook->contacts[i].email, str) == 0)
                {
                        arr[count] = i;
                        count++;
                }
        }
        if (count == 0)
        {
                printf("Contact not Found\n");
        }
        else if(count == 1)
        {
                printf("Email found successfully\n");
                printf("%s %s %s",addressBook->contacts[arr[0]].name , addressBook->contacts[arr[0]].phone,  addressBook->contacts[arr[0]].email);
                return 1;
        }
        else
        {
                printf("Multiple Emails found\n " );
                for(int i=0; i < count; i++)
                {
                        printf("%d",count);
                        printf("%s\n %s\n %s\n",addressBook->contacts[arr[i]].name , addressBook->contacts[arr[i]].phone,  addressBook->contacts[arr[i]].email);             
	        }
                return 1;
        }

}
