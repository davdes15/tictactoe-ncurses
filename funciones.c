 #include <ncurses.h>
#include <time.h>
#include "funciones.h"

void init(){
  initscr();
  cbreak();
  noecho();
  keypad(stdscr,TRUE);
}

void board(){
  int i,j;
  for(i=1;i<6;i++){
    mvaddch(i,4,'|');
    mvaddch(i,8,'|');
    if(i!=0&&i%2==0){
      for(j=0;j<=12;j++){
	mvaddch(i,j,'-');
      }
    }
    move(1,2);
  }
  refresh();
}

void initGame(int *datos){
  int i;
  for(i=0;i<=8;i++){
    datos[i]=0;
  }
}

int jugar(){
  int datos[9];
  int nJugador=1; //toma como valores 1(jugador 1) o 2 (jugador 2)
  int entrada;
  int x=2,y=1;
  int victoria=0;
  int puedeMover=0;
  int numeroMovimientos=0;
  mvprintw(0,0,"Es el turno del Jugador 1 (X) [q para salir]");
  move(y,x);
  initGame(datos);
  refresh();

  while(entrada!='q'){
    if(numeroMovimientos==9){
      mvprintw(7,0,"Empate");
      entrada=getch();
      erase();
      return 3;
    }
    entrada=getch();
    if(entrada!=' '){
      switch(entrada){
      case KEY_UP:
	if(y==3||y==5){
	  move(y-=2,x);
	}
	break;
      case KEY_DOWN:
	if(y==1||y==3){
	  move(y+=2,x);
	}
	break;
      case KEY_RIGHT:
	if(x==2||x==6){
	  move(y,x+=4);
	}
	break;
      case KEY_LEFT:
	if(x==6||x==10){
	  move(y,x-=4);
	}
	break;
      }
    }
      if(entrada==' '){
	
	if(nJugador==1){
	  getyx(stdscr,y,x);
	  puedeMover=esValido(x,y,datos,-1);
	  if(puedeMover==OKAY){
	  mvaddch(y,x,'X');
	  victoria=checkVictoria(datos);
	  if(victoria){
	    mvprintw(7,0,"Jugador 1 gana!!!!");
	    entrada=getch();
	    erase();
	    return TRUE;
	  }
	  numeroMovimientos+=1;
	  nJugador=2;
	  mvprintw(0,0,"Es el turno del Jugador 2 (O) [q para salir]");
	  move(y,x);
	  }
	}else{
	  getyx(stdscr,y,x);
	  puedeMover=esValido(x,y,datos,1);
	  if(puedeMover==OKAY){
	  mvaddch(y,x,'O');
	  victoria=checkVictoria(datos);
	  if(victoria){
	    mvprintw(7,0,"Jugador 2 gana!!!!");
	    entrada=getch();
	    erase();
	    return TRUE;
	  }
	  numeroMovimientos+=1;
	  nJugador=1;
	  mvprintw(0,0,"Es el turno del Jugador 1 (X) [q para salir]");
	  move(y,x);
	  }
	}
      }
    }
    refresh();
  
  return 0;
}

int esValido(int x,int y,int *datos,int XoO){
  if(y==1){
    if(x==2){
      if(datos[0]==0){
	datos[0]=XoO;
	return OKAY;
      }
    }else if(x==6){
      if(datos[1]==0){
	datos[1]=XoO;
	return OKAY;
      }
    }else if(x==10){
      if(datos[2]==0){
	datos[2]=XoO;
	return OKAY;
      }
    }
  }else if(y==3){
    if(x==2){
      if(datos[3]==0){
	datos[3]=XoO;
	return OKAY;
      }
    }else if(x==6){
      if(datos[4]==0){
	datos[4]=XoO;
	return OKAY;
      }
    }else if(x==10){
      if(datos[5]==0){
	datos[5]=XoO;
	return OKAY;
      }
    }
  }else if(y==5){
    if(x==2){
      if(datos[6]==0){
	datos[6]=XoO;
	return OKAY;
      }
    }else if(x==6){
      if(datos[7]==0){
	datos[7]=XoO;
	return OKAY;
      }
    }else if(x==10){
      if(datos[8]==0){
	datos[8]=XoO;
	return OKAY;
      }
    }
  }
  return FALSE;
}

