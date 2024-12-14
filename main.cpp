
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
int nrstelute=0,nrstelute_total;
int nrLinii,nrColoane,i,j;
char harta[MAX][MAX];
char car;
int vreasasara, jumpProgress=0, jumpHeight = 7;
ifstream fisier("harta.txt");

// Functia afisarii scorului 
void afiseazaScor()
{
    int x = latime * nrColoane - 200;
    int y = 10;

    // Sterge cifra/numarul anterior
    setfillstyle(SOLID_FILL, WHITE);
    bar(x, y, x + 300, y + 50);
    readimagefile("images/stars.jpg", x, y, x + 100, y + 50);

  int numX = x + 120; // Poziția pentru afișarea cifrei

    if (nrstelute == 0) {
        readimagefile("images/0.jpg", numX, y, numX + 30, y + 50);
    } else if (nrstelute == 1) {
        readimagefile("images/1.jpg", numX, y, numX + 30, y + 50);
    } else if (nrstelute == 2) {
        readimagefile("images/2.jpg", numX, y, numX + 30, y + 50);
    } else if (nrstelute == 3) {
        readimagefile("images/3.jpg", numX, y, numX + 30, y + 50);
    } else if (nrstelute == 4) {
        readimagefile("images/4.jpg", numX, y, numX + 30, y + 50);
    } else if (nrstelute == 5) {
        readimagefile("images/5.jpg", numX, y, numX + 30, y + 50);
    } else if (nrstelute == 6) {
        readimagefile("images/6.jpg", numX, y, numX + 30, y + 50);
    } else if (nrstelute == 7) {
        readimagefile("images/7.jpg", numX, y, numX + 30, y + 50);
    } else if (nrstelute == 8) {
        readimagefile("images/8.jpg", numX, y, numX + 30, y + 50);
    } else if (nrstelute == 9) {
        readimagefile("images/9.jpg", numX, y, numX + 30, y + 50);
    }
     
    }
//___________________________________________________________
void afiseazaMario()
{ 
 //CAZ 1,2,3 pentru depasare dreapta
 //CAZ -1,-2,-3 pentru deplasare stanga
 //CAZ -10 pt deplasare in jos 
 //CAZ 10 pt deplasare in sus
    int y=imario*latime, x=jmario*latime;

    switch(ipostaza) {
        case -10: 
            readimagefile("images/mario_spate_1.jpg", x,y,x+latime,y+latime); break;
        case 10: 
            readimagefile("images/mario_spate_2.jpg", x,y,x+latime,y+latime); break;
        case 1:
            readimagefile("images/mario1.jpg", x,y,x+latime,y+latime); break;
        case 2:
            readimagefile("images/mario2.jpg", x,y,x+latime,y+latime); break;
        case 3:
            readimagefile("images/mario3.jpg", x,y,x+latime,y+latime); break;
        case -1:
            readimagefile("images/mario4.jpg", x,y,x+latime,y+latime); break;
        case -2:
            readimagefile("images/mario5.jpg", x,y,x+latime,y+latime); break;
        case -3:
            readimagefile("images/mario6.jpg", x,y,x+latime,y+latime); break;
    }
}

void afiseazaPoza(char c, int i, int j)
{ 
    if (c=='@')
        readimagefile("images/iarba.jpg",latime*j,latime*i,latime*(j+1),latime*(i+1));
    if (c=='#')
        readimagefile("images/scara.jpg",latime*j,latime*i,latime*(j+1),latime*(i+1));
    if (c=='*')
        readimagefile("images/stea.jpg",latime*j,latime*i,latime*(j+1),latime*(i+1));
    if (c=='.')
        readimagefile("images/fundal.jpg",latime*j,latime*i,latime*(j+1),latime*(i+1));
}

