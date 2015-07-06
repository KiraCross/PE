#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MV 50
#define MP 500

	typedef struct { // Estrutura que fará um vetor, cada numero do vetor da struct será um departamento
		float pvpl[250]; // Onde será guardado as informaçoes na ordem <produto, vendedor, total de vendas, preço total naquele vendedor e produto, lucro>. Essa ordem será repetida de 5 em 5 no vetor.
	} depart;

int abrirArquivo(FILE *arq, char caminhoarquivo[MV]) //identificar se o arquivo existe ou não
{	
	arq = fopen(caminhoarquivo,"r");
	
	if(arq==NULL){
	return 0;}
	
	else	return 1;	
}
	   

int processaEntrada (FILE *arq, char caminhoarquivo[MV],depart departamento[MP],int v[MP], int *quantdepartamentos)// Ler e organizar os dados da forma que iremos trabalhar. Cada struct será um departamento, dentro será uma matriz organizada de 5 em 5, <produto, vendedor, total de venda, valor total, lucro>
{	
	int valor;
	int quantidade[100];
	int qtotal=0;
	double lucro;
	int fimq = 0,fimv=0,fimp=0,fimd=0;
	int i=0,j=0,h=0,k=0, t=0, x=0;
	int mj=0,mh=0;
	int o=0; //criada pra guardar quantos espaços H serão usados em cada struct
	*quantdepartamentos=0; //Irá contar a quantidade de departamentos usados
	
	arq = fopen(caminhoarquivo,"r");
	
	while(fimd != -1){ //Encerra Departamentos
	fscanf(arq,"%d",&k); // k é o numero do departamento
	fimd = k;
		if(k != -1){
		
			while(fimp != -1){ //Encerra os Produtos do Departamento
			fscanf(arq,"%f",&departamento[*quantdepartamentos].pvpl[h]); // Pergunta produto
			fimp = departamento[*quantdepartamentos].pvpl[h];
			if(mh>MP){ //Verifica se o numero de produtos do arquivo atinge o maior que o permitido.
								fimq=-1; fimp=-1; fimv=-1; fimd=-1; return 0;}
			else{
				mh++;
				if(fimp != -1){
				fscanf(arq,"%d",&valor);
				fscanf(arq,"%lf",&lucro);
					lucro=((lucro/100)*valor);
					if(departamento[*quantdepartamentos].pvpl[h] != -1){
					h++;
					
						while(fimv != -1){ //Encerra os Vendedores do Departamento
						fscanf(arq,"%f",&departamento[*quantdepartamentos].pvpl[h]); //Pergunta vendedor
						fimv = departamento[*quantdepartamentos].pvpl[h];
						
							if(departamento[*quantdepartamentos].pvpl[h] != -1){
								if (t==1) {
									x=departamento[*quantdepartamentos].pvpl[h];
									departamento[*quantdepartamentos].pvpl[h]=departamento[*quantdepartamentos].pvpl[h-5];h++;
									departamento[*quantdepartamentos].pvpl[h]=x;}
								if(mj>MV){ //Verifica se o numero de vendedores do arquivo atinge o maior que o permitido.
								fimq=-1; fimp=-1; fimv=-1; fimd=-1; return 0;}
								else{
								mj++; h++;
												
									while(fimq != -1){ //Encerra a leitura de Quantidades e Passa pro proximo Vendedor Caso Encontre o Valor -1
										fscanf(arq,"%d",&quantidade[i]);
										fimq = quantidade[i];
										if (quantidade[i] != -1){
									    qtotal = qtotal + quantidade[i];
										i++;
										t=1;
										}

									}
								departamento[*quantdepartamentos].pvpl[h]=qtotal;
								h++;
								departamento[*quantdepartamentos].pvpl[h]=qtotal*valor;
								h=h+1;
								departamento[*quantdepartamentos].pvpl[h]=qtotal*lucro;
								h++;
								fimq=0; qtotal=0; i=0;
								}
							}  
							if(departamento[*quantdepartamentos].pvpl[h] == -1) t=0;				
						}
						fimv=0; j=0;
					}
				}
			}
			}
			fimp=0;v[o]=h-2; o++; h=0; 
		} *quantdepartamentos=*quantdepartamentos+1; 
	} *quantdepartamentos=*quantdepartamentos-2; //Compensação para nao ter erro, pois repete 2 vezes a mais.
	fimd=0; k=0;
	fclose(arq);
	return 1;
}

