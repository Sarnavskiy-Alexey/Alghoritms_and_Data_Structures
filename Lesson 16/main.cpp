/*
    1. ����������� ���������� � ����������� ������ � ������������ � ������� ���������� � ������
    2. ����������� ���������� � ����������� �������������� � ������������ � ������� ���������� �
    ����������� ��������
*/
#include <iostream>
#include <string>
#include <conio.h>

char caesarEncryptionChar(char dat)
{
    if (dat >= 'A' && dat <= 'Z')
    {
        return (dat + 3 - 13) % 26 + 65;
    }
    else if (dat >= 'a' && dat <= 'z')
    {
        return (dat + 3 - 19) % 26 + 97;
    }
}

char caesarDecryptionChar(char dat)
{
    if (dat >= 'A' && dat <= 'Z')
    {
        return (dat - 3 - 13) % 26 + 65;
    }
    else if (dat >= 'a' && dat <= 'z')
    {
        return (dat - 3 - 19) % 26 + 97;
    }
}

void caesarWorkEncr()
{
    char answer = 'n';
    do
    {
        std::string str = "";

        std::cout << "\n\t\t������� ������ ��� ����������:\n";
        getline(std::cin, str);
        for (int i = 0; i < str.size(); i++)
        {
            std::cout << caesarEncryptionChar(str[i]);
        }

        std::cout << "\n\t\t������ ����������� ��� ���� ������?(y/n)";
        answer = _getche();
    } while (answer == 'y');
}
void caesarWorkDecr()
{
    char answer = 'n';
    do
    {
        std::string str = "";

        std::cout << "\n\t\t������� ������ ��� �����������:\n";
        getline(std::cin, str);
        for (int i = 0; i < str.size(); i++)
        {
            std::cout << caesarDecryptionChar(str[i]);
        }

        std::cout << "\n\t\t������ ������������ ��� ���� ������?(y/n)";
        answer = _getche();
    } while (answer == 'y');
}

void Task_1()
{
    char answer = '0';

    do
    {
        std::cout << "\n\t�������� ������:\n\t1. ����������� ������;\n\t2. ������������ ������;\n\t0. �����.\n\t��� �����: ";
        answer = _getche();

        switch (answer)
        {
        case '1': caesarWorkEncr(); break;
        case '2': caesarWorkDecr(); break;
        case '0': break;
        default: std::cout << "\n\t�� �������� � ������! ���������� ��� ���!\n";
        }
    } while (answer != '0');

    return;
}

char** initArr2Dchar(char** arr, int rows, int columns)
{
    arr = new char* [rows];
    for (int i = 0; i < rows; i++)
    {
        arr[i] = new char[columns];
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            arr[i][j] = 'X';
        }
    }

    return arr;
}

void printArr2DChar(char** arr, int rows, int columns)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            std::cout << " " << arr[i][j];
        }
        std::cout << std::endl;
    }
}

char** delArr2Dchar(char** arr, int rows)
{
    for (int i = 0; i < rows; i++)
    {
        delete[] arr[i];
    }
    delete[] arr;

    return nullptr;
}

std::string permutationEncryption(std::string str, int columns)
{
    char** permutated = nullptr;
    std::string permutatedStr = "";
    int rows = ceil(double(str.size()) / columns);

    permutated = initArr2Dchar(permutated, rows, columns);

    for (int i = 0; i < str.size(); i++)
    {
        permutated[i / columns][i % columns] = str[i];
    }

    for (int j = 0; j < columns; j++)
    {
        for (int i = 0; i < rows; i++)
        {
            permutatedStr += permutated[i][j];
        }
    }

    permutated = delArr2Dchar(permutated, rows);

    return permutatedStr;
}

std::string permutationDecryption(std::string str, int rows)
{
    char** permutated = nullptr;
    std::string permutatedStr = "";
    int columns = ceil(double(str.size()) / rows);

    permutated = initArr2Dchar(permutated, rows, columns);

    for (int i = 0; i < str.size(); i++)
    {
        permutated[i / columns][i % columns] = str[i];
    }

    for (int j = 0; j < columns; j++)
    {
        for (int i = 0; i < rows; i++)
        {
            permutatedStr += permutated[i][j];
        }
    }

    permutated = delArr2Dchar(permutated, rows);

    return permutatedStr;
}

void Task_2()
{
    char answer = '0';

    do
    {
        std::cout << "\n\t�������� ������:\n\t1. ����������� ������;\n\t2. ������������ ������;\n\t0. �����.\n\t��� �����: ";
        answer = _getche();

        switch (answer)
        {
        case '1':
        {
            std::string str = "";
            std::string encrStr = "";
            int columns = 0;

            std::cout << "\n\t������� ������ ��� ����������:\n";
            while (str.size() < 2)
            {
                getline(std::cin, str);
            }
            
            while (columns < 2)
            {
                std::cout << "\n\t������� ���������� �������� ��� ����������: ";
                std::cin >> columns;
            }
            encrStr = permutationEncryption(str, columns);
            std::cout << "\n\t������������� ������:\n\t" << encrStr;
            
            break;
        }
        case '2':
        {
            std::string str = "";
            std::string decrStr = "";
            int rows = 0;

            std::cout << "\n\t������� ������ ��� �����������:\n";
            while (str.size() < 2)
            {
                getline(std::cin, str);
            }

            while (rows < 2)
            {
                std::cout << "\n\t������� ���������� ��������, �������������� ��� ����������: ";
                std::cin >> rows;
            }
            decrStr = permutationDecryption(str, rows);
            std::cout << "\n\t�������������� ������:\n\t" << decrStr;

            break;
        }
        case '0': break;
        default: std::cout << "\n\t�� �������� � ������! ���������� ��� ���!\n";
        }
    } while (answer != '0');

    return;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    
    char answer = '0';
    do
    {
        std::cout << "�������� �������:\n1. ���� ������;\n2. ���� �������������;\n0. �����.\n��� �����: ";
        answer = _getche();

        switch (answer)
        {
        case '1': Task_1(); break;
        case '2': Task_2(); break;
        case '0': break;
        default: std::cout << "\n�� �������� � ������!\n";
        }
        std::cout << "\n**********************************************************\n";
    } while (answer != '0');

    return 0;
}