void stergeMario()
{    
     readimagefile("images/spatiu.jpg",latime*jmario,latime*imario,latime*(jmario+1),latime*(imario+1));

      if (harta[imario][jmario] == '#')
          readimagefile("images/scara.jpg",latime*jmario,latime*imario,latime*(jmario+1),latime*(imario+1));

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
                {   
                     nrstelute++;
                     afiseazaScor();
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
                {    nrstelute++;
                     afiseazaScor();
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
    afiseazaScor();
    fisier>>nrLinii>>nrColoane;
    initwindow(latime*nrColoane,latime*nrLinii,"Mario se distreaza pe scari");
    setcolor(YELLOW);  
    setlinestyle(SOLID_LINE, 0, 5);  
    rectangle(0, 0, latime*nrColoane, latime*nrLinii);
    setbkcolor(WHITE);
    cleardevice(); 
    nrstelute_total=0;
    for (i=0;i<nrLinii;i++)
    {
        for (j=0;j<nrColoane;j++)
            {
                fisier>>car;
                if (car=='*') nrstelute_total++;
                if (car=='M') {imario=i; jmario=j; car='.';} 
                harta[i][j]=car;
                afiseazaPoza(harta[i][j],i,j);
            }
    }
    fisier.close();  
}
//_________________________________________________________________________________________________
void saritura() {
    if (vreasasara) {
        //  deplasare laterală în timpul săriturii
        if (kbhit()) { // Verificăm dacă există o tastă apăsată
            char tastaSaritura = getch();
            if (tastaSaritura == STG && jmario > 0 && harta[imario][jmario - 1] == '.') {
                stergeMario();
                jmario--; // Deplasare la stânga
            }
            if (tastaSaritura == DRP && jmario < nrColoane - 1 && harta[imario][jmario + 1] == '.') {
                stergeMario();
                jmario++; // Deplasare la dreapta
            }

        }

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
        }
        // Coborâre (a doua jumătate a săriturii)
        else if (jumpProgress < jumpHeight) {
            if (imario < nrLinii - 1 && harta[imario + 1][jmario] == '.') 
            {   stergeMario();
                imario++; // Mario coboară
                jumpProgress++;
            } else 
                jumpProgress = jumpHeight; // Finalizăm coborârea dacă întâlnim o platformă
            
        }
        // Finalizare săritură
        else {
            // Verificăm dacă Mario a ajuns pe o platformă 
            if (imario < nrLinii - 1 && (harta[imario + 1][jmario] == '.'|| harta[imario + 1][jmario] == '*')) {
                while (imario < nrLinii - 1 && (harta[imario + 1][jmario] == '.'|| harta[imario + 1][jmario] == '*')) 
                {
                    stergeMario();
                    imario++; // Mario continuă să cadă până ajunge pe platformă
                    if(harta[imario + 1][jmario] == '*'){
                         nrstelute++;
                         afiseazaScor();
                         harta[imario+1][jmario]='.'; }
                }
            }
            vreasasara = 0; // Săritura s-a terminat
            jumpProgress = 0;
        }
        afiseazaMario(); // Redesenăm Mario după orice modificare
    }
}
//__________________________________________________________________________________________________
 
 void goodjob()
 {  int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);
     int windowWidth = getmaxx();
    int windowHeight = getmaxy();

    int Width = 400;  
    int Height = 100;  
    int X1 = (windowWidth - Width) / 2-50;
    int Y1 =  windowHeight/2 -30; 
    int X2 = X1 + Width;
    int Y2 = Y1 + Height;
   readimagefile("images/goodjob.jpg", X1, Y1, X2, Y2);

    int marioWidth = 150;  
    int marioHeight = 200;
    int marioX1 = windowWidth - marioWidth - 17; 
    int marioY1 = (windowHeight - marioHeight) / 2;
    int marioX2 = marioX1 + marioWidth;
    int marioY2 = marioY1 + marioHeight;

    // Display the Mario image
    readimagefile("images/goodjob_mario.jpg", marioX1, marioY1, marioX2, marioY2);

    setcolor(YELLOW);  
    setlinestyle(SOLID_LINE, 0, 5);  
    rectangle(0, 0, windowWidth, windowHeight);
 }
