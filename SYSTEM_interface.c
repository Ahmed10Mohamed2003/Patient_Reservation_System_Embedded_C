/*
Name : Ahmed Mohamed Mokhtar
JUl,2025
*/


#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include "STD_TYPES.h"
#include "PATIENT_interface.h"
#include "RESERVATION_interface.h"
#include "SYSTEM_interface.h"


static System_t MyClinicSystem;
void ClearScreen()
{
  HANDLE                     hStdOut;
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  DWORD                      count;
  DWORD                      cellCount;
  COORD                      homeCoords = { 0, 0 };

  hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
  if (hStdOut == INVALID_HANDLE_VALUE) return;

  /* Get the number of cells in the current buffer */
  if (!GetConsoleScreenBufferInfo( hStdOut, &csbi )) return;
  cellCount = csbi.dwSize.X *csbi.dwSize.Y;

  /* Fill the entire buffer with spaces */
  if (!FillConsoleOutputCharacter(
    hStdOut,
    (TCHAR) ' ',
    cellCount,
    homeCoords,
    &count
    )) return;

  /* Fill the entire buffer with the current colors and attributes */
  if (!FillConsoleOutputAttribute(
    hStdOut,
    csbi.wAttributes,
    cellCount,
    homeCoords,
    &count
    )) return;

  /* Move the cursor home */
  SetConsoleCursorPosition( hStdOut, homeCoords );
}
void SYSTEM_voidInit()
{
	RESERVATION_voidInit();
	PATIENT_voidInit();
	
	strcpy(MyClinicSystem.password,"1234"); // copy the "1234" string to MyClinicSystem.password
	MyClinicSystem.SginType = User;
}
void SYSTEM_voidStartProgram()
{
	SYSTEM_voidInit();
	u32 choice;
	u8 Response;
    while (1) {
		ClearScreen();
        printf("\n=== Clinic Reservation System ===\n");
		printf("1. Sign in as Admin\n");
		printf("2. Sign in as User\n");
        printf("0. Exit\n");
        printf("Enter choice: ");
        if(scanf("%d", &choice) < 1) // to handle scanf errors hint: use it 
		{
			scanf("%*[^\n]"); 
			choice = INVALID_CHOICE;
		}
        switch (choice) {
			case 2:
            case 1:
           
				Response = SYSTEM_u8SginIn(choice);
				if(Response == INVALID_LOGIN)
				{
					ClearScreen();
					printf("\n===You have used all three trials.have a nice day===\n");
					return ;
				}
                break;
            case 0:
                printf("Exiting program.\n");
                return ;
            default:
                printf("Invalid choice. Try again.\n");
				Sleep(500);
        }
    }	
}
u8	SYSTEM_u8SginIn(SYSTEM_Sgin_t SginType)
{
	
	// sign in as Admin or user depending on the arg SginType
	u8 Response=INVALID_LOGIN;
	if(SginType==Admin)
		Response=SYSTEM_u8AdminIn();
	else if(SginType==User)
		Response=SYSTEM_u8UserIn();

    return Response;
}
u8 SYSTEM_u8AdminIn()
{
	u32 choice;
	u8 Response;

	Response=SYSTEM_u8CheckPassword();
	if(Response==INVALID_PASSWORD)
		return INVALID_LOGIN;
	
    while (1) {
    ClearScreen();
    printf("=== Clinic Reservation System ===\n");
    printf("1. Add patient record\n");
    printf("2. Edit patient record\n");
    printf("3. Book reservation\n");
    printf("4. Cancel reservation\n");
    printf("0. MainMenu\n");
    printf("Enter choice: ");

    if (scanf("%d", &choice) < 1) {
        while (getchar() != '\n'); // flush garbage
        choice = INVALID_CHOICE;
    } else {
        while (getchar() != '\n'); // clear trailing newline
    }

    switch (choice) {
        case 1: SYSTEM_u8AddPatientInfo(); break;
        case 2: SYSTEM_u8EditPatientInfo(); break;
        case 3: SYSTEM_u8AddReservation(); break;
        case 4: SYSTEM_u8CancelReservation(); break;
        case 0: return VALID_LOGIN;
        default:
            printf("Invalid choice.\n");
            Sleep(500);
    }
   //wait until user press any key to continue
    getch(); 
}
	return VALID_LOGIN;
}
u8 SYSTEM_u8CheckPassword()
{
	u8 inputPassword[MAX_SYSTEM_PASS_LEN];
	u8 Response;
	for(u8 Tests = 0;Tests<MAX_PASSWORD_TESTS;Tests++ )
	{
		ClearScreen();
        printf("\n=== Clinic Reservation System ===\n");
		printf("===          AdminMode        ===\n");
        printf("Enter Password: ");		
		scanf("%s",inputPassword);
		if(!strcmp(MyClinicSystem.password,inputPassword))
			return VALID_PASSWORD;
		else
			printf("\ninvalid password");
	}
	
	Response=INVALID_PASSWORD;
	return Response;
}
u8 SYSTEM_u8UserIn()
{
	u32 choice;
	u8 Response;
    while (1) {
		
		ClearScreen();
        printf("\n=== Clinic Reservation System ===\n");
		printf("===          UserMode         ===\n");
		printf("1. View patient record\n");
		printf("2. View today's reservations\n");
        printf("0. MainMenu\n");
        printf("Enter choice: ");
		if(scanf("%d", &choice) < 1) // to handle scanf errors hint: use it 
		{
			scanf("%*[^\n]"); 
			choice = INVALID_CHOICE;
		}
		switch(choice)
		{
			case 1:SYSTEM_u8DisplayPatientInfo();break;
			case 2:SYSTEM_voidDisplayReservationInfo();break;
			case 0:return VALID_LOGIN;
			default:
                printf("Invalid choice\n");
				Sleep(1000);
			
		}
		//wait untill user press any key
		//wait until user press any key to continue
        getch();
		
    }
	return VALID_LOGIN;
}
u8 SYSTEM_u8DisplayPatientInfo()
{
	u8 Found;
	u8 id[MAX_ID_SIZE];
	printf("Enter id : ");
	scanf("%s",&id);
	//check if ID exists
	Found=PATIENT_u8IsIDExist(id);
	//
	if(Found==NOT_FOUND_ID)
	{
		printf("Wrong ID !!\n");
		return ERROR_PATIENT_ID_NOT_EXIST;
	}
	 
	PATIENT_u8ViewPatientInfoByID(id);
	return VALID_PATIENT_ID;
}
void SYSTEM_voidDisplayReservationInfo()
{
	// Display the data in Reservations_List using printf hint: open RESERVATION_interface use RESERVATION_voidViewReservations	
	RESERVATION_voidViewReservations();
	return ;
}
u8		SYSTEM_u8AddPatientInfo()
{	
	
	u8 Response=VALID_PATIENT_ADD;
	u8 id[MAX_ID_SIZE];
	u8 name[MAX_NAME_SIZE];
    u32 age;
    u8 gender;
	printf("Enter id : ");
	scanf("%s",id);
	printf("Enter name : ");
	scanf("%s",name);
	printf("Enter age : ");
	scanf("%d",&age);
	if(PATIENT_u8InRangeAge(age)==WRONG_AGE)
	{
		printf("out of range age!!\n");
		return INVALID_PATIENT_AGE;
	}
	printf("Enter gender : ");
	scanf(" %c",&gender);
	if(PATIENT_u8IsCorrectGender(gender)==WRONG_GENDER)
	{
		printf("wrong gender !!\n");
		return INVALID_PATIENT_GENDER;
	}
	Response=PATIENT_u8AddPatientInfo(id,name,age,gender);
	if(Response==MAX_PATIENTS_REACHED)
	{
		printf("Error max patients Reached !!\n");
	}
	else
	{
		printf("Done Process\n");
	}
	return Response;
}
u8		SYSTEM_u8EditPatientInfo()
{
	u8 id[MAX_ID_SIZE];
	u8 name[MAX_NAME_SIZE];
    u32 age;
    u8 gender;
	u8 Found;
	printf("Enter id : ");
	scanf("%s",id);
	//check if ID exists
	Found=PATIENT_u8IsIDExist(id);
	   
	if(Found==NOT_FOUND_ID)
	{
		printf("Wrong ID !!\n");
		return ERROR_PATIENT_ID_NOT_EXIST;
	}
	
	printf("Enter name : ");
	scanf("%s",name);
	printf("Enter age : ");
	scanf("%d",&age);
	if(PATIENT_u8InRangeAge(age)==WRONG_AGE)
	{
		printf("out of range age!!\n");
		return INVALID_PATIENT_AGE;
	}
	printf("Enter gender : ");
	scanf(" %c",&gender);
	if(PATIENT_u8IsCorrectGender(gender)==WRONG_GENDER)
	{
		printf("wrong gender !!\n");
		return INVALID_PATIENT_GENDER;
	}
	PATIENT_u8EditPatientInfo(id,name,age,gender);
	printf("\nDone Process\n");
	return VALID_PATIENT_EDIT;
}
u8		SYSTEM_u8AddReservation()
{

	u8 id[MAX_ID_SIZE];
    u8 Found;
	
	RESERVATION_voidViewReservations();
	Patient_t* patient;
	printf("Enter id : ");
	scanf("%s",id);
	//check valid ID
	Found=PATIENT_u8IsIDExist(id);
	 
	if(Found==NOT_FOUND_ID)
	{
		printf("Wrong ID !!\n");
		return ERROR_PATIENT_ID_NOT_EXIST;
	}
	/*because RESERVATION_u8AddReservation() takes pointer to patient 
	we need to get Patient* by id*/
	patient=PATIENT_xPGetPatientFromID(id);
	   
	u8 slot;
	printf("Enter Time slot to book : ");
	scanf("%d",&slot);
	//check slot range
	if(slot<1||slot>5)
	{
		printf("Wrong slot !!\n");
		return INVALID_SLOT;
	}
    u8 Reservation;
	//data is ready to add reservation
	Reservation=RESERVATION_u8AddReservation(patient,slot);
    if(Reservation==RESERVATION_ADD_SLOT_ERROR)
       {
         printf("This Time slot already reserved !! \n");
         return ERROR_RESERVATION_BOOKED;
       }
	   
	   printf("\nDone Process\n");
	   
	return VALID_RESERVATION_ADD;

}
u8 SYSTEM_u8CancelReservation()
{
    u32 slot;
    
    // Display current reservations first
    RESERVATION_voidViewReservations();
    
    printf("\nEnter Time slot to cancel (1-5): ");
    scanf("%d", &slot);
    
    // Validate slot number
    if(slot < 1 || slot > 5)
    {
        printf("Invalid slot!\n");
        return INVALID_SLOT;
    }
    
    
    // Perform cancellation
    u8 result = RESERVATION_u8CancelReservation(slot);
    if(result == RESERVATION_UNRESERVED)
    {
        printf("Reservation for slot %d cancelled successfully.\n", slot);
        return VALID_RESERVATION_CANCEL;
    }
    else
    {
        printf("Failed to cancel reservation.\n");
        return RESERVATION_CANCEL_SLOT_ERROR;
    }
}


