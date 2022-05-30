#pragma once
/**
 * \file   menu.h
 * \brief  
 * Obsluga menu
 * \author Piotr Miernik, Oskar Olub
 * \date   Maj 2022
 *********************************************************************/

/// <summary>
/// Wyswietlanie ozdobnego naglowka.
/// </summary>
void menu_header();

/// <summary>
/// Wyswietlenie menu glownego.
/// 
/// Funkcja wyswietla menu glowne programu i ustawia zmienna "mode" na odpowiednia wartosc wedle wyboru uzytkownika.
/// </summary>
/// <param name="mode">Wskaznik na zmienna trybow.</param>
void menu_main(unsigned short* mode);
