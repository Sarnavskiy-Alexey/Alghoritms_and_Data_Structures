#pragma once

// extern используемых функций
extern void resetArr(bool* arr, int size);
extern void resetArr(int* arr, int size);
extern int** initMatr2D(int** matr, int size);
extern bool* initMas1D(bool* arr, int size);
extern int* initMas1D(int* arr, int size);
extern void printMatr(int** matr, int size);
extern bool* delMas1D(bool* arr);
extern int* delMas1D(int* arr);
extern int** delMatr2D(int** matr, int size);
extern void printMass(int* arr1, int* arr2, int size);