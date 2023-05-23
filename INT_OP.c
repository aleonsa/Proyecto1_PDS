#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "integer_lib.h"
#include <time.h>       				

#define M 	10000 						//numero de muestras
#define N 	50							// long de ventana gaussiana
#define A	50 							// amplitud de la senal
#define PI 	3.14159265358979			//Definicion de pi

#define fs	100000 						// frecuencia de muestreo
#define snr 4.5 						// relacion señal-ruido en dB
#define alpha 0.4
#define e 2.71828
#define f 100
#define wo (2*PI*f)/fs
void convolve(int *x, int len_x, int *h, int len_h, int *y);
int main(int argc, char *argv[]){
	int xsin[M] = {}; 				// variable para guardar la senal seno de la convolucion
	int y[M+N-1] = {}; 				// variable para la senal convolucionada
	int wGauss[N] = {}; 			// variable para guardar la ventana gaussiana
	int noise[M] = {}; 				// variable para guardar el ruido
	int n;
	
	float snr_lin = pow(10, snr/10.0); 	//snr lineal 
	float noise_power = A*A/snr_lin; 	// potencia de la senal
	srand(time(NULL)); 					// semilla para ruido
	
	FILE *fsinInt, *fsinN_Int, *fgaussW_Int, *fconv_Int;
		fsinN_Int 	= fopen("sinNoise_Int.dat", "w");
		fgaussW_Int = fopen("gaussWindow_Int.dat","w");
		fconv_Int	= fopen("conv_Int.dat","w");
		fsinInt	= fopen("sinInt.dat", "w");	
	
	
			/*------- Genera ruido con SNR < 5dB ----------*/ 
	for (n = 0; n < M; n++)
	{
		noise[n] = sqrt(noise_power)*((float)rand()/(float)RAND_MAX - 0.5);
    }
    
	//Condiciones iniciales
	xsin[0] = 0; 
	xsin[1] = FLOAT2FIXED(sin(wo));	
	for (n = 2; n < M; n++)
    {
        xsin[n] = FLOAT2FIXED(2*cos(wo)*FIXED2DOUBLE(xsin[n-1])-FIXED2DOUBLE(xsin[n-2]));
    }
	//Escalamiento en amplitud y guarda en archivo
	for (n = 0; n < M; n++)
    {
        xsin[n] = A*(xsin[n]);
        fprintf(fsinInt, "%f\n", FIXED2DOUBLE(xsin[n]));
        
        xsin[n] = FLOAT2FIXED(FIXED2DOUBLE(xsin[n]) + noise[n]);
		fprintf(fsinN_Int, "%f\n", FIXED2DOUBLE(xsin[n]));
    }
    
	// Guarda la ventana gaussiana en archivo .dat
	for(n=0; n<N; n++){
		wGauss[n] = FLOAT2FIXED(exp(-0.5 * pow((n - (N-1)/2) / (alpha * (N-1)/2), 2)));
		fprintf(fgaussW_Int, "%f\n", FIXED2DOUBLE(wGauss[n]));
	}
	
	// para almacenar el tiempo de ejecución del código
    double time_spent = 0.0;
    clock_t begin = clock();
    for(n=0;n<M;n++){
    	/* ---  Aplica la convolucion con func previamente creada  ---*/
		convolve(xsin, M, wGauss, N, y);
	}	
	clock_t end = clock();
	time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
    printf("\nTiempo transcurrido Punto Fijo: %f sec.\n", time_spent);
    
	// Guarda el resultado en un archivo .dat
	for (n = 0; n < N + M - 1; n++) {
        fprintf(fconv_Int,"%f\n ", FIXED2DOUBLE(y[n]));
    }
	fclose(fsinInt);
	return 0;
}
void convolve(int *x, int len_x, int *h, int len_h, int *y)
	{
    int len_y = len_x + len_h - 1; //longitud de la conv
    int i, j;

    for (i = 0; i < len_y; i++) { 
        y[i] = 0;
        for (j = 0; j < len_h; j++) {
            if ((i - j) >= 0 && (i - j) < len_x) {
                y[i] = y[i] + (x[i-j]>>8)*(h[j]>>8);
            }
        }
    }
} 	







