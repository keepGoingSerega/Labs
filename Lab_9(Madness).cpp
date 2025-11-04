//Программа выводит статистику по студентам.
//Возможен ввод данных вручную или из файла. Возможно сохранение данных в файл.
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>
#include <iomanip>
#include <fstream>
#include <sstream>

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

void printStudentToFile(std::ofstream& file, const STUDENT& student) {
    file << "ФИО: " << student.full_name << " | Группа: " << student.group_number << " | ";
    file << "Оценки: ";
    for (int j = 0; j < GRADES_COUNT; j++) {
        file << student.grades[j] << " ";
    }
    file << "| Средний балл: " << std::fixed << std::setprecision(1) << calculateAverage(student);
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

void inputStudentsFromFile(std::vector<STUDENT>& students, const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Ошибка! Не удалось открыть файл " << filename << " для чтения." << std::endl;
        return;
    }
    
    students.clear();
    std::string line;
    int line_num = 0;
    
    while (std::getline(file, line)) {
        line_num++;
        if (line.empty() || line[0] == '#') continue;
        
        STUDENT student;
        std::istringstream iss(line);
        
        std::vector<std::string> tokens;
        std::string token;
        
        while (iss >> token) {
            tokens.push_back(token);
        }
        
        if (tokens.size() < 6) {
            std::cout << "Ошибка в строке " << line_num << ": недостаточно данных" << std::endl;
            continue;
        }
        
        int data_start = tokens.size() - 6;
        
        try {
            student.group_number = std::stoi(tokens[data_start]);
        } catch (...) {
            std::cout << "Ошибка в строке " << line_num << ": неверный формат номера группы" << std::endl;
            continue;
        }
        
        for (int j = 0; j < GRADES_COUNT; j++) {
            try {
                student.grades[j] = std::stoi(tokens[data_start + 1 + j]);
            } catch (...) {
                std::cout << "Ошибка в строке " << line_num << ": неверный формат оценки" << std::endl;
                continue;
            }
        }
        
        student.full_name = "";
        for (int i = 0; i < data_start; i++) {
            if (i > 0) student.full_name += " ";
            student.full_name += tokens[i];
        }
        
        students.push_back(student);
    }
    
    file.close();
    std::cout << "Данные успешно загружены из файла " << filename << ". Загружено " << students.size() << " студентов." << std::endl;
}

void saveStudentsToFile(const std::vector<STUDENT>& students, const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "Ошибка! Не удалось открыть файл " << filename << " для записи." << std::endl;
        return;
    }
    
    for (const STUDENT& student : students) {
        file << student.full_name << " " << student.group_number;
        for (int j = 0; j < GRADES_COUNT; j++) {
            file << " " << student.grades[j];
        }
        file << std::endl;
    }
    
    file.close();
    std::cout << "Данные успешно сохранены в файл " << filename << std::endl;
}

void sortAndOutputStudentsByGroup(std::vector<STUDENT>& students) {
    if (!hasStudents(students)) {
        std::cout << "\nНет данных о студентах для сортировки." << std::endl;
        return;
    }

    std::sort(students.begin(), students.end(), 
        [](const STUDENT& a, const STUDENT& b) {
            return a.group_number < b.group_number;
        });
    
    std::cout << "\n=== ВСЕ СТУДЕНТЫ (отсортированы по группе) ===" << std::endl;
    for (const STUDENT& student : students) {
        printStudent(student);
        std::cout << std::endl;
    }
}

void saveSortedStudentsToFile(const std::vector<STUDENT>& students, const std::string& filename) {
    if (!hasStudents(students)) {
        std::cout << "\nНет данных о студентах для сохранения." << std::endl;
        return;
    }

    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "Ошибка! Не удалось открыть файл " << filename << " для записи." << std::endl;
        return;
    }
    
    file << "=== ВСЕ СТУДЕНТЫ (отсортированы по группе) ===" << std::endl;
    for (const STUDENT& student : students) {
        printStudentToFile(file, student);
        file << std::endl;
    }
    
    file.close();
    std::cout << "Отсортированные данные сохранены в файл " << filename << std::endl;
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

