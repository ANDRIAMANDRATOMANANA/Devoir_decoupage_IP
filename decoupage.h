#include "decoupage.c" 
char **create_tab(int un,int deux);
int *create_tab_int(int dim); //creation tableau a deux dimension
int generate_IP(char **octet,char **token,char *premier_octet,char *deuxieme_octet,char *troisieme_octet,char *quatrieme_octet,char *number_decoupe,char *number_reseaux_bits);
void valid_IP(char **token,char *premier_octet,char *deuxieme_octet,char *troisieme_octet,char *quatrieme_octet,int *premier,int *deuxieme,int *troisieme,int *quatrieme,int count,char *number_decoupe,int *nbr_decoupe,char *number_reseaux_bits,int *nbr_reseaux_bits);
void transform_binaire(int *bit_msr,int *bits1,int *bits2,int *bits3,int *bits4,int *bits_msr1,int *bits_msr2,int *bits_msr3,int *bits_msr4,int premier,int deuxieme,int troisieme,int quatrieme,int nbr_reseau_bits);
void binaire(int *adress_r ,int *somme_bc);
void transform_decimal(int *bits_msr1,int *bits_msr2,int *bits_msr3,int *bits_msr4);
void adress_reseaux(int *adress_r,int *bits1,int *bits2,int *bits3,int *bits4,int *bits_msr1,int *bits_msr2,int *bits_msr3,int *bits_msr4,int nbr_reseau_bits);
void nouveau_msr(int *bit_msr,int nbr_reseaux_bits,int nbr_decoupe);
void decoupe(int *somme_bc,int *bit_msr,int *adress_r,int nbr_decoupe,int nbr_reseaux_bits);
