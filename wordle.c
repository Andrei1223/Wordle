#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define LUNG_CHENAR 3
#define LATIM_CHENAR 7
#define DIST_ORIZ 7
#define DIST_VERT 3
#define NUM_COL 6
#define NUM_LIN 6
#define NUM_CUV 27

void initializare()
{
    initscr();
    refresh();
}
// subprogram pentru alegerea unui numar aleator
int numRand ()
{
    srand(time(0));
    int num = rand() % NUM_CUV;
    return num;
}
// subprogram pentru afisarea mesajelor
void construire(WINDOW *patrate[7][7], WINDOW *cutie[2])
{
    int Xmax, Ymax;
    getmaxyx(stdscr, Ymax, Xmax);
    // stabilire proportii pentru inceput de matrice de chenare
    int i, coordX = (Xmax - 5 * LATIM_CHENAR - 10) / 2, coordY = Ymax * 0.1, j;
    for (i = 1; i <= 5; i++)
        for (j = 1; j <= 6; j++) 
        {
            patrate[i][j] = newwin(LUNG_CHENAR, LATIM_CHENAR, coordY + 
                DIST_VERT * j, coordX + DIST_ORIZ * i);
            box(patrate[i][j], 0, 0);
            // modificare fundal patrate
            wbkgd(patrate[i][j], COLOR_PAIR(1));
            wrefresh(patrate[i][j]);
        }
    // construire fereastra pentru afisare mesaje
    cutie[0] = newwin(LUNG_CHENAR * 1.5, LATIM_CHENAR * 5, coordY + 
    DIST_VERT * (NUM_COL + 1), coordX + DIST_ORIZ);
    box(cutie[0], 0, 0);
    wrefresh(cutie[0]);
    // afisare titlu
    wattron(stdscr, COLOR_PAIR(1));
    mvwprintw(stdscr, Ymax * 0.1, (Xmax - 4) / 2, "WORDLE");
    wattroff(stdscr, COLOR_PAIR(1));
    refresh();
    // afisare mesaj
    mvwprintw(cutie[0], 1, 3, "Introduceti un cuvant:");
    wbkgd(cutie[0], COLOR_PAIR(1));
    wrefresh(cutie[0]);

    // initializare meniu
    cutie[1] = newwin(LUNG_CHENAR * 5, LATIM_CHENAR * 5, 
    (Ymax - LUNG_CHENAR * 5) / 2,(Xmax - LATIM_CHENAR * 5) / 2);
}
// subprogram care verifica ce culoare trebuie sa aiba fiecare litera
int verif(char litera, char test[6], int i)
{
    int j;
    // se parcurge cuvantul ales de utilizator
    int gasit = 0;
    for (j = 0; j < 5; j++)
    {
         // daca s a gasit litera
        if ((int)test[j] == (int)litera)
        {
            // daca s a gasit pe aceeasi pozitie
            if (i == j)
            {
                return 2;
            }
            gasit = 1;    
        }
    }
    return gasit;
}
// subprogram pentru golirea cutiei in care se afiseaza mesaje
// si se afiseaza literele scrise
void golire(WINDOW *cutie[2])
{
    wrefresh(cutie[0]);
    wclear(cutie[0]);
    mvwprintw(cutie[0], 1, 3, "Introduceti un cuvant:");
    wrefresh(cutie[0]);
    box(cutie[0], 0, 0);
    wrefresh(cutie[0]);
}
// subprogram pentru golire a liniei unde se afiseaza measje
void golire_linie(WINDOW *cutie[2], char sir[30])
{
    int coordX, coordY;
    getyx(cutie[0], coordY, coordX);
    mvwprintw(cutie[0], 2, 3,"%s", sir);
    wrefresh(cutie[0]);
    wmove(cutie[0], coordY, coordX);
    wrefresh(cutie[0]);
}
// subprogram pentru afisarea meniului
void afisare(WINDOW *cutie[2], int ingros)
{
    clear();
    // setare culoare de fundal
    wbkgd(cutie[1], COLOR_PAIR(1));
    box(cutie[1], 0, 0);
    // se afiseaza mesajele
    mvwprintw(cutie[1], 1, 15, "MENIU");
    mvwprintw(cutie[1], 3, 1, "Va puteti muta de la optiune la ");
    mvwprintw(cutie[1], 4, 2, "alta apasand tasta SPACE, iar ");
    mvwprintw(cutie[1], 5, 3, "pentru a selecta o optiune, ");
    mvwprintw(cutie[1], 6, 6, "apasati tasta ENTER");
    // se afiseaza cele doua optiuni din meniu
    if (ingros == 1)
    {
        wattron(cutie[1], A_REVERSE);
        mvwprintw(cutie[1], 9, 13, "NEW GAME");
        wattroff(cutie[1], A_REVERSE);
        mvwprintw(cutie[1], 12, 15, "EXIT");
    }
    else
    {
        mvwprintw(cutie[1], 9, 13, "NEW GAME");
        wattron(cutie[1], A_REVERSE);
        mvwprintw(cutie[1], 12, 15, "EXIT");
        wattroff(cutie[1], A_REVERSE);
    }
    wrefresh(cutie[1]);
        
}
int main()
{
    WINDOW *patrate[7][7], *cutie[2];
    char cuvant[9], test[6];
    int culori[6][5], valRand, incercari = 0, i, cnt = 1, castigare, joc;
    char listaCuv[NUM_CUV][5]={"arici", "atent", "baiat", "ceata", "debut",
    "peste", "fixat", "hamac", "harta", "jalon", "jucam", "lacat", "magie",
    "nufar","oaste", "perus", "rigle", "roman", "sanie", "scris", "sonda",
    "texte", "tipar", "titan", "zebra", "vapor", "vatra"};
    joc = 1;
    castigare = 0;

    initializare();

    // nu afiseaza caracterele introduse de utilizator
    noecho();
    
    // face cursor invizibil
    curs_set(0);

    // setare culori
    start_color();
    // modificare culori
    init_color(COLOR_YELLOW, 999, 999, 0);
    init_color(COLOR_WHITE, 750, 750, 750);
    // initierea combinatiilor de culori
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    init_pair(2, COLOR_YELLOW, COLOR_WHITE);
    init_pair(3, COLOR_GREEN, COLOR_WHITE);
    // setare fundal
    bkgd(COLOR_PAIR(1));
    refresh();
    while(joc)
    {
        
        // se construiesc toate ferestrele
        construire(patrate, cutie);
        valRand = numRand();
        // se copiaza cuvantul ales
        for (i = 0; i < 5; i++)
            test[i] = listaCuv[valRand][i];
        test[5]='\0';
        // mecanica joc
        while (incercari <= 5)
        {
            castigare = 0;
            // mutare cursor
            wmove(cutie[0], 1, 26);

            wrefresh(cutie[0]);
            int cnt = 0;
            // citire pe randuri
            while(cnt != 6)
            {   
                char ch = wgetch(cutie[0]);
                // stergerea mesajului de la litera anterioara anterioara
                char sir[30] = "                        ";
                golire_linie(cutie, sir);

                // se verifica daca este litera mica
                if ((int)ch < 123 && (int)ch > 96)
                {
                    if (cnt <= 4)
                    {
                        cuvant[cnt] = ch;
                        wprintw(cutie[0], "%c", ch);
                        wrefresh(cutie[0]);
                        cnt++;
                    }
                }
                // verifica pentru caracterul delete
                else if ((int)ch == 127)
                {
                    if (cnt > 0)
                    {
                        // se sterge caracterul anterior in
                        int coordX, coordY;
                        getyx(cutie[0], coordY, coordX);
                        mvwaddch(cutie[0], coordY, coordX - 1, ' ');
                        wrefresh(cutie[0]);
                        wmove(cutie[0], coordY, coordX - 1);
                        cnt--;
                    }
                }
                // verifica daca este enter
                else if ((int)ch == 10)
                {
                    if (cnt == 5)
                    {
                        mvwprintw(cutie[0], 2, 3, "Cuvant valid!!");
                        cnt++;
                    }
                    // daca cuvantul este pera scurt
                    else if (cnt < 5)
                    {   
                        char sir[30] = "Cuvant prea scurt";
                        golire_linie(cutie, sir);
                    }
                    
                }
                // daca se doreste accesarea meniului
                else if ((int)ch == 58)
                {
                    // se iese din cele 2 loop uri
                    castigare = -1;
                    break;
                }
                 // pentru orice alt caracter
                else
                {
                    char sir[30] = "Nu ai introdus o litera!";
                    golire_linie(cutie, sir);
                }
            }
            // daca a fost apelat meniul
            if (castigare == -1)
                break;
            golire(cutie);
            // bucla pentru colorare de litere si margini
            int aux = 0;
            for (i = 1; i <= 5; i++)
            {
                int val = verif(cuvant[aux], test, aux);
                castigare += val;
                val += 1;
                // colorare patrate conform indicelui 
                wattron(patrate[i][incercari+1], COLOR_PAIR(val));
                mvwprintw(patrate[i][incercari+1], 1, 3, "%c", cuvant[aux++]);
                box(patrate[i][incercari+1],0,0);
                wattroff(patrate[i][incercari+1],COLOR_PAIR(val));
                wrefresh(patrate[i][incercari+1]);
            }
            // cazul in care a castigat jocul
            if (castigare == 10)
            {   
                wclear(cutie[0]);
                box(cutie[0], 0 ,0);
                mvwprintw(cutie[0], 1, 5, "Felicitari ai castigat!!");
                wrefresh(cutie[0]);
                break;
            }
            incercari++;
        }
        joc = 0;
        // se ofera posibilitatea de a juca din nou
        if (castigare == 10)
        {
            
            mvwprintw(cutie[0], 2, 1, "Apasa enter pentru a juca din nou");
            wrefresh(cutie[0]);
            char ch = wgetch(cutie[0]);
            // daca se doreste un nou joc
            if ((int)ch == 10)
                joc = 1;
            else
                goto FINAL;
        }
        // a fost apelat meniul
        else if (castigare == -1)
        {
            int pozitie = 1;
            MEVENT event;
            clear();
            refresh(); 
            // afisare meniu
            afisare(cutie, 1);
            while(1)
            {
                char ch = wgetch(cutie[1]);
                // daca este space
                if ((int)ch == 32)
                {
                    if (pozitie == 1)
                        pozitie = 2;

                    else 
                        pozitie = 1;
                    afisare(cutie, pozitie);
                }
                // daca este enter
                else if ((int)ch == 10)
                {
                    // daca se opreste jocul
                    if (pozitie == 2)
                        goto FINAL;
                    // daca reincepe jocul   
                    else 
                        break;
                }
                wrefresh(cutie[1]);

            }
            clear();
            refresh();
            // setarea parametrilor pentru a functiona 
            joc = 1;
            incercari = 0;
        }
        // cazul in care a pierdut
        else
        {
            wclear(cutie[0]);
            box(cutie[0], 0, 0);
            mvwprintw(cutie[0], 1, 2, "Ati pierdut jocul! Cuvantul care");
            mvwprintw(cutie[0], 2, 3, " trebuia ghicit este: %s", test);
            wrefresh(cutie[0]);
        }
    }
    getchar();
    FINAL:
    endwin();
    return 0;
} 
