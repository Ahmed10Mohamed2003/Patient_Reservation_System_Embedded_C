/*
Name : Ahmed Mohamed Mokhtar
JUl,2025
*/

#ifndef SYSTEM_H
#define SYSTEM_H

#define MAX_SYSTEM_PASS_LEN			100

#define 	INVALID_LOGIN 			0
#define		VALID_LOGIN				1


#define 	INVALID_PATIENT_GENDER  20
#define 	INVALID_PATIENT_AGE 	21
#define 	INVALID_PATIENT_NAME 	22

#define 	INVALID_PATIENT_ID		2
#define 	VALID_PATIENT_ID		3



#define 	MAX_PASSWORD_TESTS		3

#define 	INVALID_PASSWORD		4
#define 	VALID_PASSWORD			5

#define 	ERROR_RESERVATION_BOOKED		6
#define 	ERROR_RESERVATION_EMPTY			7
#define 	ERROR_RESERVATION_SLOT_NOT_EXIST		15


#define 	ERROR_PATIENT_ID_EXIST			9
#define 	ERROR_PATIENT_ID_NOT_EXIST			23
#define 	ERROR_MAX_PATIENT_CAPACITY			10

#define 	VALID_PATIENT_ADD			11
#define 	VALID_PATIENT_EDIT			12
#define 	VALID_RESERVATION_ADD		13
#define 	VALID_RESERVATION_CANCEL		14

#define 	INVALID_CHOICE				255
#define     INVALID_SLOT    50

typedef enum 
{
		Admin = 1,
		User = 2
}SYSTEM_Sgin_t;


typedef struct {
	SYSTEM_Sgin_t SginType;
	u8 password[MAX_SYSTEM_PASS_LEN];
	
} System_t;

void 	SYSTEM_voidInit();
void 	SYSTEM_voidStartProgram();
u8   	SYSTEM_u8SginIn(SYSTEM_Sgin_t SginType);
u8	 	SYSTEM_u8AdminIn();
u8	 	SYSTEM_u8UserIn();
//user funcs
u8	 	SYSTEM_u8DisplayPatientInfo();
void	SYSTEM_voidDisplayReservationInfo();
//
//Admin funcs
u8   	SYSTEM_u8InputPassword(u8* str_password);
u8   	SYSTEM_u8CheckPassword();
u8		SYSTEM_u8AddPatientInfo();
u8		SYSTEM_u8EditPatientInfo();
u8		SYSTEM_u8AddReservation();
u8		SYSTEM_u8CancelReservation();
//


#endif