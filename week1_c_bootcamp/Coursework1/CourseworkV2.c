#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define an appropriate struct
typedef struct DataRecords{
	char *date;
	char *time;
	int steps;
} FITNESS_DATA;

// Define any additional variables here



// This is your helper function. Do not change it in any way.
// Inputs: character array representing a row; the delimiter character
// Ouputs: date character array; time character array; steps character array
void tokeniseRecord(const char *input, const char *delimiter,
                    char *date, char *time, char *steps) {
    // Create a copy of the input string as strtok modifies the string
    char *inputCopy = strdup(input);
    
    // Tokenize the copied string
    char *token = strtok(inputCopy, delimiter);
    if (token != NULL) {        strcpy(date, token);
    }
    
    token = strtok(NULL, delimiter);
    if (token != NULL) {
        strcpy(time, token);
    }
    
    token = strtok(NULL, delimiter);
    if (token != NULL) {
        strcpy(steps, token);
    }
    
    // Free the duplicated string
    free(inputCopy);

}

// Complete the main function
int main() {

    // open the file
    FILE *myFile = fopen("FitnessData_2023.csv","r");
    
    // exception handling
    if (myFile == NULL){
        printf("Error reaching the file. ");
        exit(1);
    }

    char thisDate[11];
    char thisTime[6];
    char thisSteps[10];
    int recordCount=0;

    char thisLine[200];
       while (fgets(thisLine, sizeof(thisLine), myFile)) {
        recordCount++;
    }

    fseek(myFile, 0, SEEK_SET);

    FITNESS_DATA *dataArray = (FITNESS_DATA *)malloc(recordCount * sizeof(FITNESS_DATA));

    for (int i = 0; i < recordCount; i++) {
        dataArray[i].date = malloc(11); // Allocate memory for date
        dataArray[i].time = malloc(6);  // Allocate memory for time
    }

    // Read the file and populate the dataArray
    for (int i = 0; i < recordCount; i++) {
        fgets(thisLine, sizeof(thisLine), myFile);
        tokeniseRecord(thisLine, ",", thisDate, thisTime, thisSteps);

        int mySteps = atoi(thisSteps);

        strcpy(dataArray[i].date, thisDate);
        strcpy(dataArray[i].time, thisTime);
        dataArray[i].steps = mySteps;

    }
    fclose(myFile);
    printf("Number of records in file: %d\n", recordCount);
    for (int i = 0; i < 3 && i < recordCount; i++) {
        printf("%s/%s/%d\n", dataArray[i].date, dataArray[i].time, dataArray[i].steps);
    }

    for (int i = 0; i < recordCount; i++) {
    free(dataArray[i].date);
    free(dataArray[i].time);
    }

    // Free the dataArray itself
    free(dataArray);
    return 0;
    }
    