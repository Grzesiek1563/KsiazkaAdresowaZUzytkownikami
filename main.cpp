#include <iostream>
#include <windows.h>
#include <vector>
using namespace std;

struct Uzytkownik
{
    int id;
    string nazwa, haslo;
};
void rejestracja(vector<Uzytkownik> &uzytkownicy)
{
    Uzytkownik nowyUzytkownik;
    int iloscUzytkownikow = uzytkownicy.size();
    string nazwa, haslo;
    cout<<"Podaj nazwe uzytkownika: ";
    cin>>nazwa;
    int i = 0;
    while(i<iloscUzytkownikow)
    {
        if (uzytkownicy[i].nazwa==nazwa)
        {
            cout<<"Taki uzytkownik juz istnieje. Wpisz inna nazwe uzytkownika: ";
            cin>>nazwa;
            i = 0;
        }
        else
        {
            i++;
        }
    }
    cout<<"Podaj haslo: ";
    cin>>haslo;
    nowyUzytkownik.nazwa=nazwa;
    nowyUzytkownik.haslo=haslo;
    nowyUzytkownik.id=iloscUzytkownikow+1;
    uzytkownicy.push_back(nowyUzytkownik);
    cout<<"Konto zalozone"<<endl;
    Sleep(1000);
}

int logowanie(vector<Uzytkownik> &uzytkownicy)
{
    int iloscUzytkownikow = uzytkownicy.size();
    string nazwa, haslo;
    cout << "Podaj login: ";
    cin >> nazwa;
    int i =0;
    while(i<iloscUzytkownikow)
    {
        if (uzytkownicy[i].nazwa==nazwa)
        {
            for (int proby=0; proby <3; proby++)
            {
                cout<<"Podaj haslo. Pozostalo prob "<<3-proby<<":";
                cin>>haslo;
                if(uzytkownicy[i].haslo == haslo)
                {
                    cout<<"Zalogowales sie. "<<endl;
                    Sleep(1000);
                    return uzytkownicy[i].id;
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
        if (uzytkownicy[i].id==idZalogowanegoUzytkownika)
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
    int iloscUzytkownikow = 0;
    char wybor;
    while (1)
    {
        if(idZalogowanegoUzytkownika==0)
        {
            system("cls");
            cout<<"1. Rejestracja"<<endl;
            cout<<"2. Logowanie"<<endl;
            cout<<"9. Zakoncz program"<<endl;
            cin>>wybor;
            if(wybor=='1')
            {
                rejestracja(uzytkownicy);
            }
            else if (wybor=='2')
            {
                idZalogowanegoUzytkownika = logowanie(uzytkownicy);
            }
            else if (wybor=='9')
            {
                exit(0);
            }
        }
        else
        {
            system("cls");
            cout<<"1. Zmiana hasla"<<endl;
            cout<<"2. Wylogowanie"<<endl;
            cin>>wybor;
            if(wybor=='1')
            {
                zmianaHasla(uzytkownicy, idZalogowanegoUzytkownika);
            }
            else if (wybor=='2')
            {
                idZalogowanegoUzytkownika = 0;
            }
        }
    }
    return 0;
}
