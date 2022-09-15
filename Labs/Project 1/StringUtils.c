#include "StringUtils.h"
const char NULL_CHAR = '\0';
const char SPACE = ' ';
const char COLON = ':';
const char COMMA = ',';
const char SEMICOLON = ';';
const char PERIOD = '.';
const int STD_STR_LEN = 64;
const int MAX_STR_LEN = 128;
const int STR_EQ = 0;
const int SUBSTRING_NOT_FOUND = -1001;
const Boolean IGNORE_LEADING_WS = True;
const Boolean ACCEPT_LEADING_WS = False;
// File* == char**
/*
Name: compareString
Process: compares two string swith the following results
	if left string is less than right string, returns less than zero.
	if left string is greater than right string, returns greater than zero.
	if left string equals right string . returns zero
	- equals test includes length
Function Input/Parameters: c-style left and right strings (char *)
Function Output/Parameters:	none
Function Output/Returned: result as specified (int)
Device Input/Keyboard: none
Device Output/Monitor: none
Dependencies: getStringLength	
*/

int compareString(const char* OneStr, const char* OtherStr){

	int index = 0;
	int result = 0;
	while(OneStr[index] != NULL_CHAR && OtherStr[index] != NULL_CHAR){

		if(OneStr[index] != OtherStr[index]){
			return result;
		}
	index++;
        }

	int length = max_length(OneStr,OtherStr);
	if(index == length){
		result = 1;
	}
	return result;
}

int find_length(const char *s){
	int length = 0;
	while(s[length] != NULL_CHAR){
		length++;
	}
	return length;

}

int max_length(const char* OneStr, const char* OtherStr){
	int max_length = 0;
	if(find_length(OneStr) > find_length(OtherStr)){
		return find_length(OneStr);
	}
	else{
		return find_length(OtherStr);
	}
	// return find_length(OneStr)
}

/*
	Name: concatenateString
	Process: appends one string onto another
	Function Input/Parameters: c-style source strings (char *)
	Function Output/Parameters: c-style destination string (char *)
	Function Output/Returned: none
	Device Input/Keyboard: nonr
	Device Output/Monitor: none
	Dependencies: getStringLength
*/

void concatenateString(char* destStr, const char* sourceStr){
	int destStrlen = find_length(destStr);
	// int destIndex = getStringLength(destStr)
	int sourceStrlen = find_length(sourceStr);
 	char* temp = (char*) malloc(sizeof(char)* (destStrlen + sourceStrlen));
	int destStrIndex = 0;
	int sourceStrIndex = 0;
	int index = 0;
	while( destStr[destStrIndex] != NULL_CHAR){
		temp[index] = destStr[destStrIndex];
		index++;
		destStrIndex++;
	}
	while( sourceStr[sourceStrIndex] != NULL_CHAR){
		temp[index] = sourceStr[sourceStrIndex];
		index++;
		sourceStrIndex++;
	}
	printf("Combined String is %s \n", temp);
	copyString(destStr,temp);
}

/*
Name: copyString
Process: copies one string into another.
		 overwriting data in the destination string.
Function Input/Parameters: c-style source string (char *)
Function Output/Parameters: c-style destination string (char *)
Function Output/Returned: none
Device Input/Keyboard: none
Device Output/Monitor: none
Dependencies: getStringLength
*/

void copyString(char* destStr, const char* sourceStr){
	free(destStr);
	int sourceLength = find_length(sourceStr);
	destStr = (char*) malloc(sizeof(char)*sourceLength);
	int index = 0;
	while (sourceStr[index] != NULL_CHAR){

		destStr[index] = sourceStr[index];
		index++;
	}
	free(sourceStr);
}

/*
Name: findSubString
Process: linear search for given substring within another string
Function Input/Parameters: c-style source test string (char *)
						   c-style search string (char *)
Device Input/Keyboard: none
Device Ouotput/Monitor: none
Dependencies: getStringLength
*/

int findSubString( const char *testStr, const char *searchSubStr)
{
	// initialize function/variables

	// initialize test string length
		// function : getStringLength

	int testStrLen = getStringLength(testStr);
	// initialize master index - location of subs tring start point
	int masterIndex = 0;
	// initialize other variables
	int searchIndex, internalIndex;
	// loop across test string
	while( masterIndex < testStrLen){
		//set internal loop index to current test string index
		internalIndex = masterIndex;
		// set internal search index to zero
		searchIndex = 0;
		
		// loop to end of test string
		// while test string/sub string characters are the same

		while( internalIndex <= testStrLen && testStr[internalIndex] == searchSubStr[searchIndex])
		{
				// increment test string, substring indices
				internalIndex++; searchIndex++;

				if( searchSubStr[searchIndex] == NULL_CHAR){
					// return beginning location of sub string
					return masterIndex;
				}
		}
		// end interanl comparison loop

		// increment current beginning location index
		masterIndex++;		

		// assume test have fauled at this point return SUBSTRING_NOT_FOUND;
		return SUBSTRING_NOT_FOUND;

	}


}





