#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include "functions.h"
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
  		lines[count] = token;
        token = strtok(NULL, "\n");
  		  count++;
  	}

    free(dataFileChar);
    return lines;
}

void printCurrent(investments * combination)
 {
    #ifdef DEBUG
    printf("\n Enter para continuar …\n");
    while(getchar() != '\n');

    printf("Lista inversiones: ");
    for (size_t i = 0; i < combination->quantity; i++)
    {
        printf("[%d , %d] ", combination->all[i]->cost, combination->all[i]->benefit);
    }
    printf("\n");
    printf("Costo total: %d , Beneficio Total; %d\n",combination->totalCost, combination->totalBenefit );

     /* en esta parte debe escribir su código para imprimir lo que sea necesario para mostrar el estado actual  del nodo. */

    #endif
}

investments ** powerSet(investment ** set, int set_size)
{
    /*set_size of power set of a set with set_size
      n is (2**n -1)*/
    unsigned int pow_set_size = pow(2, set_size);
    investments ** investmentCombinations = malloc(sizeof(investments *)*pow_set_size);
    int counter, j,temp_cost,temp_benefit, temp_quantity, counter2 = 0, counter3;

    /*Run from counter 000..0 to 111..1*/
    for(counter = 0; counter < pow_set_size; counter++)
    {
        counter3 = 0;
        temp_cost = 0, temp_benefit = 0; temp_quantity = 0;
        investments * combination = (investments*)malloc(sizeof(investments));
        combination->all = malloc(sizeof(investment**)*(set_size));
        for(j = 0; j < set_size; j++)
        {
            combination->all[counter3] = (investment*)malloc(sizeof(investment));
            /* Check if jth bit in the counter is set
             If set then print jth element from set */
            if(counter & (1<<j))
            {
                 combination->all[counter3] = set[j];
                 temp_cost += set[j]->cost;
                 temp_benefit += set[j]->benefit;
                 temp_quantity += 1;
                 counter3++;
            }
        }

        combination->totalCost = temp_cost;
        combination->totalBenefit = temp_benefit;
        combination->quantity = temp_quantity;
        printCurrent(combination);
        investmentCombinations[counter2] = combination;
        counter2++;
    }

    return investmentCombinations;
}


//Entradas:  estructura con las combinaciones de inversiones, cantidad de inversiones disponibles, presupuesto
//Salidas: entrega como salida un puntero al nodo inicial con la mejor combinación de inversiones.
investments * bruteForce(investments ** investmentCombinations, int set_size, int budget)
{
    int maxBenefit;
    maxBenefit = -9999;
    unsigned int pow_set_size = pow(2, set_size);
    investments * bestInvesment = (investments *)malloc(sizeof(investments));
    for (size_t i = 0; i < pow_set_size ; i++)
    {
        if (investmentCombinations[i]->totalCost < budget && investmentCombinations[i]->totalBenefit > maxBenefit)
        {
            maxBenefit = investmentCombinations[i]->totalBenefit;
            bestInvesment = investmentCombinations[i];
        }
    }
    //printf("%d\n", bestInvesment->all[0]->cost);

    return bestInvesment;
}

void getOutput(investments * best)
{
    FILE *fp;
    fp=fopen("Salida.out", "w");

    if(fp == NULL)
    {
        printf("Error al crear el archivo %s\n","Salida.out");
        exit(1);
    }

    fprintf(fp, "%d %d \r\n", best->totalCost, best->totalBenefit);

    for (size_t i = 0; i < best->quantity; i++)
    {
        fprintf(fp, "%d", best->all[i]->cost);
        fprintf(fp, "\r\n");
    }
    fclose(fp);
}

int main()
{
    investments * best = (investments*)malloc(sizeof(investments));

    char* temp;
    char* fp_source_name;
    char** data;
    char * token;
    int budget;
    int investmentCount;
    fp_source_name = "entrada.in";
    data = readData(fp_source_name);
    budget = atoi(data[0]);
    investmentCount = atoi(data[1]);

    investments ** investmentCombinations = malloc(sizeof(investments*)*pow(2,investmentCount));
    investment ** readedInvestments = malloc(sizeof(investment*)*investmentCount);

    printf("\n\n <<%s>> \n\n","Bienvenido al laboratorio de fuerza bruta: Mejores inversiones" );

    printf("\n\n %s \n\n","0) Leyendo información de Entrada.in");

    for (size_t i = 2; i < investmentCount+2; i++)
    {
        temp = malloc(sizeof(char)*(100));
        strcpy(temp,data[i]);
        token = strtok(temp, " ");
        investment * a = malloc(sizeof(a));
        a->cost = atoi(token);
        while(token != NULL)
        {
            a->benefit = atoi(token);
            token = strtok(NULL, " ");
        }
        readedInvestments[i-2] = a;

    }

    printf("\n\n %s \n\n","1) Generación de todas las combinaciones posibles");

    investmentCombinations = powerSet(readedInvestments, investmentCount);

    printf("\n\n %s \n\n","2) Eligiendo la mejor opción");

    best = bruteForce(investmentCombinations, investmentCount, budget);

    printf("\n\n %s \n\n","3) Guardando la mejor opción en Salida.out");

    getOutput(best);

    printf("\n\n %s \n\n","4) Liberando memoria");

    for (size_t i = 2; i < investmentCount + 2; i++)
    {
        free(readedInvestments[i-2]);
    }

    free(readedInvestments);

    for (size_t i = 0; i < pow(2,investmentCount); i++)
    {
        for (size_t j = 0; j < investmentCombinations[i]->quantity ; j++) {
            free(investmentCombinations[i]->all[j]);
        }

        free(investmentCombinations[i]);
    }

    free(investmentCombinations);
    
    free(best);

    return 0;
}
