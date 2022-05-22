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


#include <iostream>
#include <vector>

using namespace std ;

class bilet
{
protected:
    string statiePlecare ;
    string statieSosire ;
    int ziPlecare ;
    int lunaPlecare ;
    int anPlecare ;
    int oraPlecare ;
    string codTren ;
    int durata ;
    int distanta ;
    float pret ;
    int clasa ;
    static int id_bilet ;
    string cod_bilet ;
public:
    bilet (string statiePlecare= "" ,string statieSosire= "" ,int ziPlecare = 0,int lunaPlecare = 0,int anPlecare = 0,int oraPlecare = 0,string codTren= "" ,int durata = 0,int distanta = 0,float pret = 0, int clasa = 0, string cod_bilet = ""){
        this -> statiePlecare = statiePlecare ;
        this -> statieSosire = statieSosire ;
        this -> ziPlecare = ziPlecare ;
        this -> lunaPlecare = lunaPlecare ;
        this -> anPlecare = anPlecare ;
        this -> oraPlecare = oraPlecare ;
        this -> codTren = codTren ;
        this -> durata = durata ;
        this -> distanta = distanta ;
        this -> pret = pret ;
        this -> clasa = clasa ;
        this -> cod_bilet = cod_bilet ;
        ++id_bilet ;
    }
    virtual ~bilet() {
        statiePlecare = statieSosire = codTren = "" ;
        ziPlecare = lunaPlecare = anPlecare = oraPlecare = durata = distanta = pret = clasa = 0 ;
        --id_bilet ;
    }
    void citire(istream&);
    void afisare(ostream&);
    friend istream& operator>> (istream&, bilet&);
    friend ostream& operator<< (ostream&, bilet&);
    string get_statiePlecare () ;
    string get_statieSosire () ;
    int get_ziPlecare () ;
    int get_lunaPlecare () ;
    int get_anPlecare () ;
    int get_oraPlecare () ;
    string get_codTren () ;
    int get_durata () ;
    int get_distanta () ;
    virtual float get_pret () ;
    int get_clasa();
    //static int get_idBilet() ;
    virtual string get_codBilet() ;
    void set_statiePlecare (string) ;
    void set_statieSosire (string) ;
    void set_ziPlecare (int) ;
    void set_lunaPlecare (int) ;
    void set_anPlecare (int) ;
    void set_oraPlecare (int) ;
    void set_codTren (string) ;
    void set_durata (int) ;
    void set_distanta (int) ;
    virtual void set_pret (float) ;
    void set_clasa(int) ;
    //static void set_idBilet(int) ;
};

int bilet::id_bilet = 0 ;

void bilet::citire(istream& in){
    cout << "Statie plecare: "  ;
    in >> this -> statiePlecare ;
    cout << "Statie sosire: "  ;
    in >> this -> statieSosire ;
    while(true) {
        try {
            cout << "Zi plecare: ";
            in >> this->ziPlecare;
            if (this->ziPlecare > 31)
                throw string("Zi invalida");
            else break;
        }
        catch (string s) {
            cout << s << endl ;
        }
    }
    while(true) {
        try {
            cout << "Luna plecare: ";
            in >> this->lunaPlecare;
            if (this->lunaPlecare > 12)
                throw string("Luna invalida");
            else break;
        }
        catch (string s) {
            cout << s << endl ;
        }
    }
    cout << "An plecare: "  ;
    in >> this -> anPlecare ;
    cout << "Ora plecare: "  ;
    in >> this -> oraPlecare ;
    cout << "Cod tren: "  ;
    in >> this -> codTren ;
    cout << "Durata: "  ;
    in >> this -> durata ;
    cout << "Distanta: "  ;
    in >> this -> distanta ;
    cout << "Clasa: "  ;
    in >> this -> clasa ;
}

istream& operator>> (istream& in, bilet &ob) {
    ob.citire(in);
    return in;
}

