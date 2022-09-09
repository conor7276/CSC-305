#include "StringUtils.h"
const char NULL_CHAR = '\0';

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
