//
// Created by Andrei on 12/12/2024.
//
#pragma once
#include<iostream>
#include "Teacher.h"
#include "Student.h"
#include "Date.h"
#ifndef DATAPROCESSING_H
#define DATAPROCESSING_H



class DataProcessing {
public:
	void experience(const vector<Teacher>& teachers) {
		time_t now2 = time(0);
		tm* ltm2 = localtime(&now2);
		int currentYear = 1900 + ltm2->tm_year;
		for (const auto& teacher : teachers) {
			int yearsOfExperience = currentYear - teacher.getYearOfHiring();
			if (yearsOfExperience < 6) {
				cout << "Teacher " << teacher.getGivenName() <<  "is Novice"
					<< " with: " << yearsOfExperience << " years of experience" << endl;
			}
			else if (yearsOfExperience < 16) {
				cout << "Teacher " << teacher.getGivenName() << " is Experienceds"
					<< " with: " << yearsOfExperience << " years of experience" << endl;
			}
			else {
				cout << "Teacher " << teacher.getGivenName() << " is Veteran"
					<< " with: " << yearsOfExperience << " years of experience" << endl;
			}
		}

	}
	void printSpecialStudents(vector<Student> studenti) {
		vector<Student> specialStudents = studenti;


		auto it = remove_if(specialStudents.begin(), specialStudents.end(), [](const Student& student) {
			return statusToString(student.getStatus()) == "Unknown";
			});

		// Erase the students with Unknown status from the vector
		specialStudents.erase(it, specialStudents.end());

		cout << "Special status students are: " << endl;
		for (const auto& student : specialStudents) {
			cout << student << endl;
		}
	}
	void printYearsOld(vector<Student> studenti) {
		time_t now = time(0);
		tm* ltm = localtime(&now);
		int currentMonth = ltm->tm_mon + 1;
		time_t now1 = time(0);
		tm* ltm1 = localtime(&now1);
		int currentDay = ltm1->tm_mday;
		time_t now2 = time(0);
		tm* ltm2 = localtime(&now2);
		int currentYear = 1900 + ltm2->tm_year;

		for (const auto& student : studenti) {
			int age = currentYear - student.getYearOfBirth();


			if (currentMonth < student.getMonthOfBirth() ||
				(currentMonth == student.getMonthOfBirth() && currentDay < student.getDayOfBirth())) {
				age--;
			}


			cout << student.getGivenName() << " is: " << age << " years old" << endl;
		}
	}

	void gradesManagement(vector<Student>& studenti) {
		while (true) {
			int studentId;
			cout << "Enter the student ID to manage grades (or 0 to exit): ";
			cin >> studentId;

			// Exit if user enters 0
			if (studentId == 0) {
				break;
			}

			// Find the student by ID
			auto it = find_if(studenti.begin(), studenti.end(),
				[studentId](const Student& student) { return student.getStudentId() == studentId; });

			if (it == studenti.end()) {
				cout << "Student not found!" << endl;
				continue;
			}

			// Prompt for action (add or remove grade)
			char action;
			cout << "Would you like to add or remove a grade? (a/r): ";
			cin >> action;

			string subject;
			int grade;

			if (action == 'a' || action == 'A') {
				// Add grade
				cout << "Enter the subject: ";
				cin >> subject;
				cout << "Enter the grade to add: ";
				cin >> grade;

				it->addGrade(subject, grade);  // Add grade to student
				cout << "Grade added successfully!" << endl;
			}
			else if (action == 'r' || action == 'R') {
				// Remove grade
				cout << "Enter the subject: ";
				cin >> subject;
				cout << "Enter the index of the grade to remove: ";
				int index;
				cin >> index;

				if (it->removeGrade(subject, index)) {
					cout << "Grade removed successfully!" << endl;
				}
				else {
					cout << "Invalid subject or index!" << endl;
				}
			}
			else {
				cout << "Invalid action!" << endl;
				continue;
			}

			// Show updated student information
			cout << "Updated student information: " << endl;
			cout << *it << endl;
		}
	}



	void printAverage(const vector<Student>& studenti) {
		for (const auto& student : studenti) {
			cout << "Student: " << student.getGivenName() << " " << student.getFamilyName() << ", ID: " << student.getStudentId() << endl;

			// Iterate over the grades for each subject
			for (const auto& subjectPair : student.getGrades()) {

				const string& subject = subjectPair.first;
				const vector<int>& grades = subjectPair.second;

				// Calculate the average for the subject
				if (!grades.empty()) {
					int sum = 0;
					for (int grade : grades) {
						sum += grade;
					}
					double average = static_cast<double>(sum) / grades.size();
					cout << "  Subject: " << subject << ", Average: " << average << endl;
				}
				else {
					cout << "  Subject: " << subject << ", No grades available" << endl;
				}
			}

			cout << endl;  // Print a blank line between students
		}
	}
	void displaySchoolOverview(vector<Teacher> teachers, vector<Student> students) {
		cout << "School Overview:" << endl;
		cout << "Number of Teachers: " << teachers.size() << endl;
		cout << "Number of Students: " << students.size() << endl;
	}

};



#endif //DATAPROCESSING_H
