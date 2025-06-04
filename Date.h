//
// Created by Andrei on 12/12/2024.
//
#pragma once
#ifndef DATE_H
#define DATE_H
#include<iostream>
using namespace std;
class Date {
private:
    int day;
    int month;
    int year;
public:
    // Default constructor
    Date() : day(1), month(1), year(1900) {}

    // Constructor with parameters
    Date(int d, int m, int y) : day(d), month(m), year(y) {
    }

    void print() const {
        cout << day << "/" << month << "/" << year;
    }
    int getDay() const { return day; }
    int getMonth() const { return month; }
    int getYear() const { return year; }

    // Setter functions
    void setDay(int d) { day = d; }
    void setMonth(int m) { month = m; }
    void setYear(int y) { year = y; }
};
#endif //DATE_H
