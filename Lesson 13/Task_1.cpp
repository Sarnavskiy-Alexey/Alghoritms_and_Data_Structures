/*
    1. Реализовать обход в глубину с использованием стека
*/

#include <iostream>
#include "Task_1.h"
#include "massives.h"

// инициализация стека
void init(Stack* stack)
{
    stack->head = NULL;
    stack->size = 0;
}

// функция добавления данных в стек
bool push(Stack* stack, char data)
{
    Node* tmp = new Node;
    if (tmp == NULL)
    {
        std::cout << "\nСтек переполнен!\n";
        return false;
    }
    tmp->dat = data;
    tmp->next = stack->head;

    stack->head = tmp;
    stack->size++;
    return true;
}

// функция извлечения данных из стека
char pop(Stack* stack)
{
    if (stack->head == NULL)
    {
        std::cout << "\nСтек пуст!\n";
        return -1;
    }

    Node* tmp = stack->head;
    char data = tmp->dat;
    stack->head = tmp->next;
    stack->size--;

    delete tmp;
    return data;
}

// функция взятия индекса непосещенного элемента
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

// функция обхода в глубину с использованием стека
void depthTraversStack(int** matr, bool* vis, int size, int st)
{
    // создание стека
    Stack* stack = new Stack;
    init(stack);

    // первый элемент при обходе выводится на экран и отмечается как "посещенный", помещаясь в стек
    vis[st] = 1;
    std::cout << (char)(st + 65) << " ";
    push(stack, st);

    // цикл обхода в глубину
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

    // обнуление массива посещенных элементов и удаление стэка
    resetArr(vis, size);
    delete stack;

    return;
}

void Task_1()
{
    // инициализация переменных
    int** matr = nullptr;
    bool* visited = nullptr;
    int userSize = 0;
    int userSt = -2;

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
    visited = initMas1D(visited, userSize);

    do
    {
        // ввод номера графа пользователем
        while (userSt < -1 || userSt >= userSize)
        {
            std::cout << "Введите номер графа, с которого начнется обход, \'-1\' для выхода: ";
            std::cin >> userSt;
        }

        if (userSt != -1)
        {
            // выполнение основной функции задания
            depthTraversStack(matr, visited, userSize, userSt);
            std::cout << std::endl;
            userSt = -2;
        }
    } while (userSt != -1);

    // удаление памяти
    visited = delMas1D(visited);
    matr = delMatr2D(matr, userSize);

    return;
}