//___________________________________________________________________________________________________________
void start()
{  
   incarcaHarta();
    ipostaza=1;
    nrstelute=0;
    afiseazaMario();

    do {
    if (vreasasara) 
        saritura(); 
    else {
        tasta = getch();
        if (tasta == 0) tasta = getch();

        if (!vreasasara) 
        { //  doar dacă nu sare
            if (tasta == STG && jmario > 0) 
            {
                if(harta[imario + 1][jmario - 1] != '.' && harta[imario + 1][jmario - 1] != '*')
                    directie = "stanga";
                
                if(harta[imario-1][jmario]=='#' && harta[imario+1][jmario]=='#' && harta[imario+1][jmario+1]=='.')
                    directie="stanga_scara";
            }
            if (tasta == DRP && jmario < nrColoane - 1) {
                if(harta[imario + 1][jmario + 1] != '.' && harta[imario + 1][jmario + 1] != '*')
                    directie = "dreapta";

            if(harta[imario-1][jmario]=='#'&& harta[imario+1][jmario]=='#' && harta[imario+1][jmario-1]=='.')
                    directie="dreapta_scara";
            }
            if (tasta == SUS && harta[imario - 1][jmario] == '#')
                    directie = "sus";

            if (tasta == JOS && harta[imario + 1][jmario] == '#')
                directie = "jos";

         if (tasta == SPC && !vreasasara) // Declanșare săritură
                {vreasasara = 1;
                stergeMario();
                imario--;}
        }
        stergeMario();
        urmatoareaIpostaza();
        afiseazaMario();
    }
    delay(120);

} while (tasta != ESC && nrstelute!=nrstelute_total);
        

if (nrstelute==nrstelute_total)
   { while(tasta!=ESC && tasta!=TAB)
          {   goodjob();
              tasta=getch(); }
       closegraph();     
    }

 closegraph();
}
//____________________________________________________________________________________________________
void instructiuni()
{
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);
     int windowWidth = getmaxx();
    int windowHeight = getmaxy();

    setcolor(YELLOW);  
    setlinestyle(SOLID_LINE, 0, 5);  
    rectangle(0, 0, windowWidth, windowHeight);

    int instImageWidth = 300;  
    int instImageHeight = 50; 
    int instX1 = (windowWidth - instImageWidth) / 2;
    int instY1 = 20; 
    int instX2 =instX1 + instImageWidth;
    int instY2 = instY1 + instImageHeight;
    readimagefile("images/instructiuni.jpg", instX1, instY1, instX2, instY2);

//pisica o sa fie inlocuita cu instructiuni
    int image2Width = 200;  
    int image2Height = 200; 
    int image2X1 = (windowWidth - image2Width) / 2;
    int image2Y1 = instY2 + 200; 
    int image2X2 = image2X1 + image2Width;
    int image2Y2 = image2Y1 + image2Height;
    readimagefile("images/cat.jpg", image2X1, image2Y1, image2X2, image2Y2);

    tasta = getch();
    if(tasta==ESC ||tasta==TAB||tasta==ESC) 
       closegraph();
}
//_________________________________________________________________
void exit()
{
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);
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
//____________________________________________________________________________________________________
 void meniu()
 { 
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);
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

    int arrowWidth = 50; 
    int arrowHeight = 50; 
    int arrowX = startX1 - arrowWidth;  // pozitia initiala a sagetii 
    int arrowY = startY1 + (startHeight / 2) - (arrowHeight / 2); 
    readimagefile("images/sageata.jpg", arrowX, arrowY, arrowX + arrowWidth, arrowY + arrowHeight);

    int tasta;
    int arrowPosition = 0;
    // 0 -> Start, 1 -> Instructions, 2 -> Exit

// start--ca sa nu fie delay(pt ca sageata e prima obtiune)
    if (arrowPosition==0)
        {  tasta = getch();  
            if (tasta==TAB || tasta==SPC)
                   {   start();
                      meniu();  }
         } 
    
    do {
        tasta = getch();
        if (tasta == 0) tasta = getch(); 
        readimagefile("images/negru.jpg", arrowX, arrowY, arrowX + arrowWidth, arrowY + arrowHeight); //pt as terge sageata cand ne deplasam
       
        if (tasta == JOS) {
            if (arrowPosition < 2) {  //mutam doar daca nu este la "Exit"
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
        }
        readimagefile("images/sageata.jpg", arrowX, arrowY, arrowX + arrowWidth, arrowY + arrowHeight);

//start(again)
          if (arrowPosition==0)
        {  tasta = getch();  
            if (tasta==TAB || tasta==SPC)
                   {  start();
                      meniu();  }
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
    } while (tasta != ESC);  
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
   
 int ok=0;
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
        ok=1;
    }

   if(ok==1)
    {closegraph();
     meniu(); }
    getch();
    closegraph();
}
//______________________________________________________________________________________________________
int main()
{   loading();
    meniu();
 
  
    closegraph();
    return 0;
}
