/*
    2. Имеются монеты номиналом 50, 10, 5, 2, 1 коп. Напишите функцию которая минимальным
    количеством монет наберет сумму 98 коп. Для решения задачи используйте “жадный” алгоритм.
*/
#include <iostream>

int kopecks[] = { 50, 10, 5, 2, 1 };

typedef struct Node
{
    int dat;
    Node* next;
} Node;

typedef struct
{
    Node* head;
    int size;
} List;

List* initQuery(List* lst)
{
    lst = new List;
    lst->head = nullptr;
    lst->size = 0;
    return lst;
}

void ins(List* lst, int data)
{
    Node* new_node = new Node;
    new_node->dat = data;
    new_node->next = nullptr;

    Node* current = lst->head;
    if (current == nullptr)
    {
        lst->head = new_node;
        lst->size++;
        return;
    }
    else
    {
        while (current->next != nullptr)
        {
            current = current->next;
        }
        current->next = new_node;
        lst->size++;
    }
}

Node* rem(List* lst)
{
    if (lst->head == nullptr)
    {
        return nullptr;
    }
    
    Node* current = lst->head;
    lst->head = current->next;
    lst->size--;
    return current;
}

void greedyAlgorithm(List* lst, int kop98)
{
    while (kop98 != 0)
    {
        int a = 0;
        for (int i = 0; i < 5; i++)
        {
            if (kop98 >= kopecks[i])
            {
                a = kopecks[i];
                break;
            }
        }
        kop98 -= a;
        ins(lst, a);
    }

    std::cout << "Результат: ";
    while (lst->head != nullptr)
    {
        std::cout << lst->head->dat << " ";
        rem(lst);
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");
    List* query = nullptr;
    query = initQuery(query);
    greedyAlgorithm(query, 98);

    return 0;
}