#include <ncurses.h>
#include "funciones.h"
#include <menu.h>
#include <string.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define CTRLD 4

char *choice[]={
  "1 jugador",
  "2 jugadores",
  "Salir",
};

void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string, chtype color);

int main(){
  ITEM **my_items;
  int c;
  MENU *my_menu;
  WINDOW *my_menu_win;
  int n_elecciones,i;
  ITEM *cur_item;
  //iniciar curses
  init();
  start_color();
  //colores
  init_pair(1,COLOR_RED,COLOR_BLACK);
  init_pair(2, COLOR_CYAN, COLOR_BLACK);
  init_pair(3, COLOR_MAGENTA, COLOR_BLACK);

  n_elecciones=ARRAY_SIZE(choice);
  my_items=(ITEM **)calloc(n_elecciones+1,sizeof(ITEM *));

  for(i=0;i<n_elecciones;++i){
    my_items[i]=new_item(choice[i]," ");
  }

  my_items[n_elecciones]=(ITEM *)NULL;
  my_menu=new_menu((ITEM **)my_items);
  
  my_menu_win = newwin(10, 40, 4, 4);
  keypad(my_menu_win, TRUE);
  
  set_menu_win(my_menu, my_menu_win);
  set_menu_sub(my_menu, derwin(my_menu_win, 6, 38, 3, 1));
  set_menu_format(my_menu, 5, 1);

  set_menu_mark(my_menu," * ");
  
  /*set_menu_fore(my_menu, COLOR_PAIR(1) | A_REVERSE);
  set_menu_back(my_menu, COLOR_PAIR(2));
  set_menu_grey(my_menu, COLOR_PAIR(3));
*/
  box(my_menu_win,0,0);
  print_in_middle(my_menu_win, 1, 0, 40, "3 en raya", COLOR_PAIR(1));
  mvwaddch(my_menu_win, 2, 0, ACS_LTEE);
  mvwhline(my_menu_win, 2, 1, ACS_HLINE, 38);
  mvwaddch(my_menu_win, 2, 39, ACS_RTEE);

  mvprintw(LINES -2, 0, "[q] para salir");
  post_menu(my_menu);
  wrefresh(my_menu_win);
  refresh();
  while((c=getch())!='q'){  
  //  post_menu(my_menu);
 //   wrefresh(my_menu_win);
    refresh();
    switch(c){
    case KEY_DOWN:
      menu_driver(my_menu,REQ_DOWN_ITEM);
	    break;
    case KEY_UP:
      menu_driver(my_menu,REQ_UP_ITEM);
      break;
    case '\n':
      if(strcmp(item_name(current_item(my_menu)),"2 jugadores")==0){
        erase();
        do{
         init();
         board();
        }while(jugar());
        erase();
        //refresh();
        box(my_menu_win, 0, 0);
        print_in_middle(my_menu_win, 1, 0, 40, "3 en raya", COLOR_PAIR(1));
        mvwaddch(my_menu_win, 2, 0, ACS_LTEE);
        mvwhline(my_menu_win, 2, 1, ACS_HLINE, 38);
        mvwaddch(my_menu_win, 2, 39, ACS_RTEE);
        post_menu(my_menu);
        wrefresh(my_menu_win);
        refresh();
      }else if(strcmp(item_name(current_item(my_menu)),"Salir")==0){
        endwin();
        return 0;
      }else if(strcmp(item_name(current_item(my_menu)),"1 jugador")==0){
	erase();
	do{
	  init();
	  board();
	}while(jugar1p());
  erase();
     box(my_menu_win, 0, 0);
        print_in_middle(my_menu_win, 1, 0, 40, "3 en raya", COLOR_PAIR(1));
        mvwaddch(my_menu_win, 2, 0, ACS_LTEE);
        mvwhline(my_menu_win, 2, 1, ACS_HLINE, 38);
        mvwaddch(my_menu_win, 2, 39, ACS_RTEE);
        post_menu(my_menu);
        wrefresh(my_menu_win);
        refresh(); }

      break;
    }
    wrefresh(my_menu_win);

  }
  free_item(my_items[0]);
  free_item(my_items[1]);
  endwin();
  return 0;
}


void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string, chtype color)
{ int length, x, y;
  float temp;

  if(win == NULL)
    win = stdscr;
  getyx(win, y, x);
  if(startx != 0)
    x = startx;
  if(starty != 0)
    y = starty;
  if(width == 0)
    width = 80;

  length = strlen(string);
  temp = (width - length)/ 2;
  x = startx + (int)temp;
  wattron(win, color);
  mvwprintw(win, y, x, "%s", string);
  wattroff(win, color);
  refresh();
} 
