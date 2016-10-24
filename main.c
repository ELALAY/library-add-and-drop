#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define size_arr_student 10

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

int menu(void); 
void CreateWorkshopOffering(two_days_t *two_days_offering);
void AddWorkshop (const two_days_t *two_days_offering);
void DisplayAvailiableWorkshops(const two_days_t *two_days_offering);
void EnrollStudent(student_array_t *stud, two_days_t *two_days_offering);
//void store_data (const student_array_t *stud, const two_days_t *two_days_offering);
void UnEnrollStudent(student_array_t *stud, two_days_t *two_days_offering);

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

int menu(void){
/*
 *this function prints out the menu after that the user enters the 2-days offering 
 */
	int choice;
	printf("\t\t ***** Menu *****\t\t\n");
	printf("\n1- Create a 2 days offering WS\n2- Add a workshop\n3- Display Available WS\n4- Enroll student\n5- Unenroll student\n6- Save\nchoice >> "); 
	scanf("%d", &choice);
	return choice;
}

void CreateWorkshopOffering(two_days_t *two_days_offering){
	FILE *fp;
	printf("Please choose a 2-days offering period\n e.g (Oct-3)\n");
	printf("the period should be as following:\nMonday Tuesday\nTuesday Wednesday\nWednesday Thursday\nThursday Friday\n");
	scanf("%s", two_days_offering->name);
	
	strcpy(two_days_offering->dayFile[0], two_days_offering->name);
	strcat(two_days_offering->dayFile[0], "_workshops.txt");
	strcpy(two_days_offering->dayFile[1], two_days_offering->name);
	strcat(two_days_offering->dayFile[1], "_student.bin");
	//create the 2 days offering file
	fp = fopen(two_days_offering->dayFile[0], "a");
	fclose(fp);
	fp = fopen(two_days_offering->dayFile[1], "a");
	fclose(fp);
	printf("the time slots available for %s are as follows: ", two_days_offering->name);
	printf("\n1- 8:00-10:00\n2- 10:30 to 12:30\n3- 13:00-15:00\n4- 15:30-17:30\n");
	two_days_offering->nbr_workshops=0; // initialize the counting to 0
}

void AddWorkshop (const two_days_t *two_days_offering){
	char wp_time_slot[4][20]={"8h00-10h00", "10h30-12h30" ,"13h00-15h00", "10h30-12h30"};
	int index1, index2;
	
	printf("You are creating a workshop in the %s \n", two_days_offering->name);
	printf("Enter the name of the workshop >> ");
	scanf("%s", two_days_offering->wp[two_days_offering->nbr_workshops].WpName);

	printf("Enter the workshop's instructor name >> ");
	scanf("%s", two_days_offering->wp[two_days_offering->nbr_workshops].WpInstruct);

	printf("Enter the workshop's capacity >> ");
	scanf("%d", &two_days_offering->wp[two_days_offering->nbr_workshops].capacity);
	getchar();

	printf("Please choose a time slot from the following\n");
	printf("for the first day >>\n1- 8:00-10:00\n2- 10:30 to 12:30\n3- 13:00-15:00\n4- 15:30-17:30\n >> ");
	scanf("%d", &index1);
	printf("for the second day >>\n1- 8:00-10:00\n2- 10:30 to 12:30\n3- 13:00-15:00\n4- 15:30-17:30\n >> ");
	scanf("%d", &index2);
	// we set the number of enrolled students to 0  
    two_days_offering->wp[two_days_offering->nbr_workshops].enrolled_student = 0;
    // we add the time slots to the workshop
    strcpy(two_days_offering->wp[two_days_offering->nbr_workshops].time_slot[0], wp_time_slot[index1-1]); 
	strcpy(two_days_offering->wp[two_days_offering->nbr_workshops].time_slot[1], wp_time_slot[index2-1]);

	//we increase the number of workshops
	two_days_offering->nbr_workshops++;
	//save
}

