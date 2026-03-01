// Purpose: Read the header values indicating the number of students and tests. Dynamically allocate an array of student structs. Dynamically allocate an array of test scores inside each struct. Store student name, ID, test scores, average, and letter grade.
// Calculate average test scores. Assign letter grades using the provided grading scale and deallocate memory in the correct order.

// Author: Jonathan Lopez



// HEADER FILES
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

// Student Struct

struct Student {

public:

	string name;
	int studentID;
	double *pTestScores;
	double averageScore;
	char letterGrade;

};

// PROTOTYPES
void readData(ifstream& inFile, Student* students, int numStudents, int numTests);
void calculateAverages(Student *students, int numStudents, int numTests);
void assignLetterGrades(Student *students, int numStudents);
void printReport(Student *students, int numStudents);


int main(){

	int numStudents;
	int numTests;

	ifstream inFile("student_data.txt");
	inFile >> numStudents >> numTests;

	Student* students = new Student[numStudents];


	// CALL FUNCTIONS
	readData(inFile, students, numStudents, numTests);
	calculateAverages(students, numStudents, numTests);
	assignLetterGrades(students, numStudents);
	printReport(students, numStudents);

	for (int i = 0; i < numStudents; i++) // de-allocate from memory.
		delete[] students[i].pTestScores;

	delete[] students;

	inFile.close();

}

void readData(ifstream &inFile, Student *students, int numStudents, int numTests) { // Purpose: to get data from student_data.txt

	for (int i = 0; i < numStudents; i++) { // Collect student names and ID #.
		students[i].pTestScores = new double[numTests];
		inFile >> students[i].name;
		inFile >> students[i].studentID;

		for (int j = 0; j < numTests; j++) { // nested loop. Now collect student's test scores.
			inFile >> students[i].pTestScores[j];
		}
	}

}

void calculateAverages(Student* students, int numStudents, int numTests) { // calculate averages of each student's grades.

	double sumOfTests = 0;

	for (int i = 0; i < numStudents; i++) { // for each student, get the tests -v

		double sumOfTests = 0;

		for (int j = 0; j < numTests; j++) { // iterate through the test scores.
			sumOfTests += students[i].pTestScores[j];

			students[i].averageScore = sumOfTests / numTests; // get average here.
		}
	}
}

void assignLetterGrades(Student* students, int numStudents) { // extract grades, assign them to a letter grade for each student.

	for (int i = 0; i < numStudents; i++) {

		if (students[i].averageScore >= 90) {
			students[i].letterGrade = 'A';
		}
		else if (students[i].averageScore >= 80) {
			students[i].letterGrade = 'B';
		}
		else if (students[i].averageScore >= 70) {
			students[i].letterGrade = 'C';
		}
		else if (students[i].averageScore >= 60) {
			students[i].letterGrade = 'D';
		}
		else {
			students[i].letterGrade = 'F';
		}
	}
}

void printReport(Student* students, int numStudents) { // print final and complete report.

	for (int i = 0; i < numStudents; i++) {

		cout << "Student: " << students[i].name << endl;
		cout << "ID : " << students[i].studentID << endl;
		cout << "Grade: " << students[i].letterGrade << endl << "--------------" << endl;
	}

}