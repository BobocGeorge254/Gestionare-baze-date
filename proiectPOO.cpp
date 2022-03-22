#include <iostream>
#include <cstring>
#include <vector>
#include <stdlib.h>
#include <time.h>

using namespace std ;

int atoi(string s){
    int numar = 0 , p = 1 ;
    for (int i = s.size() - 1 ; i >= 0 ; --i ){
        numar += p * ( s[i] - '0' );
        p *= 10;
    }
    return numar ;
}

class persoana {
    string nume;
    int an_nastere;
    char gen;
public :
    void set_nume(string) ;
    string get_nume();
    void set_an_nastere(int);
    int get_an_nastere();
    void set_gen(char);
    char get_gen();
};

void persoana::set_nume(string name) {
    nume = name;
}

string persoana::get_nume() {
    return nume;
}

void persoana::set_an_nastere(int an) {
    an_nastere = an ;
}

int persoana::get_an_nastere() {
    return an_nastere ;
}

void persoana::set_gen(char gender) {
    gen = gender;
}

char persoana::get_gen() {
    return gen;
}

class baza_de_date {
    vector <persoana> v;
    int nr_persoane ;
public :
    baza_de_date() {
        nr_persoane = 0;
    }
    ~baza_de_date() {
        v.clear();
    }
    void adauga(persoana);
    void sterge(string);
    void sterge(int);
    void sterge(char);
    void sterge(string, int);
    void sterge(string, char);
    void sterge(int, char);
    void sterge(string, int, char);
    void query(string);
    void query(int);
    void query(char);
    void query(string, int);
    void query(string, char);
    void query(int, char);
    void query(string, int, char);
    friend ostream& operator << (ostream&, baza_de_date&) ;
    operator persoana();
    void operator= (persoana);

};

void baza_de_date ::operator= (persoana p) {
    this->v.push_back(p);
    nr_persoane ++ ;
}

baza_de_date::operator persoana() {
    if ( nr_persoane > 0 )
        return v[0]; //implicit prima persoana
}

void baza_de_date::adauga(persoana p) {
    this->v.push_back(p);
    nr_persoane ++ ;
}

void baza_de_date::sterge(string name) {
    for (int i = 0 ; i < this->v.size(); ++i )
        if ( this->v[i].get_nume() == name )
            this->v.erase(v.begin() + i);
}

void baza_de_date::sterge(int an) {
    for (int i = 0 ; i < this->v.size(); ++i )
        if ( this->v[i].get_an_nastere() == an )
            this->v.erase(v.begin() + i);
}

void baza_de_date::sterge(char gender) {
    for (int i = 0 ; i < this->v.size(); ++i )
        if ( this->v[i].get_gen() == gender )
            this->v.erase(v.begin() + i);
}

void baza_de_date::sterge(string name, int an) {
    for (int i = 0 ; i < this->v.size(); ++i )
        if ( this->v[i].get_nume() == name &&  this->v[i].get_an_nastere() == an )
            this->v.erase(v.begin() + i);
}

void baza_de_date::sterge(string name, char gender) {
    for (int i = 0 ; i < this->v.size(); ++i )
        if ( this->v[i].get_nume() == name &&  this->v[i].get_gen() == gender )
            this->v.erase(v.begin() + i);
}

void baza_de_date::sterge(int an, char gender) {
    for (int i = 0 ; i < this->v.size(); ++i )
        if ( this->v[i].get_an_nastere() == an &&  this->v[i].get_gen() == gender )
            this->v.erase(v.begin() + i);
}

void baza_de_date::sterge(string name, int an, char gender) {
    for (int i = 0 ; i < this->v.size(); ++i )
        if ( this->v[i].get_nume() == name &&  this->v[i].get_an_nastere() == an && this->v[i].get_gen() == gender)
            this->v.erase(v.begin() + i);
}

void baza_de_date::query(string name) {
    short ct = 0 ;
    string gender ;
    for (int i = 0 ; i < this->v.size(); ++i )
        if ( this->v[i].get_nume() == name ) {
            ct ++ ;
            if (this->v[i].get_gen() == 'M')
                gender = "barbat";
            else
                gender = "femeie";
            cout << "Nume : " << this->v[i].get_nume() << " - " << this->v[i].get_an_nastere() << " - " << gender
                 << '\n';
        }
    if ( ct == 0 ) {
        cout << "In baza de date nu se afla persoane cu aceste atribute. Incercati din nou" ;
    }
}

