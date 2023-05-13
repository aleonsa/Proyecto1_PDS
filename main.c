#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define M 	10000 //numero de muestras
#define f 	100 // frecuencia de la senal
#define A	50 // amplitud de la senal
#define PI 	3.14159265358979
#define fs	100000 // frecuencia de muestreo
#define snr 4.5 // relacion señal-ruido en dB

int main(int argc, char *argv[]) {
	
	int m,n; 	//Indices 
	float xsin[M] = {};
	float noise[M] = {};
	float snr_lin = pow(10, snr/10.0); //snr lineal
	float noise_power = A*A/snr_lin;

	float t[M];
	float Ts = 1.0/fs; // periodo de muestreo

	srand(time(NULL)); // semilla para ruido

	
	
	FILE *fsin, *fsinN; // define apuntadores de archivo 
		fsin = fopen("sin.dat", "w");
		fsinN = fopen("sinNoise.dat", "w");


	for (int i = 0; i < M; i++)
    {
        t[i] = i*Ts;
        xsin[i] = A*sin(2.0*PI*f*t[i]);
		noise[i] = sqrt(noise_power)*((float)rand()/(float)RAND_MAX - 0.5);
    }

	for (int i = 0; i < M; i++)
    {
        fprintf(fsin, "%f\n", xsin[i]);
		xsin[i] += noise[i];
		fprintf(fsinN, "%f\n", xsin[i]);
    }
	
	
	fclose(fsin);
	fclose(fsinN);
	
	system("gnuplot -p graf2.gp");
	
	return 0;
}
