#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sort.h"
#include "menu.h"
#include "Timer.h"

/**
 * \file   main.h
 * \brief
 * Glowna funkcja programu
 * \author Piotr Miernik, Oskar Olub
 * \date   Maj 2022
 *********************************************************************/

/// <summary>
/// Reczne wczytywanie danych.
/// 
/// Ta funkcja obsluguje zapisywanie do tablicy liczb podanych recznie przez uzytkownika.
/// </summary>
/// <param name="n">Ilosc elementow w tablicy</param>
/// <param name="p">Wskaznik na tablice do sortowania babelkowego</param>
/// <param name="q">Wskaznik na tablice do sortowania Quicksort</param>
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

/// <summary>
/// Automatyczne wczytywanie danych.
/// 
/// Ta funkcja obsluguje zapisywanie do tablicy liczb losowanych z podanego przez uzytkownika zakresu.
/// </summary>
/// <param name="n">Ilosc elementow w tablicy</param>
/// <param name="p">Wskaznik na tablice do sortowania babelkowego</param>
/// <param name="q">Wskaznik na tablice do sortowania Quicksort</param>
/// <returns>Flaga uzycia dlugiej liczby. Funkcja zwraca "1", jesli liczba graniczna zakresu losowania zajmuje 5 lub wiecej znakow. W przeciwnym wypadku zwacana jest wartosc "0"</returns>
int auto_data_load(int n, int* p, int* q)
{
    int max, min;
    printf("Podaj minimaln� warto�� liczb: ");
    scanf("%d", &min);
    printf("Podaj maksymaln� warto�� liczb: ");
    scanf("%d", &max);
    if (min > max)
    {
        printf("\nWarto�� minimalna wi�ksza od maksymalnej!\nPrzedzia�y zostan� zamienione kolejno�ci�.\n\n");
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

/// <summary>
/// Testy wydajnosci.
/// 
/// Ta funkcja odpowiada za przeprowadzenie testow predkosci sortowan.
/// </summary>
/// <param name="n">Ilosc elementow w tablicy</param>
/// <param name="p">Wskaznik na tablice do sortowania babelkowego</param>
/// <param name="q">Wskaznik na tablice do sortowania Quicksort</param>
/// <param name="iterations">Ilosc powtorzen testow czasu sortowania</param>
/// <param name="avg_bubble">Wskaznik na zmienna przechowujaca sredni czas sortowania babelkowego</param>
/// <param name="avg_quick">Wskaznik na zmienna przechowujaca sredni czas sortowania Quicksort</param>
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

        if (iterations < 6 && (n > 201 || n < 50))
            printf("%u. B�belkowy: %lf ms\n", i + 1, czas_alg);
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

        if(iterations < 6 && (n > 201 || n < 50))
            printf("%u. Quicksort: %lf ms\n", i+1, czas_alg);
        sum_quick += czas_alg;
    }

    *avg_bubble = sum_bubble / iterations;
    *avg_quick = sum_quick / iterations;
    
    free(p_copy);
    free(q_copy);
}

/// <summary>
/// Porownanie czasow sortowan.
/// 
/// Ta funkcja porownuje ze soba srednie czasy osiagniete przez funkcje sortujace i wyswietla werdykt.
/// </summary>
/// <param name="avg_bubble">Sredni czas sortowania babelkowego</param>
/// <param name="avg_quick">Sredni czas sortowania Quicksort</param>
void compare_times(double avg_bubble, double avg_quick)
{
    double diff = avg_bubble - avg_quick;
    if (diff > 0.0)
        printf("R�nica wynosi %lf ms na korzy�� sortowania Quicksort", diff);
    else if(diff < 0.0)
        printf("R�nica wynosi %lf ms na korzy�� sortowania b�belkowego", diff * -1);
    else
        printf("Algorytmy osi�gn�y takie same czasy");

}

/// <summary>
/// Wczytanie ilosci pomiarow testow czasu.
/// 
/// Ta funkcja odpowiada za pobranie od uzytkownika ilosci pomiarow, ktore program ma wykonac.
/// </summary>
/// <param name="iterations">Wskaznik na zmienna przechowujaca ilosc pomiarow</param>
void load_iterations(int* iterations)
{
    int temp;
    do
    {
        printf("Podaj ilo�� pomiar�w: ");
        scanf("%d", &temp);
        if (temp <= 0)
            printf("Warto�� musi by� dodatnia!\n");

    } while (temp <= 0);
    *iterations = temp;
}

