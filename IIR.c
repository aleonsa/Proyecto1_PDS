#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define M 	10000 //numero de muestras
#define f 	10 // frecuencia de la senal
#define A	1 // amplitud de la senal
#define PI 	3.14159265358979
#define fs	10000 // frecuencia de muestreo


int main(int argc, char *argv[]) {

    FILE *fiir; // define apuntadores de archivo 
		fiir = fopen("iir.dat", "w");

    float w = (2*PI*f)/fs;
    int n;
    float a1,a2;
    a1 = -2*cos(w);
    a2 = 1;
    float xsin[M] = {};
    xsin[0] = 0; xsin[1] = sin(w);

    for (int n = 2; n < M; n++)
    {
        xsin[n] = -a1*xsin[n-1] - a2*xsin[n-2];
    }

    for (int n = 0; n < M; n++){
        fprintf(fiir, "%f\n", xsin[n]);
    }
    fclose(fiir);
	
	system("gnuplot -p IIR.gp");
	
	return 0;
}