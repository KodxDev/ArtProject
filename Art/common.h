#ifndef COMMON_H
#define COMMON_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <limits>

using namespace std;

// Структура для зберігання даних учасника арт-простору
struct Participant {
    int id;
    string surname;      // Прізвище
    string name;         // Ім'я
    string patronymic;   // По батькові
    string phone;        // Телефон
    string email;        // Email
    string participationType; // Тип участі (миттєць, відвідувач, організатор, волонтер тощо)
    string creativeDirection; // Напрям творчості
    string registrationDate;  // Дата реєстрації (у форматі DD.MM.YYYY)
};

// Глобальний вектор для зберігання всіх учасників
extern vector<Participant> participants;

// Константи
const string DATA_FILE = "participants.txt";

// Прототипи функцій
void displayMenu();
void addParticipant();
void viewAllParticipants();
void searchParticipant();
void editParticipant();
void deleteParticipant();
void saveToFile();
void loadFromFile();
void generateReport();
int getNextId();
void clearInputBuffer();
string getCurrentDate();

#endif // COMMON_H#pragma once