/// <summary>
/// Obsluga plikow tekstowych.
/// 
/// Funkcja ta jest odpowiedzialna za wszelka obsluge plikow tekstowych. Tworzy plik, jesli takowy nie istnieje, nadpisuje stary plik oraz dopisuje dane do aktywnego pliku w sesji programu.
/// </summary>
/// <param name="n">Ilosc elementow w tablicy</param>
/// <param name="p">Wskaznik na tablice do sortowania babelkowego</param>
/// <param name="q">Wskaznik na tablice do sortowania Quicksort</param>
/// <param name="mode">Tryb pracy programu wybierany w menu</param>
/// <param name="f_w_c">Wskaznik na licznik zapisow do pliku (pozwala na sprawdzenie czy bedzie to pierwszy zapis do pliku)</param>
/// <param name="f_d_c">Wskaznik na licznik zapisanych danych (liczy ilosc operacji wczytywania danych)</param>
/// <param name="avg_bubble">Sredni czas sortowania babelkowego</param>
/// <param name="avg_quick">Sredni czas sortowania Quicksort</param>
void file_handling(int n, int* p, int* q, unsigned short mode, unsigned short* f_w_c, unsigned short* f_d_c, double avg_b, double avg_q)
{
    FILE* fp;
    if (*f_w_c == 0) fp = fopen("dane.txt", "w");
    else fp = fopen("dane.txt", "a");
    if (fp == NULL) printf("B��D OTWARCIA PLIKU\n");
    else
    {
        if (mode == 0)
        {
            printf("\nZapisywanie danych...\n");

            fprintf(fp, "WCZYTYWANIE NR: %hu\n", *f_d_c+1);
            fprintf(fp, "---------------------\n");
            fprintf(fp, "DANE WCZYTANE: \n");
            for (int i = 0; i < n; i++)
                fprintf(fp ,"%d ", p[i]);
            fprintf(fp, "\n\n");
            *f_d_c += 1;
        }
        else if(mode == 1 || mode == 2)
        {
            printf("\nZapisywanie wynik�w...\n");

            fprintf(fp, "Posortowane b�belkowo: \n");
            for (int i = 0; i < n; i++)
                fprintf(fp, "%d ", p[i]);
            fprintf(fp, "\n\n");

            fprintf(fp, "Posortowane quicksort: \n");
            for (int i = 0; i < n; i++)
                fprintf(fp, "%d ", q[i]);
            fprintf(fp, "\n");

            if (mode == 2)
            {
                fprintf(fp, "\n�r. pr�dko�� algorytmu b�belkowego: %lf ms\n", avg_b);
                fprintf(fp, "�r. pr�dko�� algorytmu Quicksort: %lf ms\n\n", avg_q);
                if (avg_b - avg_q > 0.0)
                    fprintf(fp, "R�nica wynosi %lf ms na korzy�� sortowania Quicksort", avg_b - avg_q);
                else if (avg_b - avg_q < 0.0)
                    fprintf(fp, "R�nica wynosi %lf ms na korzy�� sortowania b�belkowego", (avg_b - avg_q) * -1);
                else
                    fprintf(fp, "Algorytmy osi�gn�y takie same czasy");
            }

            fprintf(fp, "\n+============================+\n\n");
        }
        *f_w_c += 1;
        fclose(fp);
    }
}

/// <summary>
/// Wyswietlanie posortowanych tablic.
/// 
/// Funkcja ta wyswietla posortowane tablice.
/// </summary>
/// <param name="n">Wielkosc tablicy</param>
/// <param name="p">Tablica elementow posortowanych babelkowo</param>
/// <param name="q">Tablica elementow posortowanych Quicksortem</param>
void display_sorted(int n, int* p, int* q)
{
    printf("\nPosortowane b�belkowo: \n");
    for (int i = 0; i < n; i++)
        printf("%d ", p[i]);
    printf("\n");
    printf("\nPosortowane quicksort: \n");
    for (int i = 0; i < n; i++)
        printf("%d ", q[i]);
    printf("\n");
}

