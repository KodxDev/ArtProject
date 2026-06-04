#include "common.h"

// Отримання наступного вільного ID
int getNextId() {
    if (participants.empty()) return 1;
    int maxId = 0;
    for (const auto& p : participants) {
        if (p.id > maxId) maxId = p.id;
    }
    return maxId + 1;
}

// Очищення буфера введення
void clearInputBuffer() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Отримання поточної дати у форматі DD.MM.YYYY (заглушка – можна розширити)
string getCurrentDate() {
    return "18.04.2026";  // Для демонстрації; у реальній програмі використовувати <chrono>
}

// Відображення головного меню
void displayMenu() {
    cout << "\n=== ПРОГРАМА ОБЛІКУ УЧАСНИКІВ АРТ-ПРОСТОРУ ===\n";
    cout << "1. Додати нового учасника\n";
    cout << "2. Переглянути всіх учасників\n";
    cout << "3. Пошук учасника\n";
    cout << "4. Редагувати дані учасника\n";
    cout << "5. Видалити учасника\n";
    cout << "6. Згенерувати звіт\n";
    cout << "7. Зберегти та вийти\n";
    cout << "0. Вийти без збереження (збереження все одно відбудеться)\n";
    cout << "===========================================\n";
}

// Додавання нового учасника
void addParticipant() {
    Participant p;
    p.id = getNextId();

    cout << "\n--- Додавання нового учасника (ID: " << p.id << ") ---\n";
    cout << "Прізвище: "; getline(cin, p.surname);
    cout << "Ім'я: "; getline(cin, p.name);
    cout << "По батькові: "; getline(cin, p.patronymic);
    cout << "Телефон: "; getline(cin, p.phone);
    cout << "Email: "; getline(cin, p.email);
    cout << "Тип участі (миттєць/відвідувач/організатор/волонтер): "; getline(cin, p.participationType);
    cout << "Напрям творчості: "; getline(cin, p.creativeDirection);
    p.registrationDate = getCurrentDate();

    participants.push_back(p);
    cout << "Учасник успішно доданий!\n";
    saveToFile();  // Автозбереження після додавання
}

// Перегляд всіх учасників
void viewAllParticipants() {
    if (participants.empty()) {
        cout << "\nСписок учасників порожній.\n";
        return;
    }

    cout << "\n=== СПИСОК УЧАСНИКІВ ===\n";
    cout << left << setw(5) << "ID"
        << setw(15) << "Прізвище"
        << setw(12) << "Ім'я"
        << setw(15) << "Телефон"
        << setw(25) << "Email"
        << setw(18) << "Тип участі" << endl;
    cout << string(90, '-') << endl;

    for (const auto& p : participants) {
        cout << left << setw(5) << p.id
            << setw(15) << p.surname
            << setw(12) << p.name
            << setw(15) << p.phone
            << setw(25) << p.email
            << setw(18) << p.participationType << endl;
    }
}

