/*xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
 U odnosu na Suzy dodaje se mogucnost da zica na oba kraja ima strujni izvor.
xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx */



#pragma hdrstop
#include <condefs.h>

//---------------------------------------------------------------------------
#include <stdlib.h>
#include <conio.h>
#include <math.h>
#include <complex.h>
#include <alloc.h>
#include <dos.h>


#define PI 3.14159265
#define EPS0 8.854E-12
#define MI 4*PI*1E-7

int CalcStoped,CalcPaused,CurrentStep,MaxSteps;// globalne varijable za kontrolu racunanja

struct tocka
{
   double x;
   double y;
   double z;
};

struct complex3Dvector
{
   complex<double> x;
   complex<double> y;
   complex<double> z;
};

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Klasa sluzi za dimenzioniranje matrice te pristup njenim clanovima.
// Pri tome je korisnik oslobodjen rada s pointerima i rezervacijom memorije.
class matrica
{
public:
   int m,n;      //----- broj redaka, odnosno stupaca matrice -------
   double* p;   //---- pointeri na pocetak i kraj matrice
   double* p2;
   matrica(int,int);
   matrica();
   matrica(const matrica&);
   ~matrica(void);
   double& operator ()(int,int);
   matrica& operator =(matrica);
   void dim(int,int);
   void clear(void);
} ;
matrica::matrica(int x,int y)
{
// Konstruktorska funkcija alocira potrebnu memoriju.
// ULAZ:
// int x  - broj redaka;
// int y  - broj stupaca;
  m=x;n=y;
  long int OKsize=(long int)x*y*sizeof(double);
  p =(double *) calloc(OKsize,1);
  if (p==NULL){ printf("Not enough memory");getch();exit (1);}
  p2=p+x*y-1;
}
matrica::matrica()
{
// Konstruktorska funkcija za praznu matricu.
  m=n=0;
  p=p2=NULL;
}
matrica::matrica(const matrica& mat)
{
// kopirni konstruktor omogucuje proslijedjivanje matrice funkciji po vrijednosti
  int i,size;
  m=mat.m;n=mat.n;
  long int OKsize=(long int)m*n*sizeof(double);
  p =(double *) calloc(OKsize,1);
  if (p==NULL){ printf("Not enough memory");getch();exit (1);}
  p2=p+m*n-1;
  size=m*n;
  for(i=0;i<size;++i)
    p[i]=mat.p[i];
}
matrica::~matrica() {free(p);p=NULL;}//destruktor mora oslobodit memoriju
double& matrica::operator ()(int red,int stup)
{
// operator () omogucava pristup i baratanje s pojedinim clanovima matrice
  double *p3;
  p3=p+(red-1)*n-1+stup;
  if ((p3<p)||(p3>p2)){ printf("Matrix element out of bounds !!!!! %i   %i",red,stup);exit(1);}
  return (*p3);
}
matrica& matrica::operator =(matrica mat)
{
// operator = omogucava kopiranje podataka iz jedne matrice u drugu
// pri tome se ciljana matrica predimenzionira i gube se podaci koje je prethodno sadržavala
  int i,size;
  dim(mat.m,mat.n);
  size=m*n;
  for(i=0;i<size;++i)
    p[i]=mat.p[i];
  return(*this);
}
void matrica::dim(int x,int y)
{
//Funkcija za naknadno dimenzioniranje matrice
  if (p!=NULL)free(p);//prvo se oslobodi prethodno rezervirana memorija
// Dalje sve ide kao i kod konstruktora
  m=x; n=y;
  long int OKsize=(long int)x*y*sizeof(double);
  p =(double *) calloc(OKsize,1);
  if (p==NULL){ printf("Not enough memory");getch();exit (1);}
  p2=p+x*y-1;
}
void matrica::clear(void)
{
//Funkcija za brisanje matrice
  if (p!=NULL)free(p);//oslobodi se prethodno rezervirana memorija
  m=n=0;  // sve se resetira
  p=p2=NULL;
}


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Klasa sluzi za dimenzioniranje kompleksne matrice te pristup njenim clanovima.
// Pri tome je korisnik oslobodjen rada s pointerima i rezervacijom memorije.
class compmat
{
public:
   int m,n;      //----- broj redaka, odnosno stupaca matrice -------
   complex<double>* p;   //---- pointeri na pocetak i kraj matrice
   complex<double>* p2;
   compmat(int,int);
   compmat();
   compmat(const compmat&);
   ~compmat(void);
   complex<double>& operator ()(int,int);
   compmat& operator =(compmat);
   void dim(int,int);
   void umetni(int,int,compmat);
   void dodaj(int,int,compmat);
   void clear(void);
   void save(void);
   void nula(void);
} ;
void compmat::save(void)
{
//Funkcija za zapisivanje matrice u datoteku
  int i,size;
  FILE *stream;
  char ime[25];
  scanf("%s", ime);
  stream = fopen(ime, "wt"); //ime="matrica";
  size=m*n;
  for(i=0;i<size;++i)
    fprintf(stream,"%e %e\n",real(p[i]),imag(p[i]));
  fclose(stream);
}
compmat::compmat(int x,int y)
{
// Konstruktorska funkcija alocira potrebnu memoriju.
// ULAZ:
// int x  - broj redaka;
// int y  - broj stupaca;
  m=x;n=y;
  long int OKsize=(long int)x*y*sizeof(complex<double>);
  p =(complex<double> *) calloc(OKsize,1);
  if (p==NULL){ printf("Not enough memory");getch();exit (1);}
  p2=p+x*y-1;
}
compmat::compmat()
{
// Konstruktorska funkcija za praznu matricu.
  m=n=0;
  p=p2=NULL;
}
compmat::compmat(const compmat& mat)
{
// kopirni konstruktor omogucuje proslijedjivanje matrice funkciji po vrijednosti
  int i,size;
  m=mat.m;n=mat.n;
  long int OKsize=(long int)m*n*sizeof(complex<double>);
  p =(complex<double> *) calloc(OKsize,1);
  if (p==NULL){ printf("Not enough memory");getch();exit (1);}
  p2=p+m*n-1;
  size=m*n;
  for(i=0;i<size;++i)
    p[i]=mat.p[i];
}
compmat::~compmat() {free(p);p=NULL;}//destruktor mora oslobodit memoriju
complex<double>& compmat::operator ()(int red,int stup)
{
// operator () omogucava pristup i baratanje s pojedinim clanovima matrice
  complex<double> *p3;
  p3=p+(red-1)*n-1+stup;
  if ((p3<p)||(p3>p2)){ printf("Matrix element out of bounds !!!!! %i   %i",red,stup);exit(1);}
  return (*p3);
}

compmat& compmat::operator =(compmat mat)
{
// operator = omogucava kopiranje podataka iz jedne matrice u drugu
// pri tome se ciljana matrica predimenzionira i gube se podaci koje je prethodno sadržavala
  int i,size;
  dim(mat.m,mat.n);
  size=m*n;
  for(i=0;i<size;++i)
    p[i]=mat.p[i];
  return(*this);
}
void compmat::dim(int x,int y)
{
//Funkcija za naknadno dimenzioniranje matrice
  if (p!=NULL)free(p);//prvo se oslobodi prethodno rezervirana memorija
// Dalje sve ide kao i kod konstruktora
  m=x; n=y;
  long int OKsize=(long int)x*y*sizeof(complex<double>);
  p =(complex<double> *) calloc(OKsize,1);
  if (p==NULL){ printf("Not enough memory");getch();exit (1);}
  p2=p+x*y-1;
}
void compmat::clear(void)
{
//Funkcija za brisanje matrice
  if (p!=NULL)free(p);//oslobodi se prethodno rezervirana memorija
  m=n=0;  // sve se resetira
  p=p2=NULL;
}
void compmat::nula(void)
{
//Funkcija za nuliranje matrice
  int i,size;
  size=m*n;
  for(i=0;i<size;++i)
    p[i]=complex<double>(0,0);
}

void compmat::umetni(int x,int y,compmat B)
{
// U matricu se (s pocetkom u x,y) "kopira" matrica B
  int i,j,k;
  for(j=1;j<=B.m;j++)
    for(i=1;i<=B.n;i++){
      k=(x+j-2)*n+y+i-2;
      p[k]=B(j,i);}
}
void compmat::dodaj(int x,int y,compmat B)
{
// U matricu se (s pocetkom u x,y) zbroji matrica B
  int i,j,k;
  for(j=1;j<=B.m;j++)
    for(i=1;i<=B.n;i++){
      k=(x+j-2)*n+y+i-2;
      p[k]+=B(j,i);}
}

compmat transponirana(compmat A)
{
// vraca transponiranu matricu
  int i,j;
  compmat B(A.n,A.m);

  for(j=1;j<=A.m;j++)
    for(i=1;i<=A.n;i++)
      B(i,j)=A(j,i);
  return(B);
}


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

compmat lokalna (tocka,tocka,tocka,tocka);
compmat medjulokalna (tocka,tocka,tocka,tocka);
compmat precizno (double,double,double);

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Klasa definira ravnu zicu kao objekt. Definirana je geometrija te funkcije za
// racunanje matrica impedancije. Definiran je i niz za koordinate cvorova te
// vrijednosti struje duz zice.
class zica
{
public:
   tocka t1; //pocetna i krajnja tocka zice.
   tocka t2; //zasad se podrazumijeva da imaju isti y i z, a razliciti x.
   double r; //radijus
   double L; //ukupna duljina zice
   int n; //broj konacnih elemenata
   complex<double> napon; //napon narinut na srednji element
   complex<double> I0; //strujni generator prikljucen na pocetak zice
   complex<double> IL; //strujni generator prikljucen na kraj zice
   tocka* cvor; //koordinate cvorova
   compmat struja; //iznosi struje u cvorovima
   zica(tocka,tocka,double,int,complex<double>,complex<double>,complex<double>);// konstruktor (t1,t2,a,n,napon,I0,IL)
   zica();
   ~zica(void);//destruktor
   void dim(tocka,tocka,double,int,complex<double>,complex<double>,complex<double>);// funkcija za naknadno dimenzioniranje zice
   compmat napajanje();//funkcija vraca vektor desne strane u slucaju strujnog generatora
   compmat vlastitaimp(void);// funkcija vraca matricu vlastite impedancije
};

