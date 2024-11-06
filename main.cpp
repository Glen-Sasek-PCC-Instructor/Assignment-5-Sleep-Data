//*******************************************************************************
// Author: Jonathan Reiniger
// Assignment: Assignment 5
// Date:  11/1/24
// Description: This program reads from Sleep_and_lifestyle.csv and prints the
// lifestyle of each person. Sleep_and_lifestyle.csv has 4 columns of data which are:
// PersonID, Age, Occupation, Sleep Duration. This program uses the concept of parallel
// arrays. The program will read the data into a char array and an int array. It will
// output the sleep duration for each person and will list the person with the highest
// sleep duration.
// Input: Sleep_and_lifestyle.csv
// Output: maxSleep & personID as floats
// Sources: Assignment 5 sample

#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include <cerrno> // For perror

using namespace std;

// Constants
const char DATAFILE[] = "sleep-data.csv"; 
const int MAX_PERSONS = 400;
const int MAXCHAR = 50;
const int NUMBER_OF_FIELDS = 4;
char field_labels[NUMBER_OF_FIELDS][MAXCHAR] = {0};
const char FIELD_SEPARATOR = ',';

// Function prototypes
bool openFile(ifstream &inFile);
int loadData(ifstream &inFile, int personIDs[], int ages[], char occupations[][MAXCHAR], float sleepDurations[]);
void calcHours(int personIDs[], float sleepDurations[], int count);

void printRow(int personID, int age, char occupation[], float sleepDuration);

void printRows(int personIDs[], int ages[], char occupations[][MAXCHAR], float sleepDurations[], int count);

// Main function
int main() {
    ifstream inFile;
    int count = 0;
    int personIDs[MAX_PERSONS];
    int ages[MAX_PERSONS];
    char occupations[MAX_PERSONS][MAXCHAR];
    float sleepDurations[MAX_PERSONS];

    // cout << "Please ensure Sleep_and_lifestyle.csv is in the same directory as this program." << endl;
    
    if (!openFile(inFile)) {
        cout << "File did not open! Program terminating!!" << endl;
        return 1;
    }

    count = loadData(inFile, personIDs, ages, occupations, sleepDurations);

    printRows(personIDs, ages, occupations, sleepDurations, count);

    inFile.close();
    
    calcHours(personIDs, sleepDurations, count);
    cout << "Thank you!" << endl;
    return 0;
}

bool openFile(ifstream &inFile) {
    // Attempting to open the file
    cout << "Attempting to open: " << DATAFILE << endl; // Debug output
    inFile.open(DATAFILE); // Adjust this path if necessary
    if (!inFile.is_open()) {
        cout << "Failed to open file." << endl; // Additional debug output
        perror("Error"); // Print error details
    }
    return inFile.is_open();
}

int loadData(ifstream &inFile, int personIDs[], int ages[], char occupations[][MAXCHAR], float sleepDurations[]) {
    int count = 0;
    
    for(int i = 0; i < NUMBER_OF_FIELDS - 1; i++) {
        inFile.getline(field_labels[i], MAXCHAR, ',');
    }

    inFile.getline(field_labels[NUMBER_OF_FIELDS - 1], MAXCHAR, '\n');

    bool has_next = true;
    
    do {
        inFile >> personIDs[count];
        if(inFile) {
            inFile.get();

            inFile >> ages[count];
            inFile.get();

            inFile.getline(occupations[count], MAXCHAR, ',');

            inFile >> sleepDurations[count];
            inFile.get();

            count++;
        } else {
            has_next = false;
        }
    } while(has_next);
    

    // while (count < MAX_PERSONS &&
    //        inFile >> personIDs[count] >> ages[count] >> occupations[count] >> sleepDurations[count]) {
    //     count++;
    // }
    return count; // Return the number of records loaded
}

void printRow(int personID, int age, char occupation[], float sleepDuration) {
    cout << fixed << setprecision(1);
    cout << right << setw(9) << personID;
    cout << right << setw(5) << age;
    cout << "  ";
    cout << left << setw(20) << occupation;
    cout << right << setw(16) << sleepDuration;
    cout << endl;
}

void printRows(int personIDs[], int ages[], char occupations[][MAXCHAR], float sleepDurations[], int count) {
    cout << right << setw(9) << field_labels[0];
    cout << right << setw(5) << field_labels[1];
    cout << "  ";
    cout << left << setw(20) << field_labels[2];
    cout << right << setw(16) << field_labels[3];
    cout << endl;

    for(int i = 0; i < count; i++) {
        printRow(personIDs[i], ages[i], occupations[i], sleepDurations[i]);
    }
}

void calcHours(int personIDs[], float sleepDurations[], int count) {
    float maxSleep = 0;
    int maxPersons[MAX_PERSONS];
    int maxCount = 0;

    for (int i = 0; i < count; i++) {
        cout << "Person ID: " << personIDs[i] << ", Sleep Duration: " << sleepDurations[i] << endl;

        if (sleepDurations[i] > maxSleep) {
            maxSleep = sleepDurations[i];
            maxCount = 0; // Reset for new maximum
            maxPersons[maxCount++] = personIDs[i]; // Store the new max personID
        } else if (sleepDurations[i] == maxSleep) {
            maxPersons[maxCount++] = personIDs[i]; // Add to maxPersons
        }
    }

    // Display the personIDs with maximum sleep
    cout << "PersonID's with maximum hours of sleep: ";
    for (int i = 0; i < maxCount; i++) {
        cout << maxPersons[i] << " ";
    }
    cout << "have the maximum hours of sleep: " << maxSleep << "!" << endl;
}
