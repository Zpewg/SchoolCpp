//
// Created by Andrei on 12/12/2024.
//
#pragma once
#ifndef STUDENT_H
#define STUDENT_H
#include "Date.h"
#include "Person.h"
using namespace std;


enum Status {
	ENROLLED,
	GRADUATED,
	DROPPED_OUT
};
string statusToString(Status status) {
	switch (status) {
		case Status::ENROLLED: return "Enrolled";
		case Status::GRADUATED: return "Graduated";
		case Status::DROPPED_OUT: return "Dropped Out";
		default: return "Unknown";
	}
}
class Student : public Person {
private:
	int studentId;
	unordered_map<string, vector<int>> grades;
	Status status;

public:
	// Constructor
	Student(const char* givenName, const char* familyName, const Date& dob, int studentId, const unordered_map<string, vector<int>>& grades, Status status = Status::ENROLLED)
		: Person(givenName, familyName, dob), studentId(studentId), grades(grades), status(status) {}

	// Getter for studentId
	int getStudentId() const {
		return studentId;
	}

	// Getter for status
	Status getStatus() const {
		return status;
	}

	// Getter for grades (no need for duplicate definition)
	const unordered_map<string, vector<int>>& getGrades() const {
		return grades;
	}

	// Method to add grade for a subject
	void addGrade(const string& subject, int grade) {
		grades[subject].push_back(grade);
	}

	bool removeGrade(const string& subject, size_t index) {
		// Check if the subject exists in the map
		if (grades.find(subject) != grades.end()) {
			// Check if the index is valid for the given subject
			if (index < grades[subject].size()) {
				grades[subject].erase(grades[subject].begin() + index);
				return true;  // Successfully removed the grade
			}
		}
		return false;  // Failed to remove grade (invalid subject or index)
	}

	// Overloaded << operator for printing student details
	friend ostream& operator<<(ostream& os, const Student& student) {
		os << "Name: " << student.getGivenName() << ", Family Name: " << student.getFamilyName()
			<< ", Id: " << student.getStudentId() << ", Grades: ";

		bool first = true;
		for (const auto& subjectPair : student.getGrades()) {
			if (!first) {
				os << ", "; // Add comma between subjects
			}
			os << subjectPair.first << ": "; // Print subject
			for (size_t i = 0; i < subjectPair.second.size(); ++i) {
				os << subjectPair.second[i];
				if (i < subjectPair.second.size() - 1) {
					os << ", "; // Add comma between grades for the same subject
				}
			}
			first = false;
		}

		os << ", Status: " << statusToString(student.getStatus()) << ", Date of birth: ";
		student.dateOfBirth.print();  // Assuming print() is a method in Date class

		return os;
	}
};



#endif //STUDENT_H
