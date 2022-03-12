#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstring>
#include <vector>
#include <time.h>
#include <sstream>
#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27

using namespace std ;


class Button {
    sf::RectangleShape button ;
    sf::Text text ;
public:
    Button() { }
    Button(string t,sf::Vector2f size, int charSize, sf::Color bgColor, sf::Color textColor) {
        text.setString(t);
        text.setColor(textColor);
        text.setCharacterSize(charSize);

        button.setSize(size);
        button.setFillColor(bgColor);

    }
    void setFont(sf::Font &font) {
        text.setFont(font);
    }
    void setBackColor(sf::Color color){
        button.setFillColor(color);
    }
    void setTextColor(sf::Color color){
        text.setColor(color);
    }
    void setPosition(sf::Vector2f pos){
        button.setPosition(pos);

        float xPos, yPos;
        xPos = (pos.x + button.getLocalBounds().width / 8) - (text.getLocalBounds().width / 2);
        yPos = (pos.y + button.getLocalBounds().height / 4) - (text.getLocalBounds().height / 3);
        text.setPosition(xPos,yPos);
    }
    void drawTo(sf::RenderWindow &window) {
        window.draw(button);
        window.draw(text);
    }

    bool isMouseOver(sf::RenderWindow &window) {
        float mouseX = sf::Mouse::getPosition(window).x;
        float mouseY = sf::Mouse::getPosition(window).y;

        float btnPosX = button.getPosition().x ;
        float btnPosY = button.getPosition().y;

        float btnxPosWidth = button.getPosition().x + button.getLocalBounds().width;
        float btnyPosHeight = button.getPosition().y + button.getLocalBounds().height;

        if(mouseX < btnxPosWidth && mouseX > btnPosX && mouseY < btnyPosHeight && mouseY > btnPosY)
            return true ;
        return false ;
    }
};

class TextBox {
    sf::Text textbox;
    ostringstream text;
    bool isSelected = false ;
    bool hasLimit = false ;
    int limit ;
    void inputLogic(int charTyped) {
        if(charTyped != DELETE_KEY && charTyped != ENTER_KEY && charTyped != ESCAPE_KEY) {
            text << static_cast<char>(charTyped);
        }
        else if (charTyped == DELETE_KEY){
            if(text.str().length() > 0){
                deleteLastChar();
            }
        }
        textbox.setString(text.str() + "_");
    }

    void deleteLastChar() {
        string t = text.str();
        string newT = "";
        for (int i = 0 ; i < t.length() - 1; ++i ){
            newT += t[i] ;
        }
        text.str("");
        text << newT ;

        textbox.setString(text.str());
    }

public :
    TextBox() {}
    TextBox(int size, sf::Color color, bool sel) {
        textbox.setCharacterSize(size);
        textbox.setColor(color);
        isSelected = sel ;
        if(sel)
            textbox.setString("_");
        else
            textbox.setString("");
    }

    void setFont(sf::Font &font) {
        textbox.setFont(font);
    }
    void setPosition(sf::Vector2f pos){
        textbox.setPosition(pos);
    }
    void setLimit(bool ToF) {
        hasLimit = ToF ;
    }
    void setLimit(bool ToF, int lim) {
        hasLimit = ToF ;
        limit = lim ;
    }
    void setSelected(bool sel) {
        isSelected = sel ;
        if (!sel) {
            string t = text.str();
            string newT = "";
            for (int i = 0 ; i < t.length() ; ++i ){
                newT += t[i] ;
            }
            textbox.setString(newT);
        }
    }
    string getText(){
        return text.str();
    }
    void drawTo(sf::RenderWindow &window, sf::Vector2f pos) {
        textbox.setPosition(pos);
        window.draw(textbox);
    }
    void printConsole(sf::RenderWindow &window, string text, sf::Vector2f pos) {
        sf::Font font;
        sf::Text text1;
        if( !font.loadFromFile("/Users/georgeboboc/Desktop/Proiecte/HelloSFML/arial.ttf") ) {
            cout << "ERROR" ;
        }
        text1.setString(text);
        text1.setFont(font);
        text1.setCharacterSize(24);
        text1.setPosition(pos.x,pos.y);
        window.draw(text1);
    }
    void typedOn(sf::Event input) {
        if(isSelected) {
            int charTyped = input.text.unicode ;
            if (charTyped < 128 ) {
                if (hasLimit) {
                    if (text.str().length() <= limit){
                        inputLogic(charTyped) ;
                    }
                    else if (text.str().length() > limit && charTyped == DELETE_KEY) {
                        deleteLastChar();
                    }
                }
                else
                    inputLogic(charTyped);
            }
        }
    }

};

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
};

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

