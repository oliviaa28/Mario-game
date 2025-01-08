

#include <fstream>
#include <winbgim.h>
#include <windows.h>
#include <string.h>
#include <iostream>
#include <conio.h>
#include <ctime>
#include <cstdlib>

using namespace std;
#define MAX 20
#define latime 45
#define SUS 72
#define JOS 80
#define STG 75
#define DRP 77
#define ESC 27
#define SPC 32
#define TAB 9
#define BKS 8

int imario, jmario, ipostaza, iInitial,jInitial;
char tasta;
string directie;
int nrstelute=0,nrstelute_total=0;
int nrLinii,nrColoane,i,j;
char harta[MAX][MAX];
char car;
int vreasasara, jumpProgress=0, jumpHeight = 7;
int nivelSelectat = 0,nivel=0;
int castigatAnterior = 0; 
int nrinamici;
int nrvieti=5;
int skinSelectat = 0; // 0 pentru Mario, 1 pentru Luigi
ifstream fisier;

int omorat=0;
int iInamic,jInamic;
clock_t miscare = clock(); // Timpul ultimei mișcări a inamicilor
const int intervalInamici = 400;   // Mișcă inamicii la fiecare 200ms

 
struct inamic
{
    int xinamic, yinamic;
    string pozitie;  //dreapta sau stanga
    int inviata;
    string directie;
} v[11]; //vector de inamici

void afiseazaInamic()
{  
    if(nivel==1)
    for(int i=0; i<nrinamici; i++)
    {   if (v[i].inviata==1)
        if(v[i].directie=="dreapta")
           readimagefile("images/nivel1/inamicD.jpg",latime*v[i].yinamic,latime*v[i].xinamic,latime*(v[i].yinamic+1),latime*(v[i].xinamic+1));
        else
           readimagefile("images/nivel1/inamicS.jpg",latime*v[i].yinamic,latime*v[i].xinamic,latime*(v[i].yinamic+1),latime*(v[i].xinamic+1));
    }
   else if(nivel==2)
   for(int i=0; i<nrinamici; i++)
    {   if (v[i].inviata==1)
        if(v[i].directie=="dreapta")
           readimagefile("images/nivel2/inamicD.jpg",latime*v[i].yinamic,latime*v[i].xinamic,latime*(v[i].yinamic+1),latime*(v[i].xinamic+1));
        else
           readimagefile("images/nivel2/inamicS.jpg",latime*v[i].yinamic,latime*v[i].xinamic,latime*(v[i].yinamic+1),latime*(v[i].xinamic+1));
    }
   else if(nivel==3)
   for(int i=0; i<nrinamici; i++)
    {   if (v[i].inviata==1)
        if(v[i].directie=="dreapta")
           readimagefile("images/nivel3/inamicD.jpg",latime*v[i].yinamic,latime*v[i].xinamic,latime*(v[i].yinamic+1),latime*(v[i].xinamic+1));
        else
           readimagefile("images/nivel3/inamicS.jpg",latime*v[i].yinamic,latime*v[i].xinamic,latime*(v[i].yinamic+1),latime*(v[i].xinamic+1));
    }
   else if(nivel==4)
   for(int i=0; i<nrinamici; i++)
    {   if (v[i].inviata==1)
        if(v[i].directie=="dreapta")
           readimagefile("images/nivel4/inamicD.jpg",latime*v[i].yinamic,latime*v[i].xinamic,latime*(v[i].yinamic+1),latime*(v[i].xinamic+1));
        else
           readimagefile("images/nivel4/inamicS.jpg",latime*v[i].yinamic,latime*v[i].xinamic,latime*(v[i].yinamic+1),latime*(v[i].xinamic+1));
    }
   else if(nivel==5)
   for(int i=0; i<nrinamici; i++)
    {   if (v[i].inviata==1)
        if(v[i].directie=="dreapta")
           readimagefile("images/nivel5/inamicD.jpg",latime*v[i].yinamic,latime*v[i].xinamic,latime*(v[i].yinamic+1),latime*(v[i].xinamic+1));
        else
           readimagefile("images/nivel5/inamicS.jpg",latime*v[i].yinamic,latime*v[i].xinamic,latime*(v[i].yinamic+1),latime*(v[i].xinamic+1));
    }
}

void stergeInamic(int x, int y,int nr)
{  if (nivel==1)
    {  readimagefile("images/nivel1/fundal.jpg",latime*y,latime*x,latime*(y+1),latime*(x+1));
      if (omorat) v[nr].inviata=0;}
    else if (nivel==2)
    {  readimagefile("images/nivel2/fundal.jpg",latime*y,latime*x,latime*(y+1),latime*(x+1));
       if (omorat) v[nr].inviata=0;
     }
    else if (nivel==3)
    {  readimagefile("images/nivel3/fundal.jpg",latime*y,latime*x,latime*(y+1),latime*(x+1));
      if (omorat) v[nr].inviata=0;}
    else if (nivel==4)
    {  readimagefile("images/nivel4/fundal.jpg",latime*y,latime*x,latime*(y+1),latime*(x+1));
     if (omorat) v[nr].inviata=0;}
    else if (nivel==5)
    {  readimagefile("images/nivel5/fundal.jpg",latime*y,latime*x,latime*(y+1),latime*(x+1));
     if (omorat) v[nr].inviata=0;}
}

void afiseazaPoza(char c, int i, int j)
{    
  if(nivel==1) 
   {     if (c=='1')
        readimagefile("images/nivel1/iarba1.jpg",latime*j,latime*i,latime*(j+1),latime*(i+1));
   else if (c=='2')
        readimagefile("images/nivel1/iarba2.jpg",latime*j,latime*i,latime*(j+1),latime*(i+1));
    else if (c=='3')
        readimagefile("images/nivel1/iarba3.jpg",latime*j,latime*i,latime*(j+1),latime*(i+1));
    else if (c=='4')
        readimagefile("images/nivel1/iarba4.jpg",latime*j,latime*i,latime*(j+1),latime*(i+1));
   else if (c=='5')
        readimagefile("images/nivel1/iarba5.jpg",latime*j,latime*i,latime*(j+1),latime*(i+1));
    else if (c=='6')
        readimagefile("images/nivel1/iarba6.jpg",latime*j,latime*i,latime*(j+1),latime*(i+1)); 
    else if (c=='I')
        readimagefile("images/nivel1/inamic.jpg",latime*j,latime*i,latime*(j+1),latime*(i+1));
    else if (c=='f')
        readimagefile("images/nivel1/floare.jpg",latime*j,latime*i,latime*(j+1),latime*(i+1));
    else if (c=='#')
        readimagefile("images/nivel1/scara.jpg",latime*j,latime*i,latime*(j+1),latime*(i+1));
    else if (c=='*')
        readimagefile("images/nivel1/stea.jpg",latime*j,latime*i,latime*(j+1),latime*(i+1));
    else if (c=='.')
        readimagefile("images/nivel1/fundal.jpg",latime*j,latime*i,latime*(j+1),latime*(i+1));
   }
   else if (nivel==2) 
     { if (c=='.')
        readimagefile("images/nivel2/fundal.jpg",latime*j,latime*i,latime*(j+1),latime*(i+1));
     else  if (c=='1')
        readimagefile("images/nivel2/iarba1.jpg",latime*j,latime*i,latime*(j+1),latime*(i+1));
     else if (c=='2')
        readimagefile("images/nivel2/iarba2.jpg",latime*j,latime*i,latime*(j+1),latime*(i+1));
     else if (c=='3')
        readimagefile("images/nivel2/iarba3.jpg",latime*j,latime*i,latime*(j+1),latime*(i+1));
     else if (c=='4')
        readimagefile("images/nivel2/iarba4.jpg",latime*j,latime*i,latime*(j+1),latime*(i+1));
     else if (c=='5')
        readimagefile("images/nivel2/iarba5.jpg",latime*j,latime*i,latime*(j+1),latime*(i+1));
     else if (c=='6')
        readimagefile("images/nivel2/iarba6.jpg",latime*j,latime*i,latime*(j+1),latime*(i+1));
     else if (c=='I')
        readimagefile("images/nivel2/inamic.jpg",latime*j,latime*i,latime*(j+1),latime*(i+1));
     else if (c=='f')
        readimagefile("images/nivel2/floare.jpg",latime*j,latime*i,latime*(j+1),latime*(i+1));
     else if (c=='#')
        readimagefile("images/nivel2/scara.jpg",latime*j,latime*i,latime*(j+1),latime*(i+1));
     else if (c=='*')
        readimagefile("images/nivel2/stea.jpg",latime*j,latime*i,latime*(j+1),latime*(i+1));
   }
   else if (nivel==3) 
     { if (c=='.')
        readimagefile("images/nivel3/fundal.jpg",latime*j,latime*i,latime*(j+1),latime*(i+1));
     else  if (c=='1')
        readimagefile("images/nivel3/iarba1.jpg",latime*j,latime*i,latime*(j+1),latime*(i+1));
     else if (c=='2')
        readimagefile("images/nivel3/iarba2.jpg",latime*j,latime*i,latime*(j+1),latime*(i+1));
     else if (c=='3')
        readimagefile("images/nivel3/iarba3.jpg",latime*j,latime*i,latime*(j+1),latime*(i+1));
     else if (c=='4')
        readimagefile("images/nivel3/iarba4.jpg",latime*j,latime*i,latime*(j+1),latime*(i+1));
     else if (c=='5')
        readimagefile("images/nivel3/iarba5.jpg",latime*j,latime*i,latime*(j+1),latime*(i+1));
     else if (c=='6')
        readimagefile("images/nivel3/iarba6.jpg",latime*j,latime*i,latime*(j+1),latime*(i+1));
     else if (c=='I')
        readimagefile("images/nivel3/inamic.jpg",latime*j,latime*i,latime*(j+1),latime*(i+1));
     else if (c=='f')
        readimagefile("images/nivel3/floare.jpg",latime*j,latime*i,latime*(j+1),latime*(i+1));
     else if (c=='#')
        readimagefile("images/nivel3/scara.jpg",latime*j,latime*i,latime*(j+1),latime*(i+1));
     else if (c=='*')
        readimagefile("images/nivel3/stea.jpg",latime*j,latime*i,latime*(j+1),latime*(i+1));
   }
   else if (nivel==4) 
     { if (c=='.')
        readimagefile("images/nivel4/fundal.jpg",latime*j,latime*i,latime*(j+1),latime*(i+1));
     else  if (c=='1')
        readimagefile("images/nivel4/iarba1.jpg",latime*j,latime*i,latime*(j+1),latime*(i+1));
     else if (c=='2')
        readimagefile("images/nivel4/iarba2.jpg",latime*j,latime*i,latime*(j+1),latime*(i+1));
     else if (c=='3')
        readimagefile("images/nivel4/iarba3.jpg",latime*j,latime*i,latime*(j+1),latime*(i+1));
     else if (c=='4')
        readimagefile("images/nivel4/iarba4.jpg",latime*j,latime*i,latime*(j+1),latime*(i+1));
     else if (c=='5')
        readimagefile("images/nivel4/iarba5.jpg",latime*j,latime*i,latime*(j+1),latime*(i+1));
     else if (c=='6')
        readimagefile("images/nivel4/iarba6.jpg",latime*j,latime*i,latime*(j+1),latime*(i+1));
    else if (c=='7')
        readimagefile("images/nivel4/iarba7.jpg",latime*j,latime*i,latime*(j+1),latime*(i+1));
    else if (c=='8')
        readimagefile("images/nivel4/iarba8.jpg",latime*j,latime*i,latime*(j+1),latime*(i+1));
    else if (c=='9')
        readimagefile("images/nivel4/iarba9.jpg",latime*j,latime*i,latime*(j+1),latime*(i+1));
     else if (c=='I')
        readimagefile("images/nivel4/inamic.jpg",latime*j,latime*i,latime*(j+1),latime*(i+1));
     else if (c=='f')
        readimagefile("images/nivel4/floare.jpg",latime*j,latime*i,latime*(j+1),latime*(i+1));
     else if (c=='#')
        readimagefile("images/nivel4/scara.jpg",latime*j,latime*i,latime*(j+1),latime*(i+1));
     else if (c=='*')
        readimagefile("images/nivel4/stea.jpg",latime*j,latime*i,latime*(j+1),latime*(i+1));
   }
   else if (nivel==5) 
     { if (c=='.')
        readimagefile("images/nivel5/fundal.jpg",latime*j,latime*i,latime*(j+1),latime*(i+1));
     else  if (c=='1')
        readimagefile("images/nivel5/iarba1.jpg",latime*j,latime*i,latime*(j+1),latime*(i+1));
     else if (c=='2')
        readimagefile("images/nivel5/iarba2.jpg",latime*j,latime*i,latime*(j+1),latime*(i+1));
     else if (c=='3')
        readimagefile("images/nivel5/iarba3.jpg",latime*j,latime*i,latime*(j+1),latime*(i+1));
     else if (c=='4')
        readimagefile("images/nivel5/iarba4.jpg",latime*j,latime*i,latime*(j+1),latime*(i+1));
     else if (c=='5')
        readimagefile("images/nivel5/iarba5.jpg",latime*j,latime*i,latime*(j+1),latime*(i+1));
     else if (c=='6')
        readimagefile("images/nivel5/iarba6.jpg",latime*j,latime*i,latime*(j+1),latime*(i+1));
       else if (c=='7')
        readimagefile("images/nivel5/iarba7.jpg",latime*j,latime*i,latime*(j+1),latime*(i+1));
     else if (c=='8')
        readimagefile("images/nivel5/iarba8.jpg",latime*j,latime*i,latime*(j+1),latime*(i+1));
     else if (c=='9')
        readimagefile("images/nivel5/iarba9.jpg",latime*j,latime*i,latime*(j+1),latime*(i+1));
     else if (c=='I')
        readimagefile("images/nivel5/inamic.jpg",latime*j,latime*i,latime*(j+1),latime*(i+1));
     else if (c=='f')
        readimagefile("images/nivel5/floare.jpg",latime*j,latime*i,latime*(j+1),latime*(i+1));
     else if (c=='#')
        readimagefile("images/nivel5/scara.jpg",latime*j,latime*i,latime*(j+1),latime*(i+1));
     else if (c=='*')
        readimagefile("images/nivel5/stea.jpg",latime*j,latime*i,latime*(j+1),latime*(i+1));
   }
}
void afiseazaInimi()
{
    int x = 10; 
    int y = 30;
 if (nivel==1)
    {if (nrvieti == 5) 
        readimagefile("images/nivel1/inimi5.jpg", x, y, x + 300, y + 50);
     else if (nrvieti == 4) 
        readimagefile("images/nivel1/inimi4.jpg", x, y, x + 300, y + 50);
     else if (nrvieti == 3) 
        readimagefile("images/nivel1/inimi3.jpg", x, y, x + 300, y + 50);
     else if (nrvieti == 2) 
        readimagefile("images/nivel1/inimi2.jpg", x, y, x + 300, y + 50);
     else if (nrvieti == 1) 
        readimagefile("images/nivel1/inimi1.jpg", x, y, x + 300, y + 50);}
 else if (nivel==2)
    {if (nrvieti == 5) 
        readimagefile("images/nivel2/inimi5.jpg", x, y, x + 300, y + 50);
     else if (nrvieti == 4) 
        readimagefile("images/nivel2/inimi4.jpg", x, y, x + 300, y + 50);
     else if (nrvieti == 3) 
        readimagefile("images/nivel2/inimi3.jpg", x, y, x + 300, y + 50);
     else if (nrvieti == 2) 
        readimagefile("images/nivel2/inimi2.jpg", x, y, x + 300, y + 50);
     else if (nrvieti == 1) 
        readimagefile("images/nivel2/inimi1.jpg", x, y, x + 300, y + 50);}
 else if (nivel==3)
    {if (nrvieti == 5) 
        readimagefile("images/nivel3/inimi5.jpg", x, y, x + 300, y + 50);
     else if (nrvieti == 4) 
        readimagefile("images/nivel3/inimi4.jpg", x, y, x + 300, y + 50);
     else if (nrvieti == 3) 
        readimagefile("images/nivel3/inimi3.jpg", x, y, x + 300, y + 50);
     else if (nrvieti == 2) 
        readimagefile("images/nivel3/inimi2.jpg", x, y, x + 300, y + 50);
     else if (nrvieti == 1) 
        readimagefile("images/nivel3/inimi1.jpg", x, y, x + 300, y + 50);}
 else if (nivel==4)
    {if (nrvieti == 5) 
        readimagefile("images/nivel4/inimi5.jpg", x, y, x + 300, y + 50);
     else if (nrvieti == 4) 
        readimagefile("images/nivel4/inimi4.jpg", x, y, x + 300, y + 50);
     else if (nrvieti == 3) 
        readimagefile("images/nivel4/inimi3.jpg", x, y, x + 300, y + 50);
     else if (nrvieti == 2) 
        readimagefile("images/nivel4/inimi2.jpg", x, y, x + 300, y + 50);
     else if (nrvieti == 1) 
        readimagefile("images/nivel4/inimi1.jpg", x, y, x + 300, y + 50);}
 else if (nivel==5)
    {if (nrvieti == 5) 
        readimagefile("images/nivel5/inimi5.jpg", x, y, x + 300, y + 50);
     else if (nrvieti == 4) 
        readimagefile("images/nivel5/inimi4.jpg", x, y, x + 300, y + 50);
     else if (nrvieti == 3) 
        readimagefile("images/nivel5/inimi3.jpg", x, y, x + 300, y + 50);
     else if (nrvieti == 2) 
        readimagefile("images/nivel5/inimi2.jpg", x, y, x + 300, y + 50);
     else if (nrvieti == 1) 
        readimagefile("images/nivel5/inimi1.jpg", x, y, x + 300, y + 50);}
}

