#include <iostream>
#include <vector>
#include <exception>

using namespace std ;
int no_contracte ;

int notValid(string s) {
    for (int i = 0 ; i < s.size(); ++i)
        if (!isdigit(s[i]))
            return true ;
    return false ;
}

int atoi(string s) {
    int numar = 0 , p = 1 ;
    for (int i = s.size() - 1 ; i >= 0 ; --i ){
        numar += p * ( s[i] - '0' );
        p *= 10;
    }
    return numar ;
}

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
    cout << "Introduceti numarul de contract : ";
    in >> this->numar_contract;
    bool loop = false ;
    while ( !loop ) {
        try {
            string input;
            cout << "Introduceti anul in care a fost realizat contractul : ";
            in >> input;
            if (notValid(input))
                throw 503;
            else {
                this->an = atoi(input);
                loop = true;
            }
        }
        catch (int c) {
            cout << endl << "Erorr " << c << "(expected integer). Try again." << endl;
        }
    }
    cout << "Introduceti numele beneficiarului : " ;
    in >> this->beneficiar ;
    cout << "Introduceti numele furnizorului : " ;
    in >> this->furnizor ;
    loop = false ;
    while ( !loop ) {
        try {
            string input;
            cout << "Introduceti valoarea contractului (lei) : ";
            in >> input;
            if (notValid(input))
                throw 503;
            else {
                this->valoare = atoi(input);
                loop = true;
            }
        }
        catch (int c) {
            cout << endl << "Erorr " << c << "(expected integer). Try again." << endl;
        }
    }
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
    bool loop = false ;
    while ( !loop ) {
        try {
            string input;
            //cout << "Introduceti anul in care a fost realizat contractul : ";
            cout << "Introduceti perioada ( luni ) de valabilitate a contractului : " ;
            in >> input;
            if (notValid(input))
                throw 503;
            else {
                this->perioada = atoi(input);
                loop = true;
            }
        }
        catch (int c) {
            cout << endl << "Erorr " << c << "(expected integer). Try again." << endl;
        }
    }
}

istream& operator >> (istream& in, ContractInchiriere& c) {
    c.citire(in) ;
    return in ;
}

void ContractInchiriere::afisare(ostream& out) {
    Contract::afisare(out) ;
    cout <<  "Cu valoarea totala de : -- " << this->perioada * this->get_valoare() << " unitati monetare" << endl ;
    cout << endl ;
}

ostream& operator << (ostream& out, ContractInchiriere& c) {
    c.afisare(out) ;
    return out ;
}

class Dosar {
    ContractInchiriere *Contracte[100] ;
    static int nr_contracte ;
public :
    Dosar() {
        *Contracte = new ContractInchiriere[100] ;
        nr_contracte = 1 ; // nu ca ar functiona
    }
    ~Dosar() {
        delete []*Contracte ;
    }
    static int get_nrContracte() ;
    static void set_nrContracte(int number);
    friend istream& operator >> (istream&, Dosar&) ;
    friend ostream& operator << (ostream&, Dosar&) ;
    void Citire() ;
    void SearchByNumber(string);
    void SearchByYear(int);
    void printBeneficiari();
    void printFurnizori();

};

void Dosar::SearchByNumber(string number) {
    bool found = 0 ;
    for ( int i = 1 ; i <= this->get_nrContracte() - 1 ; ++i ) {
        ContractInchiriere *c = this->Contracte[i] ;
        if ( (*c).get_numar_contract() == number ) {
            cout << *c;
            found = 1;
        }
    }
    if ( found == 0 )
        cout << "------------Nu exista--------------" << endl ;
}

void Dosar::SearchByYear(int an) {
    bool found = 0 ;
    for ( int i = 1 ; i <= this->get_nrContracte() - 1 ; ++i ) {
        ContractInchiriere *c = this->Contracte[i] ;
        if ( (*c).get_an() == an ) {
            cout << *c;
            found = 1;
        }
    }
    if ( found == 0 )
        cout << "------------Nu exista--------------" << endl ;
}

void Dosar::printBeneficiari() {
    cout << "------Lista de beneficiari-----------" << endl ;
    for ( int i = 1 ; i <= this->get_nrContracte() - 1 ; ++i ) {
        ContractInchiriere *c = this->Contracte[i] ;
        cout << i << "- " << (*c).get_beneficiar() << endl ;
    }
}

