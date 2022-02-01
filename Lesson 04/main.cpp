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

#include <iostream>
#include <conio.h>
#include <iomanip>

#define BITS_COUNT 33U
#define BARRIER_NUMBER 0U
// макрос возврата значения на единицу меньше
#define LAST(a) (a - 1U)
#define MAXNUM(a, b) (a > b ? a : b)

typedef unsigned int T_UI;

typedef struct
{
    T_UI row;
    T_UI column;
} Coords;

// функция преобразования числа из десятичного в двоичное представление (n должно задаваться нулем при вызове из другой функции)
void from_10_to_binary(const T_UI number, char* binary, const T_UI size, const T_UI n = 0)
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
double pow_1(const double row, const T_UI p)
{
    if (p == 0)
    {
        return 1.0;
    }
    else
    {
        return row * pow_1(row, p - 1U);
    }
}

// функция возведения в степень согласно свойству четности степени
double pow_2(const double row, const T_UI p)
{
    if (p == 0)
    {
        return 1.0;
    }
    else if (p % 2 == 0)
    {
        return pow_2(row * row, p / 2U);
    }
    else
    {
        return row * pow_2(row, p - 1U);
    }
}

// функция нахождения количества ходов до клетки
T_UI Check_Ways_Chess_King(T_UI** m, const T_UI row, const T_UI column)
{
    if (m[row][column] != BARRIER_NUMBER)
    {
        if (row == 0U && column == 0U)
        {
            m[row][column] = 1U;
            return m[row][column];
        }
        else if (m[row][column] != INT_MAX)
        {
            return m[row][column];
        }
        else if (row == 0U)
        {
            m[row][column] = Check_Ways_Chess_King(m, row, LAST(column));
            return m[row][column];
        }
        else if (column == 0U)
        {
            m[row][column] = Check_Ways_Chess_King(m, LAST(row), column);
            return m[row][column];
        }
        else
        {
            m[row][column] = Check_Ways_Chess_King(m, LAST(row), LAST(column)) + Check_Ways_Chess_King(m, LAST(row), column) + Check_Ways_Chess_King(m, row, LAST(column));
            return m[row][column];
        }
    }
    else
    {
        return BARRIER_NUMBER;
    }
}

// выполнение задания №1
void Task_1()
{
    // инициализация переменных
    T_UI user_number = 0U;
    char bits[BITS_COUNT];
    for (T_UI i = 0U; i < BITS_COUNT - 1U; i++)
    {
        bits[i] = '0';
    }
    bool digit_is_null = true;

    // реализация основной логики перевода из десятичной СИ в двоичную
    std::cout << "\nВведите десятичное число: ";
    std::cin >> user_number;

    from_10_to_binary(user_number, bits, BITS_COUNT, 0U);

    std::cout << "Ваше число в бинарном представлении: ";
    if (user_number != 0)
    {
        for (T_UI i = BITS_COUNT - 1U; i > 0; i--)
        {
            if (bits[i - 1] != '0')
            {
                digit_is_null = false;
            }

            if (!digit_is_null)
            {
                std::cout << bits[i - 1];
            }
        }
    }
    else
    {
        std::cout << bits[0U];
    }
    std::cout << std::endl;
}

// выполнение задания №2
void Task_2()
{
    // инициализация переменных
    double a;
    int b;
    double a_powed_1;
    double a_powed_2;

    std::cout << "\nВведите a: ";
    std::cin >> a;
    std::cout << "Введите b: ";
    std::cin >> b;
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

    std::cout << "Результат с помощью метода обычной рекурсии: " << a_powed_1 << "\nРезультат с помощью метода четной степени: " << a_powed_2 << std::endl;
}

// выполнение задания №3
void Task_3()
{
    // инициализация переменных
    T_UI rows = 0U;
    T_UI columns = 0U;
    T_UI way_count = 0U;
    bool correctly_answered = false;
    char answer_3;
    Coords barrier = { 0U, 0U };
    do
    {
        std::cout << "\nВведите максимальный размер поля (строки, столбцы) через пробел (1 <= строки,столбцы <= 13): ";
        std::cin >> rows >> columns;
        if (rows >= 1U && rows <= 13U && columns >= 1U && columns <= 13U)
        {
            correctly_answered = true;
        }
        else
        {
            std::cout << "\nВы ввели неправильный размер поля. Попробуйте еще раз!\n";
        }
    } while (!correctly_answered);

    // выделение памяти под двухмерный массив доски
    T_UI** chess_field = new T_UI * [rows];
    for (T_UI i = 0U; i < rows; i++)
    {
        chess_field[i] = new T_UI[columns];

        // инициализация двухмерного массива значениями INT_MAX
        for (T_UI j = 0U; j < columns; j++)
        {
            chess_field[i][j] = INT_MAX;
        }
    }

    // цикл добавления препятствия
    do
    {
        std::cout << "\nХотите добавить препятствие?(n/y)";
        answer_3 = (char)_getche();

        if (answer_3 == 'y')
        {
            bool b = false;
            do
            {
                std::cout << "\nКоордината строки препятствия: ";
                std::cin >> barrier.row;
                std::cout << "Координата столбца препятствия: ";
                std::cin >> barrier.column;
                if (!(barrier.row == 0 && barrier.column == 0) && (barrier.row >= 0 && barrier.row < rows && barrier.column >= 0 && barrier.column < columns))
                {
                    b = true;
                    std::cout << "Препятствие добавлено!";
                    chess_field[barrier.row][barrier.column] = 0U;
                }
                else
                {
                    std::cout << "Препятствие не добавлено!";
                }
            } while (!b);
        }
    } while (answer_3 == 'y');
    
    way_count = Check_Ways_Chess_King(chess_field, LAST(rows), LAST(columns));
    
    // вывод результата на экран
    std::cout << "\nПоле количества путей короля:\n";
    for (T_UI i = 0U; i < rows; i++, std::cout << std::endl)
    {
        for (T_UI j = 0U; j < columns; j++)
        {
            std::cout << std::setw(MAXNUM(rows, columns)) << chess_field[i][j];
        }
    }
    
    // очистка выделенной памяти
    for (T_UI i = 0U; i < rows; i++)
    {
        delete[] chess_field[i];
    }
    delete[] chess_field;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    char answer = '0';

    do
    {
        std::cout << "Выберите задание для проверки, нажав соответствующую клавишу на клавиатуре:\n\t1. Из десятичного в двоичное;\n\t2. Возвести a в степень b;\n\t3. Количество путей короля;\n\t0. Выход из программы\n";
        std::cout << "Ваш ответ: ";

        answer = (char)_getche();
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