void afiseazaMario()
{ 
 /*CAZ 1,2,3 pentru depasare dreapta
   CAZ -1,-2,-3 pentru deplasare stanga
   CAZ -10 pt deplasare in jos PE SCARA
   CAZ 10 pt deplasare in sus PE SCARA
   CAZ -11 si 111 pt sus si jos(important pt saritura)
   CAZ -12 SI 12 pt cand mario tece pe langa o scara*/
   int y=imario*latime, x=jmario*latime;
   if (skinSelectat==0){  
        if(nivel==1){
        switch(ipostaza){
        case -10: 
            readimagefile("images/nivel1/mario/mario_spate_scara1.jpg", x,y,x+latime,y+latime); break;
        case 10: 
            readimagefile("images/nivel1/mario/mario_spate_scara2.jpg", x,y,x+latime,y+latime); break;
        case -11: 
            readimagefile("images/nivel1/mario/mario_spate_1.jpg", x,y,x+latime,y+latime); break;
        case 11: 
            readimagefile("images/nivel1/mario/mario_spate_2.jpg", x,y,x+latime,y+latime); break;
        case -12: 
            readimagefile("images/nivel1/mario/mario1_scara.jpg", x,y,x+latime,y+latime); break;
        case 12: 
            readimagefile("images/nivel1/mario/mario4_scara.jpg", x,y,x+latime,y+latime); break;
        case 1:
            readimagefile("images/nivel1/mario/mario1.jpg", x,y,x+latime,y+latime); break;
        case 2:
            readimagefile("images/nivel1/mario/mario2.jpg", x,y,x+latime,y+latime); break;
        case 3:
            readimagefile("images/nivel1/mario/mario3.jpg", x,y,x+latime,y+latime); break;
        case -1:
            readimagefile("images/nivel1/mario/mario4.jpg", x,y,x+latime,y+latime); break;
        case -2:
            readimagefile("images/nivel1/mario/mario5.jpg", x,y,x+latime,y+latime); break;
        case -3:
            readimagefile("images/nivel1/mario/mario6.jpg", x,y,x+latime,y+latime); break;
    }}
   else if(nivel==2){
        switch(ipostaza){
        case -10: 
            readimagefile("images/nivel2/mario/mario_spate_scara1.jpg", x,y,x+latime,y+latime); break;
        case 10: 
            readimagefile("images/nivel2/mario/mario_spate_scara2.jpg", x,y,x+latime,y+latime); break;
        case -11: 
            readimagefile("images/nivel2/mario/mario_spate_1.jpg", x,y,x+latime,y+latime); break;
        case 11: 
            readimagefile("images/nivel2/mario/mario_spate_2.jpg", x,y,x+latime,y+latime); break;
        case -12: 
            readimagefile("images/nivel2/mario/mario1_scara.jpg", x,y,x+latime,y+latime); break;
        case 12: 
            readimagefile("images/nivel2/mario/mario4_scara.jpg", x,y,x+latime,y+latime); break;
        case 1:
            readimagefile("images/nivel2/mario/mario1.jpg", x,y,x+latime,y+latime); break;
        case 2:
            readimagefile("images/nivel2/mario/mario2.jpg", x,y,x+latime,y+latime); break;
        case 3:
            readimagefile("images/nivel2/mario/mario3.jpg", x,y,x+latime,y+latime); break;
        case -1:
            readimagefile("images/nivel2/mario/mario4.jpg", x,y,x+latime,y+latime); break;
        case -2:
            readimagefile("images/nivel2/mario/mario5.jpg", x,y,x+latime,y+latime); break;
        case -3:
            readimagefile("images/nivel2/mario/mario6.jpg", x,y,x+latime,y+latime); break;
    }}
   else if(nivel==3){
        switch(ipostaza){
        case -10: 
            readimagefile("images/nivel3/mario/mario_spate_scara1.jpg", x,y,x+latime,y+latime); break;
        case 10: 
            readimagefile("images/nivel3/mario/mario_spate_scara2.jpg", x,y,x+latime,y+latime); break;
        case -11: 
            readimagefile("images/nivel3/mario/mario_spate_1.jpg", x,y,x+latime,y+latime); break;
        case 11: 
            readimagefile("images/nivel3/mario/mario_spate_2.jpg", x,y,x+latime,y+latime); break;
        case -12: 
            readimagefile("images/nivel3/mario/mario1_scara.jpg", x,y,x+latime,y+latime); break;
        case 12: 
            readimagefile("images/nivel3/mario/mario4_scara.jpg", x,y,x+latime,y+latime); break;
        case 1:
            readimagefile("images/nivel3/mario/mario1.jpg", x,y,x+latime,y+latime); break;
        case 2:
            readimagefile("images/nivel3/mario/mario2.jpg", x,y,x+latime,y+latime); break;
        case 3:
            readimagefile("images/nivel3/mario/mario3.jpg", x,y,x+latime,y+latime); break;
        case -1:
            readimagefile("images/nivel3/mario/mario4.jpg", x,y,x+latime,y+latime); break;
        case -2:
            readimagefile("images/nivel3/mario/mario5.jpg", x,y,x+latime,y+latime); break;
        case -3:
            readimagefile("images/nivel3/mario/mario6.jpg", x,y,x+latime,y+latime); break;
    }}
   else if(nivel==4){
        switch(ipostaza){
        case -10: 
            readimagefile("images/nivel4/mario/mario_spate_scara1.jpg", x,y,x+latime,y+latime); break;
        case 10: 
            readimagefile("images/nivel4/mario/mario_spate_scara2.jpg", x,y,x+latime,y+latime); break;
        case -11: 
            readimagefile("images/nivel4/mario/mario_spate_1.jpg", x,y,x+latime,y+latime); break;
        case 11: 
            readimagefile("images/nivel4/mario/mario_spate_2.jpg", x,y,x+latime,y+latime); break;
        case -12: 
            readimagefile("images/nivel4/mario/mario1_scara.jpg", x,y,x+latime,y+latime); break;
        case 12: 
            readimagefile("images/nivel4/mario/mario4_scara.jpg", x,y,x+latime,y+latime); break;
        case 1:
            readimagefile("images/nivel4/mario/mario1.jpg", x,y,x+latime,y+latime); break;
        case 2:
            readimagefile("images/nivel4/mario/mario2.jpg", x,y,x+latime,y+latime); break;
        case 3:
            readimagefile("images/nivel4/mario/mario3.jpg", x,y,x+latime,y+latime); break;
        case -1:
            readimagefile("images/nivel4/mario/mario4.jpg", x,y,x+latime,y+latime); break;
        case -2:
            readimagefile("images/nivel4/mario/mario5.jpg", x,y,x+latime,y+latime); break;
        case -3:
            readimagefile("images/nivel4/mario/mario6.jpg", x,y,x+latime,y+latime); break;
    }}
   else if(nivel==5){
        switch(ipostaza){
        case -10: 
            readimagefile("images/nivel5/mario/mario_spate_scara1.jpg", x,y,x+latime,y+latime); break;
        case 10: 
            readimagefile("images/nivel5/mario/mario_spate_scara2.jpg", x,y,x+latime,y+latime); break;
        case -11: 
            readimagefile("images/nivel5/mario/mario_spate_1.jpg", x,y,x+latime,y+latime); break;
        case 11: 
            readimagefile("images/nivel5/mario/mario_spate_2.jpg", x,y,x+latime,y+latime); break;
        case -12: 
            readimagefile("images/nivel5/mario/mario1_scara.jpg", x,y,x+latime,y+latime); break;
        case 12: 
            readimagefile("images/nivel5/mario/mario4_scara.jpg", x,y,x+latime,y+latime); break;
        case 1:
            readimagefile("images/nivel5/mario/mario1.jpg", x,y,x+latime,y+latime); break;
        case 2:
            readimagefile("images/nivel5/mario/mario2.jpg", x,y,x+latime,y+latime); break;
        case 3:
            readimagefile("images/nivel5/mario/mario3.jpg", x,y,x+latime,y+latime); break;
        case -1:
            readimagefile("images/nivel5/mario/mario4.jpg", x,y,x+latime,y+latime); break;
        case -2:
            readimagefile("images/nivel5/mario/mario5.jpg", x,y,x+latime,y+latime); break;
        case -3:
            readimagefile("images/nivel5/mario/mario6.jpg", x,y,x+latime,y+latime); break;
    }}
    }
else if (skinSelectat==1){  
        if(nivel==1){
        switch(ipostaza){
        case -10: 
            readimagefile("images/nivel1/luigi/luigi_spate_scara1.jpg", x,y,x+latime,y+latime); break;
        case 10: 
            readimagefile("images/nivel1/luigi/luigi_spate_scara2.jpg", x,y,x+latime,y+latime); break;
        case -11: 
            readimagefile("images/nivel1/luigi/luigi_spate_1.jpg", x,y,x+latime,y+latime); break;
        case 11: 
            readimagefile("images/nivel1/luigi/luigi_spate_2.jpg", x,y,x+latime,y+latime); break;
        case -12: 
            readimagefile("images/nivel1/luigi/luigi1_scara.jpg", x,y,x+latime,y+latime); break;
        case 12: 
            readimagefile("images/nivel1/luigi/luigi4_scara.jpg", x,y,x+latime,y+latime); break;
        case 1:
            readimagefile("images/nivel1/luigi/luigi1.jpg", x,y,x+latime,y+latime); break;
        case 2:
            readimagefile("images/nivel1/luigi/luigi2.jpg", x,y,x+latime,y+latime); break;
        case 3:
            readimagefile("images/nivel1/luigi/luigi3.jpg", x,y,x+latime,y+latime); break;
        case -1:
            readimagefile("images/nivel1/luigi/luigi4.jpg", x,y,x+latime,y+latime); break;
        case -2:
            readimagefile("images/nivel1/luigi/luigi5.jpg", x,y,x+latime,y+latime); break;
        case -3:
            readimagefile("images/nivel1/luigi/luigi6.jpg", x,y,x+latime,y+latime); break;
    }}
   else if(nivel==2)
   {    switch(ipostaza){
        case -10: 
            readimagefile("images/nivel2/luigi/luigi_spate_scara1.jpg", x,y,x+latime,y+latime); break;
        case 10: 
            readimagefile("images/nivel2/luigi/luigi_spate_scara2.jpg", x,y,x+latime,y+latime); break;
        case -11: 
            readimagefile("images/nivel2/luigi/luigi_spate_1.jpg", x,y,x+latime,y+latime); break;
        case 11: 
            readimagefile("images/nivel2/luigi/luigi_spate_2.jpg", x,y,x+latime,y+latime); break;
        case -12: 
            readimagefile("images/nivel2/luigi/luigi1_scara.jpg", x,y,x+latime,y+latime); break;
        case 12: 
            readimagefile("images/nivel2/luigi/luigi4_scara.jpg", x,y,x+latime,y+latime); break;
        case 1:
            readimagefile("images/nivel2/luigi/luigi1.jpg", x,y,x+latime,y+latime); break;
        case 2:
            readimagefile("images/nivel2/luigi/luigi2.jpg", x,y,x+latime,y+latime); break;
        case 3:
            readimagefile("images/nivel2/luigi/luigi3.jpg", x,y,x+latime,y+latime); break;
        case -1:
            readimagefile("images/nivel2/luigi/luigi4.jpg", x,y,x+latime,y+latime); break;
        case -2:
            readimagefile("images/nivel2/luigi/luigi5.jpg", x,y,x+latime,y+latime); break;
        case -3:
            readimagefile("images/nivel2/luigi/luigi6.jpg", x,y,x+latime,y+latime); break;
    }}
   else if(nivel==3)
   {    switch(ipostaza){
        case -10: 
            readimagefile("images/nivel3/luigi/luigi_spate_scara1.jpg", x,y,x+latime,y+latime); break;
        case 10: 
            readimagefile("images/nivel3/luigi/luigi_spate_scara2.jpg", x,y,x+latime,y+latime); break;
        case -11: 
            readimagefile("images/nivel3/luigi/luigi_spate_1.jpg", x,y,x+latime,y+latime); break;
        case 11: 
            readimagefile("images/nivel3/luigi/luigi_spate_2.jpg", x,y,x+latime,y+latime); break;
        case -12: 
            readimagefile("images/nivel3/luigi/luigi1_scara.jpg", x,y,x+latime,y+latime); break;
        case 12: 
            readimagefile("images/nivel3/luigi/luigi4_scara.jpg", x,y,x+latime,y+latime); break;
        case 1:
            readimagefile("images/nivel3/luigi/luigi1.jpg", x,y,x+latime,y+latime); break;
        case 2:
            readimagefile("images/nivel3/luigi/luigi2.jpg", x,y,x+latime,y+latime); break;
        case 3:
            readimagefile("images/nivel3/luigi/luigi3.jpg", x,y,x+latime,y+latime); break;
        case -1:
            readimagefile("images/nivel3/luigi/luigi4.jpg", x,y,x+latime,y+latime); break;
        case -2:
            readimagefile("images/nivel3/luigi/luigi5.jpg", x,y,x+latime,y+latime); break;
        case -3:
            readimagefile("images/nivel3/luigi/luigi6.jpg", x,y,x+latime,y+latime); break;
    }}
   else if(nivel==4)
   {    switch(ipostaza){
        case -10: 
            readimagefile("images/nivel4/luigi/luigi_spate_scara1.jpg", x,y,x+latime,y+latime); break;
        case 10: 
            readimagefile("images/nivel4/luigi/luigi_spate_scara2.jpg", x,y,x+latime,y+latime); break;
        case -11: 
            readimagefile("images/nivel4/luigi/luigi_spate_1.jpg", x,y,x+latime,y+latime); break;
        case 11: 
            readimagefile("images/nivel4/luigi/luigi_spate_2.jpg", x,y,x+latime,y+latime); break;
        case -12: 
            readimagefile("images/nivel4/luigi/luigi1_scara.jpg", x,y,x+latime,y+latime); break;
        case 12: 
            readimagefile("images/nivel4/luigi/luigi4_scara.jpg", x,y,x+latime,y+latime); break;
        case 1:
            readimagefile("images/nivel4/luigi/luigi1.jpg", x,y,x+latime,y+latime); break;
        case 2:
            readimagefile("images/nivel4/luigi/luigi2.jpg", x,y,x+latime,y+latime); break;
        case 3:
            readimagefile("images/nivel4/luigi/luigi3.jpg", x,y,x+latime,y+latime); break;
        case -1:
            readimagefile("images/nivel4/luigi/luigi4.jpg", x,y,x+latime,y+latime); break;
        case -2:
            readimagefile("images/nivel4/luigi/luigi5.jpg", x,y,x+latime,y+latime); break;
        case -3:
            readimagefile("images/nivel4/luigi/luigi6.jpg", x,y,x+latime,y+latime); break;
    }}
   else if(nivel==5){
        switch(ipostaza){
        case -10: 
            readimagefile("images/nivel5/luigi/luigi_spate_scara1.jpg", x,y,x+latime,y+latime); break;
        case 10: 
            readimagefile("images/nivel5/luigi/luigi_spate_scara2.jpg", x,y,x+latime,y+latime); break;
        case -11: 
            readimagefile("images/nivel5/luigi/luigi_spate_1.jpg", x,y,x+latime,y+latime); break;
        case 11: 
            readimagefile("images/nivel5/luigi/luigi_spate_2.jpg", x,y,x+latime,y+latime); break;
        case -12: 
            readimagefile("images/nivel5/luigi/luigi1_scara.jpg", x,y,x+latime,y+latime); break;
        case 12: 
            readimagefile("images/nivel5/luigi/luigi4_scara.jpg", x,y,x+latime,y+latime); break;
        case 1:
            readimagefile("images/nivel5/luigi/luigi1.jpg", x,y,x+latime,y+latime); break;
        case 2:
            readimagefile("images/nivel5/luigi/luigi2.jpg", x,y,x+latime,y+latime); break;
        case 3:
            readimagefile("images/nivel5/luigi/luigi3.jpg", x,y,x+latime,y+latime); break;
        case -1:
            readimagefile("images/nivel5/luigi/luigi4.jpg", x,y,x+latime,y+latime); break;
        case -2:
            readimagefile("images/nivel5/luigi/luigi5.jpg", x,y,x+latime,y+latime); break;
        case -3:
            readimagefile("images/nivel5/luigi/luigi6.jpg", x,y,x+latime,y+latime); break;
    }}
   }
}

