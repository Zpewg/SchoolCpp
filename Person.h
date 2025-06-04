#pragma once
#ifndef PERSON_H
#define PERSON_H
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <cstring>
#include "Date.h"
#include <algorithm>
#include <cctype>
#include <ctime>
#include <unordered_map>
#include <thread>
#include<mutex>
#pragma warning(disable:4996)
using namespace std;
class Person {
protected:
    char* givenName;
    char* familyName;
    Date dateOfBirth;
public:
    Person(const char* givenName, const char* familyName, Date dateOfBirth = Date(1, 1, 1900)) :
        dateOfBirth(dateOfBirth) {
        this->givenName = new char[strlen(givenName) + 1];
        strncpy(this->givenName, givenName, strlen(givenName) + 1);

        this->familyName = new char[strlen(familyName) + 1];
        strncpy(this->familyName, familyName, strlen(familyName) + 1);

    }
    virtual ~Person() {
        delete[] givenName;
        delete[] familyName;
    }
    Person(const Person& other)
        : Person(other.givenName, other.familyName, other.dateOfBirth) {}

    Person operator=(const Person& other) {
        if (this != &other) {
            delete[] givenName;
            delete[] familyName;
            givenName = new char[strlen(other.givenName) + 1];
            strcpy(givenName, other.givenName);

            familyName = new char[strlen(other.familyName) + 1];
            strcpy(familyName, other.familyName);

            dateOfBirth = other.dateOfBirth;
        }
        return *this;
    }
    Person() {
        givenName = new char[1];
        givenName[0] = '\0';

        familyName = new char[1];
        familyName[0] = '\0';
    }
    Date getDateOfBirth() const {
        return dateOfBirth;
    }

    int getYearOfBirth() const {
        return dateOfBirth.getYear();
    }
    int getMonthOfBirth()const {
        return dateOfBirth.getMonth();
    }
    int getDayOfBirth()const {
        return dateOfBirth.getDay();
    }
    const char* getGivenName() const {
        return givenName;
    }

    void setGivenName(const char* newName) {
        delete[] givenName;
        givenName = new char[strlen(newName) + 1];
        strncpy(givenName, newName, strlen(newName) + 1);
    }

    const char* getFamilyName() const {
        return familyName;
    }

    void setFamilyName(const char* newFamilyName) {
        delete[] familyName;
        familyName = new char[strlen(newFamilyName) + 1];
        strncpy(familyName, newFamilyName, strlen(newFamilyName) + 1);
    }


};

#endif //PERSON_H
