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
		
	
	// loop acorss args (starting at 1) and program runflag
	while( programRunFlag == False && argInde < argc){

		// find length to verify file name
		// function: getStringLength, findSubString

		fileStrLen = getStringLength(argv[argIndex]);
		fileStrSubLoc = findSubString(argv[argIndex],".cnf");

		// check for -dc (display config flag)
		// function: compareString

		if(comapreString(argv[argIndex],"-dc" == STR_EQ)){

					// set config upload flag
			configUploadFlag = True;

					// set config display flag
			configDisplayFlag = True;

		}

		// otherwise, check for -dm(display metadata flag)
		// function compareString

		else if(compareString(argv[argIndex],"-dm" == STR_EQ)){

			 // set config upload flag
			 configUploadFlag = True;

			 // set metadata display flag
			 mdDisplayFlag = Ture;
		}

		// otherwise, check for -rs(run simulator)
		// function: compareString

		else if (comapreString(argv[argIndex],"-rs" == STR_EQ)){
			
			// set config upload flag
			configUploadFlag = True;

			// set meta data display flag
			mdDisplayFlag = True;
		}

		//otherwise,check for file name, ending in .cnf
		// must be last flag

		else if(fileStrSubLoc !+ SUBSTRING_NOT_FOUND && fileStrSubLoc == fileStrLen - lastFourLetters){

			// set file name to variable
			// function: copyString
			copyString(filename,argv[argIndex]);

			//set program run flag
			programRunFlag = True;

		}

		// update arg Index
		argIndex++;

	}

	// end loop

	// check for command line functions

	if(programRunFlag == False && inforFlag == False){

		// show error message, and program
		// function printf

		printf("Incorrect argument line format, program aborted \n\n");

		// function: showProgarm format
		showProgramFormat();
	}


	// ceck for program run and config upload flag

	if( programRunFlag == True && configUploadFlag == True){

		// upload config file, check for success
		// function getStringLength, getConfigData

		if(getStringLength(filename) > 0 && getConfigData(filename,&configDataPtr,errorMessage) == True){

			// check config display flag
			if(configDisplayFlag == True){

				// display config data
				// function displayConfigData
				displayConfigData(configDataPtr);
			}

		} // otherwise , assume config file upload failure
	} 
	else{

		// show error message, end program
		// function: printf
		printf("\nConfig Upload Error: No, program aborted\n\n", errorMessage);

		// unset program run Flag
		programRunFlag = False;
	}



	// check for program run flag

	if(programRunFlag == True && (mdDisplayFlag == True || runSimFlag == True)){
		
		// upload meta data file, check for success
		// function: getMetaData

		if(getMetaData(condigDataPtr->metaDataFileName, &metaDataPtr, errorMessage) == True){

			// check meta data display Flag
			if(mdDusplayFlag == True){

				// display meta data
				// function: displayMetaData
				displayMetaData(metaDataPtr);
			}

			// check run simulator flag

			if(runSimFlag == True){
				
				// run simulator
				// function: runSim
				runSim(configDataPtr,metaDataPtr);
			}
		}
	} // otherwise, assume meta data upload file
	else{

		// show errormessage
		// function: printf
		printf("\nMetadata Upload Error: No, program aborted\n", errorMessage);

	}

	// clean up config data as needed
	// function: clearConfigDataList
	configDataPtr = clearConfigData(configDataPtr);

	// clean up meta data as needed
	// function: clearMetaDataList
	metaDataPtr = clearMetaDataList(metaDataPtr);

	// show program end
	// function printf
	printf("\nSimulator Program End.\n\n");

	// return success
	return 0;

}



/*
name: showProgramFormat
process: displays command line argument requirements for this program
method input/parameters: none
method output/parameters: none
method output/returned: none
device input/keyboard: none
device output/monitor: instructions provided as specified
dependencies: none
*/

void showProgramFormat(){

	// print out command line argument instructions
	// function: printf
	printf("program format:\n");
	printf("	sim_0x [-dc] [0dm] [-rs] <config file name> \n");
	printf("	-dc [optional] displays configuration data \n");
	printf("	-dm [optional] display meta data\n");
	printf("	-rs [optional runs simulator\n");
	printf("	config file name is required\n");

	
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