void baza_de_date::query(int an) {
    short ct = 0 ;
    string gender ;
    for (int i = 0 ; i < this->v.size(); ++i )
        if ( this->v[i].get_an_nastere() == an ) {
            ct ++ ;
            if (this->v[i].get_gen() == 'M')
                gender = "barbat";
            else
                gender = "femeie";
            cout << "Nume : " << this->v[i].get_nume() << " - " << this->v[i].get_an_nastere() << " - " << gender
                 << '\n';
        }
    if ( ct == 0 ) {
        cout << "In baza de date nu se afla persoane cu aceste atribute. Incercati din nou" ;
    }
}

void baza_de_date::query(char Gender) {
    short ct = 0 ;
    string gender ;
    for (int i = 0 ; i < this->v.size(); ++i )
        if ( this->v[i].get_gen() == Gender ) {
            ct ++ ;
            if (this->v[i].get_gen() == 'M')
                gender = "barbat";
            else
                gender = "femeie";
            cout << "Nume : " << this->v[i].get_nume() << " - " << this->v[i].get_an_nastere() << " - " << gender
                 << '\n';
        }
    if ( ct == 0 ) {
        cout << "In baza de date nu se afla persoane cu aceste atribute. Incercati din nou" ;
    }

}

void baza_de_date::query(string name, int an) {
    short ct = 0 ;
    string gender ;
    for (int i = 0 ; i < this->v.size(); ++i )
        if ( this->v[i].get_nume() == name &&  this->v[i].get_an_nastere() == an ) {
            ct ++ ;
            if (this->v[i].get_gen() == 'M')
                gender = "barbat";
            else
                gender = "femeie";
            cout << "Nume : " << this->v[i].get_nume() << " - " << this->v[i].get_an_nastere() << " - " << gender
                 << '\n';
        }
    if ( ct == 0 ) {
        cout << "In baza de date nu se afla persoane cu aceste atribute. Incercati din nou" ;
    }

}

void baza_de_date::query(string name, char Gender) {
    short ct = 0 ;
    string gender ;
    for (int i = 0 ; i < this->v.size(); ++i )
        if ( this->v[i].get_nume() == name &&  this->v[i].get_gen() == Gender ) {
            ct ++ ;
            if (this->v[i].get_gen() == 'M')
                gender = "barbat";
            else
                gender = "femeie";
            cout << "Nume : " << this->v[i].get_nume() << " - " << this->v[i].get_an_nastere() << " - " << gender
                 << '\n';
        }
    if ( ct == 0 ) {
        cout << "In baza de date nu se afla persoane cu aceste atribute. Incercati din nou" ;
    }
}

void baza_de_date::query(int an, char Gender) {
    short ct = 0 ;
    string gender ;
    for (int i = 0 ; i < this->v.size(); ++i )
        if ( this->v[i].get_an_nastere() == an &&  this->v[i].get_gen() == Gender ) {
            ct ++ ;
            if (this->v[i].get_gen() == 'M')
                gender = "barbat";
            else
                gender = "femeie";
            cout << "Nume : " << this->v[i].get_nume() << " - " << this->v[i].get_an_nastere() << " - " << gender
                 << '\n';
        }
    if ( ct == 0 ) {
        cout << "In baza de date nu se afla persoane cu aceste atribute. Incercati din nou" ;
    }

}

void baza_de_date::query(string name, int an, char Gender) {
    short ct = 0 ;
    string gender ;
    for (int i = 0 ; i < this->v.size(); ++i )
        if ( this->v[i].get_nume() == name &&  this->v[i].get_an_nastere() == an && this->v[i].get_gen() == Gender){
            ct ++ ;
            if (this->v[i].get_gen() == 'M')
                gender = "barbat";
            else
                gender = "femeie";
            cout << "Nume : " << this->v[i].get_nume() << " - " << this->v[i].get_an_nastere() << " - " << gender
                 << '\n';
        }
    if ( ct == 0 ) {
        cout << "In baza de date nu se afla persoane cu aceste atribute. Incercati din nou" ;
    }

}