void saveHighAchieversToFile(const std::vector<STUDENT>& students, const std::string& filename) {
    if (!hasStudents(students)) {
        std::cout << "\nНет данных о студентах." << std::endl;
        return;
    }

    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "Ошибка! Не удалось открыть файл " << filename << " для записи." << std::endl;
        return;
    }

    bool foundHighAchievers = false;
    file << "=== СТУДЕНТЫ СО СРЕДНИМ БАЛЛОМ " << HIGH_ACHIEVER_THRESHOLD << " И ВЫШЕ ===" << std::endl;
    for (const STUDENT& student : students) {
        if (isHighAchiever(student)) {
            printStudentToFile(file, student);
            file << std::endl;
            foundHighAchievers = true;
        }
    }
    
    if (!foundHighAchievers) {
        file << "Студентов со средним баллом " << HIGH_ACHIEVER_THRESHOLD << " и выше не найдено." << std::endl;
    }
    
    file.close();
    std::cout << "Данные о хорошистах сохранены в файл " << filename << std::endl;
}

// Структура для хранения статистики группы
struct GroupStats {
    int group_number;
    int total_students;
    int low_achievers;
    int high_achievers;
    double average_score;
};

void showGroupStatistics(const std::vector<STUDENT>& students) {
    if (!hasStudents(students)) {
        std::cout << "\nНет данных о студентах для статистики." << std::endl;
        return;
    }

    std::cout << "\n=== СТАТИСТИКА ПО ГРУППАМ ===" << std::endl;
    
    std::vector<int> unique_groups;
    for (const STUDENT& student : students) {
        if (std::find(unique_groups.begin(), unique_groups.end(), student.group_number) == unique_groups.end()) {
            unique_groups.push_back(student.group_number);
        }
    }
    
    std::vector<GroupStats> stats;
    for (int group : unique_groups) {
        GroupStats group_stat;
        group_stat.group_number = group;
        group_stat.total_students = 0;
        group_stat.low_achievers = 0;
        group_stat.high_achievers = 0;
        group_stat.average_score = 0.0;
        
        double total_group_score = 0.0;
        for (const STUDENT& student : students) {
            if (student.group_number == group) {
                group_stat.total_students++;
                double student_avg = calculateAverage(student);
                total_group_score += student_avg;
                
                if (student_avg < LOW_ACHIEVER_THRESHOLD) {
                    group_stat.low_achievers++;
                }
                if (student_avg >= HIGH_ACHIEVER_THRESHOLD) {
                    group_stat.high_achievers++;
                }
            }
        }
        group_stat.average_score = total_group_score / group_stat.total_students;
        stats.push_back(group_stat);
    }
    
    std::sort(stats.begin(), stats.end(), 
        [](const GroupStats& a, const GroupStats& b) {
            return a.low_achievers > b.low_achievers;
        });
    
    std::cout << "-----------------------------------------------------------------" << std::endl;
    std::cout << "| Группа | Всего | Двоечники | Хорошисты | Средний балл |" << std::endl;
    std::cout << "-----------------------------------------------------------------" << std::endl;
    
    for (const GroupStats& stat : stats) {
        std::cout << "| " << std::setw(6) << stat.group_number << " | " 
                  << std::setw(5) << stat.total_students << " | " 
                  << std::setw(9) << stat.low_achievers << " | " 
                  << std::setw(9) << stat.high_achievers << " | " 
                  << std::setw(12) << std::fixed << std::setprecision(2) << stat.average_score << " |" << std::endl;
    }
    
    std::cout << "-----------------------------------------------------------------" << std::endl;
}