void DisplayAvailiableWorkshops (const two_days_t *two_days_offering){
	int i, j;
	for(i=0; i<two_days_offering->nbr_workshops; i++)
		printf("%d- %s %d %s %s\n", i+1, two_days_offering->wp[i].WpName, two_days_offering->wp[i].enrolled_student, two_days_offering->wp[i].time_slot[0], two_days_offering->wp[i].time_slot[1]);
}
/*
void store_data (student_array_t *stud, const char dayFile[], two_days_t *two_days_offering){
	FILE *wsFile, *studFile;

	wsFile = fopen(dayFile[0], "a");
	fprintf(wsFile, "%s %s %d %s %s\n", two_days_offering->wp[two_days_offering->nbr_workshops].WpName, two_days_offering->wp[two_days_offering->nbr_workshops].WpInstruct, two_days_offering->wp[two_days_offering->nbr_workshops].capacity, two_days_offering->wp[two_days_offering->nbr_workshops].time_slot[0], two_days_offering->wp[two_days_offering->nbr_workshops].time_slot[1]);

	studFile= fopen(dayFile[2], "a");
	fprintf(wsFile, "%s %s", );
}*/
void EnrollStudent(student_array_t *stud, two_days_t *two_days_offering){
	int choice, i, flag = 0, nbr_of_classes_of_student=0, line_id;
	char id_check[6];
	while(true){
		printf("You are enrolling for a workshop in %s\n", two_days_offering->name);

		printf("Please enter your student ID >> ");
		scanf("%s", id_check);
		
		//find the student user or create a new one
		for(i=0; i<size_arr_student; i++){
			if(strcmp(stud->student[i].ID, id_check) == 0){
				line_id = i;
				break;
			}
			else 
				flag = 1;
		}
		
		if(flag == 1){
			line_id = stud->nbr_of_student_users++;
			strcpy(stud->student[line_id].ID, id_check);
			printf("\nthe id copied is >> -%s\n", stud->student[line_id].ID);
		} 
		else if(flag == 0){
			printf("\n the number of classes of the student: %d\n", stud->student[line_id].nbr_classes);	
			//to make sure the student do not enroll in more than 4 workshops/two days offering
			if(stud->student[line_id].nbr_classes >= 4){
				printf("you already have 4 workshops!");
				break;
			}
		}
		
		do{
		printf("Please choose a workshop :\n");
		DisplayAvailiableWorkshops(two_days_offering);
		printf(" please choose a workshop >> ");
		scanf("%d", &choice);
		
		getchar();
		printf("Are you repeating this course >> ");
		if(getchar() == 'y')
			strcpy(stud->student[line_id].repeated_class[stud->student[line_id].nbr_repeated], two_days_offering->wp[choice-1].WpName);

		//we add the workshop the the classes taken by the student
		strcpy(stud->student[line_id].classes[stud->student[line_id].nbr_classes], two_days_offering->wp[choice-1].WpName);
		stud->student[line_id].nbr_classes = nbr_of_classes_of_student++;
		printf("nbr classes updated %d\n", nbr_of_classes_of_student);
		//we add the student's id to the workshop
		strcpy(two_days_offering->wp[choice-1].Students_IDs[two_days_offering->wp[choice-1].enrolled_student], stud->student[line_id].ID);
		two_days_offering->wp[choice-1].enrolled_student++;
		getchar();
		
		printf("do you want to add another workshop for the same student (y/n)>>");
		}while(getchar() != 'n');
		
		/*
		getchar();	
		printf("Please enter the number of credits you have >> ");
		scanf("%d", &stud->student[line_id].CreditHours);
		
		printf("Please enter your phone number (max 10 digits)>> ");
		scanf("%s", stud->student[line_id].phone);
		*/

		//this is to avoid the infinite loop
		break;
	}
}	
	
void UnEnrollStudent(student_array_t *stud, two_days_t *two_days_offering){
	int i, line_wp, line_id, found_id, choice;
	char id_student[20]; 

	printf("Please enter the student's ID >> "); 
	scanf("%s", id_student);
	getchar();
	getchar();
	printf("9bel for");
	printf("\n\ndakchi lidkhlna fl ID >> %s\n\n", id_student);
	printf("%d", stud->nbr_of_student_users);
	//we take the index of the student of the id
	for(i=0; i<stud->nbr_of_student_users; i++){
		printf("in loop");
		printf("%s", id_student);
		printf("the id found is %s\n", stud->student[i].ID);
		if(strcmp(id_student, stud->student[i].ID) == 0){
			line_id = i;
			printf("the id found is %s\n", stud->student[i].ID);
			break;
		}
	}
	getchar();
	printf("the id found is %s\n", stud->student[i].ID);
	printf("%d\n", line_id);
	printf("baa3 1\n");
	printf("nbr classes %d\n", stud->student[line_id].nbr_classes);
	printf("Please choose the workshop you want to Unenroll >> ");
	//we display the name of the workshops that the student is enrolled into
	for(i=0; i<stud->student[line_id].nbr_classes; i++)
		printf("%d- %s\n", i+1, stud->student[line_id].classes[i]);
	printf(" >> "); 
	scanf("%d", &choice);	
	printf("baa3 2\n");
	//we remove the classes name from the student's classes
	for(i=choice-1; i<stud->student[stud->nbr_of_student_users].nbr_classes; i++)
		strcpy(stud->student[line_id].classes[i], stud->student[line_id].classes[i+1]);

	//we look for the workshop that the student wants to unenroll from the workshops array
	for (i = 0; i < two_days_offering->nbr_workshops; ++i){
		if(strcmp(stud->student[line_id].classes[choice-1], two_days_offering->wp[i].WpName) == 0){
			line_wp = i;
			break;
		}
	}

	// we look for the student's id in the workshop list of students
	for(i=0; i<two_days_offering->wp[line_wp].enrolled_student; i++)
		if(strcmp(two_days_offering->wp[line_wp].Students_IDs[i], stud->student[line_id].ID) == 0){
			found_id = i;
			break;
		}

	//we remove the student's ID from the class
	for(i=found_id; i<two_days_offering->wp[line_wp].enrolled_student; i++)
		strcpy(two_days_offering->wp[line_wp].Students_IDs[i], two_days_offering->wp[line_wp].Students_IDs[i+1]);
		
	stud->student[line_id].nbr_classes--;
	two_days_offering->wp[]
}