void stergeMario()
{   
    if(nivel==1){ 
      if (harta[imario][jmario] == '#')
          readimagefile("images/nivel1/scara.jpg",latime*jmario,latime*imario,latime*(jmario+1),latime*(imario+1));
      else if (harta[imario][jmario] == 'f')
          readimagefile("images/nivel1/floare.jpg",latime*jmario,latime*imario,latime*(jmario+1),latime*(imario+1));
      else
        readimagefile("images/nivel1/fundal.jpg",latime*jmario,latime*imario,latime*(jmario+1),latime*(imario+1));}
    else if(nivel==2){
      if (harta[imario][jmario] == '#')
          readimagefile("images/nivel2/scara.jpg",latime*jmario,latime*imario,latime*(jmario+1),latime*(imario+1));
      else if (harta[imario][jmario] == 'f')
          readimagefile("images/nivel2/floare.jpg",latime*jmario,latime*imario,latime*(jmario+1),latime*(imario+1));
      else
        readimagefile("images/nivel2/fundal.jpg",latime*jmario,latime*imario,latime*(jmario+1),latime*(imario+1));} 
    else if(nivel==3)
     { if (harta[imario][jmario] == '#')
          readimagefile("images/nivel3/scara.jpg",latime*jmario,latime*imario,latime*(jmario+1),latime*(imario+1));
      else if (harta[imario][jmario] == 'f')
          readimagefile("images/nivel3/floare.jpg",latime*jmario,latime*imario,latime*(jmario+1),latime*(imario+1));
      else
        readimagefile("images/nivel3/fundal.jpg",latime*jmario,latime*imario,latime*(jmario+1),latime*(imario+1));} 
    else if(nivel==4)
     { if (harta[imario][jmario] == '#')
          readimagefile("images/nivel4/scara.jpg",latime*jmario,latime*imario,latime*(jmario+1),latime*(imario+1));
      else if (harta[imario][jmario] == 'f')
          readimagefile("images/nivel4/floare.jpg",latime*jmario,latime*imario,latime*(jmario+1),latime*(imario+1));
      else
        readimagefile("images/nivel4/fundal.jpg",latime*jmario,latime*imario,latime*(jmario+1),latime*(imario+1));} 
    else if(nivel==5)
     { if (harta[imario][jmario] == '#')
          readimagefile("images/nivel5/scara.jpg",latime*jmario,latime*imario,latime*(jmario+1),latime*(imario+1));
      else if (harta[imario][jmario] == 'f')
          readimagefile("images/nivel5/floare.jpg",latime*jmario,latime*imario,latime*(jmario+1),latime*(imario+1));
      else
        readimagefile("images/nivel5/fundal.jpg",latime*jmario,latime*imario,latime*(jmario+1),latime*(imario+1));}
}

