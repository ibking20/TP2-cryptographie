#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//Compiler version gcc  6.3.0

// variable globales
long n = 0, p = 0, q = 0, phi = 0;
int prime[] = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101,103,107,109,113,127,131,137,139,143,149};

/*
// fonction de jacobi
int J(int a, int b){
  if(a==1)
    return 1;
  else if(a==b){
    return (J(a/2,b)*((-1)^(((b*b)-1)/8)));
  }
  else{
    return (J(b%a,a)*((-1)^(((a-1)*(b-1))/4)));
  }
}
*/

// fonction de calcul du pgcd de 2 nombres
long pgcd(long a, long b)
{
  long r, i = 1;
  while((b*i) <= a)
  {
     i++;
  }
  i--;
  r = a - (b*i);
  if(r == 0)
  {
    return b;
  }
  else
  {
    return pgcd(b,r);
  }
}

// fonction de generation de p,q et de calcul de n et de Phi(n)
void GenPhi(long max){
  srand(time(NULL));
  do{
    p = prime[rand()%31 + 5];
    q = prime[rand()%31 + 5];
  }while(pgcd(p,q) != 1 || p == q || p > max || q > max);
  n = p*q;
  phi = (p-1)*(q-1);
}

// fonction de generation de e
long GenE(long phi){
  long e;
  srand(time(NULL));
  do{
    if(p<q)
      e = rand()%(phi - q) + q;
    else
      e = rand()%(phi - p) + p;
  }while(pgcd(phi,e) != 1);
  return e;
}

// fonction de calcul de l'inverse de (e)mod(Phi(n))
long GenD(long a, long b){
  long r = a, r1 = b, u=1, v=0, u1=0, v1=1;
  long q, rs, us, vs;
  long x = b, y = a;
  while(r1 != 0){
    q = r/r1;
    rs = r;
    us = u;
    vs = v;
    r = r1;
    u = u1;
    v = v1;
    r1 = rs - q*r1;
    u1 = us - q*u1;
    v1 = vs - q*v1;
  }

  return v;
}


// structure d'une cle rsa
struct subkey{
  long n;
  long exp;
};

// structure d'une paire de cle rsa
typedef struct key{
  struct subkey pubKey;
  struct subkey privKey;
}key;

// fonction d'affichage d'une paire de cle rsa
void showKey(key rsa){
  printf("\n\n");
  printf("***Public Key***\n*\n");
  printf("*  n = %d\n", rsa.pubKey.n);
  printf("*  e = %d\n", rsa.pubKey.exp);
  printf("*\n");
  printf("***Private Key***\n*\n");
  printf("*  n = %d\n", rsa.privKey.n);
  printf("*  d = %d\n*\n", rsa.privKey.exp);
  printf("******************\n\n");
}

key GenKey(){
  key rsa;
  GenPhi(19);
  rsa.pubKey.n = n;
  rsa.privKey.n = n;
  rsa.pubKey.exp = GenE(phi);
  rsa.privKey.exp = GenD(phi,rsa.pubKey.exp);
  if( ((rsa.privKey.exp*rsa.pubKey.exp)%phi) != 1 || rsa.privKey.exp < 0 || rsa.privKey.exp == 1 || rsa.privKey.exp == rsa.pubKey.exp){
    rsa = GenKey();
    return rsa;
  }

  printf("p = %d, q = %d\n",p,q);
  printf("Phi(n) = %d \n",phi);
  showKey(rsa);

  return rsa;
}

 int * convert2Bin(long x, unsigned int len){
  int *t = malloc(len * sizeof(unsigned int));
  for(long i=len-1;x>0;i--){
    t[i] = x%2;
    x = x/2;
  }
  return t;
}

unsigned int nbrBit(int x){
  unsigned int i = 0;
  while( x > 0){
    x = x/2;
    i++;    
  }
  return i;
}
/*
char cypherLetter(unsigned int x, unsigned long e, unsigned long n){
  unsigned long result=1;
  for(int i=1; i<=e;i++){
    result = (x*result)%n;
  }
  return (char) result;
}
*/

char cypherLetter(unsigned long x, int *e, unsigned int len, long n){
  unsigned long result = 1;
  long i = len - 1;
  while(i>=0){
    if(e[i] > 0)
      {
        result = (result * x)%n;
      }
    i--;
    x = (x*x)%n;
  }

  return (char) result;
}


char * cypher(char string[], long e, long n){
  printf("\nDebut du chiffrement !!!\n");
  char *cypher = malloc((strlen(string)+1)*sizeof(char));
  
  int * t = malloc(nbrBit(e)*sizeof(int));
  t = convert2Bin(e,nbrBit(e));
  
  for(int i=0;i < strlen(string);i++){
    cypher[i] = cypherLetter((unsigned long) string[i],t,nbrBit(e),n);
  }
  free(t);
  return cypher;
}


int main()
{
  int continuer = 0;

  do{

  key rsa;
  char mot[50];
  rsa = GenKey();
  printf("La paire de cle RSA a bien ete generee !!! \n");
  printf("Quel est le message a chiffrer ?\n");
  scanf("%s",&mot);
  for(int i=0;i<strlen(mot);i++)
    printf("%d ",mot[i]);
  char *motChiffre = malloc((strlen(mot)+1)*sizeof(char));
  motChiffre = cypher(mot, rsa.pubKey.exp, rsa.pubKey.n);
  for(int i=0;i<strlen(motChiffre);i++)
    printf("%d ",motChiffre[i]);
  printf("\nMot apres Chiffrement : %s\n", motChiffre);
  printf("Dechiffrement du message ...\n");
  char *motDeChiffre = malloc((strlen(motChiffre)+1)*sizeof(char));
  motDeChiffre = cypher(motChiffre, rsa.privKey.exp, rsa.privKey.n);
  for(int i=0;i<strlen(motDeChiffre);i++)
    printf("%d ",(int) motDeChiffre[i]);
  printf("\nMot apres Dechiffrement : %s\n", motDeChiffre);
  free(motChiffre);
  free(motDeChiffre);
  printf("Voulez vous reprendre l'operation ? (Oui=1 et Non=0)\n");
  scanf("%d",&continuer);
  }while(continuer);
 
  return 0;
}