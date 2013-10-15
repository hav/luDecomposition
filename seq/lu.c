#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* Things to do:
 * 1- keep original matrix as matcpy for verification later
 * 2-
 */
int size;
double **l;
double **u;
double **mat;
clock_t begin, end;
FILE *fp;

void printMatrix(double **m) {
    printf("\n \n");

	int i =0, j=0;
    for (i=0;i<size;i++) {
        for(j=0;j<size;j++) {
            printf("|  %f  | ",m[i][j]);
        }
        printf("\n");
    }
}

void freeMatrix(double **matrix)
{
	int i =0;
    for(i = 0; i < size; i++)
        free(matrix[i]);
    free(matrix);
}

/*int verify()
{
	printf("\n\t\t===== L =====\t\t");
	printMatrix(l);
	printf("\n\t\t===== U =====\t\t");
	printMatrix(u);
	printf("\n\t\t===== Original =====\t\t");
	printMatrix(matcpy);
	printf("\n\t\t===== Product =====\t\t");

	int i=0,j=0,k=0;
	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			mat[i][j] = 0;
			for (k = 0; k < size; k++)
			{
				mat[i][j] = mat[i][j] + (l[i][k] * u[k][j]);
	        }
	    }
	}
    //printMatrix(mat);
    for(i = 0; i < size; i++)
    {
    	for(j =0; j < size; j++)
    	{
    		//work around the verification thing
    		if((matcpy[i][j] - mat[i][j])*10 > 5)
    			return 0;
    	}
    }

    freeMatrix(mat);
    freeMatrix(matcpy);
    freeMatrix(l);
    freeMatrix(u);

    return 1;
}*/

void decompose(double **m) {
	begin =clock();
	int i=0, j=0, k=0;
	for(j =0; j < size-1; j++) {
        for(i = j+1; i < size; i++) {
            double factor = m[i][j]/m[j][j];
            for(k = 0; k < size; k++) {
            	u[i][k]= m[i][k] - (m[j][k] * factor);
            }
            l[i][j] = factor;
        }
        //matrix copy m = u
        for(i =0; i< size; i++) {
        	for(k=0; k < size; k++) {
        		m[i][k] = u[i][k];
        	}
        }
        //copy end
    }
	//freeMatrix(mat);
    end = clock();
}

int generateMatrix(int size)
{
    srand(time(NULL));
    mat = malloc(size * (sizeof *mat));
    u = malloc(size * (sizeof *u));
    l = malloc(size * (sizeof *l));
    //matcpy = malloc(size * (sizeof *matcpy));

    int i =0;
    for(i = 0; i<size;i++)
    {
    	u[i] = malloc((sizeof *u[i]) * size);
    	l[i] = malloc((sizeof *l[i]) * size);
    	mat[i] = malloc((sizeof *mat[i]) * size);
    }
    for( i=0 ; i < size ; i++) {
    	u[i] = malloc((sizeof *u[i]) * size);
    	l[i] = malloc((sizeof *l[i]) * size);
        mat[i] = malloc((sizeof *mat[i]) * size);
        //matcpy[i] = malloc((sizeof *matcpy[i]) * size);

        int j = i;
        for( j=i; j< size; j++) {
            mat[i][j] = i+1;
            mat[j][i] = i+1;
            u[i][j] = mat[i][j];
            u[j][i] = mat[j][i];
        }
    }
    decompose(mat);
    return 1;
}


int main(int argc, char * argv[])
{
    if(argc < 2) {
    	printf("Matrix Size missing in the arguments \n");
    	return -1;
    }
    size = strtol(argv[1],(char **)NULL,10);
    fp = fopen("output.txt","a+");

    fprintf(fp,"Matrix Size = %d \n", size);


  	int successFlag = 0;
  	if(generateMatrix(size) == 1)
    {
  		successFlag = 1;
  	}


  	if(successFlag == 1)
  	{
  		fprintf(fp, "Success ");
  	}
  	else
  	{
  		fprintf(fp,"Fail ");
  	}

  	fprintf(fp,"MatrixSize %d ", size);
  	fprintf(fp,"Time %f \n", (double)(end - begin) / CLOCKS_PER_SEC);
  	fclose(fp);
  	return 0;
}