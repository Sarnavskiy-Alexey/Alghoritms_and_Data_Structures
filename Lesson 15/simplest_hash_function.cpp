/*
    1. Реализовать простейшую хеш-функцию. На вход функции подается строка, на выходе сумма кодов
    символов.
*/
#include <iostream>
#include <iomanip>

typedef std::string K;
typedef int htIndex;

int htSize;

typedef struct OneLinkNode {
    K dat;
    struct OneLinkNode* next;
} OneLinkNode;

void fillIntRandom(int* array, int size, int border)
{
    for (int i = 0; i < size; i++)
    {
        array[i] = rand() % border;
    }
}

//htIndex hash(char data)
//{
//    return data % htSize;
//}

htIndex hash(K data)
{
    int size = data.size();
    int h = 0;
    for (int i = 0; i < size; i++)
    {
        h += (int)data[i];
        if (i % 30 == 0)
        {
            h %= 3;
        }
    }
    return h % 3;
}

bool insertNode(OneLinkNode** table, K data)
{
    OneLinkNode* p;
    OneLinkNode* p0;

    htIndex bucket = hash(data);
    p = new OneLinkNode;
    if (p == NULL)
    {
        std::cout << "Out of memory! \n";
        return false;
    }

    p0 = table[bucket];
    table[bucket] = p;
    p->next = p0;
    p->dat = data;

    return true;
}

void printTable(OneLinkNode** table, int size)
{
    OneLinkNode* p;
    for (int i = 0; i < size; i++)
    {
        std::cout << i << ": ";
        p = table[i];
        while (p != nullptr)
        {
            std::cout << p->dat << " // ";
            p = p->next;
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

OneLinkNode** initHashTable(OneLinkNode** table, int size)
{
    table = new OneLinkNode * [htSize];
    for (int i = 0; i < htSize; i++)
    {
        table[i] = new OneLinkNode;
        table[i] = nullptr;
    }

    return table;
}

int main()
{
    htSize = 3;
    const int SZ = 5;
    K someStrings[SZ] = {"Wake me up when September ends", "Hello, World!", "War is peace", "Freedom is slavery", "Ignorance is strength"};

    OneLinkNode** hashTable = nullptr;
    hashTable = initHashTable(hashTable, htSize);
    for (int i = 0; i < SZ; i++)
    {
        insertNode(hashTable, someStrings[i]);
    }

    printTable(hashTable, htSize);

    return 0;
}