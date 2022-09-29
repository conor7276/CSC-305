#include"metadataops.h"

// constant
const int BAD_ARG_VAL = -1;

/*
Function Name: addNode
Algorithm: adds op command structure with data to a linked list
PreCondition: linked list pointer assigned to null or to one op command link,
              struct pointer asigned to op command struct data.
Post Condition: assigns new structure node to beginning of linked list
              or and of established linked list.
Expection: none
Notes: assumes memory access/availability
*/
OpCodeType *addNode(OpCodeType *localPtr, OpCodeType *newNode){

    // check for local pointer assigned to NULL
    if(localPtr == NULL){
        // access memort for new link/node
        // function: malloc
        localPtr = (OpCodeType *) malloc(sizeof(OpCodeType));

        // assign all three values to newly created node
        // assign next pointer to NULL
        // function: copyString
        localPtr->pid - newNode->pid;
        copyString(localPtr->command, newNode->command);
        copyString(localPtr->inOutArg, newNode->inOutArg);
        copyString(localPtr->strArg1, newNode->strArg1);
        localPtr->intArg2 = newNode->intArg2;
        localPtr->intArg3 = newNode->intArg3;
        localPtr->opEndTime = newNode->opEndTime;
        localPtr->nextNode = NULL;

        //return current local pointer
        return localPtr;
    }

    // assume end of list not found yet
    // assign recursive function to current's next link
    // function: addNode
    localPtr->nextNode = addNode(localPtr->nextNode, newNode);

    // return current local pointer
    return localPtr;
}


/*
Function Name: clearMetaDataList
Algorithm: recursively iterates through op code linked list,
           returns memory to OS from the bottom of the list upward
Precondition: linked list, with or without data
Postcondition: all node memory, id any, is returned to OS,
               return pointer (head) is set to NULL.
Exceptions: None
Notes: None
*/
OpCodeType *clearMetaDataList(OpCodeType *localPtr){

    // check for local pointer not set to null (list not empty)
    if(localPtr != NULL){
        // call recursive function with next pointer
        // function: clearMetaDataList
        clearMetaDataList(localPtr->nextNode);

        // after recursiv ecall, release memory to OS
        free(localPtr);

        // set local pointer to NULL;
        localPtr = NULL;
        
    }
    
    // return NULL to calling function
    return NULL;
}

/*
Function Name: displayMetaData
Algorithm: iterates through op code linked list,
            displays op code dat individually
Precondition: linked list, wit or without data
                (should not be called if no data)
Postcondition: displays all ops codes in list
Exceptions: none
Notes: none
*/

void displayMetaData(OpCodeType *localPtr){

    // display title, with underline
    // function: printf
    printf("Meta-Data File Display\n");
    printf("---------------------\n\n");

    // loop until end of linked list
    while(localPtr != NULL){

        // print leader
        // function: printf
        printf("Op Code: ");

        // print op code pid
        // function: printf
        printf("/pid: %d", localPtr->pid);

        // print op code command
        // function: printf
        printf("/cmd: &s", localPtr->command);

        // check for dev op command
        if(compareString(localPtr->command, "dev") == STR_EQ){

            // print in/out parameter
            // function: printf
            printf("/io: %s", localPtr->inOutArg);
        } // otherwise assume other than dev
        else{

            // print NA
            // function printf
            printf("/io: NA");
        }
        // print first string argument
        // function: printf
        printf("\n\t /arg1: %s", localPtr->strArg1);

        // print first int argument
        // function: printf
        printf("/arg 2: %d", localPtr->intArg2);

        // print second int argument
        // function: printf
        printf("/arg 3: %d", localPtr->intArg3);

        // print op end time
        // function: printf
        printf("/op end time: %8.6f" localPtr->opEndTime);

        // end line
        // function: printf
        printf("\n\n");

        // assign local pointer to next node
        localPtr = localPtr->nextNode;
    }
    // end loop access node
}


