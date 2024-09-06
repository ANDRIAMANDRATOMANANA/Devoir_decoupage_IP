#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "decoupage.h"
#define MAX_NAME 100
int main()
{
printf("Content-type: text/html\n\n");
	printf("<!DOCTYPE html><html><head><title>IP</title></head><body>");
	int count=0;
	int pdim=100;
	int ddim=50;
	char premier_octet[MAX_NAME];
    char deuxieme_octet[MAX_NAME];
    char troisieme_octet[MAX_NAME];
    char quatrieme_octet[MAX_NAME];
    char number_decoupe[MAX_NAME];
    char number_reseaux_bits[MAX_NAME];
    int premier=0;
    int deuxieme=0;
    int troisieme=0;
    int quatrieme=0;
    int nbr_decoupe=0;
    int nbr_reseaux_bits=0;
	char **token=NULL;
	char **octet=NULL;
	int *bits1=NULL;//tableau pour stocker chaque bits d'octet
	int *bits2=NULL;
	int *bits3=NULL;
	int *bits4=NULL;
	int *bits_msr1=NULL;//tableau pour stocker chaque bits de netmask
	int *bits_msr2=NULL;
	int *bits_msr3=NULL;
	int *bits_msr4=NULL;
	int *bit_msr=NULL;
	int *adress_r=NULL;
	int *somme_bc=NULL;
	bits1=create_tab_int(50);
	bits2=create_tab_int(50);
	bits3=create_tab_int(50);
	bits4=create_tab_int(50);
	bits_msr1=create_tab_int(50);
	bits_msr2=create_tab_int(50);
	bits_msr3=create_tab_int(50);
	bits_msr4=create_tab_int(50);
	bit_msr=create_tab_int(50);
	somme_bc=create_tab_int(50);
	adress_r=create_tab_int(50);
	token=create_tab(pdim,ddim);
	octet=create_tab(pdim,ddim);
	count=generate_IP(octet,token,premier_octet,deuxieme_octet,troisieme_octet,quatrieme_octet,number_decoupe,number_reseaux_bits);
	valid_IP(token,premier_octet,deuxieme_octet,troisieme_octet,quatrieme_octet,&premier,&deuxieme,&troisieme,&quatrieme,count,number_decoupe,&nbr_decoupe,number_reseaux_bits,&nbr_reseaux_bits);
	transform_binaire(bit_msr,bits1,bits2,bits3,bits4,bits_msr1,bits_msr2,bits_msr3,bits_msr4,premier,deuxieme,troisieme,quatrieme,nbr_reseaux_bits);
	transform_decimal(bits_msr1,bits_msr2,bits_msr3,bits_msr4);
	adress_reseaux(adress_r,bits1,bits2,bits3,bits4,bits_msr1,bits_msr2,bits_msr3,bits_msr4,nbr_reseaux_bits);
	nouveau_msr(bit_msr,nbr_reseaux_bits,nbr_decoupe);
	decoupe(somme_bc,bit_msr,adress_r,nbr_decoupe,nbr_reseaux_bits);
	printf("</body></html>");
	for(int i=0;i<pdim;i++)
	{
		free(token[i]);
	}
	free(token);
	for(int i=0;i<pdim;i++)
	{
		free(octet[i]);
	}
	free(octet);
	free(bits1);
	free(bits2);
	free(bits3);
	free(bits4);
	free(bits_msr1);
	free(bits_msr2);
	free(bits_msr3);
	free(bits_msr4);
	free(somme_bc);
	return 0;
}
