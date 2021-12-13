#include "gauss.h"

/**
 * Zwraca 0 - elimnacja zakonczona sukcesem
 * Zwraca 1 - macierz osobliwa - dzielenie przez 0
 */
int eliminate(Matrix *mat, Matrix *b)
{
	int l, i, j, k, maxsimum;
	double q;
	double *pp;
	
	for(i = 0; i < (mat->c - 1); i++){
		maxsimum = i;
		for( l = i + 1; l < (mat->r); l++){
			if(mat->data[maxsimum][i] < mat->data[l][i])
				maxsimum = l;
		}
		if(maxsimum != i){
			pp = mat->data[i];
			mat->data[i] = mat->data[maxsimum];
			mat->data[maxsimum] = pp;
			
			pp = b->data[i];
			b->data[i] = b->data[maxsimum];
			b->data[maxsimum] = pp;
		}
	
		for(j = i+1; j < (mat->r); j++)
		{
			if(mat->data[i][i] != 0)
			{
				q = mat->data[j][i] / mat->data[i][i];
				for(k = i; k < (mat->c); k++)
				{
					mat->data[j][k] -= q * mat->data[i][k];
				}
				b->data[j][0] -= q * b->data[i][0];
			}
			else
			{
				return 1;
			}
		}
	}
	
	return 0;
}
