#pragma once

// структура узла стека
typedef struct Node
{
    char dat;
    struct Node* next;
} Node;

// структура головы стека
typedef struct
{
    Node* head;
    int size;
} Stack;

extern void Task_1();