// starts logging in logger.txt.
#include <stdio.h>
#include <stdlib.h>
void logg(){
	freopen("logger.txt","a+",stdout);
}