void saveGroupStatisticsToFile(const std::vector<STUDENT>& students, const std::string& filename) {
    if (!hasStudents(students)) {
        std::cout << "\nНет данных о студентах для статистики." << std::endl;
        return;
    }

    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "Ошибка! Не удалось открыть файл " << filename << " для записи." << std::endl;
        return;
    }

    file << "=== СТАТИСТИКА ПО ГРУППАМ ===" << std::endl;
    
    std::vector<int> unique_groups;
    for (const STUDENT& student : students) {
        if (std::find(unique_groups.begin(), unique_groups.end(), student.group_number) == unique_groups.end()) {
            unique_groups.push_back(student.group_number);
        }
    }
    
    std::vector<GroupStats> stats;
    for (int group : unique_groups) {
        GroupStats group_stat;
        group_stat.group_number = group;
        group_stat.total_students = 0;
        group_stat.low_achievers = 0;
        group_stat.high_achievers = 0;
        group_stat.average_score = 0.0;
        
        double total_group_score = 0.0;
        for (const STUDENT& student : students) {
            if (student.group_number == group) {
                group_stat.total_students++;
                double student_avg = calculateAverage(student);
                total_group_score += student_avg;
                
                if (student_avg < LOW_ACHIEVER_THRESHOLD) {
                    group_stat.low_achievers++;
                }
                if (student_avg >= HIGH_ACHIEVER_THRESHOLD) {
                    group_stat.high_achievers++;
                }
            }
        }
        group_stat.average_score = total_group_score / group_stat.total_students;
        stats.push_back(group_stat);
    }
    
    std::sort(stats.begin(), stats.end(), 
        [](const GroupStats& a, const GroupStats& b) {
            return a.low_achievers > b.low_achievers;
        });
    
    file << "-----------------------------------------------------------------" << std::endl;
    file << "| Группа | Всего | Двоечники | Хорошисты | Средний балл |" << std::endl;
    file << "-----------------------------------------------------------------" << std::endl;
    
    for (const GroupStats& stat : stats) {
        file << "| " << std::setw(6) << stat.group_number << " | " 
             << std::setw(5) << stat.total_students << " | " 
             << std::setw(9) << stat.low_achievers << " | " 
             << std::setw(9) << stat.high_achievers << " | " 
             << std::setw(12) << std::fixed << std::setprecision(2) << stat.average_score << " |" << std::endl;
    }
    
    file << "-----------------------------------------------------------------" << std::endl;
    
    file.close();
    std::cout << "Статистика сохранена в файл " << filename << std::endl;
}

