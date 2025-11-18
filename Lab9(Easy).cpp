#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>

struct STUDENT {
    std::string full_name;  
    int group_number;
    int grades[5];
};

double calculateAverage(const STUDENT& student) {
    double sum = 0;
    for (int j = 0; j < 5; j++) {
        sum += student.grades[j];
    }
    return sum / 5;
}

void printStudent(const STUDENT& student) {
    std::cout << "ФИО: " << student.full_name << " | Группа: " << student.group_number << " | ";
    std::cout << "Оценки: ";
    for (int j = 0; j < 5; j++) {
        std::cout << student.grades[j] << " ";
    }
    std::cout << "| Средний балл: " << calculateAverage(student) << std::endl;
}

int main() {
    int numberOfStudents;
    std::cout << "Введите количество студентов: ";
    std::cin >> numberOfStudents;
    std::cin.ignore();

    std::vector<STUDENT> students(numberOfStudents);
    
    for (int i = 0; i < numberOfStudents; i++) {
        std::cout << "\nСтудент " << (i + 1) << ":\n";
        std::cout << "ФИО: ";
        std::getline(std::cin, students[i].full_name);
        std::cout << "Группа: ";
        std::cin >> students[i].group_number;
        std::cout << "5 оценок: ";
        for (int j = 0; j < 5; j++) {
            std::cin >> students[i].grades[j];
        }
        std::cin.ignore();
    }

    std::sort(students.begin(), students.end(), 
        [](const STUDENT& a, const STUDENT& b) {
            return a.group_number < b.group_number;
        });
    
    std::cout << "\n=== Все студенты (отсортированы по группе) ===" << std::endl;
    for (const STUDENT& student : students) {
        printStudent(student);
    }

    std::cout << "\n=== Студенты со средним баллом 4.0 и выше ===" << std::endl;
    bool found = false;
    for (const STUDENT& student : students) {
        if (calculateAverage(student) >= 4.0) {
            printStudent(student);
            found = true;
        }
    }
    if (!found) std::cout << "Не найдено" << std::endl;

    std::cout << "\n=== Статистика по группам ===" << std::endl;
    std::vector<int> groups;
    for (const STUDENT& student : students) {
        if (std::find(groups.begin(), groups.end(), student.group_number) == groups.end()) {
            groups.push_back(student.group_number);
        }
    }

    // Табличный вывод статистики с вертикальными разделителями
    std::cout << std::string(45, '-') << std::endl;
    std::cout << "| " << std::left << std::setw(8) << "Группа" << " | "
              << std::setw(14) << "Всего студентов" << " | "
              << std::setw(12) << "Двоечников" << " | " << std::endl;
    std::cout << std::string(45, '-') << std::endl;

    for (int group : groups) {
        int total = 0, low = 0;
        for (const STUDENT& student : students) {
            if (student.group_number == group) {
                total++;
                if (calculateAverage(student) < 2.6) low++;
            }
        }
        
        std::cout << "| " << std::left << std::setw(8) << group << " | "
                  << std::setw(14) << total << " | "
                  << std::setw(12) << low << " | " << std::endl;

    }
    std::cout << std::string(45, '-') << std::endl;
    
    return 0;
}