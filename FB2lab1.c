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
  	int count = 1;
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
    lines[0] = malloc(sizeof(char)*2);
  	while(token != NULL)
  	{
        lines[count] = malloc(sizeof(char)*(size));
  		  memcpy(lines[count],token,sizeof(char)*(size));
        token = strtok(NULL, "\n");
  		  count++;
  	}
    return lines;
}

int main(int argc, char** argv)
{
  char* fp_source_name;
  char** data;
  fp_source_name = "test1.txt";
  data = readData(fp_source_name);
  printf("%s\n",data[1] );
}
