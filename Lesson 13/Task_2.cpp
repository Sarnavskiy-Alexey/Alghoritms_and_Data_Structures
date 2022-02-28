/*
    2. Моделируем робот поисковой системы. Дан готовый простой граф с циклическими связями.
    Нужно обойти этот граф двумя способами и подсчитать количество ссылок на каждый из узлов
    графа (полустепень захода).
        a) обход графа рекурсивной функцией (с подсчётом только смежных со стартовой вершин)
        b) обход графа по матрице смежности (с подсчётом всех вершин графа) В конце обхода
        вывести два получившихся списка всех узлов в порядке уменьшения количества ссылок на них.
*/

#include <iostream>
#include "Task_2.h"
#include "massives.h"

void adjacencyMatrixWay(int** matr, int* adj, int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (matr[i][j] == 1)
            {
                adj[i]++;
            }
        }
    }
}

void recursiveFuncWay(int** matr, int* rec, int size, int st)
{
    if (st == size)
    {
        return;
    }

    for (int i = 0; i < size; i++)
    {
        if ((matr[st][i] == 1) && (i != st))
        {
            rec[st]++;
        }
    }
    st++;
    recursiveFuncWay(matr, rec, size, st);
}

void Task_2()
{
    // инициализация переменных
    int** matr = nullptr;
    int* adjacencyLinks = nullptr;
    int* recursiveLinks = nullptr;
    int userSize = 0;

    // ввод количества графов пользователем
    while (userSize <= 0 || userSize > 27)
    {
        std::cout << "Введите количество графов (1..26): ";
        std::cin >> userSize;
    }

    // инициализация массивов
    matr = initMatr2D(matr, userSize);
    std::cout << "Матрица смежности:\n";
    printMatr(matr, userSize);
    adjacencyLinks = initMas1D(adjacencyLinks, userSize);
    recursiveLinks = initMas1D(recursiveLinks, userSize);

    // задание a
    recursiveFuncWay(matr, recursiveLinks, userSize, 0);

    // задание b
    adjacencyMatrixWay(matr, adjacencyLinks, userSize);

    // вывод на экран количества вершин
    printMass(recursiveLinks, adjacencyLinks, userSize);

    // удаление памяти
    recursiveLinks = delMas1D(recursiveLinks);
    adjacencyLinks = delMas1D(adjacencyLinks);
    matr = delMatr2D(matr, userSize);

	return;
}