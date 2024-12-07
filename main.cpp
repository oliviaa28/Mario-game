/*  Ce goaluri ar trebui sa setam:   (sa presupunem ca dorim toti nota maxima si un proiect decent)

1. Meniu(instrucțiuni cu ce taste se pot utiliza etc etc, info echipa, meniu pt nivele)

2. Nivele( cu mape diferite-> pur si simplu facem mai multe fisiere text cu mape)

3.Viata mario 

4.stelute acumulate mario 

5. sa il facem pe mario sa poata sari ca sa nu fie obligatoriu sa foloseasca scarile 

6. fall damage(sa poata sa cada de pe platformele alea)

7. Inamici care se misca și îi scad din viata lui mario 

8. Sunete (acumulare bănuți, damage mario, mario când moare, sunet general/de fundal)

 -> finisari: Parte frontend 


RESURSE:
        -> https://docs.google.com/document/d/1f-WtvGDanuLMUIOxYEowxs6C_GYHOogXOAeA0g86tbk/edit?pli=1&tab=t.0 
          (gasiti cod scris de Patrut pt mario care va poate ajuta )

        ->instalare graphics.h pe vs code: https://youtu.be/J0_vt-7Ok6U?si=yOFTJqR0KNpSud4a

->pt vs code pt a rula programul: 1. CTRL+SHIFT+B 
                                  2.apasati click dreapta pe fisiereul main.exe ->Run executable     
    
*/

#include <fstream>
#include <winbgim.h>
#include <windows.h>
#include <string.h>
#include <iostream>
#include <conio.h>

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

int imario, jmario, ipostaza;
char tasta;
string directie;
int nrstelute;
int nrLinii,nrColoane,i,j;
char harta[MAX][MAX];
char car;


//cand vom implementa mai multe nivele trb sa facem o functie or smt pt citirea din fisierele care trebuie 
ifstream fisier("harta.txt");

//____________________________________________________________________________________________________________________________

void afiseazaMario()
{ 
 //CAZ 1,2,3 pentru depasare dreapta
 //CAZ -1,-2,-3 pentru deplasare stanga
 //CAZ -10 pt deplasare in jos 
 //CAZ 10 pt deplasare in sus
    int y=imario*latime, x=jmario*latime;
    //cand vom trece la finisari vom implementa aici un mers mai smooth pt mario(pt care avem nevoie de mai multe poze si cazuri)
    //, dar nu e momentul acum
    switch(ipostaza) {
        case -10: 
            readimagefile("mario_spate_1.jpg", x,y,x+latime,y+latime); break;
        case 10: 
            readimagefile("mario_spate_2.jpg", x,y,x+latime,y+latime); break;
        case 1:
            readimagefile("mario1.jpg", x,y,x+latime,y+latime); break;
        case 2:
            readimagefile("mario2.jpg", x,y,x+latime,y+latime); break;
        case 3:
            readimagefile("mario3.jpg", x,y,x+latime,y+latime); break;
        case -1:
            readimagefile("mario4.jpg", x,y,x+latime,y+latime); break;
        case -2:
            readimagefile("mario5.jpg", x,y,x+latime,y+latime); break;
        case -3:
            readimagefile("mario6.jpg", x,y,x+latime,y+latime); break;
    }
}

void afiseazaPoza(char c, int i, int j)
{ // olivia- cand am vb cu hadambu mi-a zis ca nu prea avem cum sa folosim png uri cu biblioteca asta:(((( /sau sa adaugam layers pt design
    if (c=='@')
        readimagefile("iarba.jpg",latime*j,latime*i,latime*(j+1),latime*(i+1));
    if (c=='#')
        readimagefile("scara.jpg",latime*j,latime*i,latime*(j+1),latime*(i+1));
    if (c=='*')
        readimagefile("stea.jpg",latime*j,latime*i,latime*(j+1),latime*(i+1));
    if (c=='.')
        readimagefile("fundal.jpg",latime*j,latime*i,latime*(j+1),latime*(i+1));
}

void stergeMario()
{
     readimagefile("spatiu.jpg",latime*jmario,latime*imario,latime*(jmario+1),latime*(imario+1));

      if (harta[imario][jmario] == '#')
      readimagefile("scara.jpg",latime*jmario,latime*imario,latime*(jmario+1),latime*(imario+1));

}


