#pragma once

// ��������� ���� �����
typedef struct Node
{
    char dat;
    struct Node* next;
} Node;

// ��������� ������ �����
typedef struct
{
    Node* head;
    int size;
} Stack;

extern void Task_1();