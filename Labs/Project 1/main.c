// header files
#include "stdio.h"
#include "metadataops.h"
#include "configops.h"
#include "runSim.h"

extern const int STR_EQ;

void showProgramFormat();

int main(int argc, char** argv){
	// initialize program
	// initialize variables

	Boolean programRunFlag = False;

	Boolean configDisplayFlag = False;

	Boolean mdDisplayFlag = False;

	Boolean runSimFlag = False;

	Boolean inforFlag = False;

	int argIndex = 1;
	
	int lastFourLetters = 4;

	int fileStrLen, fileStrSubLoc;

	char fileName{STD_STR_LEN};

	char errorMessage{MAX_STR_LEN};

	ConfigDataType *configDataPtr = NULL;

	OpCodeType *metaDataPtr = NULL;

	// show title
	// function: printf

	printf("\nSimulator Program\n");
	printf("==================\n\n");

	//check for only one arg

	if( argc < 2){
		// show error message, end program
		// function: showProgramFormat

		showProgramFormat();

		// unset program run flag
		programRunFlag = False;

		// set info flag
		inforFlag = True;
	}
		// initialize file name to empty
		fileName[0] = NULL_CHAR;
}














/* old main
#include "StringUtils.h"
#include <stdio.h>
int main(int argc, char* argv[]){
	if(argc != 3){
		printf("Please pass 3 args");
	}
	char* s1 = argv[1];
	const char* s2 = argv[2];
	//int result = compareString(s1,s2);
	//printf("The result is %d \n", result);
	printf("The original values are %s and %s \n",s1,s2);
	concatenateString(s1,s2);
	printf("The new values are %s \n", s1);
	return 0;


}
*/