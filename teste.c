#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <windows.h>
#include <string.h>
#include <math.h>
#define MAX 500000
void omp_set_num_threads(int num_threads);

double PCFreq = 0.0;
__int64 CounterStart = 0;

void StartCounter(){
    LARGE_INTEGER li;
    if(!QueryPerformanceFrequency(&li))
    printf("QueryPerformanceFrequency failed!\n");
    PCFreq = (double)(li.QuadPart)/10000000000000000000.0;
    QueryPerformanceCounter(&li);
    CounterStart = li.QuadPart;
}

double GetCounter(){
    LARGE_INTEGER li;
    QueryPerformanceCounter(&li);
    return (double)(li.QuadPart-CounterStart)/PCFreq;
}

int ordena(int tam, int tipo, int vetor[]);

void quickSort(int *a, int left, int right);

void swap(int *xp, int *yp); 

void selectionSort(int arr[], int n);

char* readFile(char caminho[]);

void writeFile(char caminho[], int mensagem[], int n);

int tamanhoArquivo(char caminho[]);

int* charToIntVet(char *vetor, int n);

char* intToCharVet (int* vetor, int n);

int contEnter (char *vetor, int n);


int main(int argc, char** argv) {
	
	char nomes[14][40] = {
		"./arquivosep2/arq5.txt",
		"./arquivosep2/arq10.txt",
		"./arquivosep2/arq25.txt",
		"./arquivosep2/arq50.txt",
		"./arquivosep2/arq100.txt",
		"./arquivosep2/arq250.txt",
		"./arquivosep2/arq500.txt",
		"./arquivosep2/arq1000.txt",
		"./arquivosep2/arq10000.txt",
		"./arquivosep2/arq25000.txt",
		"./arquivosep2/arq50000.txt",
		"./arquivosep2/arq100000.txt",
		"./arquivosep2/arq1000000.txt",
		"./arquivosep2/arq5000000.txt"
	};
	
	char *arquivo = nomes[2];
	char *retorno;
	retorno = readFile(arquivo); // guardando string do arquivo
	int tam = tamanhoArquivo(arquivo);
	retorno[tam] = ' '; // acrescentar espaço vazio no final da string
	tam++;
	int espacos = contEnter(retorno, tam);
	int novoTam = espacos + 1;
	
	int *armazem1;
	int *armazem2;
	armazem1 = charToIntVet(retorno, tam);
	armazem2 = charToIntVet(retorno, tam);
	novoTam--;

		
	ordena(novoTam, 1, armazem);
		
	ordena(novoTam, 2, armazem);
	
	
//	Escreveno no arquivo e lendo arquivo
//	writeFile(arquivo, armazem, novoTam);
//	readFile(arquivo);

	
	return 0;
}

// Funções

char* intToCharVet (int* vetor, int n) {
	char resp[n];
	for (int i = 0; i < n; i++) {
//		sprintf(resp, "%d", vetor[i]);
		char ch = vetor[i];
		resp[i] = ch + 48;
	}
//	for (int i = 0; i < n; i++) {
//		printf("%c", resp[i]);
//	}
	
	return resp;
}

int* charToIntVet(char *vetor, int n) {
	int array[MAX];
	int tamanho = 0;
	int numCasas = 0;
	for (int i = 0; i < n; i++) {
	    numCasas++;
		    
	    if (vetor[i] == '\n') {
	    	numCasas--;
	        int valorTotal = 0;
		        
	        for (int j = 1; j <= numCasas; j++) {
		        	
	        	int pot = 1;
	        	for(int p = 0; p < j-1; p++){
	        		pot = pot * 10;
	        	}
		        	
	        	int ij = i-j;
	        	int charPraInt = vetor[ij]-48;
	        	int valorParcial = charPraInt * pot;
	        	valorTotal = valorTotal + valorParcial;
	        }
		        
	        array[tamanho] = valorTotal;
	        tamanho++;
	        valorTotal = 0;
	        numCasas = 0;
	    }
		    
	}
	
	return array;
}

int tamanhoArquivo(char caminho[]) {
	char ch;
	char elem[MAX];
	int n = 0;
	FILE *arq;
 
 	arq = fopen(caminho, "r");
 	if(arq == NULL)
    	printf("Erro, nao foi possivel abrir o arquivo\n");
 	else
    	while( (ch=fgetc(arq))!= EOF ) {
    		elem[n] = ch;
    		n++;
		}
 	fclose(arq);
 	return n;
}

char* readFile(char caminho[]) {
	char ch;
	char elem[MAX];
	int n = 0;
	FILE *arq;
 	arq = fopen(caminho, "r");
 	if(arq == NULL)
    	printf("Erro, nao foi possivel abrir o arquivo\n");
 	else
    	while( (ch=fgetc(arq))!= EOF ) {
			printf("a-%c\n",ch);
    		elem[n] = ch;
    		n++;
//			putchar(ch);
		}
 	fclose(arq);
 	return elem;
}

bool writeFile(char caminho[], int mensagem[], int n) {
	FILE *arq;
	arq = fopen(caminho, "wt");  // Cria um arquivo texto para gravaï¿½ï¿½o
	if (arq == NULL) // Se nï¿½o conseguiu criar
	{
   		printf("Problemas na CRIACAO do arquivo\n");
   		return false;
	}
	char str[n];
	for (int i = 0; i < n; i++) {
		sprintf(str, "%d", mensagem[i]);
		int result = fputs(str, arq);
		result = fputs("\n", arq);
		if (result == EOF)
    		printf("Erro na Gravacao\n");
	}
	
	fclose(arq);
}

int contEnter (char *vetor, int n) {
	int cont = 0;
	for (int i = 0; i < n; i++) {
		if (vetor[i] == '\n'){
			cont++;
		}
	}
	return cont;
}

// tipo = 0   -->  selectionSort
// tipo = 1   -->  quickSort
int ordena(int tam, int tipo, int vetor[]) {
	if (tipo==0) {
		selectionSort(vetor, tam);
	} else {
		quickSort(vetor, 0, tam-1);
	}
	return tam;
} 

// SelectioSort
void swap(int *xp, int *yp){ 
    int temp = *xp; 
    *xp = *yp; 
    *yp = temp; 
} 

void selectionSort(int arr[], int n){ 
    int i, j, min_idx; 

    // One by one move boundary of unsorted subarray 
    for (i = 0; i < n-1; i++) 
    { 
        // Find the minimum element in unsorted array 
        min_idx = i; 
        for (j = i+1; j < n; j++) 
          if (arr[j] < arr[min_idx]) 
            min_idx = j; 

        // Swap the found minimum element with the first element 
        swap(&arr[min_idx], &arr[i]); 
    } 
}

// Quick sort function
void quickSort(int *a, int left, int right) {
    int i, j, x, y;

    i = left;
    j = right;
    x = a[(left + right) / 2];

    while(i <= j) {
        while(a[i] < x && i < right) {
            i++;
        }
        while(a[j] > x && j > left) {
            j--;
        }
        if(i <= j) {
            y = a[i];
            a[i] = a[j];
            a[j] = y;
            i++;
            j--;
        }
    }

    if(j > left) {
        quickSort(a, left, j);
    }
    if(i < right) {
        quickSort(a, i, right);
    }
}
