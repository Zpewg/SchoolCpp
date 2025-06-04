#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <ctime>
#include <unordered_map>
#include <thread>
#include<mutex>
#include "Date.h"
#include "Person.h"
#include "Teacher.h"
#include "Student.h"
#include "Principal.h"
#include "DataProcessing.h"
#include "FileManager.h"
#pragma warning(disable:4996)

using namespace std;



int main() {
	try {
		FileManager fileManager;
		DataProcessing dataProcessing;
		Teacher teacher;
		vector<Student> studenti = fileManager.readStudentsFromFile("C:/Users/Andrei/CLionProjects/untitled/studentInformation.txt");
		vector<Teacher> teachers = fileManager.readTeachersFromFile("C:/Users/Andrei/CLionProjects/untitled/teachers.txt");

		Principal* principal = Principal::GetInstance("Alice", "Johnson", Date(1975, 12, 30), studenti, teachers);
		principal->SomeBusinessLogic();
		cout << "Students: " << endl;

			dataProcessing.printSpecialStudents(studenti);
			dataProcessing.printYearsOld(studenti);
			dataProcessing.gradesManagement(studenti);
			dataProcessing.printAverage(studenti);
			dataProcessing.experience(teachers);
			teacher.modifyingStudents(teachers, studenti);

			cout << "Modified list: ";
			for (const auto& teacher : teachers) {
				cout << teacher << endl;
			}

			principal->printStudentCountPerTeacher(teachers);
		dataProcessing.displaySchoolOverview(teachers, studenti);
	}
	catch (const exception& e) {
		cerr << "Error: " << e.what() << endl;
	}

	return 0;
}
