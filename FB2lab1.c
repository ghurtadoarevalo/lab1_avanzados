#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <unistd.h>


//Función encargada de leer todas las lineas del archivo con el nombre que contenga la variable fp_source_name_1
//Entradas: nombre del archivo a leer
//Salidas: Arreglo de arreglos de strings con los datos leídos del archivo
char** readData(char* fp_source_name_1)
{
  	FILE *fp = NULL;
  	int size = 0;
  	int count = 0;
  	int linesNumber = 0;
  	int lineLen = 1;
  	char* dataFileChar = NULL;
  	char* temp = NULL;
  	char* token = NULL;
  	char** lines = NULL;


  	fp = fopen (fp_source_name_1, "r" );

      if (fp==NULL)
      {
          printf("No existe archivo con nombre: %s, asegúrese de que se encuentre en el directorio correcto o exista el archivo.\n", fp_source_name_1);
          exit (1);
      }

  	fseek(fp,0,SEEK_END);
  	size = ftell(fp);
  	rewind(fp);

  	dataFileChar = malloc(sizeof(char)*(size+1));
  	fread(dataFileChar,sizeof(char), size, fp);
  	fclose(fp);

    dataFileChar[size] = '\0';
  	//Se recorre el char* para encontrar la cantidad de palabras
  	for (int i = 0; i < size ; ++i)
  	{
  		  if(dataFileChar[i] == '\n' || dataFileChar[i] == '\0')
  		  {
  			     linesNumber++;
  		  }
  	}

  	//Se asigna memoria para cada linea dentro del arreglo
  	lines = malloc(sizeof(char*)*(linesNumber+1));

  	//Se asigna memoria para cada linea dentro del arreglo
  	linesNumber = 0;
  	for (int i = 0; i <= size; ++i)
  	 {
    	 	if(dataFileChar[i] == '\n' || dataFileChar[i] == '\0')
    		{
      			lines[linesNumber] = malloc(sizeof(char)*(lineLen));
      			linesNumber++;
      			lineLen = 1;
    		}

    		else if(dataFileChar[i] != '\n')
    		{
    		    lineLen++;;
    		}
  	}

  	//Se separan las palabras por \n
  	temp = malloc(sizeof(char)*(size+1));
  	strcpy(temp,dataFileChar);
  	token = strtok(temp, "\n");
  	while(token != NULL)
  	{
        lines[count] = malloc(sizeof(char)*(size));
  		  memcpy(lines[count],token,sizeof(char)*(size));
        token = strtok(NULL, "\n");
  		  count++;
  	}

    free(dataFileChar);
    free(temp);

    return lines;
}


void investmentCombinations()
{
  char* fp_source_name;
  char** data;
  int budget;
  int investmentCount;
  fp_source_name = "test1.txt";
  data = readData(fp_source_name);
  budget = atoi(data[0]);
  investmentCount = atoi(data[1]);
  unsigned ** allCombinations = malloc(sizeof(unsigned*)*investmentCount);

  for (size_t i = 0; i < investmentCount; i++)
  {
      //comb(investmentCount, 4);
  }

    // for (size_t i = 0; i < investmentCount; i++)
    // {
    //   for (size_t j = 0; j <= i; j++)
    //   {
    //       //printf("%d \n", allCombinations[i][j]);
    //   }
    //   printf("\n");
    // }
}
//
// /* Function to swap values at two pointers */
// void swap(char *x, char *y)
// {
//     char temp;
//     temp = *x;
//     *x = *y;
//     *y = temp;
// }
//
// /* Function to print permutations of string
//    This function takes three parameters:
//    1. String
//    2. Starting index of the string
//    3. Ending index of the string. */
// void permute(char *a, int l, int r)
// {
//    int i;
//    if (l == r)
//      printf("%s\n", a);
//    else
//    {
//        for (i = l; i <= r; i++)
//        {
//           swap((a+l), (a+i));
//           permute(a, l+1, r);
//           swap((a+l), (a+i)); //backtrack
//        }
//    }
// }

void swap(int *x1,int *x2)
{
    int x=*x1;
    *x1=*x2;
    *x2=x;
}

void per(int *arr,int st,int ls)
{
    int i=0;
    if(st==ls)
    {
        int k;
        for(k=0;k<ls;k++)
        {
            printf("%d ",arr[k]);
        }
    printf("\n");
    }
    else
    {
        for(i=st;i<ls;i++)
        {
            swap(arr+st,arr+i);
            per(arr,st+1,ls);
            swap(arr+st,arr+i);
        }
    }
}


int main(int argc, char** argv)
{


  int arr[3]={1,2,3};
  int st=0;
  int ls=2;
  per(arr,st,ls);
  return 0;
}
