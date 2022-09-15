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
/*
Name: find_length
Process: find the length of a string by counting characters up to the NULL_CHAR character
Function Input/Parameters: c-style string (char *)
Function Output/Parameters: None
Function Output/Returned: length of string
Device Input/keyboard: none
Device Output/Monitor: none
Dependencies: none
*/
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

/*
Name: getStringConstrained
Process: capture a string form the input stream
		 to a specified delimiter;
		 Note: Consumes delimiter
Function Input/Parameters: input stream (File *) stops at specified delimiter (char),
Function Output/ParametersL string returned (char *)
Function Output/Returned: success of operation (bool)
Device Input/Keyboard: none
Device Output/Monitor: none
Dependencies: fgetc
*/

bool getStringConstrained(
						FILE *instream,
						bool clearLeadingNonPrintable,
						bool clearLeadingSpace,
						bool stopAtNonPrintable,
						char delimiter,
						char *capturedString){
	// initialize variables
	int intChar = EOF, index = 0;
	//initialize output string
	capturedString[index] = NULL_CHAR;
	// caputer first value ins tream
	// function: fgetc
	intChar = fgetc(instream);

	// loop to clear non printable or space, if indicated
	while ((intChar != EOF) && ((clearLeadingNonPrintable && intChar == (int)SPACE)) || (clearLeadingSpace && intChar == (int)SPACE))
	{
		// get next character
		// function: fgetc
		intChar = fgetc(inStream);
	}
	if(intChar == EOF)
	{
		//return Failed Operation
		return false;
	}

	// loop to capture input

	while(
	
		//continues if not at end of file and max string length not reached
		(intChar != EOF && index < MAX_STR_LEN - 1)

		// AND continues if not printable flag set and characters are printable
		// or continues if not printable flag not set
		&& ((stopAtNonPrintable && intChar >= (int)SPACE) || (!stopAtNonPrintable))

		// AND
		// continues if specified delimiter is not found
		&& (intChar != (char)delimiter)
		)
	{
	// place character in array element
	capturedString[index] = (char)intChar;

	// increment array inde
	index++;

	// set next element to null character / end of c-string
	capturedString[index] == NULL_CHAR;

	// get next character as integer
	// function :fgetc
	intChar = fgetc(inStream);
	}
	//end loop
	//return successful operation
	return true;
}

/*
Name: getStringToDelimiter
Process: capture a string from the input stream to a specified delimtiter
Note: Consumes Delimiter
Function INput/Parameters: input stream (FILE *) stops at specified delimiter (char),
Function Output/Parameters: string returned (char *)
Device Input/Keyboard: none
Device Output/Monitor: none
Dependencies: getStringConstrained
*/
bool getStringToDelimiter(FILE *instream, char delimiter, char *capturedString)
{
	// call engine function with delimiter
	// function: getStringConstrained
	return getStringConstrained(
							     inStream, 		//file stream pointer
								 true,			// clears leading non printable character
								 true, 			// bool clearLeadingSpace,
								 true,			// stops at non printable
								 delimiter,		// stops at delimiter
								 capturedString // returns String
								);								
}

/*
Name: getStringToLineEnd
Process: capture a string from the input stream to the endo f the line
Function Input/Parameters: input stream (FILE *)
Function Output/Parameters: string returned(char *)
Function Output/Returned: success of operation (bool)
Device Input/Keyboard: none
Device Output/Monitor: none
Dependencies: getStringConstrained
*/
bool getStringToLineEnd(FILE *inStream, char *capturedString)
{
	// call engine function with delimiter
	// function: getStringConstrained
	return getStringConstrained(
								 inStream, 			//file stream pointer
								 true,				// clears leading non printable character
								 true, 				// bool clearLeadingSpace,
								 true,				// stops at non printable
								 NON_PRINTABLE_CHAR,// non printable delimiter
								 capturedString 	// returns String
								);
	
}

/*
Function name: getSubString
Process: captures sub string within larget string between two inclusive indices
		 return empty string if either index is out of range, assumes enough memory in destination string
Function Input/Parameters: c-style source string (char *), start and end indices (int)
Function Output/Parameters: c-style destination string (char *)
Device Input/Keyboard: none
Device Output/Monitor: none
Dependencies: getStringLength, malloc, copyString, free
*/

void getSubString(char *destStr, const char *sourceStr, int startIndex, int endIndex)
{
	// initialize function/variables
	// set length of source string
	// function getStringLength
	int sourceStrLen = getStringLength(sourceStr);

	// initialize destination index to zero
	int destIndex = 0;

	// initalize source index to start index (parameter)
	int sourceIndex = startIndex;

	// create pointer to temp string
	char *tempStr;

	// check for indices within limits
	if( startIndex >= 0 && startIndex <= endIndex && endIndex < sourceStrLen)
	{
		// create temporary string
		// function: malloc, copyString
		tempStr = (char *) malloc(sourceStrLen + 1);
		copyString( tempStr, sourceStr);

		// loop across requested substring (indices)
		while( sourceIndex <= endIndex)
		{
			// assign source character to destination element
			destStr[destIndex] = tempStr[sourceIndex];

			// increment indices
			destIndex++;
			sourceIndex++;

			// set temporary end of destination string
			destStr[destIndex] = NULL_CHAR;

		}
		// end loop

		// release memory for temporary string 
		// function: free
		free(tempStr);
	}
}