zica::zica(tocka ta,tocka tb,double rad,int brel,complex<double> V,complex<double> Ia,complex<double> Ib)
{
// Konstruktorska funkcija alocira potrebnu memoriju i racuna pomocne varijable.
// ULAZ:  (t1,t2,a,n)
  int i;
  double dx,dy,dz;

  t1=ta;t2=tb;r=rad;n=brel;napon=V;I0=Ia;IL=Ib;
  L=tb.x-ta.x;
  dx=L/n;dy=0.;dz=0.;
  long int OKsize=(long int)(n+1)*sizeof(tocka);
  cvor =(tocka *) calloc(OKsize,1);
  if (cvor==NULL){ printf("Not enough memory");getch();exit(1);}
  struja.dim(n+1,1);
  struja(1,1)=I0;struja(n+1,1)=IL;
  cvor[0]=t1; cvor[n]=t2;
  for (i=1;i<n;i++)
    {cvor[i].x=cvor[i-1].x+dx;cvor[i].y=t1.y;cvor[i].z=t1.z;}
}
zica::zica()
{
// Konstruktorska funkcija za praznu varijablu.
  t1.x=0;t1.y=0;t1.z=0;
  t2.x=0;t2.y=0;t2.z=0;
  r=0;n=0;L=0;napon=complex<double>(0.,0.);
  I0=complex<double>(0.,0.); IL=complex<double>(0.,0.);
  cvor=NULL;struja.dim(1,1);
}
zica::~zica() {free(cvor);cvor=NULL;struja.clear();}//destruktor mora oslobodit memoriju
void zica::dim(tocka ta,tocka tb,double rad,int brel,complex<double> V,complex<double> Ia,complex<double> Ib)
{
// Funkcija alocira potrebnu memoriju i racuna pomocne varijable.
// ULAZ:  (t1,t2,a,n)
  int i;
  double dx,dy,dz;

  if (cvor!=NULL)free(cvor);struja.clear();
  t1=ta;t2=tb;r=rad;n=brel;napon=V;I0=Ia;IL=Ib;
  L=tb.x-ta.x;
  dx=L/n;dy=0.;dz=0.;
  long int OKsize=(long int)(n+1)*sizeof(tocka);
  cvor =(tocka *) calloc(OKsize,1);
  if (cvor==NULL){ printf("Not enough memory");getch();exit(1);}
  struja.dim(n+1,1);
  struja(1,1)=I0;struja(n+1,1)=IL;
  cvor[0]=t1; cvor[n]=t2;
  for (i=1;i<n;i++)
    {cvor[i].x=cvor[i-1].x+dx;cvor[i].y=t1.y;cvor[i].z=t1.z;}
}


