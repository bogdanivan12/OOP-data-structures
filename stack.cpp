#include <iostream>
#include <fstream>
#include <string>

using namespace std;

ifstream f("date.in");

class Nod
{
    char info;
    int val;
    Nod* next;
public:
    Nod( char info = '\0', Nod* next = NULL )
    {
        this->info = info;
        this->next = next;
    }
    Nod( Nod* next = NULL )
    {
        this->info = '\0';
        this->next = NULL;
    }
    Nod( Nod& n )
    {
        this->info = n.info;
        this->next = n.next;
    }
    ~Nod()
    {
        this->next = NULL;
    }
    Nod& operator=( Nod& );
    void set_info( char info )
    {
        this->info = info;
    }
    void set_next( Nod* next )
    {
        this->next = next;
    }
    char get_info()
    {
        return this->info;
    }
    Nod* get_next()
    {
        return this->next;
    }
};

Nod& Nod::operator=( Nod& n )
{
    this->info = n.info;
    this->next = n.next;
    return *this;
}

class Stiva_de_caractere
{
    Nod* top;
    int dim;
public:
    Stiva_de_caractere( Nod* n = NULL )
    {
        this->top = n;
        if( n )
            dim = 1;
        else
            dim = 0;
    }
    Stiva_de_caractere( char info, int dim = 1 )
    {
        top = new Nod( info);
        this->dim = dim;
    }
    Stiva_de_caractere( Stiva_de_caractere& );
    Stiva_de_caractere( bool );
    ~Stiva_de_caractere();
    void push( char info )
    {
        Nod* nou = new Nod( info );
        nou->set_next( top );
        top = nou;
        ++dim;
    }
    void pop()
    {
        Nod* nou = top;
        top = top->get_next();
        delete nou;
        --dim;
    }
    bool isempty()
    {
        return !top;
    }
    char get_top()
    {
        return this->isempty() ? '\0' : this->top->get_info();
    }
    int get_dim()
    {
        return this->dim;
    }
    void afisare();
    string strrev( string );
    friend istream& operator>>( istream&, Stiva_de_caractere& );
    friend ostream& operator<<( ostream&, Stiva_de_caractere& );
    Stiva_de_caractere& operator-( Stiva_de_caractere& );
    Stiva_de_caractere& operator=( Stiva_de_caractere& );
    Stiva_de_caractere& operator-();
    Stiva_de_caractere& operator++();
    Stiva_de_caractere& operator++( int );
    bool operator!=( Stiva_de_caractere& v )
    {
        return this->dim != v.dim;
    }
    operator int()
    {
        return this->dim;
    }
    operator bool()
    {
        return this->dim != 0;
    }
};

void Stiva_de_caractere::afisare()
{
    for( Nod*p = this->top; p; p = p->get_next() )
        cout << p->get_info();
    cout << "\nDimensiune: " << this->get_dim() << "\n";
}

Stiva_de_caractere& Stiva_de_caractere::operator++()
{
    ++dim;
    return *this;
}

Stiva_de_caractere& Stiva_de_caractere::operator++( int )
{
    dim++;
    return *this;
}

Stiva_de_caractere& Stiva_de_caractere::operator-()
{
    Stiva_de_caractere *aux = new Stiva_de_caractere(*this);
    aux->dim = -(aux->dim);
    return *aux;
}

Stiva_de_caractere::Stiva_de_caractere( bool consola )
{
    top = NULL;
    if( consola )
        cin >> *this;
    else
        f >> *this;
}

Stiva_de_caractere::Stiva_de_caractere( Stiva_de_caractere& v )
{
    this->top = NULL;
    if( !v.isempty() )
    {
        this->push( v.get_top() );
        Nod* p = this->top, *q = v.top->get_next();
        while( q != NULL )
        {
            Nod *nou = new Nod( q->get_info() );
            p->set_next( nou );
            p = p->get_next();
            q = q->get_next();
        }
    }
    this->dim = v.dim;
}

Stiva_de_caractere::~Stiva_de_caractere()
{
    while( top != NULL )
    {
        Nod* aux = top;
        top = top->get_next();
        delete aux;
    }
    dim = 0;
}