// НОВАЯ ФУНКЦИЯ: Сохранение всей статистики в один файл
void saveCompleteReport(const std::vector<STUDENT>& students, const std::string& filename) {
    if (!hasStudents(students)) {
        std::cout << "\nНет данных о студентах для отчета." << std::endl;
        return;
    }

    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "Ошибка! Не удалось открыть файл " << filename << " для записи." << std::endl;
        return;
    }

    // Заголовок отчета
    file << "=================================================================" << std::endl;
    file << "                 ПОЛНЫЙ ОТЧЕТ ПО СТУДЕНТАМ" << std::endl;
    file << "=================================================================" << std::endl;
    file << "Дата создания: " << __DATE__ << " " << __TIME__ << std::endl;
    file << "Всего студентов: " << students.size() << std::endl;
    file << "=================================================================\n" << std::endl;

    // 1. Все студенты (отсортированные по группе)
    file << "1. ВСЕ СТУДЕНТЫ (отсортированы по группе):" << std::endl;
    file << "===========================================" << std::endl;
    
    std::vector<STUDENT> sorted_students = students;
    std::sort(sorted_students.begin(), sorted_students.end(), 
        [](const STUDENT& a, const STUDENT& b) {
            return a.group_number < b.group_number;
        });
    
    for (const STUDENT& student : sorted_students) {
        printStudentToFile(file, student);
        file << std::endl;
    }
    file << std::endl;

    // 2. Хорошисты
    file << "2. СТУДЕНТЫ СО СРЕДНИМ БАЛЛОМ " << HIGH_ACHIEVER_THRESHOLD << " И ВЫШЕ:" << std::endl;
    file << "===========================================" << std::endl;
    
    bool foundHighAchievers = false;
    for (const STUDENT& student : students) {
        if (isHighAchiever(student)) {
            printStudentToFile(file, student);
            file << std::endl;
            foundHighAchievers = true;
        }
    }
    if (!foundHighAchievers) {
        file << "Студентов со средним баллом " << HIGH_ACHIEVER_THRESHOLD << " и выше не найдено." << std::endl;
    }
    file << std::endl;

    // 3. Статистика по группам
    file << "3. СТАТИСТИКА ПО ГРУППАМ:" << std::endl;
    file << "==========================" << std::endl;
    
    std::vector<int> unique_groups;
    for (const STUDENT& student : students) {
        if (std::find(unique_groups.begin(), unique_groups.end(), student.group_number) == unique_groups.end()) {
            unique_groups.push_back(student.group_number);
        }
    }
    
    std::vector<GroupStats> stats;
    for (int group : unique_groups) {
        GroupStats group_stat;
        group_stat.group_number = group;
        group_stat.total_students = 0;
        group_stat.low_achievers = 0;
        group_stat.high_achievers = 0;
        group_stat.average_score = 0.0;
        
        double total_group_score = 0.0;
        for (const STUDENT& student : students) {
            if (student.group_number == group) {
                group_stat.total_students++;
                double student_avg = calculateAverage(student);
                total_group_score += student_avg;
                
                if (student_avg < LOW_ACHIEVER_THRESHOLD) {
                    group_stat.low_achievers++;
                }
                if (student_avg >= HIGH_ACHIEVER_THRESHOLD) {
                    group_stat.high_achievers++;
                }
            }
        }
        group_stat.average_score = total_group_score / group_stat.total_students;
        stats.push_back(group_stat);
    }
    
    std::sort(stats.begin(), stats.end(), 
        [](const GroupStats& a, const GroupStats& b) {
            return a.low_achievers > b.low_achievers;
        });
    
    file << "-----------------------------------------------------------------" << std::endl;
    file << "| Группа | Всего | Двоечники | Хорошисты | Средний балл |" << std::endl;
    file << "-----------------------------------------------------------------" << std::endl;
    
    for (const GroupStats& stat : stats) {
        file << "| " << std::setw(6) << stat.group_number << " | " 
             << std::setw(5) << stat.total_students << " | " 
             << std::setw(9) << stat.low_achievers << " | " 
             << std::setw(9) << stat.high_achievers << " | " 
             << std::setw(12) << std::fixed << std::setprecision(2) << stat.average_score << " |" << std::endl;
    }
    
    file << "-----------------------------------------------------------------" << std::endl;
    file << std::endl;

    // 4. Общая статистика
    file << "4. ОБЩАЯ СТАТИСТИКА:" << std::endl;
    file << "====================" << std::endl;
    
    int total_low_achievers = 0;
    int total_high_achievers = 0;
    double overall_average = 0.0;
    
    for (const STUDENT& student : students) {
        double avg = calculateAverage(student);
        overall_average += avg;
        if (avg < LOW_ACHIEVER_THRESHOLD) total_low_achievers++;
        if (avg >= HIGH_ACHIEVER_THRESHOLD) total_high_achievers++;
    }
    overall_average /= students.size();
    
    file << "Всего студентов: " << students.size() << std::endl;
    file << "Всего групп: " << unique_groups.size() << std::endl;
    file << "Двоечников (средний балл < " << LOW_ACHIEVER_THRESHOLD << "): " << total_low_achievers << std::endl;
    file << "Хорошистов (средний балл >= " << HIGH_ACHIEVER_THRESHOLD << "): " << total_high_achievers << std::endl;
    file << "Общий средний балл: " << std::fixed << std::setprecision(2) << overall_average << std::endl;
    
    file << "\n=================================================================" << std::endl;
    file << "                       КОНЕЦ ОТЧЕТА" << std::endl;
    file << "=================================================================" << std::endl;

    file.close();
    std::cout << "Полный отчет сохранен в файл " << filename << std::endl;
}

