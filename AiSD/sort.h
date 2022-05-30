#pragma once
/**
 * \file   sort.h
 * \brief
 * Funckje sortujace
 * \author Piotr Miernik, Oskar Olub
 * \date   Maj 2022
 *********************************************************************/

/// <summary>
/// Funkcja sortowania babelkowego.
/// 
/// Polega na porownywaniu dwoch kolejnych elementow i zamianie ich kolejnosci, jezeli zaburza ona porzadek, w jakim sie sortuje tablice.
/// </summary>
/// <param name="tab">Tablica do posortowania</param>
/// <param name="size">Rozmiar tablicy do posortowania</param>
void bubblesort(int tab[], int size);
/// <summary>
/// Funkcja sortowania Quicksort.
///  
/// W technice Lomuto zwykle ostatni element listy jest wybierany jako pivot. Po ustawieniu go na wlasciwym miejscu, nie bierze juz on udzialu w kolejnych etapach wywolan rekurencyjnych.
/// Proces sortowania rozpoczyna sie od skrajnego lewego elementu i obrania go jako biezacy indeks. Za kazdym razem, gdy napotkany zostanie element mniejszy niz pivot, zwiekszamy biezacy indeks.
/// Nastepnie zamieniamy element mniejszy od pivotu z elementem o biezacym indeksie. Proces ten przechodzi przez wszystkie elementy.
/// W kolejnym kroku element spod biezacego indeksu oraz pivot sa ze soba zamieniane.
/// Proces ten ustawia elementy mniejsze od pivotu po jego lewej stronie, a wieksze po jego prawej stronie.
/// Na tak podzielonej tablicy wywolywanie sa rekurencyjnie funkcje quicksort, az do momentu, gdy nie ma z czym porownac pivotu.
/// </summary>
/// <param name="tab">Tablica do posortowania</param>
/// <param name="first">Indeks pierwszego elementu</param>
/// <param name="last">Indeks ostatniego elementu</param>
void quicksort(int tab[], int first, int last);