// Пошук учасника (за прізвищем або email)
void searchParticipant() {
    if (participants.empty()) {
        cout << "\nСписок учасників порожній.\n";
        return;
    }

    string keyword;
    cout << "\nВведіть прізвище або частину email для пошуку: ";
    getline(cin, keyword);

    bool found = false;
    cout << "\nРезультати пошуку:\n";
    for (const auto& p : participants) {
        if (p.surname.find(keyword) != string::npos ||
            p.email.find(keyword) != string::npos) {
            cout << "ID: " << p.id
                << " | " << p.surname << " " << p.name
                << " | Тел: " << p.phone
                << " | Email: " << p.email
                << " | Тип: " << p.participationType << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "Учасників за заданим критерієм не знайдено.\n";
    }
}

// Редагування учасника
void editParticipant() {
    if (participants.empty()) {
        cout << "\nСписок учасників порожній.\n";
        return;
    }

    int id;
    cout << "\nВведіть ID учасника для редагування: ";
    cin >> id;
    clearInputBuffer();

    for (auto& p : participants) {
        if (p.id == id) {
            cout << "\nРедагування учасника ID " << id << ":\n";
            cout << "Нове прізвище (поточне: " << p.surname << "): "; getline(cin, p.surname);
            cout << "Нове ім'я (поточне: " << p.name << "): "; getline(cin, p.name);
            cout << "По батькові (поточне: " << p.patronymic << "): "; getline(cin, p.patronymic);
            cout << "Телефон (поточний: " << p.phone << "): "; getline(cin, p.phone);
            cout << "Email (поточний: " << p.email << "): "; getline(cin, p.email);
            cout << "Тип участі (поточний: " << p.participationType << "): "; getline(cin, p.participationType);
            cout << "Напрям творчості (поточний: " << p.creativeDirection << "): "; getline(cin, p.creativeDirection);

            cout << "Дані успішно оновлено!\n";
            saveToFile();
            return;
        }
    }
    cout << "Учасника з ID " << id << " не знайдено.\n";
}

// Видалення учасника
void deleteParticipant() {
    if (participants.empty()) {
        cout << "\nСписок учасників порожній.\n";
        return;
    }

    int id;
    cout << "\nВведіть ID учасника для видалення: ";
    cin >> id;
    clearInputBuffer();

    for (auto it = participants.begin(); it != participants.end(); ++it) {
        if (it->id == id) {
            cout << "Ви впевнені, що хочете видалити учасника "
                << it->surname << " " << it->name << "? (y/n): ";
            char confirm;
            cin >> confirm;
            clearInputBuffer();

            if (confirm == 'y' || confirm == 'Y') {
                participants.erase(it);
                cout << "Учасник видалений!\n";
                saveToFile();
            }
            else {
                cout << "Видалення скасовано.\n";
            }
            return;
        }
    }
    cout << "Учасника з ID " << id << " не знайдено.\n";
}

// Збереження даних у файл (текстовий формат)
void saveToFile() {
    ofstream outFile(DATA_FILE);
    if (!outFile.is_open()) {
        cout << "Помилка відкриття файлу для запису!\n";
        return;
    }

    for (const auto& p : participants) {
        outFile << p.id << "|"
            << p.surname << "|"
            << p.name << "|"
            << p.patronymic << "|"
            << p.phone << "|"
            << p.email << "|"
            << p.participationType << "|"
            << p.creativeDirection << "|"
            << p.registrationDate << "\n";
    }
    outFile.close();
}

// Завантаження даних з файлу
void loadFromFile() {
    ifstream inFile(DATA_FILE);
    if (!inFile.is_open()) {
        cout << "Файл даних не знайдено. Створено новий порожній список.\n";
        return;
    }

    participants.clear();
    string line;
    while (getline(inFile, line)) {
        if (line.empty()) continue;
        Participant p;
        size_t pos = 0;
        size_t nextPos;

        nextPos = line.find('|', pos);
        p.id = stoi(line.substr(pos, nextPos - pos));
        pos = nextPos + 1;

        nextPos = line.find('|', pos);
        p.surname = line.substr(pos, nextPos - pos);
        pos = nextPos + 1;

        nextPos = line.find('|', pos);
        p.name = line.substr(pos, nextPos - pos);
        pos = nextPos + 1;

        nextPos = line.find('|', pos);
        p.patronymic = line.substr(pos, nextPos - pos);
        pos = nextPos + 1;

        nextPos = line.find('|', pos);
        p.phone = line.substr(pos, nextPos - pos);
        pos = nextPos + 1;

        nextPos = line.find('|', pos);
        p.email = line.substr(pos, nextPos - pos);
        pos = nextPos + 1;

        nextPos = line.find('|', pos);
        p.participationType = line.substr(pos, nextPos - pos);
        pos = nextPos + 1;

        nextPos = line.find('|', pos);
        p.creativeDirection = line.substr(pos, nextPos - pos);
        pos = nextPos + 1;

        p.registrationDate = line.substr(pos);

        participants.push_back(p);
    }
    inFile.close();
}

// Генерація простого звіту
void generateReport() {
    if (participants.empty()) {
        cout << "\nСписок учасників порожній. Звіт неможливо згенерувати.\n";
        return;
    }

    int total = participants.size();
    int artists = 0, visitors = 0, organizers = 0;

    for (const auto& p : participants) {
        if (p.participationType.find("миттєць") != string::npos ||
            p.participationType.find("художник") != string::npos) artists++;
        else if (p.participationType.find("відвідувач") != string::npos) visitors++;
        else if (p.participationType.find("організатор") != string::npos) organizers++;
    }

    cout << "\n=== ЗВІТ ПРО УЧАСНИКІВ АРТ-ПРОСТОРУ ===\n";
    cout << "Загальна кількість учасників: " << total << endl;
    cout << "Митців: " << artists << endl;
    cout << "Відвідувачів: " << visitors << endl;
    cout << "Організаторів: " << organizers << endl;
    cout << "Інших: " << (total - artists - visitors - organizers) << endl;
    cout << "Дата звіту: " << getCurrentDate() << endl;
}