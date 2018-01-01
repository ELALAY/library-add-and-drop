#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Structures.h"

//------------------------------------------------------------------------------
//---------------------------------prototypes-----------------------------------
//------------------------------------------------------------------------------

int menu(void); 
void CreateWorkshopOffering(two_days_t *two_days_offering);
void AddWorkshop (const two_days_t *two_days_offering);
void DisplayAvailiableWorkshops(const two_days_t *two_days_offering);
void EnrollStudent(student_array_t *stud, two_days_t *two_days_offering);
//void store_data (const student_array_t *stud, const two_days_t *two_days_offering);
void rollStudent(student_array_t *stud, two_days_t *two_days_offering);