void vendasValor(FILE *arq, char caminhosaida[MV], depart departamento[MP],int v[MP], int *quantdepartamentos){// Função responsavel por imprimir a informação requisitada n. 1
double vendedorproduto[100];
int n,k,g=0;
int i=0;
int w=0;
for (n=0;n<=*quantdepartamentos;n++){ //ORGANIZAR UM VETOR SOMENTE COM PREÇO E VENDEDOR!
	for (k=3;k<=v[n]+1;k=k+5){
		vendedorproduto[i]=departamento[n].pvpl[k]; //passando valor do preço
		i++;
		vendedorproduto[i]=departamento[n].pvpl[k-2]; // passando valor do vendedor
		i++;
		w++; // Conta a quantidade de vendedores
	}
}
	for (i=1;i<2*w;i=i+2){//JUNTAR VENDEDORES REPETIDOS
		for (k=1;k<w;k++){
			if (vendedorproduto[i]==vendedorproduto[i+(2*k)]){
				vendedorproduto[i-1]=vendedorproduto[i-1]+vendedorproduto[i+(2*k)-1];
				vendedorproduto[i+(2*k)]=0;
				vendedorproduto[i+(2*k)-1]=0;
			}
		}
	}
for (g=0;g<=*quantdepartamentos;g++){
	for (i=0;i<50;i++){ //TECNICA DA BOLHA PRA ORDERNAR
		for (n=0;n<=(float)(v[g]*2)/5;n=n+2){
			if (vendedorproduto[n]<vendedorproduto[n+2]){
				k=vendedorproduto[n];
				vendedorproduto[n]=vendedorproduto[n+2];
				vendedorproduto[n+2]=k;
				k=vendedorproduto[n+1];
				vendedorproduto[n+1]=vendedorproduto[n+3];
				vendedorproduto[n+3]=k;
			}
		}
	}
}
for (n=0;(n<w)&&(vendedorproduto[n]!=0);n=n+2){
	fprintf (arq,"(%.0lf, %.2lf) ", vendedorproduto[n+1], vendedorproduto[n]);
}

	fprintf (arq,"\n");
}
void vendasQuantidade(FILE *arq, char caminhosaida[MV], depart departamento[MP],int v[MP], int *quantdepartamentos){// Função responsavel por imprimir a informação requisitada n. 2
double vendedorproduto[100];
int n,k, c;
int i=0;
int w=0;
for (n=0;n<=*quantdepartamentos;n++){ //ORGANIZAR UM VETOR SOMENTE COM TOTAL DE VENDAS E VENDEDOR!
	for (k=2;k<=v[n]+1;k=k+5){
		vendedorproduto[i]=departamento[n].pvpl[k]; //passaando valor do total
		i++;
		vendedorproduto[i]=departamento[n].pvpl[k-1]; // passando valor do vendedor
		i++;
		w++; // Conta a quantidade de vendedores
	}
}
	for (i=1;i<2*w;i=i+2){//JUNTAR VENDEDORES REPETIDOS
		for (k=1;k<w;k++){
			if (vendedorproduto[i]==vendedorproduto[i+(2*k)]){
				vendedorproduto[i-1]=vendedorproduto[i-1]+vendedorproduto[i+(2*k)-1];
				vendedorproduto[i+(2*k)]=0;
				vendedorproduto[i+(2*k)-1]=0;
			}
		}
	}
for (c=0;c<=*quantdepartamentos;c++){
	for (i=0;i<50;i++){ //TECNICA DA BOLHA PRA ORDERNAR
		for (n=0;n<=(float)(v[c]*2)/5;n=n+2){
			if (vendedorproduto[n]<vendedorproduto[n+2]){
				k=vendedorproduto[n];
				vendedorproduto[n]=vendedorproduto[n+2];
				vendedorproduto[n+2]=k;
				k=vendedorproduto[n+1];
				vendedorproduto[n+1]=vendedorproduto[n+3];
				vendedorproduto[n+3]=k;
			}
		}
	}
}
for (n=0;(n<w)&&(vendedorproduto[n]!=0);n=n+2){
	fprintf (arq,"(%.0lf, %.0lf) ", vendedorproduto[n+1], vendedorproduto[n]);
}
	fprintf (arq,"\n");

}
void produtoValor(FILE *arq, char caminhosaida[MV], depart departamento[MP],int v[MP], int *quantdepartamentos){// Função responsavel por imprimir a informação requisitada n. 3
double produtovalor[100];
int n,k,c;
int i=0;
int w=0;
for (n=0;n<=*quantdepartamentos;n++){ //ORGANIZAR UM VETOR SOMENTE COM PRODUTO E PREÇO
	for (k=3;k<=v[n]+1;k=k+5){
		produtovalor[i]=departamento[n].pvpl[k]; //passaando valor do preço
		i++;
		produtovalor[i]=departamento[n].pvpl[k-3]; // passando valor do produto
		i++;
		w++; // Conta a quantidade
	}
}
	for (i=1;i<2*w;i=i+2){//JUNTAR PRODUTOS REPETIDOS
		for (k=1;k<w;k++){
			if (produtovalor[i]==produtovalor[i+(2*k)]){
				produtovalor[i-1]=produtovalor[i-1]+produtovalor[i+(2*k)-1];
				produtovalor[i+(2*k)]=0;
				produtovalor[i+(2*k)-1]=0;
			}
		}
	}
for (c=0;c<=*quantdepartamentos;c++){
	for (i=0;i<50;i++){ //TECNICA DA BOLHA PRA ORDERNAR
		for (n=0;n<=(float)(v[c]*2)/5;n=n+2){
			if (produtovalor[n]<produtovalor[n+2]){
				k=produtovalor[n];
				produtovalor[n]=produtovalor[n+2];
				produtovalor[n+2]=k;
				k=produtovalor[n+1];
				produtovalor[n+1]=produtovalor[n+3];
				produtovalor[n+3]=k;
			}
		}
	}
}

for (n=0;(n<w)&&(produtovalor[n]!=0);n=n+2){
	fprintf (arq,"(%.0lf, %.2lf) ", produtovalor[n+1], produtovalor[n]);
}	
	fprintf (arq,"\n");

}
void produtoLucro(FILE *arq, char caminhosaida[MV], depart departamento[MP],int v[MP], int *quantdepartamentos){// Função responsavel por imprimir a informação requisitada n. 4
double produtovalor[100];
int n,k,c;
int i=0;
int w=0;
for (n=0;n<=*quantdepartamentos;n++){ //ORGANIZAR UM VETOR SOMENTE COM LUCRO E PRODUTOS
	for (k=4;k<=v[n]+1;k=k+5){
		produtovalor[i]=departamento[n].pvpl[k]; //Passaando valor do lucro
		i++;
		produtovalor[i]=departamento[n].pvpl[k-4]; // Passando valor do produto
		i++;
		w++; // Conta a quantidade
	}
}
	for (i=1;i<2*w;i=i+2){//JUNTAR PRODUTOS REPETIDOS
		for (k=1;k<w;k++){
			if (produtovalor[i]==produtovalor[i+(2*k)]){
				produtovalor[i-1]=produtovalor[i-1]+produtovalor[i+(2*k)-1];
				produtovalor[i+(2*k)]=0;
				produtovalor[i+(2*k)-1]=0;
			}
		}
	}
for (c=0;c<=*quantdepartamentos;c++){
	for (i=0;i<50;i++){ //TECNICA DA BOLHA PRA ORDERNAR
		for (n=0;n<=(float)(v[c]*2)/5;n=n+2){
			if (produtovalor[n]<produtovalor[n+2]){
				k=produtovalor[n];
				produtovalor[n]=produtovalor[n+2];
				produtovalor[n+2]=k;
				k=produtovalor[n+1];
				produtovalor[n+1]=produtovalor[n+3];
				produtovalor[n+3]=k;
			}
		}
	}
}
for (n=0;(n<w)&&(produtovalor[n]!=0);n=n+2){
	fprintf (arq,"(%.0lf, %.2lf) ", produtovalor[n+1], produtovalor[n]);
}
	fprintf (arq,"\n");
}

int main()
{
	FILE *arqEntrada=NULL; 
	FILE *arqSaida=NULL;
	char caminhoarquivo[50]="entrada.txt";
	char caminhosaida[60]="saida.txt";
	depart vetor[MP];
	int dado1[MP]; // indica ate que numero cada struct foi usado internamente
	int quantdepusados; //Vai marcar quantos structs(departamentos) foram usados
	arqSaida = fopen(caminhosaida, "w");
	
	if (abrirArquivo(arqEntrada,caminhoarquivo) && processaEntrada(arqEntrada,caminhoarquivo,vetor, dado1, &quantdepusados) == 1){
				vendasValor(arqSaida, caminhosaida, vetor,dado1,&quantdepusados);	
				vendasQuantidade(arqSaida, caminhosaida, vetor,dado1,&quantdepusados);	
				produtoValor(arqSaida, caminhosaida, vetor,dado1,&quantdepusados);	
				produtoLucro(arqSaida, caminhosaida, vetor,dado1,&quantdepusados);	

	}
	fclose(arqSaida);
	return 0;
}
