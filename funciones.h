#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

#define J1 1
#define J2 2
#define OKAY 5

void init();
void board();
void initGame(int *datos);
int jugar();
int esValido(int x,int y,int *datos,int XoO);
int checkVictoria(int *datos);
int jugar1p();
void movimientoIA(int *datos,int *posIA,int nmov);
