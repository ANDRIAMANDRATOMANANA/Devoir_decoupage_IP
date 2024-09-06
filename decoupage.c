#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX_NAME 100
char **create_tab(int un,int deux)  //creation tableau a deux dimension
{
	int i=0;
	char **name=NULL;
	name=(char**)malloc(un*sizeof(char*));
	for(i=0;i<un;i++)
	{
		name[i]=(char*)malloc(deux*sizeof(char));
	}
	if(name == NULL)
	{
		printf("Erreur d'allocation");
		exit(1);
	}
	return name;
}
int *create_tab_int(int dim)  //creation tableau a deux dimension
{
	int  *tab=NULL;
	tab=(int*)malloc(dim*sizeof(int));
	if(tab == NULL)
	{
		printf("Erreur d'allocation");
		exit(1);
	}
	return tab;
}		
int generate_IP(char **octet,char **token,char *premier_octet,char *deuxieme_octet,char *troisieme_octet,char *quatrieme_octet,char *number_decoupe,char *number_reseaux_bits)
{
	char *get=getenv("QUERY_STRING");//ip=   &number= &decoupe
    char *ken;
    int b=0;
    ken = strtok(get, "&=");
    while (ken != NULL)
    {
       strcpy(octet[b],ken); 
       ken = strtok(NULL,"&=");
       b++;
	}
	char ip[MAX_NAME];
	strcpy(ip,octet[1]); 
	strcpy(number_reseaux_bits,octet[3]); 
	strcpy(number_decoupe,octet[5]); 
	ip[strcspn(ip, "\n")] = '\0';
	char *tok;
	tok = strtok(ip,".");
	int i=0;
	while (tok != NULL)
	{
		strcpy(token[i],tok);
		tok = strtok(NULL,".");
		i++;
	}
	int ok=0;
	char *endptr=NULL;
	int base=10;
	long opt_enum=0;
	for(int c=0;c<i;c++)
	{
		opt_enum=strtol(token[c], &endptr, base); //strtol detecte les caractere non base 10
		if(opt_enum<0 || opt_enum>255 )
		{
          printf("IP non valide");
          exit(1);
		}
		if (endptr == token[c] || *endptr != '\0') //egal quand le premier caractere trouver n'est pas un chiffre
		{
          printf("IP non valide");
                exit(1);
	            
		}
		if(*endptr == '\0' && opt_enum>-1 && opt_enum<256) // Si tout est bon, afficher le nombre converti et sortir de la boucle
        {
			ok++;
	    }
	}
    if(ok==4)
    {
		strcpy(premier_octet,token[0]);
		strcpy(deuxieme_octet,token[1]);
		strcpy(troisieme_octet,token[2]);
		strcpy(quatrieme_octet,token[3]);
	}
	return i;
}
void valid_IP(char **token,char *premier_octet,char *deuxieme_octet,char *troisieme_octet,char *quatrieme_octet,int *premier,int *deuxieme,int *troisieme,int *quatrieme,int count,char *number_decoupe,int *nbr_decoupe,char *number_reseaux_bits,int *nbr_reseaux_bits)
{
	
	if(count!=4)
	{
          printf("IP non valide");
          exit(1);
	}
	if(count==4)
	{
		*premier=atoi(premier_octet);
		
		
		
		*deuxieme=atoi(deuxieme_octet);
		
		
		
		*troisieme=atoi(troisieme_octet);
		
		
		
		*quatrieme=atoi(quatrieme_octet);
	}
	printf("IP:%d.%d.%d.%d",*premier,*deuxieme,*troisieme,*quatrieme);
	*nbr_reseaux_bits=atoi(number_reseaux_bits);
	if(*nbr_reseaux_bits>31 || *nbr_reseaux_bits<1)
	{
		printf("nombre de bits reseaux non valide");
		exit(1);
	}
	printf("<br>Nombre bits pour le reseaux:%d",*nbr_reseaux_bits);
	*nbr_decoupe=atoi(number_decoupe);
	if(*nbr_decoupe>31 || *nbr_decoupe<1)
	{
		printf("nombre de decoupe non valide");
		exit(1);
	}
	printf("<br>Nombre de decoupe:%d",*nbr_decoupe);
}
void transform_binaire(int *bit_msr,int *bits1,int *bits2,int *bits3,int *bits4,int *bits_msr1,int *bits_msr2,int *bits_msr3,int *bits_msr4,int premier,int deuxieme,int troisieme,int quatrieme,int nbr_reseaux_bits)
{
    int tmp1=0;//IP en binaire
	for(int j=0,d=7;j<8 && d>=0;j++,d--)
	{
					int ok=0;
					if(premier==pow(2,d))
					{
						ok++;
						bits1[j]=1;
						premier=0;
						
					}
					if(ok==0 && premier<pow(2,d)+tmp1)
					{
						ok++;
						bits1[j]=0;
						
					}
					if(ok==0 && premier>=pow(2,d)+tmp1)
					{
						ok++;
						bits1[j]=1;
						tmp1=pow(2,d)+tmp1;
					}
	}
    int tmp2=0;
	for(int j=0,d=7;j<8 && d>=0;j++,d--)
	{
			int ok=0;
					if(deuxieme==pow(2,d))
					{
						ok++;
						bits2[j]=1;
						deuxieme=0;
					}
					if(ok==0 && deuxieme<pow(2,d)+tmp2)
					{
						ok++;
						bits2[j]=0;
						
					}
					if(ok==0 && deuxieme>=pow(2,d)+tmp2)
					{
						ok++;
						bits2[j]=1;
						tmp2=pow(2,d)+tmp2;
					}
					
	}
    int tmp3=0;
	for(int j=0,d=7;j<8 && d>=0;j++,d--)
	{
					int ok=0;
					if(troisieme==pow(2,d))
					{
						ok++;
						bits3[j]=1;
						troisieme=0;
						
					}
					if(ok==0 && troisieme<pow(2,d)+tmp3)
					{
						ok++;
						bits3[j]=0;
						
					}
					if(ok==0 && troisieme>=pow(2,d)+tmp3)
					{
						ok++;
						bits3[j]=1;
						tmp3=pow(2,d)+tmp3;
					}
					
	}
    int tmp4=0;
	for(int j=0,d=7;j<8 && d>=0;j++,d--)
	{
					int ok=0;
					if(quatrieme==pow(2,d))
					{
						ok++;
						bits4[j]=1;
						troisieme=0;
						
					}
					if(ok==0 && quatrieme<pow(2,d)+tmp4)
					{
						ok++;
						bits4[j]=0;
						
					}
					if(ok==0 && quatrieme>=pow(2,d)+tmp4)
					{
						ok++;
						bits4[j]=1;
						tmp4=pow(2,d)+tmp4;
					}
	}
	for(int i=0;i<nbr_reseaux_bits;i++)//reseaux
	{
		bit_msr[i]=1;
		
	 }
	for(int i=nbr_reseaux_bits;i<32;i++)//Hote
	{
		bit_msr[i]=0;
	}
	
	for(int i=0;i<8;i++)// pour mettre chaque nouveau bits dans chaque tableau de bits i
	{
		bits_msr1[i]=bit_msr[i];
		
	}
	
	for(int i=8;i<16;i++)
	{
		bits_msr2[i]=bit_msr[i];
		
	}
	
	for(int i=16;i<24;i++)
	{
		bits_msr3[i]=bit_msr[i];
		
	}
	
	for(int i=24;i<32;i++)
	{
		bits_msr4[i]=bit_msr[i];
		
	}
	
}
void binaire(int *adress_r ,int *somme_bc)
{
	int tmp1=0;//IP en binaire
	for(int j=0,d=7;j<8 && d>=0;j++,d--)
	{
					int ok=0;
					if(somme_bc[1]==pow(2,d))
					{
						ok++;
						adress_r[j]=1;
						somme_bc[1]=0;
						
					}
					if(ok==0 && somme_bc[1]<pow(2,d)+tmp1)
					{
						ok++;
						adress_r[j]=0;
						
					}
					if(ok==0 && somme_bc[1]>=pow(2,d)+tmp1)
					{
						ok++;
						adress_r[j]=1;
						tmp1=pow(2,d)+tmp1;
					}
	}
    int tmp2=0;
	for(int j=8,d=7;j<16 && d>=0;j++,d--)
	{
			int ok=0;
					if(somme_bc[2]==pow(2,d))
					{
						ok++;
						adress_r[j]=1;
						somme_bc[2]=0;
					}
					if(ok==0 && somme_bc[2]<pow(2,d)+tmp2)
					{
						ok++;
						adress_r[j]=0;
						
					}
					if(ok==0 && somme_bc[2]>=pow(2,d)+tmp2)
					{
						ok++;
						adress_r[j]=1;
						tmp2=pow(2,d)+tmp2;
					}
					
	}
    int tmp3=0;
	for(int j=16,d=7;j<24 && d>=0;j++,d--)
	{
					int ok=0;
					if(somme_bc[3]==pow(2,d))
					{
						ok++;
						adress_r[j]=1;
						somme_bc[3]=0;
						
					}
					if(ok==0 && somme_bc[3]<pow(2,d)+tmp3)
					{
						ok++;
						adress_r[j]=0;
						
					}
					if(ok==0 && somme_bc[3]>=pow(2,d)+tmp3)
					{
						ok++;
						adress_r[j]=1;
						tmp3=pow(2,d)+tmp3;
					}
	}
    int tmp4=0;
	for(int j=24,d=7;j<32 && d>=0;j++,d--)
	{
					int ok=0;
					if(somme_bc[4]==pow(2,d))
					{
						ok++;
						adress_r[j]=1;
						somme_bc[4]=0;
						
					}
					if(ok==0 && somme_bc[4]<pow(2,d)+tmp4)
					{
						ok++;
						adress_r[j]=0;
						
					}
					if(ok==0 && somme_bc[4]>=pow(2,d)+tmp4)
					{
						ok++;
						adress_r[j]=1;
						tmp4=pow(2,d)+tmp4;
					}
	}
}
void transform_decimal(int *bits_msr1,int *bits_msr2,int *bits_msr3,int *bits_msr4)
{
	int dim=50;
	int *octet=NULL;
	octet=(int*)malloc(dim*sizeof(int));//pour stocker chaque bits en decimal
	int somme1=0;
	
	for(int i=0,j=7;i<8 && j>=0;i++,j--)
	{
		octet[i]=bits_msr1[i]*pow(2,j);
		somme1=somme1+octet[i];
	}
	
	int somme2=0;
	for(int i=8,j=7;i<16 && j>=0;i++,j--)
	{
		octet[i]=bits_msr2[i]*pow(2,j);
		somme2=somme2+octet[i];
	}
	
	int somme3=0;
	for(int i=16,j=7;i<24 && j>=0;i++,j--)
	{
		octet[i]=bits_msr3[i]*pow(2,j);
		somme3=somme3+octet[i];
	}
	
	int somme4=0;
	for(int i=24,j=7;i<32 && j>=0;i++,j--)
	{
		octet[i]=bits_msr4[i]*pow(2,j);
		somme4=somme4+octet[i];
	}
	
	free(octet);
}
void adress_reseaux(int *adress_r,int *bits1,int *bits2,int *bits3,int *bits4,int *bits_msr1,int *bits_msr2,int *bits_msr3,int *bits_msr4,int nbr_reseau_bits)
{
	int dim=50;
	
	for(int i=0;i<8;i++)
	{
		adress_r[i]=bits1[i]*bits_msr1[i];
		
	}
	for(int i=0,j=8;i<8 && j<16;i++,j++)
	{
		adress_r[j]=bits2[i]*bits_msr2[j];
		
	}
	for(int i=0,j=16;i<8 && j<24;i++,j++)
	{
		adress_r[j]=bits3[i]*bits_msr3[j];
		
	}
	for(int i=0,j=24;i<8 && j<32;i++,j++)
	{
		adress_r[j]=bits4[i]*bits_msr4[j];
		
	}
	int *octet_r=NULL;
	octet_r=(int*)malloc(dim*sizeof(int));//pour stocker chaque produit des bits par les 2puissance nombre
	int somme1=0;
	printf("<br>Adresse Reseaux:");
	for(int i=0,j=7;i<8 && j>=0;i++,j--)
	{
		octet_r[i]=adress_r[i]*pow(2,j);
		somme1=somme1+octet_r[i];
	}
	printf("%d.",somme1);
	int somme2=0;
	for(int i=8,j=7;i<16 && j>=0;i++,j--)
	{
		octet_r[i]=adress_r[i]*pow(2,j);
		somme2=somme2+octet_r[i];
	}
	printf("%d.",somme2);
	int somme3=0;
	for(int i=16,j=7;i<24 && j>=0;i++,j--)
	{
		octet_r[i]=adress_r[i]*pow(2,j);
		somme3=somme3+octet_r[i];
	}
	printf("%d.",somme3);
	int somme4=0;
	for(int i=24,j=7;i<32 && j>=0;i++,j--)
	{
		octet_r[i]=adress_r[i]*pow(2,j);
		somme4=somme4+octet_r[i];
	}
	printf("%d",somme4);
	int *octet_bc=NULL;
	octet_bc=(int*)malloc(dim*sizeof(int));//pour stocker chaque bits de diffusion en decimal
	int *bits_bc=NULL;
	bits_bc=(int*)malloc(dim*sizeof(int));
	printf("<br>adresse de broadcast:");
	int somme1_bc=0;
	for(int i=0;i<nbr_reseau_bits;i++)
	{
		bits_bc[i]=adress_r[i];
	}
	for(int i=nbr_reseau_bits;i<32;i++)
	{
		bits_bc[i]=1;
	}
	for(int i=0,j=7;i<8 && j>=0;i++,j--)
	{
		octet_bc[i]=bits_bc[i]*pow(2,j);
		somme1_bc=somme1_bc+octet_bc[i];
	}
	printf("%d.",somme1_bc);
	int somme2_bc=0;
	for(int i=8,j=7;i<16 && j>=0;i++,j--)
	{
		octet_bc[i]=bits_bc[i]*pow(2,j);
		somme2_bc=somme2_bc+octet_bc[i];
	}
	printf("%d.",somme2_bc);
	int somme3_bc=0;
	for(int i=16,j=7;i<24 && j>=0;i++,j--)
	{
		octet_bc[i]=bits_bc[i]*pow(2,j);
		somme3_bc=somme3_bc+octet_bc[i];
	}
	printf("%d.",somme3_bc);
	int somme4_bc=0;
	for(int i=24,j=7;i<32 && j>=0;i++,j--)
	{
		octet_bc[i]=bits_bc[i]*pow(2,j);
		somme4_bc=somme4_bc+octet_bc[i];
	}
	printf("%d.",somme4_bc);
	free(octet_bc);
	free(octet_r);
	free(bits_bc);
}
void nouveau_msr(int *bit_msr,int nbr_reseaux_bits,int nbr_decoupe)
{
	
	for(int i=0;i<nbr_reseaux_bits+nbr_decoupe;i++)// pour mettre chaque nouveau bits dans chaque tableau de bits i
	{
		bit_msr[i]=1;
	}
	for(int i=nbr_reseaux_bits+nbr_decoupe;i<32;i++)
	{
		bit_msr[i]=0;
	}
}
void decoupe(int *somme_bc,int *bit_msr,int *adress_r,int nbr_decoupe,int nbr_reseaux_bits)
{
	int dim=50;
	int *octet_bc=NULL;
	octet_bc=(int*)malloc(dim*sizeof(int));
	int *octet_r=NULL;
	octet_r=(int*)malloc(dim*sizeof(int));//pour stocker chaque produit des bits par les 2puissance nombre
	int *bits_r=NULL;
	bits_r=(int*)malloc(dim*sizeof(int));
	int *bits_bc=NULL;
	bits_bc=(int*)malloc(dim*sizeof(int));
	printf("<br>-------------------------------------------------");
	for(int a=0;a<pow(2,nbr_decoupe);a++)
	{
		if(a==0)
		{
			printf("<br>%dere sous reseaux:",a+1);
		}
		else
		{
			printf("<br>%deme sous reseaux:",a+1);
		}
		int somme1=0;
		printf("<br>Adresse Reseaux:");
		for(int i=0,j=7;i<8 && j>=0;i++,j--)
		{
			octet_r[i]=adress_r[i]*pow(2,j);
			somme1=somme1+octet_r[i];
		}
		printf("%d.",somme1);
		int somme2=0;
		for(int i=8,j=7;i<16 && j>=0;i++,j--)
		{
			octet_r[i]=adress_r[i]*pow(2,j);
			somme2=somme2+octet_r[i];
		}
		printf("%d.",somme2);
		int somme3=0;
		for(int i=16,j=7;i<24 && j>=0;i++,j--)
		{
			octet_r[i]=adress_r[i]*pow(2,j);
			somme3=somme3+octet_r[i];
		}
		printf("%d.",somme3);
		int somme4=0;
		for(int i=24,j=7;i<32 && j>=0;i++,j--)
		{
			octet_r[i]=adress_r[i]*pow(2,j);
			somme4=somme4+octet_r[i];
		}
		printf("%d",somme4);
		int nbr_machine=0;
		nbr_machine=pow(2,32-(nbr_decoupe+nbr_reseaux_bits));
		printf("<br>Nombre dIP possible d'un machine:%d",nbr_machine);
		printf("<br>adresse de broadcast:");
		for(int n=0;n<nbr_reseaux_bits+nbr_decoupe;n++)
		{
			bits_bc[n]=adress_r[n];
		}
		for(int n=nbr_reseaux_bits+nbr_decoupe;n<32;n++)
		{
			bits_bc[n]=1;
		}
		somme_bc[1]=0;
		for(int i=0,j=7;i<8 && j>=0;i++,j--)
		{
			octet_bc[i]=bits_bc[i]*pow(2,j);
			somme_bc[1]=somme_bc[1]+octet_bc[i];
		}
		printf("%d.",somme_bc[1]);
		somme_bc[2]=0;
		for(int i=8,j=7;i<16 && j>=0;i++,j--)
		{
			octet_bc[i]=bits_bc[i]*pow(2,j);
			somme_bc[2]=somme_bc[2]+octet_bc[i];
		}
		printf("%d.",somme_bc[2]);
		somme_bc[3]=0;
		for(int i=16,j=7;i<24 && j>=0;i++,j--)
		{
			octet_bc[i]=bits_bc[i]*pow(2,j);
			somme_bc[3]=somme_bc[3]+octet_bc[i];
		}
		printf("%d.",somme_bc[3]);
		somme_bc[4]=0;
		for(int i=24,j=7;i<32 && j>=0;i++,j--)
		{
			octet_bc[i]=bits_bc[i]*pow(2,j);
			somme_bc[4]=somme_bc[4]+octet_bc[i];
		}
		printf("%d",somme_bc[4]);
		int verf=0;
		for(int y=4;y>0;y--)
		{
			if(verf==0 && somme_bc[4]==255 && somme_bc[y]==255 && somme_bc[y-1]!=255)
			{
				verf++;
				somme_bc[y]=0;
				somme_bc[y-1]=somme_bc[y-1]+1;
			}
			if(verf==0 && somme_bc[4]!=255)
			{
				verf++;
				somme_bc[4]=somme_bc[4]+1;
			}
		}
		printf("<br>-------------------------------------------------");
		binaire(adress_r,somme_bc);
	}
	free(octet_bc);
	free(bits_bc);
	free(octet_r);
	free(bits_r);
	
}





