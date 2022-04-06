#include <iostream>
#include <vector>

using namespace std ;
int no_contracte ;

class Contract {
    string numar_contract ;
    int an ;
    string beneficiar ;
    string furnizor ;
    int valoare ;
public :
    Contract(string nr = "NULL" , int a = 0 , string b = "NULL" , string f = "NULL" , int v = 0 ) {
        numar_contract = nr ;
        an = a ;
        beneficiar = b ;
        furnizor = f ;
        valoare = v ;
    }
    virtual ~Contract() {
        this->numar_contract = "";
        this->beneficiar = "" ;
        this->furnizor = "" ;
    }
    void set_numar_contract(string) ;
    void set_an(int) ;
    void set_beneficiar(string);
    void set_furnizor(string);
    void set_valoare(int) ;
    string get_numar_contract() ;
    int get_an() ;
    string get_beneficiar() ;
    string get_furnizor() ;
    int get_valoare() ;
    void operator = (Contract& ) ;
    friend istream& operator >> (istream&, Contract&);
    friend ostream& operator << (ostream&, Contract&);
    virtual void citire(istream&);
    virtual void afisare(ostream&);
};

void Contract::operator=(Contract &c) {
    this->set_numar_contract(c.get_numar_contract()) ;
    this->set_an(c.get_an()) ;
    this->set_beneficiar(c.get_beneficiar()) ;
    this->set_furnizor(c.get_furnizor()) ;
    this->set_valoare(c.get_valoare()) ;
}

void Contract::set_numar_contract(string nr) {
    numar_contract = nr ;
}

void Contract::set_an(int a){
    an = a ;
}

void Contract::set_beneficiar(string b) {
    beneficiar = b ;
}

void Contract::set_furnizor(string f) {
    furnizor = f ;
}

void Contract::set_valoare(int v)  {
    valoare = v ;
}

string Contract::get_numar_contract() {
    return numar_contract ;
}
int Contract::get_an() {
    return an ;
}

string Contract::get_beneficiar() {
    return beneficiar ;
}

string Contract::get_furnizor() {
    return furnizor ;
}

int Contract::get_valoare() {
    return valoare ;
}

void Contract::citire(istream& in){
    cout << "Introduceti numarul de contract : " ;
    in >> this->numar_contract ;
    cout << "Introduceti anul in care a fost realizat contractul : " ;
    in >> this->an ;
    cout << "Introduceti numele beneficiarului : " ;
    in >> this->beneficiar ;
    cout << "Introduceti numele furnizorului : " ;
    in >> this->furnizor ;
    cout << "Introduceti valoarea contractului ( lei ) : " ;
    in >> this->valoare ;
}

istream& operator >> (istream& in, Contract& c) {
    c.citire(in) ;
    return in ;
}

void Contract::afisare (ostream& out) {
    out << endl ;
    out << "Date privind contractul numarul -- " << this->get_numar_contract() << endl ;
    out << "Realizat in -- " << this->get_an() << endl ;
    out << "Pentru beneficiarul -- " << this->get_beneficiar() << endl ;
    out << "De catre furnizorul -- " << this->get_furnizor() << endl ;
}

ostream& operator << (ostream& out, Contract& c) {
    c.afisare(out) ;
    return out ;
}

class ContractInchiriere : public Contract {
    int perioada ;
public :
    ContractInchiriere(string nr = "NULL" , int a = 0 , string b = "NULL" , string f = "NULL" , int v = 0 , int per = 0) : Contract(nr,a,b,f,v) {
       perioada = per ;
    }
    int get_perioada() ;
    void set_perioada(int) ;
    friend istream& operator >> (istream&, ContractInchiriere&);
    friend ostream& operator >> (ostream&, ContractInchiriere&);
    void citire(istream&) ;
    void afisare(ostream&) ;
};

int ContractInchiriere::get_perioada() {
    return perioada ;
}

void ContractInchiriere::set_perioada(int per) {
    perioada = per ;
}

void ContractInchiriere::citire(istream& in) {
    Contract::citire(in) ;
    cout << "Introduceti perioada ( luni ) de valabilitate a contractului : " ;
    in >> this->perioada ;
}

istream& operator >> (istream& in, ContractInchiriere& c) {
    c.citire(in) ;
    return in ;
}

void ContractInchiriere::afisare(ostream& out) {
    Contract::afisare(out) ;
    cout <<  "Cu valoarea totala de : -- " << this->perioada * this->get_valoare() << " unitati monetare" << endl ;
}

ostream& operator << (ostream& out, ContractInchiriere& c) {
    c.afisare(out) ;
    return out ;
}

class Dosar {
    ContractInchiriere *Contracte ;
    static int nr_contracte ;
public :
    Dosar() {
        Contracte = new ContractInchiriere[100] ;
        nr_contracte = 1 ;
    }
    ~Dosar() {
        delete []Contracte ;
    }
    static int get_nrContracte() ;
    static void set_nrContracte(int number);
    friend istream& operator >> (istream&, Dosar&) ;
    friend ostream& operator << (ostream&, Dosar&) ;
    void Citire() ;

};

int Dosar::nr_contracte = 1 ;

int Dosar::get_nrContracte() {
    return nr_contracte ;
}

void Dosar::set_nrContracte(int number) {
    nr_contracte = number ;
}

istream& operator >> (istream& in, Dosar& d) {
    cout << "Introduceti numarul de contracte de inchiere : " ;
    in >> no_contracte ;
    cout << endl ;
    for (int i = 1 ; i <= no_contracte ; ++i ) {
        ContractInchiriere c;
        cout << "Introduceti contractul de inchiriere cu numarul " << d.get_nrContracte() << endl;
        in >> c ;
        cout << endl ;
        d.Contracte[d.get_nrContracte()] = c ;
        d.set_nrContracte(d.get_nrContracte() + 1) ;
    }
    return in ;
}

ostream& operator << (ostream& out, Dosar& d) {
    for (int i = 1 ; i <= d.get_nrContracte() - 1; ++i ) {
        ContractInchiriere c ;
        c = d.Contracte[i] ;
        cout << c  ;
    }
}


int main() {
    ContractInchiriere c1("a",0,"a","a",0,1) ;
    //cout << c1 ;
    //c2 = c1 ;
    //cout << c2 ;
    //Dosar Dosar1;
    //cout << Dosar1.get_nrContracte();
    Dosar d ;
    cin >> d ;
    cout << d ;
}