/*
Name: setStrToLowerCase
Process: iterates through string, sets an upper case letter to lower case;
		 no effect on other letters.
Function Input/Parameters: c-style source string (char *)
Function Output/Parameters: c-style destination string (char *)
Function Output/Returned: none
Device Input/Keyboard: none
Device Output/Keyboard: none
Dependencies: toLowerCase
*/

void setStrToLowerCase( char *destStr, const char *sourceStr)
{
	// initalize function/variables
	// get source string length
	// function: getStringLength

	int sourceStrLen = getStringLength(sourceStr);
		// create temporary string pointer

	char *tempStr;

	//create other variables
	int index = 0;

	//copy source string in case of aliasing
	// function: malloc, copyString

	tempStr = (char *) malloc (sizeof(sourceStrLen + 1));
	copyString(tempStr,sourceStr);

	// loop across Source String
	while( tempStr[index] != NULL_CHAR && index < MAX_STR_LEN)
	{
		//set indivdual character to lower case as needed, assign to destination string
		destStr[index] = toLowerCase(tempStr[index]);

		//update index
		index++;

		// set temporary end of destination string
		destStr[index] == NULL_CHAR;
	}

	//release memory used for temp string
	// function: free
	free(tempStr);
}


/* Function Name: toLowerCase
Process: if character is upper case, sets it to lower case otherwise returns character unchanged
Function Input/Parameters: test character (char)
Function Output/Parameters: none
Function Output/Returned: character to set to lower case, if appropriate
Device Input/Keyboard: none
Device Output/Monitor: none
Dependencies: none
*/
char toLowerCase(char testChar)
{
	// check for uppercase letter
	if( testChar >= 'A' && testChar <= 'Z')
	{
		//return lower case letter
		testChar == testChar - 'A' + 'a';
	}
	// otherwise, assume no uppercase letter,
	// return character unchanged
	return testChar;
}

int getLineTo(FILE *filePtr, int bufferSize, char stopChar, char *buffer,
			Boolean omitLeadingWhiteSpace, Boolean stopAtNonPrintable)
{
	//initialize function/variables
	int charAsInt, charIndex = 0;
	int statusReturn = NO_ERR;
	Boolean bufferSizeAvailable = True;
	Boolean nonPrintableFound = False;

	// get first character (as integer)
	// function: fgetc
	charAsInt = fgetc(filePtr);

	// consume leading white space, if flagged
	while( omitLeadingWhiteSpace == True && charAsInt != (int) stopChar && charIndex < bufferSize && charAsInt <= (int) SPACE)
	{
		// get next character (as integer)
		// function: fgetc
		charAsInt = fgetc(filePtr);

	}

	// cheack for stop at non printable if needed
	if(stopAtNonPrintable == True && charAsInt < (int)SPACE)
	{
		// set non printable flag to true
		nonPrintableFound = True;
	}
	// capture String
	// loop while character is not stop character and buffer size available

	while(charAsInt != (int) stopChar && nonPrintableFound == False && bufferSizeAvailable == True)
	{
		// check for input failure
		// function: isEndOfFile
		if( isEndOfFile(filePtr) == True)
		{
			// return incomplete file error
			return INCOMPLETE_FILE_ERR;
		}
		// check for usable (printable character)
		if(charAsInt >= (int) SPACE)
		{
			// assign input character to buffer string
			buffer[charIndex] = (char) charAsInt;

			// increment index
			charIndex++;
		}
		// set next buffer element to null character
		buffer[charIndex] = NULL_CHAR;

		//check for not at end buffer size
		if(charIndex < bufferSize - 1)
		{
			// get a new character
			charAsInt = fgetc(filePtr);
			// check for stop non printabl eif needed
			if(stopAtNonPrintable == True && charAsInt < (int)SPACE)
			{
				// set non printable flag to true
				nonPrintableFound = True;
			}

		} // otherwise assume end of buffer size
		else
		{
			// set buffer size Boolean to false to end loop
			bufferSizeAvailable = False;

			// set status return to buffer overrun
			statusReturn = INPUT_BUFFER_OVERRUN_ERR;
		}
	}

	// return operation status
	return statusReturn;
}

Boolean isEndOfFile(FILE *filePtr)
{
	// check for feof end of file response
	if(feof(filePtr) != 0)
	{
		// return true
		return True;
	}
	// return false
	return False;

}
