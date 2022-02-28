#include <iostream>
#include "massives.h"

// функция обнуления данных 1D массива
void resetArr(bool* arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        arr[i] = false;
    }
}

// функция обнуления данных 1D массива
void resetArr(int* arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        arr[i] = false;
    }
}

// выделение памяти под 2D матрицу
int** initMatr2D(int** matr, int size)
{
    matr = new int* [size];
    for (int i = 0; i < size; i++)
    {
        matr[i] = new int[size];
    }

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            matr[i][j] = rand() % 2;
        }
    }

    return matr;
}

// выделение памяти под 1D матрицу
bool* initMas1D(bool* arr, int size)
{
    arr = new bool[size];
    resetArr(arr, size);

    return arr;
}

// выделение памяти под 1D матрицу
int* initMas1D(int* arr, int size)
{
    arr = new int[size];
    resetArr(arr, size);

    return arr;
}

// вывод матрицы на экран
void printMatr(int** matr, int size)
{
    std::cout << "  ";
    for (int i = 0; i < size; i++)
    {
        std::cout << (char)(i + 65) << " ";
    }
    std::cout << "\n";

    for (int i = 0; i < size; i++)
    {
        std::cout << (char)(i + 65) << " ";
        for (int j = 0; j < size; j++)
        {
            std::cout << matr[i][j] << " ";
        }
        std::cout << "\n";
    }
    std::cout << std::endl;

    return;
}

// вывод массива на экран
void printMass(int* arr1, int* arr2, int size)
{
    for (int i = 0; i < size; i++)
    {
        std::cout << (char)(i + 65) << " ";
    }
    std::cout << std::endl;
    for (int i = 0; i < size; i++)
    {
        std::cout << arr1[i] << " ";
    }
    std::cout << std::endl;
    for (int i = 0; i < size; i++)
    {
        std::cout << arr2[i] << " ";
    }
    std::cout << std::endl;
}

// удаление выделенной под 1D массив памяти
bool* delMas1D(bool* arr)
{
    delete[] arr;

    return nullptr;
}

// удаление выделенной под 1D массив памяти
int* delMas1D(int* arr)
{
    delete[] arr;

    return nullptr;
}

// удаление выделенной под 2D матрицу памяти
int** delMatr2D(int** matr, int size)
{
    for (int i = 0; i < size; i++)
    {
        delete[] matr[i];
    }
    delete[] matr;

    return nullptr;
}