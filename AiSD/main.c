#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sort.h"
#include "menu.h"
#include "Timer.h"

// MANUAL
void manual_data_load(int n, int* p, int* q)
{
    printf("Podaj liczby: \n");
    for (int i = 0; i < n; i++)
    {
        printf("%d.: ", i + 1);
        scanf("%d", &p[i]);
    }
    memcpy(q, p, n * sizeof(int));
}
// ---------------------------------------------------
// AUTO
int auto_data_load(int n, int* p, int* q)
{
    int max, min;
    printf("Podaj minimaln¹ wartoœæ liczb: ");
    scanf("%d", &min);
    printf("Podaj maksymaln¹ wartoœæ liczb: ");
    scanf("%d", &max);
    if (min > max)
    {
        printf("\nWartoœæ minimalna wiêksza od maksymalnej!\nPrzedzia³y zostan¹ zamienione kolejnoœci¹.\n\n");
        int temp = max;
        max = min;
        min = temp;
    }
    for (int i = 0; i < n; i++)
        p[i] = (rand() % (max-min+1)) + min;
    memcpy(q, p, n * sizeof(int));

    if (abs(min) > 9999 || abs(max) > 9999)
        return 1;
    return 0;
}

void stress_test(int n, int* p, int* q, unsigned int iterations, double* avg_bubble, double* avg_quick)
{
    int* p_copy = (int*)malloc(n * sizeof(int));
    int* q_copy = (int*)malloc(n * sizeof(int));
    double sum_bubble = 0.0;
    double sum_quick = 0.0;
    for (unsigned int i = 0; i < iterations; i++)
    {
        double czas_alg = 0.0;
        if (i < iterations - 1)
        {
            memcpy(p_copy, p, n * sizeof(int));
            StartCounter();
            bubblesort(p_copy, n);
            czas_alg = GetCounter();
        }
        else
        {
            StartCounter();
            bubblesort(p, n);
            czas_alg = GetCounter();
        }

        if (iterations < 6 && (n > 250 || n < 50))
            printf("%u. B¹belkowy: %lf ms\n", i + 1, czas_alg);
        sum_bubble += czas_alg;
    }
    printf("\n");
    for (unsigned int i = 0; i < iterations; i++)
    {
        double czas_alg = 0.0;
        if (i < iterations - 1)
        {
            memcpy(q_copy, q, n * sizeof(int));
            StartCounter();
            quicksort(q_copy, 0, n - 1);
            czas_alg = GetCounter();
        }
        else
        {
            StartCounter();
            quicksort(q, 0, n - 1);
            czas_alg = GetCounter();
        }

        if(iterations < 6 && (n > 250 || n < 50))
            printf("%u. Quicksort: %lf ms\n", i+1, czas_alg);
        sum_quick += czas_alg;
    }

    *avg_bubble = sum_bubble / iterations;
    *avg_quick = sum_quick / iterations;
    
    free(p_copy);
    free(q_copy);
}

void compare_times(double avg_bubble, double avg_quick)
{
    double diff = avg_bubble - avg_quick;
    if (diff > 0.0)
        printf("Ró¿nica wynosi %lf ms na korzyœæ sortowania Quicksort", diff);
    else if(diff < 0.0)
        printf("Ró¿nica wynosi %lf ms na korzyœæ sortowania b¹belkowego", diff * -1);
    else
        printf("Algorytmy osi¹gnê³y takie same czasy");

}

void load_iterations(int* iterations)
{
    int temp;
    do
    {
        printf("Podaj iloœæ pomiarów: ");
        scanf("%d", &temp);
        if (temp <= 0)
            printf("Wartoœæ musi byæ dodatnia!\n");

    } while (temp <= 0);
    *iterations = temp;
}
// ---------------------------------------------------
void display_sorted(int n, int* p, int* q)
{
    printf("\nPosortowane b¹belkowo: \n");
    for (int i = 0; i < n; i++)
        printf("%d ", p[i]);
    printf("\n");
    printf("\nPosortowane quicksort: \n");
    for (int i = 0; i < n; i++)
        printf("%d ", q[i]);
    printf("\n");
}

void load_quantity(int* n)
{
    int temp;
    do
    {
        printf("Podaj iloœæ liczb: ");
        scanf("%d", &temp);
        if (temp<=0)
            printf("Wartoœæ musi byæ dodatnia!\n");
    } while (temp<=0);
    *n = temp;
}

int *allocate_memory(int n)
{
    int* ptr = (int*)malloc(n * sizeof(int));
    return ptr;
}

int main()
{
    system("CHCP 1250 >NUL"); //polskie znaki w konsoli
    system("mode 150,40");

    unsigned short mode; //? 1XX-rêczny, 2XX-generowanie, X0X-bez_pliku, X1X-z_plikiem, XX0-bez_czasu, XX1-z_czasem, 777 - exit
    int quantity; //iloœæ liczb
    int big_min_max;
    unsigned int iterations;

    double avg_bubble;
    double avg_quick;


    int* p = NULL;
    int* q = NULL;


    do
    {
        menu_main(&mode);

        if (mode == 100)
        {
            menu_header();
            printf("RÊCZNE WCZYTYWANIE LICZB\n");
            printf("------------------------\n\n");
            load_quantity(&quantity);
            p = allocate_memory(quantity);
            q = allocate_memory(quantity);
            manual_data_load(quantity, p, q);
            printf("\nTrwa sortowanie...\n");
            bubblesort(p, quantity);
            quicksort(q, 0, quantity - 1);
            display_sorted(quantity, p, q);
            free(p);
            free(q);
        }
        else if (mode == 211)
        {
            menu_header();
            // wszsytko
        }
        else if (mode == 210)
        {
            menu_header();
            // plik
        }
        else if (mode == 201)
        {
            menu_header();
            printf("AUTOMATYCZNE GENEROWANIE LICZB\n");
            printf("------------------------------\n\n");
            load_quantity(&quantity);
            p = allocate_memory(quantity);
            q = allocate_memory(quantity);

            big_min_max = auto_data_load(quantity, p, q);
            load_iterations(&iterations);
            printf("\nTrwa sortowanie...\n\n");
            stress_test(quantity, p, q, iterations, &avg_bubble, &avg_quick);
            if(quantity <= 200 && !big_min_max)
                display_sorted(quantity, p, q);
            printf("\nŒr. prêdkoœæ algorytmu b¹belkowego: %lf ms\n", avg_bubble);
            printf("Œr. prêdkoœæ algorytmu Quicksort: %lf ms\n\n", avg_quick);
            compare_times(avg_bubble, avg_quick);
            free(p);
            free(q);
        }
        else if (mode == 777) return 0;

        printf("\n\n\n");
        system("pause");
    } while (1);

    return 0;
}