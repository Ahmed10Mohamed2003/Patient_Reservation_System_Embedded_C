/*
Name : Ahmed Mohamed Mokhtar
JUl,2025
*/


#ifndef PATIENT_H
#define PATIENT_H


#define PATIENTS_ID_ERROR 	(u8)0
#define PATIENTS_ADD_ERROR 		0
#define PATIENTS_EDIT_ERROR 	0
#define MAX_PATIENTS_SLOTS	 2
#define MAX_NAME_SIZE 		 50
#define MAX_ID_SIZE 		 50
#define WRONG_ID 1
#define MAX_PATIENTS_REACHED 2

#define NOT_USED 0
#define USED 1

#define FOUND_ID 1
#define NOT_FOUND_ID 0

#define WRONG_AGE 0
#define RIGHT_AGE 1

#define WRONG_GENDER 0
#define RIGHT_GENDER 1


typedef enum
{
	MALE,
	FEMALE
} Gender_t;

typedef struct {
    u8 id[MAX_ID_SIZE];
    u8 name[MAX_NAME_SIZE];
    u32 age;
    u8 gender;
	u8 isUsed;
} Patient_t;


void PATIENT_voidInit();
u8 PATIENT_u8ViewPatientInfoByID(u8* id);
u8 PATIENT_u8AddPatientInfo(u8* id,u8* name,u32 age,u8 gender);
u8 PATIENT_u8EditPatientInfo(u8* id,u8* name,u32 age,u8 gender);
s64 PATIENT_s64GetPatientIndexById(u8* id);
u8* PATIENT_u8PGetPatientID(Patient_t* Patient);
Patient_t* PATIENT_xPGetPatientFromID(u8* id);

u8 PATIENT_u8IsIDExist(u8* id);
u8 PATIENT_u8InRangeAge(u32 age);
u8 PATIENT_u8IsCorrectGender(u8 gender);


#endif