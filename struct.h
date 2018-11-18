#ifndef STRUCTS_H
#define STRUCTS_H

//Estructura que se utiliza para almacenar una inversion
typedef struct {
	int cost;
	int benefit;
} investment;

//Estructura que se utiliza para almacenar las combinaciones de inversiones
typedef struct {
	investment ** all;
	int quantity;
	int totalCost;
	int totalBenefit;
} investments;


typedef enum { false, true } bool;

#endif
