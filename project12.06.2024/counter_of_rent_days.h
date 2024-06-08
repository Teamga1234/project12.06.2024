#pragma once
#include "structs_of_info_disk.h"
// Функція для перевірки, чи є рік високосним
bool isLeapYear(int year) {
    if (year % 4 == 0) {
        if (year % 100 == 0) {
            return year % 400 == 0;
        }
        return true;
    }
    return false;
}

// Функція для отримання кількості днів у місяці
int getDaysInMonth(int month, int year) {
    switch (month) {
    case 1: return 31;
    case 2: return isLeapYear(year) ? 29 : 28;
    case 3: return 31;
    case 4: return 30;
    case 5: return 31;
    case 6: return 30;
    case 7: return 31;
    case 8: return 31;
    case 9: return 30;
    case 10: return 31;
    case 11: return 30;
    case 12: return 31;
    default: return 0;
    }
}


int daysBetweenDates(const Date& date_from, const Date& date_to) {
    int days = 0;


    Date start = date_from;
    Date end = date_to;


    while (start.year < end.year ||
        (start.year == end.year && start.month < end.month) ||
        (start.year == end.year && start.month == end.month && start.day < end.day)) {


        start.day++;
        if (start.day > getDaysInMonth(start.month, start.year)) {
            start.day = 1;
            start.month++;
            if (start.month > 12) {
                start.month = 1;
                start.year++;
            }
        }

        days++;
    }

    return days;
}