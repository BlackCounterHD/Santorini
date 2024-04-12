
#include "smekerie.h"

#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_WHITE   "\x1b[37m"

typedef struct map {
	int building_level;
	int player_movement;
}M;

typedef struct coord_worker {
	int x;
	int y;
}worker;

typedef struct player {
	char player_name[100];
	char player_color[20];
	worker boy, girl;
	int want_god;
}P;

typedef struct buildings {

	    int level1;
		int level2;
		int level3;
		int domes;
}B;

void init_map(M e[][5], int k) {

	int i,j;
	for (i = 0; i <=k; i++)
		for (j = 0; j <= k; j++)
		{
			e[i][j].building_level = 0;
			e[i][j].player_movement = 0;
		}
	 
	//return e;
	     
}

void configure_player(P* p) {

		for (int i = 0; i < 2; ++i) {
			printf("Player%d please enter your name : \n", i + 1);
			fgets(p[i].player_name, sizeof(p[i].player_name), stdin);
			printf("Player%d please choose your color (red,green,yellow,cyan,blue,white,magenta) : \n",i + 1);
			fgets(p[i].player_color, sizeof(p[i].player_color), stdin);
			printf("Player%d do you want to choose a god ? (1 for yes, 0 for no) : \n",i+1);
			(void)scanf("%d", &p[i].want_god);
			(void)getchar();
			if (p[i].want_god == 1)
				printf("Your God is Demeter => Your Worker may build one additional time but not on the same space\n");
		}
}

void player_color(P* p,int i) {

	switch (p[i].player_color[0])
	{
	case 'r':
		printf(ANSI_COLOR_RED);
		break;
	case 'g':
		printf(ANSI_COLOR_GREEN);
		break;
	case 'y':
		printf(ANSI_COLOR_YELLOW);
		break;
	case 'b':
		printf(ANSI_COLOR_BLUE);
		break;
	case 'm':
		printf(ANSI_COLOR_MAGENTA);
		break;
	case 'c':
		printf(ANSI_COLOR_CYAN);
		break;
	case 'w':
		printf(ANSI_COLOR_WHITE);
		break;
	default:
		printf(ANSI_COLOR_RESET);
		break;
	}
	printf("%s", p[i].player_name);
	printf(ANSI_COLOR_RESET);
}

void print_worker(int x) {
	if (x == 1)
		printf("Boy");
	else
		printf("Girl");
}

void init_buildings(B* b) {
	b->domes = 18; //18 domes
	b->level1 = 22;  //22 level1 
	b->level2 = 18;   //18 level2
	b->level3 = 14;   //14 level3

}

void print_bulding_materials(B* b) {

	printf("There are %d domes left \n", b->domes);
	printf("There are %d level1 left \n", b->level1);
	printf("There are %d level2 left \n", b->level2);
	printf("There are %d level3 left \n", b->level3);

}

void print_map(M e[][5], int k) {
	int i, j;
	for (i = 0; i <= k; i++) {
		for (j = 0; j <= k; j++)
			printf("%d ", e[i][j].player_movement);
		printf("\t");
		for (j = 0; j <= k; j++)
			printf("%d ", e[i][j].building_level);
		printf("\n");
	}
}

int win_condition(M e[][5],int k) {
	
	int i, j;
	for (i = 0; i <= k; i++) 
		for (j = 0; j <= k; j++)
			if (e[i][j].building_level == 3 && e[i][j].player_movement == 1)
				return 1;
			else
				return 0;
	return 0;
	
}

void verf_worker_position(M e[][5], P* p,int k,int x, int u, int v) {

	while (u > 4 || v > 4 || e[u][v].player_movement == 1) {
		printf("Coordinates need to be smaller or equal to 4 and different from the other workers :)\n");
		while (scanf("%d %d", &u, &v) != 2) {
			printf("Invalid input\n");
			while (getchar() != '\n');
		}
	}
	e[u][v].player_movement = 1;
	if (x == 1) {
		p[k].boy.x = u;
		p[k].boy.y = v;
	}
	else
	{
		p[k].girl.x = u;
		p[k].girl.y = v;
	}
	
}

void place_buildings(M e[][5]) {

	int u, v;
	printf("Choose the coordinates where you want to build : (x and y)\n");
	while (scanf("%d %d", &u, &v) != 2) {
		printf("Invalid input\n");
		while (getchar() != '\n');
	}
}

void place_workers(M e[][5],P *p,int k,int *t,B *b) {


	int x,u,v,i,t1=-1,t2=-1;
	for (i = 0; i < 2; i++) {
		player_color(p, 0);
		printf("Choose the Boy/Girl Worker (1 for Boy and 0 for Girl) : \n");
		while (scanf("%d", &x) != 1) {
			printf("Invalid input\n");
			while (getchar() != '\n');
		}
		if (x == t1) {
			x =abs(t1-1);
		}
		if (i == 0)
			t1 = x;
		printf("You chose the : ");
		print_worker(x);
		printf("\n");
		printf("Now choose the coordinates for your  Worker : (x and y)\n");
		while (scanf("%d %d", &u, &v) != 2) {
			printf("Invalid input\n");
			while (getchar() != '\n');
		}
		verf_worker_position(e, p, 0, x, u, v);
		print_map(e, k);
		print_bulding_materials(b);
		player_color(p, 1);
		printf("Choose the Boy/Girl Worker (1 for Boy and 0 for Girl) : \n");
		while (scanf("%d", &x) != 1) {
			printf("Invalid input\n");
			while (getchar() != '\n');
		}
		if (x == t2) {
			x = abs(t2 - 1);
		}
		if (i == 0)
			t2 = x;
		printf("You chose the : ");
		print_worker(x);
		printf("\n");
		printf("Now choose the coordinates for your  Worker : (x and y)\n");
		while (scanf("%d %d", &u, &v) != 2) {
			printf("Invalid input\n");
			while (getchar() != '\n');
		}
		verf_worker_position(e, p, 1, x, u, v);
		print_map(e, k);
		print_bulding_materials(b);

	}
}

void take_turns(M e[][5], P* p,B *b,int k,int *t) {

	(*t)++;
	do {
		place_workers(e, p,k,t,b);
	} while (win_condition(e, k) == 0);
	

}


int main() {
	
	M e[5][5];
	P p[2];
	B b;
	int k = 4;
	int t = 0;
	init_map(e, k);
	init_buildings(&b);
	configure_player(p);
	place_workers(e,p,k,&t,&b);
	//take_turns(e, p,k);
	/*
	for (i = 0; i <= 1; i++) {
		printf("%d\n",strlen(p[1].player_name));
		printf("%s %s", p[i].player_name, p[i].player_color);
		printf("\n");
	}
	*/
	
}