Stiva_de_caractere& Stiva_de_caractere::operator=( Stiva_de_caractere& v )
{
    while( top != NULL )
    {
        Nod* aux = top;
        top = top->get_next();
        delete aux;
    }
    if( !v.isempty() )
    {
        this->push( v.get_top() );
        Nod* p = this->top, *q = v.top->get_next();
        while( q != NULL )
        {
            Nod *nou = new Nod( q->get_info() );
            p->set_next( nou );
            p = p->get_next();
            q = q->get_next();
        }
    }
    this->dim = v.dim;
    return *this;
}

istream& operator>>( istream& in, Stiva_de_caractere& v )
{
    Stiva_de_caractere aux;
    string s;
    getline( in, s );
    int n = s.size();
    for( int i = 0; i < n; ++i )
        aux.push( s[i] );
    v = aux;
    v.dim = n;
    return in;
}

ostream& operator<<( ostream& out, Stiva_de_caractere& v )
{
    while( !v.isempty() )
    {
        out << v.get_top();
        v.pop();
    }
    out << "\nDimensiune: " << v.get_dim();
    return out;
}

Stiva_de_caractere& Stiva_de_caractere::operator-( Stiva_de_caractere& v )
{
    Stiva_de_caractere* nou = new Stiva_de_caractere;
    while( !this->isempty() && !v.isempty() )
    {
        if( this->get_top() > v.get_top() )
            nou->push( this->get_top() );
        else
            nou->push( v.get_top() );
        this->pop();
        v.pop();
    }
    return *nou;
}

string Stiva_de_caractere::strrev( string s )
{
    string aux = "";
    int n = s.size();
    for( int i = 0; i < n; ++i )
        this->push( s[i] );
    for( int i = 0; i < n; ++i )
    {
        aux += this->get_top();
        this->pop();
    }
    return aux;
}

void clear()
{
    for( int i = 0; i < 200; ++i )
        cout << endl;
}

void meniu( Stiva_de_caractere& );

void citire( Stiva_de_caractere &v )
{
    clear();
    cout << "------------------CITIRE------------------" << endl << endl;
    cout << "Introduceti un sir de caractere:" << endl;
    cout << endl << " -> ";
    cin.get();
    cin >> v;
    cout << endl << endl << "Stiva a fost citita cu succes. Apasati ENTER pentru a continua.";
    cin.get();
    meniu( v );
}

void adaugare( Stiva_de_caractere &v )
{
    clear();
    cout << "------------------ADAUGARE------------------" << endl << endl;
    cout << "Introduceti caracterul pe care doriti sa il adaugati in stiva" << endl;
    cout << endl << " -> ";
    char c;
    cin >> c;
    v.push( c );
    cout << "Caracterul \'" << c << "\' a fost adaugat cu succes in stiva. Apasati ENTER pentru a continua.";
    cin.get();
    cin.get();
    meniu( v );
}

void stergere( Stiva_de_caractere &v )
{
    clear();
    cout << "------------------STERGERE------------------" << endl << endl;
    if( v.isempty() )
        cout << "Eroare: Stiva este goala. Apasati ENTER pentru a continua.";
    else
    {
        char c = v.get_top();
        v.pop();
        cout << "Caracterul \'" << c << "\' a fost sters cu succes din stiva. Apasati ENTER pentru a continua.";
    }
    cin.get();
    cin.get();
    meniu( v );
}

void afisareVarf( Stiva_de_caractere &v )
{
    clear();
    cout << "------------------AFISARE VARF------------------" << endl << endl;
    if( v.isempty() )
        cout << "Eroare: Stiva este goala. Apasati ENTER pentru a continua.";
    else
        cout << "In varful stivei este caracterul \'" << v.get_top() << "\'. Apasati ENTER pentru a continua.";
    cin.get();
    cin.get();
    meniu( v );
}

void verifGoala( Stiva_de_caractere &v )
{
    clear();
    cout << "------------------VERIFICARE STIVA GOALA------------------" << endl << endl;
    if( v.isempty() )
        cout << "Stiva este goala. Apasati ENTER pentru a continua.";
    else
        cout << "Stiva NU este goala. Apasati ENTER pentru a continua.";
    cin.get();
    cin.get();
    meniu( v );
}

void inversareSir( Stiva_de_caractere &v )
{
    clear();
    cout << "------------------INVERSARE SIR------------------" << endl << endl;
    cout << "Introduceti un sir de caractere:" << endl;
    cout << endl << " -> ";
    string s;
    cin.get();
    getline( cin, s );
    cout << endl << "Sirul \"" << s << "\" inversat este \"" << v.strrev( s ) << "\". Apasati ENTER pentru a continua." << endl;
    cin.get();
    meniu( v );
}

