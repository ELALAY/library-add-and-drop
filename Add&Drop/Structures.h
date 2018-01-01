#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define size_arr_student 10

//------------------------------------------------------------------------------
//---------------------------------Structures-----------------------------------
//------------------------------------------------------------------------------

typedef struct{
	char WpInstruct[50], WpName[50], time_slot[2][20], Students_IDs[11][6];
	int capacity, enrolled_student;
}workshop_t;

typedef struct{
	int CreditHours, nbr_classes, nbr_repeated;
	char phone[11], repeated_class[10][20], classes[10][20], ID[6];
}student_t;

// to keep track of how many students have users we have
typedef struct{
	student_t student[size_arr_student];
	int nbr_of_student_users;
}student_array_t;

typedef struct{
	char name[50];
	char dayFile[2][50];
	int nbr_workshops;
	workshop_t wp[4];
}two_days_t;

typedef enum{
	true,
	false
}boole_t;

char workshop_Status[4][20]={"Open"};
