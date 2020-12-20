#include <stdio.h>
#include <omp.h>
#include <windows.h>
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

int main(){

StartCounter();Sleep(10000);printf("%f\n",GetCounter());

	char x[][3]= {
	"aaa",
	"bbb",
	"ccc"
	};
	omp_set_num_threads(3);
//	puts(  x[1] )
	int i;
	for(i = 0;i<3; i++)
	#pragma omp parallel
	{
	//	printf("%d || %d\n\n",omp_get_thread_num(),omp_get_num_threads());]
		printf("%c\n",x[0][1]);
	}
	return 0;
	
	
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
			putchar(ch);
//			printf("%c",ch);
		}
 	fclose(arq);
 	return elem;
}
	
}