/*
Function Name: getCommand
Algorithm: gets first three letters of input string to get command
Precondition: provided starting index
Postcondition: returns command (ref param) and updated index (return)
Exceptions: none
Notes: none
*/
int getCommand(char *cmd, char *inputStr, int index){
    
    // initialize variables
    int lengthOfCommand = 3;

    // loop access command length
    while(index < lengthOfCommand){

        // assign character from input string to buffer string
        cmd[index] = inputStr[index];

        // increment index
        index++;

        // set next character to null character
        cmd[index] = NULL_CHAR;
    }

    // return current index
    return index;
}

/*
Function Name: getMetaData
Algorithm: acquires the metadata items from file, stores them in a linked list
Precondition: provided file name
Postcondition: returns success (Boolean), returns linked list head via parameter.
                returns endstate/error message via parameter
Exceptions: function halted and error message returned if bad input data
Notes: None
*/
Boolean getMetaData(char* filename, OpCodeType **opCodeDataHead, char *endStateMsg){

    // initalize function/variables
    const char READ_ONLY_FLAG[] = "r";

    // intialize variables
    int accessResult, startCount = 0, endCount = 0;
    char dataBuffer[MAX_STR_LEN];
    Boolean ignoreLeadingWhiteSpace = True;
    Boolean stopAtNonPrintable = True;
    Boolean returnState = True;
    OpCodeType *newNodePtr;
    OpCodeType *localHeadPtr = NULL;
    FILE *fileAccessPtr;

    // initalize op code data pointer in case of return error
    *opCodeDataHead = NULL;

    // initalize end state message
    // functionL copySTring
    copyString(endStateMsg,"MetaData file upload successfull");

    // open file for reading
    // function: fopen
    fileAccessPtr = fopen(filename, READ_ONLY_FLAG);

    // check for file open failure
    if(fileAccessPtr == NULL){

        // set end state message
        // function: copyString
        copyString(endStateMsg,"Metadata file access error");

        // return file access error
        return False;
    }

    // check first line for correct leader
    // function: getLineTo, compareString
    if(getLineTo(fileAccessPtr,MAX_STR_LEN,COLON,databuffer,ignoreLeadingWhiteSpace, stopAtNonPrintable) != NO_ERR || compareString(dataBuffer, "Start Program Meta-Data Code") != STR_EQ){

        // close file
        // function: fclose
        fclose(fileAccessPtr);

        // set end state message
        // function: copyString
        copyString(endStateMsg, "Corrupt metadata leader line error");

        // return corrupt descriptor error
        return False;
    }

    // allocate memort for the temporary data structure
    // function: malloc
    newNodePtr = (OpCodeType *) malloc(sizeof(OpCodeType));

    // get the fist op command
    // function: getOpCommand
    accessResult = getOpCommand(fileAccessPtr, newNodePtr);

    // get start and end counts for later comparison
    // function: updateStartCount, updateEndCount
    startCount = updateStartCount(startCount,newNodePtr->strArg1);
    endCount = updateEndCount(endCount, newNodePtr->strArg1);

    // check for failure of first op command
    if(accessResult != COMPLETE_OPCMD_FOUND_MSG){
        printf("Theres a failure in the first op command\n");
        // close file
        // function fclose
        fclose(fileAccessPtr);

        // clear data from the structure list
        // functionL clearMetaDataList
        *opCodeDataHead = clearMetaDataList(localHeadPtr);

        // free temporary structure memory
        // function: free
        free(newNodePtr);

        // set end state message
        // function: copyString
        copyString(endStateMsg, "Metadata incomplete first op command found");

        // return result of operation
        return False;
    }

    // loop across all remaining op commands
    // wile complete op commands are found
    while(accessResult == COMPLETE_OPCMD_FOUND_MSG){

        // add the new op command to the linked list
        // function: addNode
        localHeadPtr = addNode(localHeadPtr, newNodePtr);

        // get a new op code command
        // function: getOpCommand
        accessResult = getOpCommand(fileAccessPtr, newNodePtr);

        // update start and end counts for later comparison
        // functionL updateStartCount, updateEndCount
        startCount = updateStartCount(startCount, newNodePtr->strArg1);
        endCount = updateEndCount(endCount,newNodePtr->strArg1);
    }

    // end loop across remaining op commands

    // after loop completion, check for last op command found
    if(accessResult == LAST_OPCMD_FOUND_MSG){

        // check for start and end op code counts equal
        if(startCount == endCount){

            // add the last node to the linked list
            //function: addNode
            localheadPtr = addNode(localheadPtr, newNodePtr);

            // set access result to no error for later operation
            accessResult = NO_ERR;

            // check last line for incorrect end descriptor
            // functionL getLineTo, compareString
            if(getLineTo(fileAccessPtr,MAX_STR_LEN,PERIOD,dataBuffer,ignroeLeadingWhiteSpace, stopAtNonPrintable) != NO_ERR || compareString(dataBuffer, "End Program Meta-Data Code") != STR_EQ){

                // set access result to corrupteed descriptor error
                accessResult = MD_CORRUPT_DESCRIPTOR_ERR;
                
                // set end state message
                // function: copyString
                copyString(endStateMsg, "Metadata corrupted descriptor error");
            }
        }
    } // otherwise assume didn't find end
    else{

        // set end state message
        // function: copyString
        copyString(endStateMsg,"Corrupted metadata op code");
        
        // unset return state
        returnState = False;
    }

    // check for any errors found (not no error)
    if(accessResult != NO_ERR){
        // clear the op command list
        // function: clearMetaDataList
        localHeadPtr = clearMetaDataList(localHeadPtr);
    }

    // close access file
    // function: fclose
    fclose(fileAccessPtr);

    // release temporary structure memory
    // function: free
    free(newNodePtr);

    // assign temporary local head pointer to parameter return pointer
    *opCodeDataHead = localHeadPtr;

    // return access result
    return returnState;
}

