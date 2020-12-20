#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 500000

int ordena(int tam, int tipo, int vetor[]);

void quickSort(int *a, int left, int right);

void swap(int *xp, int *yp); 

void selectionSort(int arr[], int n);

char* readFile(char caminho[]);

bool writeFile(char caminho[], int mensagem[], int n);

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
	
//	char arquivo[] = "./arquivosep2/arq5000000.txt";
	char *arquivo = nomes[2];
//	char *texto = "3 8 1 0";
//	writeFile(arquivo, texto);
//	printf("%c",arquivo[3]);
	char *retorno;
	retorno = readFile(arquivo); // guardando string do arquivo
//	printf("%c%c%c%c%c",arquivo[0],arquivo[1],arquivo[2],arquivo[3],arquivo[18]);
//		printf("%c",retorno[i]);
	int tam = tamanhoArquivo(arquivo);
	retorno[tam] = ' '; // acrescentar espaço vazio no final da string
	tam++;
	int espacos = contEnter(retorno, tam);
	int novoTam = espacos + 1;
	
	
//	alterando de string para int[]
	printf("\n");
	int *armazem;
	armazem = charToIntVet(retorno, tam);
	novoTam--;
//	for(int i =0; i<30;i++)
//		printf("%c\n",retorno[i]);
//	printf("----------------------\n");
//	ordenando int[]
	for(int i=0; i<novoTam,i++)
		
		
		
	
	
		ordena(novoTam, 1, armazem);
		
		ordena(novoTam, 2, armazem);
	
	
//	Escreveno no arquivo e lendo arquivo
	printf("\n\n");
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
void swap(int *xp, int *yp) 
{ 
    int temp = *xp; 
    *xp = *yp; 
    *yp = temp; 
} 

void selectionSort(int arr[], int n) 
{ 
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