void verificaColiziune()
{ 
    for(int i=0; i<nrinamici; i++)
    {
        if(v[i].inviata==1)
        {
            // Verificăm dacă Mario este deasupra inamicului
            if (imario == v[i].xinamic && jmario == v[i].yinamic &&(vreasasara==1 || directie=="stanga_scara" ||directie=="dreapta_scara"))
            {   
                // Mario a sărit pe inamic
                omorat=1;
                harta[imario][jmario]='.';
                stergeInamic(imario, jmario, i);
                omorat=0;
                afiseazaMario();
                return; 
            }
            else if (imario == v[i].xinamic && jmario == v[i].yinamic && vreasasara == 0) 
            {
                // Mario a atins inamicul fără să sară
                stergeMario();
                imario = iInitial;
                jmario = jInitial;
                afiseazaMario();
                afiseazaInamic();
                nrvieti--; 
                afiseazaInimi();
                delay(100);
            }
        }
    }
}

void afiseazaScor()
{  int x = latime * nrColoane - 200;
    int y = 30;
    int numX = x + 120; // Poziția pentru afișarea cifrei
if(nivel==1)
   { readimagefile("images/nivel1/stars.jpg", x, y, x + 100, y + 50);
    if (nrstelute == 0) {
        readimagefile("images/nivel1/0.jpg", numX, y, numX + 30, y + 50);
    } else if (nrstelute == 1) {
        readimagefile("images/nivel1/1.jpg", numX, y, numX + 30, y + 50);
    } else if (nrstelute == 2) {
        readimagefile("images/nivel1/2.jpg", numX, y, numX + 30, y + 50);
    } else if (nrstelute == 3) {
        readimagefile("images/nivel1/3.jpg", numX, y, numX + 30, y + 50);
    } else if (nrstelute == 4) {
        readimagefile("images/nivel1/4.jpg", numX, y, numX + 30, y + 50);
    } else if (nrstelute == 5) {
        readimagefile("images/nivel1/5.jpg", numX, y, numX + 30, y + 50);
    } else if (nrstelute == 6) {
        readimagefile("images/nivel1/6.jpg", numX, y, numX + 30, y + 50);
    } else if (nrstelute == 7) {
        readimagefile("images/nivel1/7.jpg", numX, y, numX + 30, y + 50);
    } else if (nrstelute == 8) {
        readimagefile("images/nivel1/8.jpg", numX, y, numX + 30, y + 50);
    } else if (nrstelute == 9) {
        readimagefile("images/nivel1/9.jpg", numX, y, numX + 30, y + 50);
    }}
else if(nivel==2)
    { readimagefile("images/nivel2/stars.jpg", x, y, x + 100, y + 50);
    if (nrstelute == 0) {
        readimagefile("images/nivel2/0.jpg", numX, y, numX + 30, y + 50);
    } else if (nrstelute == 1) {
        readimagefile("images/nivel2/1.jpg", numX, y, numX + 30, y + 50);
    } else if (nrstelute == 2) {
        readimagefile("images/nivel2/2.jpg", numX, y, numX + 30, y + 50);
    } else if (nrstelute == 3) {
        readimagefile("images/nivel2/3.jpg", numX, y, numX + 30, y + 50);
    } else if (nrstelute == 4) {
        readimagefile("images/nivel2/4.jpg", numX, y, numX + 30, y + 50);
    } else if (nrstelute == 5) {
        readimagefile("images/nivel2/5.jpg", numX, y, numX + 30, y + 50);
    } else if (nrstelute == 6) {
        readimagefile("images/nivel2/6.jpg", numX, y, numX + 30, y + 50);
    } else if (nrstelute == 7) {
        readimagefile("images/nivel2/7.jpg", numX, y, numX + 30, y + 50);
    } else if (nrstelute == 8) {
        readimagefile("images/nivel2/8.jpg", numX, y, numX + 30, y + 50);
    } else if (nrstelute == 9) {
        readimagefile("images/nivel2/9.jpg", numX, y, numX + 30, y + 50);
    }}
else if(nivel==3)
    { readimagefile("images/nivel3/stars.jpg", x, y, x + 100, y + 50);
    if (nrstelute == 0) {
        readimagefile("images/nivel3/0.jpg", numX, y, numX + 30, y + 50);
    } else if (nrstelute == 1) {
        readimagefile("images/nivel3/1.jpg", numX, y, numX + 30, y + 50);
    } else if (nrstelute == 2) {
        readimagefile("images/nivel3/2.jpg", numX, y, numX + 30, y + 50);
    } else if (nrstelute == 3) {
        readimagefile("images/nivel3/3.jpg", numX, y, numX + 30, y + 50);
    } else if (nrstelute == 4) {
        readimagefile("images/nivel3/4.jpg", numX, y, numX + 30, y + 50);
    } else if (nrstelute == 5) {
        readimagefile("images/nivel3/5.jpg", numX, y, numX + 30, y + 50);
    } else if (nrstelute == 6) {
        readimagefile("images/nivel3/6.jpg", numX, y, numX + 30, y + 50);
    } else if (nrstelute == 7) {
        readimagefile("images/nivel3/7.jpg", numX, y, numX + 30, y + 50);
    } else if (nrstelute == 8) {
        readimagefile("images/nivel3/8.jpg", numX, y, numX + 30, y + 50);
    } else if (nrstelute == 9) {
        readimagefile("images/nivel3/9.jpg", numX, y, numX + 30, y + 50);
    }}
else if(nivel==4)
    { readimagefile("images/nivel4/stars.jpg", x, y, x + 100, y + 50);
    if (nrstelute == 0) {
        readimagefile("images/nivel4/0.jpg", numX, y, numX + 30, y + 50);
    } else if (nrstelute == 1) {
        readimagefile("images/nivel4/1.jpg", numX, y, numX + 30, y + 50);
    } else if (nrstelute == 2) {
        readimagefile("images/nivel4/2.jpg", numX, y, numX + 30, y + 50);
    } else if (nrstelute == 3) {
        readimagefile("images/nivel4/3.jpg", numX, y, numX + 30, y + 50);
    } else if (nrstelute == 4) {
        readimagefile("images/nivel4/4.jpg", numX, y, numX + 30, y + 50);
    } else if (nrstelute == 5) {
        readimagefile("images/nivel4/5.jpg", numX, y, numX + 30, y + 50);
    } else if (nrstelute == 6) {
        readimagefile("images/nivel4/6.jpg", numX, y, numX + 30, y + 50);
    } else if (nrstelute == 7) {
        readimagefile("images/nivel4/7.jpg", numX, y, numX + 30, y + 50);
    } else if (nrstelute == 8) {
        readimagefile("images/nivel4/8.jpg", numX, y, numX + 30, y + 50);
    } else if (nrstelute == 9) {
        readimagefile("images/nivel4/9.jpg", numX, y, numX + 30, y + 50);
    }}
else if(nivel==5)
    { readimagefile("images/nivel5/stars.jpg", x, y, x + 100, y + 50);
    if (nrstelute == 0) {
        readimagefile("images/nivel5/0.jpg", numX, y, numX + 30, y + 50);
    } else if (nrstelute == 1) {
        readimagefile("images/nivel5/1.jpg", numX, y, numX + 30, y + 50);
    } else if (nrstelute == 2) {
        readimagefile("images/nivel5/2.jpg", numX, y, numX + 30, y + 50);
    } else if (nrstelute == 3) {
        readimagefile("images/nivel5/3.jpg", numX, y, numX + 30, y + 50);
    } else if (nrstelute == 4) {
        readimagefile("images/nivel5/4.jpg", numX, y, numX + 30, y + 50);
    } else if (nrstelute == 5) {
        readimagefile("images/nivel5/5.jpg", numX, y, numX + 30, y + 50);
    } else if (nrstelute == 6) {
        readimagefile("images/nivel5/6.jpg", numX, y, numX + 30, y + 50);
    } else if (nrstelute == 7) {
        readimagefile("images/nivel5/7.jpg", numX, y, numX + 30, y + 50);
    } else if (nrstelute == 8) {
        readimagefile("images/nivel5/8.jpg", numX, y, numX + 30, y + 50);
    } else if (nrstelute == 9) {
        readimagefile("images/nivel5/9.jpg", numX, y, numX + 30, y + 50);
    }}
 }

