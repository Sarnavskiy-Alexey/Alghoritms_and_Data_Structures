/*
    1. Написать программу, которая определяет, является ли введенная скобочная
    последовательность правильной. Примеры правильных скобочных выражений:
    (), ([])(), {}(), ([{}]),
    неправильных — )(, ())({), (, ])}), ([(]) для скобок [,(,{.
    Например: (2+(2*2)) или [2/{5*(4+7)}]
    2. Создать функцию, копирующую односвязный список (без удаления первого списка).
    3. Реализуйте алгоритм, который определяет, отсортирован ли связный список.

Результатом работы должен стать один файл с кодом на языке С, содержащий функцию
main и функции, соответствующие заданиям.
*/

#include <iostream>
#include <string>
#include <conio.h>

typedef struct Node
{
    char dat;
    struct Node* next;
} Node;

typedef struct
{
    Node* head;
    int size;
} Stack;

typedef struct
{
    Node* head;
    int size;
} List;

void init(Stack* stack)
{
    stack->head = NULL;
    stack->size = 0;
}

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

void init(List* lst)
{
    lst->head = NULL;
    lst->size = 0;
}

void ins(List* lst, char data)
{
    Node* tmp = new Node;
    tmp->dat = data;
    tmp->next = NULL;
    
    Node* current = lst->head;
    if (current == NULL)
    {
        lst->head = tmp;
        lst->size++;
    }
    else
    {
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = tmp;
        lst->size++;
    }
}

void printNode(Node* n)
{
    if (n == NULL)
    {
        std::cout << "[]";
        return;
    }
    std::cout << "[" << n->dat << "]";
}

void printList(List* lst)
{
    Node* current = lst->head;
    if (current == NULL)
    {
        printNode(current);
    }
    else
    {
        do
        {
            printNode(current);
            current = current->next;
        } while (current != NULL);
    }
    std::cout << " Size: " << lst->size << std::endl;
}

// функция копирования односвязных списков
void copyList(List* lst_old, List* lst_new)
{
    if (lst_old->head != NULL)
    {
        Node* tmp = new Node;

        tmp = lst_old->head;
        do
        {
            ins(lst_new, tmp->dat);
            tmp = tmp->next;
        } while (tmp != NULL);
    }
}

// функция проверки сортировки списка
bool checkListSorted(List* lst)
{
    bool b = true;
    if (lst->head != NULL && lst->head->next != NULL)
    {
        Node* tmp = lst->head;
        do
        {
            if (tmp->dat > tmp->next->dat)
            {
                b = false;
            }
            tmp = tmp->next;
        } while (b == true && tmp->next != NULL);
    }

    return b;
}

void Task_1()
{
    Stack* stack = new Stack;
    init(stack);

    std::string s;
    std::cout << "Введите скобочную последовательность:" << std::endl;
    getline(std::cin, s);

    bool break_cycle = false;
    for (char c : s)
    {
        break_cycle = false;
        if (c == '[' || c == '{' || c == '(')
        {
            bool b = push(stack, c);
            if (!b)
            {
                break;
            }
        }
        else if (stack->size > 0)
        {
            switch (c)
            {
            case ']':
                if (stack->head->dat == '[')
                    pop(stack);
                else
                    break_cycle = true;
                break;
            case '}':
                if (stack->head->dat == '{')
                    pop(stack);
                else
                    break_cycle = true;
                break;
            case ')':
                if (stack->head->dat == '(')
                    pop(stack);
                else
                    break_cycle = true;
                break;
            }
        }
        else
        {
            break_cycle = true;
        }

        if (break_cycle) break;
    }

    if (stack->size == 0 && !break_cycle)
    {
        std::cout << "Скобочная последовательность правильная!";
    }
    else
    {
        std::cout << "Скобочная последовательность не является правильной!";
    }

    delete stack;
}

void Task_2()
{
    List* lst_old = new List;
    List* lst_new = new List;

    init(lst_old);
    init(lst_new);

    std::string s;
    std::cout << "Введите строку для копирования в список:" << std::endl;
    getline(std::cin, s);

    for (char c : s)
    {
        ins(lst_old, c);
    }

    copyList(lst_old, lst_new);

    std::cout << "Старый список:" << std::endl;
    printList(lst_old);
    std::cout << "Новый список:" << std::endl;
    printList(lst_new);

    delete lst_new;
    delete lst_old;
}

void Task_3()
{
    List* lst = new List;
    init(lst);
    char answer = '0';

    do
    {
        std::cout << "Хотите ввести данные для списка?(y/n) ";
        answer = (char)_getche();
        std::cout << std::endl;

        if (answer == 'y' || answer == 'Y')
        {
            char c;
            std::cout << "Введите символ для записи в список: ";
            c = (char)_getche();
            std::cout << std::endl;
            ins(lst, c);
        }
    } while (answer == 'y' || answer == 'Y');

    std::cout << "Список:" << std::endl;
    printList(lst);

    if (checkListSorted(lst))
    {
        std::cout << "Введен отсортированный список!";
    }
    else
    {
        std::cout << "Введен неотсортированный список!";
    }

    delete lst;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    srand(time(0ULL));

    char answer = '0';

    do
    {
        std::cout << "Выберите задание для проверки, нажав соответствующую клавишу на клавиатуре:\n\t1. Проверка скобочной последовательности;\n\t2. Копирование односвязного списка;\n\t3. Проверка на отсортированность связного списка;\n\t0. Выход из программы\n";
        std::cout << "Ваш ответ: ";

        answer = (char)_getche();
        std::cout << std::endl;
        switch (answer)
        {
        case '1': Task_1(); break;
        case '2': Task_2(); break;
        case '3': Task_3(); break;
        case '0': break;
        default: std::cout << "\nВы нажали неправильную клавишу. Попробуйте еще раз!\n";
        }
        std::cout << "\n***************************************************\n";
    } while (answer != '0');

    return 0;
}
