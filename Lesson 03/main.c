#include <stdio.h>

typedef enum
{
    FALSE = 0,
    TRUE = 1
} boolean;

int main()
{
    int i = 2;
    int a = 0;
    boolean is_simple = TRUE;

    printf("Enter number: ");
    scanf("%d", &a);

    if (a > 1)
    {
        while (i <= a / 2 && is_simple == TRUE)
        {
            if (a % i == 0)
            {
                is_simple = FALSE;
            }
            i++;
        }
    }
    else
    {
        is_simple = FALSE;
    }

    if (is_simple == FALSE)
    {
        printf("The number %i is not simple!", a);
    }
    else
    {
        printf("The number %i is simple!", a);
    }
    return 0;
}