void incarcaHarta()
{   nrstelute_total=0;
    nrinamici=0;
    nrvieti=5;
    fisier>>nrLinii>>nrColoane;
    initwindow(latime*nrColoane,latime*nrLinii,"Mario se distreaza pe scari");
    readimagefile("images/pleasewait.jpg",0, 0, latime*nrColoane,latime*nrLinii ); //left, top, right, bottom
    nrstelute_total=0;
    for (i=0;i<nrLinii;i++)
    {
        for (j=0;j<nrColoane;j++)
            {
                fisier>>car;
                if (car=='*') nrstelute_total++;
                else if (car=='M') {imario=i; jmario=j; iInitial=i; jInitial=j; car='.';} 
                else if(car=='I')
                {
                    v[nrinamici].inviata=1;
                    v[nrinamici].xinamic=i;
                    v[nrinamici].yinamic=j;
                    v[nrinamici].directie = "dreapta";
                    car='.'; nrinamici++;
                }
                harta[i][j]=car;
                afiseazaPoza(harta[i][j],i,j);
            }
    }
    fisier.close();  
}
//__________________________________________________________________________________________________
void urmatoareaIpostaza() 
{    
    if (directie=="dreapta")
        {
            if (abs(ipostaza)==10 || abs(ipostaza)==11||abs(ipostaza)==12) ipostaza=1;
            if (ipostaza<0) ipostaza=-ipostaza;

            ipostaza++;
            if (ipostaza==4) ipostaza=1;

            if (jmario<nrColoane-1 && harta[imario+1][jmario+1]!='.') //verificam daca mario nu iese din harta și daca se poate deplasa in dreapta (daca nu este gaura lol)
            {
                jmario++;
                if (harta[imario][jmario]=='*') // daca pe urmatoarea pozitie este o steluța
                {   
                     nrstelute++;
                     afiseazaScor();
                     harta[imario][jmario]='.'; 
                }
                if (harta[imario][jmario]=='#')
                    ipostaza=-12;
            }
        }
    else if (directie=="stanga")
        {
            if (abs(ipostaza)==10 || abs(ipostaza)==11||abs(ipostaza)==12) ipostaza=-1;
            if (ipostaza>0) ipostaza=-ipostaza;

            ipostaza--;
            if (ipostaza==-4) ipostaza=-1;
            if (jmario>0  &&  harta[imario+1][jmario-1]!='.' ) //la fel ca la dreapta.
            {
                jmario--;
                if (harta[imario][jmario]=='*') // daca pe urmatoarea pozitie este o steluța
                {    nrstelute++;
                     afiseazaScor();
                     harta[imario][jmario]='.';
                }
                 if (harta[imario][jmario]=='#')
                    ipostaza=12;
            }
        }

    if (directie=="sus")
    {    if (abs(ipostaza)==12)
             ipostaza=10;

        if (abs(ipostaza)==10 || abs(ipostaza)==11 )
            ipostaza=-ipostaza;
        else ipostaza=10;
        
        if (harta[imario-1][jmario]=='#') imario--;  //verificam daca este scara si daca poate urca
        harta[imario][jmario]='#';
    }

    if (directie=="jos")
    {
         if (abs(ipostaza)==12|| abs(ipostaza)==11 )
             ipostaza=-10;
        else   
             ipostaza=-10; 
         if(abs(ipostaza)==10)
             ipostaza=-ipostaza;   
        if (harta[imario+1][jmario]=='#') imario++; 
          
        harta[imario][jmario]='#';  
    }
    if (directie == "dreapta_scara" && harta[imario][jmario] == '#')
    {
        if (abs(ipostaza) == 10|| abs(ipostaza)==11 ||abs(ipostaza)==12) ipostaza = 1;
        if (ipostaza < 0) ipostaza = -ipostaza;
        ipostaza++;
        if (ipostaza == 4) ipostaza = 1;
          afiseazaMario();
        // Verifică dacă Mario poate ieși la dreapta de pe scară
        if (jmario < nrColoane - 1 && (harta[imario][jmario + 1] == '.' || harta[imario][jmario + 1] == '*'|| harta[imario+1][jmario]=='I'))
        {
            stergeMario();          
            jmario++;
            ipostaza=1;
            afiseazaMario(); 

            if (harta[imario][jmario] == '*')
            {
                nrstelute++; 
                afiseazaScor();
                harta[imario][jmario] = '.';  // Șterge steaua
            }
            if(harta[imario][jmario]=='I')
                verificaColiziune();

            // Verifică dacă dedesubt este gol și Mario trebuie să cadă
            if (imario < nrLinii - 1 && (harta[imario + 1][jmario] == '.' || harta[imario + 1][jmario] == '*'||harta[imario+1][jmario]=='I'))
            {
                while (imario < nrLinii - 1 &&(harta[imario + 1][jmario] == '.' || harta[imario + 1][jmario] == '*'||harta[imario+1][jmario]=='I'))
                {
                    stergeMario();   
                    imario++; // Mario cade pe verticală
                    afiseazaMario();  
                    delay(100);
                    verificaColiziune();
                    // Colectează stele în timpul căderii
                    if (harta[imario][jmario] == '*')
                    {   nrstelute++;
                        afiseazaScor();
                        harta[imario][jmario] = '.'; 
                    }
                 
                }
            }
        }
    }
     if (directie == "stanga_scara" && harta[imario][jmario] == '#')
    {
        // Schimbă ipostaza pentru animație
        if (abs(ipostaza)==10|| abs(ipostaza)==11 ||abs(ipostaza)==12) ipostaza=-1;
        if (ipostaza>0) ipostaza=-ipostaza;
        ipostaza--;
        if (ipostaza==-4) ipostaza=-1;
         afiseazaMario();
        // Verifică dacă Mario poate ieși la stanga de pe scară
        if (jmario >0 &&(harta[imario][jmario - 1] == '.' || harta[imario][jmario - 1] == '*'|| harta[imario+1][jmario]=='I'))
        {
            stergeMario();          
            jmario--;               // Mută Mario la stanga
            afiseazaMario();      

            // Dacă noua poziție conține o stea, o colectează
            if (harta[imario][jmario] == '*')
            {
                nrstelute++;
                afiseazaScor();
                harta[imario][jmario] = '.';  // Șterge steaua
            }
            if(harta[imario][jmario]=='I')
                verificaColiziune();

           
            // Verifică dacă dedesubt este gol și Mario trebuie să cadă
            if (imario < nrLinii - 1 &&(harta[imario + 1][jmario] == '.' || harta[imario + 1][jmario] == '*'|| harta[imario+1][jmario]=='I'))
            {
                while (imario < nrLinii - 1 && (harta[imario + 1][jmario] == '.' || harta[imario + 1][jmario] == '*'|| harta[imario+1][jmario]=='I'))
                {
                    stergeMario();    
                    imario++;         // Mario cade pe verticală
                    afiseazaMario();  
                    delay(100);
                    verificaColiziune();
                    if (harta[imario][jmario] == '*')
                    {
                        nrstelute++;
                        afiseazaScor();
                        harta[imario][jmario] = '.';  // Șterge steaua
                    }
                }
            }
        }
    }

}
//_________________________________________________________________________________________________
void saritura()
 {
    if (vreasasara) {
        //  deplasare laterală în timpul săriturii
        if (kbhit()) { 
            char tastaSaritura = getch();
            if (tastaSaritura == STG && jmario > 0 ){//&& harta[imario][jmario - 1] == '.') {
                stergeMario();
                jmario--; // Deplasare la stânga
            }
            if (tastaSaritura == DRP && jmario < nrColoane - 1 && harta[imario][jmario + 1] == '.') {
                stergeMario();
                jmario++; // Deplasare la dreapta
            }
        }

        if (jumpProgress < jumpHeight / 2)  //cand merge in sus
           ipostaza = 11;  
        else if (jumpProgress < jumpHeight)   // cand cade 
           ipostaza = -11;  
      afiseazaMario();
        
        // Urcare (prima jumătate a săriturii)
        if (jumpProgress < jumpHeight / 2) {
            if (imario > 0 && harta[imario - 1][jmario] == '.') {
                stergeMario();
                imario--; // Mario se ridică
                jumpProgress++;
                if(harta[imario - 1][jmario] == '*')
                {       nrstelute++;
                        afiseazaScor();
                        harta[imario-1][jmario]='.'; }
            } 
            else 
                jumpProgress = jumpHeight / 2; // Trecem la coborâre dacă întâlnim un obstacol
                afiseazaMario();
        }
        // Coborâre (a doua jumătate a săriturii)
        else if (jumpProgress < jumpHeight) 
        {
            if (imario < nrLinii - 1 && (harta[imario + 1][jmario] == '.'||harta[imario+1][jmario]=='I')) 
            {   stergeMario();
                imario++; // Mario coboară
                jumpProgress++;
                if(harta[imario - 1][jmario] == '*')
                 {  nrstelute++;
                    afiseazaScor();
                    harta[imario-1][jmario]='.';
                    }

                if(harta[imario+1][jmario]=='I')
                {        
                        stergeMario();
                        imario++;
                        jumpProgress++;
                        vreasasara=1;
                        verificaColiziune();
                }
            } else 
                jumpProgress = jumpHeight; // Finalizăm coborârea dacă întâlnim o platformă
        }
        // Finalizare săritură
        else {
            // Verificăm dacă Mario a ajuns pe o platformă 
            if (imario < nrLinii - 1 && (harta[imario + 1][jmario] == '.'|| harta[imario + 1][jmario] == '*')) 
            {
                while (imario < nrLinii - 1 && (harta[imario + 1][jmario] == '.'|| harta[imario + 1][jmario] == '*'||harta[imario+1][jmario]=='I')) 
                {
                    stergeMario();
                    imario++; // Mario continuă să cadă până ajunge pe platformă
                    if(harta[imario ][jmario] == '*'){
                         nrstelute++;
                         afiseazaScor();
                         harta[imario][jmario]='.'; }

                     if(harta[imario+1][jmario]=='I')
                     {  
                        vreasasara=1;
                         verificaColiziune();}
                         afiseazaMario();
                }
            }
            vreasasara = 0; // Săritura s-a terminat
            jumpProgress = 0;
            afiseazaMario();
            afiseazaScor(); 
            afiseazaInimi(); 
        }
        afiseazaMario(); // Redesenăm Mario după orice modificare
    }
}

void miscaInamici() 
{ int I[20];
     if(nivel==1)//inamic 4,1,3
        {I[0]=1; I[1]=4; I[2]=3;}
else if(nivel==2)//1,2,3
        {I[0]=1; I[1]=2;I[2]=3;}
else if (nivel==3)//0,3
        {I[0]=0; I[1]=3; I[2]=1;}
else if(nivel==4)//2,4
         {I[0]=2; I[1]=4; I[2]=5;}
else if(nivel==5)//24, 
        {I[0]=2; I[1]=4; I[2]=5;}

    for (int j = 0; j <=2; j++) {
         i=I[j];
        if (v[i].inviata == 1) 
        {  iInamic=v[i].xinamic;
           jInamic=v[i].yinamic;
            if (v[i].directie == "dreapta")
            {   // Verifică dacă inamicul poate merge la dreapta
                if (nivel!=4 && v[i].yinamic < nrColoane - 1 && harta[v[i].xinamic][v[i].yinamic + 1] == '.' && harta[v[i].xinamic+1][v[i].yinamic + 1] != '.') 
                    {harta[v[i].xinamic][v[i].yinamic] = '.';
                     stergeInamic(iInamic, jInamic, i);
                        v[i].yinamic++;
                        harta[v[i].xinamic][v[i].yinamic] = 'I'; 
                        afiseazaInamic(); }
                else if(nivel==4 && v[i].yinamic < nrColoane - 1 && harta[v[i].xinamic][v[i].yinamic + 1] == '.')
                    {harta[v[i].xinamic][v[i].yinamic] = '.';
                     stergeInamic(iInamic, jInamic, i);
                        v[i].yinamic++;
                        harta[v[i].xinamic][v[i].yinamic] = 'I'; 
                        afiseazaInamic(); }
                else 
                    v[i].directie = "stanga"; 
            }
             else if (v[i].directie == "stanga")
             {
                if ( nivel!=4 && v[i].yinamic > 0 && harta[v[i].xinamic][v[i].yinamic - 1] == '.'&& harta[v[i].xinamic+1][v[i].yinamic - 1] != '.' ) // Verifică dacă inamicul poate merge la stânga
                    {harta[v[i].xinamic][v[i].yinamic] = '.';
                        stergeInamic(iInamic, jInamic, i);
                        v[i].yinamic--;
                        harta[v[i].xinamic][v[i].yinamic] = 'I';
                        afiseazaInamic(); 
                    }
                else if(nivel==4 && v[i].yinamic > 0 && harta[v[i].xinamic][v[i].yinamic - 1] == '.')
                   {harta[v[i].xinamic][v[i].yinamic] = '.';
                        stergeInamic(iInamic, jInamic, i);
                        v[i].yinamic--;
                        harta[v[i].xinamic][v[i].yinamic] = 'I';
                        afiseazaInamic(); 
                    }
                    
                 else 
                    v[i].directie = "dreapta";
            }
        }
    
        afiseazaInamic();   } 
}