int checkVictoria(int *datos){ 
  /*horizontales*/
  if(datos[0]==datos[1]&&datos[1]==datos[2]&&datos[0]!=0){
    return TRUE;
  }else if(datos[3]==datos[4]&&datos[4]==datos[5]&&datos[3]!=0){
    return TRUE;
  }else if(datos[6]==datos[7]&&datos[7]==datos[8]&&datos[6]!=0){
    return TRUE;
  }
  /*verticales*/
  else if(datos[0]==datos[3]&&datos[3]==datos[6]&&datos[0]!=0){
    return TRUE;
  }else if(datos[1]==datos[4]&&datos[4]==datos[7]&&datos[1]!=0){
    return TRUE;
  }else if(datos[2]==datos[5]&&datos[5]==datos[8]&&datos[2]!=0){
    return TRUE;
  }
  /*diagonales*/
  else if(datos[0]==datos[4]&&datos[4]==datos[8]&&datos[0]!=0){
    return TRUE;
  }else if(datos[2]==datos[4]&&datos[4]==datos[6]&&datos[2]!=0){
    return TRUE;
  }
  return FALSE;
}

int jugar1p(){
  int datos[9];
  int posIA[2];
  int nJugador=1;
  int entrada;
  int x=2,y=1;
  int victoria=0;
  int puedeMover=0;
  int numeroMovimientos=0;
  mvprintw(0,0,"Es el turno del Jugador 1 (X) [q para salir]");
  move(y,x);
  initGame(datos);
  refresh();
  while(entrada!='q'){
     if(numeroMovimientos==9){
      mvprintw(7,0,"Empate");
      entrada=getch();
      erase();
      return 3;
    }
      entrada=getch();
      if(entrada!=' '){
      switch(entrada){
      case KEY_UP:
        if(y==3||y==5){
          move(y-=2,x);
	}
        break;
      case KEY_DOWN:
        if(y==1||y==3){
          move(y+=2,x);
        }
        break;
      case KEY_RIGHT:
        if(x==2||x==6){
          move(y,x+=4);
        }
        break;
      case KEY_LEFT:
        if(x==6||x==10){
          move(y,x-=4);
        }
        break;
      }
     }
     if(entrada==' '){

        if(nJugador==1){
	  getyx(stdscr,y,x);
          puedeMover=esValido(x,y,datos,-1);
          if(puedeMover==OKAY){
          mvaddch(y,x,'X');
          victoria=checkVictoria(datos);
          if(victoria){
            mvprintw(7,0,"Jugador 1 gana!!!!");
            entrada=getch();
            erase();
            return TRUE;
          }
	  numeroMovimientos+=1;
	  movimientoIA(datos,posIA,numeroMovimientos);
	  puedeMover=esValido(posIA[1],posIA[0],datos,1);
	  if(puedeMover==OKAY){
	    mvaddch(posIA[0],posIA[1],'O');
	    victoria=checkVictoria(datos);
	    if(victoria){
	      mvprintw(7,0,"Jugador 2 Gana!!!!");
	      entrada=getch();
	      erase();
	      return TRUE;
	    }
	    numeroMovimientos+=1;
	    move(y,x);
	  }
	  }
	}	  
     }
  }
  refresh();
  return 0;
}

/* DEMASIADO INEFICEINTE, MEJOR UTILIZAR EL ALGORITMO MINIMAX */

