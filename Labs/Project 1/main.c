#include "StringUtils.h"
#include <stdio.h>
int main(int argc, char* argv[]){
	if(argc != 3){
		printf("Please pass 3 args");
	}
	const char* s1 = argv[1];
	const char* s2 = argv[2];
	//int result = compareString(s1,s2);
	//printf("The result is %d \n", result);
	printf("The original values are %s and %s \n",s1,s2);
	concatenateString(s1,s2);
	printf("The new values are %s \n", s1);
	return 0;


}