//__________________________________________________________________________________________________
 void pierdut()
 {
    int width = 780; 
    int height = 520;
    initwindow(width, height, "GOOD JOB MAN");
     int windowWidth = getmaxx();
    int windowHeight = getmaxy();
    int imageWidth, imageHeight;
    int x1, y1;
    imageWidth = 600; 
    imageHeight =400;
    x1 = (windowWidth - imageWidth) / 2;
    y1 = (windowHeight - imageHeight) / 2-20;
    readimagefile("images/pierdut2.jpg", x1, y1, x1 + imageWidth, y1 + imageHeight);
    int instructiuniWidth = 370; 
    int instructiuniHeight = 60;
    int instructiuniX1 = (windowWidth - instructiuniWidth) / 2;
    int instructiuniY1 = windowHeight - instructiuniHeight - 20; 
    int instructiuniX2 = instructiuniX1 + instructiuniWidth;
    int instructiuniY2 = instructiuniY1 + instructiuniHeight;
    readimagefile("images/instructiuniGoodjob.jpg", instructiuniX1, instructiuniY1, instructiuniX2, instructiuniY2);
    setcolor(YELLOW);  
    setlinestyle(SOLID_LINE, 0, 5);  
    rectangle(0, 0, windowWidth, windowHeight);
 }

 void niv()
{ 
    int width = 780; 
    int height = 520;
    initwindow(width, height, "GOOD JOB MAN");
     int windowWidth = getmaxx();
    int windowHeight = getmaxy();
    int imageWidth, imageHeight;
    int x1, y1;
    imageWidth = 600; 
    imageHeight =400;
    x1 = (windowWidth - imageWidth) / 2;
    y1 = (windowHeight - imageHeight) / 2-20;
if (nivel==1)
    readimagefile("images/bun1.jpg", x1, y1, x1 + imageWidth, y1 + imageHeight);
else if (nivel==2)
    readimagefile("images/bun2.jpg", x1, y1, x1 + imageWidth, y1 + imageHeight);
else if (nivel==3)
    readimagefile("images/bun3.jpg", x1, y1, x1 + imageWidth, y1 + imageHeight);
else if (nivel==4)
    readimagefile("images/bun4.jpg", x1, y1, x1 + imageWidth, y1 + imageHeight);
else if (nivel==5)
    readimagefile("images/bun5.jpg", x1, y1, x1 + imageWidth, y1 + imageHeight);
    int instructiuniWidth = 370; 
    int instructiuniHeight = 60;
    int instructiuniX1 = (windowWidth - instructiuniWidth) / 2;
    int instructiuniY1 = windowHeight - instructiuniHeight - 20; 
    int instructiuniX2 = instructiuniX1 + instructiuniWidth;
    int instructiuniY2 = instructiuniY1 + instructiuniHeight;
    readimagefile("images/instructiuniGoodjob.jpg", instructiuniX1, instructiuniY1, instructiuniX2, instructiuniY2);
    setcolor(YELLOW);  
    setlinestyle(SOLID_LINE, 0, 5);  
    rectangle(0, 0, windowWidth, windowHeight);
    
}
  void final()
 { int width = 780;
     int height = 520;
    initwindow(width, height, "story");
    int windowWidth = getmaxx();
    int windowHeight = getmaxy();
    int imageWidth, imageHeight;
    int x1, y1;
   
    imageWidth = 600; 
    imageHeight = 400;
    x1 = (windowWidth - imageWidth) / 2;
    y1 = (windowHeight - imageHeight) / 2;
    if (skinSelectat==0)
    readimagefile("images/final/finalm.jpg", x1, y1, x1 + imageWidth, y1 + imageHeight);
 else 
    readimagefile("images/final/finall.jpg", x1, y1, x1 + imageWidth, y1 + imageHeight);
    setcolor(YELLOW);  
    setlinestyle(SOLID_LINE, 0, 5);  
    rectangle(0, 0, windowWidth, windowHeight);
    delay(3000);
    cleardevice();

    // Imaginea 1
    imageWidth = 600; 
    imageHeight = 400;
    x1 = (windowWidth - imageWidth) / 2;
    y1 = (windowHeight - imageHeight) / 2;
    readimagefile("images/final/final1.jpg", x1, y1, x1 + imageWidth, y1 + imageHeight);
    setcolor(YELLOW);  
    setlinestyle(SOLID_LINE, 0, 5);  
    rectangle(0, 0, windowWidth, windowHeight);
    delay(4000);
    cleardevice();

    imageWidth = 500; 
    imageHeight = 400;
    x1 = (windowWidth - imageWidth) / 2;
    y1 = (windowHeight - imageHeight) / 2;
    if (skinSelectat==0)
    readimagefile("images/final/final2m.jpg", x1, y1, x1 + imageWidth, y1 + imageHeight);
 else 
    readimagefile("images/final/final2l.jpg", x1, y1, x1 + imageWidth, y1 + imageHeight);
    setcolor(YELLOW);  
    setlinestyle(SOLID_LINE, 0, 5);  
    rectangle(0, 0, windowWidth, windowHeight);
    delay(4000);
    cleardevice();

    imageWidth = 500; 
    imageHeight = 500;
    x1 = (windowWidth - imageWidth) / 2;
    y1 = (windowHeight - imageHeight) / 2;
    readimagefile("images/final/final3.jpg", x1, y1, x1 + imageWidth, y1 + imageHeight);
    setcolor(YELLOW);  
    setlinestyle(SOLID_LINE, 0, 5);  
    rectangle(0, 0, windowWidth, windowHeight);
    delay(4000);
    cleardevice();

    imageWidth = 530; 
    imageHeight = 500;
    x1 = (windowWidth - imageWidth) / 2;
    y1 = (windowHeight - imageHeight) / 2;
    readimagefile("images/final/final3s.jpg", x1, y1, x1 + imageWidth, y1 + imageHeight);
    setcolor(YELLOW);  
    setlinestyle(SOLID_LINE, 0, 5);  
    rectangle(0, 0, windowWidth, windowHeight);
    delay(4000);
    cleardevice();

    imageWidth = 500; 
    imageHeight = 450;
    x1 = (windowWidth - imageWidth) / 2;
    y1 = (windowHeight - imageHeight) / 2;
    readimagefile("images/final/final4.jpg", x1, y1, x1 + imageWidth, y1 + imageHeight);
    setcolor(YELLOW);  
    setlinestyle(SOLID_LINE, 0, 5);  
    rectangle(0, 0, windowWidth, windowHeight);
    delay(4000);
    cleardevice();

    imageWidth =600; 
    imageHeight = 500;
    x1 = (windowWidth - imageWidth) / 2;
    y1 = (windowHeight - imageHeight) / 2;
    readimagefile("images/final/final5.jpg", x1, y1, x1 + imageWidth, y1 + imageHeight);
    setcolor(YELLOW);  
    setlinestyle(SOLID_LINE, 0, 5);  
    rectangle(0, 0, windowWidth, windowHeight);
    delay(4000);
    cleardevice();

    imageWidth = 500; 
    imageHeight = 400;
    x1 = (windowWidth - imageWidth) / 2;
    y1 = (windowHeight - imageHeight) / 2;
    if (skinSelectat==0)
    readimagefile("images/final/final6m.jpg", x1, y1, x1 + imageWidth, y1 + imageHeight);
 else 
    readimagefile("images/final/final6l.jpg", x1, y1, x1 + imageWidth, y1 + imageHeight);
    setcolor(YELLOW);  
    setlinestyle(SOLID_LINE, 0, 5);  
    rectangle(0, 0, windowWidth, windowHeight);
    delay(4000);
    cleardevice();

    imageWidth = 500; 
    imageHeight = 400;
    x1 = (windowWidth - imageWidth) / 2;
    y1 = (windowHeight - imageHeight) / 2;
    if (skinSelectat==0)
    readimagefile("images/final/final7m.jpg", x1, y1, x1 + imageWidth, y1 + imageHeight);
 else 
    readimagefile("images/final/final7l.jpg", x1, y1, x1 + imageWidth, y1 + imageHeight);
    setcolor(YELLOW);  
    setlinestyle(SOLID_LINE, 0, 5);  
    rectangle(0, 0, windowWidth, windowHeight);
    delay(4000);
    cleardevice();

    imageWidth = 500; 
    imageHeight = 500;
    x1 = (windowWidth - imageWidth) / 2;
    y1 = (windowHeight - imageHeight) / 2;
    if (skinSelectat==0)
    readimagefile("images/final/final8m.jpg", x1, y1, x1 + imageWidth, y1 + imageHeight);
 else 
    readimagefile("images/final/final8l.jpg", x1, y1, x1 + imageWidth, y1 + imageHeight);
    setcolor(YELLOW);  
    setlinestyle(SOLID_LINE, 0, 5);  
    rectangle(0, 0, windowWidth, windowHeight);
    delay(4000);
    cleardevice();

//ciuperca
    imageWidth =500; 
    imageHeight = 500;
    x1 = (windowWidth - imageWidth) / 2;
    y1 = (windowHeight - imageHeight) / 2;
    readimagefile("images/final/final9.jpg", x1, y1, x1 + imageWidth, y1 + imageHeight);
    setcolor(YELLOW);  
    setlinestyle(SOLID_LINE, 0, 5);  
    rectangle(0, 0, windowWidth, windowHeight);
    delay(4000);
    cleardevice();

//meanwhile
    imageWidth = 500; 
    imageHeight = 250;
    x1 = (windowWidth - imageWidth) / 2;
    y1 = (windowHeight - imageHeight) / 2;
    if (skinSelectat==0)
    readimagefile("images/final/final10m.jpg", x1, y1, x1 + imageWidth, y1 + imageHeight);
 else 
    readimagefile("images/final/final10l.jpg", x1, y1, x1 + imageWidth, y1 + imageHeight);
    setcolor(YELLOW);  
    setlinestyle(SOLID_LINE, 0, 5);  
    rectangle(0, 0, windowWidth, windowHeight);
    delay(4000);
    cleardevice();

    imageWidth =500; 
    imageHeight = 500;
    x1 = (windowWidth - imageWidth) / 2;
    y1 = (windowHeight - imageHeight) / 2;
    readimagefile("images/final/final11.jpg", x1, y1, x1 + imageWidth, y1 + imageHeight);
    setcolor(YELLOW);  
    setlinestyle(SOLID_LINE, 0, 5);  
    rectangle(0, 0, windowWidth, windowHeight);
    delay(4000);
    cleardevice();
 
 }

//________________________________________________________________________________________________
void start()
{  int interval=0;
    incarcaHarta();
    ipostaza=1;
    nrstelute=0;
    afiseazaMario();
    afiseazaInamic();
     afiseazaScor();
     afiseazaInimi();
while (1)
{  interval++;
    if (vreasasara) 
      {      saritura();
             verificaColiziune();
             afiseazaMario();
        }
    else 
    {   
        tasta = getch();
        if (tasta == 0) tasta = getch();

        if (!vreasasara) 
        { //  doar dacă nu sare

             if (tasta == STG && jmario > 0)
                    {
                        if(harta[imario + 1][jmario - 1] != '.' && harta[imario + 1][jmario - 1] != '*')
                            directie = "stanga";
                        if(harta[imario-1][jmario]=='#'&&harta[imario+1][jmario]=='#'&&harta[imario+1][jmario+1]=='.')
                            directie="stanga_scara";
                    }
                    if (tasta == DRP && jmario < nrColoane - 1)
                    {
                        if(harta[imario + 1][jmario + 1] != '.'&& harta[imario + 1][jmario + 1] != '*')
                            directie = "dreapta";
                        if(harta[imario-1][jmario]=='#'&&harta[imario+1][jmario]=='#'&&harta[imario+1][jmario-1]=='.')
                            directie="dreapta_scara";
                    }
                    if (tasta == SUS && harta[imario - 1][jmario] == '#')
                        directie = "sus";

                    if (tasta == SPC && !vreasasara) // Declanșare săritură
                    {
                        vreasasara = 1;
                        stergeMario();
                        if(ipostaza>0)
                            jmario--;
                        if(ipostaza<0)
                            jmario++;
                    }
                    if (tasta == JOS && harta[imario + 1][jmario] == '#')
                        directie = "jos";

            if (interval%4==0) {
            miscaInamici();
            verificaColiziune();
            }
               
                }
        verificaColiziune();
        if (nrvieti==0)
        {while(tasta!=ESC && tasta!=TAB )
             {   closegraph();
                 pierdut();
                 tasta=getch(); }
         closegraph(); 
         break;
        }
        stergeMario();
        urmatoareaIpostaza();
        afiseazaMario();
    }

  delay(50); // Controlează viteza generală a jocului 
  if(tasta == ESC || nrstelute==nrstelute_total)
       break;
}       
if (nrstelute==nrstelute_total)
  { 
     while(tasta!=ESC && tasta!=TAB )
          {   closegraph();
              niv();
              tasta=getch(); }
       closegraph();  
     castigatAnterior++;
  }
    nrstelute=0;

    if(castigatAnterior==5)
       final();
closegraph();  
}

