#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

#define buffer_size 1024
char buffer[buffer_size];

void setting(); 
FILE *open_file();
int task_exist(FILE *file);
int print_tasks(FILE *file);
void remove_rename();
void clean_stdin();
int end_of_file(FILE * file);
int counter_value(char *string);
long long int Atoi(char *characters);
int add_tasks();
int modify_tasks();
int remove_tasks();
