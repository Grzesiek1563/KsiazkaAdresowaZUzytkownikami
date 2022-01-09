#include <iostream>
#include <conio.h>
#include <windows.h>
#include <fstream>
#include <cstdlib>
#include <vector>
using namespace std;
struct DaneKontaktu
{
    int idKontaktu, idZalogowanegoUzytkownika;
    string imie, nazwisko, nrTelefonu, adresZamieszkania, email;
};
struct Uzytkownik
{
    int idUzytkownika;
    string login, haslo;
};
bool sprawdzCzyKsiazkaAdresowaZawieraKontakty (vector<DaneKontaktu> &kontakty)
{
    if (kontakty.size() == 0)
    {
        cout<<"Twoja ksiazka adresowa jest pusta. Dodaj nowe kontakty.";
        Sleep(1500);
        return false;
    }
    else
        return true;
}
bool sprawdzCzyIstniejeJuzTakiKontakt (string imie, string nazwisko, vector<DaneKontaktu> &kontakty)
{
    bool istniejeJuzTakiKontakt = false;
    int iloscKontaktow = kontakty.size();
    for (int i = 0; i < iloscKontaktow; i++)
    {
        if(imie == kontakty[i].imie && nazwisko == kontakty[i].nazwisko)
        {
            istniejeJuzTakiKontakt = true;
        }
    }
    if(istniejeJuzTakiKontakt)
    {
        cout << "Posiadasz  juz osobe o takim imieniu i nazwisku w swoich kontaktach. Czy chcesz kontynuowac? (T/N)" << endl;
        char znakDecyzji = getch();
        if (znakDecyzji == 'N' || znakDecyzji == 'n')
        {
            cout<<"Przerwano dodawanie kontaktu";
            Sleep(1000);
            return false;
        }
    }
    return true;
}
void zapiszKontakt(DaneKontaktu osobaDoDodania)
{
    fstream ksiazkaAdresowa;
    ksiazkaAdresowa.open("Adresaci.txt", ios::out|ios::app);
    if(ksiazkaAdresowa.good())
    {
        ksiazkaAdresowa << osobaDoDodania.idKontaktu << "|";
        ksiazkaAdresowa << osobaDoDodania.idZalogowanegoUzytkownika << "|";
        ksiazkaAdresowa << osobaDoDodania.imie << "|";
        ksiazkaAdresowa << osobaDoDodania.nazwisko << "|";
        ksiazkaAdresowa << osobaDoDodania.nrTelefonu << "|";
        ksiazkaAdresowa << osobaDoDodania.email << "|";
        ksiazkaAdresowa << osobaDoDodania.adresZamieszkania << "|" << endl;
    }
    ksiazkaAdresowa.close();
}
int wyznaczIdNowegoAdresata ()
{
    fstream ksiazkaAdresowa;
    string zaczytanaLinia;
    string idOstatniegoAdresata = "";
    int idNowegoAdresata = 1;
    int iloscLiniiPliku = 0;
    int licznikLiniiPliku = 1;
    ksiazkaAdresowa.open("Adresaci.txt", ios::in);
    if (ksiazkaAdresowa.good() == true)
    {
        while(getline(ksiazkaAdresowa, zaczytanaLinia))
        {
            iloscLiniiPliku++;
        }
    }
    ksiazkaAdresowa.close();
    ksiazkaAdresowa.open("Adresaci.txt", ios::in);
    if (ksiazkaAdresowa.good() == true)
    {
        while(getline(ksiazkaAdresowa, zaczytanaLinia))
        {
            if(licznikLiniiPliku == iloscLiniiPliku)
            {
                int indeksZnaku = 0;
                while (zaczytanaLinia[indeksZnaku] != '|')
                {
                    idOstatniegoAdresata += zaczytanaLinia[indeksZnaku];
                    indeksZnaku++;
                }
            }
            else
            {
                licznikLiniiPliku++;
            }
        }
        idNowegoAdresata = atoi(idOstatniegoAdresata.c_str()) + 1;
        return idNowegoAdresata;
    }
    ksiazkaAdresowa.close();
    return idNowegoAdresata;
}

