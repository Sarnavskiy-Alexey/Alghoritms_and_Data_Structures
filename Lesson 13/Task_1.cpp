/*
    1. ����������� ����� � ������� � �������������� �����
*/

#include <iostream>
#include "Task_1.h"
#include "massives.h"

// ������������� �����
void init(Stack* stack)
{
    stack->head = NULL;
    stack->size = 0;
}

// ������� ���������� ������ � ����
bool push(Stack* stack, char data)
{
    Node* tmp = new Node;
    if (tmp == NULL)
    {
        std::cout << "\n���� ����������!\n";
        return false;
    }
    tmp->dat = data;
    tmp->next = stack->head;

    stack->head = tmp;
    stack->size++;
    return true;
}

// ������� ���������� ������ �� �����
char pop(Stack* stack)
{
    if (stack->head == NULL)
    {
        std::cout << "\n���� ����!\n";
        return -1;
    }

    Node* tmp = stack->head;
    char data = tmp->dat;
    stack->head = tmp->next;
    stack->size--;

    delete tmp;
    return data;
}

// ������� ������ ������� ������������� ��������
int getUnvisitedElement(int** matr, bool* vis, int size, int el)
{
    for (int i = 0; i < size; i++)
    {
        if (matr[el][i] == 1 && !vis[i])
        {
            return i;
        }
    }
    return -1;
}

// ������� ������ � ������� � �������������� �����
void depthTraversStack(int** matr, bool* vis, int size, int st)
{
    // �������� �����
    Stack* stack = new Stack;
    init(stack);

    // ������ ������� ��� ������ ��������� �� ����� � ���������� ��� "����������", ��������� � ����
    vis[st] = 1;
    std::cout << (char)(st + 65) << " ";
    push(stack, st);

    // ���� ������ � �������
    while (stack->size > 0)
    {
        int v = getUnvisitedElement(matr, vis, size, stack->head->dat);
        if (v == -1)
        {
            pop(stack);
        }
        else
        {
            vis[v] = true;
            std::cout << (char)(v + 65) << " ";
            push(stack, v);
        }
    }
    std::cout << std::endl;

    // ��������� ������� ���������� ��������� � �������� �����
    resetArr(vis, size);
    delete stack;

    return;
}

void Task_1()
{
    // ������������� ����������
    int** matr = nullptr;
    bool* visited = nullptr;
    int userSize = 0;
    int userSt = -2;

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
    visited = initMas1D(visited, userSize);

    do
    {
        // ���� ������ ����� �������������
        while (userSt < -1 || userSt >= userSize)
        {
            std::cout << "������� ����� �����, � �������� �������� �����, \'-1\' ��� ������: ";
            std::cin >> userSt;
        }

        if (userSt != -1)
        {
            // ���������� �������� ������� �������
            depthTraversStack(matr, visited, userSize, userSt);
            std::cout << std::endl;
            userSt = -2;
        }
    } while (userSt != -1);

    // �������� ������
    visited = delMas1D(visited);
    matr = delMatr2D(matr, userSize);

    return;
}