void bilet::afisare(ostream& out){
    out << "Statie plecare: "  << this -> statiePlecare << endl ;
    out << "Statie sosire: "  << this -> statieSosire << endl ;
    out << "Zi plecare: "  << this -> ziPlecare << endl ;
    out << "Luna plecare: "  << this -> lunaPlecare << endl ;
    out << "An plecare: "  << this -> anPlecare << endl ;
    out << "Ora plecare: "  << this -> oraPlecare << endl ;
    out << "Cod tren: "  << this -> codTren << endl ;
    out << "Durata: "  << this -> durata << endl ;
    out << "Distanta: "  << this -> distanta << endl ;
    out << "Clasa: " << this -> clasa << endl ;
    out << "Pret: "  << this -> pret << endl ;
    out << "Cod: " << this -> cod_bilet << endl ;
}

ostream& operator<< (ostream& out, bilet&ob) {
    ob.afisare(out);
    return out;
}

void bilet::set_statiePlecare (string info){
    this -> statiePlecare = info ;
}

void bilet::set_statieSosire (string info){
    this -> statieSosire = info ;
}

void bilet::set_ziPlecare (int info){
    this -> ziPlecare = info ;
}

void bilet::set_lunaPlecare (int info){
    this -> lunaPlecare = info ;
}

void bilet::set_anPlecare (int info){
    this -> anPlecare = info ;
}

void bilet::set_oraPlecare (int info){
    this -> oraPlecare = info ;
}

void bilet::set_codTren (string info){
    this -> codTren = info ;
}

void bilet::set_durata (int info){
    this -> durata = info ;
}

void bilet::set_distanta (int info){
    this -> distanta = info ;
}

void bilet::set_pret (float info){
    this -> pret = info ;
}

void bilet::set_clasa(int clasa) {
    this -> clasa = clasa ;
}

/*
void bilet::set_idBilet(int id_bilet) {
    bilet::id_bilet = id_bilet ;
}*/

string bilet::get_statiePlecare (){
    return statiePlecare ;
}

string bilet::get_statieSosire (){
    return statieSosire ;
}

int bilet::get_ziPlecare (){
    return ziPlecare ;
}

int bilet::get_lunaPlecare (){
    return lunaPlecare ;
}

int bilet::get_anPlecare (){
    return anPlecare ;
}

int bilet::get_oraPlecare (){
    return oraPlecare ;
}

string bilet::get_codTren (){
    return codTren ;
}

int bilet::get_durata (){
    return durata ;
}

int bilet::get_distanta (){
    return distanta ;
}

float bilet::get_pret (){
    return pret ;
}

int bilet::get_clasa() {
    return clasa ;
}

string bilet::get_codBilet() {
    return cod_bilet ;
}

/*
int bilet::get_idBilet() {
    return id_bilet ;
}*/

class Regio : public bilet {
public:
    Regio(string statiePlecare= "" ,string statieSosire= "" ,int ziPlecare = 0,int lunaPlecare = 0,int anPlecare = 0,int oraPlecare = 0,string codTren= "" ,int durata = 0,int distanta = 0,float pret = 0, int clasa = 0, string cod_bilet = "") :
    bilet(statiePlecare, statieSosire, ziPlecare, lunaPlecare, anPlecare, oraPlecare, codTren, durata, distanta, pret, clasa, cod_bilet) {
        pret = get_pret() ;
        cod_bilet = get_codBilet() ;
    };
    friend istream& operator>> (istream& in, Regio& r) ;
    friend ostream& operator<< (ostream& out, Regio& r) ;
    float get_pret();
    string get_codBilet() ;
};

istream& operator>> (istream& in, Regio& r) {
    r.citire(in) ;
    r.pret = r.get_pret() ;
    r.cod_bilet = r.get_codBilet() ;
    return in ;
}

ostream& operator<< (ostream& out, Regio& r){
    r.afisare(out) ;
    return out ;
}

float Regio::get_pret() {
    float temp = float(this -> distanta) * 0.39 ;
    if ( this -> clasa == 1)
        return  temp + temp * 0.2 ;
    return temp ;
}

string Regio::get_codBilet() {
    string clasaIsauII ;
    string idBiletString = to_string(id_bilet) ;
    if ( this -> clasa == 1 )
        clasaIsauII = 'I' ;
    else
        clasaIsauII = "II" ;
    return 'R' + clasaIsauII + '-' +  idBiletString;
}