/*void movimientoIA(int *datos, int *posIA,int nmov){
  int random;
  srand(time(NULL));
  if(nmov==1&&datos[4]==1){
    random=rand()&3;
    switch(random){
      case 0:
        posIA[0]=1;
        posIA[1]=2;
        break;
      case 1:
        posIA[0]=1;
        posIA[1]=10;
        break;
      case 2:
        posIA[0]=5;
        posIA[1]=2;
        break;
      case 3:
        posIA[0]=5;
        posIA[1]=10;
        break;
  }
  }else if(nmov==1&&datos[4]!=1){
    posIA[0]=3;
    posIA[1]=6;
  }else if(nmov==3&&(datos[3]==datos[5]&&datos[4]==0)){
    
      random=rand()&1;
      switch (random){
        case 0:
          posIA[0]=1;
          posIA[1]=6;
          break;
        case 1:
          posIA[0]=5;
          posIA[1]=6;
          break;
      }

    }else if(datos[4]==datos[8]&&datos[0]!=0&&datos[0]!=1){
    posIA[0]=1;
    posIA[1]=2;
  }else if(datos[0]==datos[1]&&datos[2]!=0&&datos[2]!=1){
    posIA[0]=1;
    posIA[1]=10;
  }else if(datos[6]==datos[7]&&datos[8]!=0&&datos[8]!=1){
    posIA[0]=5;
    posIA[1]=10;
  }else if(datos[7]==datos[8]&&datos[6]!=0&&datos[6]!=1){
    posIA[0]=5;
    posIA[1]=2;
  }else if(datos[0]==datos[6]&&datos[3]!=0&&datos[3]!=1){
    posIA[0]=3;
    posIA[1]=2;
  }else if(datos[0]==datos[8]&&datos[7]!=0&&datos[7]!=1){
    posIA[0]=5;
    posIA[1]=6;  
  }else if(datos[2]==datos[1]&&datos[0]!=0&&datos[0]!=1){
    posIA[0]=1;
    posIA[1]=2;
  }else if(datos[4]==datos[2]&&datos[6]!=0&&datos[6]!=1){
    posIA[0]=5;
    posIA[1]=2;
  }else if(datos[4]==datos[6]&&datos[2]!=0&&datos[2]!=1){
    posIA[0]=1;
    posIA[1]=10;
  }else if(datos[4]==datos[1]&&datos[7]!=0&&datos[7]!=1){
    posIA[0]=5;
    posIA[1]=6;
  }else if(datos[4]==datos[7]&&datos[1]!=0&&datos[1]!=1){
    posIA[0]=1;
    posIA[1]=6;
  }else if(datos[4]==datos[5]&&datos[3]!=0&&datos[3]!=1){
    posIA[0]=3;
    posIA[1]=2;
  }else if(datos[4]==datos[3]&&datos[5]!=0&&datos[5]!=1){
    posIA[0]=3;
    posIA[1]=10;
  }else if(datos[8]==datos[6]&&datos[7]!=0&&datos[7]!=1){
    posIA[0]=5;
    posIA[1]=6;
  }else if(datos[2]==datos[8]&&datos[5]!=1&&datos[5]!=0){
    posIA[0]=3;
    posIA[1]=10;
  }else if(datos[0]==datos[3]&&datos[6]!=0&&datos[6]!=1){
    posIA[0]=5;
    posIA[1]=2;
  }else if(datos[3]==datos[6]&&datos[0]!=1&&datos[0]!=0){
    posIA[0]=1;
    posIA[1]=2;
  }else if(datos[2]==datos[5]&&datos[8]!=0&&datos[8]!=1){
    posIA[0]=5;
    posIA[1]=10;
  }else if(datos[5]==datos[8]&&datos[2]!=0&&datos[2]!=1){
    posIA[0]=1;
    posIA[1]=10;
  }else if(datos[0]==datos[4]&&datos[8]!=0&&datos[4]!=1){
    posIA[0]=5;
    posIA[1]=10;
  }else if(datos[3]==datos[7]&&datos[6]!=1&&datos[6]!=0){
    if(datos[8]!=1&&datos[8]!=0){
      random=rand()&1;
      switch(random){
        case 0:
          posIA[0]=5;
          posIA[1]=2;
          break;
        case 1:
          posIA[0]=5;
          posIA[1]=10;
          break;
      }
    }else{
    posIA[0]=5;
    posIA[1]=2;
    }
  }else if(datos[1]==datos[3]&&datos[0]!=1&&datos[0]!=0){
    if(datos[2]!=0&&datos[2]!=1){
      random=rand()&1;
      switch(random){
        case 0:
          posIA[0]=1;
          posIA[1]=2;
          break;
        case 1:
          posIA[0]=1;
          posIA[1]=10;
          break;
      }
    }else{
      posIA[0]=1;
      posIA[1]=2;
    }
  }else if(datos[3]==datos[4]){
    if(datos[5]==0||datos[5]==1){
     // mvprintw(20,0,"si");
     if(datos[2]!=0&&datos[2]!=1){
       if(datos[7]!=0&&datos[7]!=1){
         random=rand()&1;
         switch(random){
           case 0:
             posIA[0]=1;
             posIA[1]=6;
             break;
           case 1:
             posIA[0]=5;
             posIA[1]=6;
             break;
         }
       }else{
       posIA[0]=1;
       posIA[1]=6;
       }
    }else if(datos[7]!=0&&datos[7]!=1){
      posIA[0]=5;
      posIA[1]=6;
    }
  }
}else if(datos[4]==datos[5]){
    if(datos[3]==0||datos[3]==1){
     // mvprintw(20,0,"si");
     if(datos[2]!=0&&datos[2]!=1){
       if(datos[7]!=0&&datos[7]!=1){
         random=rand()&1;
         switch(random){
           case 0:
             posIA[0]=1;
             posIA[1]=6;
             break;
           case 1:
             posIA[0]=5;
             posIA[1]=6;
             break;
         }
       }else{
       posIA[0]=1;
       posIA[1]=6;
       }
    }else if(datos[7]!=0&&datos[7]!=1){
      posIA[0]=5;
      posIA[1]=6;
    }
  }
}else if(datos[]){

}
}*/

