#include "../headers/to_do_list.h"

// This function opens files and displays an error message if this is not done
FILE *open_file(char *path, char *mode){
	// FILE* file = NULL;
	FILE* file ;	
	file = fopen(path,mode);
	if(file == NULL){
		printf("\n\t\t\tThere is a problem with opening the file !");
		exit(1);
	}
	return file;
}

// This function checks if there is a task exist
int task_exist(FILE *file){
	if(end_of_file(file) == 1){
		printf("\n\n");
		printf("\t\t\t\t    ***********************************\n");
		printf("\t\t\t\t    *    There are no saved tasks !   *\n");
		printf("\t\t\t\t    ***********************************\n\n");
		fclose(file);
		sleep(2);
		setting();
		return 0;
	}
}

// This function displays the tasks on the screen and asks the user to choose one of them
void printing_chosing_tasks(FILE *file, int *count, int *num){
	(*count) = 1;
	fseek(file, 0, SEEK_SET);
	while(end_of_file(file)==0){
		fgets(buffer, buffer_size, file);
		printf("%d) %s", (*count)++, buffer);	
	}
	printf("\n\n");
	(*count)--;
	fseek(file, 0, SEEK_SET);
	memset(buffer, 0, sizeof(char) * buffer_size);
	do{
		printf("Please enter the number of the task do you want to modify (enter 0 to return to the menu) : ");
		fgets(buffer, 10, stdin);
		(*num) = (int)Atoi(buffer);
		memset(buffer, 0, sizeof(char) * buffer_size);
	}while((*num) < 0 || (*num) > (*count));
}

// This function removes the old file and renames the new file
void remove_rename(){
	//////////////////////////////  Removing the old file  ////////////////////////////
	if (remove("database/data.txt") != 0){
		printf("\n\nThere is a problem with removing the old file\n\n");
		exit(1);
	}
	//////////////////////////////  Renaming the new file  ////////////////////////////
	if(rename("database/data2.txt", "database/data.txt") != 0){
		printf("\n\nThere is a problem with renaming the new file\n\n");	
		exit(1);
	}
}

// This function checks if the file end
int end_of_file(FILE * file){
	if(fgetc(file) == EOF){
		fseek(file, -1, SEEK_CUR);
		return 1;
	}else{
		fseek(file, -1, SEEK_CUR);
		return 0;
	}
}

// This function check if the string start by a (-) or not (this function used just in the Atoi function !)
int counter_value(char *string){
	return (string[0] == '-')? 1 : 0;
}
// This function converts a string to a number
long long int Atoi(char *characters){
	long long int num = 0;
	bool isZero = true;
	int i;
	if(counter_value(characters) == 1 && strlen(characters) == 2){
		return -1;
	}
	int length = strlen(characters);
	if(characters[length-1] == '\n'){
		length--;
	}
	i = counter_value(characters);
	for( ; i<length; i++){
		if(characters[i] < 48 || characters[i] > 57){
			return -1;
		}
		if(characters[i] != 48){
			isZero = false;
		}
	}
	if(isZero == true){
		return 0;
	}
	i = counter_value(characters);
	for( ;i<length; i++){
		num += (characters[i] - 48);
		if(i != (length-1)){
			num *= 10;
		}
	}
	if(counter_value(characters) == 1){
		num *= -1;
	}
	return num;
}

