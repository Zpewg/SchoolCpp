
#pragma once
#ifndef TEACHER_H
#define TEACHER_H
#include "Date.h"
#include "Student.h"
#include "Person.h"

enum Subjects {
	MATH,
	COMPUTER_SCIENCE,
	ENGLISH
};
string subjectToString(Subjects sbj) {
	switch (sbj) {
	case Subjects::MATH: return "Math";
	case Subjects::COMPUTER_SCIENCE: return "Computer_Science";
	case Subjects::ENGLISH: return "English";
	default:return"Unkown";
	}
}
class Teacher : public Person {
protected:
	Subjects sbj;
	Date dateOfHiring;
	unordered_map<int, unordered_map<int, string>> students;

public:
	Teacher(const char* givenName, const char* familyName, const Date& dob, Subjects sbj, Date dateOfHiring,
		unordered_map<int, unordered_map<int, string>> students)
		:Person(givenName, familyName, dob), sbj(sbj), dateOfHiring(dateOfHiring), students(students) {

	}
	Teacher() {

	}
	const unordered_map<int, unordered_map<int, string>>& getStudents() const {
		return students;
	}
	Teacher& operator=(const Teacher& other) {
		if (this != &other) {
			sbj = other.sbj;
			dateOfHiring = other.dateOfHiring;
			students = other.students;

		}
		return *this;
	}
	int getYearOfHiring() const {
		return dateOfHiring.getYear();
	}
	int getAssignedStudentCount(int teacherId) const {
		auto teacherIt = students.find(teacherId);
		if (teacherIt != students.end()) {
			return teacherIt->second.size();  // Return number of students
		}
		return 0;  // If no students assigned
	}
	friend ostream& operator<<(ostream& os, const Teacher& teacher) {
		// Print basic information
		os << "Name: " << teacher.getGivenName() << ", Family Name: " << teacher.getFamilyName()
			<< ", Subject: " << subjectToString(teacher.sbj)
			<< ", Date of Birth: " << teacher.dateOfBirth.getDay() << "/"
			<< teacher.dateOfBirth.getMonth() << "/" << teacher.dateOfBirth.getYear()
			<< ", Date of Hiring: " << teacher.dateOfHiring.getDay() << "/"
			<< teacher.dateOfHiring.getMonth() << "/" << teacher.dateOfHiring.getYear()
			<< ", Students: ";

		bool hasStudents = false; // Flag to check if there are any students
		// Iterate through the outer unordered_map (int -> unordered_map<int, string>)
		for (const auto& outerPair : teacher.students) {
			os << "\n  Student ID: " << outerPair.first << " => ";

			// Iterate through the inner unordered_map (int -> string)
			for (const auto& innerPair : outerPair.second) {
				os << "\n    Assignment ID: " << innerPair.first << ", Student: " << innerPair.second;
			}
			hasStudents = true;
		}

		if (!hasStudents) {
			os << "No students assigned."; // In case the students map is empty
		}

		return os;
	}
	void modifyingStudents(vector<Teacher>& teachers, vector<Student>& studentsList) {
		int choice;
		do {
			cout << "\nWhat would you like to do?\n";
			cout << "1. Assign a student to a teacher\n";
			cout << "2. Deassign a student from a teacher\n";
			cout << "3. Exit\n";
			cout << "Enter your choice: ";
			cin >> choice;

			switch (choice) {
			case 1: { // Assign a student to a teacher
				cout << "Which teacher gets a new student? Please insert their ID: ";
				int teacherId;
				cin >> teacherId;

				for (auto& teacher : teachers) { // Use non-const reference to modify
					if (teacher.students.find(teacherId) != teacher.students.end()) {
						cout << "Found Teacher ID: " << teacherId << endl;

						cout << "Who's the new student? Please provide their name and ID.\n";
						string studentName;
						int studentId;
						cout << "Name: ";
						cin.ignore();
						getline(cin, studentName);
						cout << "ID: ";
						cin >> studentId;

						// Validate studentId
						bool studentExists = false;
						for (const auto& student : studentsList) {
							if (student.getStudentId() == studentId) {
								studentExists = true;
								break;
							}
						}

						if (!studentExists) {
							cout << "Error: Student ID " << studentId << " does not exist in the student list.\n";
							break;
						}

						// Add the student
						teacher.students[teacherId][studentId] = studentName;
						cout << "Added Student ID: " << studentId << ", Name: " << studentName
							<< " to Teacher ID: " << teacherId << endl;
						break;
					}
				}
				break;
			}

			case 2: { // Deassign a student from a teacher
				cout << "Which teacher's student would you like to remove? Please insert their ID: ";
				int teacherId;
				cin >> teacherId;

				for (auto& teacher : teachers) { // Use non-const reference to modify
					if (teacher.students.find(teacherId) != teacher.students.end()) {
						cout << "Found Teacher ID: " << teacherId << endl;

						cout << "Which student would you like to remove? Please provide their ID: ";
						int studentId;
						cin >> studentId;

						auto& innerMap = teacher.students[teacherId];
						if (innerMap.find(studentId) != innerMap.end()) {
							innerMap.erase(studentId); // Remove the student
							cout << "Removed Student ID: " << studentId << " from Teacher ID: " << teacherId << endl;
						}
						else {
							cout << "Error: Student ID " << studentId << " is not assigned to Teacher ID " << teacherId << ".\n";
						}
						break;
					}
				}
				break;
			}

			case 3: // Exit
				cout << "Exiting...\n";
				break;

			default: // Invalid choice
				cout << "Invalid choice. Please try again.\n";
			}

		} while (choice != 3);


	}




};



#endif //TEACHER_H
