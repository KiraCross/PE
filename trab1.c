#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TF 50

int abrirArquivo(FILE *arq, char caminhoarquivo[TF]) //identificar se o arquivo existe ou não
{	
	arq = fopen(caminhoarquivo,"r");
	
	if(arq==NULL){
	printf("Arquivo Não Encontrado\n");
	return 0;}
	
	else	return 1;	
}
	   

void processaEntrada (FILE *arq, char caminhoarquivo[TF])
{	
	int departamento [5];
	int produto[5];
	int valor[6];
	int quantidade[50];
	int qtotal=0;
	int fimq = 0,fimv= 0;
	float lucro[5];
	int vendedor[50];
	int i=0,j=0;
	
	
	arq = fopen(caminhoarquivo,"r");
	fscanf(arq,"%d",departamento);
	printf("Departamento: %d\n\n",*departamento);
	
	fscanf(arq,"%d %d %f",produto,valor,lucro);
	printf("Código do Produto: %d\t Valor do produto: %d\t Lucro: %.1f%% \n\n",*produto,*valor,*lucro*100);
	
		while(fimv != -1){ //Encerra os Vendedores do Departamento
		
		fscanf(arq,"%d",&vendedor[j]);
		fimv = vendedor[j];
		
		if(vendedor[j] != -1){
			printf("Código do Vendedor: %d\n\n",vendedor[j]);
			j++;
		
		
				while(fimq != -1){ //Encerra a leitura de Quantidades e Passa pro proximo Vendedor Caso Encontre o Valor -1
					fscanf(arq,"%d",&quantidade[i]);
					fimq = quantidade[i];
					
					if (quantidade[i] != -1){
				    printf("Quantidade Vendida %d: %d\n",i+1,quantidade[i]);
				    qtotal = qtotal + quantidade[i];
					i++;}
					
					else{ printf("Total: %d \n\n",qtotal); }
				}
			fimq=0; qtotal =0; i=0;
			}
			
			
		}
		fimv = 0; j=0;
	fclose(arq);	


	

}

int menu (){ //Responsável pela impressão do menu
	int op;
	fflush(stdin);
	printf("|=========================================================================|\n");
	printf("|===================================MENU==================================|\n");
	printf("|=========================================================================|\n");
	printf("|==   1.Ranking de Vendedores Decrescente Pelo Valor Total de Vendas    ==|\n");
	printf("|==   2.Ranking de Vendedores Decrescente Pela Quantidade de Vendas     ==|\n");
	printf("|==   3.Lista de Produtos Decrecente Pelo Valor Total de Vendas         ==|\n");
	printf("|==       4.Lista de Produtos Decrescente Pelo Lucro Obtido             ==|\n");
	printf("|==                              0. Sair                                ==|\n");
	printf("|=========================================================================|\n");
	printf("\nDigite uma opção do menu: ");	scanf("%d",&op);

	return op;
}


int main()
{
	FILE *arqEntrada=NULL;
	char caminhoarquivo[100]="C:\\Users\\JúlioCésar\\entrada.txt";
	int k=1;
	
	if (abrirArquivo(arqEntrada,caminhoarquivo) == 1){ //Verifica se o arquivo existe ou não	
	processaEntrada(arqEntrada,caminhoarquivo);
	
		do{//Exibir menu
			switch(menu()){
	
			case 1: //Ranking Total de Vendas
				break;
			case 2: //Ranking Quantidade de Vendas
				break;
			case 3: //Lista Produtos por Valor
				break;
			case 4: //Lista Produtos por Lucro
				break;
			case 0: //Sair
				printf("PROGRAMA FINALIZADO \n\n"); k=0;		break;
			default://Numero Inválido
				printf("Numero Inválido, repita a operação\n\n");	break;
		}
	}while(k!=0);
	}
	
	else printf("Programa Finalizado\n");

	return 0;
}
