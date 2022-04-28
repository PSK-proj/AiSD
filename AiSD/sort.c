void bubblesort(int tab[], int size)
{
	int temp;
	for (int i = 0; i < size - 1; i++)
	{
		for (int j = 0; j < size - 1 - i; j++)
		{
			if (tab[j] > tab[j + 1])
			{
				temp = tab[j + 1];
				tab[j + 1] = tab[j];
				tab[j] = temp;
			}
		}
	}
}

void quicksort(int tab[], int first, int last)
{
	int i = first - 1;
	int temp;
	int pivot = tab[last];
	for (int j = first; j < last; ++j)
	{
		if (tab[j] < pivot)
		{
			++i;
			temp = tab[i];
			tab[i] = tab[j];
			tab[j] = temp;
		}
	}
	if (i < first)
	{
		temp = tab[first];
		tab[first] = tab[last];
		tab[last] = temp;
		++i;
	}
	if (first < i) quicksort(tab, first, i);
	if (last > i + 1) quicksort(tab, i + 1, last);
}