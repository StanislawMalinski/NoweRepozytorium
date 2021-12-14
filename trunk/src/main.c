#include "gauss.h"
#include "backsubst.h"
#include "mat_io.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>


int main(int argc, char ** argv) {
	int res, i, j;
        double sum;
	Matrix * A = readFromFile(argv[1]);
	Matrix * b = readFromFile(argv[2]);
	Matrix * x;

	if (A == NULL) return -1;
	if (b == NULL) return -2;
	printToScreen(A);
	printToScreen(b);

	res = eliminate(A,b);
        if(res == 1)
        {
            fprintf(stderr, "Macierz %d x %d: Błąd! Dzielenie przez 0.\n", A->r, A->c);
            freeMatrix(A);
            freeMatrix(b);
            return -3;
        }
        x = createMatrix(b->r, 1);
        if (x != NULL) {
	    res = backsubst(x,A,b);
        if(res == 1)
        {
            fprintf(stderr, "Macierz %d x %d: Błąd! Dzielenie przez 0 lub macierz osobliwa.\n", A->r, A->c);
            freeMatrix(A);
            freeMatrix(b);
            freeMatrix(x);
            return -4;
        }
        else if(res == 2)
        {
            fprintf(stderr, "Macierz %d x %d: Błąd! Nieprawidłowe rozmiary macierzy.\n", A->r, A->c);
            freeMatrix(A);
            freeMatrix(b);
            freeMatrix(x);
            return -5;
        }
	printToScreen(x);
        for(i = 0; i < (A->r); i++)
        {
            sum = 0;
            for(j = 0; j < (A->c); j++)
            {
                sum += A->data[i][j] * x->data[j][0];
            }
            if(fabs(sum - b->data[i][0]) > 0.0000001) /*sprawdzenie dokładności wyniku do 10^(-7)*/
            {
                fprintf(stderr, "Macierz %d x %d: Błąd! Nieprawidłowy wynik.\n", A->r, A->c);
                freeMatrix(A);
                freeMatrix(b);
                freeMatrix(x);
                return -6;
            }
        }
	freeMatrix(x);
	} else {
		fprintf(stderr,"Błąd! Nie mogłem utworzyć wektora wynikowego x.\n");
	}

	fprintf(stderr, "Macierz %d x %d: Poprawne dane i wynik.\n", A->r, A->c);

	freeMatrix(A);
	freeMatrix(b);

	return 0;
}
