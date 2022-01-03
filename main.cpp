#include <iostream>
#include <windows.h>
#include <vector>
#include <conio.h>
using namespace std;

struct Uzytkownik
{
    int idUzytkownika;
    string login, haslo;
};
void rejestracja(vector<Uzytkownik> &uzytkownicy)
{
    Uzytkownik nowyUzytkownik;
    int iloscUzytkownikow = uzytkownicy.size();
    string login, haslo;
    cout<<"Podaj nazwe uzytkownika: ";
    cin>>login;
    int i = 0;
    while(i<iloscUzytkownikow)
    {
        if (uzytkownicy[i].login==login)
        {
            cout<<"Taki uzytkownik juz istnieje. Wpisz inna nazwe uzytkownika: ";
            cin>>login;
            i = 0;
        }
        else
        {
            i++;
        }
    }
    cout<<"Podaj haslo: ";
    cin>>haslo;
    nowyUzytkownik.login=login;
    nowyUzytkownik.haslo=haslo;
    nowyUzytkownik.idUzytkownika=iloscUzytkownikow+1;
    uzytkownicy.push_back(nowyUzytkownik);
    cout<<"Konto zalozone"<<endl;
    Sleep(1000);
}

int logowanie(vector<Uzytkownik> &uzytkownicy)
{
    int iloscUzytkownikow = uzytkownicy.size();
    string login, haslo;
    cout << "Podaj login: ";
    cin >> login;
    int i =0;
    while(i<iloscUzytkownikow)
    {
        if (uzytkownicy[i].login==login)
        {
            for (int proby=0; proby <3; proby++)
            {
                cout<<"Podaj haslo. Pozostalo prob "<<3-proby<<":";
                cin>>haslo;
                if(uzytkownicy[i].haslo == haslo)
                {
                    cout<<"Zalogowales sie. "<<endl;
                    Sleep(1000);
                    return uzytkownicy[i].idUzytkownika;
                }
            }
            cout<<"Podales 3 razy bledne haslo. Poczekaj 3 sekundy przed kolejna proba"<<endl;
            Sleep(3000);
            return 0;
        }
        i++;
    }
    cout<<"Nie ma uzytkownika z takim loginem"<<endl;
    Sleep(1000);
    return 0;

}
void zmianaHasla (vector<Uzytkownik> &uzytkownicy, int idZalogowanegoUzytkownika)
{
    int iloscUzytkownikow = uzytkownicy.size();
    string haslo;
    cout<<"Podaj nowe haslo: ";
    cin>>haslo;
    for(int i=0; i<iloscUzytkownikow; i++)
    {
        if (uzytkownicy[i].idUzytkownika==idZalogowanegoUzytkownika)
        {
            uzytkownicy[i].haslo=haslo;
            cout<<"Haslo zostalo zmienione"<<endl;
            Sleep(1500);
        }
    }
}

int main()
{
    vector<Uzytkownik> uzytkownicy(0);
    int idZalogowanegoUzytkownika = 0;
    char wybor;
    while (1)
    {
        if(idZalogowanegoUzytkownika==0)
        {
            system("cls");
            cout<<"1. Rejestracja"<<endl;
            cout<<"2. Logowanie"<<endl;
            cout<<"9. Zakoncz program"<<endl;
            cout<<"Twoj wybor: ";
            wybor = getch();
            switch (wybor)
            {
            case '1':
            {
                system("cls");
                rejestracja(uzytkownicy);
            }
            break;
            case '2':
            {
                system("cls");
                idZalogowanegoUzytkownika = logowanie(uzytkownicy);
            }
            break;
            case '9':
            {
                exit(0);
            }
            break;
            default:
            {
            cout<<"Wybrales nieprawidlowy numer."<<endl;
            Sleep(1500);
            }
            }
        }
        else
        {
            system("cls");
            cout<<"1. Zmiana hasla"<<endl;
            cout<<"2. Wylogowanie"<<endl;
            cout<<"Twoj wybor: ";
            wybor = getch();
            switch (wybor)
            {
            case '1':
            {
                system("cls");
                zmianaHasla(uzytkownicy, idZalogowanegoUzytkownika);
            }
            break;
            case '2':
            {
                system("cls");
                idZalogowanegoUzytkownika = 0;
            }
            break;
            default:
            {
            cout<<"Wybrales nieprawidlowy numer."<<endl;
            Sleep(1500);
            }
            }
        }
    }
    return 0;
}
