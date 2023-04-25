#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>  
#include <string.h>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <stdlib.h>
#include <cstring>  
#include <string>
#include <iomanip>   
#include <Windows.h>
struct Date {
    int day;
    int month;
    int year;
};
struct Student {
    char surname[255];
    char name[255];
    char group[10];
    int course;
    Date birth;
};

void printArrayStruct(const char* header, Student* st, int n);
int setSize(std::string path);
bool getFromFile(std::string path, Student* arr, int size);
bool sortByGroupNumber(Student* arr, int size);
bool sortByGroupNumberAlphabetically(Student* arr, int size);
bool sortBySurnameAlphabetically(Student* arr, int size);

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Student* st, * arr;
    st = new Student[5];
    char header[] = "  Массив записей о студентах из файла";
    int i = 0, n = 1;
    char str[] = "Матієшин Кирило 2 Кб-21 12.02.2006";
    printf("Разделение строки \"%s\" на лексемы.", str);
    char* pch = strtok(str, " .");
    printf("\nЛексемы:");

    while (pch != NULL)
    {
        printf("\n%s", pch);
        i++;
        switch (i)
        {
        case 1: strcpy(st[0].surname, pch); break;
        case 2: strcpy(st[0].name, pch); break;
        case 3: st[0].course = atoi(pch); break;
        case 4: strcpy(st[0].group, pch); break;
        case 5: st[0].birth.day = atoi(pch); break;
        case 6: st[0].birth.month = atoi(pch); break;
        case 7: st[0].birth.year = atoi(pch); break;
        }
        pch = strtok(NULL, " ,.");
    }
    printArrayStruct("  Постоянная запись в программе", st, 1);

    std::string path = "Student.txt";
    int size = setSize(path);

    arr = new Student[size];
    bool fileRead = getFromFile(path, arr, size);

    if (fileRead)
    {
        std::cout << "Не отсортованний масив: " << std::endl;
        printArrayStruct(header, arr, size);
    }
    else
        std::cout << "Ошибка чтения из файла" << std::endl;

    sortByGroupNumber(arr, size);
    std::cout << "Отсортировано по номеру группы:\n";
    printArrayStruct(header, arr, size);

    sortByGroupNumberAlphabetically(arr, size);
    std::cout << "Отсортировано по номеру группы в алфавитном порядке:\n";
    printArrayStruct(header, arr, size);

    sortBySurnameAlphabetically(arr, size);
    std::cout << "Отсортировано по фамилии в алфавитном порядке:\n";
    printArrayStruct(header, arr, size);

    delete[] st;
    delete[] arr;

    return 0;
}

void printArrayStruct(const char* header, Student* st, int n)
{
    printf("\n%-50s\n", header);
    printf("|----------------------------------------------------------|\n");
    printf("|Курс| Група  |    Прізвище    |    Ім'я   |Дата народження|\n");
    printf("|----|--------|----------------|-----------|---------------|\n");
    for (int i = 0; i < n; i++)
    {
        printf("|  %d | %-6s | %-14s | %-10s|   %02d/%02d/%4d  |\n", st[i].course, st[i].group, st[i].surname, st[i].name,
            st[i].birth.day, st[i].birth.month, st[i].birth.year);

    }
    printf("------------------------------------------------------------\n\n");
}

int setSize(std::string path) {
    int size = 0;
    std::ifstream fin;
    fin.open(path);

    if (!fin.is_open())
    {
        std::cout << "ERROR";
        exit(1);
    }

    std::string line;
    while (std::getline(fin, line)) {
        size++;
    }
    fin.close();
    return size;
}

bool getFromFile(std::string path, Student* arr, int size)
{
    std::string line;
    bool yes = true;
    char str[100] = "";
    std::ifstream fin;
    fin.open(path, std::ios::in);

    if (!fin.is_open())
    {
        std::cout << "ERROR";
        exit(1);
    }
    int i, k, err;
    i = 0; k = 0;
    while (getline(fin, line))
    {
        i = 0;
        strcpy(str, line.c_str());
        char* pch = strtok(str, " .");
        while (pch != NULL)
        {
            i++;
            switch (i)
            {
            case 1: strcpy(arr[k].surname, pch); break;
            case 2: strcpy(arr[k].name, pch); break;
            case 3: arr[k].course = atoi(pch); break;
            case 4: strcpy(arr[k].group, pch); break;
            case 5: arr[k].birth.day = atoi(pch); break;
            case 6: arr[k].birth.month = atoi(pch); break;
            case 7: arr[k].birth.year = atoi(pch); break;
            }
            pch = strtok(NULL, " .");
        }
        k++;
    }
    fin.close();
    return yes;
}

bool sortByGroupNumber(Student* arr, int size) {
    std::sort(arr, arr + size, [](const Student& a, const Student& b) {
        return strcmp(a.group, b.group) < 0;
        });
    return true;
}

bool sortByGroupNumberAlphabetically(Student* arr, int size) {
    std::sort(arr, arr + size, [](const Student& a, const Student& b) {
        if (strcmp(a.group, b.group) != 0) {
            return strcmp(a.group, b.group) < 0;
        }
    return strcmp(a.name, b.name) < 0;
        });
    return true;
}

int getCharInt(char c)
{
    const char alphabet[34] = "абвгґдеєжзиіїйклмнопрстуфхцчшщьюя";
    const char bigAlphabet[34] = "АБВГҐДЕЄЖЗИІЇЙКЛМНОПРСТУФХЦЧШЩЬЮЯ";

    for (int i = 0; i < 33; i++)
    {
        if (c == alphabet[i] || c == bigAlphabet[i]) return i;
    }
    return -1;
}

bool checkSurnameAlphabetically(const Student& a, const Student& b)
{
    const char* a_ptr = a.surname;
    const char* b_ptr = b.surname;

    while (*a_ptr != '\0' && *b_ptr != '\0')
    {
        int ai = getCharInt(*a_ptr);
        int bi = getCharInt(*b_ptr);
        if (ai < bi) return true;
        if (ai > bi) return false;
        a_ptr++;
        b_ptr++;
    }
    return true;
}

bool sortBySurnameAlphabetically(Student* arr, int size)
{
    std::sort(arr, arr + size, checkSurnameAlphabetically);
    return true;
}
