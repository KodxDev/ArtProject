#include "common.h"

// Ініціалізація глобального вектора
vector<Participant> participants;

int main() {

    system("chcp 1251");

    loadFromFile();  // Завантаження даних при старті програми

    int choice;
    do {
        displayMenu();
        cout << "Введіть ваш вибір: ";
        cin >> choice;
        clearInputBuffer();

        switch (choice) {
        case 1:
            addParticipant();
            break;
        case 2:
            viewAllParticipants();
            break;
        case 3:
            searchParticipant();
            break;
        case 4:
            editParticipant();
            break;
        case 5:
            deleteParticipant();
            break;
        case 6:
            generateReport();
            break;
        case 7:
            saveToFile();
            cout << "Дані збережено. Програма завершує роботу.\n";
            break;
        case 0:
            saveToFile();  // Автозбереження при виході
            cout << "До побачення!\n";
            break;
        default:
            cout << "Невірний вибір! Спробуйте ще раз.\n";
        }
        if (choice != 0 && choice != 7) {
            cout << "\nНатисніть Enter для продовження...";
            cin.get();
        }
    } while (choice != 0 && choice != 7);

    return 0;
}