/*
    1. �������� ������� ����������� �������� �� ���������� � �� �������� ������ ���������������� �
    �������� ���������, �������:
        a) ������� [50] �������� �� [10000] ����� � �������� ���� ���������� ��������������
        ����������;
        b) ����������, ����� ������� �� ��������� �������� �������� �����������������.
    2. �������� ����������� ������� ��������� ������ � ������ ���������� � �����, � �� � �������.
*/

#include <iostream>
#include <conio.h>

typedef struct Node
{
    int key;
    struct Node* left;
    struct Node* right;
} TreeNode;

TreeNode* treeInsert(TreeNode* t, int data)
{
    TreeNode* newNode;
    newNode = new TreeNode;
    newNode->key = data;
    newNode->left = nullptr;
    newNode->right = nullptr;

    TreeNode* current = t;
    TreeNode* parent = t;

    if (t == NULL)
    {
        t = newNode;
    }
    else
    {
        while (current->key != data)
        {
            parent = current;
            if (current->key > data)
            {
                current = current->left;
                if (current == NULL)
                {
                    parent->left = newNode;
                    return t;
                }
            }
            else
            {
                current = current->right;
                if (current == NULL)
                {
                    parent->right = newNode;
                    return t;
                }
            }
        }
    }
    
    return t;
}

void printTree(TreeNode* root)
{
    if (root)
    {
        std::cout << root->key;
        if (root->left || root->right)
        {
            std::cout << "(";
            if (root->left)
            {
                printTree(root->left);
            }
            else
            {
                std::cout << "NULL";
            }
            
            std::cout << ",";

            if (root->right)
            {
                printTree(root->right);
            }
            else
            {
                std::cout << "NULL";
            }
            std::cout << ")";
        }
    }
}

int countNodes(TreeNode* node)
{
    int leftDepth = 0;
    int rightDepth = 0;
    if (node == NULL)
    {
        return 0;
    }
    leftDepth = countNodes(node->left);
    rightDepth = countNodes(node->right);

    return 1 + (leftDepth > rightDepth ? leftDepth : rightDepth);
}

int checkBalance(TreeNode* root)
{
    if (abs(countNodes(root->left) - countNodes(root->right)) <= 1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

bool binSearchRec(TreeNode* root, int key)
{
    bool keyFound = false;
    if (root == NULL)
    {
        return false;
    }
    if (root->key == key)
    {
        return true;
    }
    if (root->key > key)
    {
        keyFound = binSearchRec(root->left, key);
    }
    else
    {
        keyFound = binSearchRec(root->right, key);
    }
    return keyFound;
}

TreeNode* delTree(TreeNode* node)
{
    if (node == NULL)
    {
        return nullptr;
    }
    
    if (node->left != NULL)
    {
        node->left = delTree(node->left);
    }

    if (node->right != NULL)
    {
        node->right = delTree(node->right);
    }

    delete node;
    return nullptr;
}

void Task_1()
{
    int counter = 0;
    int counterBalanced = 0;

    while (counter++ < 50)
    {
        TreeNode* tree = nullptr;

        tree = treeInsert(tree, rand() % 10'000);
        for (int i = 1; i < 10'000; i++)
        {
            treeInsert(tree, rand() % 10'000);
        }
        counterBalanced += checkBalance(tree);
        tree = delTree(tree);
    }
    std::cout << "������� ���������������� ��������: " << counterBalanced / 0.5 << "%.\n";
}

void Task_2()
{
    TreeNode* tree = nullptr;
    unsigned int treeSize = 0;
    int userKey = 0;

    std::cout << "������� ���������� ����� ������ (���� ������������ ��������): ";
    std::cin >> treeSize;
    std::cout << "������� ���� ��� ������ � �������� ������ (0..99): ";
    std::cin >> userKey;

    tree = treeInsert(tree, rand() % 100);
    for (int i = 1; i < treeSize; i++)
    {
        treeInsert(tree, rand() % 100);
    }
    printTree(tree);

    if (binSearchRec(tree, userKey))
    {
        std::cout << "\n���� " << userKey << " � ������ ������!\n";
    }
    else
    {
        std::cout << "\n���� " << userKey << " � ������ �� ������!\n";
    }

    tree = delTree(tree);
}

int main()
{
    setlocale(LC_ALL, "Russian");
    srand(time(0ULL));

    char answer = '0';

    do
    {
        std::cout << "�������� ������� ��� ��������, ����� ��������������� ������� �� ����������:\n\t1. �������� ��������� ������;\n\t2. �������� �����;\n\t0. ����� �� ���������\n";
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