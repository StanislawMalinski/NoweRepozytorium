#include "gauss.h"
#include <math.h>

/**
 * Zwraca 0 - elimnacja zakonczona sukcesem
 * Zwraca 1 - macierz osobliwa - dzielenie przez 0
 */
int eliminate(Matrix *mat, Matrix *b)
{
	int i, j, k, max;
	double q;
	double *tmp;

	for(i = 0; i < (mat->c - 1); i++)
	{
        max = i;
        for(j = i+1; j < (mat->r); j++)
        {
            if(fabs(mat->data[j][i]) > fabs(mat->data[max][i]))
            {
                max = j;
            }
        }
        if(max != i)
        {
            tmp = mat->data[i];
            mat->data[i] = mat->data[max];
            mat->data[max] = tmp;
            tmp = b->data[i];
            b->data[i] = b->data[max];
            b->data[max] = tmp;
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