void showMenu() {
    std::cout << "\n=== МЕНЮ ===" << std::endl;
    std::cout << "1. Ввести данные вручную" << std::endl;
    std::cout << "2. Загрузить данные из файла" << std::endl;
    std::cout << "3. Сохранить данные в файл" << std::endl;
    std::cout << "4. Показать всех студентов (отсортировано по группе)" << std::endl;
    std::cout << "5. Сохранить отсортированных студентов в файл" << std::endl;
    std::cout << "6. Показать студентов со средним баллом 4.0 и выше" << std::endl;
    std::cout << "7. Сохранить хорошистов в файл" << std::endl;
    std::cout << "8. Показать статистику по группам" << std::endl;
    std::cout << "9. Сохранить статистику в файл" << std::endl;
    std::cout << "10. Сохранить полный отчет в один файл" << std::endl;  // НОВАЯ ОПЦИЯ
    std::cout << "0. Выход" << std::endl;
    std::cout << "Выберите опцию: ";
}

int main() {
    std::vector<STUDENT> students;
    int choice;
    
    do {
        showMenu();
        std::cin >> choice;
        clearInputBuffer();
        
        switch (choice) {
            case 1: {
                int numberOfStudents;
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
                        clearInputBuffer();
                        break; 
                    }
                }
                students.resize(numberOfStudents);
                inputStudents(students);
                break;
            }
            case 2: {
                std::string filename;
                std::cout << "Введите имя файла для загрузки: ";
                std::getline(std::cin, filename);
                inputStudentsFromFile(students, filename);
                break;
            }
            case 3: {
                if (!hasStudents(students)) {
                    std::cout << "Нет данных для сохранения." << std::endl;
                    break;
                }
                std::string filename;
                std::cout << "Введите имя файла для сохранения: ";
                std::getline(std::cin, filename);
                saveStudentsToFile(students, filename);
                break;
            }
            case 4:
                sortAndOutputStudentsByGroup(students);
                break;
            case 5: {
                if (!hasStudents(students)) {
                    std::cout << "Нет данных для сохранения." << std::endl;
                    break;
                }
                std::string filename;
                std::cout << "Введите имя файла для сохранения: ";
                std::getline(std::cin, filename);
                saveSortedStudentsToFile(students, filename);
                break;
            }
            case 6:
                fourOrMore(students);
                break;
            case 7: {
                if (!hasStudents(students)) {
                    std::cout << "Нет данных для сохранения." << std::endl;
                    break;
                }
                std::string filename;
                std::cout << "Введите имя файла для сохранения: ";
                std::getline(std::cin, filename);
                saveHighAchieversToFile(students, filename);
                break;
            }
            case 8:
                showGroupStatistics(students);
                break;
            case 9: {
                if (!hasStudents(students)) {
                    std::cout << "Нет данных для сохранения." << std::endl;
                    break;
                }
                std::string filename;
                std::cout << "Введите имя файла для сохранения: ";
                std::getline(std::cin, filename);
                saveGroupStatisticsToFile(students, filename);
                break;
            }
            case 10: {  // НОВАЯ ОПЦИЯ
                if (!hasStudents(students)) {
                    std::cout << "Нет данных для отчета." << std::endl;
                    break;
                }
                std::string filename;
                std::cout << "Введите имя файла для полного отчета: ";
                std::getline(std::cin, filename);
                saveCompleteReport(students, filename);
                break;
            }
            case 0:
                std::cout << "Выход из программы." << std::endl;
                break;
            default:
                std::cout << "Неверный выбор. Попробуйте снова." << std::endl;
        }
    } while (choice != 0);
    
    return 0;
}