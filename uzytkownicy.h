#include <iostream>
#include <vector>

using namespace std;
class Uzytkownik
{
    public:
    int idUzytkownika;
    string login, haslo;
    void zapiszUzytkownika(Uzytkownik nowyUzytkownik);
    void wczytajUzytkownikow(vector <Uzytkownik> &uzytkownicy);
    void rejestracja (vector<Uzytkownik> &uzytkownicy);
    int logowanie(vector<Uzytkownik> &uzytkownicy);
};


