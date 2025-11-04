#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>
#include <iomanip>

// Константы
const int GRADES_COUNT = 5;
const double HIGH_ACHIEVER_THRESHOLD = 4.0;
const double LOW_ACHIEVER_THRESHOLD = 2.6;

struct STUDENT {
    std::string full_name;  
    int group_number;
    int grades[GRADES_COUNT];
};

void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

double calculateAverage(const STUDENT& student) {
    double sum = 0;
    for (int j = 0; j < GRADES_COUNT; j++) {
        sum += student.grades[j];
    }
    return sum / GRADES_COUNT;
}

void printStudent(const STUDENT& student) {
    std::cout << "ФИО: " << student.full_name << " | Группа: " << student.group_number << " | ";
    std::cout << "Оценки: ";
    for (int j = 0; j < GRADES_COUNT; j++) {
        std::cout << student.grades[j] << " ";
    }
    std::cout << "| Средний балл: " << std::fixed << std::setprecision(1) << calculateAverage(student);
}

bool hasStudents(const std::vector<STUDENT>& students) {
    return !students.empty();
}

void inputStudents(std::vector<STUDENT>& students) {
    if (students.empty()) {
        return;
    }
    
    for (int i = 0; i < students.size(); i++) {
        std::cout << "\n=== Студент " << (i + 1) << " ===" << std::endl;
        
        // Ввод ФИО с проверкой
        while (true) {
            std::cout << "ФИО: ";
            std::getline(std::cin, students[i].full_name);
            if (!students[i].full_name.empty()) {
                break;
            }
            std::cout << "Ошибка! ФИО не может быть пустым. Попробуйте снова: ";
        }
        
        // Ввод номера группы с проверкой
        while (true) {
            std::cout << "Группа: ";
            if (!(std::cin >> students[i].group_number)) {
                std::cout << "Ошибка! Введите целое число: ";
                clearInputBuffer();
            } else if (students[i].group_number <= 0) {
                std::cout << "Ошибка! Введите положительное число: ";
                clearInputBuffer();
            } else {
                clearInputBuffer(); // Очищаем буфер после успешного ввода числа
                break;
            }
        }
        
        // Ввод оценок с проверкой
        std::cout << "Введите " << GRADES_COUNT << " оценок (через пробел): ";
        for (int j = 0; j < GRADES_COUNT; j++) {
            while (true) {
                if (!(std::cin >> students[i].grades[j])) {
                    std::cout << "Ошибка! Введите целое число для оценки " << (j + 1) << ": ";
                    clearInputBuffer();
                } else if (students[i].grades[j] < 1 || students[i].grades[j] > 5) {
                    std::cout << "Ошибка! Введите оценку от 1 до 5 для оценки " << (j + 1) << ": ";
                    clearInputBuffer();
                } else {
                    break;
                }
            }
        }
        clearInputBuffer(); // Очищаем буфер после ввода оценок
    }
}

void sortAndOutputStudentsByGroup(std::vector<STUDENT>& students) {
    if (!hasStudents(students)) {
        std::cout << "\nНет данных о студентах для сортировки." << std::endl;
        return;
    }

    // Сортировка по группе с использованием STL
    std::sort(students.begin(), students.end(), 
        [](const STUDENT& a, const STUDENT& b) {
            return a.group_number < b.group_number;
        });
    
    // Вывод отсортированных студентов
    std::cout << "\n=== ВСЕ СТУДЕНТЫ (отсортированы по группе) ===" << std::endl;
    for (const STUDENT& student : students) {
        printStudent(student);
        std::cout << std::endl;
    }
}

bool isHighAchiever(const STUDENT& student) {
    double average = calculateAverage(student);
    return average >= HIGH_ACHIEVER_THRESHOLD;
}

void fourOrMore(const std::vector<STUDENT>& students) {
    if (!hasStudents(students)) {
        std::cout << "\nНет данных о студентах." << std::endl;
        return;
    }

    bool foundHighAchievers = false;
    std::cout << "\n=== СТУДЕНТЫ СО СРЕДНИМ БАЛЛОМ " << HIGH_ACHIEVER_THRESHOLD << " И ВЫШЕ ===" << std::endl;
    for (const STUDENT& student : students) {
        if (isHighAchiever(student)) {
            printStudent(student);
            std::cout << std::endl;
            foundHighAchievers = true;
        }
    }
    
    if (!foundHighAchievers) {
        std::cout << "Студентов со средним баллом " << HIGH_ACHIEVER_THRESHOLD << " и выше не найдено." << std::endl;
    }
}

// Структура для хранения статистики группы
struct GroupStats {
    int group_number;
    int total_students;
    int low_achievers;
};

void showGroupStatistics(const std::vector<STUDENT>& students) {
    if (!hasStudents(students)) {
        std::cout << "\nНет данных о студентах для статистики." << std::endl;
        return;
    }

    std::cout << "\n=== СТАТИСТИКА ПО ГРУППАМ ===" << std::endl;
    
    // Собираем уникальные группы
    std::vector<int> unique_groups;
    for (const STUDENT& student : students) {
        if (std::find(unique_groups.begin(), unique_groups.end(), student.group_number) == unique_groups.end()) {
            unique_groups.push_back(student.group_number);
        }
    }
    
    // Собираем статистику по группам
    std::vector<GroupStats> stats;
    for (int group : unique_groups) {
        GroupStats group_stat;
        group_stat.group_number = group;
        group_stat.total_students = 0;
        group_stat.low_achievers = 0;
        
        for (const STUDENT& student : students) {
            if (student.group_number == group) {
                group_stat.total_students++;
                if (calculateAverage(student) < LOW_ACHIEVER_THRESHOLD) {
                    group_stat.low_achievers++;
                }
            }
        }
        stats.push_back(group_stat);
    }
    
    // Сортировка по убыванию количества двоечников с использованием STL
    std::sort(stats.begin(), stats.end(), 
        [](const GroupStats& a, const GroupStats& b) {
            return a.low_achievers > b.low_achievers;
        });
    
    // Выводим таблицу с форматированием
    std::cout << "-------------------------------------------------" << std::endl;
    std::cout << "| Группа | Всего студентов |  Двоечники  |" << std::endl;
    std::cout << "-------------------------------------------------" << std::endl;
    
    for (const GroupStats& stat : stats) {
        std::cout << "| " << std::setw(6) << stat.group_number << " | " 
                  << std::setw(14) << stat.total_students << " | " 
                  << std::setw(10) << stat.low_achievers << " |" << std::endl;
    }
    
    std::cout << "-------------------------------------------------" << std::endl;
}

int main() {
    int numberOfStudents;
    
    // Ввод количества студентов с валидацией
    while (true) {
        std::cout << "Введите количество студентов: ";
        
        if (!(std::cin >> numberOfStudents)) {
            std::cout << "Ошибка! Введите целое число." << std::endl;
            clearInputBuffer();
        }
        else if (numberOfStudents <= 0) {
            std::cout << "Ошибка! Введите положительное число." << std::endl;
            clearInputBuffer();
        }
        else {
            clearInputBuffer(); // Очищаем буфер после успешного ввода
            break; 
        }
    }

    std::vector<STUDENT> students(numberOfStudents);
    inputStudents(students);
    sortAndOutputStudentsByGroup(students);
    fourOrMore(students);
    showGroupStatistics(students); 
    
    return 0;
}