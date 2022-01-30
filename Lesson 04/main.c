/*
    1. Реализовать функцию перевода чисел из десятичной системы в двоичную, используя рекурсию.
    2. Реализовать функцию возведения числа [a] в степень [b]:
        - Рекурсивно.
        - Рекурсивно, используя свойство чётности степени (то есть, если степень, в которую нужно возвести число,
        чётная, основание возводится в квадрат, а показатель делится на два, а если степень нечётная - результат
        умножается на основание, а показатель уменьшается на единицу)
    3. Реализовать нахождение количества маршрутов шахматного короля с препятствиями (где единица - это наличие
    препятствия, а ноль - свободная для хода клетка)(король начинает путь с клетки 0,0)
 */

#include "stdio.h"
#define BITS_COUNT 33U
#define CHESS_SIZE 8

typedef enum
{
    K_FALSE = 0,
    K_TRUE = 1
} boolean;

typedef struct
{
    int x;
    int y;
} Coords;

// функция преобразования числа из десятичного в двоичное представление (n должно задаваться нулем при вызове из другой функции)
void from_10_to_binary(unsigned int number, char* binary, unsigned int size, unsigned int n)
{
    switch (number)
    {
        case 0: binary[n] = '0'; break;
        case 1: binary[n] = '1'; break;
        default:
        {
            switch (number % 2)
            {
                case 0: binary[n] = '0'; break;
                case 1: binary[n] = '1'; break;
            }
            from_10_to_binary(number / 2U, binary, size, n + 1U);
        }
    }
}

// функция возведения в степень
double pow_1(double x, unsigned int p)
{
    if (p == 0)
    {
        return 1.0;
    }
    else
    {
        return x * pow_1(x, p - 1U);
    }
}

// функция возведения в степень согласно свойству четности степени
double pow_2(double x, unsigned int p)
{
    if (p == 0)
    {
        return 1.0;
    }
    else if (p % 2 == 0)
    {
        return pow_2(x * x, p / 2U);
    }
    else
    {
        return x * pow_2(x, p - 1U);
    }
}

// функция нахождения количества ходов до клетки
void Check_Ways_Chess_King(int m[][CHESS_SIZE], Coords barrier)
{
    m[0][0] = 1;
    for (int i = 0; i < CHESS_SIZE; i++)
    {
        for (int j = 0; j < CHESS_SIZE; j++)
        {
            if (!(i == 0 && j == 0))
            {
                if (m[i][j] != 0)
                {
                    if (i == barrier.x && j == barrier.y)
                    {
                        m[i][j] = 0;
                    }
                    else if (i == 0)
                    {
                        m[i][j] = m[i][j - 1] + 0;
                    }
                    else if (j == 0)
                    {
                        m[i][j] = 0 + m[i - 1][j];
                    }
                    else
                    {
                        m[i][j] = m[i][j - 1] + m[i - 1][j];
                    }
                }
            }
        }
    }
}

// функция инициализации доски
void First_Init_Chess_Desk(int m[][CHESS_SIZE])
{
    m[0][0] = 1;
    for (int i = 0; i < CHESS_SIZE; i++)
    {
        for (int j = 0; j < CHESS_SIZE; j++)
        {
            if (!(i == 0 && j == 0))
            {
                if (i == 0)
                {
                    m[i][j] = m[i][j - 1] + 0;
                }
                else if (j == 0)
                {
                    m[i][j] = 0 + m[i - 1][j];
                }
                else
                {
                    m[i][j] = m[i][j - 1] + m[i - 1][j];
                }
            }
        }
    }
}

// выполнение задания №1
void Task_1()
{
    // инициализация переменных
    unsigned int user_number = 0U;
    char bits[BITS_COUNT];
    unsigned int i = 0U;
    for (i = 0U; i < BITS_COUNT - 1U; i++)
    {
        bits[i] = '0';
    }
    boolean digit_is_null = K_TRUE;

    // реализация основной логики перевода из десятичной СИ в двоичную
    printf("\nEnter your number: ");
    scanf("%d", &user_number);

    from_10_to_binary(user_number, bits, BITS_COUNT, 0U);

    printf("\nYour number in binary is: \n");
    if (user_number != 0)
    {
        for (i = BITS_COUNT - 1U; i > 0; i--)
        {
            if (bits[i - 1] != '0')
            {
                digit_is_null = K_FALSE;
            }

            if (digit_is_null == K_FALSE)
            {
                printf("%c", bits[i - 1]);
            }
        }
    }
    else
    {
        printf("%c", bits[0U]);
    }
    printf("\n");
}

// выполнение задания №2
void Task_2()
{
    // инициализация переменных
    double a;
    int b;
    double a_powed_1;
    double a_powed_2;

    printf("\nEnter a: ");
    scanf("%lf", &a);
    printf("Enter b: ");
    scanf("%d", &b);
    if (b >= 0)
    {
        a_powed_1 = pow_1(a, b);
        a_powed_2 = pow_2(a, b);
    }
    else
    {
        a_powed_1 = pow_1(1.0 / a, -b);
        a_powed_2 = pow_2(1.0 / a, -b);
    }

    printf("Powed number by first method: %lf\nPowed number by second method: %lf\n", a_powed_1, a_powed_2);
}

// выполнение задания №3
void Task_3()
{
    // инициализация переменных
    int chess[CHESS_SIZE][CHESS_SIZE];
    for (int i = 0; i < CHESS_SIZE; i++)
    {
        for (int j = 0; j < CHESS_SIZE; j++)
        {
            chess[i][j] = 0;
        }
    }
    char answer_3 = 'n';
    Coords barrier = { 0, 0 };

    First_Init_Chess_Desk(chess);
    do
    {
        printf("Do you want to add barrier?(n/y)");
        fseek(stdin, 0, SEEK_END);
        scanf("%c", &answer_3);

        if (answer_3 == 'y')
        {
            boolean b = K_FALSE;
            do
            {
                printf("X-coordinate: ");
                scanf("%d", &barrier.x);
                printf("Y-coordinate: ");
                scanf("%d", &barrier.y);
                if (!(barrier.x == 0 && barrier.y == 0) && (barrier.x >= 0 && barrier.x < CHESS_SIZE && barrier.y >= 0 && barrier.y < CHESS_SIZE))
                {
                    b = K_TRUE;
                }
            } while (b == K_FALSE);
            Check_Ways_Chess_King(chess, barrier);
        }
    } while (answer_3 == 'y');

    for (int i = 0; i < CHESS_SIZE; i++)
    {
        for (int j = 0; j < CHESS_SIZE; j++)
        {
            printf("%d ", chess[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    char answer = '0';

    do
    {
        printf("Choose the task to check by tapping appropriate key on the keyboard:\n\t1. From decimal to binary;\n\t2. Pow a in b;\n\t3. Ways of the Chess King;\n\t0. Exit");
        printf("\nYour answer: ");
        fseek(stdin, 0, SEEK_END);
        scanf("%c", &answer);
        switch (answer)
        {
            case '1': Task_1(); break;
            case '2': Task_2(); break;
            case '3': Task_3(); break;
            case '0': break;
            default: printf("\nYou entered wrong key. Try again, please!\n");
        }
    } while (answer != '0');

    return 0;
}
