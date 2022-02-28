/*
    2. ���������� ����� ��������� �������. ��� ������� ������� ���� � ������������ �������.
    ����� ������ ���� ���� ����� ��������� � ���������� ���������� ������ �� ������ �� �����
    ����� (����������� ������).
        a) ����� ����� ����������� �������� (� ��������� ������ ������� �� ��������� ������)
        b) ����� ����� �� ������� ��������� (� ��������� ���� ������ �����) � ����� ������
        ������� ��� ������������ ������ ���� ����� � ������� ���������� ���������� ������ �� ���.
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
    // ������������� ����������
    int** matr = nullptr;
    int* adjacencyLinks = nullptr;
    int* recursiveLinks = nullptr;
    int userSize = 0;

    // ���� ���������� ������ �������������
    while (userSize <= 0 || userSize > 27)
    {
        std::cout << "������� ���������� ������ (1..26): ";
        std::cin >> userSize;
    }

    // ������������� ��������
    matr = initMatr2D(matr, userSize);
    std::cout << "������� ���������:\n";
    printMatr(matr, userSize);
    adjacencyLinks = initMas1D(adjacencyLinks, userSize);
    recursiveLinks = initMas1D(recursiveLinks, userSize);

    // ������� a
    recursiveFuncWay(matr, recursiveLinks, userSize, 0);

    // ������� b
    adjacencyMatrixWay(matr, adjacencyLinks, userSize);

    // ����� �� ����� ���������� ������
    printMass(recursiveLinks, adjacencyLinks, userSize);

    // �������� ������
    recursiveLinks = delMas1D(recursiveLinks);
    adjacencyLinks = delMas1D(adjacencyLinks);
    matr = delMatr2D(matr, userSize);

	return;
}