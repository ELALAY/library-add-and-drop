#include "Fuctions_definition.h"

int main(void){
	int choice, i;
	two_days_t two_days_offering ={.nbr_workshops = 0};
	student_array_t stud = {.nbr_of_student_users = 0};

	// we initialize the nbr of classes of all the students to 0
	for(i=0; i<size_arr_student; i++)
		stud.student[i].nbr_classes = 0;
		
	/*
	test_file = fopen("test_file.txt", "r");
	if(test_file == NULL){
		// we create the file the point the fact that the prog has already been executed at least once
		test_file=fopen("test_file.txt", "w");
			fprintf(test_file, "Hello Word!");
		printf("You need to create a two day workshop offering >> ");
		CreateWorkshopOffering(dayFile, &two_days_offering);
	}*/
//	else{	
		//fill_arrays();
		do{
			do{
				choice = menu();
				switch(choice){
					case 1:
						CreateWorkshopOffering(&two_days_offering);
						break;
					case 2:
						if (two_days_offering.nbr_workshops >= 4){
							printf("you need to create a new offering days !");
						}
						else
						AddWorkshop(&two_days_offering);
						break;
					case 3:
						DisplayAvailiableWorkshops(&two_days_offering);
						break;
					case 4:
						EnrollStudent(&stud, &two_days_offering);
						break;
					case 5:
						UnEnrollStudent(&stud, &two_days_offering);
						break;
					case 6:
						//Exit();
						break;
				}
			}while(choice != 6);
			getchar();
			printf("Do you want to choose another two days offering (y/n) >> ");
		}while(getchar() != 'n');
//	}
	printf("Thank you for using our program !! ");
	return 0;
}


