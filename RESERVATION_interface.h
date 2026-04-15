/*
Name : Ahmed Mohamed Mokhtar
JUl,2025
*/


#ifndef RESERVATION_H
#define RESERVATION_H

#define MAX_RESERVATIONS_SLOTS 5


#define RESERVATION_RESERVED   1
#define RESERVATION_UNRESERVED 0

#define RESERVATION_ADD_SLOT_ERROR 2
#define RESERVATION_CANCEL_SLOT_ERROR 3

typedef enum 
{
		TWO_PM = 1, 			//2pm to 2:30pm
		TWO_HALF_PM,		//2:30pm to 3pm
		THREE_PM, 			//3pm to 3:30pm
		FOUR_PM,			//4pm to 4:30pm
		FOUR_HALF_PM,       //4:30pm to 5pm
		
}RESERVATIONS_SlotsTimes;

typedef struct {
	Patient_t* Patient;
	u8 slotReserved;
} Reservation_t;



void RESERVATION_voidInit();//
u8 RESERVATION_u8CancelReservation(RESERVATIONS_SlotsTimes SlotTime);
u8 RESERVATION_u8AddReservation(Patient_t* Patient,RESERVATIONS_SlotsTimes SlotTime );
void RESERVATION_voidViewReservations();


#endif