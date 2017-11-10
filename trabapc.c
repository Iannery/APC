/* 
Universidade de Brasilia
Instituto de Ciencias Exatas
Departamento de Ciencia da Computacao
Algoritmos e Programação de Computadores – 2/2017
Aluno(a): Ian Nery Bandeira
Matricula: 17/0144739
Turma: A
Versão do compilador: gcc (Ubuntu 6.3.0-12ubuntu2) 6.3.0 20170406
Descricao: < breve descricao do programa > */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/*valor médio que a bomba levará para explodir (turnos)*/
#define MEDIA_TEMPO 6
/* erro da medida de tempo que a bomba levará para explodir (turnos)*/
#define ERRO_TEMPO 4
/* expressão que gera um número aleatório no intervalo [M - E, M + E]*/
#define RAND (MEDIA_TEMPO + (rand() % (2* ERRO_TEMPO + 1) - ERRO_TEMPO))
#ifdef _WIN32
#define CLEAR system("cls");
#else
#define CLEAR system("clear");
#endif
#define MENUMAIN_JOGAR 1
#define MENUMAIN_CONFIGURACOES 2
#define MENUMAIN_RANKING 3
#define MENUMAIN_INSTRUCOES 4
#define MENUMAIN_SAIR 5
#define NORTE 'w'
#define OESTE 'a'
#define LESTE 'd'
#define SUL 's'
#define BOLD        "\x1b[1m"
#define ITALICO     "\x1b[3m"
#define REVERSE     "\x1b[7m"
#define VERMELHO    "\x1B[31m"
#define VERDE       "\x1B[32m"
#define AMARELO	    "\x1B[33m"
#define AZUL		"\x1B[34m"
#define MAGENTA	    "\x1B[35m"
#define CIANO		"\x1B[36m"
#define NORMAL 	    "\x1B[0m"
char tabuleiro[20][20];
int temporario[20][20];
int altura = 20, largura = 20;
int vetaxisX[100];
int vetaxisB[100];
int quantO, quantB, quantX;
int tamanhoB, loucuraX, tamanhoQ;
int tempo = 1;
void apres();
void menu();
void mapcreate();
void mapprint();
void movC();
void movX();
void jogar();
void configuracoes();
void ranking();
void instrucoes();
void sair();

