#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// ###################### Service Class #############################

typedef struct 
{
	int id;
	char Nom[20];
	int price;
} Service;

Service init_Service(int a,char b[20],int c){
	Service CL;
	CL.id=a;
	strcpy(CL.Nom,b);
	CL.price=c;
	return CL;
}

Service Services[100];
#define Empty_Service init_Service(0,"",0);

int len_Service(){
	for (int i = 0; i < sizeof(Services)/sizeof(Service); ++i)
	{
		if (Services[i].id==0){return i;}

	}
}

void get_Service(){
	FILE *CP=fopen("Service.txt","a+");
	int id,price;
	char Nom[20];
	int i=0;
	do{	
		fscanf(CP,"%d\t%s\t%d\n",&id,Nom,&price);
		Services[i]=init_Service(id,Nom,price);i++;	
	} while (!feof(CP));
	fclose(CP);
}
void set_Service(){
	FILE *CP=fopen("Service.txt","w+");
	int l=len_Service();
	for (int i = 0; i < l; ++i){
		Service C=Services[i];
		fprintf(CP,"%d\t%s\t%d\n",C.id,C.Nom,C.price);
	}
	fclose(CP);
}


int max_id(){
	get_Service();
	int k = 0;
	for (int i = 0; i < sizeof(Services)/sizeof(Service); ++i)
	{
		if (Services[i].id>k){k=Services[i].id;}

	}
	return k+1;
}


Service get_Service_by_id(int Id){
	get_Service();
	int l=len_Service();
	for (int i = 0; i < l; ++i){
		if (Services[i].id==Id)	
		{
			return Services[i];
		}
	}	
	return Empty_Service;
}

void add_Service(Service C){
	get_Service();
	int l=len_Service();
	if (get_Service_by_id(C.id).id==0)
	{
	Services[l]=C;
	set_Service();
	printf("Ajouter <Service %d>\n",C.id);
	}
	else{
	printf("<Service %d> deja existe\n",C.id);
	}   
}

void show_Service(){
	get_Service();
	int l = len_Service();
	for (int i = 0; i < l; ++i)
	{
		Service C=Services[i];
		printf("%s\t%d\n",C.Nom,C.price);
	}
}

void delete_Service(int Id){
	get_Service();
	int l = len_Service();
	int k=0;
	if (get_Service_by_id(Id).id==0)
	{
		printf("<Service %d> n'existe pas\n",Id);
	}else{
	for (int i = 0; i < l; ++i)
	{	
		if(Services[i].id==Id && k==0){k=1;}
		if(k==1){
			Services[i]=Services[i+1];
			Services[i+1]=Empty_Service;
		}
	}
	printf("supprimer <Service %d>\n",Id);

	set_Service();
	}
}

void modifier_Service(Service C){
	get_Service();
	int l = len_Service();
	if (get_Service_by_id(C.id).id!=0)
	{
	for (int i = 0; i < l; ++i)
	{	
		if(Services[i].id==C.id){
			Services[i]=C;
		}

	}
	set_Service();	
	printf("modifier <Service %d>\n",C.id);
	}
	else{
	printf("<Service  %d> n'existe pas\n",C.id);
	}
}


void tri_price_Service(){
	get_Service();
	int a=len_Service();
	Service tmp=Empty_Service;
	for (int i=0 ; i < a-1; i++)
	{
	for (int j=0 ; j < a-i-1; j++)
		{
			if (Services[j].price < Services[j+1].price)//) 
			{
				tmp=Services[j];
				Services[j]=Services[j+1];
				Services[j+1]=tmp;
			}
		}
		}
	set_Service();
	show_Service();
}


// void main(){
// 	add_Service(init_Service(max_id(),"restauration",1000));
// }

int main(int argc, char* argv[])
{
    if (strcmp(argv[1], "-a")==0){
    	add_Service(init_Service(max_id(),argv[2],atoi(argv[3])));
    }
    if (strcmp(argv[1], "-u")==0){
    	modifier_Service(init_Service(atoi(argv[2]),argv[3],atoi(argv[4])));
    }
    if (strcmp(argv[1], "-d")==0){
    	delete_Service(atoi(argv[2]));
    }
    if (strcmp(argv[1], "-s")==0){
    	tri_price_Service();
    }

}