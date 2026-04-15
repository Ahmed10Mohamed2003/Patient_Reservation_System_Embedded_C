/*
Name : Ahmed Mohamed Mokhtar
JUl,2025
*/

#include <stdio.h>
#include <string.h>
#include "STD_TYPES.h"
#include "PATIENT_interface.h"
#include "RESERVATION_interface.h"

static u8 reservationTimeStr[MAX_RESERVATIONS_SLOTS][50];
static Reservation_t Reservations_List[MAX_RESERVATIONS_SLOTS];


void RESERVATION_voidInit()
{
		strcpy(reservationTimeStr[0],"2pm to 2:30pm");
		strcpy(reservationTimeStr[1],"2:30pm to 3pm");
		strcpy(reservationTimeStr[2],"3pm to 3:30pm");
		strcpy(reservationTimeStr[3],"4pm to 4:30pm");
		strcpy(reservationTimeStr[4],"4:30pm to 5pm");
		// ADD CODE 
		for(int i=0;i<MAX_RESERVATIONS_SLOTS;i++)
		{
			Reservations_List[i].Patient=NULL;
			Reservations_List[i].slotReserved=RESERVATION_UNRESERVED;
		}
		return;

}

void RESERVATION_voidViewReservations()
{

	for(u8 i=0;i<MAX_RESERVATIONS_SLOTS;i++)
	{
		if(Reservations_List[i].slotReserved==RESERVATION_UNRESERVED)
			printf("%s is not reserved\n",reservationTimeStr[i]);
		else
		{
			if (Reservations_List[i].Patient != NULL)
			printf("%s is reserved to patient with id %s\n",reservationTimeStr[i],(Reservations_List[i].Patient)->id);
		}
	}
		
	return;		
}


u8 RESERVATION_u8AddReservation(Patient_t* Patient,RESERVATIONS_SlotsTimes SlotTime )
{
	if(Reservations_List[SlotTime-1].Patient==NULL)
	{
		Reservations_List[SlotTime-1].Patient=Patient;
		Reservations_List[SlotTime-1].slotReserved=RESERVATION_RESERVED;
	}
	else
	{
		printf("Can't Reserve this time slot \n"); 
		return RESERVATION_ADD_SLOT_ERROR;
	}
	return RESERVATION_RESERVED;
}


u8 RESERVATION_u8CancelReservation(RESERVATIONS_SlotsTimes SlotTime)
{
	// Check if slot is actually reserved
    if(Reservations_List[SlotTime-1].slotReserved == RESERVATION_UNRESERVED)
    {
        printf("This time slot is not currently reserved.\n");
        return RESERVATION_CANCEL_SLOT_ERROR;
    }
	Reservations_List[SlotTime-1].Patient=0;
	Reservations_List[SlotTime-1].slotReserved=RESERVATION_UNRESERVED;
	return RESERVATION_UNRESERVED;	
}