bool key(persoana a, persoana b) {
    return a.get_an_nastere() < b.get_an_nastere() ;
}

ostream& operator << (ostream& out, baza_de_date& b) {
    sort(b.v.begin(), b.v.end(), key);
    out << "--------In acest moment in baza de date se afla---------" << endl ;
    string gender;
    for (int i = 0; i < b.v.size(); ++i) {
        if (b.v[i].get_gen() == 'M')
            gender = "barbat";
        else
            gender = "femeie";
        out << "Nume : " << b.v[i].get_nume() << " - " << b.v[i].get_an_nastere() << " - " << gender
            << '\n';
    }
    return out;
}

void AfisareInformatii(){
    cout << endl << "Operatii posibile : " << endl << "1. Adaugarea unui om in baza de date - prin codul de comanda -- add"
         << endl;
    cout << "2. Stergerea unui om din baza de date - prin codul de comanda -- delete" << endl;
    cout << "3. Interogarea bazei de date - prin codul de comanda -- query" << endl;
    cout << "4. Afisarea bazei de date - prin codul de comanda -- print" << endl ;
    cout << "5.Inchidere aplicatie - print codul de comanda -- exit" << endl ;
}

int main() {
    cout << "-----------Program gestiune baze de date-----------------" << endl;
    cout << endl << "Operatii posibile : " << endl << "1. Adaugarea unui om in baza de date - prin codul de comanda -- add"
         << endl;
    cout << "2. Stergerea unui om din baza de date - prin codul de comanda -- delete" << endl;
    cout << "3. Interogarea bazei de date - prin codul de comanda -- query" << endl;
    cout << "4. Afisarea bazei de date - print codul de comanda -- print" << endl ;
    cout << "5.Inchidere aplicatie - print codul de comanda -- exit" << endl ;
    string comanda, nume_de_familie, prenume, cod, cod1, cod2, an_string;
    int an;
    persoana p;
    baza_de_date b;
    char gender;
    while (true) {
        cout << endl << "Introduceti codul operatiei : ";
        cin >> comanda;
        if (comanda == "exit" || comanda == "EXIT") {
            break;
        }
        else if (comanda == "add") {
            cout << "Introduceti numele de familie al persoanei : " << " ";
            cin >> nume_de_familie;
            //cin>>p.nume_de_familie;
            cout << "Introduceti prenumele persoanei : " << " ";
            cin >> prenume;
            p.set_nume(nume_de_familie + " " + prenume);
            cout << "Introduceti anul nasterii persoanei : " << " ";
            cin >> an_string;
            bool ok = true ;
            for (int i = 0 ; i <an_string.size(); ++i)
                if (an_string[i] < '0' || an_string[i] > '9')
                    ok = false ;
            if (ok == true) {
                an = atoi(an_string) ;
                p.set_an_nastere(an);
                cout << "Introduceti genul persoanei (M/F) : " << " ";
                cin >> gender;
                if (gender != 'M' && gender != 'F') {
                    cout << "---------Invalid. Reia operatia------------ ";
                    AfisareInformatii();
                } else {
                    p.set_gen(gender);
                    b.adauga(p);
                    cout << endl << "---------Adaugat cu succes-----------" << endl;
                    AfisareInformatii();
                }
            }
            else {
                cout << "---------Invalid. Reia operatia------------ ";
                AfisareInformatii();
            }
        }
        else if (comanda == "delete" || comanda == "DELETE") {
            int numar;
            cout << "------Optiuni de stergere---------" << endl;
            cout << "Stergerea unei persoane dupa nume - prin codul de comanda -- nume" << endl;
            cout << "Stergerea unei persoane dupa anul nasterii - prin codul de comanda -- an" << endl;
            cout << "Stergerea unei persoane dupa gen - prin codul de comanda -- gen " << endl;
            cout << "Stergerea unei persoane dupa mai multe atribute" << endl ;
            cout << "Introduceti numarul de atribute dupa care se face stergerea : ";
            cin >> numar;
            if (numar == 1) {
                cout << "Introduceti atributul dupa care doriti sa se faca stergerea : " ;
                cin >> cod;
                if (cod == "nume") {
                    cout << "Introduceti numele de familie al persoanei/persoanelor pe care vrei sa le elimini  : ";
                    cin >> nume_de_familie;
                    cout << "Introduceti prenumele persoanei/persoanelor pe care vrei sa le elimini : ";
                    cin >> prenume;
                    b.sterge(nume_de_familie + " " + prenume);
                    cout << "-----------------Stergere realizata cu succes------------------";
                    AfisareInformatii() ;

                } else if (cod == "an") {
                    cout << "Introduceti anul de nastere persoanei/persoanelor pe care vrei sa le elimini : ";
                    cin >> an_string;
                    bool ok = true ;
                    for (int i = 0 ; i <an_string.size(); ++i)
                        if (an_string[i] < '0' || an_string[i] > '9')
                            ok = false ;
                    if ( ok == true ) {
                        an = atoi(an_string);
                        b.sterge(an);
                        cout << "-----------------Stergere realizata cu succes------------------";
                        AfisareInformatii();
                    }
                    else {
                        cout << "---------Invalid. Reia operatia------------ ";
                        AfisareInformatii();
                    }

                } else if (cod == "gen") {
                    cout << "Introduceti genul al persoanei/persoanelor pe care vrei sa le elimini (M/F): ";
                    cin >> gender;
                    b.sterge(gender);
                    cout << "-----------------Stergere realizata cu succes------------------";
                    AfisareInformatii() ;

                } else {
                    cout << "---------Cod invalid. Reia operatia------------ ";
                    AfisareInformatii();
                }
            }
            else if (numar == 2) {
                cout << "Introduceti primul atribut dupa care doriti sa se faca stergerea : " ;
                cin >> cod1 ;
                cout << "Introduceti primul atribut dupa care doriti sa se faca stergerea : " ;
                cin >> cod2 ;
                if ( (cod1 == "nume" && cod2 == "an") || (cod2 == "nume" && cod1 == "an")) {
                    cout << "Introduceti numele de familie al persoanei/persoanelor pe care vrei sa le elimini  : ";
                    cin >> nume_de_familie;
                    cout << "Introduceti prenumele persoanei/persoanelor pe care vrei sa le elimini : ";
                    cin >> prenume;
                    cout << "Introduceti anul de nastere persoanei/persoanelor pe care vrei sa le elimini : ";
                    cin >> an_string ;
                    bool ok = true ;
                    for (int i = 0 ; i <an_string.size(); ++i)
                        if (an_string[i] < '0' || an_string[i] > '9')
                            ok = false ;
                    if (ok == true) {
                        an = atoi(an_string);
                        b.sterge(nume_de_familie + " " + prenume, an);
                        cout << "-----------------Stergere realizata cu succes------------------";
                        AfisareInformatii();
                    }
                    else {
                        cout << "------------Invalid. Reia operatia------------ ";
                        AfisareInformatii();
                    }

                }
                else if ( (cod1 == "nume" && cod2 == "gen") || (cod2 == "nume" && cod1 == "gen")) {
                    cout << "Introduceti numele de familie al persoanei/persoanelor pe care vrei sa le elimini  : ";
                    cin >> nume_de_familie;
                    cout << "Introduceti prenumele persoanei/persoanelor pe care vrei sa le elimini : ";
                    cin >> prenume;
                    cout << "Introduceti genul persoanei/persoanelor pe care vrei sa le elimini (M/F): ";
                    cin >> gender;
                    b.sterge(nume_de_familie + " " + prenume, gender) ;
                    cout << "-----------------Stergere realizata cu succes------------------";
                    AfisareInformatii() ;
                }
                else if ( (cod1 == "an" && cod2 == "gen") || (cod2 == "an" && cod1 == "gen")) {
                    cout << "Introduceti anul de nastere persoanei/persoanelor pe care vrei sa le elimini : ";
                    cin >> an_string;
                    bool ok = true ;
                    for (int i = 0 ; i <an_string.size(); ++i)
                        if (an_string[i] < '0' || an_string[i] > '9')
                            ok = false ;
                    if ( ok == true ) {
                        an = atoi(an_string);
                        cout << "Introduceti genul persoanei/persoanelor pe care vrei sa le elimini (M/F): ";
                        cin >> gender;
                        b.sterge(an, gender);
                        cout << "-----------------Stergere realizata cu succes------------------";
                        AfisareInformatii();
                    }
                    else {
                        cout << "------------Invalid. Reia operatia------------ ";
                        AfisareInformatii();
                    }
                }
                else {
                    cout << "---------Cod invalid. Reia operatia------------ ";
                    AfisareInformatii();
                }
            }
            else if (numar == 3) {
                cout << "Introduceti numele de familie al persoanei/persoanelor pe care vrei sa le elimini  : ";
                cin >> nume_de_familie;
                cout << "Introduceti prenumele persoanei/persoanelor pe care vrei sa le elimini : ";
                cin >> prenume;
                cout << "Introduceti anul de nastere persoanei/persoanelor pe care vrei sa le elimini : ";
                cin >> an_string;
                bool ok = true ;
                for (int i = 0 ; i <an_string.size(); ++i)
                    if (an_string[i] < '0' || an_string[i] > '9')
                        ok = false ;
                if ( ok == true ) {
                    an = atoi(an_string) ;
                    cout << "Introduceti genul persoanei/persoanelor pe care vrei sa le elimini (M/F): ";
                    cin >> gender;
                    b.sterge(nume_de_familie + " " + prenume, an, gender);
                    cout << "-----------------Stergere realizata cu succes------------------";
                    AfisareInformatii();
                }
                else {
                    cout << "------------Invalid. Reia operatia------------ ";
                    AfisareInformatii();
                }
            }
            else {
                cout << "---------Numar invalid de atribute. Reia operatia---------";
                AfisareInformatii();
            }
        }
        else if (comanda == "print" || comanda == "PRINT") {
            cout << endl;
            cout << b;
            cout << endl ;
            AfisareInformatii() ;
        }
        else if (comanda == "query" || comanda == "QUERY") {
            int numar ;
            cout << "-----------Optiuni de interogare-------------" << endl ;
            cout << "Interogarea unei persoane dupa nume - prin codul de comanda -- nume" << endl;
            cout << "Interogare unei persoane dupa anul nasterii - prin codul de comanda -- an" << endl;
            cout << "Interogarea unei persoane dupa gen - prin codul de comanda -- gen " << endl;
            cout << "Interogarea unei persoane dupa mai multe atribute" << endl ;
            cout << "Introduceti numarul de atribute dupa care se face interogarea : ";
            cin >> numar;
            if (numar == 1) {
                cout << "Introduceti atributul dupa care doriti sa se faca interogarea : " ;
                cin >> cod;
                if (cod == "nume") {
                    cout << "Introduceti numele de familie al persoanei/persoanelor pe care vrei sa le interoghezi  : ";
                    cin >> nume_de_familie;
                    cout << "Introduceti prenumele persoanei/persoanelor pe care vrei sa le interoghezi : ";
                    cin >> prenume;
                    b.query(nume_de_familie + " " + prenume);
                    AfisareInformatii() ;

                } else if (cod == "an") {

                    cout << "Introduceti anul de nastere persoanei/persoanelor pe care vrei sa le interoghezi : ";
                    cin >> an_string;
                    bool ok = true ;
                    for (int i = 0 ; i <an_string.size(); ++i)
                        if (an_string[i] < '0' || an_string[i] > '9')
                            ok = false ;
                    if ( ok == true ) {
                        an = atoi(an_string) ;
                        b.query(an);
                        AfisareInformatii() ;
                    }
                    else {
                        cout << "------------Invalid. Reia operatia------------ ";
                        AfisareInformatii();
                    }

                } else if (cod == "gen") {
                    cout << "Introduceti genul al persoanei/persoanelor pe care vrei sa le interoghezi (M/F) : ";
                    cin >> gender;
                    b.query(gender);
                    AfisareInformatii() ;

                } else {
                    cout << "---------Cod invalid. Reia operatia------------ ";
                    AfisareInformatii();
                }
            }
            else if (numar == 2) {
                cout << "Introduceti primul atribut dupa care doriti sa se faca interogarea : ";
                cin >> cod1;
                cout << "Introduceti al doilea atribut dupa care doriti sa se faca interogarea : ";
                cin >> cod2;
                if ((cod1 == "nume" && cod2 == "an") || (cod2 == "nume" && cod1 == "an")) {
                    cout << "Introduceti numele de familie al persoanei/persoanelor pe care vrei sa le interoghezi  : ";
                    cin >> nume_de_familie;
                    cout << "Introduceti prenumele persoanei/persoanelor pe care vrei sa le interoghezi : ";
                    cin >> prenume;
                    cout << "Introduceti anul de nastere persoanei/persoanelor pe care vrei sa le interoghezi : ";
                    cin >> an_string;
                    bool ok = true;
                    for (int i = 0; i < an_string.size(); ++i)
                        if (an_string[i] < '0' || an_string[i] > '9')
                            ok = false;
                    if (ok == true) {
                        an = atoi(an_string);
                        b.query(nume_de_familie + " " + prenume, an);
                        AfisareInformatii();
                    } else {
                        cout << "------------Invalid. Reia operatia------------ ";
                        AfisareInformatii();
                    }
                } else if ((cod1 == "nume" && cod2 == "gen") || (cod2 == "nume" && cod1 == "gen")) {
                    cout << "Introduceti numele de familie al persoanei/persoanelor pe care vrei sa le interoghezi  : ";
                    cin >> nume_de_familie;
                    cout << "Introduceti prenumele persoanei/persoanelor pe care vrei sa le interoghezi : ";
                    cin >> prenume;
                    cout << "Introduceti genul persoanei/persoanelor pe care vrei sa le interoghezi (M/F): ";
                    cin >> gender;
                    b.query(nume_de_familie + " " + prenume, gender);
                    AfisareInformatii();
                } else if ((cod1 == "an" && cod2 == "gen") || (cod2 == "an" && cod1 == "gen")) {
                    cout << "Introduceti anul de nastere persoanei/persoanelor pe care vrei sa le interoghezi : ";
                    cin >> an_string;
                    bool ok = true;
                    for (int i = 0; i < an_string.size(); ++i)
                        if (an_string[i] < '0' || an_string[i] > '9')
                            ok = false;
                    if (ok == true) {
                        an = atoi(an_string);
                        cout << "Introduceti genul persoanei/persoanelor pe care vrei sa le interoghezi (M/F) : ";
                        cin >> gender;
                        b.query(an, gender);
                        AfisareInformatii();
                    } else {
                        cout << "---------Cod invalid. Reia operatia------------ ";
                        AfisareInformatii();
                    }
                }
            }
            else if (numar == 3) {
                cout << "Introduceti numele de familie al persoanei/persoanelor pe care vrei sa le interoghezi  : ";
                cin >> nume_de_familie;
                cout << "Introduceti prenumele persoanei/persoanelor pe care vrei sa le interoghezi : ";
                cin >> prenume;
                cout << "Introduceti anul de nastere persoanei/persoanelor pe care vrei sa le interoghezi : ";
                cin >> an_string;
                bool ok = true;
                for (int i = 0; i < an_string.size(); ++i)
                    if (an_string[i] < '0' || an_string[i] > '9')
                        ok = false;
                if ( ok == true ) {
                    an = atoi(an_string);
                    cout << "Introduceti genul persoanei/persoanelor pe care vrei sa le interoghezi (M/F): ";
                    cin >> gender;
                    b.query(nume_de_familie + " " + prenume, an, gender);
                    AfisareInformatii();
                }
                else {
                    cout << "---------Cod invalid. Reia operatia------------ ";
                    AfisareInformatii();
                }
            }
            else {
                cout << "---------Numar invalid de atribute. Reia operatia---------";
                AfisareInformatii();
            }

        }
        else {
            cout << "---------Cod invalid. Reia operatia------------ ";
            AfisareInformatii();
        }
    }/*
    persoana p;
    p.set_nume("Boboc George");
    p.set_an_nastere(2003);
    p.set_gen('M');

    /*
    Partea intai // overload pe operator de atribuire
    baza_de_date b;
    b = p;
    cout << b;
     */

    /*Partea a doua // operator de cast
    baza_de_date b;
    b.adauga(p);
    persoana q = b;
    cout << q.get_nume() << " " << q.get_an_nastere() << " "  << q.get_gen();//OKAY
     */


}