void dodajKontakt (vector<DaneKontaktu> &kontakty, int idZalogowanegoUzytkownika)
{
    int iloscKontaktow = kontakty.size();
    bool kontynowacDodawanieKontaktu = true;
    DaneKontaktu osobaDoDodania;
    string imie, nazwisko;
    cout << "Podaj imie: ";
    cin >> imie;
    cout << "Podaj nazwisko: ";
    cin >> nazwisko;
    kontynowacDodawanieKontaktu = sprawdzCzyIstniejeJuzTakiKontakt(imie, nazwisko, kontakty);
    if(kontynowacDodawanieKontaktu)
    {
        osobaDoDodania.imie = imie;
        osobaDoDodania.nazwisko = nazwisko;
        cout << "Podaj numer telefonu: ";
        cin.sync();
        getline(cin, osobaDoDodania.nrTelefonu);
        cout << "Podaj adres zamieszkania: ";
        cin.sync();
        getline(cin, osobaDoDodania.adresZamieszkania);
        cout << "Podaj email: ";
        cin >> osobaDoDodania.email;
        osobaDoDodania.idZalogowanegoUzytkownika = idZalogowanegoUzytkownika;
        osobaDoDodania.idKontaktu = wyznaczIdNowegoAdresata();
        kontakty.push_back(osobaDoDodania);
        zapiszKontakt(osobaDoDodania);
    }
}
void wyszukiwanieImieniem(vector<DaneKontaktu> &kontakty, string &imieDoOdszukania)
{
    int iloscKontaktow = kontakty.size();
    bool ksiazkaZawieraPodaneImie = false;
    for(int i = 0; i < iloscKontaktow; i++)
    {
        if (kontakty[i].imie == imieDoOdszukania)
        {
            cout << "ID kontaktu: " << kontakty[i].idKontaktu << endl;
            cout << kontakty[i].imie << " " << kontakty[i].nazwisko << endl;
            cout << "Numer telefonu: " << kontakty[i].nrTelefonu << endl;
            cout << "Email: " << kontakty[i].email << endl;
            cout << "Adres zamieszkania: " << kontakty[i].adresZamieszkania << endl;
            ksiazkaZawieraPodaneImie = true;
        }
    }
    if (!ksiazkaZawieraPodaneImie)
        cout << "W Twojej ksiazce nie ma osoby o takim imeniu" << endl;
    system("pause");
}
void wyszukiwanieNazwiskiem(vector<DaneKontaktu> &kontakty, string &nazwiskoDoOdszukania)
{
    int iloscKontaktow = kontakty.size();
    bool ksiazkaZawieraPodaneNazwisko = false;
    for(int i = 0; i < iloscKontaktow; i++)
    {
        if (kontakty[i].nazwisko == nazwiskoDoOdszukania)
        {
            cout << "ID kontaktu: " << kontakty[i].idKontaktu << endl;
            cout << kontakty[i].imie << " " << kontakty[i].nazwisko << endl;
            cout << "Numer telefonu: " << kontakty[i].nrTelefonu << endl;
            cout << "Email: " << kontakty[i].email << endl;
            cout << "Adres zamieszkania: " << kontakty[i].adresZamieszkania << endl;
            ksiazkaZawieraPodaneNazwisko = true;
        }
    }
    if (!ksiazkaZawieraPodaneNazwisko)
        cout << "W Twojej ksiazce nie ma osoby o takim nazwisku" << endl;
    system("pause");
}
void wyswietlWszystkieKontakty(vector<DaneKontaktu> &kontakty)
{
    int iloscKontaktow = kontakty.size();
    for(int i = 0; i < iloscKontaktow; i++)
    {
        cout << "ID kontaktu: " << kontakty[i].idKontaktu << endl;
        cout << kontakty[i].imie << " " << kontakty[i].nazwisko << endl;
        cout << "Numer telefonu: " << kontakty[i].nrTelefonu << endl;
        cout << "Email: " << kontakty[i].email << endl;
        cout << "Adres zamieszkania: " << kontakty[i].adresZamieszkania << endl;
    }
}
void zapisDoPlikuPoUsunieciuKontaktu (int idUsuwanegoKontaktu)
{
    fstream ksiazkaAdresowa;
    string zaczytanaLinia, idAdresata;
    ksiazkaAdresowa.open("Adresaci.txt", ios::in);
    if (ksiazkaAdresowa.good() == true)
    {
        fstream ksiazkaAdresowaTymczasowy;
        ksiazkaAdresowaTymczasowy.open("Adresaci_tymczasowy.txt", ios::out);
        if (ksiazkaAdresowaTymczasowy.good() == true)
        {
            while(getline(ksiazkaAdresowa, zaczytanaLinia))
            {
                idAdresata = "";
                int indeksZnaku = 0;
                while (zaczytanaLinia[indeksZnaku] != '|')
                {
                    idAdresata += zaczytanaLinia[indeksZnaku];
                    indeksZnaku++;
                }
                int zaczytaneIdAresata = atoi(idAdresata.c_str());
                if(idUsuwanegoKontaktu == zaczytaneIdAresata)
                {
                    ;
                }
                else
                {
                    ksiazkaAdresowaTymczasowy << zaczytanaLinia << endl;
                }
            }
        }
        ksiazkaAdresowaTymczasowy.close();
    }
    ksiazkaAdresowa.close();
    remove("Adresaci.txt");
    rename("Adresaci_tymczasowy.txt", "Adresaci.txt");
}
bool sprawdzCzyJestKontaktOTakimId(vector<DaneKontaktu> kontakty, int idSprawdzanegoKontaktu)
{
    for (int i = 0; i < kontakty.size(); i++)
    {
        if(kontakty[i].idKontaktu == idSprawdzanegoKontaktu)
        {
            return true;
        }
    }
    return false;
}
void usunAdresata (vector<DaneKontaktu> &kontakty)
{
    bool ksiazkaAdresowaZawieraKontakty = sprawdzCzyKsiazkaAdresowaZawieraKontakty(kontakty);
    if (ksiazkaAdresowaZawieraKontakty)
    {
        cout << "Oto lista wszystkich kontaktow: " << endl;
        wyswietlWszystkieKontakty(kontakty);
        cout << "Aby usunac kontakt, wpisz jego ID: ";
        int idKontaktuDoUsuniecia;
        cin >> idKontaktuDoUsuniecia;
        bool wKsiazceJestKontaktOTakimId = sprawdzCzyJestKontaktOTakimId(kontakty, idKontaktuDoUsuniecia);
        if(wKsiazceJestKontaktOTakimId)
        {
            char potwierdzenieUsuniecia;
            cout << "Czy jestes pewien ze chcesz usunac ten kontakt(t/n)?";
            potwierdzenieUsuniecia = getch();
            if (potwierdzenieUsuniecia == 't' || potwierdzenieUsuniecia == 'T')
            {
                for(int i = 0; i < kontakty.size(); i++)
                {
                    if(kontakty[i].idKontaktu == idKontaktuDoUsuniecia)
                    {
                        kontakty.erase(kontakty.begin() + i);
                        system("cls");
                        cout << "Pomyslnie usunieto kontakt";
                        Sleep(2000);
                    }
                }
                zapisDoPlikuPoUsunieciuKontaktu(idKontaktuDoUsuniecia);
            }
        }
        else
        {
            cout << "W Twojej ksiazce nie ma osoby o takim ID" << endl;
            Sleep(1500);
        }
    }
}
void zapisDoPlikuPoZedytowaniuKontaktu (int iDEdytowanegoKontaktu, DaneKontaktu zedytowanyKontakt)
{
    fstream ksiazkaAdresowa;
    string zaczytanaLinia, idAdresata;
    ksiazkaAdresowa.open("Adresaci.txt", ios::in);
    if (ksiazkaAdresowa.good() == true)
    {
        fstream ksiazkaAdresowaTymczasowy;
        ksiazkaAdresowaTymczasowy.open("Adresaci_tymczasowy.txt", ios::out);
        if (ksiazkaAdresowaTymczasowy.good() == true)
        {
            while(getline(ksiazkaAdresowa, zaczytanaLinia))
            {
                idAdresata = "";
                int indeksZnaku = 0;
                while (zaczytanaLinia[indeksZnaku] != '|')
                {
                    idAdresata += zaczytanaLinia[indeksZnaku];
                    indeksZnaku++;
                }
                int zaczytaneIdAresata = atoi(idAdresata.c_str());
                if(iDEdytowanegoKontaktu == zaczytaneIdAresata)
                {
                    ksiazkaAdresowaTymczasowy << zedytowanyKontakt.idKontaktu << "|";
                    ksiazkaAdresowaTymczasowy <<zedytowanyKontakt.idZalogowanegoUzytkownika << "|";
                    ksiazkaAdresowaTymczasowy <<zedytowanyKontakt.imie << "|";
                    ksiazkaAdresowaTymczasowy <<zedytowanyKontakt.nazwisko << "|";
                    ksiazkaAdresowaTymczasowy <<zedytowanyKontakt.nrTelefonu << "|";
                    ksiazkaAdresowaTymczasowy <<zedytowanyKontakt.email << "|";
                    ksiazkaAdresowaTymczasowy <<zedytowanyKontakt.adresZamieszkania << "|" << endl;
                }
                else
                {
                    ksiazkaAdresowaTymczasowy << zaczytanaLinia << endl;
                }
            }
        }
        ksiazkaAdresowaTymczasowy.close();
    }
    ksiazkaAdresowa.close();
    remove("Adresaci.txt");
    rename("Adresaci_tymczasowy.txt", "Adresaci.txt");
}
void edytujAdresata (vector<DaneKontaktu> &kontakty)
{
    bool ksiazkaAdresowaZawieraKontakty = sprawdzCzyKsiazkaAdresowaZawieraKontakty(kontakty);
    if (ksiazkaAdresowaZawieraKontakty)
    {
        cout << "Oto lista wszystkich kontaktow: " << endl;
        wyswietlWszystkieKontakty(kontakty);
        int idEdytowanegoKontaktu;
        cout << "Podaj ID kontaktu dla ktorego chcesz wprowadzic zmiany: ";
        cin >> idEdytowanegoKontaktu;
        bool wKsiazceJestKontaktOTakimId = sprawdzCzyJestKontaktOTakimId(kontakty, idEdytowanegoKontaktu);
        if(wKsiazceJestKontaktOTakimId)
        {
            DaneKontaktu zedytowanyKontakt;
            int indeksEdytowanegoKontaktu = 0;
            for (int i = 0; i < kontakty.size(); i++)
            {
                if(kontakty[i].idKontaktu == idEdytowanegoKontaktu)
                {
                    indeksEdytowanegoKontaktu = i;
                }
            }
            system("cls");
            cout << "1 - imie" << endl << "2 - nazwisko" << endl << "3 - numer telefonu" << endl;
            cout << "4 - email" << endl << "5 - adres" << endl << "6 - powrot do menu" << endl;
            cout << "Twoj wybor: ";
            char znakWyboru;
            znakWyboru = getch();
            system("cls");
            switch(znakWyboru)
            {
            case '1':
            {
                string noweImie;
                cout << "Podaj nowe imie: ";
                cin >> noweImie;
                kontakty[indeksEdytowanegoKontaktu].imie = noweImie;
            }
            break;
            case '2':
            {
                string noweNazwisko;
                cout << "Podaj nowe nazwisko: ";
                cin >> noweNazwisko;
                kontakty[indeksEdytowanegoKontaktu].nazwisko = noweNazwisko;
            }
            break;
            case '3':
            {
                string nowyNrTelefonu;
                cout << "Podaj nowy numer telefonu: ";
                cin.sync();
                getline(cin, nowyNrTelefonu);
                kontakty[indeksEdytowanegoKontaktu].nrTelefonu = nowyNrTelefonu;
            }
            break;
            case '4':
            {
                string nowyEmail;
                cout << "Podaj nowy email: ";
                cin >> nowyEmail;
                kontakty[indeksEdytowanegoKontaktu].email = nowyEmail;
            }
            break;
            case '5':
            {
                string nowyAdres;
                cout << "Podaj nowy adres: ";
                cin.sync();
                getline(cin, nowyAdres);
                kontakty[indeksEdytowanegoKontaktu].adresZamieszkania = nowyAdres;
            }
            break;
            case '6':
            {
                ;
            }
            break;
            default:
            {
                cout << "Wybrales nieprawidlowy numer." << endl;
                Sleep(1500);
            }
            }
            zedytowanyKontakt = kontakty[indeksEdytowanegoKontaktu];
            zapisDoPlikuPoZedytowaniuKontaktu(idEdytowanegoKontaktu, zedytowanyKontakt);
        }
        else
        {
            cout << "W Twojej ksiazce nie ma osoby o takim ID" << endl;
            Sleep(1500);
        }
    }
}
vector<DaneKontaktu> wczytajAdresatow(int idZalogowanegoUzytkownika)
{
    fstream ksiazkaAdresowa;
    ksiazkaAdresowa.open("Adresaci.txt",ios::in);
    vector<DaneKontaktu> kontakty(0);
    if (ksiazkaAdresowa.good() == true)
    {
        string zaczytanaLinia;
        while(getline(ksiazkaAdresowa, zaczytanaLinia))
        {
            string daneAdresata [7];
            int indeksDanej = 0;
            DaneKontaktu osobaDoPrzypisania;
            string danaDoPrzypisania = "";
            int dlugoscZaczytanejLinii = zaczytanaLinia.length();
            for(int i = 0; i < dlugoscZaczytanejLinii; i++)
            {
                if(zaczytanaLinia[i] != '|')
                {
                    danaDoPrzypisania += zaczytanaLinia[i];
                }
                else if(zaczytanaLinia[i] == '|')
                {
                    daneAdresata[indeksDanej] = danaDoPrzypisania;
                    danaDoPrzypisania = "";
                    indeksDanej++;
                }
            }
            int zaczytaneIdUzytkownika = atoi(daneAdresata[1].c_str());
            if (zaczytaneIdUzytkownika == idZalogowanegoUzytkownika)
            {
                osobaDoPrzypisania.idKontaktu = atoi(daneAdresata[0].c_str());
                osobaDoPrzypisania.idZalogowanegoUzytkownika = atoi(daneAdresata[1].c_str());
                osobaDoPrzypisania.imie = daneAdresata[2];
                osobaDoPrzypisania.nazwisko = daneAdresata[3];
                osobaDoPrzypisania.nrTelefonu = daneAdresata[4];
                osobaDoPrzypisania.email = daneAdresata[5];
                osobaDoPrzypisania.adresZamieszkania = daneAdresata[6];
                kontakty.push_back(osobaDoPrzypisania);
            }
        }
    }
    ksiazkaAdresowa.close();
    return kontakty;
}
vector<Uzytkownik> wczytajUzytkownikow()
{
    fstream daneUzytkownika;
    daneUzytkownika.open("Uzytkownicy.txt",ios::in);
    vector<Uzytkownik> uzytkownicy(0);
    if (daneUzytkownika.good() == true)
    {
        string zaczytanaLinia;
        while(getline(daneUzytkownika, zaczytanaLinia))
        {
            string daneDoPrzypisania [3];
            int indeksDanej = 0;
            Uzytkownik uzytkownikDoPrzypisania;
            string danaDoPrzypisania = "";
            int dlugoscZaczytanejLinii = zaczytanaLinia.length();
            int indeksOstatniegoZnakuZaczytanejLinii = dlugoscZaczytanejLinii - 1;
            for(int i = 0; i < dlugoscZaczytanejLinii; i++)
            {
                if(zaczytanaLinia[i] != '|')
                {
                    danaDoPrzypisania += zaczytanaLinia[i];
                }
                else if(zaczytanaLinia[i] == '|')
                {
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
    return uzytkownicy;
}
void zapiszUzytkownika(Uzytkownik nowyUzytkownik)
{
    fstream daneUzytkownika;
    daneUzytkownika.open("Uzytkownicy.txt",ios::out|ios::app);
    if(daneUzytkownika.good())
    {
        daneUzytkownika << nowyUzytkownik.idUzytkownika << "|";
        daneUzytkownika << nowyUzytkownik.login << "|";
        daneUzytkownika << nowyUzytkownik.haslo << "|" << endl;
    }
    daneUzytkownika.close();
}
void rejestracja(vector<Uzytkownik> &uzytkownicy)
{
    Uzytkownik nowyUzytkownik;
    int iloscUzytkownikow = uzytkownicy.size();
    string login, haslo;
    cout << "Podaj nazwe uzytkownika: ";
    cin >> login;
    int i = 0;
    while(i < iloscUzytkownikow)
    {
        if (uzytkownicy[i].login == login)
        {
            cout << "Taki uzytkownik juz istnieje. Wpisz inna nazwe uzytkownika: ";
            cin >> login;
            i = 0;
        }
        else
        {
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

int logowanie(vector<Uzytkownik> uzytkownicy)
{
    int iloscUzytkownikow = uzytkownicy.size();
    if (iloscUzytkownikow == 0)
    {
        cout << "Brak zarejestrowanych uzytkownikow. " << endl;
        Sleep(1500);
        return 0;
    }
    else
    {
        string login, haslo;
        cout << "Podaj login: ";
        cin >> login;
        int i = 0;
        while(i < iloscUzytkownikow)
        {
            if (uzytkownicy[i].login == login)
            {
                for (int proby = 0; proby < 3; proby++)
                {
                    cout << "Podaj haslo. Pozostalo prob " << 3-proby << ": ";
                    cin >> haslo;
                    if(uzytkownicy[i].haslo == haslo)
                    {
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
void zapiszUzytkownikowPoZmianieHasla (vector<Uzytkownik> uzytkownicy)
{
    fstream daneUzytkownika;
    daneUzytkownika.open("Uzytkownicy.txt",ios::out);
    if(daneUzytkownika.good())
    {
        for (int i = 0; i < uzytkownicy.size(); i++)
        {
            daneUzytkownika << uzytkownicy[i].idUzytkownika << "|";
            daneUzytkownika << uzytkownicy[i].login << "|";
            daneUzytkownika << uzytkownicy[i].haslo << "|" << endl;
        }
    }
    daneUzytkownika.close();
}
void zmianaHasla (vector<Uzytkownik> &uzytkownicy, int idZalogowanegoUzytkownika)
{
    int iloscUzytkownikow = uzytkownicy.size();
    string haslo;
    cout << "Podaj nowe haslo: ";
    cin >> haslo;
    for(int i = 0; i < iloscUzytkownikow; i++)
    {
        if (uzytkownicy[i].idUzytkownika == idZalogowanegoUzytkownika)
        {
            uzytkownicy[i].haslo = haslo;
            cout << "Haslo zostalo zmienione" << endl;
            Sleep(1500);
        }
    }
    zapiszUzytkownikowPoZmianieHasla(uzytkownicy);
}
int uruchomKsiazkeAdresowa(vector <Uzytkownik> &uzytkownicy, int idZalogowanegoUzytkownika)
{
    bool ksiazkaAdresowaZawieraKontakty = false;
    vector<DaneKontaktu> kontakty(0);
    kontakty = wczytajAdresatow(idZalogowanegoUzytkownika);
    char wyborOpcji;
    while (1)
    {
        system("cls");
        cout << "KSIAZKA ADRESOWA" << endl;
        cout << "1. Dodaj adresata" << endl;
        cout << "2. Wyszukaj po imieniu" << endl;
        cout << "3. Wyszukaj po nazwisku" << endl;
        cout << "4. Wyswietl wszystkich adresatow" << endl;
        cout << "5. Usun adresata" << endl;
        cout << "6. Edytuj adresata" << endl;
        cout << "7. Zmien haslo" << endl;
        cout << "8. Wyloguj sie" << endl;
        cout << "Twoj wybor: ";
        wyborOpcji = getch();
        switch(wyborOpcji)
        {
        case '1':
        {
            system("cls");
            dodajKontakt(kontakty, idZalogowanegoUzytkownika);
        }
        break;
        case '2':
        {
            system("cls");
            ksiazkaAdresowaZawieraKontakty = sprawdzCzyKsiazkaAdresowaZawieraKontakty(kontakty);
            if (ksiazkaAdresowaZawieraKontakty)
            {
                string imieDoOdszukania;
                cout << "Podaj imie: ";
                cin >> imieDoOdszukania;
                wyszukiwanieImieniem(kontakty, imieDoOdszukania);
            }
        }
        break;
        case '3':
        {
            system("cls");
            ksiazkaAdresowaZawieraKontakty = sprawdzCzyKsiazkaAdresowaZawieraKontakty(kontakty);
            if (ksiazkaAdresowaZawieraKontakty)
            {
                string nazwiskoDoOdszukania;
                cout << "Podaj nazwisko: ";
                cin >> nazwiskoDoOdszukania;
                wyszukiwanieNazwiskiem(kontakty, nazwiskoDoOdszukania);
            }
        }
        break;
        case '4':
        {
            system("cls");
            ksiazkaAdresowaZawieraKontakty = sprawdzCzyKsiazkaAdresowaZawieraKontakty(kontakty);
            if (ksiazkaAdresowaZawieraKontakty)
            {
                wyswietlWszystkieKontakty(kontakty);
                system("pause");
            }
        }
        break;
        case '5':
        {
            system("cls");
            usunAdresata(kontakty);
        }
        break;
        case '6':
        {
            system("cls");
            edytujAdresata(kontakty);
        }
        break;
        case '7':
        {
            system("cls");
            zmianaHasla(uzytkownicy, idZalogowanegoUzytkownika);
        }
        break;
        case '8':
        {
            system("cls");
            return 0;
        }
        break;
        default:
        {
            cout << "Wybrales nieprawidlowy numer." << endl;
            Sleep(1500);
        }
        }
    }
}

int main()
{
    vector<Uzytkownik> uzytkownicy(0);
    uzytkownicy = wczytajUzytkownikow();
    int idZalogowanegoUzytkownika = 0;
    char wybor;
    while (1)
    {
        if(idZalogowanegoUzytkownika == 0)
        {
            system("cls");
            cout << "1. Rejestracja" << endl;
            cout << "2. Logowanie" << endl;
            cout << "9. Zakoncz program" << endl;
            cout << "Twoj wybor: ";
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
                cout << "Wybrales nieprawidlowy numer." << endl;
                Sleep(1500);
            }
            }
        }
        else
        {
            system("cls");
            idZalogowanegoUzytkownika = uruchomKsiazkeAdresowa(uzytkownicy, idZalogowanegoUzytkownika);
        }
    }
    return 0;
}
