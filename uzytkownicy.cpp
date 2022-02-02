#include <iostream>
#include "uzytkownicy.h"
#include <vector>
#include <fstream>
#include <windows.h>
using namespace std;
void Uzytkownik::wczytajUzytkownikow(vector <Uzytkownik> &uzytkownicy)
{
    fstream daneUzytkownika;
    daneUzytkownika.open("Uzytkownicy.txt",ios::in);
    if (daneUzytkownika.good() == true) {
        string zaczytanaLinia;
        while(getline(daneUzytkownika, zaczytanaLinia)) {
            string daneDoPrzypisania [3];
            int indeksDanej = 0;
            Uzytkownik uzytkownikDoPrzypisania;
            string danaDoPrzypisania = "";
            int dlugoscZaczytanejLinii = zaczytanaLinia.length();
            for(int i = 0; i < dlugoscZaczytanejLinii; i++) {
                if(zaczytanaLinia[i] != '|') {
                    danaDoPrzypisania += zaczytanaLinia[i];
                } else if(zaczytanaLinia[i] == '|') {
                    daneDoPrzypisania[indeksDanej] = danaDoPrzypisania;
                    danaDoPrzypisania = "";
                    indeksDanej++;
                }
            }
            uzytkownikDoPrzypisania.idUzytkownika = atoi(daneDoPrzypisania[0].c_str());
            uzytkownikDoPrzypisania.login = daneDoPrzypisania[1];
            uzytkownikDoPrzypisania.haslo = daneDoPrzypisania[2];
            uzytkownicy.push_back(uzytkownikDoPrzypisania);
        }
    }
    daneUzytkownika.close();
}
void Uzytkownik::zapiszUzytkownika(Uzytkownik nowyUzytkownik)
{
    fstream daneUzytkownika;
    daneUzytkownika.open("Uzytkownicy.txt",ios::out|ios::app);
    if(daneUzytkownika.good()) {
        daneUzytkownika << nowyUzytkownik.idUzytkownika << "|";
        daneUzytkownika << nowyUzytkownik.login << "|";
        daneUzytkownika << nowyUzytkownik.haslo << "|" << endl;
    }
    daneUzytkownika.close();
}
void Uzytkownik::rejestracja(vector<Uzytkownik> &uzytkownicy) {
    Uzytkownik nowyUzytkownik;
    int iloscUzytkownikow = uzytkownicy.size();
    string login, haslo;
    cout << "Podaj nazwe uzytkownika: ";
    cin >> login;
    int i = 0; //sprobuj wrzucic to linie nizej od razu while 0<ilosc
    while(i < iloscUzytkownikow) {
        if (uzytkownicy[i].login == login) {
            cout << "Taki uzytkownik juz istnieje. Wpisz inna nazwe uzytkownika: ";
            cin >> login;
            i = 0;
        } else {
            i++;
        }
    }
    cout << "Podaj haslo: ";
    cin >> haslo;
    nowyUzytkownik.login = login;
    nowyUzytkownik.haslo = haslo;
    nowyUzytkownik.idUzytkownika = iloscUzytkownikow + 1;
    uzytkownicy.push_back(nowyUzytkownik);
    zapiszUzytkownika(nowyUzytkownik);
    cout << "Konto zalozone" << endl;
    Sleep(1000);
}
int Uzytkownik::logowanie(vector<Uzytkownik> &uzytkownicy) {
    int iloscUzytkownikow = uzytkownicy.size();
    if (iloscUzytkownikow == 0) {
        cout << "Brak zarejestrowanych uzytkownikow. " << endl;
        Sleep(1500);
        return 0;
    } else {
        string login, haslo;
        cout << "Podaj login: ";
        cin >> login;
        int i = 0;
        while(i < iloscUzytkownikow) {
            if (uzytkownicy[i].login == login) {
                for (int proby = 0; proby < 3; proby++) {
                    cout << "Podaj haslo. Pozostalo prob " << 3-proby << ": ";
                    cin >> haslo;
                    if(uzytkownicy[i].haslo == haslo) {
                        cout << "Zalogowales sie. " << endl;
                        Sleep(1000);
                        return uzytkownicy[i].idUzytkownika;
                    }
                }
                cout << "Podales 3 razy bledne haslo. Poczekaj 3 sekundy przed kolejna proba" << endl;
                Sleep(3000);
                return 0;
            }
            i++;
        }
        cout << "Nie ma uzytkownika z takim loginem" << endl;
        Sleep(1000);
        return 0;
    }
}