/// <summary>
/// Wczytywanie wielkosci tablicy.
/// 
/// Funkcja ta odpowiada za pobranie od uzytkownika oczekiwanej przez niego ilosci liczb do posortowania.
/// </summary>
/// <param name="n">Wskaznik na zmienna przechowujaca wielkosc tablicy</param>
void load_quantity(int* n)
{
    int temp;
    do
    {
        printf("Podaj ilo�� liczb: ");
        scanf("%d", &temp);
        if (temp<=0)
            printf("Warto�� musi by� dodatnia!\n");
    } while (temp<=0);
    *n = temp;
}

/// <summary>
/// Tworzenie tablicy donamicznej.
/// 
/// Funkcja ta jest odpowiedzialna za stworzenie dynamicznej tablicy o dlugosci podanej wczesniej przez uzytkownika. Zwraca ona wskaznik na miejsce w pamieci, ktore zostalo dla niej zaalokowane.
/// </summary>
/// <param name="n">Dlugosc tablicy</param>
/// <returns>Wskaznik na miejsce w pamieci, gdzie tablica zostala utowrzona</returns>
int *allocate_memory(int n)
{
    int* ptr = (int*)malloc(n * sizeof(int));
    return ptr;
}

/// <summary>
/// Glowna funkcja programu.
/// </summary>
int main()
{
    system("CHCP 1250 >NUL");
    system("mode 150,40");

    unsigned short mode;
    int quantity;
    
    int big_min_max;
    unsigned int iterations;
    double avg_bubble;
    double avg_quick;

    unsigned short file_writes_count = 0;
    unsigned short file_data_load_count = 0;

    int* p = NULL;
    int* q = NULL;



    do
    {
        menu_main(&mode);

        if (mode == 100)
        {
            menu_header();
            printf("R�CZNE WCZYTYWANIE LICZB\n");
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
            printf("AUTOMATYCZNE GENEROWANIE LICZB (zapis do pliku i testy wydajno�ci)\n");
            printf("------------------------------------------------------------------\n\n");
            load_quantity(&quantity);
            p = allocate_memory(quantity);
            q = allocate_memory(quantity);

            big_min_max = auto_data_load(quantity, p, q);
            load_iterations(&iterations);
            file_handling(quantity, p, q, 0, &file_writes_count, &file_data_load_count, 0.0, 0.0);
            printf("\nTrwa sortowanie...\n");
            stress_test(quantity, p, q, iterations, &avg_bubble, &avg_quick);
            if (quantity <= 200 && !big_min_max)
                display_sorted(quantity, p, q);
            printf("\n�r. pr�dko�� algorytmu b�belkowego: %lf ms\n", avg_bubble);
            printf("�r. pr�dko�� algorytmu Quicksort: %lf ms\n\n", avg_quick);
            compare_times(avg_bubble, avg_quick);
            file_handling(quantity, p, q, 2, &file_writes_count, &file_data_load_count, avg_bubble, avg_quick);
            free(p);
            free(q);
        }
        else if (mode == 210)
        {
            menu_header();
            printf("AUTOMATYCZNE GENEROWANIE LICZB (zapis do pliku)\n");
            printf("-----------------------------------------------\n\n");
            load_quantity(&quantity);
            p = allocate_memory(quantity);
            q = allocate_memory(quantity);
            auto_data_load(quantity, p, q);
            file_handling(quantity, p, q, 0, &file_writes_count, &file_data_load_count, 0.0, 0.0);
            printf("\nTrwa sortowanie...\n");
            bubblesort(p, quantity);
            quicksort(q, 0, quantity - 1);
            file_handling(quantity, p, q, 1, &file_writes_count, &file_data_load_count, 0.0, 0.0);
            free(p);
            free(q);
        }
        else if (mode == 201)
        {
            menu_header();
            printf("AUTOMATYCZNE GENEROWANIE LICZB (testy wydajno�ci)\n");
            printf("-------------------------------------------------\n\n");
            load_quantity(&quantity);
            p = allocate_memory(quantity);
            q = allocate_memory(quantity);

            big_min_max = auto_data_load(quantity, p, q);
            load_iterations(&iterations);
            printf("\nTrwa sortowanie...\n");
            stress_test(quantity, p, q, iterations, &avg_bubble, &avg_quick);
            if(quantity <= 200 && !big_min_max)
                display_sorted(quantity, p, q);
            printf("\n�r. pr�dko�� algorytmu b�belkowego: %lf ms\n", avg_bubble);
            printf("�r. pr�dko�� algorytmu Quicksort: %lf ms\n\n", avg_quick);
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