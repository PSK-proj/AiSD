#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sort.h"
#include "menu.h"

void display_sorted(int n, int* p, int* q)
{
    printf("\nPosortowane b¹belkowo: \n");
    for (int i = 0; i < n; i++)
        printf("%d ", p[i]);
    printf("\n");
    printf("\nPosortowane quicksort: \n");
    for (int i = 0; i < n; i++)
        printf("%d ", q[i]);
}

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

void load_quantity(int* n)
{
    int temp;
    do
    {
        printf("Podaj iloœæ liczb: ");
        scanf("%d", &temp);
        if (temp<=0)
        {
            system("cls");
            printf("Wartoœæ musi byæ dodatnia!\n");
        }
    } while (temp<=0);
    *n = temp;
}

int main()
{
    system("CHCP 1250 >NUL"); //polskie znaki w konsoli
    system("mode 150,40");

    unsigned short mode; //? 1XX-rêczny, 2XX-generowanie, X0X-bez_pliku, X1X-z_plikiem, XX0-bez_czasu, XX1-z_czasem, 777 - exit
    unsigned int quantity; //iloœæ liczb

    menu_main(&mode);

    // ALOKOWANIE TABLIC DYNAMICZNYCH
    load_quantity(&quantity);
    int* p = NULL;
    int* q = NULL;
    p = (int*)malloc(quantity * sizeof(int));
    q = (int*)malloc(quantity * sizeof(int));
    //----------------------------------------

    manual_data_load(quantity, p, q);
    bubblesort(p, quantity);
    quicksort(q, 0, quantity - 1);
    display_sorted(quantity, p, q);

    free(p);
    free(q);

    printf("\n\n\n");
    system("pause");

    return 0;
}