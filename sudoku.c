/*	NOME: BEATRIZ ARIA
	RA: 167130
	O OBJETIVO DESTE LABORATÓRIO É CRIAR UM PROGRAMA QUE RESOLVA UM JOGO DE SUDOKU.
*/
#include <stdio.h>
#include <stdlib.h>

#define MAX 9

void print_sudoku(int resposta[MAX][MAX]);

void achar(int mat[MAX][MAX], int vetor[], int k, int l){		//UMA FUNÇÃO QUE 
	int lin, col;
	
	for(lin=k; lin<(3+k); lin++){		// A FUNÇÃO PEGA A POSIÇÃO SUPEIOR ESQUERDA DA REGIÃO QUE SE DESEJA ANALISAR E FAZ UM LOOP
		for(col=l; col<(l+3); col++){
			if(mat[lin][col] != 0){
				vetor[mat[lin][col]] = 1;		//TODOS OS ELEMENTOS ENCONTRADOS SÃO SETADOS COMO 1 NO VETOR BASE
			}
		}
	}
	
	return;
}

void regiao(int matrixx[MAX][MAX], int vetore[], int p, int q){		//IDENTIFICA QUAL DOS 9 QUADRANTES MENORES A POSIÇÃO ESTÁ
	
	if((p >= 0) && (p <= 2)){
		if((q >= 0) && (q <= 2)){
			achar(matrixx, vetore, 0, 0);		//APÓS IDENTIFICAR, CHAMA A FUNÇÃO achar QUE FAZ UM LOOP NESSA REGIÃO PARA DETERMINAR AS POSSIBILIDADES
		}else if((q >= 3) && (q <= 5)){
			achar(matrixx, vetore, 0, 3);
		}else if((q >= 6) && (q <= 8)){
			achar(matrixx, vetore, 0, 6);
		}
	
	}else if((p >= 3) && (p <= 5)){
		if((q >= 0) && (q <= 2)){
			achar(matrixx, vetore, 3, 0);
		}else if((q >= 3) && (q <= 5)){
			achar(matrixx, vetore, 3, 3);
		}else if((q >= 6) && (q <= 8)){
			achar(matrixx, vetore, 3, 6);
		}
	
	}else if((p >= 6) && (p <= 8)){
		if((q >= 0) && (q <= 2)){
			achar(matrixx, vetore, 6, 0);
		}else if((q >= 3) && (q <= 5)){
			achar(matrixx, vetore, 6, 3);
		}else if((q >= 6) && (q <= 8)){
			achar(matrixx, vetore, 6, 6);
		}
	}
	
	return;
}

void verifica (int matriz[MAX][MAX], int v[], int a, int b){
	int r, c;
	
	for(r=0; r<MAX; r++){
		if(matriz[r][b] != 0){		//VERIFICA QUAIS NUMEROS JÁ EXISTEM NA COLUNA b
			v[matriz[r][b]] = 1;		//TODOS OS NUMEROS QUE ESTÃO NESSA COLUNA SÃO SETADOS COMO 1 NO VETOR BASE
		}
	}
	
	for(c=0; c<MAX; c++){
		if(matriz[a][c] != 0){		//VERIFICA QUAIS NUMEROS JÁ EXISTEM NA LINHA a
			v[matriz[a][c]] = 1;		//TODOS OS NUMEROS QUE ESTÃO NESSA LINHA SÃO SETADOS COMO 1 NO VETOR BASE
		}
	}
	
	regiao(matriz, v, a, b);		//CHAMA A FUNÇÃO REGIAO, QUE TAMBÉM ALTERA O VETOR BASE
	
	return;
}

int tamanho(int array[]){
	int t, cont=0;
	
	for(t=1; t<=MAX; t++){		//O PRIMEIRO ELEMENTO DO VETOR SERÁ SEMPRE 0
		if(array[t] == 0){		//CADA VEZ QUE, A PARTIR DA POSIÇÃO 1, O VETOR SEJA 0, A CONTAGEM DO TAMANHO ATUALIZA
			cont++;
		}
	}
	
	return cont;
}

int resolve(int resposta[MAX][MAX]) {
	int i, j, m, batata, tam, ind;
	int vet[MAX+1] = {0};		//INICIA UM VETOR DE TAMANHO 10, SOMENTE COM ELEMENTOS ZERO
	
	for(i=0; i<MAX; i++){
  		for(j=0; j<MAX; j++){
  			if(resposta[i][j] == 0){		//ENCONTRANDO A PRIMEIRA POSIÇÃO VAZIA DA MATRIZ
  			
  				verifica(resposta, vet, i, j);		//PEGA O VETOR NULO E SETA 1 NAS POSIÇÕES CORRESPONDENTES AOS NÚMEROS JÁ EXISTENTES NAS LINHAS, COLUNAS E REGIÕES ESPECÍFICAS PARA A POSIÇÃO i,j
  				tam = tamanho(vet);		//QUANTIDADE DE ELEMENTOS POSSÍVEIS PARA A POSIÇÃO i,j
  				
  				if(tam == 0){		//SE NÃO HOUVER NENHUM NÚMERO POSSÍVEL PARA AQUELA POSIÇÃO, QUER DIZER QUE A RECURSÃO ANTERIOR DEVE TROCAR DE NÚMERO
  					return 0;
  				}
  				
  				m = 1;
  				ind = 0;
  				
  				while(m < MAX+1){
  					if(vet[m] == 0){		//CASO O VALOR SETADO SEJA 0, ESSE É UM VALOR POSSÍVEL PARA AQUELA POSIÇÃO
  						resposta[i][j] = m;		//TESTANDO ESSE VALOR
  						print_sudoku(resposta);		//PRINTANDO A MATRIZ MODIFICADA

  						if((tam == 1) && (i == MAX-1) && (j == MAX-1)){			//CASO SÓ HAJA UM POSSÍVEL NÚMERO PARA A POSIÇÃO E ESSA POSIÇÃO SEJA A ULTIMA DA MATRIZ, QUER DIZER QUE O RESTO DO TABULEIRO FOI COMPLETADO SEM PROBLEMAS, OU SEJA, ACHAMOS UMA SOLUÇÃO PARA O JOGO
  							return 1;
  						}
  						  					
           			batata = resolve(resposta);		//CHAMA RECURSIVAMENTE A FUNÇÃO RESOLVE, COM A POSIÇÃO ALTERADA, PARA ANALISAR O PRÓXIMO ESPAÇO VAZIO

  						if(batata == 0){		//SE DER ALGUM PROBLEMA, RETORNA 0, E A RECURSÃO ANTERIOR SUBSTITUI OUTRO VALOR POSSÍVEL PARA AQUELA POSIÇÃO
							m++;
							ind++;
  						}
  						
  						if(batata == 1){		//SE CHEGOU AO FIM, RETORNA 1, PARA QUE A RECURSÃO INICIAL SAIBA QUE DEU CERTO
        					return 1;        
  						}
            
            		if(ind == tam){		//SE JÁ TESTOU TODAS AS POSSIBILIDADES DAQUELA POSIÇÃO, E RETORNOU 0 PARA TODAS, ENTÃO RESETA A POSIÇÃO PARA 0 E FAZ A RECURSÃO ANTERIOR TROCAR DE VALOR POSSÍVEL
              			resposta[i][j] = 0;
              			print_sudoku(resposta);
              			return 0;
						}
					}else{
						m++;
					}
  				}
  			}
  		}
  	}
	return 1;
}
