#include "gauss.h"
#include "backsubst.h"
#include "mat_io.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char ** argv) {
        int res;
        Matrix * A = argc > 1 ? readFromFile(argv[1]) : NULL;
        Matrix * b = argc > 2 ? readFromFile(argv[2]) : NULL;
        Matrix * x;

        if (A == NULL) return -1;
        if (b == NULL) return -2;
        printToScreen(A);
        printToScreen(b);
	printf("Test 0 : fukcja 'printToScreen' działa prawidłowo.\n");
        res = eliminate(A,b);
	if (res == 1){
        	fprintf(stderr,"'eliminate' :Błąd! Na djagonalnej znajduje się 0, nie można kontynuwać obliczeń.\n");
                freeMatrix(A);
		freeMatrix(b);
		return 1;
	}
	printf("Test 1: funckja elimnate działa prawidłowo.\n");
        x = createMatrix(b->r, 1);
        if (x != NULL) {
		printf("Test 2: funkcja 'creatMatrix' działa prawidłowo.\n");
                res = backsubst(x,A,b);
		if (res == 1){
			fprintf(stderr,"'backsubst' :Błąd! Na djagonalnej znajduje się 0, nie można kontynuwać obliczeń.\n");
        	        freeMatrix(A);
        	        freeMatrix(b);
       		        freeMatrix(x);
			return 1;
		} else if (res == 2){
			fprintf(stderr,"'backsubst' :Błąd! Błędne rozmiary macierzy, nie można kontynuwać obliczeń.\n");
        	        freeMatrix(A);
                	freeMatrix(b);
                	freeMatrix(x);		
			return 1; 
		}
		printf("Test 3: funkcja 'backsubst' działa prawidłowo.\n");
                printToScreen(x);
          	freeMatrix(x);
		printf("Test 4: funkcja 'freeMatrix' działa prawidłowo.\n");
        } else {
        	fprintf(stderr, "'createMatrix' :Błąd! Nie mogłem utworzyć wektora wynikowego x.\n");
        }
	
        freeMatrix(A);
        freeMatrix(b);
	
	printf("Test zakończono sukcesem.\n");
        return 0;
}