class InterRegio : public bilet {
public:
    InterRegio(string statiePlecare= "" ,string statieSosire= "" ,int ziPlecare = 0,int lunaPlecare = 0,int anPlecare = 0,int oraPlecare = 0,string codTren= "" ,int durata = 0,int distanta = 0,float pret = 0, int clasa = 0, string cod_bilet = "") :
            bilet(statiePlecare, statieSosire, ziPlecare, lunaPlecare, anPlecare, oraPlecare, codTren, durata, distanta, pret, clasa, cod_bilet) {
        pret = get_pret() ;
        cod_bilet = get_codBilet() ;
    };
    friend istream& operator>> (istream& in, InterRegio& Ir) ;
    friend ostream& operator<< (ostream& out, InterRegio& Ir) ;
    float get_pret();
    string get_codBilet() ;
};

istream& operator>> (istream& in, InterRegio& Ir) {
    Ir.citire(in) ;
    Ir.pret = Ir.get_pret() ;
    Ir.cod_bilet = Ir.get_codBilet() ;
    return in ;
}

ostream& operator<< (ostream& out, InterRegio& Ir){
    Ir.afisare(out) ;
    return out ;
}

float InterRegio::get_pret() {
    float temp = float(this -> distanta) * 0.7 ;
    if ( this -> clasa == 1)
        return  temp + temp * 0.2 ;
    return temp ;
}

string InterRegio::get_codBilet() {
    string clasaIsauII ;
    string idBiletString = to_string(id_bilet) ;
    if ( this -> clasa == 1 )
        clasaIsauII = 'I' ;
    else
        clasaIsauII = "II" ;
    return "IR" + clasaIsauII + '-' +  idBiletString;
}

class CFR {
    vector <bilet*> bilete ;
public :
    CFR(vector <bilet*> bilete = {}) {
        for (int i = 0 ; i < bilete.size() ; ++i )
            this -> bilete[i] = bilete[i] ;
    }
    ~CFR() {
        bilete.clear() ;
    }
    void adaugaBilet() ;
    void biletePtTren() ;
    void biletePtDistanta() ;
    void anuleazaBilet() ;
};

void CFR::adaugaBilet() {
    string tipBilet ;
    cout << "Introduceti tipul biletului (R/IR)" ;
    cin >> tipBilet ;
    if ( tipBilet == "R" ) {
        Regio *bilet = new Regio ;
        cin >> *bilet ;
        bilete.push_back(bilet) ;
    }
    else {
        InterRegio *bilet = new InterRegio() ;
        cin >> *bilet ;
        bilete.push_back(bilet) ;
    }
}

void CFR::biletePtTren() {
    string cod ;
    int ct = 0 ;
    cout << "Introduceti codul trenului: " ;
    cin >> cod ;
    for ( int i = 0 ; i < bilete.size() ; ++i ) {
        if ( bilete[i] -> get_codTren() == cod ) {
            cout << bilete[i]->get_codBilet() << endl;
            ct++;
        }

    }
    if ( ct == 0 )
        cout << "Nu exista trenuri" << endl ;

}

void CFR::biletePtDistanta() {
    int distanta ;
    int ct = 0 ;
    cout << "Introduceti distanta rutei: " ;
    cin >> distanta ;
    for ( int i = 0 ; i < bilete.size() ; ++i ) {
        if ( bilete[i] -> get_distanta() >=  distanta ) {
            cout << bilete[i]->get_codBilet() << endl;
            ct++;
        }

    }
    if ( ct == 0 )
        cout << "Nu exista trenuri" << endl ;
}

void CFR::anuleazaBilet() {
    string serie;
    cout << "Introduceti seria biletului: ";
    bool stergere = false ;
    cin >> serie;
    for (int i = 0; i < bilete.size(); ++i) {
        if (bilete[i]->get_codBilet() == serie) {
            bilete.erase(bilete.begin() + i);
            stergere = true;
        }
    }
    if ( stergere == false )
        cout << "Nu exista seria ceruta" << endl ;
    else
        cout << "Bilet sters cu succes" << endl ;
}