compmat zica::vlastitaimp(void)
{
 int i,j,dijagonala;
 double dx;
 compmat imp,lok;

 imp.dim(n-1,n-1);
 dx=L/n;

 for(j=1;j<=2;j++){ // elementi izvora
   for(i=1;i<=n;i++){ // elementi cilja
      if (i==j) lok=precizno(cvor[j-1].x,cvor[j].x,cvor[j].z);
      else lok=lokalna(cvor[j-1],cvor[j],cvor[i-1],cvor[i]);
      if(j==2 && i!=1)
	    imp(j-1,i-1)+=lok(1,1); //a11
      if(j==2 && i!=n)
	    imp(j-1,i)+=lok(1,2); //a12
      if(j==1 && i!=1)
	    imp(j,i-1)+=lok(2,1); //a21
      if(j==1 && i!=n)
	    imp(j,i)+=lok(2,2); //a22
   }//i petlja
 }//j petlja

 for(j=2;j<=n-1;j++){ // elementi izvora
   for(i=1;i<=n-1;i++){ // elementi cilja
     dijagonala=abs(i-j);
     imp(j,i)=imp(1,dijagonala+1);
   }//i petlja
 }//j petlja
 return(imp);
}
compmat zica::napajanje(void)
{
 int i,j;
 compmat b,c,lok;

 c.dim(n-1,1);
 b.dim(n-1,1);
 i=1;
  for(j=1;j<=n;j++){ // elementi izvora
   if (i==j) lok=precizno(cvor[j-1].x,cvor[j].x,cvor[j].z);
   else lok=lokalna(cvor[j-1],cvor[j],cvor[i-1],cvor[i]);
   if(j!=1)
    b(j-1,1)-=lok(1,1); //a11
   if(j!=n)
    b(j,1)-=lok(2,1); //a21
  }
 if (I0!=complex<double>(0.,0.))
      for(j=1;j<=n-1;j++) c(j,1)+=b(j,1)*I0;
 if (IL!=complex<double>(0.,0.))
      for(j=1;j<=n-1;j++) c(j,1)+=b(n-j,1)*IL;


  return(c);
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
compmat medjunapajanje (zica *prva,zica *druga)
// Funkcija racuna matricu medjuimpedancije izmedju dvi zice
{
 int i,j;
 compmat imp,lok;

 imp.dim(druga->n-1,1);

 j=1; // elementi izvora na prvoj zici
   for(i=1;i<=druga->n;i++){ // elementi cilja na drugoj zici
      lok=medjulokalna(prva->cvor[j-1],prva->cvor[j],druga->cvor[i-1],druga->cvor[i]);
      if(i!=1)
	    imp(i-1,1)-=prva->I0*lok(1,1); //a11
      if(i!=druga->n)
	    imp(i,1)-=prva->I0*lok(1,2); //a12
      //if(j!=prva->n && i!=1)
	   // imp(j,i-1)+=lok(2,1); //a21
      //if(j!=prva->n && i!=druga->n)
	    //imp(j,i)+=lok(2,2); //a22
   }//i petlja
 //j petlja

 return(imp);
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
compmat medjuimp (zica *prva,zica *druga)
// Funkcija racuna matricu medjuimpedancije izmedju dvi zice
{
 int i,j;
 compmat imp,lok;

 imp.dim(prva->n-1,druga->n-1);

 for(j=1;j<=prva->n;j++){ // elementi izvora na prvoj zici
   for(i=1;i<=druga->n;i++){ // elementi cilja na drugoj zici
      lok=medjulokalna(prva->cvor[j-1],prva->cvor[j],druga->cvor[i-1],druga->cvor[i]);
      if(j!=1 && i!=1)
	    imp(j-1,i-1)+=lok(1,1); //a11
      if(j!=1 && i!=druga->n)
	    imp(j-1,i)+=lok(1,2); //a12
      if(j!=prva->n && i!=1)
	    imp(j,i-1)+=lok(2,1); //a21
      if(j!=prva->n && i!=druga->n)
	    imp(j,i)+=lok(2,2); //a22
   }//i petlja
 }//j petlja

 return(imp);
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
compmat rijesisustav(compmat m,compmat v)
// Funkcija rjesava matricni sustav mx=v i vraca x
{
  int i,j,k,n;
  compmat A,b;

  A=m;b=v;
  if (A.m!=A.n){ printf("Matrica nije kvadratna!");getch();exit(1);}
  if (A.n!=b.m){ printf("Matrica i vektor nisu iste dimenzije!");getch();exit(1);}
  n=A.n;

 for (k=1;k<=n-1;k++){
    for (i=k+1;i<=n;i++){
        A(i,k)=A(i,k)/A(k,k);
        for (j=k+1;j<=n;j++){
            A(i,j)=A(i,j)-A(i,k)*A(k,j);
        }
        b(i,1)=b(i,1)-b(k,1)*A(i,k);
    }
  }
  b(n,1)=b(n,1)/A(n,n);
  for (i=n-1;i>=1;i--){
    for (j=i+1;j<=n;j++){
        b(i,1)=b(i,1)-A(i,j)*b(j,1);
    }
  b(i,1)=b(i,1)/A(i,i);
  }
  return(b);
}

//**************************************************************************************
//***                 G L O B A L N E    V A R I J A B L E                           ***
//**************************************************************************************
int brojzica,totalnodes,nf,ulazna,freqcvor,ispod;
double  omega,eps,epsr,a,freq,sgm,startf,stopf,Einc,visina;
double  epsr1,epsr2,sgm1,sgm2,dub1;
//double wx[100],gx[100];//Gauss tocke i tezine
double gx[]={0.0,-0.90617985,-0.53846931,0.0,0.53846931,0.90617985};
double wx[]={0.0,0.23692689,0.47862867,0.56888889,0.23692689,0.47862867};
complex<double> k1,k2,epsef,jot,n_;
complex<double> gama2,Z[3],nn[3];
zica wire[100];
compmat rjesenja,impedance;
double dijagram[360];
//**************************************************************************************

void gtocke(int n){
/*
********************************************************************
*  funkcija izracunava tocke za gaussovu integraciju te pripadne   *
*  tezinske faktore koji se pohranjuju u nizu gx[] i wx[].         *
*  vrijednosti gx[0] i wx[0] su namjerno preskocene radi kompatibi-*
*  lnosti s funkcijama za integraciju                              *
********************************************************************
*/
 int r,i,k,ic,a;
 float g,test,t,u,v,p,dp,s,sum;

 if (n<1) return;

 if (n==1){
   gx[1]=0; wx[1]=2; return;}

 r=n; g=-1;
 for (i=1;i<=n;i++){
   test=-2;
   ic=n+1-i;
   if(ic<1) return;
   while(1){
     s=g; t=1; u=1; v=0;
     for (k=2;k<=n;k++){
       a=k;
       p=((2.0*a-1.0)*s*g-(a-1.0)*t)/a;
       dp=((2.0*a-1.0)*(s+g*u)-(a-1.0)*v)/a;
       v=u; u=dp; t=s; s=p;
     }
     if (fabs((test-g)/(test+g))<0.0000005) break;
     sum=0;
     if(i!=1)  for (k=2;k<=i;k++) sum+=1/(g-gx[k-1]);
     test=g;
     g=g-p/(dp-p*sum);
   }
   gx[ic]=-g; gx[i]=g;
   wx[i]=2/(r*t*dp);
   wx[ic]=wx[i];
   g=g-r*t/((r+2.)*g*dp+r*v-2.*r*t*sum);
 }
 return;
}

compmat precizno (double xa,double xb,double z)
{
 double hx,hy,bx,by,x1,x2,ya,yb,delta;
 double pom1,radijus,radijus2,kut;
 complex<double> rez1,rez2,rtm,clan1,clan2,G0,Gi;
 int i,j,nx;
 compmat mat(2,2),temp(2,2);

 nx=5; // broj Gauss tocaka povezan sa gtocke() u Racunaj() !!!!!!!
 delta=(xb-xa)*(xb-xa);//deltax^2

 if(epsr==-1)rtm=1.; //idealno vodljiva zemlja
 if(epsr==-2)rtm=0.; // slobodan prostor...

 // Slavkova integracija, unutrasnji integral se dili na dva podpodrucja
 hx=(xb-xa)/2;
 bx=xa+hx;
 for (i=1;i<=nx;i++){
    x1=hx*gx[i]+bx;
    ya=xa; yb=x1; // Prvo podpodrucje od pocetka segmenta do tocke izvora
    hy=(yb-ya)/2;
    by=ya+hy;
    for (j=1;j<=nx;j++){
       x2=hy*gx[j]+by;

       radijus=sqrt((x2-x1)*(x2-x1)+a*a);
       radijus2=sqrt(radijus*radijus+4*z*z);

       if(epsr>0){ //konacno vodljiva zemlja
         kut=atan(radijus/(2*z));
         clan1=n_*cos(kut); clan2=sqrt(n_-sin(kut)*sin(kut));
         rtm=(clan1-clan2)/(clan1+clan2);}

       G0=exp(-jot*k1*radijus)/radijus; Gi=exp(-jot*k1*radijus2)/radijus2;
       rez2=G0-rtm*Gi;
       rez1=k1*k1*rez2;
        //a11
       pom1=(xb-x1)*(xb-x2);
       temp(1,1)+=wx[j]*(pom1*rez1-rez2);
        //a12
       pom1=(xb-x1)*(x2-xa);
       temp(1,2)+=wx[j]*(pom1*rez1+rez2);
        //a21
       pom1=(x1-xa)*(xb-x2);
       temp(2,1)+=wx[j]*(pom1*rez1+rez2);
        //a22
       pom1=(x1-xa)*(x2-xa);
       temp(2,2)+=wx[j]*(pom1*rez1-rez2);
    }
    mat(1,1)+=temp(1,1)*hy*wx[i];
    mat(1,2)+=temp(1,2)*hy*wx[i];
    mat(2,1)+=temp(2,1)*hy*wx[i];
    mat(2,2)+=temp(2,2)*hy*wx[i];
    temp.nula(); //izbrisat vrijednosti

    ya=x1; yb=xb;  // Drugo podpodrucje od tocke izvora do kraja segmenta
    hy=(yb-ya)/2;
    by=ya+hy;
    for (j=1;j<=nx;j++){
       x2=hy*gx[j]+by;

       radijus=sqrt((x2-x1)*(x2-x1)+a*a);
       radijus2=sqrt(radijus*radijus+4*z*z);

       if(epsr>0){ //konacno vodljiva zemlja
         kut=atan(radijus/(2*z));
         clan1=n_*cos(kut); clan2=sqrt(n_-sin(kut)*sin(kut));
         rtm=(clan1-clan2)/(clan1+clan2);}

       G0=exp(-jot*k1*radijus)/radijus; Gi=exp(-jot*k1*radijus2)/radijus2;
       rez2=G0-rtm*Gi;
       rez1=k1*k1*rez2;
        //a11
       pom1=(xb-x1)*(xb-x2);
       temp(1,1)+=wx[j]*(pom1*rez1-rez2);
        //a12
       pom1=(xb-x1)*(x2-xa);
       temp(1,2)+=wx[j]*(pom1*rez1+rez2);
        //a21
       pom1=(x1-xa)*(xb-x2);
       temp(2,1)+=wx[j]*(pom1*rez1+rez2);
        //a22
       pom1=(x1-xa)*(x2-xa);
       temp(2,2)+=wx[j]*(pom1*rez1-rez2);
   }
    mat(1,1)+=temp(1,1)*hy*wx[i];
    mat(1,2)+=temp(1,2)*hy*wx[i];
    mat(2,1)+=temp(2,1)*hy*wx[i];
    mat(2,2)+=temp(2,2)*hy*wx[i];
    temp.nula(); //izbrisat vrijednosti
 }
 mat(1,1)=mat(1,1)*hx/delta;
 mat(1,2)=mat(1,2)*hx/delta;
 mat(2,1)=mat(2,1)*hx/delta;
 mat(2,2)=mat(2,2)*hx/delta;
 return (mat);
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
compmat lokalna (tocka ta,tocka tb,tocka tc,tocka td)
{
 /**************************************************************************************
 Funkcija racuna lokalnu matricu impedancije.
 ta-tb i tc-td su koordinate promatranih elemenata. (zasad igraju samo x-evi)
 ***************************************************************************************/
 double hx,hy,bx,by;
 compmat mat(2,2);
 int i,j,nx,ny;
 tocka t1,t2;
 double pom1,rad,radijus2,kut;
 complex<double> rez1,rez2,rtm,clan1,clan2;

 static double gtocke[]={0.0,-0.861136311594053,-0.339981043584856,0.339981043584856,0.861136311594053};
 static double tezine[]={0.0,0.347854845137454,0.652145154862546,0.652145154862546,0.347854845137454};

 nx=ny=4;

 t1=ta; t2=tc;

 hx=(tb.x-ta.x)/2.0;
 hy=(td.x-tc.x)/2.0;

   by=tc.x+hy;
   bx=ta.x+hx;

 if(epsr>0){ //konacno vodljiva zemlja
   for (j=1;j<=ny;j++){
     t2.x=hy*gtocke[j]+by;
     for (i=1;i<=nx;i++){
       t1.x=hx*gtocke[i]+bx;

       rad=sqrt((t1.x-t2.x)*(t1.x-t2.x)+a*a);
       radijus2=sqrt(rad*rad+4*t1.z*t1.z);
       kut=atan(rad/(2*t1.z));
       clan1=n_*cos(kut); clan2=sqrt(n_-sin(kut)*sin(kut));
       rtm=(clan1-clan2)/(clan1+clan2);
       rez1=k1*k1*(exp(-jot*k1*rad)/rad-rtm*exp(-jot*k1*radijus2)/radijus2);
       rez2=exp(-jot*k1*rad)/rad-rtm*exp(-jot*k1*radijus2)/radijus2;

       pom1=(tb.x-t1.x)*(td.x-t2.x);
       mat(1,1)+=tezine[j]*tezine[i]*(pom1*rez1-rez2);

       pom1=(tb.x-t1.x)*(t2.x-tc.x);
       mat(1,2)+=tezine[j]*tezine[i]*(pom1*rez1+rez2);

       pom1=(t1.x-ta.x)*(td.x-t2.x);
       mat(2,1)+=tezine[j]*tezine[i]*(pom1*rez1+rez2);

       pom1=(t1.x-ta.x)*(t2.x-tc.x);
       mat(2,2)+=tezine[j]*tezine[i]*(pom1*rez1-rez2);
     }
   }
 }

 if(epsr==-1){ //idealno vodljiva zemlja
   rtm=1.;
   for (j=1;j<=ny;j++){
     t2.x=hy*gtocke[j]+by;
     for (i=1;i<=nx;i++){
       t1.x=hx*gtocke[i]+bx;

       rad=sqrt((t1.x-t2.x)*(t1.x-t2.x)+a*a);
       radijus2=sqrt(rad*rad+4*t1.z*t1.z);
       rez1=k1*k1*(exp(-jot*k1*rad)/rad-rtm*exp(-jot*k1*radijus2)/radijus2);
       rez2=exp(-jot*k1*rad)/rad-rtm*exp(-jot*k1*radijus2)/radijus2;

       pom1=(tb.x-t1.x)*(td.x-t2.x);
       mat(1,1)+=tezine[j]*tezine[i]*(pom1*rez1-rez2);

       pom1=(tb.x-t1.x)*(t2.x-tc.x);
       mat(1,2)+=tezine[j]*tezine[i]*(pom1*rez1+rez2);

       pom1=(t1.x-ta.x)*(td.x-t2.x);
       mat(2,1)+=tezine[j]*tezine[i]*(pom1*rez1+rez2);

       pom1=(t1.x-ta.x)*(t2.x-tc.x);
       mat(2,2)+=tezine[j]*tezine[i]*(pom1*rez1-rez2);
     }
   }
 }

 if(epsr==-2){ // slobodan prostor...
   for (j=1;j<=ny;j++){
     t2.x=hy*gtocke[j]+by;
     for (i=1;i<=nx;i++){
       t1.x=hx*gtocke[i]+bx;

       rad=sqrt((t1.x-t2.x)*(t1.x-t2.x)+a*a);
       rez1=k1*k1*(exp(-jot*k1*rad)/rad);
       rez2=exp(-jot*k1*rad)/rad;

       pom1=(tb.x-t1.x)*(td.x-t2.x);
       mat(1,1)+=tezine[j]*tezine[i]*(pom1*rez1-rez2);

       pom1=(tb.x-t1.x)*(t2.x-tc.x);
       mat(1,2)+=tezine[j]*tezine[i]*(pom1*rez1+rez2);

       pom1=(t1.x-ta.x)*(td.x-t2.x);
       mat(2,1)+=tezine[j]*tezine[i]*(pom1*rez1+rez2);

       pom1=(t1.x-ta.x)*(t2.x-tc.x);
       mat(2,2)+=tezine[j]*tezine[i]*(pom1*rez1-rez2);
     }
   }
 }

 mat(1,1)=mat(1,1)/4.0;
 mat(1,2)=mat(1,2)/4.0;
 mat(2,1)=mat(2,1)/4.0;
 mat(2,2)=mat(2,2)/4.0;

 return (mat);
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
compmat medjulokalna (tocka ta,tocka tb,tocka tc,tocka td)
{
 /**************************************************************************************
 Funkcija racuna lokalnu matricu medjuimpedancije.
 ta-tb i tc-td su koordinate promatranih elemenata. (zasad igraju samo x i y)
 ***************************************************************************************/
 double hx,hy,bx,by;
 compmat mat(2,2);
 int i,j,nx,ny;
 tocka t1,t2;
 double pom1,rad,radijus2,radhor,kut,deltay,deltaz;
 complex<double> rez1,rez2,rtm,clan1,clan2;

 static double gtocke[]={0.0,-0.861136311594053,-0.339981043584856,0.339981043584856,0.861136311594053};
 static double tezine[]={0.0,0.347854845137454,0.652145154862546,0.652145154862546,0.347854845137454};

 nx=ny=4;

 t1=ta; t2=tc;

 deltay=(tc.y-ta.y)*(tc.y-ta.y);
 deltaz=(tc.z-ta.z)*(tc.z-ta.z);
 hx=(tb.x-ta.x)/2.0;
 hy=(td.x-tc.x)/2.0;

   by=tc.x+hy;
   bx=ta.x+hx;

 if(epsr>0){ //konacno vodljiva zemlja
   for (j=1;j<=ny;j++){
     t2.x=hy*gtocke[j]+by;
     for (i=1;i<=nx;i++){
       t1.x=hx*gtocke[i]+bx;

       rad=sqrt(deltay+(t1.x-t2.x)*(t1.x-t2.x)+deltaz);
       radhor=deltay+(t1.x-t2.x)*(t1.x-t2.x);
       radijus2=sqrt(radhor+(ta.z+tc.z)*(ta.z+tc.z));
       kut=atan(radhor/(ta.z+tc.z));
       clan1=n_*cos(kut); clan2=sqrt(n_-sin(kut)*sin(kut));
       rtm=(clan1-clan2)/(clan1+clan2);
       rez1=k1*k1*(exp(-jot*k1*rad)/rad-rtm*exp(-jot*k1*radijus2)/radijus2);
       rez2=exp(-jot*k1*rad)/rad-rtm*exp(-jot*k1*radijus2)/radijus2;

       pom1=(tb.x-t1.x)*(td.x-t2.x);
       mat(1,1)+=tezine[j]*tezine[i]*(pom1*rez1-rez2);

       pom1=(tb.x-t1.x)*(t2.x-tc.x);
       mat(1,2)+=tezine[j]*tezine[i]*(pom1*rez1+rez2);

       pom1=(t1.x-ta.x)*(td.x-t2.x);
       mat(2,1)+=tezine[j]*tezine[i]*(pom1*rez1+rez2);

       pom1=(t1.x-ta.x)*(t2.x-tc.x);
       mat(2,2)+=tezine[j]*tezine[i]*(pom1*rez1-rez2);
     }
   }
 }

 if(epsr==-1){ //idealno vodljiva zemlja
   rtm=1.;
   for (j=1;j<=ny;j++){
     t2.x=hy*gtocke[j]+by;
     for (i=1;i<=nx;i++){
       t1.x=hx*gtocke[i]+bx;

       rad=sqrt(deltay+(t1.x-t2.x)*(t1.x-t2.x)+deltaz);
       radhor=deltay+(t1.x-t2.x)*(t1.x-t2.x);
       radijus2=sqrt(radhor+(ta.z+tc.z)*(ta.z+tc.z));
       rez1=k1*k1*(exp(-jot*k1*rad)/rad-rtm*exp(-jot*k1*radijus2)/radijus2);
       rez2=exp(-jot*k1*rad)/rad-rtm*exp(-jot*k1*radijus2)/radijus2;

       pom1=(tb.x-t1.x)*(td.x-t2.x);
       mat(1,1)+=tezine[j]*tezine[i]*(pom1*rez1-rez2);

       pom1=(tb.x-t1.x)*(t2.x-tc.x);
       mat(1,2)+=tezine[j]*tezine[i]*(pom1*rez1+rez2);

       pom1=(t1.x-ta.x)*(td.x-t2.x);
       mat(2,1)+=tezine[j]*tezine[i]*(pom1*rez1+rez2);

       pom1=(t1.x-ta.x)*(t2.x-tc.x);
       mat(2,2)+=tezine[j]*tezine[i]*(pom1*rez1-rez2);
     }
   }
 }

 if(epsr==-2){ //slobodan prostor
   for (j=1;j<=ny;j++){
     t2.x=hy*gtocke[j]+by;
     for (i=1;i<=nx;i++){
       t1.x=hx*gtocke[i]+bx;

       rad=sqrt(deltay+(t1.x-t2.x)*(t1.x-t2.x)+deltaz);
       rez1=k1*k1*(exp(-jot*k1*rad)/rad);
       rez2=exp(-jot*k1*rad)/rad;

       pom1=(tb.x-t1.x)*(td.x-t2.x);
       mat(1,1)+=tezine[j]*tezine[i]*(pom1*rez1-rez2);

       pom1=(tb.x-t1.x)*(t2.x-tc.x);
       mat(1,2)+=tezine[j]*tezine[i]*(pom1*rez1+rez2);

       pom1=(t1.x-ta.x)*(td.x-t2.x);
       mat(2,1)+=tezine[j]*tezine[i]*(pom1*rez1+rez2);

       pom1=(t1.x-ta.x)*(t2.x-tc.x);
       mat(2,2)+=tezine[j]*tezine[i]*(pom1*rez1-rez2);
     }
   }
 }

 mat(1,1)=mat(1,1)/4.0;
 mat(1,2)=mat(1,2)/4.0;
 mat(2,1)=mat(2,1)/4.0;
 mat(2,2)=mat(2,2)/4.0;

 return (mat);
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

complex<double> racunaj(int index){
  int i,j,k,jpomak,ipomak;
  compmat m,m1,x;
  complex<double> ipom,medju,zm,zin,wavegtm,wavertm,R0[2],Rtm,Zeq,X1;
  double dx;

  omega=2*PI*freq;

// za dijagram zracenja koristimo dvosloj
  gama2=omega*sqrt(MI*(epsr1*EPS0-jot*sgm1/omega));
  nn[0]=1.;
  nn[1]=sqrt(epsr1-jot*sgm1/(omega*EPS0));
  nn[2]=sqrt(epsr2-jot*sgm2/(omega*EPS0));
  Z[0]=sqrt(MI/EPS0);
  Z[1]=sqrt((jot*omega*MI)/(sgm1+jot*omega*epsr1*EPS0));
  Z[2]=sqrt((jot*omega*MI)/(sgm2+jot*omega*epsr2*EPS0));


// sad triba izracunat parametre ekvivalentnog jednosloja za proracun raspodjele struje
  for(i=0;i<2;i++) R0[i]=(Z[i+1]-Z[i])/(Z[i+1]+Z[i]);
  Rtm=(R0[0]+R0[1]*exp(-2*gama2*dub1))/(1+R0[0]*R0[1]*exp(-2*gama2*dub1));
  Zeq=Z[0]*((1+Rtm)/(1-Rtm));
  X1=(jot*omega*MI)/(Zeq*Zeq);
  epsr=imag(X1)/(omega*EPS0);
  sgm=real(X1);

  eps=epsr*EPS0;
  epsef=complex<double>(eps,-sgm/omega);

  //gtocke(5);// za precizno

  if(ispod==0){ //zica iznad zemlje
    k1=omega*sqrt(MI*EPS0);
    k2=omega*sqrt(MI*epsef);
    n_=epsef/EPS0;
    ipom=complex<double>(0.,-4*PI*omega*EPS0);
    if(epsr>0)wavertm=(n_-sqrt(n_))/(n_+sqrt(n_));
    if(epsr==-1) wavertm=complex<double>(1.0,0.0);
    if(epsr==-2) wavertm=complex<double>(0.0,0.0);}
  else{  //zica u zemlji
    k2=omega*sqrt(MI*EPS0);
    k1=omega*sqrt(MI*epsef);
    n_=EPS0/epsef;
    ipom=-4*jot*PI*omega*epsef;
    wavegtm=(2*sqrt(1/n_))/(1/n_+sqrt(1/n_));}

  m.dim(totalnodes,totalnodes);
  jpomak=1;
  for(i=0;i<brojzica;i++){
     m.umetni(jpomak,jpomak,wire[i].vlastitaimp());
     ipomak=jpomak;
     for(j=i+1;j<brojzica;j++){
        ipomak+=wire[j-1].n-1;
        m1=medjuimp(wire+i,wire+j);
        m.umetni(jpomak,ipomak,m1);
        m.umetni(ipomak,jpomak,transponirana(m1));
     }
     jpomak+=wire[i].n-1;
  }


  m1.dim(totalnodes,1);
  if(Einc==0){
  //antenski mod
   jpomak=0;
   for(i=0;i<brojzica;i++){
     m1(jpomak+(wire[i].n-1)/2,1)=ipom*wire[i].napon/2;
     m1(jpomak+(wire[i].n-1)/2+1,1)=ipom*wire[i].napon/2;
     jpomak+=wire[i].n-1;
     }
  }
  else{
   //rasprsivacki mod
   jpomak=0;
   for(i=0;i<brojzica;i++){
      dx=wire[i].cvor[1].x-wire[i].cvor[0].x;
      if(ispod==0)medju=ipom*Einc*dx*(exp(-jot*(visina-wire[i].cvor[0].z)*k1)-wavertm*exp(-jot*(wire[i].cvor[0].z+visina)*k1));
      else medju=ipom*Einc*dx*wavegtm*exp(jot*wire[i].cvor[0].z*k1);
      for(j=1;j<wire[i].n;j++){
         jpomak++;
         m1(jpomak,1)=medju;
      }
   }
  }
  //m.save();
  //m1.save();

// sad triba pozvat napajanje za svaku zicu koja ima strujni generator
// i to dodat na vektor m1


  jpomak=1;
  for(i=0;i<brojzica;i++){
     if (!(wire[i].I0==complex<double>(0.,0.)&&wire[i].I0==complex<double>(0.,0.))){
            m1.dodaj(jpomak,1,wire[i].napajanje());
            ipomak=1;
            for(j=0;j<brojzica;j++){
              if(j!=i)
                  m1.dodaj(ipomak,1,medjunapajanje(wire+i,wire+j));
              ipomak+=wire[j].n-1;
     }}
     jpomak+=wire[i].n-1;
  }

  //m1=wire[0].napajanje();
  //m1.save();
    //m.save();
  x=rijesisustav(m,m1);
  m1.clear();

 zin=complex<double>(0.,0.);

// medjuimpedancija
 jpomak=0;ipomak=0;
 for (i=0;i<index;i++) jpomak+=wire[i].n-1;

 for (i=0;i<brojzica;i++){
   if(i!=index){
     zm=complex<double>(0.,0.);
     for(j=1;j<wire[index].n-1;j++){
         medju=complex<double>(0.,0.);
         for(k=1;k<wire[i].n-1;k++){
	         medju+=m(jpomak+j,ipomak+k)*x(ipomak+k,1);}
         zm+=medju*x(jpomak+j,1);
     }
   }
   ipomak+=wire[i].n-1;
 }
 medju=x(jpomak+wire[index].n/2,1);
 medju=medju*medju;
 zin+=zm/(medju*ipom);

// vlastita impedancija
 zm=complex<double>(0.,0.);
 for(j=1;j<wire[index].n-1;j++){
    medju=complex<double>(0.,0.);
    for(k=1;k<wire[index].n-1;k++){
        medju+=m(jpomak+j,jpomak+k)*conj(x(jpomak+k,1));}
    zm+=medju*x(jpomak+j,1);
 }
 medju=x(jpomak+wire[index].n/2,1);
 zin+=zm/(abs(medju)*abs(medju)*ipom);
 m.clear();

 ipomak=0;
 for(i=0;i<brojzica;i++)
    for(j=1;j<=wire[i].n-1;j++){
       ipomak++;
       wire[i].struja(j+1,1)=x(ipomak,1);
    }
 x.clear();
 return(zin);
}

complex3Dvector elpolje(tocka T)
{
 int i,j,ii,jj;
 double deltax,dl;
 complex<double> suma,sumax,sumay,sumaz,term2,term3;
 complex<double> dGdx,dGdy,dGdz,struja,medju,clan1,clan2;
 double A,B,dx;
 tocka t1,t2,ti;
 complex3Dvector polje;
 static double gtocke[]={0.33998104,0.86113631};
 static double tezine[]={0.65214515,0.34785485};
 double rad,radijus2,kut;
 complex<double> rez1,rez2,rez3,rtm,gama2x,gama2y,ro[2],kut1,kut2;

 polje.x=complex<double>(0.,0.);
 polje.y=complex<double>(0.,0.);
 polje.z=complex<double>(0.,0.);

 for (j=0;j<brojzica;j++){
  ti.y=wire[j].cvor[0].y;ti.z=wire[j].cvor[0].z;//integriramo po zici y i z su konst.
  for (i=0;i<wire[j].n;i++){
    t1=wire[j].cvor[i];
    t2=wire[j].cvor[i+1];
    deltax=t2.x-t1.x; dl=a;//deltax/1.;
    term2=((wire[j].struja(i+2,1)-wire[j].struja(i+1,1))/deltax);//derivacija struje
    A=deltax/2; B=(t1.x+t2.x)/2;
    suma=complex<double>(0,0);sumax=complex<double>(0,0);
    sumay=complex<double>(0,0);sumaz=complex<double>(0,0);
    // gtocke i tezine su simetricne pa racunamo dvi po dvi
    for(ii=0;ii<2;ii++){
        dx=A*gtocke[ii];
        ti.x=B+dx;
        //udaljenost tocke promatranja od tocke izvora na anteni
        rad=sqrt((T.x-ti.x)*(T.x-ti.x)+(T.y-ti.y)*(T.y-ti.y)+(T.z-ti.z)*(T.z-ti.z));
        //udaljenost tocke promatranja od tocke na preslikanoj anteni
        radijus2=sqrt((T.x-ti.x)*(T.x-ti.x)+(T.y-ti.y)*(T.y-ti.y)+(T.z+ti.z)*(T.z+ti.z));
        kut=atan(sqrt((T.x-ti.x)*(T.x-ti.x)+(T.y-ti.y)*(T.y-ti.y))/(T.z+ti.z));

        clan1=n_*cos(kut); clan2=sqrt(n_-sin(kut)*sin(kut));
        rtm=(clan1-clan2)/(clan1+clan2);


        gama2x=-jot*k1*sin(kut);
        gama2y=sqrt(gama2*gama2-gama2x*gama2x);
        medju=(nn[0]/nn[1])*sin(kut);
        kut1=-jot*log(jot*medju+sqrt(1-medju*medju)); //kut upada u prvom sloju
        medju=(nn[1]/nn[2])*sin(kut1);
        kut2=-jot*log(jot*medju+sqrt(1-medju*medju)); //kut upada u drugom sloju
        ro[0]=(Z[0]*cos(kut)-Z[1]*cos(kut1))/(Z[0]*cos(kut)+Z[1]*cos(kut1));
        ro[1]=(Z[1]*cos(kut1)-Z[2]*cos(kut2))/(Z[1]*cos(kut1)+Z[2]*cos(kut2));
        rtm=(ro[0]+ro[1]*exp(-2*gama2y*dub1))/(1+ro[0]*ro[1]*exp(-2*gama2y*dub1));

        rez1=exp(-jot*k1*rad)/rad-rtm*exp(-jot*k1*radijus2)/radijus2;
        // dG/dx
        rad=sqrt((T.x-dl-ti.x)*(T.x-dl-ti.x)+(T.y-ti.y)*(T.y-ti.y)+(T.z-ti.z)*(T.z-ti.z));
        radijus2=sqrt((T.x-dl-ti.x)*(T.x-dl-ti.x)+(T.y-ti.y)*(T.y-ti.y)+(T.z+ti.z)*(T.z+ti.z));
        rez2=exp(-jot*k1*rad)/rad-rtm*exp(-jot*k1*radijus2)/radijus2;
        rad=sqrt((T.x+dl-ti.x)*(T.x+dl-ti.x)+(T.y-ti.y)*(T.y-ti.y)+(T.z-ti.z)*(T.z-ti.z));
        radijus2=sqrt((T.x+dl-ti.x)*(T.x+dl-ti.x)+(T.y-ti.y)*(T.y-ti.y)+(T.z+ti.z)*(T.z+ti.z));
        rez3=exp(-jot*k1*rad)/rad-rtm*exp(-jot*k1*radijus2)/radijus2;
        dGdx=(rez3-rez2)/(2*dl);
        // dG/dy
        rad=sqrt((T.x-ti.x)*(T.x-ti.x)+(T.y-dl-ti.y)*(T.y-dl-ti.y)+(T.z-ti.z)*(T.z-ti.z));
        radijus2=sqrt((T.x-ti.x)*(T.x-ti.x)+(T.y-dl-ti.y)*(T.y-dl-ti.y)+(T.z+ti.z)*(T.z+ti.z));
        rez2=exp(-jot*k1*rad)/rad-rtm*exp(-jot*k1*radijus2)/radijus2;
        rad=sqrt((T.x-ti.x)*(T.x-ti.x)+(T.y+dl-ti.y)*(T.y+dl-ti.y)+(T.z-ti.z)*(T.z-ti.z));
        radijus2=sqrt((T.x-ti.x)*(T.x-ti.x)+(T.y+dl-ti.y)*(T.y+dl-ti.y)+(T.z+ti.z)*(T.z+ti.z));
        rez3=exp(-jot*k1*rad)/rad-rtm*exp(-jot*k1*radijus2)/radijus2;
        dGdy=(rez3-rez2)/(2*dl);
        // dG/dz
        rad=sqrt((T.x-ti.x)*(T.x-ti.x)+(T.y-ti.y)*(T.y-ti.y)+(T.z-dl-ti.z)*(T.z-dl-ti.z));
        radijus2=sqrt((T.x-ti.x)*(T.x-ti.x)+(T.y-ti.y)*(T.y-ti.y)+(T.z-dl+ti.z)*(T.z-dl+ti.z));
        rez2=exp(-jot*k1*rad)/rad-rtm*exp(-jot*k1*radijus2)/radijus2;
        rad=sqrt((T.x-ti.x)*(T.x-ti.x)+(T.y-ti.y)*(T.y-ti.y)+(T.z+dl-ti.z)*(T.z+dl-ti.z));
        radijus2=sqrt((T.x-ti.x)*(T.x-ti.x)+(T.y-ti.y)*(T.y-ti.y)+(T.z+dl+ti.z)*(T.z+dl+ti.z));
        rez3=exp(-jot*k1*rad)/rad-rtm*exp(-jot*k1*radijus2)/radijus2;
        dGdz=(rez3-rez2)/(2*dl);

        struja=rez1*(wire[j].struja(i+1,1)*(t2.x-ti.x)+(wire[j].struja(i+2,1)*(ti.x-t1.x)))/deltax;

 // druga Gauss tocka
        ti.x=B-dx;
        //udaljenost tocke promatranja od tocke izvora na anteni
        rad=sqrt((T.x-ti.x)*(T.x-ti.x)+(T.y-ti.y)*(T.y-ti.y)+(T.z-ti.z)*(T.z-ti.z));
        //udaljenost tocke promatranja od tocke na preslikanoj anteni
        radijus2=sqrt((T.x-ti.x)*(T.x-ti.x)+(T.y-ti.y)*(T.y-ti.y)+(T.z+ti.z)*(T.z+ti.z));
        kut=atan(sqrt((T.x-ti.x)*(T.x-ti.x)+(T.y-ti.y)*(T.y-ti.y))/(T.z+ti.z));

        gama2x=-jot*k1*sin(kut);
        gama2y=sqrt(gama2*gama2-gama2x*gama2x);
        medju=(nn[0]/nn[1])*sin(kut);
        kut1=-jot*log(jot*medju+sqrt(1-medju*medju)); //kut upada u prvom sloju
        medju=(nn[1]/nn[2])*sin(kut1);
        kut2=-jot*log(jot*medju+sqrt(1-medju*medju)); //kut upada u drugom sloju
        ro[0]=(Z[0]*cos(kut)-Z[1]*cos(kut1))/(Z[0]*cos(kut)+Z[1]*cos(kut1));
        ro[1]=(Z[1]*cos(kut1)-Z[2]*cos(kut2))/(Z[1]*cos(kut1)+Z[2]*cos(kut2));
        rtm=(ro[0]+ro[1]*exp(-2*gama2y*dub1))/(1+ro[0]*ro[1]*exp(-2*gama2y*dub1));

        rez1=exp(-jot*k1*rad)/rad-rtm*exp(-jot*k1*radijus2)/radijus2;
        // dG/dx
        rad=sqrt((T.x-dl-ti.x)*(T.x-dl-ti.x)+(T.y-ti.y)*(T.y-ti.y)+(T.z-ti.z)*(T.z-ti.z));
        radijus2=sqrt((T.x-dl-ti.x)*(T.x-dl-ti.x)+(T.y-ti.y)*(T.y-ti.y)+(T.z+ti.z)*(T.z+ti.z));
        rez2=exp(-jot*k1*rad)/rad-rtm*exp(-jot*k1*radijus2)/radijus2;
        rad=sqrt((T.x+dl-ti.x)*(T.x+dl-ti.x)+(T.y-ti.y)*(T.y-ti.y)+(T.z-ti.z)*(T.z-ti.z));
        radijus2=sqrt((T.x+dl-ti.x)*(T.x+dl-ti.x)+(T.y-ti.y)*(T.y-ti.y)+(T.z+ti.z)*(T.z+ti.z));
        rez3=exp(-jot*k1*rad)/rad-rtm*exp(-jot*k1*radijus2)/radijus2;
        dGdx+=(rez3-rez2)/(2*dl);
        // dG/dy
        rad=sqrt((T.x-ti.x)*(T.x-ti.x)+(T.y-dl-ti.y)*(T.y-dl-ti.y)+(T.z-ti.z)*(T.z-ti.z));
        radijus2=sqrt((T.x-ti.x)*(T.x-ti.x)+(T.y-dl-ti.y)*(T.y-dl-ti.y)+(T.z+ti.z)*(T.z+ti.z));
        rez2=exp(-jot*k1*rad)/rad-rtm*exp(-jot*k1*radijus2)/radijus2;
        rad=sqrt((T.x-ti.x)*(T.x-ti.x)+(T.y+dl-ti.y)*(T.y+dl-ti.y)+(T.z-ti.z)*(T.z-ti.z));
        radijus2=sqrt((T.x-ti.x)*(T.x-ti.x)+(T.y+dl-ti.y)*(T.y+dl-ti.y)+(T.z+ti.z)*(T.z+ti.z));
        rez3=exp(-jot*k1*rad)/rad-rtm*exp(-jot*k1*radijus2)/radijus2;
        dGdy+=(rez3-rez2)/(2*dl);
        // dG/dz
        rad=sqrt((T.x-ti.x)*(T.x-ti.x)+(T.y-ti.y)*(T.y-ti.y)+(T.z-dl-ti.z)*(T.z-dl-ti.z));
        radijus2=sqrt((T.x-ti.x)*(T.x-ti.x)+(T.y-ti.y)*(T.y-ti.y)+(T.z-dl+ti.z)*(T.z-dl+ti.z));
        rez2=exp(-jot*k1*rad)/rad-rtm*exp(-jot*k1*radijus2)/radijus2;
        rad=sqrt((T.x-ti.x)*(T.x-ti.x)+(T.y-ti.y)*(T.y-ti.y)+(T.z+dl-ti.z)*(T.z+dl-ti.z));
        radijus2=sqrt((T.x-ti.x)*(T.x-ti.x)+(T.y-ti.y)*(T.y-ti.y)+(T.z+dl+ti.z)*(T.z+dl+ti.z));
        rez3=exp(-jot*k1*rad)/rad-rtm*exp(-jot*k1*radijus2)/radijus2;
        dGdz+=(rez3-rez2)/(2*dl);

        struja+=rez1*(wire[j].struja(i+1,1)*(t2.x-ti.x)+(wire[j].struja(i+2,1)*(ti.x-t1.x)))/deltax;

        suma+=tezine[ii]*struja;
        sumax+=tezine[ii]*dGdx;
        sumay+=tezine[ii]*dGdy;
        sumaz+=tezine[ii]*dGdz;
    }
    polje.x+=A*(k1*k1*suma+term2*sumax);
    polje.y+=-A*term2*sumay;
    polje.z+=-A*term2*sumaz;
 }}
 term3=jot*4*PI*omega*epsef;
 polje.x/=term3;
 polje.y/=term3;
 polje.z/=term3;
 return(polje);
}
complex3Dvector elpolje1(tocka T)
{ // varijanta za idealno vodljivu zemlju
 int i,j,ii;
 double deltax,dl;
 complex<double> suma,sumax,sumay,sumaz,term2,term3;
 complex<double> dGdx,dGdy,dGdz,struja;
 double A,B,dx;
 tocka t1,t2,ti;
 complex3Dvector polje;
 static double gtocke[]={0.33998104,0.86113631};
 static double tezine[]={0.65214515,0.34785485};
 double rad,radijus2;
 complex<double> rez1,rez2,rez3,rtm;

 polje.x=complex<double>(0.,0.);
 polje.y=complex<double>(0.,0.);
 polje.z=complex<double>(0.,0.);

 rtm=1.;
 for (j=0;j<brojzica;j++){
  ti.y=wire[j].cvor[0].y;ti.z=wire[j].cvor[0].z;//integriramo po zici y i z su konst.
  for (i=0;i<wire[j].n;i++){
    t1=wire[j].cvor[i];
    t2=wire[j].cvor[i+1];
    deltax=t2.x-t1.x; dl=deltax/1.;
    term2=((wire[j].struja(i+2,1)-wire[j].struja(i+1,1))/deltax);//derivacija struje
    A=deltax/2; B=(t1.x+t2.x)/2;
    suma=complex<double>(0,0);sumax=complex<double>(0,0);
    sumay=complex<double>(0,0);sumaz=complex<double>(0,0);
    // gtocke i tezine su simetricne pa racunamo dvi po dvi
    for(ii=0;ii<2;ii++){
        dx=A*gtocke[ii];
        ti.x=B+dx;
        //udaljenost tocke promatranja od tocke izvora na anteni
        rad=sqrt((T.x-ti.x)*(T.x-ti.x)+(T.y-ti.y)*(T.y-ti.y)+(T.z-ti.z)*(T.z-ti.z));
        //udaljenost tocke promatranja od tocke na preslikanoj anteni
        radijus2=sqrt((T.x-ti.x)*(T.x-ti.x)+(T.y-ti.y)*(T.y-ti.y)+(T.z+ti.z)*(T.z+ti.z));
        rez1=exp(-jot*k1*rad)/rad-rtm*exp(-jot*k1*radijus2)/radijus2;
        // dG/dx
        rad=sqrt((T.x-dl-ti.x)*(T.x-dl-ti.x)+(T.y-ti.y)*(T.y-ti.y)+(T.z-ti.z)*(T.z-ti.z));
        radijus2=sqrt((T.x-dl-ti.x)*(T.x-dl-ti.x)+(T.y-ti.y)*(T.y-ti.y)+(T.z+ti.z)*(T.z+ti.z));
        rez2=exp(-jot*k1*rad)/rad-rtm*exp(-jot*k1*radijus2)/radijus2;
        rad=sqrt((T.x+dl-ti.x)*(T.x+dl-ti.x)+(T.y-ti.y)*(T.y-ti.y)+(T.z-ti.z)*(T.z-ti.z));
        radijus2=sqrt((T.x+dl-ti.x)*(T.x+dl-ti.x)+(T.y-ti.y)*(T.y-ti.y)+(T.z+ti.z)*(T.z+ti.z));
        rez3=exp(-jot*k1*rad)/rad-rtm*exp(-jot*k1*radijus2)/radijus2;
        dGdx=(rez3-rez2)/(2*dl);
        // dG/dy
        rad=sqrt((T.x-ti.x)*(T.x-ti.x)+(T.y-dl-ti.y)*(T.y-dl-ti.y)+(T.z-ti.z)*(T.z-ti.z));
        radijus2=sqrt((T.x-ti.x)*(T.x-ti.x)+(T.y-dl-ti.y)*(T.y-dl-ti.y)+(T.z+ti.z)*(T.z+ti.z));
        rez2=exp(-jot*k1*rad)/rad-rtm*exp(-jot*k1*radijus2)/radijus2;
        rad=sqrt((T.x-ti.x)*(T.x-ti.x)+(T.y+dl-ti.y)*(T.y+dl-ti.y)+(T.z-ti.z)*(T.z-ti.z));
        radijus2=sqrt((T.x-ti.x)*(T.x-ti.x)+(T.y+dl-ti.y)*(T.y+dl-ti.y)+(T.z+ti.z)*(T.z+ti.z));
        rez3=exp(-jot*k1*rad)/rad-rtm*exp(-jot*k1*radijus2)/radijus2;
        dGdy=(rez3-rez2)/(2*dl);
        // dG/dz
        rad=sqrt((T.x-ti.x)*(T.x-ti.x)+(T.y-ti.y)*(T.y-ti.y)+(T.z-dl-ti.z)*(T.z-dl-ti.z));
        radijus2=sqrt((T.x-ti.x)*(T.x-ti.x)+(T.y-ti.y)*(T.y-ti.y)+(T.z-dl+ti.z)*(T.z-dl+ti.z));
        rez2=exp(-jot*k1*rad)/rad-rtm*exp(-jot*k1*radijus2)/radijus2;
        rad=sqrt((T.x-ti.x)*(T.x-ti.x)+(T.y-ti.y)*(T.y-ti.y)+(T.z+dl-ti.z)*(T.z+dl-ti.z));
        radijus2=sqrt((T.x-ti.x)*(T.x-ti.x)+(T.y-ti.y)*(T.y-ti.y)+(T.z+dl+ti.z)*(T.z+dl+ti.z));
        rez3=exp(-jot*k1*rad)/rad-rtm*exp(-jot*k1*radijus2)/radijus2;
        dGdz=(rez3-rez2)/(2*dl);

        struja=rez1*(wire[j].struja(i+1,1)*(t2.x-ti.x)+(wire[j].struja(i+2,1)*(ti.x-t1.x)))/deltax;

 // druga Gauss tocka
        ti.x=B-dx;
        //udaljenost tocke promatranja od tocke izvora na anteni
        rad=sqrt((T.x-ti.x)*(T.x-ti.x)+(T.y-ti.y)*(T.y-ti.y)+(T.z-ti.z)*(T.z-ti.z));
        //udaljenost tocke promatranja od tocke na preslikanoj anteni
        radijus2=sqrt((T.x-ti.x)*(T.x-ti.x)+(T.y-ti.y)*(T.y-ti.y)+(T.z+ti.z)*(T.z+ti.z));
        rez1=exp(-jot*k1*rad)/rad-rtm*exp(-jot*k1*radijus2)/radijus2;
        // dG/dx
        rad=sqrt((T.x-dl-ti.x)*(T.x-dl-ti.x)+(T.y-ti.y)*(T.y-ti.y)+(T.z-ti.z)*(T.z-ti.z));
        radijus2=sqrt((T.x-dl-ti.x)*(T.x-dl-ti.x)+(T.y-ti.y)*(T.y-ti.y)+(T.z+ti.z)*(T.z+ti.z));
        rez2=exp(-jot*k1*rad)/rad-rtm*exp(-jot*k1*radijus2)/radijus2;
        rad=sqrt((T.x+dl-ti.x)*(T.x+dl-ti.x)+(T.y-ti.y)*(T.y-ti.y)+(T.z-ti.z)*(T.z-ti.z));
        radijus2=sqrt((T.x+dl-ti.x)*(T.x+dl-ti.x)+(T.y-ti.y)*(T.y-ti.y)+(T.z+ti.z)*(T.z+ti.z));
        rez3=exp(-jot*k1*rad)/rad-rtm*exp(-jot*k1*radijus2)/radijus2;
        dGdx+=(rez3-rez2)/(2*dl);
        // dG/dy
        rad=sqrt((T.x-ti.x)*(T.x-ti.x)+(T.y-dl-ti.y)*(T.y-dl-ti.y)+(T.z-ti.z)*(T.z-ti.z));
        radijus2=sqrt((T.x-ti.x)*(T.x-ti.x)+(T.y-dl-ti.y)*(T.y-dl-ti.y)+(T.z+ti.z)*(T.z+ti.z));
        rez2=exp(-jot*k1*rad)/rad-rtm*exp(-jot*k1*radijus2)/radijus2;
        rad=sqrt((T.x-ti.x)*(T.x-ti.x)+(T.y+dl-ti.y)*(T.y+dl-ti.y)+(T.z-ti.z)*(T.z-ti.z));
        radijus2=sqrt((T.x-ti.x)*(T.x-ti.x)+(T.y+dl-ti.y)*(T.y+dl-ti.y)+(T.z+ti.z)*(T.z+ti.z));
        rez3=exp(-jot*k1*rad)/rad-rtm*exp(-jot*k1*radijus2)/radijus2;
        dGdy+=(rez3-rez2)/(2*dl);
        // dG/dz
        rad=sqrt((T.x-ti.x)*(T.x-ti.x)+(T.y-ti.y)*(T.y-ti.y)+(T.z-dl-ti.z)*(T.z-dl-ti.z));
        radijus2=sqrt((T.x-ti.x)*(T.x-ti.x)+(T.y-ti.y)*(T.y-ti.y)+(T.z-dl+ti.z)*(T.z-dl+ti.z));
        rez2=exp(-jot*k1*rad)/rad-rtm*exp(-jot*k1*radijus2)/radijus2;
        rad=sqrt((T.x-ti.x)*(T.x-ti.x)+(T.y-ti.y)*(T.y-ti.y)+(T.z+dl-ti.z)*(T.z+dl-ti.z));
        radijus2=sqrt((T.x-ti.x)*(T.x-ti.x)+(T.y-ti.y)*(T.y-ti.y)+(T.z+dl+ti.z)*(T.z+dl+ti.z));
        rez3=exp(-jot*k1*rad)/rad-rtm*exp(-jot*k1*radijus2)/radijus2;
        dGdz+=(rez3-rez2)/(2*dl);

        struja+=rez1*(wire[j].struja(i+1,1)*(t2.x-ti.x)+(wire[j].struja(i+2,1)*(ti.x-t1.x)))/deltax;

        suma+=tezine[ii]*struja;
        sumax+=tezine[ii]*dGdx;
        sumay+=tezine[ii]*dGdy;
        sumaz+=tezine[ii]*dGdz;
    }
    polje.x+=A*(k1*k1*suma+term2*sumax);
    polje.y+=-A*term2*sumay;
    polje.z+=-A*term2*sumaz;
 }}
 term3=jot*4*PI*omega*EPS0;
 polje.x/=term3;
 polje.y/=term3;
 polje.z/=term3;
 return(polje);
}

complex3Dvector elpolje2(tocka T)
{ // varijanta za slobodni prostor
 int i,j,ii;
 double deltax,dl;
 complex<double> suma,sumax,sumay,sumaz,term2,term3;
 complex<double> dGdx,dGdy,dGdz,struja;
 double A,B,dx;
 tocka t1,t2,ti;
 complex3Dvector polje;
 static double gtocke[]={0.33998104,0.86113631};
 static double tezine[]={0.65214515,0.34785485};
 double rad;
 complex<double> rez1,rez2,rez3;

 polje.x=complex<double>(0.,0.);
 polje.y=complex<double>(0.,0.);
 polje.z=complex<double>(0.,0.);

 for (j=0;j<brojzica;j++){
  ti.y=wire[j].cvor[0].y;ti.z=wire[j].cvor[0].z;//integriramo po zici y i z su konst.
  for (i=0;i<wire[j].n;i++){
    t1=wire[j].cvor[i];
    t2=wire[j].cvor[i+1];
    deltax=t2.x-t1.x; dl=deltax/1.;
    term2=((wire[j].struja(i+2,1)-wire[j].struja(i+1,1))/deltax);//derivacija struje
    A=deltax/2; B=(t1.x+t2.x)/2;
    suma=complex<double>(0,0);sumax=complex<double>(0,0);
    sumay=complex<double>(0,0);sumaz=complex<double>(0,0);
    // gtocke i tezine su simetricne pa racunamo dvi po dvi
    for(ii=0;ii<2;ii++){
        dx=A*gtocke[ii];
        ti.x=B+dx;
        //udaljenost tocke promatranja od tocke izvora na anteni
        rad=sqrt((T.x-ti.x)*(T.x-ti.x)+(T.y-ti.y)*(T.y-ti.y)+(T.z-ti.z)*(T.z-ti.z));
        rez1=exp(-jot*k1*rad)/rad;
        // dG/dx
        rad=sqrt((T.x-dl-ti.x)*(T.x-dl-ti.x)+(T.y-ti.y)*(T.y-ti.y)+(T.z-ti.z)*(T.z-ti.z));
        rez2=exp(-jot*k1*rad)/rad;
        rad=sqrt((T.x+dl-ti.x)*(T.x+dl-ti.x)+(T.y-ti.y)*(T.y-ti.y)+(T.z-ti.z)*(T.z-ti.z));
        rez3=exp(-jot*k1*rad)/rad;
        dGdx=(rez3-rez2)/(2*dl);
        // dG/dy
        rad=sqrt((T.x-ti.x)*(T.x-ti.x)+(T.y-dl-ti.y)*(T.y-dl-ti.y)+(T.z-ti.z)*(T.z-ti.z));
        rez2=exp(-jot*k1*rad)/rad;
        rad=sqrt((T.x-ti.x)*(T.x-ti.x)+(T.y+dl-ti.y)*(T.y+dl-ti.y)+(T.z-ti.z)*(T.z-ti.z));
        rez3=exp(-jot*k1*rad)/rad;
        dGdy=(rez3-rez2)/(2*dl);
        // dG/dz
        rad=sqrt((T.x-ti.x)*(T.x-ti.x)+(T.y-ti.y)*(T.y-ti.y)+(T.z-dl-ti.z)*(T.z-dl-ti.z));
        rez2=exp(-jot*k1*rad)/rad;
        rad=sqrt((T.x-ti.x)*(T.x-ti.x)+(T.y-ti.y)*(T.y-ti.y)+(T.z+dl-ti.z)*(T.z+dl-ti.z));
        rez3=exp(-jot*k1*rad)/rad;
        dGdz=(rez3-rez2)/(2*dl);

        struja=rez1*(wire[j].struja(i+1,1)*(t2.x-ti.x)+(wire[j].struja(i+2,1)*(ti.x-t1.x)))/deltax;

 // druga Gauss tocka
        ti.x=B-dx;
        //udaljenost tocke promatranja od tocke izvora na anteni
        rad=sqrt((T.x-ti.x)*(T.x-ti.x)+(T.y-ti.y)*(T.y-ti.y)+(T.z-ti.z)*(T.z-ti.z));
        rez1=exp(-jot*k1*rad)/rad;
        // dG/dx
        rad=sqrt((T.x-dl-ti.x)*(T.x-dl-ti.x)+(T.y-ti.y)*(T.y-ti.y)+(T.z-ti.z)*(T.z-ti.z));
        rez2=exp(-jot*k1*rad)/rad;
        rad=sqrt((T.x+dl-ti.x)*(T.x+dl-ti.x)+(T.y-ti.y)*(T.y-ti.y)+(T.z-ti.z)*(T.z-ti.z));
        rez3=exp(-jot*k1*rad)/rad;
        dGdx+=(rez3-rez2)/(2*dl);
        // dG/dy
        rad=sqrt((T.x-ti.x)*(T.x-ti.x)+(T.y-dl-ti.y)*(T.y-dl-ti.y)+(T.z-ti.z)*(T.z-ti.z));
        rez2=exp(-jot*k1*rad)/rad;
        rad=sqrt((T.x-ti.x)*(T.x-ti.x)+(T.y+dl-ti.y)*(T.y+dl-ti.y)+(T.z-ti.z)*(T.z-ti.z));
        rez3=exp(-jot*k1*rad)/rad;
        dGdy+=(rez3-rez2)/(2*dl);
        // dG/dz
        rad=sqrt((T.x-ti.x)*(T.x-ti.x)+(T.y-ti.y)*(T.y-ti.y)+(T.z-dl-ti.z)*(T.z-dl-ti.z));
        rez2=exp(-jot*k1*rad)/rad;
        rad=sqrt((T.x-ti.x)*(T.x-ti.x)+(T.y-ti.y)*(T.y-ti.y)+(T.z+dl-ti.z)*(T.z+dl-ti.z));
        rez3=exp(-jot*k1*rad)/rad;
        dGdz+=(rez3-rez2)/(2*dl);

        struja+=rez1*(wire[j].struja(i+1,1)*(t2.x-ti.x)+(wire[j].struja(i+2,1)*(ti.x-t1.x)))/deltax;

        suma+=tezine[ii]*struja;
        sumax+=tezine[ii]*dGdx;
        sumay+=tezine[ii]*dGdy;
        sumaz+=tezine[ii]*dGdz;
    }
    polje.x+=A*(k1*k1*suma+term2*sumax);
    polje.y+=-A*term2*sumay;
    polje.z+=-A*term2*sumaz;
 }}
 term3=jot*4*PI*omega*EPS0;
 polje.x/=term3;
 polje.y/=term3;
 polje.z/=term3;
 return(polje);
}

double KutPolje(double xc, double yc, double rad, double phi)
{
 tocka t1;
 complex3Dvector medju;
 double polje;
 complex3Dvector (*funkcijapolja)(tocka);


 if(epsr>0) funkcijapolja=elpolje;
 if(epsr==-1) funkcijapolja=elpolje1;
 if(epsr==-2) funkcijapolja=elpolje2;

 t1.x=xc;
 t1.y=yc+rad*cos(phi*PI/180.);
 t1.z=wire[ulazna].cvor[0].z+rad*sin(phi*PI/180.);
 medju=(*funkcijapolja)(t1);
 if(CalcStoped) return 0;
 polje=sqrt(abs(medju.x)*abs(medju.x)+abs(medju.y)*abs(medju.y)+abs(medju.z)*abs(medju.z));

 return(polje);
}

int dijagramzracenja(int tip)
{
 double rad,phi,max,xmin,xmax,ymin,ymax,xc,yc;
 double phi1,phi2,phi3,phiA,phiB,dphi;
 double poljeA,poljeB;
 int i,maxphi;


 rad=0.;
 for (i=0;i<brojzica;i++) if(wire[i].L>rad) rad=wire[i].L;
 rad*=100.;
 xmin=xmax=wire[0].t1.x;ymin=ymax=wire[0].t1.y;
 for (i=0;i<brojzica;i++) {
   if(wire[i].t1.x<xmin) xmin=wire[i].t1.x;
   if(wire[i].t2.x>xmax) xmax=wire[i].t2.x;
   if(wire[i].t1.y<ymin) ymin=wire[i].t1.y;
   if(wire[i].t2.y>ymax) ymax=wire[i].t2.y;
 }
 xc=(xmin+xmax)/2; yc=(ymin+ymax)/2;//centar antenskog sustava

 // zy ravnina
 // trazimo maksimum dijagrama zracenja u prvoj latici od 3 do 5 stupnjeva
 // koristi se sukcesivna aproksimacija

 phi1=3.0; phi2=4.0; phi3=5.0;
 max=KutPolje(xc,yc,rad,phi2);
 dphi=phi2-phi1;
 //printf("\n %f    %f    %f\n",phi1,phi2,phi3);
 while(dphi>0.001){
    dphi=dphi/2.;
    phiA=phi2-dphi; phiB=phi2+dphi;
    poljeA=KutPolje(xc,yc,rad,phiA);
    poljeB=KutPolje(xc,yc,rad,phiB);
    if(poljeA>max){
        phi3=phi2; phi2=phiA;
        max=poljeA;}
    else if (poljeB>max){
        phi1=phi2; phi2=phiB;
        max=poljeB;}
    else {
        phi1=phiA; phi3=phiB;}
    //printf("\n %f    %f    %f\n",phi1,phi2,phi3);
 }
 max=floor(phi2*100);
 maxphi=(int)(floor(phi2*200-max));

return (maxphi);

}
void bliskopolje(int tip,double t1,double t2,double t3,double t4,double t5,int n1,int n2)
{
 double d1,d2;
 int i,j;
 complex3Dvector medju;
 tocka ta;
 compmat Ex(n1,n2),Ey(n1,n2),Ez(n1,n2);
 matrica Etot(n1,n2),xx(n1,1),yy(n2,1);

 if(n1>1)d1=(t2-t1)/(n1-1);
 if(n2>1)d2=(t4-t3)/(n2-1);
 // 0-xy ravnina, 1-zx ravnina, 2-zy ravnina
 switch(tip){
  case 0:
   ta.z=t5;
   for(i=0;i<n1;i++){
    ta.x=t1+i*d1;
    xx(i+1,1)=ta.x;
    for(j=0;j<n2;j++){
      ta.y=t3+j*d2;
      yy(j+1,1)=ta.y;
      medju=elpolje(ta);
      Ex(i+1,j+1)=medju.x;
      Ey(i+1,j+1)=medju.y;
      Ez(i+1,j+1)=medju.z;
    }
   }
   break;
  case 1:
   ta.y=t5;
   for(i=0;i<n1;i++){
    ta.x=t1+i*d1;
    xx(i+1,1)=ta.x;
    for(j=0;j<n2;j++){
      ta.z=t3+j*d2;
      yy(j+1,1)=ta.z;
      medju=elpolje(ta);
      Ex(i+1,j+1)=medju.x;
      Ey(i+1,j+1)=medju.y;
      Ez(i+1,j+1)=medju.z;
    }
   }
   break;
  case 2:
   ta.x=t5;
   for(i=0;i<n1;i++){
    ta.y=t1+i*d1;
    xx(i+1,1)=ta.y;
    for(j=0;j<n2;j++){
      ta.z=t3+j*d2;
      yy(j+1,1)=ta.z;
      medju=elpolje(ta);
      Ex(i+1,j+1)=medju.x;
      Ey(i+1,j+1)=medju.y;
      Ez(i+1,j+1)=medju.z;
    }
   }
   break;
 }
 for(i=1;i<=n1;i++)
  for(j=1;j<=n2;j++)
   Etot(i,j)=sqrt(abs(Ex(i,j))*abs(Ex(i,j))+abs(Ey(i,j))*abs(Ey(i,j))+abs(Ez(i,j))*abs(Ez(i,j)));

 char ime[10];
 FILE *stream;

 printf(" Naziv izlazne datoteke za raspodjelu polja: ");
 scanf("%s", ime);
// ------------------------------------------------------------------------
// +++++++++++++++  zapisivanje  rjesenja u datoteku  +++++++++++++++++++++
// ------------------------------------------------------------------------
 stream = fopen(ime, "wt");
 for(i=1;i<=n1;i++)
  for(j=1;j<=n2;j++)
   fprintf(stream,"%f %f %e %e %e %e\n",xx(i,1),yy(j,1),abs(Ex(i,j)),abs(Ey(i,j)),abs(Ez(i,j)),Etot(i,j));
  fclose(stream);
// ------------------------------------------------------------------------

}


void SetBasicData(int Buried,int BrojAntena,double FreqStart,double FreqStop,int FreqSteps, double Sigma1,
        double Epsr1, double Sigma2,double Epsr2, double PolumjerAntene,int UlaznaAntena,double sloj)
{
  jot=complex<double>(0,1);
  brojzica=BrojAntena;
  sgm1=Sigma1; epsr1=Epsr1; Einc=0.;
  sgm2=Sigma2; epsr2=Epsr2; dub1=sloj;
  a=PolumjerAntene; ulazna=UlaznaAntena;
  startf=FreqStart; stopf=FreqStop; nf=FreqSteps;
  ispod=Buried;
}
void SetAntennaData(int BrojAntene,int BrojElemenata,double Z,double Y,double X1,double X2,
                             double NaponRe, double NaponIm,double I0Re, double I0Im,double ILRe, double ILIm)
{
  complex<double> Uexc, I0, IL;
  Uexc=complex<double>(NaponRe,NaponIm);
  I0=complex<double>(I0Re,I0Im);
  IL=complex<double>(ILRe,ILIm);
  tocka ta,tb;
  ta.x=X1;ta.y=Y;ta.z=Z;
  tb.x=X2;tb.y=Y;tb.z=Z;
  wire[BrojAntene].dim(ta,tb,a,BrojElemenata,Uexc,I0,IL);
}

void FreeAll(void)
{ int i;
  rjesenja.clear();
  impedance.clear();
  for(i=0;i<brojzica;i++){
     wire[i].struja.clear();
     if(wire[i].cvor!=NULL){free(wire[i].cvor);wire[i].cvor=NULL;}
  }
}
int Calculation(void)
{
 int i,ii,j,pomak;
 double deltaf;

 //Beep(200,1000);
 CalcStoped=0;
 deltaf=0.;
 if(nf>1)deltaf=(stopf-startf)/(nf-1);
 totalnodes=0;
 for(i=0;i<brojzica;i++) totalnodes+=wire[i].n-1;
 rjesenja.dim(totalnodes+2*brojzica,nf);
 impedance.dim(nf,1);
 CurrentStep=0;
 MaxSteps=2*totalnodes+totalnodes*(totalnodes+1)/2;
 for(i=0;i<brojzica;i++)
   for(j=i+1;j<brojzica;j++)MaxSteps+=(wire[i].n-1)*(wire[j].n-1);
 MaxSteps*=nf;
 for(i=0;i<nf;i++){
   freq=startf+i*deltaf;
   impedance(i+1,1)=racunaj(ulazna);
   if(CalcStoped){FreeAll();return(0);}
   pomak=0;
   for(ii=0;ii<brojzica;ii++)
     for(j=1;j<=wire[ii].n+1;j++){
       pomak++;
       rjesenja(pomak,i+1)=wire[ii].struja(j,1);
     }
 }
 //impedance.save();
 return(totalnodes+2*brojzica);
}
void SaveCurrent(){
 char ime[10];
 FILE *stream;
 complex<double> medju;
 int i;

 printf(" Naziv izlazne datoteke za struju duz zice  : ");
 scanf("%s", ime);

// ------------------------------------------------------------------------
// +++++++++++++++  zapisivanje  rjesenja u datoteku  +++++++++++++++++++++
// ------------------------------------------------------------------------
 stream = fopen(ime, "wt");
 for(i=1;i<=totalnodes+2*brojzica;i++){
   medju=rjesenja(i,1);
   fprintf(stream,"%d %e %e %e\n",i,real(medju),imag(medju),abs(medju));
  }
  fclose(stream);
// ------------------------------------------------------------------------

}



void SetFreqStep(int BrojFreqCvora)
{ freqcvor=BrojFreqCvora;}
double GetGlobalNodeRe(int BrojCvora)
{ return(real(rjesenja(BrojCvora,freqcvor)));}
double GetGlobalNodeIm(int BrojCvora)
{ return(imag(rjesenja(BrojCvora,freqcvor)));}
double GetGlobalNodeAbs(int BrojCvora)
{ return(abs(rjesenja(BrojCvora,freqcvor)));}
double GetGlobalNodeFi(int BrojCvora)
{ return(arg(rjesenja(BrojCvora,freqcvor)));}
double GetUkupnaImpRe(void)
{ return(real(impedance(freqcvor,1)));}
double GetUkupnaImpIm(void)
{ return(imag(impedance(freqcvor,1)));}
double GetUkupnaImpAbs(void)
{ return(abs(impedance(freqcvor,1)));}
double GetUkupnaImpFi(void)
{ return(arg(impedance(freqcvor,1)));}

void SetFieldFreq(int BrojFreqCvora)
{
  //int ii,j,pomak;
  double deltaf;

  deltaf=0.;
  if(nf>1)deltaf=(stopf-startf)/(nf-1);
  freq=startf+(BrojFreqCvora-1)*deltaf;

  omega=2*PI*freq;
  eps=epsr*EPS0;
  epsef=complex<double>(eps,-sgm/omega);

  if(ispod==0){ //zica iznad zemlje
    k1=omega*sqrt(MI*EPS0);
    k2=omega*sqrt(MI*epsef);
    n_=epsef/EPS0;}
  else{  //zica u zemlji
    k2=omega*sqrt(MI*EPS0);
    k1=omega*sqrt(MI*epsef);
    n_=EPS0/epsef;}

/*  pomak=0;
  for(ii=0;ii<brojzica;ii++)
    for(j=1;j<=wire[ii].n+1;j++){
       pomak++;
       wire[ii].struja(j,1)=rjesenja(pomak,BrojFreqCvora);
    }*/
}

void SetCurrent(int indeks,double Re,double Im)
{
  int pomak,ii,j;
  pomak=0;
  for(ii=0;ii<brojzica;ii++)
    for(j=1;j<=wire[ii].n+1;j++){
       pomak++;
       if(pomak==indeks)
         {wire[ii].struja(j,1)=complex<double>(Re,Im);return;}
  }
}
void SetPlane(int Presjek)
{ CalcStoped=0;
  MaxSteps=360; CurrentStep=0;
  dijagramzracenja(Presjek);}
double GetFieldAmplitude(int Fi)
{ return(dijagram[Fi]);}
void PauseCalc(void)
{ CalcPaused=1;}
void ContinueCalc(void)
{ CalcPaused=0;}
void StopCalc(void)
{ CalcStoped=1;}

//---------------------------------------------------------------------------




//---------------------------------------------------------------------------
#pragma argsused
int main(int argc, char **argv)
{
 double s1,s2,e1,e2,d1;
 int kut;

//ulazne podatke ucitavamo iz commandline-a !!!!!!!
if (argc==6){
    s1 = atof(argv[1]);
    e1 = atof(argv[2]);
    s2 = atof(argv[3]);
    e2 = atof(argv[4]);
    d1 = atof(argv[5]);

  }
else { printf ("Proslijedite vrijednosti parametara uz poziv programa iz komandne linije:\n");
       printf ("Kut.exe s1 e1 s2 e2 d\n");
       printf (" s1 e1 - parametri snijega\n s2 e2 - parametri tla\n d - debljina snijega");
       getch();
       return 0;}





/*
void SetBasicData(int Buried,int BrojAntena,double FreqStart,double FreqStop,int FreqSteps, double Sigma1,
        double Epsr1, double Sigma2,double Epsr2, double PolumjerAntene,int UlaznaAntena,double sloj)
void SetAntennaData(int BrojAntene,int BrojElemenata,double Z,double Y,double X1,double X2,
                             double NaponRe, double NaponIm,double I0Re, double I0Im,double ILRe, double ILIm)
*/
  int rezultat;

  SetBasicData(0,32,3.28e8,3.28e8,1,s1,e1,s2,e2,0.003,1,d1);

  SetAntennaData(0,11,3.22500,0.13500,-1.05000,-0.60000,1.0,0.0,0.0,0.0,0.0,0.0);
  SetAntennaData(1,11,3.22500,0.13500,-0.50000,-0.05000,1.0,0.0,0.0,0.0,0.0,0.0);
  SetAntennaData(2,11,3.22500,0.13500,0.05000,0.50000,1.0,0.0,0.0,0.0,0.0,0.0);
  SetAntennaData(3,11,3.22500,0.13500,0.60000,1.05000,1.0,0.0,0.0,0.0,0.0,0.0);
  SetAntennaData(4,11,3.22500,-0.13500,-1.05000,-0.60000,1.0,0.0,0.0,0.0,0.0,0.0);
  SetAntennaData(5,11,3.22500,-0.13500,-0.50000,-0.05000,1.0,0.0,0.0,0.0,0.0,0.0);
  SetAntennaData(6,11,3.22500,-0.13500,0.05000,0.50000,1.0,0.0,0.0,0.0,0.0,0.0);
  SetAntennaData(7,11,3.22500,-0.13500,0.60000,1.05000,1.0,0.0,0.0,0.0,0.0,0.0);
  SetAntennaData(8,11,2.77500,0.13500,-1.05000,-0.60000,1.0,0.0,0.0,0.0,0.0,0.0);
  SetAntennaData(9,11,2.77500,0.13500,-0.50000,-0.05000,1.0,0.0,0.0,0.0,0.0,0.0);
  SetAntennaData(10,11,2.77500,0.13500,0.05000,0.50000,1.0,0.0,0.0,0.0,0.0,0.0);
  SetAntennaData(11,11,2.77500,0.13500,0.60000,1.05000,1.0,0.0,0.0,0.0,0.0,0.0);
  SetAntennaData(12,11,2.77500,-0.13500,-1.05000,-0.60000,1.0,0.0,0.0,0.0,0.0,0.0);
  SetAntennaData(13,11,2.77500,-0.13500,-0.50000,-0.05000,1.0,0.0,0.0,0.0,0.0,0.0);
  SetAntennaData(14,11,2.77500,-0.13500,0.05000,0.50000,1.0,0.0,0.0,0.0,0.0,0.0);
  SetAntennaData(15,11,2.77500,-0.13500,0.60000,1.05000,1.0,0.0,0.0,0.0,0.0,0.0);

  SetAntennaData(16,11,6.22500,0.13500,-1.05000,-0.60000,1.0,0.0,0.0,0.0,0.0,0.0);
  SetAntennaData(17,11,6.22500,0.13500,-0.50000,-0.05000,1.0,0.0,0.0,0.0,0.0,0.0);
  SetAntennaData(18,11,6.22500,0.13500,0.05000,0.50000,1.0,0.0,0.0,0.0,0.0,0.0);
  SetAntennaData(19,11,6.22500,0.13500,0.60000,1.05000,1.0,0.0,0.0,0.0,0.0,0.0);
  SetAntennaData(20,11,6.22500,-0.13500,-1.05000,-0.60000,1.0,0.0,0.0,0.0,0.0,0.0);
  SetAntennaData(21,11,6.22500,-0.13500,-0.50000,-0.05000,1.0,0.0,0.0,0.0,0.0,0.0);
  SetAntennaData(22,11,6.22500,-0.13500,0.05000,0.50000,1.0,0.0,0.0,0.0,0.0,0.0);
  SetAntennaData(23,11,6.22500,-0.13500,0.60000,1.05000,1.0,0.0,0.0,0.0,0.0,0.0);
  SetAntennaData(24,11,5.77500,0.13500,-1.05000,-0.60000,1.0,0.0,0.0,0.0,0.0,0.0);
  SetAntennaData(25,11,5.77500,0.13500,-0.50000,-0.05000,1.0,0.0,0.0,0.0,0.0,0.0);
  SetAntennaData(26,11,5.77500,0.13500,0.05000,0.50000,1.0,0.0,0.0,0.0,0.0,0.0);
  SetAntennaData(27,11,5.77500,0.13500,0.60000,1.05000,1.0,0.0,0.0,0.0,0.0,0.0);
  SetAntennaData(28,11,5.77500,-0.13500,-1.05000,-0.60000,1.0,0.0,0.0,0.0,0.0,0.0);
  SetAntennaData(29,11,5.77500,-0.13500,-0.50000,-0.05000,1.0,0.0,0.0,0.0,0.0,0.0);
  SetAntennaData(30,11,5.77500,-0.13500,0.05000,0.50000,1.0,0.0,0.0,0.0,0.0,0.0);
  SetAntennaData(31,11,5.77500,-0.13500,0.60000,1.05000,1.0,0.0,0.0,0.0,0.0,0.0);

  rezultat=Calculation();
  kut=dijagramzracenja(2);
  FreeAll();
  //printf("\nKut=%d\n\nPress any key to continue...",kut);
  //getch();

          return (kut);
}
