/*
    1. Описать в коде улучшенный алгоритм быстрой сортировки
    2. Сортировать в массиве целых положительных чисел только чётные числа,
    нечётные оставив на своих местах при помощи алгоритма блочной сортировки,
    то есть массив вида [0 2 8 3 4 6 5 9 8 2 7 3] превратить в [0 2 2 3 4 6 5 9 8 8 7 3]

    Результатом работы должен стать один файл с кодом на языке С, содержащий функцию main и функции, необходимые для реализации сортировок
*/

#include <iostream>
#include <iomanip>
#include <conio.h>

// выделение памяти под динамический одномерный массив
int* initArray1D(int* arr, const int par_size)
{
    arr = new int[par_size];
    return arr;
}

// удаление памяти, выделенной под динамический одномерный массив
void deleteArray1D(int* arr)
{
    delete[] arr;
}

// вывод на экран одномерного массива
void printArray1D(int* arr, const int par_size_arr)
{
    std::cout << "|";
    for (int i = 0; i < par_size_arr; i++)
    {
        std::cout << std::setw(4) << arr[i] << "|";
    }
}

// заполнение рандомными значениями двумерного массива
void fillArray1D(int* arr, const int par_size, const int max_mod)
{
    for (int i = 0; i < par_size; i++)
    {
        arr[i] = rand() % max_mod + 1;
    }
}

// выделение памяти под динамический двумерный массив
int** initArray2D(int** arr, const int par_rows, const int par_columns)
{
    arr = new int* [par_rows];
    for (int i = 0; i < par_rows; i++)
    {
        arr[i] = new int[par_columns];
    }

    return arr;
}

// удаление памяти, выделенной под динамический двумерный массив
void deleteArray2D(int** arr, const int par_rows)
{
    for (int i = 0; i < par_rows; i++)
    {
        delete[] arr[i];
    }
    delete[] arr;
}

// смена местами элементов
void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

int swap3median(int* a, int* b, int* c)
{
    // (a >= b && b >= c) ? b : ((b >= c && c >= a) ? c : a)
    if (*b >= *c && *c >= *a)
    {
        swap(c, b);
    }
    else if (*c >= *a && *a >= *b)
    {
        swap(a, b);
    }
    return *b;
}

void insertsSort(int* arr, int first, int last)
{
    int tmp;
    int pos;

    for (int i = first + 1; i < last; i++)
    {
        tmp = arr[i];
        pos = i - 1;
        while (pos >= first && arr[pos] > tmp)
        {
            arr[pos + 1] = arr[pos];
            pos--;
        }
        arr[pos + 1] = tmp;
    }
}

void quickSortImproved(int* arr, int first, int last)
{
    int i = first;
    int j = last;

    if (last - first > 10)      // если в подмассиве более 10 элементов, то применяется быстрая сортировка
    {
        int x = swap3median(&arr[i], &arr[j], &arr[(i + j) / 2]);
        do
        {
            while (arr[i] < x)
            {
                i++;
            }
            while (arr[j] > x)
            {
                j--;
            }

            if (i <= j)
            {
                swap(&arr[i], &arr[j]);
                i++;
                j--;
            }
        } while (i <= j);

        if (i < last)
        {
            quickSortImproved(arr, i, last);
        }
        if (j > first)
        {
            quickSortImproved(arr, first, j);
        }
    }
    else        // иначе применяется сортировка вставками
    {
        insertsSort(arr, first, last + 1);
    }
}

void bucketSort(int* arr, const int len)
{
    const int max = len;
    const int b = 10;

    int** buckets = nullptr;
    buckets = initArray2D(buckets, b, max + 1);

    for (int i = 0; i < b; i++)
    {
        buckets[i][max] = 0;
    }

    for (int digit = 1; digit < 1'000; digit *= 10)
    {
        for (int i = 0; i < max; i++)
        {
            if (arr[i] % 2 == 0)
            {
                int d = (arr[i] / digit) % b;
                buckets[d][buckets[d][max]++] = arr[i];
                arr[i] = -1;
            }
        }

        int idx = 0;
        for (int i = 0; i < b; i++)
        {
            for (int j = 0; j < buckets[i][max]; j++)
            {
                while ((arr[idx] != -1) && (idx < max))
                {
                    idx++;
                }
                arr[idx++] = buckets[i][j];
            }
            buckets[i][max] = 0;
        }
    }

    deleteArray2D(buckets, b);
}

void Task_1()
{
    int* mas = nullptr;
    int mas_size = -1;

    while (mas_size <= 0 || mas_size > 100)
    {
        std::cout << "\nВведите количество элементов массива (до 100): ";
        std::cin >> mas_size;
    }

    mas = initArray1D(mas, mas_size);
    fillArray1D(mas, mas_size, 100);
    std::cout << "До сортировки:\n";
    printArray1D(mas, mas_size);
    quickSortImproved(mas, 0, mas_size - 1);
    std::cout << "\nПосле сортировки:\n";
    printArray1D(mas, mas_size);
}

void Task_2()
{
    int* mas = nullptr;
    int mas_size = -1;

    while (mas_size <= 0 || mas_size > 100)
    {
        std::cout << "\nВведите количество элементов массива (до 100): ";
        std::cin >> mas_size;
    }

    mas = initArray1D(mas, mas_size);
    fillArray1D(mas, mas_size, 100);
    std::cout << "До сортировки:\n";
    printArray1D(mas, mas_size);
    bucketSort(mas, mas_size);
    std::cout << "\nПосле сортировки:\n";
    printArray1D(mas, mas_size);
}

int main()
{
    setlocale(LC_ALL, "Russian");
    srand(time(0ULL));

    char answer = '0';

    do
    {
        std::cout << "Выберите задание для проверки, нажав соответствующую клавишу на клавиатуре:\n\t1. Улучшенная быстрая сортировка;\n\t2. Блочная сортировка;\n\t0. Выход из программы\n";
        std::cout << "Ваш ответ: ";

        answer = (char)_getche();
        std::cout << std::endl;
        switch (answer)
        {
        case '1': Task_1(); break;
        case '2': Task_2(); break;
        case '0': break;
        default: std::cout << "\nВы нажали неправильную клавишу. Попробуйте еще раз!\n";
        }
        std::cout << "\n***************************************************\n";
    } while (answer != '0');

    return 0;
}