/*
Function Name: getOpCommand
Algorithm: acquires one op command, verifies all parts of it, returns as parameter
Precondition: file is open and file cursor is at beginning of an op code
Postconditon: in correct operation,
                find, tests, and returns op command as parameter,
                and return status as integer
                - either complete op command found,
                or last op command found
Exceptions: correctly and apporoptiately (without program failure)
            responds to and reports file access failure,
            incorrectly formatted op command letter,
            incorrectly formatted op command name,
            incorrect or out range op command value
Notes: none
*/

int getOpCommand(File *filePtr, OpCodeType *inData){

    // initialize function/ variables
    // initalize local constans
    const int MAX_CMD_LENGTH = 5;
    const int MAX_ARG_STR_LENGTH = 15;

    // initalize other variables
    int accessResult, numBuffer = 0;
    char strBuffer[STD_STR_LEN];
    char cmdBuffer[MAX_CMD_LENGTH];
    char argStrBuffer[MAX_ARG_STR_LENGTH];
    int runningStringIndex = 0;
    Boolean stopAtNonPrintable = True;
    Boolean arg2FailureFlag = False;
    Boolean arg3FailureFlag = False;

    // get whole op command as a string
    // fucntion: getLineTo
    accessResult = getLineTo(filePtr, STD_STR_LEN, SEMICOLON, strBuffer, IGNORE_LEADING_WS, stopAtNonPrintable);

    // check for successful access
    if(accessResult == NO_ERR){

        // get three-letter command
        // function: getCommand
        runningStringIndex = getCommand(cmdBuffer,strBuffer,runningStringIndex);

        // assign op command to node
        // function: copyString
        copyString(inData->command, cmdBuffer);
    } // otherwise, assume unsuccessful access
    else{

        // set pointer to data structure to null
        inData = NULL;

        // return op command access failure
        return OPCMD_ACCESS_ERR;
    }

    // verify op command
    // functionL verifyValidCommand
    if(verifyValidCommand(cmdBuffer) == False){

        // return op command error
        return CORRUPT_OPCMD_ERR;
    }


    // set all struct values that may not be initialized to defaults
    intData->pid = 0;
    inData->inOutArg[0] = NULL_CHAR;
}