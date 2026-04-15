/*
Name : Ahmed Mohamed Mokhtar
JUl,2025
*/


#include <stdio.h>
#include <string.h>
#include "STD_TYPES.h"
#include "PATIENT_interface.h"


static Patient_t Patients_List[MAX_PATIENTS_SLOTS];

void PATIENT_voidInit()  //Done
{
	// ADD CODE 
	// handle any error inputs
	for(u8 i=0;i<MAX_PATIENTS_SLOTS;i++)
		Patients_List[i].isUsed=NOT_USED;
}

u8 PATIENT_u8ViewPatientInfoByID(u8* id)
{
	// ADD CODE 
	// handle any error inputs
	s64 index;
    index=PATIENT_s64GetPatientIndexById(id);
	
    if(index<0||index>=MAX_PATIENTS_SLOTS||Patients_List[index].isUsed==NOT_USED)
		return WRONG_ID;
	printf("name   : %s\n",Patients_List[index].name);
	printf("age    : %d\n",Patients_List[index].age);
	printf("gender : %c\n",Patients_List[index].gender);
	
	return 0;
}


s64 PATIENT_s64GetPatientIndexById(u8* id)
{
	// ADD CODE 
	// handle any error inputs
	
	for(u8 i=0;i<MAX_PATIENTS_SLOTS;i++)
	{
		if(!strcmp(Patients_List[i].id,id))
			return i;
	}
	return -1;
}

u8* PATIENT_u8PGetPatientID(Patient_t* Patient)
{
	// ADD CODE 
	// handle any error inputs
	return Patient->id;
}

u8 PATIENT_u8AddPatientInfo(u8* id,u8* name,u32 age,u8 gender)
{
	// ADD CODE 
	// handle any error inputs
	
	for(u8 i=0;i<MAX_PATIENTS_SLOTS;i++)
	{
		if(Patients_List[i].isUsed!=USED)
		{
			strcpy(Patients_List[i].id,id);
			strcpy(Patients_List[i].name,name);
			Patients_List[i].age=age;
			Patients_List[i].gender=gender;
			Patients_List[i].isUsed=USED;
			
			return 0;
		}
	}
	

	return MAX_PATIENTS_REACHED;
}

u8 PATIENT_u8EditPatientInfo(u8* id,u8* name,u32 age,u8 gender)
{
	// ADD CODE 
	// handle any error inputs	
	for(u8 i=0;i<MAX_PATIENTS_SLOTS;i++)
	{
		if(!strcmp(id,Patients_List[i].id))
		{
			strcpy(Patients_List[i].name,name);
			Patients_List[i].age=age;
			Patients_List[i].gender=gender;

        
			return 0;
		}
	}

	return -1;
}


Patient_t* PATIENT_xPGetPatientFromID(u8* id)
{
	// ADD CODE 
	// handle any error inputs
	u8 index;
	u8 Found=0;
	for(u8 i=0;i<MAX_PATIENTS_SLOTS;i++)
	{
		if(!strcmp(Patients_List[i].id,id))
		{
			index=i;
			Found=1;
			break;
		}
	}
	if(Found==0)
		return 0;
		
	return (Patients_List+index);
}

u8 PATIENT_u8IsIDExist(u8* id)
{
	s64 index;
	index=PATIENT_s64GetPatientIndexById(id);
	if(index<0)
		return NOT_FOUND_ID;
	else 
		return FOUND_ID;
	
}

u8 PATIENT_u8InRangeAge(u32 age)
{
	if(age>200||age<0)
		return WRONG_AGE;
	else
		return RIGHT_AGE;;
}
u8 PATIENT_u8IsCorrectGender(u8 gender)
{
	if(gender!='m'&&gender!='M'&&gender!='F'&&gender!='f')
		return WRONG_GENDER;
	else
		return RIGHT_GENDER;
}