void apres()
{
	CLEAR;
	printf(NORMAL "Bem-vindo ao " BOLD "CMAN, O COMEDOR DE O's™\n");
	 /*Solicita que o usuario aperte ENTER para continuar o programa*/
    printf(NORMAL "Pressione " BOLD "ENTER" NORMAL " se deseja jogar " ITALICO "Cman, o comedor de O's™" NORMAL);
    getchar();
}
void menu()
{
	CLEAR;
	int Num_Menu;
	printf(BOLD VERDE "1 - Jogar\n" NORMAL BOLD "2 - Configuracoes\n3 - Ranking\n4 - Instrucoes\n" VERMELHO "5 - Sair\n\n" NORMAL "Escolha uma opcao: ");

	scanf("%d", &Num_Menu);
	switch(Num_Menu)
	{
		case MENUMAIN_JOGAR: 
			jogar(); 
			break;
		case MENUMAIN_CONFIGURACOES: 
			configuracoes(); 
			break;
		case MENUMAIN_RANKING: 
			ranking(); 
			break;
		case MENUMAIN_INSTRUCOES: 
			instrucoes(); 
			break;
		case MENUMAIN_SAIR: 
			sair(); 
			break;
		default:
			exit(EXIT_FAILURE);
	}
}
int randomaxis()
/* A chamada da funcao determina eixo randomico no qual um personagem surge. */
{
	int axis;
	axis = rand() % 20;
	return axis;
}
void randommov(int* i, int* j, char CharMov, char CharAux1, char CharAux2, char CharAux3, char CharAux4,  char CharAux5) 
/* A chamada da funcao determina um movimento aleatorio da variavel CharMov, considerando o fato de que nao pode haver colisoes entre CharMov e os personagens do jogo CharAux(1...4). */
{
	int mov;
	mov = rand() % 4;
	switch(mov)
	{
		case 0:
			if(*i == 0 || tabuleiro[*i - 1][*j]  == CharAux1 || tabuleiro[*i - 1][*j] == CharAux2 || tabuleiro[*i - 1][*j] == CharAux3 || tabuleiro[*i - 1][*j] == CharAux4 || tabuleiro[*i - 1][*j] == CharAux5)
			{
				break;
			}
			else
				tabuleiro[*i - 1][*j] = CharMov;
				tabuleiro[*i][*j] = '.';
				*i = *i - 1;
				break;
		case 1:
			if(*i == 19 || tabuleiro[*i + 1][*j]  == CharAux1 || tabuleiro[*i + 1][*j] == CharAux2 || tabuleiro[*i + 1][*j] == CharAux3 || tabuleiro[*i + 1][*j] == CharAux4 || tabuleiro[*i + 1][*j] == CharAux5)
			{
				break;
			}
			else
				tabuleiro[*i + 1][*j] = CharMov;
				tabuleiro[*i][*j] = '.';
				*i = *i + 1;
				break;
		case 2:
			if(*j == 19 || tabuleiro[*i][*j + 1]  == CharAux1 || tabuleiro[*i][*j + 1] == CharAux2 || tabuleiro[*i][*j + 1] == CharAux3 || tabuleiro[*i][*j + 1] == CharAux4 || tabuleiro[*i][*j + 1] == CharAux5)
			{
				break;
			}
			else
				tabuleiro[*i][*j + 1] = CharMov;
				tabuleiro[*i][*j] = '.';
				*j = *j + 1;
				break;
		case 3:
			if(*j == 0 || tabuleiro[*i][*j - 1]  == CharAux1 || tabuleiro[*i][*j - 1] == CharAux2 || tabuleiro[*i][*j - 1] == CharAux3 || tabuleiro[*i][*j - 1] == CharAux4 || tabuleiro[*i][*j - 1] == CharAux5)
			{
				break;
			}
			else
				tabuleiro[*i][*j - 1] = CharMov;
				tabuleiro[*i][*j] = '.';
				*j = *j - 1;
				break;
	}
}
void randommovb(int* i, int* j, char CharMov, char CharAux1, char CharAux2, char CharAux3, char CharAux4) 
/* A chamada da funcao determina um movimento aleatorio da variavel CharMov, considerando o fato de que nao pode haver colisoes entre CharMov e os personagens do jogo CharAux(1...4). */
{
	int vetaux[20];
	int mov;
	int i1, j1;
	mov = rand() % 4;
	switch(mov)
	{
		case 0:
			if(*i == 0 || tabuleiro[*i - 1][*j]  == CharAux1 || tabuleiro[*i - 1][*j] == CharAux2 || tabuleiro[*i - 1][*j] == CharAux3 || tabuleiro[*i - 1][*j] == CharAux4)
			{
				break;
			}
			else
				tabuleiro[*i - 1][*j] = CharMov;
				temporario[*i - 1][*j] = tempo;
				*i = *i - 1;
				break;
		case 1:
			if(*i == 19 || tabuleiro[*i + 1][*j]  == CharAux1 || tabuleiro[*i + 1][*j] == CharAux2 || tabuleiro[*i + 1][*j] == CharAux3 || tabuleiro[*i + 1][*j] == CharAux4)
			{
				break;
			}
			else
				tabuleiro[*i + 1][*j] = CharMov;
				temporario[*i + 1][*j] = tempo;
				*i = *i + 1;
				break;
		case 2:
			if(*j == 19 || tabuleiro[*i][*j + 1]  == CharAux1 || tabuleiro[*i][*j + 1] == CharAux2 || tabuleiro[*i][*j + 1] == CharAux3 || tabuleiro[*i][*j + 1] == CharAux4)
			{
				break;
			}
			else
				tabuleiro[*i][*j + 1] = CharMov;
				temporario[*i][*j + 1] = tempo;
				*j = *j + 1;
				break;
		case 3:
			if(*j == 0 || tabuleiro[*i][*j - 1]  == CharAux1 || tabuleiro[*i][*j - 1] == CharAux2 || tabuleiro[*i][*j - 1] == CharAux3 || tabuleiro[*i][*j - 1] == CharAux4)
			{
				break;
			}
			else
				tabuleiro[*i][*j - 1] = CharMov;
				temporario[*i][*j - 1] = tempo;
				*j = *j - 1;
				break;
	}
	if(tempo >= 6)
	{
		// printf("%d\n", tempo);
		for(i1 = 0; i1 < 20; i1++)
		{
			for(j1 = 0; j1 < 20; j1++)
			{
				if(temporario[i1][j1] == tempo - 5)
				{
					tabuleiro[i1][j1] = '.';
				}
			}
		}
	}
}	
void mapcreate(int* CaxisX, int* CaxisY)
/* Cria o mapa no qual o jogo rodará. */
{
	int Xaxis, Baxis, OaxisX, OaxisY, QaxisX, QaxisY;
	int i, j, k;
	for(i = 0; i < altura; i++)
	{
		for(j = 0; j < largura; j++)
		{
			tabuleiro[i][j] = '.';
		}
	}
	*CaxisX = randomaxis();
	*CaxisY = randomaxis();
	tabuleiro[*CaxisX][*CaxisY] = 'C';
	for(k = 0; k < 4; k++)
	{
		Xaxis = randomaxis();
		vetaxisX[k] = Xaxis;
	}
	for(quantX = 0; quantX < 4; quantX += 2)
	{
		tabuleiro[vetaxisX[quantX]][vetaxisX[quantX + 1]] = 'X';
	}
	for(k = 0; k < 6; k++)
	{
		Baxis = randomaxis();
		vetaxisB[k] = Baxis;
	}
	for(quantB = 0; quantB < 6; quantB += 2)
	{
		tabuleiro[vetaxisB[quantB]][vetaxisB[quantB + 1]] = 'B';
		temporario[vetaxisB[quantB]][vetaxisB[quantB + 1]] = tempo;
	}
	for(quantO = 0; quantO < 2; quantO++)
	{
		OaxisX = randomaxis();
		OaxisY = randomaxis();
		tabuleiro[OaxisX][OaxisY] = 'O';
	}
}
void mapprint(int qtd_mov, int pontos)
/* Mostra na tela o mapa. */
{
	int i, j;
	printf("Pontos : %d\tJogadas Restantes : %d\n\n", pontos, qtd_mov);
	for(i = 0; i < altura; i++)
	{
		for(j = 0; j < largura; j++)
		{
			if(tabuleiro[i][j] == 'X')
			{
				printf(BOLD VERMELHO"%c "NORMAL, tabuleiro[i][j]);	
			}
			else if(tabuleiro[i][j] == 'C')
			{
				printf(BOLD VERDE"%c " NORMAL, tabuleiro[i][j]);
			}
			else if(tabuleiro[i][j] == 'O')
			{
				printf(BOLD AZUL "%c " NORMAL, tabuleiro[i][j]);	
			}
			else if(tabuleiro[i][j] == 'B')
			{
				printf(BOLD "%c " NORMAL, tabuleiro[i][j]);	
			}
			else
			{
				printf("%c ", tabuleiro[i][j]);
			}
		}
		printf("\n");
	}
}
void movC(int* CaxisX, int* CaxisY, int* pontos, int* contponto)
/* A funcao determina o movimento de C, utilizando das teclas WASD do teclado. Ao digitar algo diferente de WASD, o movimento de C é aleatorio. */
{
	char Direcao;
	scanf(" %c", &Direcao);
	switch(Direcao)
	{
		case NORTE:
			if(*CaxisX == 0 || tabuleiro[*CaxisX - 1][*CaxisY]  == 'X' || tabuleiro[*CaxisX - 1][*CaxisY] == 'B' || tabuleiro[*CaxisX - 1][*CaxisY] == 'Q')
			{
				break;
			}
			else
			{
				if(tabuleiro[*CaxisX - 1][*CaxisY] == 'O')
				{
					*pontos = *pontos + 50;
					(*contponto)++;
				}
				tabuleiro[*CaxisX - 1][*CaxisY] = 'C';
				tabuleiro[*CaxisX][*CaxisY] = '.';
				*CaxisX = *CaxisX - 1;
				break;
			}
		case SUL:
			if(*CaxisX == 19 || tabuleiro[*CaxisX + 1][*CaxisY]  == 'X' || tabuleiro[*CaxisX + 1][*CaxisY] == 'B' || tabuleiro[*CaxisX + 1][*CaxisY] == 'Q')
			{
				break;
			}
			else
				if(tabuleiro[*CaxisX + 1][*CaxisY] == 'O')
				{
					*pontos = *pontos + 50;
					(*contponto)++;
				}
				tabuleiro[*CaxisX + 1][*CaxisY] = 'C';
				tabuleiro[*CaxisX][*CaxisY] = '.';
				*CaxisX = *CaxisX + 1;
				break;
		case LESTE:
			if(*CaxisY == 19 || tabuleiro[*CaxisX][*CaxisY + 1]  == 'X' || tabuleiro[*CaxisX][*CaxisY + 1] == 'B' || tabuleiro[*CaxisX][*CaxisY + 1] == 'Q')
			{
				break;
			}
			else
				if(tabuleiro[*CaxisX][*CaxisY + 1] == 'O')
				{
					*pontos = *pontos + 50;
					(*contponto)++;
				}
				tabuleiro[*CaxisX][*CaxisY + 1] = 'C';
				tabuleiro[*CaxisX][*CaxisY] = '.';
				*CaxisY = *CaxisY + 1;
				break;
		case OESTE:
			if(*CaxisY == 0 || tabuleiro[*CaxisX][*CaxisY - 1]  == 'X' || tabuleiro[*CaxisX][*CaxisY - 1] == 'B' || tabuleiro[*CaxisX][*CaxisY - 1] == 'Q')
			{
				break;
			}
			else
				if(tabuleiro[*CaxisX][*CaxisY - 1] == 'O')
				{
					*pontos = *pontos + 50;
					(*contponto)++;
				}
				tabuleiro[*CaxisX][*CaxisY - 1] = 'C';
				tabuleiro[*CaxisX][*CaxisY] = '.';
				*CaxisY = *CaxisY - 1;
				break;
		default:
			randommov(CaxisX, CaxisY, 'C', 'X', 'B', 'Q', '0', '0');
			break;
	}
}
void movX(int* XaxisX,int* XaxisY, int CaxisX, int CaxisY, int* game_over)
{
	/* ARRUMAR SOBREPOSIÇÃO DE X SOBRE OS OUTRO AMIGUINHO */
	int auxrand;
	loucuraX = rand() % 3;
	auxrand = rand() % 2;
	if(loucuraX == 0)
	{
		randommov(XaxisX, XaxisY, 'X', 'C', 'B', 'Q', 'O', 'X'); /* BOTAR X AQUI TAMBEM  */
	}
	else
	{
		if(CaxisX > *XaxisX)
		{
			if(CaxisY > *XaxisY)
			{
				if(auxrand)
				{
					if(*XaxisY == 19 || tabuleiro[*XaxisX][*XaxisY + 1]  == 'O' || tabuleiro[*XaxisX][*XaxisY + 1] == 'B' || tabuleiro[*XaxisX][*XaxisY + 1] == 'Q' || tabuleiro[*XaxisX][*XaxisY + 1] == 'X')
					{

					}
					else
					{
						/* MOV PARA DIREITA */
						tabuleiro[*XaxisX][*XaxisY + 1] = 'X';
						tabuleiro[*XaxisX][*XaxisY] = '.';
						*XaxisY = *XaxisY + 1;
					}
				}
				else
				{
					if(*XaxisX == 19 || tabuleiro[*XaxisX + 1][*XaxisY]  == 'O' || tabuleiro[*XaxisX + 1][*XaxisY] == 'B' || tabuleiro[*XaxisX + 1][*XaxisY] == 'Q' || tabuleiro[*XaxisX + 1][*XaxisY] == 'X')
					{
			
					}
					else
					{
						/* MOV PARA BAIXO */
						tabuleiro[*XaxisX + 1][*XaxisY] = 'X';
						tabuleiro[*XaxisX][*XaxisY] = '.';
						*XaxisX = *XaxisX + 1;
					}
				}
			}
			else if(CaxisY < *XaxisY)
			{
				if(auxrand)
				{
					if(*XaxisY == 0 || tabuleiro[*XaxisX][*XaxisY - 1]  == 'O' || tabuleiro[*XaxisX][*XaxisY - 1] == 'B' || tabuleiro[*XaxisX][*XaxisY - 1] == 'Q' || tabuleiro[*XaxisX][*XaxisY - 1] == 'X')
					{
					
					}
					else
					{
						/* MOV PARA ESQUERDA */
						tabuleiro[*XaxisX][*XaxisY - 1] = 'X';
						tabuleiro[*XaxisX][*XaxisY] = '.';
						*XaxisY = *XaxisY - 1;
					}
				}
				else
				{
					if(*XaxisX == 19 || tabuleiro[*XaxisX + 1][*XaxisY]  == 'O' || tabuleiro[*XaxisX + 1][*XaxisY] == 'B' || tabuleiro[*XaxisX + 1][*XaxisY] == 'Q' || tabuleiro[*XaxisX - 1][*XaxisY] == 'X')
					{
			
					}
					else
					{
						/* MOV PARA BAIXO */
						tabuleiro[*XaxisX + 1][*XaxisY] = 'X';
						tabuleiro[*XaxisX][*XaxisY] = '.';
						*XaxisX = *XaxisX + 1;
					}
				}
			}
			else
			{
				if(*XaxisX == 19 || tabuleiro[*XaxisX + 1][*XaxisY]  == 'O' || tabuleiro[*XaxisX + 1][*XaxisY] == 'B' || tabuleiro[*XaxisX + 1][*XaxisY] == 'Q' || tabuleiro[*XaxisX + 1][*XaxisY] == 'X')
				{

				}
				else
				{
					/* MOV PARA BAIXO */
					tabuleiro[*XaxisX + 1][*XaxisY] = 'X';
					tabuleiro[*XaxisX][*XaxisY] = '.';
					*XaxisX = *XaxisX + 1;
				}
			}
		}
		else if(CaxisX < *XaxisX)
		{
			if(CaxisY > *XaxisY)
			{
				if(auxrand)
				{
					if(*XaxisY == 19 || tabuleiro[*XaxisX][*XaxisY + 1]  == 'O' || tabuleiro[*XaxisX][*XaxisY + 1] == 'B' || tabuleiro[*XaxisX][*XaxisY + 1] == 'Q' || tabuleiro[*XaxisX][*XaxisY + 1] == 'X')
					{

					}
					else
					{
						/* MOV PARA DIREITA */
						tabuleiro[*XaxisX][*XaxisY + 1] = 'X';
						tabuleiro[*XaxisX][*XaxisY] = '.';
						*XaxisY = *XaxisY + 1;
					}
				}
				else
				{
					if(*XaxisX == 0 || tabuleiro[*XaxisX - 1][*XaxisY]  == 'O' || tabuleiro[*XaxisX - 1][*XaxisY] == 'B' || tabuleiro[*XaxisX - 1][*XaxisY] == 'Q' || tabuleiro[*XaxisX - 1][*XaxisY] == 'X')
					{
					
					}
					else
					{
						/* MOV PARA CIMA */
						tabuleiro[*XaxisX - 1][*XaxisY] = 'X';
						tabuleiro[*XaxisX][*XaxisY] = '.';
						*XaxisX = *XaxisX - 1;
					}
				}
			}
			else if(CaxisY < *XaxisY)
			{
				if(auxrand)
				{
					if(*XaxisY == 0 || tabuleiro[*XaxisX][*XaxisY - 1]  == 'O' || tabuleiro[*XaxisX][*XaxisY - 1] == 'B' || tabuleiro[*XaxisX][*XaxisY - 1] == 'Q' || tabuleiro[*XaxisX][*XaxisY - 1] == 'X')
					{
					
					}
					else
					{
						/* MOV PARA ESQUERDA */
						tabuleiro[*XaxisX][*XaxisY - 1] = 'X';
						tabuleiro[*XaxisX][*XaxisY] = '.';
						*XaxisY = *XaxisY - 1;
					}
				}
				else
				{
					if(*XaxisX == 0 || tabuleiro[*XaxisX - 1][*XaxisY]  == 'X' || tabuleiro[*XaxisX - 1][*XaxisY] == 'B' || tabuleiro[*XaxisX - 1][*XaxisY] == 'Q' || tabuleiro[*XaxisX - 1][*XaxisY] == 'X')
					{
					
					}
					else
					{
						/* MOV PARA CIMA */
						tabuleiro[*XaxisX - 1][*XaxisY] = 'X';
						tabuleiro[*XaxisX][*XaxisY] = '.';
						*XaxisX = *XaxisX - 1;
					}
				}
			}
			else
			{
				if(*XaxisX == 0 || tabuleiro[*XaxisX - 1][*XaxisY]  == 'O' || tabuleiro[*XaxisX - 1][*XaxisY] == 'B' || tabuleiro[*XaxisX - 1][*XaxisY] == 'Q' || tabuleiro[*XaxisX - 1][*XaxisY] == 'X')
				{
				
				}
				else
				{
					/* MOV PARA CIMA */
					tabuleiro[*XaxisX - 1][*XaxisY] = 'X';
					tabuleiro[*XaxisX][*XaxisY] = '.';
					*XaxisX = *XaxisX - 1;
				}
			}
		}
		else
		{
			if(CaxisY > *XaxisY)
			{
				if(*XaxisY == 19 || tabuleiro[*XaxisX][*XaxisY + 1]  == 'O' || tabuleiro[*XaxisX][*XaxisY + 1] == 'B' || tabuleiro[*XaxisX][*XaxisY + 1] == 'Q' || tabuleiro[*XaxisX][*XaxisY + 1] == 'X')
				{

				}
				else
				{
					/* MOV PARA DIREITA */
					tabuleiro[*XaxisX][*XaxisY + 1] = 'X';
					tabuleiro[*XaxisX][*XaxisY] = '.';
					*XaxisY = *XaxisY + 1;
				}
			}
			else
			{
				if(*XaxisY == 0 || tabuleiro[*XaxisX][*XaxisY - 1]  == 'O' || tabuleiro[*XaxisX][*XaxisY - 1] == 'B' || tabuleiro[*XaxisX][*XaxisY - 1] == 'Q' || tabuleiro[*XaxisX][*XaxisY - 1] == 'X')
				{
				
				}
				else
				{
					/* MOV PARA ESQUERDA */
					tabuleiro[*XaxisX][*XaxisY - 1] = 'X';
					tabuleiro[*XaxisX][*XaxisY] = '.';
					*XaxisY = *XaxisY - 1;
				}
			}
		}
	}
	if(((CaxisX == *XaxisX + 1 || CaxisX == *XaxisX - 1 ) && (CaxisY == *XaxisY)) || ((CaxisY == *XaxisY + 1 || CaxisY == *XaxisY - 1) && (CaxisX == *XaxisX)) || (CaxisX == *XaxisX && CaxisY == *XaxisY))
	{
		*game_over = 1;
	}
}
void movB(int* BaxisX, int* BaxisY)
{
	randommovb(BaxisX, BaxisY, 'B', 'C', 'X', 'O', 'Q');

}
void spawnQ(int* QaxisX, int* QaxisY)
{
	*QaxisX = rand() % 20;
	*QaxisY = rand() % 20;
	tabuleiro[*QaxisX][*QaxisY] = 'Q';
}
void explosQ(int QaxisX, int QaxisY, int* game_over, int* Qup)
{

	int i, randexplosao;
	randexplosao = RAND;
	if(randexplosao == 4)
	{
		for(i = 0; i < 8; i++)
		{
			if(QaxisX + i == 19)
			{
				break;
			}
			else
			tabuleiro[QaxisX + i][QaxisY] = '#';
		}
		for(i = 0; i < 8; i++)
		{
			if(QaxisX + i == 19)
			{
				break;
			}
			tabuleiro[QaxisX - i][QaxisY] = '#';
		}
		for(i = 0; i < 8; i++)
		{
			if(QaxisX + i == 19)
			{
				break;
			}
			tabuleiro[QaxisX][QaxisY + i] = '#';
		}
		for(i = 0; i < 8; i++)
		{
			if(QaxisX + i == 19)
			{
				break;
			}
			tabuleiro[QaxisX][QaxisY - i] = '#';
		}
		*Qup = 0;
		printf("EXPLODIU\n");
	}
}
void backtonormalQ()
{
	int i, j;
	for(i = 0; i < 20; i++)
	{
		for(j = 0; j < 20; j++)
		{
			if(tabuleiro[i][j] == '#')
			{
				tabuleiro[i][j] = '.';
			}
		}
	}
}
void jogar()
{	
	int game_over = 0, qtd_mov = 250, pontos = 0, contponto = 0, Qup = 0, Qexplos = 0, indicespawnQ, CaxisX, CaxisY, QaxisX, QaxisY;
	mapcreate(&CaxisX, &CaxisY);
	while(!game_over && qtd_mov >= 0)
	{
		CLEAR;
		mapprint(qtd_mov, pontos);
		if(Qexplos)
		{
			printf("ENTROU!1!\n");
			backtonormalQ(QaxisX, QaxisY);
			Qexplos = 0;
		}
		movC(&CaxisX, &CaxisY, &pontos, &contponto);
		pontos++;
		for(quantX = 0; quantX < 4; quantX += 2)
		{
			movX(&vetaxisX[quantX], &vetaxisX[quantX + 1], CaxisX, CaxisY, &game_over);
		}
		for(quantB = 0; quantB < 6; quantB += 2)
		{
			movB(&vetaxisB[quantB], &vetaxisB[quantB + 1]); /* TEM Q FAZER UM VETOR PRA GUARDAR A POSIÇÃO DO RASTRO */
		}
		tempo++;
		qtd_mov--;
		if(contponto == 2)
		{
			game_over = 1;
		}
		indicespawnQ = rand() % 5;
		if(tempo >= 4 && indicespawnQ == 0 && !Qup)
		{
			printf("SPANWO\n");
			spawnQ(&QaxisX, &QaxisY);
			Qup = 1;
		}
		if(Qup)
		{
			explosQ(QaxisX, QaxisY, &game_over, &Qup);
			Qexplos = 1;
		}
	}
	if(game_over)
	{
		mapprint(qtd_mov, pontos);
		printf("GAME OVER.\n");
		printf("Voce adquiriu %d pontos em %d jogadas.\n\n", pontos, 250 - qtd_mov);
		printf("Pressione enter para voltar ao menu.\n");
		getchar();
		getchar();
		menu();
	}
	menu();
}
void configuracoes()
{
	CLEAR;
	menu();
}
void ranking()
{
	CLEAR;
	menu();
}
void instrucoes()
{
	CLEAR;
	printf("O jogo CMan e um jogo cujo objetivo eh coletar todos os pontos O no menor numero de jogadas possivel, sem ser morto pelos inimigos X ou explodidos pela bomba Q.\n \nPersonagens do jogo: \n \n- C : Avatar do jogador, pode se mover para norte, oeste, sul e leste, utilizando dos controles W, A, S, D; respectivamente.\nO avatar nao pode ficar parado durante um turno e caso seja utilizada uma tecla diferente das Padroes de movimento, sera apresentada uma mensagem de erro e realizado um movimento aleatorio.\n \n- X : Inimigo do jogador, persegue o avatar e caso se encontrem, o personagem morrera e o jogo sera finalizado.\nPersegue o jogador, exceto quando esta em frenesi, quando tal se move aleatoriamente na area de jogo.\n \n- B : Inimigo Passivo, o qual deixa um rastro de padrao 2 quadros por onde esse se move, sempre aleatorio. Impede a passagem do jogador.\n \n- O : Pontos de jogo, perseguidos pelo jogador para a finalizacao do jogo.\n \n- Q : Inimigo bomba, aparece aleatoriamente no tabuleiro durante o jogo a cada certo período de tempo, e apos um certo tempo explode matando o jogador caso ele esteja a area de explosao, cuja area e ocupada por 8 posicoes do tabuleiro, por default.\n \n \n");
	printf("Pressione enter para voltar ao menu:\n");
	getchar();
	getchar();
	menu();
}
void sair()
{
	CLEAR;
	printf("E isso pessoal, tamo juntissimo\n");
}
int main()
{
	srand(time(0));
	apres();
	menu();

	return 0;
}