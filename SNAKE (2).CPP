#include <iostream.h>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <dos.h>
#include <time.h>

int far * scr  = ( int far * ) 0XB8000000 ;		//global shode chon badan be dard mikhore!

int sx[100] ;		//x snake
int sy[100] ;
int xwall[100];
int ywall[100];		//y snake
int slen = 3;		//toole mar
int x = 40;
int y = 12;
int m = 0;		//2 yani samte rast harekat kone (to tabe paiin tar tarif sho
int ifo;
int jfo;
int sizef = 1;
int lost= 0;
char c;
int rl = 1;
int ud = 0;
int iwall;
int jwall;
int win = 0;
int last = 0;
int zaman = 1;
int winf = 0;

char funckey( int &T)		//tabe baraye shenasoondane dokme haye keyboard
{
	char c = getch();

	if(c==0)
	{
		T=1;
		c=getch();
	}
	else
		T=0;

	return c ;
}

void chap(int x,int y,int c,int color,int islight,int bgcolor,int isBlink)
{

	int far * scr = ( int far * ) 0XB8000000;
	int v = color + 8*islight + 16*bgcolor + 128*isBlink ;
	scr [ y * 80 + x] = v * 256 + c ;

}

void Move(m) {

	for (int i=slen-1; i>0; i-- ) {
		sx[i] = sx[i-1] ;
		sy[i] = sy[i-1] ;
	}

	 x = sx[0] ;
	 y = sy[0] ;

	switch (m) {
		case 0 :		//chap
			x--;
			if (x<0)
				x=79;
			break;

		case 1 :		//bala
			y--;
			if (y<0)
				y=24;
			break;
		case 2 :		//rast
			x++;
			if (x>79)
				x=0;
			break;
		case 3 :		//paiin
			y++;
			if (y>24)
				y=0;
			break;

		case -1 :
			break;
	}

	sx[0] = x;
	sy[0] = y;
}

int getKey(char key, int isfunc) {

		if(isfunc == 1) {

			switch(key) {

				case 'K':
					ud = 0;			//chap
					if (rl == 0){

			//			ud != ud;
						rl =1;
						return 0;
					}
				break ;

				case 'H':
					rl = 0;	//bala
					if ( ud == 0) {

			//			rl != rl;
						ud = 1;
						return 1;
					}
				       //	else return -1;
					 break ;

				case 'M':
					ud = 0;	//rast
					if (rl == 0){

			//			ud != ud;
						rl =1;
						return 2;
					}
				      //	else return -1;
					break ;

				case 'P':
					rl = 0;		//paiin
					if (ud == 0){

			//			rl != rl;
						ud = 1;
						return 3;
					}
				       //	else return -1;
					break;
		}
	}
	return -1;
}

void clear() {
	int i;
	int j;
		for (j=0 ; j<25 ; j++) {
			for (i=0 ; i<80 ; i++) {
			chap(i,j,' ',0,0,0,0);
			}
		}
	}


void chapsnake(){

	 for(int i=slen-1 ; i>=1 ; i--){
		 chap(sx[i],sy[i],233,1,0,7,0);
	  }
	  chap (sx[slen-1],sy[slen-1],219,0,0,0,0);
	  chap (sx[0],sy[0],':',1,0,7,0);
}

void pushfood(){

	srand(time(NULL));
	ifo = rand() %79 ;
	jfo = rand() %24 ;
	int w ;

	if (sizef == 10){
	sizef = 0;
	winf = 1;
	}

	 for (int i=0 ; i<slen-1 ; i++) {
		 if ( ifo == sx[i] && jfo == sy[i]) {
			  w = 0;
	  }
	}
	if (win == 1) {
		for (int j=0 ; j<last ; j++){
			if (ifo == xwall[j] && jfo == ywall[j]){
				w = 0;
			}
		}
	}

	if ( w ) {
		chap (ifo,jfo,48+sizef,2,0,4,0);
	}

	  else { pushfood() ;
	   }
       //	   sizef ++ ;
       //	   if (sizef == 10){
	//    winf = 1 ;
       //	    sizef = 0 ;
       //	    }
}

void food () {

	if (sx[0] == ifo && sy[0] == jfo ) {
			slen = slen + sizef ;
			sizef ++ ;
			pushfood();
	}

}

void blue () {
 int i;
 int j;
	for (i=0 ; i<79 ; i++) {
		for (j=0 ; j<24 ; j++) {
			chap (i,j,' ',0,0,1,0) ;
		}
	}
       //	sizef ++ ;
}

void loose() {
		//int last=0 ;
		int i ;

	for (i=1 ; i<slen-1 ; i++) {
		if (sx[0] == sx[i] && sy[0] == sy[i]) {
			lost ++ ;
		}
	}
	if (win==1){
		for (i=0 ; i<last ; i++){
		if (sx[0]==xwall[i] && sy[0]==ywall[i]) lost ++;
		}
	}

	if (lost != 0) {
		blue() ;
		chap (37,13,'G',4,0,1,0);
		chap (38,13,'A',4,0,1,0);
		chap (39,13,'M',4,0,1,0);
		chap (40,13,'E',4,0,1,0);
		chap (42,13,'O',4,0,1,0);
		chap (43,13,'V',4,0,1,0);
		chap (44,13,'E',4,0,1,0);
		chap (45,13,'R',4,0,1,0);
		delay (3000);
		c = 27;
	}
}

void level () {
      //	srand(time(NULL));
      //	 iwall = rand() %79;
       //	 jwall = rand() %24;
  //	int win ;
	int l;

	if (sizef == 1 && winf == 1) {
	       //	srand(time(NULL));
		iwall = rand() %79;
		jwall = rand() %24;
		for (l=0 ; l<15 ; l++){
			chap(l+iwall,jwall,177,2,0,6,0);
		}
		sizef = 1;
		winf = 0 ;
		for (l=2 ; l<slen-1 ; l++){
			chap(sx[l],sy[l],219,0,0,0,0);
			sx[l] = -1;
			sy[l] = -1;
		}

		for (l=0 ; l<15 ; l++){
			xwall[last+l] = iwall + l;
			ywall[last+l] = jwall ;
		}
		last = last + 15;
		slen = 3;
		delay(20);
		pushfood();
		win = 1;
		zaman=zaman+10;
	}
}

int main(int &m) {

    for (int i=0 ; i<3 ; i++) {
	sy[i] = 12 ;
	sx[i] = 40 + i ;
	}

       //	clear();

	//chapsnake() ;
	//Move (m);


       int isfunc;
      //int key;
       //char c;  // = funckey(isfunc);


	clear();
	pushfood();
//	c=funckey(isfunc);
//	int cont;

	while ( c!=27) {
		Move(m);
		chapsnake();
		delay(100 - zaman) ;

	       if(kbhit()) {
		       //	cont = m;
			c = funckey(isfunc);
			int cont = getKey(c, isfunc);
			if (cont > -1) m = cont ;
	       }
			food() ;
			loose() ;
			level() ;
       }


	return 0;
}