void urmatoareaIpostaza() 
{
    if (directie=="dreapta")
        {
            if (abs(ipostaza)==10) ipostaza=1;

            if (ipostaza<0) ipostaza=-ipostaza;

            ipostaza++;
            if (ipostaza==4) ipostaza=1;

            if (jmario<nrColoane-1 && harta[imario+1][jmario+1]!='.') //verificam daca mario nu iese din harta și daca se poate deplasa in dreapta (daca nu este gaura lol)
            {
                jmario++;
                if (harta[imario][jmario]=='*') // daca pe urmatoarea pozitie este o steluța
                {  // aici trebuie crescut scorul
                     harta[imario][jmario]='.'; 
                }
                
            }
        }
    else
    if (directie=="stanga")
        {
            if (abs(ipostaza)==10) ipostaza=-1;

            if (ipostaza>0) ipostaza=-ipostaza;

            ipostaza--;
            if (ipostaza==-4) ipostaza=-1;
            if (jmario>0  &&  harta[imario+1][jmario-1]!='.' ) //la fel ca la dreapta.
            {
                jmario--;
                if (harta[imario][jmario]=='*') // daca pe urmatoarea pozitie este o steluța
                {   // aici trebuie crescut scorul 
                     harta[imario][jmario]='.';
                }

            }
        }
    if (directie=="sus")
    {
        if (abs(ipostaza)==10)
            ipostaza=-ipostaza;
        else ipostaza=10;
        if (harta[imario-1][jmario]=='#') imario--; //verificam daca este scara si daca poate urca
        harta[imario][jmario]='#';
    }
    if (directie=="jos")
    {
        if (abs(ipostaza)==10) 
            ipostaza=-ipostaza;
        else ipostaza=-10;

        if (harta[imario+1][jmario]=='#') imario++;

        harta[imario][jmario]='#';
    }
}


void incarcaHarta()
{
    fisier>>nrLinii>>nrColoane;
    initwindow(latime*nrColoane,latime*nrLinii,"Mario se distreaza pe scari");
    setbkcolor(WHITE); 
    cleardevice();
    nrstelute=0; //o sa avem nevoie pt cand implementam scorul

    for (i=0;i<nrLinii;i++)
    {
        for (j=0;j<nrColoane;j++)
            {
                fisier>>car;
                if (car=='*') nrstelute++;
                if (car=='M') {imario=i; jmario=j; car='.';}
                harta[i][j]=car;
                afiseazaPoza(harta[i][j],i,j);
            }
    }
    fisier.close();

}
//____________________________________________________________________________________________________
/*void afiseazaText(int x, int y,  char *text) {
    setcolor(WHITE);  // Setăm culoarea textului
    outtextxy(x, y, text);  // Afișează textul la coordonatele (x, y)
}
void afiseazaMeniu() {
    setcolor(WHITE);
    rectangle(100, 100, 500, 200);  // Contur pentru meniu
    rectangle(100, 250, 500, 350);  // Contur pentru opțiunea Start Game
    rectangle(100, 400, 500, 500);  // Contur pentru opțiunea Help
    rectangle(100, 550, 500, 650);  // Contur pentru opțiunea Exit
    
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);  // Setăm stilul textului

    // Afisăm titluri folosind `outtextxy` dar putem să creăm o funcție mai robustă pentru afisare
    afiseazaText(200, 130, "Meniu Joc");
    afiseazaText(200, 270, "Start Game");
    afiseazaText(200, 420, "Help");
    afiseazaText(200, 570, "Exit");
}

// Funcția customizată pentru a afișa textul în coordonatele (x, y)

void procesareMeniu() {
    int x = mousex(), y = mousey();
    int optiune = 0;

    while (true) {
        // Afișăm din nou meniul pentru a face actualizări
        afiseazaMeniu();
        
        // Detectăm click-ul mouse-ului pentru opțiuni
        if (ismouseclick(WM_LBUTTONDOWN)) {
            getmouseclick(WM_LBUTTONDOWN, x, y);

            if (x >= 100 && x <= 500) {
                if (y >= 250 && y <= 350) {
                    optiune = 1;  // Start Game
                } else if (y >= 400 && y <= 500) {
                    optiune = 2;  // Help
                } else if (y >= 550 && y <= 650) {
                    optiune = 3;  // Exit
                }
            }
            
            if (optiune == 1) {
                afiseazaText(200, 300, "Jocul a inceput!");  // Oferim un feedback că jocul începe
                delay(2000);  // Așteptăm 2 secunde pentru a vedea mesajul
                break;  // Ieșim din meniu
            } else if (optiune == 2) {
                afiseazaText(200, 300, "Ajutor: Foloseste tastele pentru a naviga!");  // Mesaj ajutor
                delay(2000);  // Așteptăm 2 secunde pentru a vedea mesajul
                break;  // Ieșim din meniu
            } else if (optiune == 3) {
                afiseazaText(200, 300, "Iesire...");  // Mesaj de ieșire
                delay(2000);
                break;  // Ieșim din meniu
            }
        }
    }
}



*/

//____________________________________________________________________________________________________
int main()
{   

    incarcaHarta();
    ipostaza=1;
    afiseazaMario();

    do
    {
        tasta=getch(); 
        if (tasta==0) tasta=getch();

        if (tasta==STG && jmario>0 && harta[imario+1][jmario-1]!='.')           directie="stanga";
        if (tasta==DRP && jmario<nrColoane-1 && harta[imario+1][jmario+1]!='.') directie="dreapta";
        if (tasta==SUS && harta[imario-1][jmario]=='#')                         directie="sus";
        if (tasta==JOS && harta[imario+1][jmario]=='#')                         directie="jos";
         stergeMario();
        urmatoareaIpostaza();
        afiseazaMario();
        delay(100);        //delay(100) introduce o pauză de 100 milisecunde (sau 0,1 secunde) înainte ca programul să continue cu următoarea instrucțiune.
    } while (tasta!=ESC);  
    //sau trebuie sa facem ca programul sa ruleze cat timp nu am luat toate stelutele or smt

    closegraph();

    return 0;
}