int main() {
    CFR cfr ;
    bool running = true ;
    int optiune ;
    while ( running == true ) {
        cout << "Introduceti optiunea : 1/2/3/4/5" << endl ;
        cout << "1 - Adaugarea unui bilet" << endl ;
        cout << "2 - Afisarea biletelor pt un anumit tren" << endl ;
        cout << "3 - Afisarea biletelor care au o distanta decat o anumita distanta" << endl ;
        cout << "4 - Stergerea unui bilet dupa serie" << endl ;
        cout << "5 - Iesire" << endl ;
        cout << "Optiunea : " ;
        cin >> optiune ;
        if ( optiune == 1 )
            cfr.adaugaBilet();
        if ( optiune == 2 )
            cfr.biletePtTren() ;
        if ( optiune == 3 )
            cfr.biletePtDistanta() ;
        if ( optiune == 4 )
            cfr.anuleazaBilet() ;
        if (optiune == 5 )
            running = false ;
    }
    
    
    #include <iostream>
#include <vector>

using namespace std ;

class produs {
    static int idProdus;
    int pret;
    int cantitate;
public :
    produs(int pret = 0, int cantitate = 0) {
        this->pret = pret;
        this->cantitate = cantitate;
        idProdus = idProdus + 1;
    }

    friend istream &operator>>(istream &, produs &);
    friend ostream &operator<<(ostream &, produs &);
    virtual void citire(istream &);
    virtual void afisare(ostream &);
    int get_cantitate() ;
};

int produs::get_cantitate() {
    return this -> cantitate ;
}

int produs::idProdus = 0 ;

void produs::citire(istream &in) {
    cout << "Introduceti pretul produsului: " ;
    in >> this->pret ;
    cout << "Introduceti cantitatea de produs: " ;
    in >> this -> cantitate ;
}

istream& operator>> (istream& in, produs& p) {
    p.citire(in) ;
    return in ;
}

void produs::afisare(ostream &out) {
    out << "Pretul produsului: " << this->pret << '\n';
    out << "Cantitatea de produs: " << this -> cantitate << '\n';
}

ostream& operator<< (ostream& out, produs& p){
    p.afisare(out) ;
    return out ;
}


class carte : public produs {
    string titlu ;
    int nrAutori ;
    string autori[10] ;
    string editura ;
public :
    carte(int pret = 0, int cantitate = 0,string titlu = "", int nrAutori = 0 , string autori = "", string editura = "") : produs(pret,cantitate) {
        this -> titlu = titlu ;
        this -> nrAutori = nrAutori ;
        for ( int i = 0 ; i < nrAutori ; ++i )
            this -> autori[i] = autori[i] ;
        this -> editura = editura ;
    }
    virtual ~carte() {
        titlu = "";
        editura = "";
    }
    friend istream& operator>> (istream&, carte&) ;
    friend ostream& operator<< (ostream&, carte& ) ;
    void citire(istream&) ;
    void afisare(ostream&) ;
    string getTitlu() ;
    void setTitlu(string) ;
    int getNrAutori() ;
    void setNrAutori(int) ;
    string* getAutori() ;
    void setAutori(string[]) ;
    string getEditura();
    void setEditura(string) ;
    void operator= (carte& ) ;
};

void carte::citire(istream &in) {
    produs::citire(in) ;
    cout << "Introduceti titlul cartii: " ;
    in >> this -> titlu ;
    cout << "Introduceti numarul de autori: " ;
    in >> this -> nrAutori ;
    cout << "Introduceti autorii: " << '\n';
    for ( int i = 1 ; i <= nrAutori ; ++i ) {
        cout << i << ": " ;
        in >> this -> autori[i] ;
    }
    cout << "Introduceti editura: " ;
    in >> this -> editura ;
}

istream& operator>> (istream& in, carte& c) {
    c.citire(in) ;
    return in ;
}

void carte::afisare(ostream &out) {
    produs::afisare(out) ;
    cout << "Titlul cartii: " <<  this -> titlu << '\n' ;
    cout << "Numarul de autori: " << this -> nrAutori << '\n' ;
    cout << "Autorii: " << '\n';
    for ( int i = 1 ; i <= nrAutori ; ++i )
        cout << i << ": " << this -> autori[i] << '\n';
    cout << "Editura: " <<  this -> editura;
}

ostream& operator<< (ostream& out, carte& c) {
    c.afisare(out) ;
    return out ;
}

string carte::getTitlu() {
    return this -> titlu ;
}

void carte::setTitlu(string titlu) {
    this -> titlu = titlu ;
}

int carte::getNrAutori() {
    return this -> nrAutori ;
}

void carte::setNrAutori(int nrAutori) {
    this -> nrAutori = nrAutori ;
}

string* carte::getAutori() {
    return this->autori ;
}

void carte::setAutori(string autori[]) {
    for ( int i = 1 ; i <= this -> getNrAutori() ; ++i)
        this -> autori[i] = autori[i] ;
}

string carte::getEditura() {
    return this -> editura ;
}

void carte::setEditura(string editura) {
    this -> editura = editura ;
}

void carte::operator=(carte &c) {
    this -> setTitlu(c.getTitlu()) ;
    this ->setNrAutori(c.getNrAutori()) ;
    this -> setAutori(c.getAutori()) ;
    this -> setEditura(c.getEditura()) ;
}

class DVD : public produs {
    int nrMinute ;
public :
    DVD(int pret = 0, int cantitate = 0,int nrMinute = 0) : produs(pret, cantitate) {
        this -> nrMinute = nrMinute ;
    }
    friend istream& operator>> (istream&, DVD&) ;
    friend ostream& operator<< (ostream&, DVD& ) ;
    void citire(istream&) ;
    void afisare(ostream&) ;
};

void DVD::citire(istream &in) {
    produs::citire(in) ;
    cout << "Numarul de minute al DVD-ului: " ;
    in >> this -> nrMinute ;
}

istream& operator>> (istream& in, DVD& d) {
    d.citire(in) ;
    return in ;
}

void DVD::afisare(ostream &out) {
    produs::afisare(out) ;
    cout << "Numarul de minute al DVD-ului: " << this -> nrMinute << '\n' ;
}

ostream& operator<< (ostream& out, DVD& d) {
    d.afisare(out) ;
    return out ;
}

class DVD_Music : public DVD {
    string numeAlbum ;
    int nrInterpreti ;
    string interpreti[10] ;
public :
    DVD_Music(int pret = 0, int cantitate = 0,int nrMinute = 0, string numeAlbum = "" , int nrInterpreti = 0 ,string interpreti = "") : DVD(pret,cantitate, nrMinute) {
        this -> numeAlbum = numeAlbum ;
        this -> nrInterpreti = nrInterpreti ;
        for ( int i = 1 ; i <= nrInterpreti ; ++i )
            this -> interpreti[i] = interpreti[i] ;
    }
    ~DVD_Music() {
        numeAlbum = "" ;
    }
    friend istream& operator>> (istream&, DVD_Music&) ;
    friend ostream& operator<< (ostream&, DVD_Music& ) ;
    void citire(istream&) ;
    void afisare(ostream&) ;
};

void DVD_Music::citire(istream& in) {
    DVD::citire(in) ;
    cout << "Introduceti numele albumului: " ;
    in >> this -> numeAlbum ;
    cout << "Introduceti numarul de interpreti: " ;
    in >> this -> nrInterpreti ;
    cout << "Introduceti interpretii: " << '\n' ;
    for ( int i = 1 ; i <= nrInterpreti ; ++i ) {
        cout << i << ": " ;
        in >> this -> interpreti[i];
    }
}

istream& operator>> (istream& in,  DVD_Music& d ) {
    d.citire(in) ;
    return in ;
}

void DVD_Music::afisare(ostream& out) {
    DVD::afisare(out) ;
    out << "Numele albumului: " ;
    out << this -> numeAlbum << '\n' ;
    out << "Numarul de interpreti: " ;
    out <<  this -> nrInterpreti << '\n';
    out << "Interpreti: " << '\n' ;
    for ( int i = 1 ; i <= nrInterpreti ; ++i ) {
        out << i << ": " ;
        out << this -> interpreti[i] << '\n';
    }
}

ostream& operator<< (ostream& out, DVD_Music& d) {
    d.afisare(out) ;
    return out ;
}

class DVD_Film : public DVD {
    string numeFilm ;
    string genFilm ;
public :
    DVD_Film(int pret = 0, int cantitate = 0,int nrMinute = 0, string numeFilm = "", string genFilm = "") : DVD(pret, cantitate, nrMinute) {
        this -> numeFilm = numeFilm ;
        this -> genFilm = genFilm ;
    }
    ~DVD_Film() {
        numeFilm = "" ;
        genFilm = "" ;
    }
    friend istream& operator>> (istream&, DVD_Film&) ;
    friend ostream& operator<< (ostream&, DVD_Film& ) ;
    void citire(istream&) ;
    void afisare(ostream&) ;
};

void DVD_Film::citire(istream &in) {
    DVD::citire(in) ;
    cout << "Introduceti numele filmului : " ;
    in >> this -> numeFilm ;
    cout << "Introduceti genul filmului : "  ;
    in >> this -> genFilm ;
}

istream& operator>> (istream& in, DVD_Film& d) {
    d.citire(in) ;
    return in ;
}

void DVD_Film::afisare(ostream &out) {
    DVD::afisare(out) ;
    out << "Introduceti numele filmului : " ;
    out << this -> numeFilm << '\n' ;
    out << "Introduceti genul filmului : "  ;
    out << this -> genFilm << '\n' ;
}

class colectie : public produs {
    string denumire ;
public :
};

class figurina : public colectie {
    string categorie ;
    string brand ;
    string material ;
public :
};

class poster : public colectie {
    string format ;
public :
};

class librarie {
    vector<produs *> produse;
public :
    void adaugare();
    void afisare();
    void cautare() ;
    void cautareDupaStoc() ;
};

void librarie::adaugare() {
    int tipObiect ;
    cout << "Introduceti tipul obiectului pe care doriti sa il adaugati: " << endl ;
    cout << "1 - Carte " << endl ;
    cout << "2 - DVD-Music" << endl ;
    cout << "3 - DVD-Film" << endl ;
    cout << "Introduceti tipul: " ;
    cin >> tipObiect ;
    if ( tipObiect == 1 ) {
        carte *c = new carte;
        cin >> *c ;
        produse.push_back(c) ;
    }
    if ( tipObiect == 2 ) {
        DVD_Music *d = new DVD_Music;
        cin >> *d ;
        produse.push_back(d) ;
    }
    if ( tipObiect == 3 ) {
        DVD_Film *d = new DVD_Film;
        cin >> *d ;
        produse.push_back(d) ;
    }
}

void librarie::afisare() {
    for (int i = 0 ; i < produse.size() ; ++i ) {
        produs *p = produse[i] ;
        if ( typeid(*p) == typeid(carte) ) {
            carte* c = static_cast <carte*> (p) ;
            cout << *c << endl;
        }
        if ( typeid(*p) == typeid(DVD_Music) ) {
            DVD_Music* d = static_cast <DVD_Music*> (p) ;
            cout << *d << endl;
        }
        cout << endl ;
    }
}

void librarie::cautare() {
    string nume ;
    bool found = 0 ;
    cout << "Introduceti numele cartii cautate: " ;
    cin >> nume ;
    for ( int i = 0 ; i < produse.size() ; ++i ) {
        produs *p = produse[i] ;
        if ( typeid(*p) == typeid(carte) ) {
            carte* c = static_cast <carte*> (p) ;
            if ( c -> getTitlu() == nume ) {
                cout << *c << endl;
                found = 1;
            }
        }
    }
    if ( found == 0 ) {
        cout << "------Nu exista cartea-------" << endl ;
    }
}

void librarie::cautareDupaStoc() {
    int vmax = 0 ;
    vector <produs*> rezultat ;
    for ( int i = 0 ; i < produse.size() ; ++i ) {
        produs *p = produse[i] ;
        if ( p -> get_cantitate() > vmax) {
            vmax = p -> get_cantitate() ;
            rezultat.clear() ;
        }
        if ( p -> get_cantitate() == vmax )
            rezultat.push_back(p) ;
    }
    for (int i = 0 ; i < rezultat.size() ; ++i)
        cout << *rezultat[i] << endl ;

}

int main() {
    librarie l ;
    int optiune ;
    while (true) {
        cout << "Introduceti optiunea: " << endl ;
        cout << "1 - Adaugarea unui obiect" << endl ;
        cout << "2 - Afisarea obiectelor din librarie" << endl ;
        cout << "3 - Cautarea unei carti dupa titlu" << endl ;
        cout << "4 - Cautarea produsului cu cel mai mare stoc" << endl ;
        cout << "5 - Iesire" << endl ;
        cout << "Optiune : " ;
        cin >> optiune ;
        if ( optiune == 1 )
            l.adaugare() ;
        if ( optiune == 2 )
            l.afisare() ;
        if ( optiune == 3 )
            l.cautare() ;
        if ( optiune == 4 )
            l.cautareDupaStoc() ;
        if ( optiune == 5 )
            break ;
    }

}

}
