#include "../headers/date_time.h"

char buffer[100]; 

// This function displays the date on the screen
void print_date(){
	now = time(NULL);
	cur_time = localtime(&now);
	strftime(buffer, 100, "%A %d %B ", cur_time);	
	printf("%s", buffer);
	printf("%d", cur_time->tm_year + 1900);
}

// This function displays the time on the screen
void print_time(){
	now = time(NULL);
	cur_time = localtime(&now);
	strftime(buffer, 100, "%k : %M : %S  %p", cur_time);	
	printf("%s", buffer);
}