int main()
{
    /*
     cout << "-----------Program gestiune baze de date-----------------" << endl;
    cout << "Operatii posibile : " << endl << "1. Adaugarea unui om in baza de date - prin codul de comanda -- add"
         << endl;
    cout << "2. Stergerea unui om din baza de date - prin codul de comanda -- delete" << endl;
    cout << "3. Interogarea bazei de date - prin codul de comanda -- query" << endl;
    cout << "4. Afisarea bazei de date - print codul de comanda -- print" << endl ;
    string comanda, nume_de_familie, prenume, cod, cod1, cod2 ;
    persoana p;
    baza_de_date b;
    int an;
    char gender;
    while (true) {
        cout << endl << "Introduceti codul operatiei : ";
        cin >> comanda;
        if (comanda == "exit") {
            break;
        }
        else if (comanda == "add") {
            cout << "Introduceti numele de familie al persoanei : " << " ";
            cin >> nume_de_familie;
            cout << "Introduceti prenumele persoanei : " << " ";
            cin >> prenume;
            p.set_nume(nume_de_familie + " " + prenume);
            cout << "Introduceti anul nasterii persoanei : " << " ";
            cin >> an;
            p.set_an_nastere(an);
            cout << "Introduceti genul persoanei : " << " ";
            cin >> gender;
            p.set_gen(gender);
            b.adauga(p);
        }
        else if (comanda == "delete") {
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

                } else if (cod == "an") {
                    cout << "Introduceti anul de nastere persoanei/persoanelor pe care vrei sa le elimini : ";
                    cin >> an;
                    b.sterge(an);

                } else if (cod == "gen") {
                    cout << "Introduceti genul al persoanei/persoanelor pe care vrei sa le elimini : ";
                    cin >> gender;
                    b.sterge(gender);

                } else
                    cout << "---------Cod invalid. Reia operatia------------ ";
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
                    cin >> an;
                    b.sterge(nume_de_familie + " " + prenume, an) ;
                }
                else if ( (cod1 == "nume" && cod2 == "gen") || (cod2 == "nume" && cod1 == "gen")) {
                    cout << "Introduceti numele de familie al persoanei/persoanelor pe care vrei sa le elimini  : ";
                    cin >> nume_de_familie;
                    cout << "Introduceti prenumele persoanei/persoanelor pe care vrei sa le elimini : ";
                    cin >> prenume;
                    cout << "Introduceti genul persoanei/persoanelor pe care vrei sa le elimini : ";
                    cin >> gender;
                    b.sterge(nume_de_familie + " " + prenume, gender) ;
                }
                else if ( (cod1 == "an" && cod2 == "gen") || (cod2 == "an" && cod1 == "gen")) {
                    cout << "Introduceti anul de nastere persoanei/persoanelor pe care vrei sa le elimini : ";
                    cin >> an;
                    cout << "Introduceti genul persoanei/persoanelor pe care vrei sa le elimini : ";
                    cin >> gender;
                    b.sterge(an, gender) ;
                }
                else
                    cout << "---------Cod invalid. Reia operatia------------ ";
            }
            else if (numar == 3) {
                cout << "Introduceti numele de familie al persoanei/persoanelor pe care vrei sa le elimini  : ";
                cin >> nume_de_familie;
                cout << "Introduceti prenumele persoanei/persoanelor pe care vrei sa le elimini : ";
                cin >> prenume;
                cout << "Introduceti anul de nastere persoanei/persoanelor pe care vrei sa le elimini : ";
                cin >> an;
                cout << "Introduceti genul persoanei/persoanelor pe care vrei sa le elimini : ";
                cin >> gender;
                b.sterge(nume_de_familie + " " + prenume, an, gender) ;
            }
            else
                cout << "---------Numar invalid de atribute. Reia operatia---------" ;
        }
        else if (comanda == "print") {
            cout << endl;
            cout << b;
        }
        else if (comanda == "query") {
            int numar ;
            cout << "-----------Optiuni de interogare-------------";
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

                } else if (cod == "an") {
                    cout << "Introduceti anul de nastere persoanei/persoanelor pe care vrei sa le interoghezi : ";
                    cin >> an;
                    b.query(an);

                } else if (cod == "gen") {
                    cout << "Introduceti genul al persoanei/persoanelor pe care vrei sa le interoghezi : ";
                    cin >> gender;
                    b.query(gender);

                } else
                    cout << "---------Cod invalid. Reia operatia------------ ";
            }
            else if (numar == 2) {
                cout << "Introduceti primul atribut dupa care doriti sa se faca interogarea : " ;
                cin >> cod1 ;
                cout << "Introduceti al doilea atribut dupa care doriti sa se faca interogarea : " ;
                cin >> cod2 ;
                if ( (cod1 == "nume" && cod2 == "an") || (cod2 == "nume" && cod1 == "an")) {
                    cout << "Introduceti numele de familie al persoanei/persoanelor pe care vrei sa le interoghezi  : ";
                    cin >> nume_de_familie;
                    cout << "Introduceti prenumele persoanei/persoanelor pe care vrei sa le interoghezi : ";
                    cin >> prenume;
                    cout << "Introduceti anul de nastere persoanei/persoanelor pe care vrei sa le interoghezi : ";
                    cin >> an;
                    b.query(nume_de_familie + " " + prenume, an) ;
                }
                else if ( (cod1 == "nume" && cod2 == "gen") || (cod2 == "nume" && cod1 == "gen")) {
                    cout << "Introduceti numele de familie al persoanei/persoanelor pe care vrei sa le interoghezi  : ";
                    cin >> nume_de_familie;
                    cout << "Introduceti prenumele persoanei/persoanelor pe care vrei sa le interoghezi : ";
                    cin >> prenume;
                    cout << "Introduceti genul persoanei/persoanelor pe care vrei sa le interoghezi : ";
                    cin >> gender;
                    b.query(nume_de_familie + " " + prenume, gender) ;
                }
                else if ( (cod1 == "an" && cod2 == "gen") || (cod2 == "an" && cod1 == "gen")) {
                    cout << "Introduceti anul de nastere persoanei/persoanelor pe care vrei sa le interoghezi : ";
                    cin >> an;
                    cout << "Introduceti genul persoanei/persoanelor pe care vrei sa le interoghezi : ";
                    cin >> gender;
                    b.query(an, gender) ;
                }
                else
                    cout << "---------Cod invalid. Reia operatia------------ ";
            }
            else if (numar == 3) {
                cout << "Introduceti numele de familie al persoanei/persoanelor pe care vrei sa le interoghezi  : ";
                cin >> nume_de_familie;
                cout << "Introduceti prenumele persoanei/persoanelor pe care vrei sa le interoghezi : ";
                cin >> prenume;
                cout << "Introduceti anul de nastere persoanei/persoanelor pe care vrei sa le interoghezi : ";
                cin >> an;
                cout << "Introduceti genul persoanei/persoanelor pe care vrei sa le interoghezi : ";
                cin >> gender;
                b.query(nume_de_familie + " " + prenume, an, gender) ;
            }
            else
                cout << "---------Numar invalid de atribute. Reia operatia---------" ;

        }
        else
            cout << "---------Cod invalid. Reia operatia------------ ";
    }
     */
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Baza de date");
    sf::Font font;
    if( !font.loadFromFile("/Users/georgeboboc/Desktop/Proiecte/HelloSFML/arial.ttf") ) {
        cout << "ERROR" ;
    }
    sf::Text text1 ,text2 , text3 , text4 ,text5;
    text1.setFont(font);
    text1.setString("---------------Program gestiune baze de date-----------------");
    text1.setCharacterSize(48);
    text1.setFillColor(sf::Color::White);
    text1.setStyle(sf::Text::Bold);

    TextBox textbox1(24, sf::Color::White, true);
    textbox1.setFont(font) ;
    textbox1.setPosition({850,100});

    TextBox textbox2(24, sf::Color::White, true);
    textbox2.setFont(font) ;
    textbox2.setPosition({750,125});

    TextBox textbox(24, sf::Color::White, true);
    textbox.setFont(font) ;
    textbox.setPosition({450,100});

    Button btn1("Adaugare", {200,100}, 32, sf::Color::Green, sf::Color::Black);
    btn1.setPosition({100,100});
    btn1.setFont(font);

    Button btn2("Stergere", {200,100}, 32, sf::Color::Green, sf::Color::Black);
    btn2.setPosition({100,225});
    btn2.setFont(font);

    Button btn3("Interogare", {200,100}, 32, sf::Color::Green, sf::Color::Black);
    btn3.setPosition({100,350});
    btn3.setFont(font);

    Button btn4("Afisare BD", {200,100}, 32, sf::Color::Green, sf::Color::Black);
    btn4.setPosition({100,475});
    btn4.setFont(font);

    static bool lock_click ;
    persoana p;
    baza_de_date b;
    string nume_de_familie, prenume;
    int an;
    char gender;
    p.set_nume("Gigel Frone");
    p.set_an_nastere(2000);
    p.set_gen('M');
    b.adauga(p);
    while (window.isOpen())
    {
        sf::Event event;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
            textbox1.setSelected(true);
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            textbox1.setSelected(false);
        while (window.pollEvent(event))
        {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                case sf::Event::TextEntered:
                    textbox1.typedOn(event);
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
                        cout << textbox1.getText() ;
                case sf::Event::MouseMoved:
                    if(btn1.isMouseOver(window))
                        btn1.setBackColor(sf::Color::White);
                    else if (!btn1.isMouseOver(window))
                        btn1.setBackColor(sf::Color::Green);
                    if(btn2.isMouseOver(window))
                        btn2.setBackColor(sf::Color::White);
                    else if (!btn2.isMouseOver(window))
                        btn2.setBackColor(sf::Color::Green);
                    if(btn3.isMouseOver(window))
                        btn3.setBackColor(sf::Color::White);
                    else if (!btn3.isMouseOver(window))
                        btn3.setBackColor(sf::Color::Green);
                    if(btn4.isMouseOver(window))
                        btn4.setBackColor(sf::Color::White);
                    else if (!btn4.isMouseOver(window))
                        btn4.setBackColor(sf::Color::Green);
                case sf::Event::MouseButtonPressed:
                    if (event.mouseButton.button == sf::Mouse::Left && lock_click != true) {
                        if(btn1.isMouseOver(window)) {
                            /*
                            cout << "Introduceti numele de familie al persoanei : " << " ";
                            cin >> nume_de_familie;
                            cout << "Introduceti prenumele persoanei : " << " ";
                            cin >> prenume;
                            p.set_nume(nume_de_familie + " " + prenume);
                            cout << "Introduceti anul nasterii persoanei : " << " ";
                            cin >> an;
                            p.set_an_nastere(an);
                            cout << "Introduceti genul persoanei : " << " ";
                            cin >> gender;
                            p.set_gen(gender);
                            b.adauga(p);
                            cout << "Adaugat cu succes";
                             */
                            bool loop = true ;
                            while ( loop ) {
                                //cout << "PL";
                                window.clear();
                                window.draw(text1);
                                textbox1.drawTo(window,{850,200});
                                textbox.printConsole(window, "Introduceti numele de familie al persoanei : " , {350,200});
                                nume_de_familie = textbox.getText();
                                textbox.printConsole(window, "Introduceti prenumele persoanei : " , {457,227});
                                prenume = textbox.getText();
                                p.set_nume(nume_de_familie + " " + prenume) ;
                                textbox.printConsole(window, "Introduceti anul nasterii persoanei : " , {437, 254} ) ;
                                textbox.printConsole(window,"Introduceti genul persoanei (M/F) : ", {447,281}) ;
                                btn1.drawTo(window);
                                btn2.drawTo(window);
                                btn3.drawTo(window);
                                btn4.drawTo(window);
                                window.display();
                            }
                        }
                        if(btn4.isMouseOver(window)){
                            cout << "OK" ;
                        }
                        lock_click = true ;
                    }
            }
        }
        window.clear();
        window.draw(text1);
        //textbox1.drawTo(window);
        //textbox1.printConsole(window, "Hello world", {500,300});
        btn1.drawTo(window);
        btn2.drawTo(window);
        btn3.drawTo(window);
        btn4.drawTo(window);
        window.display();
    }
}