//____________________________________________________________________________________________________
void instructiuni()
{
    int width = 780;  // Lățimea ferestrei
    int height = 520;  // Înălțimea ferestrei
    initwindow(width, height, "INSTRUCTIUNI");
     int windowWidth = getmaxx();
    int windowHeight = getmaxy();

    setcolor(YELLOW);  
    setlinestyle(SOLID_LINE, 0, 5);  
    rectangle(0, 0, windowWidth, windowHeight);
    int instImageWidth = 400;  
    int instImageHeight = 80; 
    int instX1 = (windowWidth - instImageWidth) / 2;
    int instY1 = 20; 
    int instX2 =instX1 + instImageWidth;
    int instY2 = instY1 + instImageHeight;
    readimagefile("images/instructiuni.jpg", instX1, instY1, instX2, instY2);

    int image2Width = 550;  
    int image2Height = 350; 
    int image2X1 = (windowWidth - image2Width) / 2;
    int image2Y1 = instY2 + 30; 
    int image2X2 = image2X1 + image2Width;
    int image2Y2 = image2Y1 + image2Height;
    readimagefile("images/instructiuni1.jpg", image2X1, image2Y1, image2X2, image2Y2);

    tasta = getch();
    if(tasta==ESC ||tasta==TAB||tasta==ESC) 
    closegraph();
}
//_________________________________________________________________
void exit()
{
     int width = 780;  // Lățimea ferestrei
    int height = 520;  // Înălțimea ferestrei
    initwindow(width, height, "EXITT");
     int windowWidth = getmaxx();
    int windowHeight = getmaxy();

    setcolor(YELLOW);  
    setlinestyle(SOLID_LINE, 0, 5);  
    rectangle(0, 0, windowWidth, windowHeight);
     char stringData1[] = "BYE BYEEE";

    int textWidth = textwidth(stringData1);   
    int textHeight = textheight(stringData1); 
    int startY = (windowHeight - textHeight) / 2; // centrat vertical

    for (int i = 10; i < 500; i = i + 10)
    {
        setcolor(YELLOW);
        settextstyle(SANS_SERIF_FONT, 0, 8);
        outtextxy(0 + i, startY, stringData1);
        delay(80);

        setcolor(0); // 0 e negru
        outtextxy(0 + i, startY, stringData1);
    }
    closegraph();
}
//_______________________________________________________________________________________
void nivele()
{
    int width = 780;  // Lățimea ferestrei
    int height = 520;  // Înălțimea ferestrei
    initwindow(width, height, "Nivele");
    int windowWidth = getmaxx();
    int windowHeight = getmaxy();
//borderrr
    setcolor(YELLOW);  
    setlinestyle(SOLID_LINE, 0, 5);  
    rectangle(0, 0, windowWidth, windowHeight);
//menu img
    int levelWidth = 300;  
    int levelHeight = 100; 
    int levelX1 = (windowWidth - levelWidth) / 2;
    int levelY1 = 20; 
    int levelX2 = levelX1 + levelWidth;
    int levelY2 = levelY1 + levelHeight;
    readimagefile("images/levels.jpg", levelX1, levelY1, levelX2, levelY2);

int dimensiune = 140;
int spatiu = 40;
int latimeRand = 3 * dimensiune + 2 * spatiu;
int xStart1 = (windowWidth - latimeRand) / 2;
int yStart1 = levelY2 + 40;
int x[5], y[5], x2[5], y2[5];

// Nivel 1
x[0] = xStart1;
y[0] = yStart1;
x2[0] = x[0] + dimensiune;
y2[0] = y[0] + dimensiune;
readimagefile("images/niv1.jpg", x[0], y[0], x2[0], y2[0]);

// Nivel 2
x[1] = xStart1 + (dimensiune + spatiu);
y[1] = yStart1;
x2[1] = x[1] + dimensiune;
y2[1] = y[1] + dimensiune;
readimagefile("images/niv2_locked.jpg", x[1], y[1], x2[1], y2[1]);

// Nivel 3
x[2] = xStart1 + 2 * (dimensiune + spatiu);
y[2] = yStart1;
x2[2] = x[2] + dimensiune;
y2[2] = y[2] + dimensiune;
readimagefile("images/niv3_locked.jpg", x[2], y[2], x2[2], y2[2]);

int xStart2 = (windowWidth - (2 * dimensiune + spatiu)) / 2;
int yStart2 = yStart1 + dimensiune + spatiu;

// Nivel 4
x[3] = xStart2;
y[3] = yStart2;
x2[3] = x[3] + dimensiune;
y2[3] = y[3] + dimensiune;
readimagefile("images/niv4_locked.jpg", x[3], y[3], x2[3], y2[3]);

// Nivel 5
x[4] = xStart2 + (dimensiune + spatiu);
y[4] = yStart2;
x2[4] = x[4] + dimensiune;
y2[4] = y[4] + dimensiune;
readimagefile("images/niv5_locked.jpg", x[4], y[4], x2[4], y2[4]);

//colorare nivele
    if (castigatAnterior >= 1)
        readimagefile("images/niv2.jpg", x[1], y[1], x2[1], y2[1]);
    if (castigatAnterior >= 2)
        readimagefile("images/niv3.jpg", x[2], y[2], x2[2], y2[2]);
    if (castigatAnterior >= 3)
        readimagefile("images/niv4.jpg", x[3], y[3], x2[3], y2[3]);
    if (castigatAnterior >= 4)
        readimagefile("images/niv5.jpg", x[4], y[4], x2[4], y2[4]);

 setcolor(DARKGRAY); // Nivel blocat
      if (nivelSelectat == 0) // se schimba culorile la patratu in  momentul in care poti juca acel nivel
          setcolor(1);
      if (nivelSelectat == 1 && castigatAnterior >= 1)
            setcolor(YELLOW);
      if (nivelSelectat == 2 && castigatAnterior >= 2)
            setcolor(RED);
       if (nivelSelectat == 3 && castigatAnterior >= 3)
            setcolor(GREEN);
       if (nivelSelectat == 4 && castigatAnterior >= 4)
            setcolor(MAGENTA);
        rectangle(x[nivelSelectat] - 5, y[nivelSelectat] - 5, x2[nivelSelectat] + 5, y2[nivelSelectat] + 5);

    do {
        tasta = getch(); 
        if (tasta == 0) tasta = getch();
        setcolor(BLACK);
        rectangle(x[nivelSelectat] - 5, y[nivelSelectat] - 5, x2[nivelSelectat] + 5, y2[nivelSelectat] + 5);

        if( castigatAnterior>=1)
           readimagefile("images/niv2.jpg", x[1], y[1], x2[1], y2[1]);
        if( castigatAnterior>=2)  
           readimagefile("images/niv3.jpg", x[2], y[2], x2[2], y2[2]); 
        if( castigatAnterior>=3)
           readimagefile("images/niv4.jpg", x[3], y[3], x2[3], y2[3]);
        if( castigatAnterior>=4)
           readimagefile("images/niv5.jpg", x[4], y[4], x2[4], y2[4]);
           
        // Setarea culorii pentru nivele

        if (tasta == DRP) { 
            nivelSelectat = (nivelSelectat + 1) % 5; //coordonatele
        } else if (tasta == STG) { 
            nivelSelectat = (nivelSelectat - 1 + 5) % 5;
        } else if (tasta == SPC || tasta == TAB) { // TAB sau SPACE
            if (nivelSelectat <= castigatAnterior) 
            { // Nivel deblocat
               if (nivelSelectat == 0)   
                 {  nivel=1;
                    fisier.open("harti/harta1.txt");}
                else if (nivelSelectat == 1 && castigatAnterior>=1)
                 {  nivel=2;
                    fisier.open("harti/harta2.txt");}
                else if (nivelSelectat == 2 && castigatAnterior>=2)
                 {  nivel=3;
                    fisier.open("harti/harta3.txt");}
                else if (nivelSelectat == 3 && castigatAnterior>=3)
                 {  nivel=4;
                    fisier.open("harti/harta4.txt");}
                else if (nivelSelectat == 4 && castigatAnterior>=4)
                 {  nivel=5;
                    fisier.open("harti/harta5.txt");}

                if (fisier.is_open()) {
                    start();
                    fisier.close();
                    nivele();} 
                    closegraph();
                    nivele();
            }
        }
      setcolor(DARKGRAY); // Nivel blocat
      if (nivelSelectat == 0)
          setcolor(1);
      if (nivelSelectat == 1 && castigatAnterior >= 1)
            setcolor(YELLOW);
      if (nivelSelectat == 2 && castigatAnterior >= 2)
            setcolor(RED);
       if (nivelSelectat == 3 && castigatAnterior >= 3)
            setcolor(GREEN);
       if (nivelSelectat == 4 && castigatAnterior >= 4)
            setcolor(MAGENTA);
        rectangle(x[nivelSelectat] - 5, y[nivelSelectat] - 5, x2[nivelSelectat] + 5, y2[nivelSelectat] + 5);
    } while (tasta != ESC); // ESC pentru ieșire  
}

void  alegeSkin()
{
    int width = 780;  // Lățimea ferestrei
    int height = 520;  // Înălțimea ferestrei
    initwindow(width, height, "Nivele");
    int windowWidth = getmaxx();
    int windowHeight = getmaxy();

 //borderrr
    int skinImageWidth = 700;  
    int skinImageHeight = 90; 
    int skinX1 = (windowWidth - skinImageWidth) / 2;
    int skinY1 = 20; 
    int skinX2 =skinX1 + skinImageWidth;
    int skinY2 = skinY1 + skinImageHeight;
    readimagefile("images/alege.jpg", skinX1, skinY1, skinX2, skinY2);

    int latimeSkin = 200; 
    int inaltimeSkin = 200; 
    int spatiuIntreSkinuri = 60; // Spațiu între imagini
    
    int marioX = (windowWidth / 2) - latimeSkin - spatiuIntreSkinuri;
    int marioY = skinY2 + 30;
    int marioX2 = marioX + latimeSkin;
    int marioY2 = marioY + inaltimeSkin;
    
    int luigiX = (windowWidth / 2) + spatiuIntreSkinuri;
    int luigiY = marioY;
    int luigiX2 = luigiX + latimeSkin;
    int luigiY2 = marioY2;
    readimagefile("images/marioSkin.jpg", marioX, marioY, marioX2, marioY2);
    readimagefile("images/luigiSkin.jpg", luigiX, luigiY, luigiX2, luigiY2);

    int inaltimeNume = 70; // Înălțimea imaginilor cu numele
    int marioNumeY1 = marioY2 + 10;
    int marioNumeY2 = marioNumeY1 + inaltimeNume;
    int luigiNumeY1 = luigiY2 + 10;
    int luigiNumeY2 = luigiNumeY1 + inaltimeNume;

    readimagefile("images/mario_unlocked.jpg", marioX, marioNumeY1, marioX2, marioNumeY2);
    readimagefile("images/luigi_locked.jpg", luigiX, luigiNumeY1, luigiX2, luigiNumeY2);
    //intrsuctiuni
    readimagefile("images/instructiuniSkin.jpg", 0,windowHeight-100,windowWidth, windowHeight);
    setcolor(YELLOW);  
    setlinestyle(SOLID_LINE, 0, 5);  
    rectangle(0, 0, windowWidth, windowHeight);

do {
        tasta = getch();
        if (tasta == 0) tasta = getch(); // Pentru taste speciale

        if (tasta == STG) { 
            skinSelectat = 0; //mario
        } else if (tasta == DRP ) { 
            skinSelectat = 1; //luigi
        }
        if (skinSelectat == 0) {
              readimagefile("images/mario_unlocked.jpg", marioX, marioNumeY1, marioX2, marioNumeY2);
              readimagefile("images/luigi_locked.jpg", luigiX,luigiNumeY1, luigiX2, luigiNumeY2);
              tasta = getch();
              if (tasta == SPC || tasta == TAB)  
                  break;}
         else {
              readimagefile("images/mario_locked.jpg", marioX, marioNumeY1, marioX2, marioNumeY2);
              readimagefile("images/luigi_unlocked.jpg", luigiX, luigiNumeY1, luigiX2,luigiNumeY2);
              tasta = getch();
              if (tasta == SPC || tasta == TAB)  
                  break;}
    } while (tasta != ESC && tasta!=TAB);
closegraph();
}

