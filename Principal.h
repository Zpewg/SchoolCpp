//
// Created by Andrei on 12/12/2024.
//
#pragma once
#include"Person.h"
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
#include "Student.h"
#include "Date.h"
#include "Teacher.h"
#ifndef PRINCIPAL_H
#define PRINCIPAL_H



class Principal : public Person {
private:
	static Principal* pinstance_;
	static mutex mutex_;
protected:
	vector<Student> studenti;
	vector<Teacher> teachers;
	Principal(const char* givenName, const char* familyName, const Date& dob,
		const vector<Student>& studenti, const vector<Teacher>& teachers)
		: Person(givenName, familyName, dob), studenti(studenti), teachers(teachers) {}
	~Principal() {}
public:
	Principal(Principal& other) = delete;
	void operator=(const Principal&) = delete;
	static Principal* GetInstance(const char* givenName, const char* familyName, const Date& dob,
		const vector<Student>& studenti, const vector<Teacher>& teachers);
	void SomeBusinessLogic() {
		// Print Principal details
		std::cout << "Principal Details:" << std::endl;
		std::cout << "Name: " << getGivenName() << " " << getFamilyName() << std::endl;
		std::cout << "Date of Birth: ";
		dateOfBirth.print();  // Assuming `dateOfBirth` has a `print` method

		// Print list of students
		std::cout << "\nList of Students:" << std::endl;
		for (const auto& student : studenti) {
			std::cout << student << std::endl;  // Assuming Student has an overloaded `<<` operator
		}

		// Print list of teachers
		std::cout << "\nList of Teachers:" << std::endl;
		for (const auto& teacher : teachers) {
			std::cout << teacher << std::endl;  // Assuming Teacher has an overloaded `<<` operator
		}
	}
	void printStudentCountPerTeacher(const vector<Teacher>& teachers) {
		std::cout << "\nNumber of Students Assigned to Each Teacher:" << std::endl;

		for (const auto& teacher : teachers) {
			// Use the getter to access the students map
			const auto& students = teacher.getStudents();

			// Count the number of students for each teacher
			int studentCount = 0;
			for (const auto& outerPair : students) {
				studentCount += outerPair.second.size();  // Count the number of students in the inner map
			}

			std::cout << teacher.getGivenName() << " " << teacher.getFamilyName()
				<< " has " << studentCount << " students." << std::endl;
		}
	}


	const vector<Student>& getStudents() const {
		return studenti;
	}

	const vector<Teacher>& getTeachers() const {
		return teachers;
	}
	const char* getGivenName() const {
		return givenName;
	}

	const char* getFamilyName() const {
		return familyName;
	}

	const Date& getDateOfBirth() const {
		return dateOfBirth;
	}
};
Principal* Principal::pinstance_{ nullptr };
mutex Principal::mutex_;
Principal* Principal::GetInstance(const char* givenName, const char* familyName, const Date& dob,
	const vector<Student>& studenti, const vector<Teacher>& teachers) {
	std::lock_guard<std::mutex> lock(mutex_);
	if (pinstance_ == nullptr) {
		pinstance_ = new Principal(givenName, familyName, dob, studenti, teachers);
	}
	return pinstance_;
}



#endif //PRINCIPAL_H
