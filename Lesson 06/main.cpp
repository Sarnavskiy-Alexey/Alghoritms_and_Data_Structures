/*
    1. ����������� ����������� ���������� ���������� �������
    ��������, ������

    1,9,2
    5,7,6
    4,3,8

    ������ �� ������ �����

    1,2,3
    4,5,6
    7,8,9

    2. ������� ��������� ����-����� ��������� ������-�����-�����:

    1 - ��������� � ������������ 11 ����� � �������� �� � ������������������ �
    2 - ������������� ������������������ �
    3 - ��� ������� �������� ������������������ � ���������� ���������� �� �������
    sqrt(fabs(�)) + 5 * pow(�, 3)
    � ���� ��������� ���������� ��������� 400 - ���������������� ������������.

    3. ����������� �������� ������-�����-����� � ���� �� ����� �

    ����������� ���������� ������� ������ ����� ��� �����: � ����� �� ����� �,
    ���������� ������� main � ��� �������, ��������������� ���������� � ���������
    ������-�����-�����, � � ������������ � ����� ���������� ������� (jpg, png, gif)
*/

#include <iostream>
#include <iomanip>
#include <conio.h>
#include <cmath>

// ������-���������
#define K_TPK_size 11
#define K_TPK_five 5.0

// �������
#define CHECK_RANGE(a, l, r) (((a >= l) && (a <= r)) ? true : false)

// ��������� ������ ��� ������������ ���������� ������
int* initArray1D(int* arr, const int par_size)
{
    arr = new int [par_size];
    return arr;
}

// �������� ������, ���������� ��� ������������ ���������� ������
void deleteArray1D(int* arr)
{
    delete[] arr;
}

// ����� �� ����� ����������� �������
void printArray1D(int* arr, const int par_size_arr)
{
    std::cout << "|";
    for (int i = 0; i < par_size_arr; i++)
    {
        std::cout << std::setw(4) << arr[i] << "|";
    }
}

// ��������� ������ ��� ������������ ��������� ������
int** initArray2D(int** arr, const int par_rows, const int par_columns)
{
    arr = new int* [par_rows];
    for (int i = 0; i < par_rows; i++)
    {
        arr[i] = new int[par_columns];
    }

    return arr;
}

// �������� ������, ���������� ��� ������������ ��������� ������
void deleteArray2D(int** arr, const int par_rows)
{
    for (int i = 0; i < par_rows; i++)
    {
        delete[] arr[i];
    }
    delete[] arr;
}

// ���������� ���������� ���������� ���������� �������
void fillArray2D(int** arr, const int par_rows, const int par_columns, const int max_mod)
{
    for (int i = 0; i < par_rows; i++)
    {
        for (int j = 0; j < par_columns; j++)
        {
            arr[i][j] = rand() % max_mod + 1;
        }
    }
}

// ����� �� ����� ���������� �������
void printArray2D(int** arr, const int par_rows, const int par_columns)
{
    for (int i = 0; i < par_rows; i++, std::cout << std::endl)
    {
        std::cout << "|";
        for (int j = 0; j < par_columns; j++)
        {
            std::cout << std::setw(4) << arr[i][j] << "|";
        }
    }
}

void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

// ���������� ��������� ���������� �������
void bubbleSort(int** arr, const int par_rows, const int par_columns)
{
    int* tmp_arr = nullptr;
    int size_tmp_arr = par_rows * par_columns;
    int counter = 0;

    tmp_arr = initArray1D(tmp_arr, size_tmp_arr);

    for (int i = 0; i < par_rows; i++)
    {
        for (int j = 0; j < par_columns; j++)
        {
            tmp_arr[counter++] = arr[i][j];
        }
    }

    for (int i = 0; i < size_tmp_arr; i++)
    {
        for (int j = 0; j < size_tmp_arr - 1; j++)
        {
            if (tmp_arr[j] > tmp_arr[j + 1])
            {
                swap(&tmp_arr[j], &tmp_arr[j + 1]);
            }
        }
    }

    counter = 0;

    for (int i = 0; i < par_rows; i++)
    {
        for (int j = 0; j < par_columns; j++)
        {
            arr[i][j] = tmp_arr[counter++];
        }
    }

    deleteArray1D(tmp_arr);
}

// �������������� ����������� �������
void reverseArr(double* arr)
{
    for (int i = 0; i < K_TPK_size / 2; i++)
    {
        double tmp = arr[i];
        arr[i] = arr[K_TPK_size - 1 - i];
        arr[K_TPK_size - 1 - i] = tmp;
    }
}

void Task_1()
{
    setlocale(LC_ALL, "Russian");
    srand(time(0ULL));

    // ������������� ����������
    int** arr = nullptr;
    int rows = 0;
    int columns = 0;
    int max_mod = 50;

    do
    {
        std::cout << "������� ���������� ����� ������� (1 <= rows <= 50): ";
        std::cin >> rows;
    } while (!(CHECK_RANGE(rows, 1, 50)));
    do
    {
        std::cout << "������� ���������� �������� ������� (1 <= columns <= 50): ";
        std::cin >> columns;
    } while (!(CHECK_RANGE(columns, 1, 50)));
    
    arr = initArray2D(arr, rows, columns);
    fillArray2D(arr, rows, columns, max_mod);
    std::cout << "������ �������� ���������� ���������� �� 1 �� " << max_mod << ":\n";
    printArray2D(arr, rows, columns);

    std::cout << "---------------------------------------------\n";

    bubbleSort(arr, rows, columns);
    std::cout << "������ ������������:\n";
    printArray2D(arr, rows, columns);

    deleteArray2D(arr, rows);
}

void TPK_Algorithm()
{
    double arr[K_TPK_size] = { 0 };
    int i = 0;
    double d = 0.0;

    for (i = 0; i < K_TPK_size; i++)
    {
        std::cout << "������� �[" << i << "]: ";
        std::cin >> arr[i];
    }

    reverseArr(arr);

    for (i = 0; i < K_TPK_size; i++)
    {
        d = sqrt(fabs(arr[i])) + K_TPK_five * pow(arr[i], 3);
        if (d <= 400.0)
        {
            std::cout << d << std::endl;
        }
        else
        {
            std::cout << "��������������! ����� ������ 400!" << std::endl;
        }
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");
    char answer = '0';

    do
    {
        std::cout << "�������� ������� ��� ��������, ����� ��������������� ������� �� ����������:\n\t1. ���������� ��������� 2-�� �������;\n\t2. �������� ������-�����-�����;\n\t0. ����� �� ���������\n";
        std::cout << "��� �����: ";

        answer = (char)_getche();
        std::cout << std::endl;
        switch (answer)
        {
            case '1': Task_1(); break;
            case '2': TPK_Algorithm(); break;
            case '0': break;
            default: std::cout << "\n�� ������ ������������ �������. ���������� ��� ���!\n";
        }
        std::cout << "\n***************************************************\n";
    } while (answer != '0');

    return 0;
}
