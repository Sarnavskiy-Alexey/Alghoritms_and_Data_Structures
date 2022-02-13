/*
    1. ������� ������� � ������������ �����������
    2. ����������� ������� �� ���������� � �������� ������� ��������� � �������������� �����.

    ����������� ������ ������ ����� ���� ���� � ����� �� ����� �, ���������� ������� main, �
    ����� �������, ����������� ��� ������ ������������ ������� � �������� ������ ���������

*/

#include <iostream>
#include <conio.h>
#include <iomanip>

// ���������������
#define SZ 5
#define SIZE 33

// �������
#define CHECK_RANGE(a, l, r) (((a >= l) && (a <= r)) ? true : false)

typedef struct
{
    int pr;
    int dat;
} Node;

int head;
int tail;
int items;

void init(Node* arr)
{
    for (int i = 0; i < SZ; i++)
    {
        arr[i] = { NULL, NULL };
    }
    head = 0;
    tail = 0;
    items = 0;
}

void ins(Node* arr, int pr, int dat)
{
    Node* node = new Node;
    node->pr = pr;
    node->dat = dat;

    if (items == SZ)
    {
        std::cout << "\nQueue is full!\n";
    }
    else
    {
        arr[(tail++) % SZ] = *node;
        items++;
    }
}

Node* rem(Node* arr)
{
    if (items == 0)
    {
        return NULL;
    }
    else
    {
        int idx;
        int max_pr = -1;
        int headx = head;
        int tailx = (head < tail) ? tail : tail + SZ;
        Node* tmp = NULL;

        for (idx = headx; idx != tailx; idx++)
        {
            max_pr = (arr[idx % SZ].pr < max_pr) ? max_pr : arr[idx % SZ].pr;
        }

        for (idx = headx; idx != tailx; idx++)
        {
            if (max_pr == arr[idx % SZ].pr)
            {
                break;
            }
        }

        for (int i = idx; i != headx; i--)
        {
            tmp = &arr[i % SZ];
            arr[i % SZ] = arr[(i - 1) % SZ];
            arr[(i - 1) % SZ] = *tmp;
        }
        tmp = NULL;
        arr[headx % SZ] = { NULL,NULL };
        head++;
        items--;

        return tmp;
    }
}

void printQueue(Node* arr)
{
    std::cout << "\n[ ";
    for (int i = 0; i < SZ; i++)
    {
        if (arr[i].pr == NULL && arr[i].dat == NULL)
        {
            std::cout << " (*,*) ";
        }
        else
        {
            std::cout << " (" << arr[i].pr << "," << arr[i].dat << ") ";
        }
    }
    std::cout << " ]\n ";
}

void Task_1()
{
    Node* arr = new Node[SZ];

    init(arr);
    char answer = '0';

    do
    {
        std::cout << "\n�������� ��������:\n\t1. �������� ������� � �������;\n\t2. ������� ������� �� �������;\n\t3. �������� �������;\n\t0. ����� �� ���������\n";
        std::cout << "��� �����: ";

        answer = (char)_getche();
        std::cout << std::endl;
        switch (answer)
        {
        case '1':
        {
            int loc_pr = 0;
            int loc_dat = 0;

            do
            {
                std::cout << "������� ���� (���� >= 1): ";
                std::cin >> loc_pr;
            } while (!(CHECK_RANGE(loc_pr, 1, INT_MAX)));
            std::cout << "������� ������: ";
            std::cin >> loc_dat;

            ins(arr, loc_pr, loc_dat);
            break;
        }
        case '2': rem(arr); break;
        case '3': printQueue(arr); break;
        case '0': break;
        default: std::cout << "\n�� ������ ������������ �������. ���������� ��� ���!\n";
        }
    } while (answer != '0');

    delete[] arr;
}

int cursor = -1;
char Stack[SIZE];

bool push(char data)
{
    if (cursor < SIZE)
    {
        Stack[++cursor] = data;
        return true;
    }
    else
    {
        std::cout << "\nStack overflow!\n";
        return false;
    }
}

char pop()
{
    if (cursor != -1)
    {
        return Stack[cursor--];
    }
    else
    {
        std::cout << "Stack is empty";
        return -1;
    }
}


void Task_2()
{
    int userNumber = 0;

    do
    {
        std::cout << "������� ����� ��� �������� � �������� ������� ��������� (����� >= 0): ";
        std::cin >> userNumber;
    } while (!(CHECK_RANGE(userNumber, 0, INT_MAX)));

    int loc_userNumber = userNumber;
    while (loc_userNumber > 0)
    {
        push((char)(loc_userNumber % 2));
        loc_userNumber /= 2;
    }

    while (cursor >= 0)
    {
        std::cout << (int)pop();
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");
    srand(time(0ULL));

    char answer = '0';

    do
    {
        std::cout << "�������� ������� ��� ��������, ����� ��������������� ������� �� ����������:\n\t1. ������� � ������������ �����������;\n\t2. ������� �� ���������� � �������� ������� ��������� � �������������� �����;\n\t0. ����� �� ���������\n";
        std::cout << "��� �����: ";

        answer = (char)_getche();
        std::cout << std::endl;
        switch (answer)
        {
        case '1': Task_1(); break;
        case '2': Task_2(); break;
        case '0': break;
        default: std::cout << "\n�� ������ ������������ �������. ���������� ��� ���!\n";
        }
        std::cout << "\n***************************************************\n";
    } while (answer != '0');

    return 0;
}
