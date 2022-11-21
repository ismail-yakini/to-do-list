#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h> 
#include <stdbool.h> 



#include "headers/date_time.h"
#include "headers/to_do_list.h"


void signal_handler();
void Menu();
int to_do_list();
void setting();

// If the user press ctrl+C the variable will be true
bool sig_caught=false;  
void signal_handler(int sig) 
{ 
  if (sig == SIGINT) { 
    sig_caught=true; 
  } 
} 

// This function displays the date and the time and the saved tasks on the file
int to_do_list(){
	int count;
	// Opening the file containing the tasks
	FILE *file = open_file("database/data.txt", "r");
	if (signal(SIGINT, signal_handler) == SIG_ERR) { 
    	fprintf(stderr, "signal func registration failed\n"); 
    	return 1; 
	} 
 	while(1){
		sleep(1);
    	system("clear");
    	printf("\n\n");
		printf("\t\t\t\t  ***************************************\n");
		printf("\t\t\t\t  *                                     *\n");
		printf("\t\t\t\t  *              To do list             *\n");
		printf("\t\t\t\t  *                                     *\n");
		printf("\t\t\t\t  ***************************************\n");
		printf("\n\n");
		printf("\t\t\t\t\t");
		print_date(); // Printing the date
		printf("\n\n");
		printf("\t\t\t\t\t   ");
		print_time(); // Printing the time
		printf("\n\n");
		// If there is no task
		if(end_of_file(file) != 0){
			// If there is no task
			printf("\n\n");
			printf("\t\t\t\t  +++++++++++++++++++++++++++++++++++++++\n");
			printf("\t\t\t\t  +                                     +\n");
			printf("\t\t\t\t  +       There are no saved tasks      +\n");
			printf("\t\t\t\t  +                                     +\n");
			printf("\t\t\t\t  +++++++++++++++++++++++++++++++++++++++\n");
			printf("\n\n");
			
		}else{
			// If there is a task
			printf("+++++++++++++++++++++++++++++++++++++++| These are your tasks |+++++++++++++++++++++++++++++++++++++++\n\n");
			count = 1;
			while(end_of_file(file)==0){
				fgets(buffer, buffer_size, file);
				printf("%d) %s", count++, buffer);	
				memset(buffer, 0, sizeof(char) * buffer_size);
			}
			printf("\n");
			printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n\n");
			fseek(file, 0, SEEK_SET);
		}
		printf("\n\n");
		printf("\t\t\t\t*******************************************\n");
		printf("\t\t\t\t* Press |ctrl + C | to return to the menu *\n");
		printf("\t\t\t\t*******************************************\n");
		printf("\n\n");
			
    	if (sig_caught) {  
    		sig_caught=false;  // This line is very important to return the signal to his original value
			Menu();
     		return 0; 
    	} 
	} 
}

// This function gives the setting to the user
void setting(){
	system("clear");
	char ch;
	printf("\n\n");
	printf("\t\t\t\t***************************************\n");
	printf("\t\t\t\t*             1) Add tasks            *\n");
	printf("\t\t\t\t***************************************\n");
	printf("\t\t\t\t*           2) Remove tasks           *\n");
	printf("\t\t\t\t***************************************\n");
	printf("\t\t\t\t*           3) Modify tasks           *\n");
	printf("\t\t\t\t***************************************\n");
	printf("\t\t\t\t*     4) Return to the main menu      *\n");
	printf("\t\t\t\t***************************************\n");
	printf("\t\t\t\t*               5) Exit               *\n");
	printf("\t\t\t\t***************************************\n\n");
	do{
		printf("Please enter a choice : ");
		scanf("%c", &ch);
		clean_stdin();
	}while(ch<'1' || ch >'5');

	switch (ch) {
		case '1':
			add_tasks();
			break;
		case '2':
			remove_tasks();
			break;
		case '3':
			modify_tasks(1);
			break; 
		case '4':
			Menu();
			break;
		case '5':
			exit(1);
			break;
	}
}

// The main menu that the program displays in the bigining and the user can return to it frpom other functions
void Menu(){
	system("clear");
	char ch;
	printf("\n\n");
	printf("\t\t\t\t***************************************\n");
	printf("\t\t\t\t*           1) To do list             *\n");
	printf("\t\t\t\t***************************************\n");
	printf("\t\t\t\t*            2) Setting               *\n");
	printf("\t\t\t\t***************************************\n");
	printf("\t\t\t\t*             3) Exit                 *\n");
	printf("\t\t\t\t***************************************\n\n");
	do{
		printf("Please enter a choice : ");
		scanf("%c", &ch);
		clean_stdin();
	}while(ch<'1' || ch >'3');
	switch (ch) {
		case '1':
			to_do_list();
			break;
		case '2':
			setting();
			break;
		case '3':
			exit(1);
			break; 
	}
}

// The main
int main(){	
	Menu();
	return 0;

}
