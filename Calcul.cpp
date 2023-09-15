#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>


struct Data_for_square
{
    double a;
    double b;
    double c;

    double x1;
    double x2;

    int num_of_roots;
};

int welcom();
void clean_buff();
void solve_square_eq();
void running_tests();
void begin_solve_square();
void print_roots(struct Data_for_square* data);
int solve_square(struct Data_for_square* data);
int solve_lin_eq(double b, double c, double* x1);
int check_solv(struct Data_for_square data_ref, int num_of_exam);
int is_zero(double a);
int is_equal(double a, double b);

int const NUM_OF_TESTS = 11U;          // количество тестов
int const INF_NUM_OF_ROOTS = -1;     // используется при бесконечном числе корней
double const ACCURACY = 0.000001;   // точность

int main()
{
    //solve_square_eq();
    running_tests();
}

void clean_buff()
{
    while (getchar() != '\n') {}
}

void solve_square_eq()
{
    int flag = welcom();

    if (flag == '0')
    {
        clean_buff();
        begin_solve_square();
        return;
    }
    printf("\nYou enter other value programm will end Goodbay!\n");
    return;
}
int welcom()
{
    printf("If you would like start solve_square enter 0\n"
        "For ending program enter any other valeu\n\n");
    return getchar();
}

void running_tests() // выполняет проверку решения квадратных уравнений на тестах
{
    int flag = 0;
    //                                           a      b     c       x1     x2     num_of_roots
    struct Data_for_square data[NUM_OF_TESTS] = {
                                               {0    , 0    , 0    , NAN  , NAN  , INF_NUM_OF_ROOTS},       //1
                                               {0    , 0    , 10   , NAN  , NAN  , 0               },       //2
                                               {1    , 1    , 1    , NAN  , NAN  , 0               },       //3
                                               {34   , 34   , 34   , NAN  , NAN  , 0               },       //4
                                               {10   , 0    , 10   , NAN  , NAN  , 0               },       //5
                                               {1    , -2   , 1    , 1    , NAN  , 1               },       //6
                                               {1    , 2    , 1    , -1   , NAN  , 1               },       //7
                                               {0    , 4    , 2    , -0.5 , NAN  , 1               },       //8
                                               {0    , 1    , 0    , 0    , NAN  , 1               },       //9
                                               {4    , 5    , 0    , 0    , -1.25, 2               },       //10
                                               {4    , 5    , 1    , -0.25, -1   , 2               }        //11
    };

    for (int i = 0; i < NUM_OF_TESTS; i++)
    {
        flag += check_solv(data[i], i + 1); // нахожу количество неправильно решенных примеров
    }
    printf("%d example of %u successful\n", NUM_OF_TESTS - flag, NUM_OF_TESTS);
    if (flag == 0)
    {
        printf("Thats great!\n");
    }
}

int check_solv(struct Data_for_square data_ref, int num_of_exam) // выполняет проверку одного теста, и выводит ошибку если тест не пройден
{
    struct Data_for_square data = data_ref;
    data.num_of_roots = 0;
    data.x1 = NAN;
    data.x2 = NAN;

    data.num_of_roots = solve_square(&data);

    if (!(is_equal(data.num_of_roots, data_ref.num_of_roots) && // Эквивалентно если хотя бы одно из значений не равно
        is_equal(data.x1, data_ref.x1) &&
        is_equal(data.x2, data_ref.x2)))
    {
        printf("Example number %d\n", num_of_exam);
        printf("Expected x1 = %lg, x2 = %lg, nRoots = %d\n", data_ref.x1, data_ref.x2, data_ref.num_of_roots);
        printf("Return   x1 = %lg, x2 = %lg, nRoots = %d\n", data.x1, data.x2, data.num_of_roots);
        return 1;
    }
    return 0;
}

void begin_solve_square() // программа решающая уравнение вводимое с клавиатуры
{
    struct Data_for_square data = {};
    printf("# Solve of square equation: DVT, 2023, ACCURACY is %f\n\n", ACCURACY);

    printf("#Square equation is a*x^2+b*x+c:\n"
        "Please enter a b c\n");

    while (scanf_s("%lg %lg %lg", &data.a, &data.b, &data.c) != 3)
    {
        printf("Please enter 3 numbers\n");
        clean_buff();
    }
    printf("You entered the equation % f*x^2%+f*x%+f = 0\n", data.a, data.b, data.c);
    data.num_of_roots = solve_square(&data);
    print_roots(&data);
}


int solve_square(struct Data_for_square* data) // решает уравнение возвращяет количество корней, решение записывает в структуру data в х1 и х2
{
    assert(isfinite(data->a));
    assert(isfinite(data->b));
    assert(isfinite(data->c));
    assert(data != NULL);
    if (is_zero(data->a))
    {
        return solve_lin_eq(data->b, data->c, &(data->x1));
    }

    // a != 0

    double d = data->b * data->b - 4 * data->a * data->c;
    if (d < 0)
    {
        /*data->x1 = 0;
        data->x2 = 0;*/
        return 0;
    }
    if (is_zero(d))
    {
        data->x1 = -(data->b) / (2 * (data->a));
        //data->x2 = 0;
        return 1;
    }
    data->x1 = (-data->b + sqrt(d)) / (2 * data->a);
    data->x2 = (-data->b - sqrt(d)) / (2 * data->a);
    return 2;
}

int solve_lin_eq(double  b, double  c, double* x1)
{
    if (is_zero(c))
    {
        if (is_zero(b)) return INF_NUM_OF_ROOTS;
        *x1 = 0;
        return 1;
    }
    if (is_zero(b))
    {
        return 0;
    }
    *x1 = -c / b;
    return 1;
}

int is_zero(double a)
{
    return fabs(a) < ACCURACY;
}

int is_equal(double a, double b)
{
    if (isnan(a))
    {
        return isnan(b) ? 1 : 0;
    }
    return isnan(b) ? 0 : (fabs(a - b) < ACCURACY);
}

void print_roots(struct Data_for_square* data)
{
    switch (data->num_of_roots)
    {
    case 0:
        printf("Your's equation has no roots\n");
        break;

    case 1:
        printf("x = %lg\n", data->x1);
        break;

    case 2:
        printf("x1 = %lg, x2 = %lg\n", data->x1, data->x2);
        break;

    case INF_NUM_OF_ROOTS:
        printf("Root of your equation is any number");
        break;

    default:
        printf("main(): ERROR: nRoots = %d\n", data->num_of_roots);
        return;
    }
}
