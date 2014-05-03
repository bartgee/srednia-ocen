/*
Srednia Ocen (wersja 1.0 beta)

Program wylicza srednia ocen.
Przydatny dla uczniow i rodzicow. :)

autor: Bart Grzybicki (bartgee)
email: bart@grzybicki.pl
*/

#include <iostream>
#include <iomanip> //potrzebne dla ustawienia ilosci miejsc po przecinku dla zmiennej typu double
#include <cstdio> //potzebne dla getchar()
#include <cstdlib> //potrzebne do czyszczenia ekranu
#include <sstream> // potrzebne do konwertowania zmiennej typu string do int
#include <time>

using namespace std;

// ponizej deklaracje funkcji, aby mialy wzajemny dostep do siebie
void clear_screen();
void exit_program();
void get_ratings();
bool isNumeric(const string pszInput, int nNumberBase);
int print_average();
void print_header();
void rerun();

double suma = 0; // deklaracja i przypisanie wartosci 0 zmiennej dla sumy ocen
string ocena_str; //deklaracja zmiennej typu string dla pobrania oceny
int ocena; // deklaracja zmiennej dla pojedynczej oceny
int wyjscie = 0; // deklaracja i przypisanie wartosci 0 dla zmiennej okreslajacej czy user chce wyjsc z  programu
double srednia = 0; // deklaracja i przypisanie wartosci 0 zmiennej dla sredniej ocen
int ilosc_ocen = 0; // deklaracja i przypisanie wartosci 0 dla zmiennej okreslajacej ilosc ocen, z ktorych liczona jest srednia ocen
char jeszcze_raz; //deklaracja zmiennej dla pytania czy user chce obliczac srednia od poczatku
int szybkie_wyjscie = 0; // deklaracja i przypisanie wartosci 0 zmiennej dla szybkiego wyjscia z programu (opcja q)

void clear_screen() // funkcja czyszczaca ekran - kod uwglednia platformy Windows i Unix/Linux
{
    #ifdef WIN32
    std::system ( "CLS" ); // czyszczenie ekranu dla systemu Windows
    #else
    std::system ( "clear" ); // czyszczenie ekranu dla systemow POSIX
    #endif
}

void print_header() //funkcja wyswietlajaca naglowek programu
{
    clear_screen();
    cout << "  ************************************" << endl;
    cout << "  *  Srednia Ocen (wersja 1.0 beta)  *" << endl;
    cout << "  *                  autor: bartgee  *" << endl;
    cout << "  *                                  *" << endl;
    cout << "  *  0 - wyliczenie sredniej         *" << endl;
    cout << "  *  q - wyjscie z programu          *" << endl;
    cout << "  ************************************" << endl << endl;
}

bool isNumeric(const string pszInput, int nNumberBase) // funkcja sprawdzajaca czy podana wartosc jest liczba
{
    string base = "0123456789ABCDEF";
    string input = pszInput;

    return (input.find_first_not_of(base.substr(0, nNumberBase)) == string::npos);
}

void get_ratings() //funkcja pobierajaca oceny
{
    jeszcze_raz = 'n';
    do
    {
        ocena_str = "";
        cout << "Podaj ocene nr " << ilosc_ocen + 1 << ": ";
        cin >> ocena_str;
        if (ocena_str == "q" || ocena_str == "Q")
        {
            //jeszcze_raz = 't';
            szybkie_wyjscie = 1;
            wyjscie = 1;
            break;
        }
        istringstream iss(ocena_str);
        iss >> ocena;
        //cout << ocena << endl;
        while ( isNumeric(ocena_str, 7) == false || ocena > 6 || ocena < 0)
        {
            clear_screen();
            print_header();
            cout << "BLAD, wprowadz ocene od 1 do 6!" << endl;
            get_ratings();
            break;
        }
        if (isNumeric(ocena_str,7) == true && ocena <= 6 && ocena > 0)
        {
            ilosc_ocen++; // zwieksza wartosc zmiennej ilosc_ocen o 1
            suma = suma + ocena; // dodaje sume ocen do wczesniejszej sumy ocen
            //cout << "ilosc ocen=" << ilosc_ocen;
        }
        if (ocena == 0) // jezeli user wybral wyliczenie sredniej (podal ocene 0) to wychodzimy z petli "do while"
        {
            wyjscie = 1;
            break;
        }
        srednia = suma/ilosc_ocen; // jezeli user wprowadzil co najmniej jedna ocene, wyliczamy srednia ocen.. a w zasadzie oceny :D
    } while (wyjscie == 0 && ocena <= 6 && ocena >= 0 || ocena == 'q');
}

int print_average() // funkcja wyswietlajaca srednia ocen
{
    if (wyjscie == 1 && szybkie_wyjscie == 1)
        return 0;
    if (ilosc_ocen  == 0) // wyswietenie komunikatu jesli user nie wprowadzil zadnych ocen
    {
        cout << "Nie wprowadzono zadnych ocen!" << endl;
        return(1); // wychodzimy z funkcji i nie wyswietlany sredniej, ktora wynioslaby 0 :)))
    }
    if (ilosc_ocen == 1) // wyswietenie komunikatu jesli user wprowadzil 1 ocene
    {
        cout << "Chyba samemu mozna obliczyc srednia z 1 oceny?! ;)" << endl;
        return(1); // wychodzimy z funkcji i nie wyswietlany sredniej, ktora wynioslaby tyle co 1 ocena  :)))
    }
    cout << "Ilosc ocen: " << ilosc_ocen << endl;
    cout << "________________________________________" << endl;
    cout << std::fixed << std::setprecision(2) << "Srednia ocen: " << srednia << endl << endl; // std::setprecision(2) ustawia dokladnosc 2 znakow po przecinku dla zmiennej typu double
    return(0);
}

void exit_program() // funkcja wychodzaca z programu
{
    char znak;
    cout << "Wcisnij ENTER aby wyjsc: " << endl;
    cin.clear();
    cin.ignore(1024, '\n');
    getchar() >> znak; // pobieranie znaku dla zatrzymania wykonywania programu
    cout << "bye! :)" << endl;
    sleep(1000);
}

void rerun () // funkcja uruchamiajaca wyliczanie sredniej od poczatku
{
    if (wyjscie == 1 && szybkie_wyjscie == 1)
    {
        jeszcze_raz = 'n';
    }
    else
    {
        cout << "Chcesz ponownie obliczyc srednia? (t/n): ";
        cin.clear();
        cin.ignore(1024, '\n');
        cin >> jeszcze_raz;
    }
}

int main()
{
    do
    {
    // zerujemy zmienne i uruchamiamy kolejne funkcje do obliczania sredniej
    suma = 0;
    wyjscie = 0;
    srednia = 0;
    ilosc_ocen = 0;
    print_header(); // wywolanie funkcji wyswietlajacej naglowek programu
    get_ratings(); // wywolanie funkcji pobierajacej oceny
    clear_screen(); // czyszczenie ekranu
    print_average(); // wywolanie funkcji wyswietlajacej srednia ocen
    rerun(); // wywolanie funkcji uruchamiajacej obliczanie sredniej od poczatku
    } while (jeszcze_raz == 't' || jeszcze_raz == 'T');
    exit_program(); // wywolanie funkcji wychodzacej z programu
}