// This function for cleaning the buffer we use it after scanf function it is so important
void clean_stdin(){
	while(getchar() != '\n');	
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////

// This function to add tasks and saving them on a file
int add_tasks(){

	FILE * file = open_file("database/data.txt","a"); //  Opening the file to stor the tasks
	char ch;//this variable to store the choice of the user
	repeate : // This line for add another task

	system("clear");
    printf("\n\n");
	printf("\t\t\t\t***************************************\n");
	printf("\t\t\t\t*                                     *\n");
	printf("\t\t\t\t*              Add tasks              *\n");
	printf("\t\t\t\t*                                     *\n");
	printf("\t\t\t\t***************************************\n");
	printf("\n\n");
	
	memset(buffer, 0, sizeof(char) * buffer_size); //Clean the buffer

	///////////////////////  Entring the task and checking if it's correct  ///////////////////////
	printf("Please enter the task (enter 0 to return to the menu) : ");
	fgets(buffer, buffer_size, stdin);
	if(strlen(buffer) == 2 && buffer[0] == '0'){
		fclose(file);
		setting();
		return 0;
	}
	// printf("your task is : %s", buffer);
	if(strlen(buffer) == 1){
		
		printf("\n\n");
		printf("\t\t\t\t\t    ***********************************\n");
		printf("\t\t\t\t\t    * Enter at least one charachter ! *\n");
		printf("\t\t\t\t\t    ***********************************\n\n");
		sleep(2);
		goto repeate; // to enter the task again
	} 
	buffer[strlen(buffer)] = '\0';	
	///////////////////////////////////////////////////////////////////////////////////////////////
	
	///////////////////////////////  Writting the task on the file  ///////////////////////////////
	if((fputs(buffer, file)) > 0){
		printf("\n\n");
		printf("\t\t\t\t***************************************\n");
		printf("\t\t\t\t*                                     *\n");
		printf("\t\t\t\t*       Task saved Successfully       *\n");
		printf("\t\t\t\t*                                     *\n");
		printf("\t\t\t\t***************************************\n");
		printf("\n\n");
	}else{
		printf("There is an error with writting on the file\n");
		fclose(file);
		exit(1);
	}
	///////////////////////////////////////////////////////////////////////////////////////////////

	//////////////////////////  Asking the user for adding another task  //////////////////////////
	do{
		printf("\nDo you want to add another task (Y/N) : ");
		scanf("%c", &ch);
		clean_stdin();
		if(ch == 'y' || ch == 'Y'){
			goto repeate; // to add another task
		}else if(ch == 'n' || ch == 'N'){
			fclose(file);
			setting();
			return 0; 
		}
	}while(ch != 'Y' && ch != 'y' && ch != 'N' && ch != 'n');
	///////////////////////////////////////////////////////////////////////////////////////////////	
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////

// This function to remove tasks from the file
int remove_tasks(){	

	FILE * file = open_file("database/data.txt","r"); //  Opening the file containing the tasks

	char ch; //this variable to store the choice of the user
	int num; //this variable to store the choice of the user
	int count; //this variable to count the number of tasks

	system("clear");
    printf("\n\n");
	printf("\t\t\t\t***************************************\n");
	printf("\t\t\t\t*                                     *\n");
	printf("\t\t\t\t*             remove task             *\n");
	printf("\t\t\t\t*                                     *\n");
	printf("\t\t\t\t***************************************\n");
	printf("\n\n");

	task_exist(file); //  Checking if the file containing the tasks

	// writting the tasks on the screen and Choosing the task to remove or returning to the setting
	printing_chosing_tasks(file, &count, &num);


	////////////////////////  removing the task or returning to the setting  ////////////////////////
	if(num == 0){																				 
		fclose(file);																			   
		setting();	
		return 0;	
	}else{

		FILE * newFile = open_file("database/data2.txt","w"); // creating a new file to store the unremoved tasks
		
		////////////////////////////  Writting on the new file  ////////////////////////////
		for(int i=1; i<=count; i++){
			fgets(buffer, buffer_size, file);
			if(i != num){
				if(fputs(buffer, newFile) < 0){
					printf("\n\nThere is a problem with writting on the new file \n");
					fclose(newFile);
					exit(1);
				}
			}
		}

		///////////////////////////////  Closing the files  ///////////////////////////////
		fclose(file);
		fclose(newFile);

		remove_rename(); // Removing the old file and Renaming the new file

	}

	/////////////////////////////////////////////////////////////////////////////////////////////////

	printf("\n\n");
	printf("\t\t\t\t***************************************\n");
	printf("\t\t\t\t*                                     *\n");
	printf("\t\t\t\t*      Task removed Successfully      *\n");
	printf("\t\t\t\t*                                     *\n");
	printf("\t\t\t\t***************************************\n");
	printf("\n\n");

	//////////////////////////  Asking the user for removing another task  //////////////////////////
	
	// if the counter equal to one that means there is no task to remove again 
	if(count > 1){ 
		do{
			printf("\nDo you want to remove another task (Y/N) : ");
			scanf("%c", &ch);
			clean_stdin();
			if(ch == 'y' || ch == 'Y'){
				remove_tasks();
				return 0;
			}else if(ch == 'n' || ch == 'N'){
				setting();
				return 0;
			}
		}while(ch != 'Y' && ch != 'y' && ch != 'N' && ch != 'n');
	
	}else{
		sleep(1.5);
		setting();
		return 0;
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////



}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////

// This function to modify tasks in the file
int modify_tasks(){

	FILE * file = open_file("database/data.txt","r"); //  Opening the file containing the tasks

	char ch; //this variable to store the choice of the user
	int num; //this variable to store the choice of the user
	int count; //this variable to count the number of tasks

	system("clear");
    printf("\n\n");
	printf("\t\t\t\t***************************************\n");
	printf("\t\t\t\t*                                     *\n");
	printf("\t\t\t\t*             Modify task             *\n");
	printf("\t\t\t\t*                                     *\n");
	printf("\t\t\t\t***************************************\n");
	printf("\n\n");

	task_exist(file); //  Checking if the file containing the tasks

	// writting the tasks on the screen and Choosing the task to remove or returning to the setting
	printing_chosing_tasks(file, &count, &num);


	////////////////////////  removing the task or returning to the setting  ////////////////////////
	if(num == 0){																				 
		fclose(file);																			   
		setting();	
		return 0;	
	}else{
		FILE * newFile = open_file("database/data2.txt","w"); // Creating a new file to store the unremoved tasks

		////////////////////////////  Writting on the new file  ////////////////////////////
		for(int i=1; i<=count; i++){
			fgets(buffer, buffer_size, file);
			if(i != num){
				if(fputs(buffer, newFile) < 0){
					printf("\n\nThere is a problem with writting on the new file \n");
					fclose(file);
					fclose(newFile);
					exit(1);
				}
				memset(buffer, 0, buffer_size);
			}else{
				repeate:
				memset(buffer, 0, buffer_size);
				printf("\nEnter the modification : ");
				fgets(buffer, buffer_size, stdin);
				if(strlen(buffer) == 1){
					printf("\n");
					printf("\t\t\t\t    ( Enter at least one charachter ! )\n");
					goto repeate; // to enter the task again
				} 
				if(fputs(buffer, newFile) < 0){
					printf("\n\nThere is a problem with writting on the new file \n");
					fclose(file);
					fclose(newFile);
					exit(1);
				}
				memset(buffer, 0, buffer_size);
			}
		}

		///////////////////////////////  Closing the files  ///////////////////////////////
		fclose(file);
		fclose(newFile);
	
		remove_rename(); // Removing the old file and Renaming the new file

	}

	/////////////////////////////////////////////////////////////////////////////////////////////////

	printf("\n\n");
	printf("\t\t\t\t***************************************\n");
	printf("\t\t\t\t*                                     *\n");
	printf("\t\t\t\t*      Task modifyed Successfully      *\n");
	printf("\t\t\t\t*                                     *\n");
	printf("\t\t\t\t***************************************\n");
	printf("\n\n");

	//////////////////////////  Asking the user for modifying another task  //////////////////////////

	do{
		printf("\nDo you want to modify another task (Y/N) : ");
		scanf("%c", &ch);
		clean_stdin();
		if(ch == 'y' || ch == 'Y'){
			modify_tasks();
			return 0;
		}else if(ch == 'n' || ch == 'N'){
			setting();
			return 0;
		}
	}while(ch != 'Y' && ch != 'y' && ch != 'N' && ch != 'n');

	/////////////////////////////////////////////////////////////////////////////////////////////////

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////

