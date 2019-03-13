//O objetivo do programa é resolver um sudoku usando bakctracking.

#include <stdio.h>
#include <stdlib.h>

#define MAX 9

int conferirpos(int x, int y,int num, int mat[MAX][MAX]){       //a função retorna 1 se for uma posição possível, e 0 caso contrário
    int i, j;

    for(i=0; i<9; i++){     //confere a linha
        if(num==mat[x][i]){
            return 0;
        }
    }

    for(i=0; i<9; i++){     //confere a coluna
        if(num==mat[i][y]){
            return 0;
        }
    }

    if(x<3){        //confere os quadrados
        if(y<3){
            for(i=0;i<3;i++){
                for(j=0;j<3;j++){
                    if(mat[i][j]==num){
                        return 0;
                    }
                }
            }
        }
        if(y<6 && y>=3){
            for(i=0;i<3;i++){
                for(j=3;j<6;j++){
                    if(mat[i][j]==num){
                        return 0;
                    }
                }
            }
        }
        if(y<9 && y>=6){
            for(i=0;i<3;i++){
                for(j=6;j<9;j++){
                    if(mat[i][j]==num){
                        return 0;
                    }
                }
            }
        }
    }
    if(x>=3 && x<6){
        if(y<3){
            for(i=3;i<6;i++){
                for(j=0;j<3;j++){
                    if(mat[i][j]==num){
                        return 0;
                    }
                }
            }
        }
        if(y<6 && y>=3){
            for(i=3;i<6;i++){
                for(j=3;j<6;j++){
                    if(mat[i][j]==num){
                        return 0;
                    }
                }
            }
        }
        if(y<9 && y>=6){
            for(i=3;i<6;i++){
                for(j=6;j<9;j++){
                    if(mat[i][j]==num){
                        return 0;
                    }
                }
            }
        }
    }
    if(x<9 && x>=6){
        if(y<3){
            for(i=6;i<9;i++){
                for(j=0;j<3;j++){
                    if(mat[i][j]==num){
                        return 0;
                    }
                }
            }
        }
        if(y<6 && y>=3){
            for(i=6;i<9;i++){
                for(j=3;j<6;j++){
                    if(mat[i][j]==num){
                        return 0;
                    }
                }
            }
        }
        if(y<9 && y>=6){
            for(i=6;i<9;i++){
                for(j=6;j<9;j++){
                    if(mat[i][j]==num){
                        return 0;
                    }
                }
            }
        }
    }
    return 1;
}

void possibilidades(int x, int y,int mat[MAX][MAX], int *v){        //identifica as possibilidades de uma posição, e salva em um vetor
    int i, a=0;

    for(i=0;i<9;i++){
        v[i]=-1;
    }

    for(i=1; i<=9; i++){
        if(conferirpos(x,y,i,mat)==1){
            v[a]=i;
            a++;
        }
    }
    
    return;
}

void print_sudoku(int resposta[MAX][MAX]);

int resolve(int resposta[MAX][MAX]) {
    int v[9], pos=0, i, j, sud;

    for(i=0;i<9;i++){
        for(j=0;j<9;j++){
					if(resposta[i][j]==0){
						possibilidades(i,j,resposta,v);     //identifica as possibilidades de uma posição
              
            if(v[0]==-1){
              return 0;
            } 
            
            while(v[pos]!=-1){
            
            	resposta[i][j]=v[pos];      //testa uma possibilidade
            	print_sudoku(resposta);
            	
            	if(i==8 && j==8){
              	return 1;
            	}
        			
        			sud = resolve(resposta);
        			
            	if(sud==0){       //se não resolve, testa a próxima
              	pos++;
            	}
            
            	if(sud==1){       //se resolveu, YAY!!
              	return 1;
            	}
            }
            									
          	resposta[i][j]=0;
            print_sudoku(resposta);
           	return 0;
         }
       }
    }
    
  return 1; //aqui tem que ser return 1
}