void diferenta( Stiva_de_caractere &v )
{
    clear();
    cout << "------------------DIFERENTA------------------" << endl << endl;
    cout << "Introduceti un sir de caractere pentru a citi cea de-a doua stiva:" << endl;
    cout << endl << " -> ";
    cin.get();
    Stiva_de_caractere v2;
    cin >> v2;
    cout << endl << "Diferenta dintre cele doua stive este, incepand de la varf: \"" << v - v2 << "\". Apasati ENTER pentru a continua." << endl;
    cin.get();
    meniu( v );
}

void afisare( Stiva_de_caractere &v )
{
    clear();
    cout << "------------------AFISARE (SI GOLIRE)------------------" << endl << endl;
    if( v.isempty() )
        cout << "Stiva este goala. ";
    else
        cout << "Elementele stivei, incepand de la varf, sunt: \"" << v << "\"." << endl;
    cout << "Apasati ENTER pentru a continua." << endl;
    cin.get();
    cin.get();
    meniu( v );
}

void iesire( Stiva_de_caractere &v ) //////////////////////////////////////////////////////////////////////////////////////////////////
{
    clear();
    cout << "------------------IESIRE------------------" << endl << endl;
    cout << "Sigur doriti sa iesiti?" << endl;
    cout << "1. DA" << endl;
    cout << "2. NU" << endl;
    int optiune;
    cout << endl << " -> ";
    cin >> optiune;
    cout << endl;
    while( optiune < 1 || optiune > 2 )
    {
        cout << "Eroare: Nu ati introdus un numar intre 1 si 2. Introduceti alt numar:" << endl;
        cout << endl << " -> ";
        cin >> optiune;
        cout << endl;
    }
    if( optiune == 2 )
        meniu(v);
}

void meniu( Stiva_de_caractere &v )
{
    clear();
    cout << "------------------MENIU------------------" << endl << endl;
    cout << "1. Citeste stiva" << endl;
    cout << "2. Adauga un element in stiva" << endl;
    cout << "3. Sterge un element din stiva" << endl;
    cout << "4. Afiseaza varful stivei" << endl;
    cout << "5. Verifica daca stiva este goala" << endl;
    cout << "6. Inverseaza un sir de caractere" << endl;
    cout << "7. Diferenta dintre doua stive" << endl;
    cout << "8. Afiseaza (si goleste) stiva" << endl;
    cout << "9. Iesire" << endl;
    int optiune;
    cout << endl << " -> ";
    cin >> optiune;
    cout << endl;
    while( optiune < 1 || optiune > 9 )
    {
        cout << "Eroare: Nu ati introdus un numar intre 1 si 9. Introduceti alt numar:" << endl;
        cout << endl << " -> ";
        cin >> optiune;
        cout << endl;
    }
    if( optiune == 1 )
        citire( v );
    else if( optiune == 2 )
        adaugare( v );
    else if( optiune == 3 )
        stergere( v );
    else if( optiune == 4 )
        afisareVarf( v );
    else if( optiune == 5 )
        verifGoala( v );
    else if( optiune == 6 )
        inversareSir( v );
    else if( optiune == 7 )
        diferenta( v );
    else if( optiune == 8 )
        afisare( v );
    else
        iesire( v );
}

int main()
{
    /*
    Stiva_de_caractere ob1, ob2('a'), ob3('b', 3), ob4 = ob3, ob5(false);
    //cout << ob1 << endl << ob2 << endl << ob3 << endl << ob4 << endl << ob5;
    cin>>ob1;
    ob1.afisare();
    ob2 = -ob1;
    ob2.afisare();
    //int y = ob5;
    ++ob1;
    ob1.afisare();
    ob1++;
    cout << ob1;
    cout << endl << int(ob1) << bool(ob1);
    //int y = ob1;
    //cout<<y<<endl;
    
    f.close();
    */
    Stiva_de_caractere v;
    meniu( v );
    /*
    Nod *a = new Nod('a');
    Stiva_de_caractere stiva( a );
    cout << stiva.isempty();
    stiva.push('b');
    stiva.push('c');
    stiva.push('d');
    Stiva_de_caractere s( stiva ), s2;
    s2 = s;
    Stiva_de_caractere nou = stiva - s;
    cout << nou;
    Stiva_de_caractere x;
    cin >> x;
    cout << x;
    cout << endl << endl << x.strrev( "cal" );
    */
    return 0;
}