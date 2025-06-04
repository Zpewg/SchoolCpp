//
// Created by Andrei on 12/12/2024.
//
#pragma once
#include "Teacher.h"
#include "Student.h"
#include "Date.h"
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
#ifndef FILEMANAGER_H
#define FILEMANAGER_H
using namespace std;


string trim(const string& str) {
	size_t start = str.find_first_not_of(" ");
	size_t end = str.find_last_not_of(" ");
	return (start == string::npos) ? "" : str.substr(start, end - start + 1);
}



class FileManager {
public:
	Status parseStatus(const string& statusStr) {
		string trimmedStatus = trim(statusStr);  // Trim leading and trailing spaces
		if (trimmedStatus == "ENROLLED") return Status::ENROLLED;
		if (trimmedStatus == "GRADUATED") return Status::GRADUATED;
		if (trimmedStatus == "DROPPED_OUT") return Status::DROPPED_OUT;
		throw invalid_argument("Invalid status: " + trimmedStatus);
	}
	// Utility function to convert a string to lowercase
	string toLower(const string& str) {
		string lowerStr = str;
		transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
		return lowerStr;
	}
	string trim(const string& str) {
		size_t first = str.find_first_not_of(" \t");
		size_t last = str.find_last_not_of(" \t");
		return (first == string::npos || last == string::npos) ? "" : str.substr(first, last - first + 1);
	}
	Subjects parseSubject(const string& statusTeacherStr) {
		string trimmedStatus = trim(statusTeacherStr);
		string lowerStatus = toLower(trimmedStatus);

		if (lowerStatus == "math") {
			return Subjects::MATH;
		}
		else if (lowerStatus == "computer_science") {
			return Subjects::COMPUTER_SCIENCE;
		}
		else if (lowerStatus == "english") {
			return Subjects::ENGLISH;
		}
		else {
			throw invalid_argument("Invalid subject found: " + statusTeacherStr);
		}
	}
	vector<Student> readStudentsFromFile(const string& fileName) {
		vector<Student> studenti;
		ifstream file(fileName);

		if (!file.is_open()) {
			cerr << "Could not open the file!" << endl;
			throw runtime_error("File could not be opened");
		}

		string line;
		while (getline(file, line)) {
			istringstream iss(line);
			string givenNameStr, familyNameStr, statusStr, subject;
			int studentId;
			unordered_map<string, vector<int>> grades;

			string dateStr;
			int day, month, year;

			// Read givenName, familyName, studentId, and dateStr
			if (!(iss >> givenNameStr >> familyNameStr >> studentId >> dateStr)) {
				cerr << "Error reading student information!" << endl;
				continue;
			}

			if (sscanf(dateStr.c_str(), "%d/%d/%d", &day, &month, &year) != 3) {
				cerr << "Error parsing date: " << dateStr << endl;
				continue;
			}

			Date dob(day, month, year);

			// First, read the status
			if (!(iss >> statusStr)) {
				cerr << "Error reading status!" << endl;
				continue;
			}

			// Convert status string to enum
			statusStr = trim(statusStr);  // Remove leading/trailing spaces
			Status status = Status::ENROLLED;  // Default value
			try {
				status = parseStatus(statusStr);  // Parse the status
			}
			catch (const invalid_argument& e) {
				cerr << e.what() << endl;
				continue;  // Skip this entry if status is invalid
			}

			// Read subjects and grades (subject may have multiple grades)
			while (iss >> subject) {
				if (isalpha(subject[0])) {  // If it's a subject
					vector<int> assignedGrades;
					int grade;
					while (iss >> grade) {
						assignedGrades.push_back(grade);
					}
					grades[subject] = assignedGrades;
					iss.clear();  // Clear the stream to read again
				}
			}

			// Allocate memory for char* (no std::string here)
			char* givenName = new char[givenNameStr.size() + 1];
			char* familyName = new char[familyNameStr.size() + 1];

			strcpy(givenName, givenNameStr.c_str());
			strcpy(familyName, familyNameStr.c_str());

			// Create the Student object
			studenti.emplace_back(givenName, familyName, dob, studentId, grades, status);

			// Cleanup memory for char* fields
			delete[] givenName;
			delete[] familyName;
		}

		file.close();

		if (studenti.empty()) {
			throw runtime_error("No valid students found in the file");
		}

		return studenti;
	}
	vector<Teacher> readTeachersFromFile(const string& fileName) {
		vector<Teacher> teachers;
		ifstream file(fileName);

		if (!file.is_open()) {
			cerr << "Could not open the file!" << endl;
			throw runtime_error("File could not be opened");
		}

		string line;
		while (getline(file, line)) {
			istringstream iss(line);
			string givenNameStr, familyNameStr, subjectStr;
			int teacherId, studentId;
			string studentName;
			int day, month, year;
			unordered_map<int, unordered_map<int, string>> studentsAssigned;
			string dateStr;



			if (!(iss >> givenNameStr >> familyNameStr >> dateStr)) {
				cerr << "Error reading teacher information!" << endl;
				continue;  // Skip this line if data is invalid
			}

			// Try to parse the date
			int result = sscanf(dateStr.c_str(), "%d/%d/%d", &day, &month, &year);
			if (result != 3) {
				cerr << "Error parsing date: " << dateStr << endl;
				continue;  // Skip this line if the date is invalid
			}
			// Create the Date object with parsed values
			Date dob(day, month, year);

			if (!(iss >> subjectStr >> dateStr)) {
				cerr << "Error reading hiring date!" << endl;
				continue;
			}

			// Parse the subject
			Subjects sbjStr;
			if (subjectStr == "MATH" || subjectStr == "COMPUTER_SCIENCE" || subjectStr == "ENGLISH") {
				try {
					sbjStr = parseSubject(subjectStr);
				}
				catch (const invalid_argument& e) {
					cerr << e.what() << endl;
					continue;
				}
			}

			result = sscanf(dateStr.c_str(), "%d/%d/%d", &day, &month, &year);
			if (result != 3) {
				cerr << "Error parsing date: " << dateStr << endl;
				continue;
			}
			Date doh(day, month, year);

			while (iss >> teacherId) {
				// Read each student's ID and name
				while (iss >> studentId >> studentName) {
					// Trim leading spaces from studentName
					size_t startPos = studentName.find_first_not_of(" ");
					if (startPos != string::npos) {
						studentName = studentName.substr(startPos); // Remove leading spaces
					}

					// Insert the data into the nested unordered_map
					studentsAssigned[teacherId][studentId] = studentName;

				}
			}




			// Now create the Teacher object
			char* givenName = new char[givenNameStr.size() + 1];
			char* familyName = new char[familyNameStr.size() + 1];
			strncpy(givenName, givenNameStr.c_str(), givenNameStr.size() + 1);
			strncpy(familyName, familyNameStr.c_str(), familyNameStr.size() + 1);

			teachers.emplace_back(givenName, familyName, dob, sbjStr, doh, studentsAssigned);

			delete[] givenName;
			delete[] familyName;
		}


		file.close();

		if (teachers.empty()) {
			throw runtime_error("No valid teachers found in the file");
		}

		return teachers;
	}

};



#endif //FILEMANAGER_H
