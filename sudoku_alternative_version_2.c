#include <stdio.h>

#define MAX 9

void print_sudoku(int resposta[MAX][MAX]);

void regiao(int matriz[MAX][MAX], int lin, int col, int *p, int *q){
	if((lin >= 0) && (lin <= 2)){
		if((col >= 0) && (col <= 2)){
			*p = 0;
			*q = 0;
		}else if((col >= 3) && (col <= 5)){
			*p = 0;
			*q = 3;
		}else if((col >= 6) && (col <= 8)){
			*p = 0;
			*q = 6;
		}
	
	}else if((lin >= 3) && (lin <= 5)){
		if((col >= 0) && (col <= 2)){
			*p = 3;
			*q = 0;
		}else if((col >= 3) && (col <= 5)){
			*p = 3;
			*q = 3;
		}else if((col >= 6) && (col <= 8)){
			*p = 3;
			*q = 6;
		}
	
	}else if((lin >= 6) && (lin <= 8)){
		if((col >= 0) && (col <= 2)){
			*p = 6;
			*q = 0;
		}else if((col >= 3) && (col <= 5)){
			*p = 6;
			*q = 3;
		}else if((col >= 6) && (col <= 8)){
			*p = 6;
			*q = 6;
		}
	}
	return;
}

int resolve(int resposta[MAX][MAX]){
	int l, m, a, b, h=0, w=0, soma=0, resolucao;
	int possibilidades[MAX] = {1,2,3,4,5,6,7,8,9};
	
	for(l=0; l<9; l++){
		for(m=0; m<9; m++){
			if(resposta[l][m] == 0){
				for(a=0; a<9; a++){
					if(resposta[a][m] != 0){
						possibilidades[resposta[a][m]-1] = 0;
					}
				}
				
				for(a=0; a<9; a++){
					if(resposta[l][a] != 0){
						possibilidades[resposta[l][a]-1] = 0;
					}
				}
				
				regiao(resposta, l, m, &h, &w);
				
				for(a=h; a<h+3; a++){
					for(b=w; b<w+3; b++){
						if(resposta[a][b] != 0){
							possibilidades[resposta[a][b]-1] = 0;
						}
					}
				}
				
				a=0;
				while(a!=10){
					if(possibilidades[a]!=0){
						soma++;
					}
					a++;
				}
				
				if(soma == 0){
					return 0;
				}
				
				for(a=0; a<9; a++){
					if(possibilidades[a] != 0){
						resposta[l][m] = possibilidades[a];
						print_sudoku(resposta);
						
						if((soma==1) && (l==8) && (m==8)){
							return 1;
						}
						
						resolucao = resolve(resposta);
						
						if(resolucao==1){
							return 1;
						}
					}
					
					if(a==8){
						resposta[l][m] = 0;
						print_sudoku(resposta);
						return 0;
					}
				}
			}
		}
	}
	
	return 1;
}
