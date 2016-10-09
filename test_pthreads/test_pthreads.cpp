//============================================================================
// Name        : test_pthreads.cpp
// Author      : asa
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C, Ansi-style
//============================================================================


#if 0
#include <stdio.h>
#include <stdlib.h>

int main(void) {
	puts("!!!Hello World!!!");
	return EXIT_SUCCESS;
}
#endif


/*
 * main.c
 *
 * To jest oryginalny task dla kodu ponizej w postaci wyjsciowej.
 *
 * Wykorzystaj kod z zadania 2.
 * Wstrzyknij do tej klasy opcjonalny komparator.
 * Tym razem nie porzadek bedzie odwrotny.
 *
 *
 *
 * Task 07:
 *
 * - Zaimplementowac kolejke FIFO dla typu int.
 *
 * - Zaimplementowac program testujacy kolejke:
 *
 * 		+ Program posiada N watkow pobierajacych dane z kolejki.
 * 		+ Watek glowny wyrzucam przez M sekund losowe liczby na kolejke.
 * 		+ Kazdy z N watkow, K razy wypisuje specyficzny dla siebie log.
 * 		+ M i N sa argumentami programu.
 * 		+ K jest wartoscia pobrana z kolejki
 *
 * 	- Program ma zakonczyc sie "na czysto", wszystkie watki musza byc
 * 	  "z-joinowane".
 *
 * 	- Jako kontener na dane wykorzystaj liste z zadan 1 i 2.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "forward_list.h"

void basic_test(void);
void solution(void);

int fl_pred(int l, int r)
{
	return l < r;
}

int main(int argc, const char *argv[])
{
	//basic_test();
	solution();
	return 0;
}

void basic_test(void)
{
	const node* n = 0;
	forward_list fl;
	init_forward_list(&fl, fl_default_pred);
	fl.insert(&fl, 3);
	fl.insert(&fl, 0);
	fl.insert(&fl, 2);
	fl.insert(&fl, 5);

	for (n = fl.front(&fl); n != 0; n = n->next)
		printf("%d ", n->key);
	printf("\n");

	fl.erase(&fl, 0);
	fl.erase(&fl, 3);
	fl.erase(&fl, 5);

	for (n = fl.front(&fl); n != 0; n = n->next)
		printf("%d ", n->key);
	printf("\n");

	clean_forward_list(&fl);
}

void solution(void)
{
	time_t start = 0;
	time_t end = 0;
	size_t i = 0;
	int v = 0;
	const node* n = 0;
	forward_list fl;

	start = time(0);
	init_forward_list(&fl, fl_pred);
	srand(time(0));

	for (; i < 1000; ++i) {
		v = rand() % 10000 + 1;
		fl.insert(&fl, v);
	}

	for (i = 0; i < 100; ++i) {
		v = rand() % 10000 + 1;
		fl.erase(&fl, v);
	}

	for (n = fl.front(&fl); n != 0; n = n->next)
		printf("%d ", n->key);
	printf("\n");

	clean_forward_list(&fl);

	end = time(0);
	printf("Duration: %d\n", (int)(end-start));
}