//____________________________________________________________________________________________________
  void meniu()
 { 
   int width = 780;  // Lățimea ferestrei
    int height = 520;  // Înălțimea ferestrei
    initwindow(width, height, "Meniu joc");
    int windowWidth = getmaxx();
    int windowHeight = getmaxy();
//borderrr
    setcolor(YELLOW);  
    setlinestyle(SOLID_LINE, 0, 5);  
    rectangle(0, 0, windowWidth, windowHeight);
//menu img
    int menuImageWidth = 300;  
    int menuImageHeight = 120; 
    int menuX1 = (windowWidth - menuImageWidth) / 2;
    int menuY1 = 20; 
    int menuX2 = menuX1 + menuImageWidth;
    int menuY2 = menuY1 + menuImageHeight;
    readimagefile("images/meniu.jpg", menuX1, menuY1, menuX2, menuY2);
//start 
    int startWidth = 200;  
    int startHeight = 70; 
    int startX1 = (windowWidth - startWidth) / 2;
    int startY1 = menuY2 + 60; 
    int startX2 = startX1 + startWidth;
    int startY2 = startY1 + startHeight;
    readimagefile("images/start.jpg", startX1, startY1, startX2, startY2);
//instructions 
    int instrWidth = 300;  
    int instrHeight = 50;  
    int instrX1 = (windowWidth - instrWidth) / 2;
    int instrY1 = startY2 + 25; 
    int instrX2 = instrX1 + instrWidth;
    int instrY2 = instrY1 + instrHeight;
   readimagefile("images/instructiuni.jpg", instrX1, instrY1, instrX2, instrY2);
//exit 
    int exitWidth = 200;  
    int exitHeight = 60; 
    int exitX1 = (windowWidth - exitWidth) / 2;
    int exitY1 = startY2 + 100; 
    int exitX2 = exitX1 + exitWidth;
    int exitY2 = exitY1 + exitHeight;
    readimagefile("images/exit.jpg", exitX1, exitY1, exitX2, exitY2);
 //skins
  int skinWidth = 200, skinHeight = 110;
    int skinX1 = windowWidth - skinWidth - 20; // Așezat în dreapta jos
    int skinY1 = windowHeight - skinHeight - 20;
    int skinX2 = skinX1 + skinWidth;
    int skinY2 = skinY1 + skinHeight;
    readimagefile("images/skin.jpg", skinX1, skinY1, skinX2, skinY2);
//sageata    
    int arrowWidth = 50; 
    int arrowHeight = 50; 
    int arrowX = startX1 - arrowWidth;  // pozitia initiala a sagetii 
    int arrowY = startY1 + (startHeight / 2) - (arrowHeight / 2); 
    readimagefile("images/sageata.jpg", arrowX, arrowY, arrowX + arrowWidth, arrowY + arrowHeight);
    int arrowPosition = 0;
    // 0 -> Start, 1 -> Instructions, 2 -> Exit

// start--ca sa nu fie delay(pt ca sageata e prima obtiune)
    if (arrowPosition==0)
        {  tasta = getch();  
            if (tasta==TAB || tasta==SPC)
                   {   nivele();
                       closegraph();
                        meniu();  }
         } 
    do {
        tasta = getch();
        if (tasta == 0) tasta = getch(); 
        readimagefile("images/negru.jpg", arrowX, arrowY, arrowX + arrowWidth, arrowY + arrowHeight); //pt as terge sageata cand ne deplasam
       
        if (tasta == JOS) {
            if (arrowPosition < 3) {  //mutam doar daca nu este la "Exit"
                arrowPosition++;  
            }
        }
        if (tasta == SUS) {
            if (arrowPosition > 0) {  // mutam doar daca nu este la "Start"
                arrowPosition--; 
            }
        }
           
        switch (arrowPosition) {
            case 0: // Start
                {   arrowX=startX1 - arrowWidth;
                    arrowY = startY1 + (startHeight / 2) - (arrowHeight / 2);}
                break;
            case 1: // Instructions
                {   arrowX=instrX1 - arrowWidth;
                    arrowY = instrY1 + (instrHeight / 2) - (arrowHeight / 2);}
                break;
            case 2: // Exit
                {   arrowX=exitX1 - arrowWidth;
                    arrowY = exitY1 + (exitHeight / 2) - (arrowHeight / 2);                                          
                }
                break;
            case 3: 
            {
            arrowX = skinX1 - arrowWidth;
            arrowY = skinY1 + (skinHeight / 2) - (arrowHeight / 2);
            }
            break;
        }
        readimagefile("images/sageata.jpg", arrowX, arrowY, arrowX + arrowWidth, arrowY + arrowHeight);

//start(again)
          if (arrowPosition==0)
        {  tasta = getch();  
            if (tasta==TAB || tasta==SPC)
                   {   nivele();
                       closegraph();
                        meniu(); }
         } 
         else
//instructiuni             
             if (arrowPosition==1)
        {  tasta = getch();  
                    if (tasta==TAB || tasta==SPC)
                       {    instructiuni();
                            meniu();}            
                            
        }
         else
//exit  
        if (arrowPosition==2)
        {  tasta = getch();  
           if (tasta==TAB || tasta==SPC)
                exit();     
         }   

        if (arrowPosition == 3 ) {
          tasta = getch();  
           if (tasta==TAB || tasta==SPC)
               { alegeSkin(); 
                 closegraph();   
                 meniu(); 
               }
           
        }        
    } while (tasta != ESC);  
 }
  void poveste()
 {
    int width = 780;
    int height = 520;

    // Inițializarea ferestrei grafice
    initwindow(width, height, "story");
    int windowWidth = getmaxx();
    int windowHeight = getmaxy();

    setcolor(YELLOW);  
    setlinestyle(SOLID_LINE, 0, 5);  
    rectangle(0, 0, windowWidth, windowHeight);
    int imageWidth, imageHeight;
    int x1, y1;

    // Imaginea 1
    imageWidth = 492; 
    imageHeight = 412;
    x1 = (windowWidth - imageWidth) / 2;
    y1 = (windowHeight - imageHeight) / 2;
    readimagefile("images/poveste/poveste1.jpg", x1, y1, x1 + imageWidth, y1 + imageHeight);
    delay(3000);
    cleardevice();

    setcolor(YELLOW);  
    setlinestyle(SOLID_LINE, 0, 5);  
    rectangle(0, 0, windowWidth, windowHeight);

    // Imaginea 2
    imageWidth = 427; 
    imageHeight = 405;
    x1 = (windowWidth - imageWidth) / 2;
    y1 = (windowHeight - imageHeight) / 2;
    readimagefile("images/poveste/poveste2.jpg", x1, y1, x1 + imageWidth, y1 + imageHeight);
    delay(5000);
    cleardevice();

    setcolor(YELLOW);  
    setlinestyle(SOLID_LINE, 0, 5);
    rectangle(0, 0, windowWidth, windowHeight);  

    // Imaginea 3
    imageWidth = 500; 
    imageHeight = 400;
    x1 = (windowWidth - imageWidth) / 2;
    y1 = (windowHeight - imageHeight) / 2;
    readimagefile("images/poveste/poveste3.jpg", x1, y1, x1 + imageWidth, y1 + imageHeight);
    delay(4000);
    cleardevice();

    setcolor(YELLOW);  
    setlinestyle(SOLID_LINE, 0, 5);  
    rectangle(0, 0, windowWidth, windowHeight);

    // Imaginea 4
    imageWidth = 500; 
    imageHeight = 350;
    x1 = (windowWidth - imageWidth) / 2;
    y1 = (windowHeight - imageHeight) / 2;
    readimagefile("images/poveste/poveste4.jpg", x1, y1, x1 + imageWidth, y1 + imageHeight);
    delay(5000);
    cleardevice();

    setcolor(YELLOW);  
    setlinestyle(SOLID_LINE, 0, 5);  
    rectangle(0, 0, windowWidth, windowHeight);

    // Imaginea 5
    imageWidth = 550; 
    imageHeight = 450;
    x1 = (windowWidth - imageWidth) / 2;
    y1 = (windowHeight - imageHeight) / 2;
    readimagefile("images/poveste/poveste5.jpg", x1, y1, x1 + imageWidth, y1 + imageHeight);
    delay(5000);
    cleardevice();  

    setcolor(YELLOW);  
    setlinestyle(SOLID_LINE, 0, 5);  
    rectangle(0, 0, windowWidth, windowHeight);

    // Imaginea 6
    imageWidth = 550; 
    imageHeight = 400;
    x1 = (windowWidth - imageWidth) / 2;
    y1 = (windowHeight - imageHeight) / 2;
    readimagefile("images/poveste/poveste6.jpg", x1, y1, x1 + imageWidth, y1 + imageHeight);
    delay(5000);
    cleardevice();

    setcolor(YELLOW);  
    setlinestyle(SOLID_LINE, 0, 5);  
    rectangle(0, 0, windowWidth, windowHeight);
    // Imaginea 7
    imageWidth = 560; 
    imageHeight = 400;
    x1 = (windowWidth - imageWidth) / 2-80;
    y1 = (windowHeight - imageHeight) / 2+54;
    readimagefile("images/poveste/poveste7.jpg", x1, y1, x1 + imageWidth, y1 + imageHeight);
    delay(8000);
    cleardevice();

    setcolor(YELLOW);  
    setlinestyle(SOLID_LINE, 0, 5);  
    rectangle(0, 0, windowWidth, windowHeight);

    // Imaginea 8
    imageWidth = 570; 
    imageHeight = 400;
    x1 = (windowWidth - imageWidth) / 2;
    y1 = (windowHeight - imageHeight) / 2;
    readimagefile("images/poveste/poveste8.jpg", x1, y1, x1 + imageWidth, y1 + imageHeight);
    delay(5000);
    cleardevice();

    setcolor(YELLOW);  
    setlinestyle(SOLID_LINE, 0, 5);  
    rectangle(0, 0, windowWidth, windowHeight);

    // Imaginea 9
    imageWidth = 590; 
    imageHeight =400;
    x1 = (windowWidth - imageWidth) / 2;
    y1 = (windowHeight - imageHeight) / 2;
    readimagefile("images/poveste/poveste9.jpg", x1, y1, x1 + imageWidth, y1 + imageHeight);
    delay(5000);
    cleardevice();
    setcolor(YELLOW);  
    setlinestyle(SOLID_LINE, 0, 5);  
    rectangle(0, 0, windowWidth, windowHeight);
    // Imaginea 10
    imageWidth = 550; 
    imageHeight = 450;
    x1 = (windowWidth - imageWidth) / 2;
    y1 = (windowHeight - imageHeight) / 2;
    readimagefile("images/poveste/poveste10.jpg", x1, y1, x1 + imageWidth, y1 + imageHeight);
    delay(8000);
    cleardevice(); 


    setcolor(YELLOW);  
    setlinestyle(SOLID_LINE, 0, 5);  
    rectangle(0, 0, windowWidth, windowHeight);
    // Imaginea 11
    imageWidth =550; 
    imageHeight = 450;
    x1 = (windowWidth - imageWidth) / 2;
    y1 = (windowHeight - imageHeight) / 2;
    readimagefile("images/poveste/poveste11.jpg", x1, y1, x1 + imageWidth, y1 + imageHeight);
    delay(8000);
    cleardevice(); 

    setcolor(YELLOW);  
    setlinestyle(SOLID_LINE, 0, 5);  
    rectangle(0, 0, windowWidth, windowHeight);
    // Imaginea 12
    imageWidth = 670; 
    imageHeight =450;
    x1 = (windowWidth - imageWidth) / 2;
    y1 = (windowHeight - imageHeight) / 2;
    readimagefile("images/poveste/poveste12.jpg", x1, y1, x1 + imageWidth, y1 + imageHeight);
    delay(5000);
    cleardevice();

    setcolor(YELLOW);  
    setlinestyle(SOLID_LINE, 0, 5);  
    rectangle(0, 0, windowWidth, windowHeight);
    // Imaginea 13
    imageWidth = 410; 
    imageHeight = 285;
    x1 = (windowWidth - imageWidth) / 2;
    y1 = (windowHeight - imageHeight) / 2;
    readimagefile("images/poveste/poveste13.jpg", x1, y1, x1 + imageWidth, y1 + imageHeight);
    delay(4000);
    cleardevice();
    closegraph();
 }

 void loading()
 {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);
    int windowWidth = getmaxx();
    int windowHeight = getmaxy();
    setcolor(YELLOW);  
    setlinestyle(SOLID_LINE, 0, 5);  // Line style (SOLID), pattern (0), thickness (3)
    rectangle(0, 0, windowWidth, windowHeight);

    int mariolatime = 400;
    int marioinaltime = 300;
    int x1 = (getmaxx() - mariolatime) / 2;
    int y1 = (getmaxy() - marioinaltime) / 2;
    int x2 = x1 + mariolatime;
    int y2 = y1 + marioinaltime;
    readimagefile("images/meniu.mario.jpg", x1, y1, x2, y2);

    int stealatime = 150;
    int steainaltime = 150;
    int X1 = min(x2 + 10, getmaxx() - stealatime - 10);  //nu depaseste bordura ferestrei
    int Y1 = max(y1 - steainaltime - 10, 10);            //la fel si aici
    int X2 = X1 + stealatime;
    int Y2 = Y1 + steainaltime;
    readimagefile("images/stea.meniu.jpg", X1, Y1, X2, Y2);   

    for (i = 10; i < 650; i = i + 10)
    {
        setcolor(YELLOW);
        settextstyle(SANS_SERIF_FONT, 0, 8);
        char stringData1[] = "MARIO GAME";
        outtextxy(0 + i, 390, stringData1);
        delay(80);
        setcolor(0);
        settextstyle(SANS_SERIF_FONT, 0, 8);
        outtextxy(0 + i, 390, stringData1);
        
    }
closegraph();
}

//______________________________________________________________________________________________________
int main()
{   loading();
    poveste();
    meniu();
    closegraph();
    return 0;
}
