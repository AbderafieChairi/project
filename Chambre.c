#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


// ###################### Chambre Class #############################

typedef struct 
{
	int nbr;	// le nombre de chambre
	int price;	// le couts de chambre
} Chambre;

Chambre init_Chambre(int a,int b){
	Chambre CH;
	CH.nbr=a;
	CH.price=b;
	return CH;
}

Chambre Chambres[100];
#define Empty_Chambre init_Chambre(0,0);

int len_Chambre(){
	for (int i = 0; i < sizeof(Chambres)/sizeof(Chambre); ++i)
	{
		if (Chambres[i].nbr==0){return i;}

	}
}

void get_Chambre(){
	FILE *CP=fopen("Chambre.txt","a+");
	int nbr,price;
	int i=0;
	do{	
		fscanf(CP,"%d\t%d\n",&nbr,&price);
		Chambres[i]=init_Chambre(nbr,price);i++;	
	} while (!feof(CP));
	fclose(CP);
}
void set_Chambre(){
	FILE *CP=fopen("Chambre.txt","w+");
	int l=len_Chambre();
	for (int i = 0; i < l; ++i){
		Chambre C=Chambres[i];
		fprintf(CP,"%d\t%d\n",C.nbr,C.price);
	}
	fclose(CP);
}
Chambre get_Chambre_by_nbr(int nbr){
	get_Chambre();
	int l=len_Chambre();
	for (int i = 0; i < l; ++i){
		if (Chambres[i].nbr==nbr)	
		{
			return Chambres[i];
		}
	}	
	return Empty_Chambre;
}



// ###################### Question 2 : Gestion des Chambres #############################





void add_Chambre(Chambre C){
	get_Chambre();
	int l=len_Chambre();
	if (get_Chambre_by_nbr(C.nbr).nbr==0)
	{
	Chambres[l]=C;
	set_Chambre();
	printf("Ajouter <Chambre %d>\n",C.nbr);
	}
	else{
	printf("Chambre deja existe\n");
	}   
}

void show_Chambre(){
	get_Chambre();
	int l = len_Chambre();
	for (int i = 0; i < l; ++i)
	{
		Chambre C=Chambres[i];
		printf("%d\t%d\n",C.nbr,C.price);
	}
}

void delete_Chambre(int nbr){
	get_Chambre();
	int l = len_Chambre();
	int k=0;
	if (get_Chambre_by_nbr(nbr).nbr==0){
		printf("Le chambre n'existe pas\n");
	}
	else{
	for (int i = 0; i < l; ++i)
	{	
		if(Chambres[i].nbr==nbr && k==0){k=1;}
		if(k==1){
			Chambres[i]=Chambres[i+1];
			Chambres[i+1]=Empty_Chambre;
		}
	}
	printf("supprimer <Chambre %d>\n",nbr);

	set_Chambre();
	}
}

void modifier_Chambre(Chambre C){
	get_Chambre();
	int l = len_Chambre();
	if (get_Chambre_by_nbr(C.nbr).nbr!=0)
	{
	for (int i = 0; i < l; ++i)
	{	
		if(Chambres[i].nbr==C.nbr){
			Chambres[i]=C;
		}

	}
	set_Chambre();	
	printf("modifier <Chambre %d>\n",C.nbr);
	}
	else{
	printf("Chambre n'existe pas\n");
	}
}

void tri_price_Chambre(){
	get_Chambre();
	int a=len_Chambre();
	Chambre tmp=Empty_Chambre;
	for (int i=0 ; i < a-1; i++)
	{
	for (int j=0 ; j < a-i-1; j++)
		{
			if (Chambres[j].price < Chambres[j+1].price)//) 
			{
				tmp=Chambres[j];
				Chambres[j]=Chambres[j+1];
				Chambres[j+1]=tmp;
			}
		}
		}
	set_Chambre();
	printf("tri par	price : \n");
	show_Chambre();
}

int main(int argc, char* argv[])
{
    if (strcmp(argv[1], "-a")==0){
    	add_Chambre(init_Chambre(atoi(argv[2]),atoi(argv[3])));
    }
    if (strcmp(argv[1], "-u")==0){
    	modifier_Chambre(init_Chambre(atoi(argv[2]),atoi(argv[3])));
    }
    if (strcmp(argv[1], "-d")==0){
    	delete_Chambre(atoi(argv[2]));
    }
    if (strcmp(argv[1], "-s")==0){
    	show_Chambre();
    }   
}