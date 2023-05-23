#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define M 	10000 //numero de muestras
#define N 	100	// long de ventana gaussiana
#define f 	100 // frecuencia de la senal
#define A	50 // amplitud de la senal
#define PI 	3.14159265358979
#define fs	10000 // frecuencia de muestreo
#define snr 4.5 // relacion señal-ruido en dB
#define alpha 0.4 // alpha para la campana gaussiana


//Funcion para obtener el espectro de una señal float
void DFTF(double *x, int len_x, double *y, int klim){
	int n,k;
	double AI, AR;
	float dw=2*PI/klim;
	float we=0; 

	for(k=0; k<klim; k++){
		AI=0;
		AR=0;
		for(n=0; n<len_x; n++){
			AR= AR + x[n]*cos(we*n);
			AI= AI + x[n]*sin(we*n);
		}
		y[k]= sqrt(AR*AR+AI*AI);
		we= we + dw;
	}

}

//funcion para ejecutar convolucion entre dos senales
void convolve(float *x, int len_x, float *h, int len_h, double *y)
{
    int len_y = len_x + len_h - 1; //longitud de la conv
    int i, j;

    for (i = 0; i < len_y; i++) { 
        y[i] = 0;
        for (j = 0; j < len_h; j++) {
            if ((i - j) >= 0 && (i - j) < len_x) {
                y[i] += x[i - j] * h[j];
            }
        }
    }
}

int main(int argc, char *argv[]) {
	
	int m,n; 	//Indices 
	float xsin[M] = {}; // variable para guardar la senal seno
	float xsinN[M] = {};
	float noise[M] = {}; // variable para guardar el ruido
	double y[M+N-1] = {}; // variable para la senal convolucionada
	double espsinN[M] = {};
	double espwGauss[M] = {};
	double espy[M+N-1]= {};
	double esprxx[M+M-1]= {};
	double rxx[M+M-1] = {};
	float wGauss[M] = {}; // variable para guardar la ventana gaussiana
	float snr_lin = pow(10, snr/10.0); //snr lineal 
	float noise_power = A*A/snr_lin; // potencia de la senal

	float w = (2*PI*f)/fs; // omega normalizada

	srand(time(NULL)); // semilla para ruido

	/*------- define apuntadores de archivo ----------*/ 
	FILE *fsin, *fsinN, *fgaussW, *fconv, *fauto; 
		fsin = fopen("sin.dat", "w");
		fsinN = fopen("sinNoise.dat", "w");
		fgaussW = fopen("gaussWindow.dat","w");
		fconv	= fopen("conv.dat","w");
		fauto	= fopen("auto.dat","w");

	FILE *fesp_sinN,*fesp_gaussW, *fesp_conv, *fesp_auto; 
		fesp_sinN = fopen("esp_sinNoise.dat", "w");
		fesp_gaussW = fopen("esp_gaussWindow.dat","w");
		fesp_conv	= fopen("esp_conv.dat","w");
		fesp_auto	= fopen("esp_auto.dat","w");
	/*------ Genera senal con IIR cuasiestable --------*/ 
	float a1,a2;
    a1 = -2*cos(w);
    a2 = 1;
    
    xsin[0] = 0; xsin[1] = sin(w);
	
	for (int n = 2; n < M; n++)
    {
        xsin[n] = -a1*xsin[n-1] - a2*xsin[n-2];
    }
	//Escalamiento en amplitud
	for (int n = 0; n < M; n++)
    {
        xsin[n] = A*xsin[n];
    }

	/*------- Genera ruido con SNR < 5dB ----------*/ 
	for (int n = 0; n < M; n++){
		noise[n] = sqrt(noise_power)*((float)rand()/(float)RAND_MAX - 0.5);
    }

	// Guarda el seno y el seno con ruido sumado en archivos .dat
	for (int n = 0; n < M; n++){
        fprintf(fsin, "%f\n", xsin[n]);
		xsin[n] += noise[n];
		fprintf(fsinN, "%f\n", xsin[n]);
    }
	
	// Guarda la ventana gaussiana en archivo .dat
	for(int n=0; n<N; n++){
		wGauss[n] = exp(-0.5 * pow((n - (N-1)/2) / (alpha * (N-1)/2), 2));
		fprintf(fgaussW, "%f\n", wGauss[n]);
	}

	/* ---  Aplica la convolucion con func previamente creada  ---*/
	convolve(xsin, M, wGauss, N, y);

	// Guarda el resultado en un archivo .dat
	for (n = 0; n < N + M - 1; n++) {
        fprintf(fconv,"%f\n ", y[n]);
    }

	//Autocorrelacion
	for (int n = 0; n < M; n++)
    {
        xsinN[n] = -1*xsin[n];
    }
	convolve(xsin, M, xsinN, M, rxx);
	// Guarda el resultado en un archivo .dat
	for (n = 0; n < M + M - 1; n++) {
        fprintf(fauto,"%f\n ", rxx[n]);
    }


	DFTF((double *)xsin,M,espsinN,M);
	for (int i = 0; i < M; i++)
	{
		fprintf(fesp_sinN,"%f\n ", espsinN[i]);
	}
	
	
	DFTF((double *)wGauss,N,espwGauss,N);
	for (int i = 0; i < N; i++)
	{
		fprintf(fesp_gaussW,"%f\n ", espwGauss[i]);
	}

	DFTF(y,M+N-1,espy,M+N-1);
	for (int i = 0; i < M+N-1; i++)
	{
		fprintf(fesp_conv,"%f\n ", espy[i]);
	}

	DFTF(rxx,M+M-1,esprxx,M+M-1);
	for (int i = 0; i < M+M-1; i++)
	{
		fprintf(fesp_auto,"%f\n ", esprxx[i]);
	}
	


	/*---  Cierra archivos  ---*/
	fclose(fsin);
	fclose(fsinN);
	fclose(fgaussW);
	fclose(fconv);
	fclose(fauto);

	fclose(fesp_sinN);
	fclose(fesp_gaussW);
	fclose(fesp_conv);
	fclose(fesp_auto);
	
	/*Grafica con herramienta GNU-Plot*/
	//system("gnuplot -p main.gp");
	//system("gnuplot -p auto.gp");
	system("gnuplot -p espectros.gp");
	
	return 0; // Fin del programa
}
