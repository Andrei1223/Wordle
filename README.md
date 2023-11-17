# Wordle

## Descriere
Pentru implementarea jocului WORDLE am folosit 7 subprograme acre aveau
rolul de a usura citirea liniilor de cod scrise in main. Aceasta 
reinterpretare a jocului accepta orice input de 5 litere mici ca fiind 
cuvant valid, iar in caz contrar afiseaza ori ca nu este litera ori ca
nu sunt 5 litere
Aceasta este schema optiunilor din timpul jocului:

     ---------->INCEPUT<-------------|
     |             |                 |
     |     |<------|                 |
     |     |       |                 |
   MENIU<--|   (CASTIG)              |
     |     |       |                 |
     |     |<------|                 |
     |             |                 |
     |  PIERDERE<----->CASTIG--------|
     |     |              |
     |---->|---->EXIT<----|

Totodata jocul are un meniu care poate fi accesat apasand tasta ':', 
insa acest lucru nu este scris nicaieri pe ecranul principal, fiind astfel 
greu de gasit acest lucru. 

## Implementare
WINDOW(s) : fiecare patrat care are asociat cate o litera este de forma
patrate[i][j] (aceasta fiind numele folosit in program)
            pentru chenarul de sub acestea s a folosit variabila cutie[0]
            iar pentru meniu s a folisit cutie[1]

--Subprogramul initializare

Contine functiile de baza pentru a initializa o fereastra folosit
biblioteca ncurses.

--Subprogramul numRand

Are rolul de a returna un numar aleator pentru a se alege cuvantul
din fiecare runda.

--Subprogramul construire

Contine toate ferestrele care trebuiesc construite pentru functionarea
jocului (plasarea acestora pe ecran si creearea borderului)si ,totodata,
setarea culorii de fundal si afisarea anumirtor mesaje cum ar fi titlul.

--Subprogramul verif

Verifica fiecare litera introdusa de utilizator si returneaza 0, 1, 2, 
reprezentand 0 - nu exista in cuvantul care trebuie ghicit, 1 - nu este
pe pozitia introdusa ed utilizatorsi 2 - se afla pe aceeasi pozitie. 


--Subprogramul golire

Are rolul de a goli zona de afisat mesaje dupa ce s a introdus un cuvant
adica dupa apasarea tastei ENTER (daca sunt suficiente litere).

--Subprogramul golire_linie

Are rolul de a elibera cea de a doua linie din fereastra cutie[0], si de 
a scrie textul primit in acel loc.

--Subprogramul afisare

Este folosit pentru mutarea in meniu de pe o optiune pe alta, schimbandu se
in functie de input highlight ul de pe una pe alta.