int checkVictoria1(const int *board){
  unsigned wins[8][3] = {{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};
    int i;
    for(i = 0; i < 8; ++i) {
        if(board[wins[i][0]] != 0 &&
           board[wins[i][0]] == board[wins[i][1]] &&
           board[wins[i][0]] == board[wins[i][2]])
            return board[wins[i][2]];
    }
    return 0;
}

int minimax(int board[9], int player) {
    //comprueba si el jugador gana en siu posicion
    int winner = checkVictoria1(board);
    if(winner != 0) return winner*player;

    int move = -1;
    int score = -2;//-2 ya que los movimientos en los que pierdes son mejores que ningun movimiento
    int i;
    for(i = 0; i < 9; ++i) {//recorre el array para hacer la comprobación en todas las posibles posiciones,
        if(board[i] == 0) {//comprueba si el movimiento es legal,
            board[i] = player;//prueba el movimiento
            int thisScore = -minimax(board, player*-1); //se llama recursivamente probando los movimientos consecutivos hasta obtener la puntuación de ese movimiento
            if(thisScore > score) { //si la puntuación es mayor a la puntuación inicial se queda con ella
                score = thisScore;
                move = i;
            }//con esto elige el peor movimiento para el jugador
            board[i] = 0;//resetea la posicion en el tablero
        }
    }
    if(move == -1) return 0;
    return score;
}

void movimientoIA(int *datos,int *posIA,int nmov){
   int move = -1;
   int score = -2;
   int i;
   for(i = 0; i < 9; ++i) {
       if(datos[i] == 0) {
           datos[i] = 1;
           int tempScore = -minimax(datos, -1);
           datos[i] = 0;
           if(tempScore > score) {
               score = tempScore;
               move = i;
           }
       }
   }
  //basado en el movimiento obetenido anteriormente a partir de la puntuación elige la posición de la IA
  switch(move){
    case 0:
      posIA[0]=1;
      posIA[1]=2;
      break;
    case 1:
      posIA[0]=1;
      posIA[1]=6;
      break;
    case 2:
      posIA[0]=1;
      posIA[1]=10;
      break;
    case 3:
      posIA[0]=3;
      posIA[1]=2;
      break;
    case 4:
      posIA[0]=3;
      posIA[1]=6;
      break;
    case 5:
      posIA[0]=3;
      posIA[1]=10;
      break;
    case 6:
      posIA[0]=5;
      posIA[1]=2;
      break;
    case 7:
      posIA[0]=5;
      posIA[1]=6;
      break;
    case 8:
      posIA[0]=5;
      posIA[1]=10;
      break;
  }
}