void Dosar::printFurnizori() {
    cout << "------Lista de furnizori-----------" << endl ;
    for ( int i = 1 ; i <= this->get_nrContracte() - 1 ; ++i ) {
        ContractInchiriere *c = this->Contracte[i] ;
        cout << i << "- " << (*c).get_furnizor() << endl ;
    }
}

int Dosar::nr_contracte = 1 ;

int Dosar::get_nrContracte() {
    return nr_contracte ;
}

void Dosar::set_nrContracte(int number) {
    nr_contracte = number ;
}

void vector_n_contracte(int nr_elemente) {
    Contract **vector = static_cast <Contract**> (malloc(sizeof(Contract *) * nr_elemente));
    for ( int i = 0 ; i < nr_elemente ; i++ ){
        vector[i] = new ContractInchiriere("NULL" , 0 , "NULL", "NULL" , 0 , 0);
        ContractInchiriere *pInchiriere = dynamic_cast <ContractInchiriere*> (vector[i]);
        cin >> *pInchiriere ;
        cout << *pInchiriere << '\n';
    }
}

ContractInchiriere c[100];
istream& operator >> (istream& in, Dosar& d) {
    cout << "Introduceti numarul de contracte de inchiere : " ;
    in >> no_contracte ;
    cout << endl ;
    for (int i = 1 ; i <= no_contracte ; ++i ) {
        cout << "Introduceti contractul de inchiriere cu numarul " << d.get_nrContracte() << endl;
        in >> c[i] ;
        cout << endl ;
        d.Contracte[d.get_nrContracte()] = &c[i] ;
        d.set_nrContracte(d.get_nrContracte() + 1) ;
    }
    return in ;
}

ostream& operator << (ostream& out, Dosar& d) {
    for (int i = 1; i <= d.get_nrContracte() - 1; ++i) {
        //ContractInchiriere *c ;
        //c = d.Contracte[i] ;
        //out << *c ;

        //Sper ca UPCAST
        Contract *p ; // asta e TOP-ul ierarhiei
        p = d.Contracte[i] ; //ii atribui un pointer catre un obiect din clasa derivata
        cout << *p ;

    }
    out << endl ;
    return out ;
}



int main() {
    //cout << c1 ;
    //c2 = c1 ;
    //cout << c2 ;
    //Dosar Dosar1;
    //cout << Dosar1.get_nrContracte();
    Dosar d ;
    cin >> d ;
    int operatie = 0 ;
    //vector_n_contracte(3);
    while ( operatie != 6 ) {
        cout << "---------------Alegeti operatia :" << endl;
        cout << "1 - Afisarea tuturor contractelor din dosarul curent" << endl;
        cout << "2 - Afisarea unui contract cu numar precizat din dosarul curent" << endl;
        cout << "3 - Afisarea unui contract cu anul precizat din dosarul curent" << endl;
        cout << "4 - Afisarea tuturor beneficiarilor din dosarul curent" << endl;
        cout << "5 - Afisarea tuturor furnizorilor din dosarul curent" << endl;
        cout << "6 - Exit" << endl;
        cout << "Introduceti operatia : ";
        cin >> operatie;
        cout << endl;
        if ( operatie == 1 ) cout << d ;
        else if ( operatie == 2 ) {
            string number ;
            cout << "Introduceti numarul de contract: " ;
            cin >> number ;
            d.SearchByNumber(number) ;

        }
        else if ( operatie == 3 ) {
            int an ;
            bool loop = false ;
            while ( !loop ) {
                try {
                    string input;
                    //cout << "Introduceti anul in care a fost realizat contractul : ";
                    cout << "Introduceti anul in care a fost inceput contractul: " ;
                    cin >> input;
                    if (notValid(input))
                        throw 503;
                    else {
                        d.SearchByYear(atoi(input)) ;;
                        loop = true;
                    }
                }
                catch (int c) {
                    cout << endl << "Erorr " << c << "(expected integer). Try again." << endl;
                }
            }
        }
        else if ( operatie == 4 ) d.printBeneficiari() ;
        else if ( operatie == 5 ) d.printFurnizori() ;
        else if ( operatie == 6 ) exit(0) ;
        else
            cout << "-----------Operatie invalida. Incearca din nou--------------" << endl ;

    }
}
