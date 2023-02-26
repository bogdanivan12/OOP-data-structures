#include <iostream>
#include <cstring>

using namespace std;

class Nod{
    Nod* next;
protected:
    int info;
public:
    int getInfo()
    {
        return this->info;
    }
    Nod* getNext()
    {
        return this->next;
    }
    void setInfo( int info )
    {
        this->info = info;
    }
    void setNext( Nod* next )
    {
        this->next = next;
    }
    Nod( int info = 0 )
    {
        this->info = info;
        this->next = NULL;
    }
    Nod( Nod& n )
    {
        this->info = n.info;
        this->next = n.next;
    }
    Nod& operator=( Nod& n )
    {
        this->info = n.info;
        this->next = n.next;
        return *this;
    }
    Nod& operator=( int& n )
    {
        this->info = n;
        this->next = NULL;
        return *this;
    }
    Nod& operator-()
    {
        this->info = -this->info;
        return *this;
    }
    Nod& operator++()
    {
        ++this->info;
        return *this;
    }
    Nod& operator++( int )
    {
        ++this->info;
        return *this;
    }
    friend istream& operator>>( istream&, Nod& );
    friend ostream& operator<<( ostream&, Nod& );
};

istream& operator>>( istream& in, Nod& n )
{
    in >> n.info;
    return in;
}

ostream& operator<<( ostream& out, Nod& n )
{
    out << n.info;
    return out;
}

class NodDublu: public Nod{
    NodDublu *prev, *next;
public:
    NodDublu* getNext()
    {
        return this->next;
    }
    NodDublu* getPrev()
    {
        return this->prev;
    }
    void setNext( NodDublu* next )
    {
        this->next = next;
    }
    void setPrev( NodDublu* prev )
    {
        this->prev = prev;
    }
    NodDublu( int info = 0 )
    {
        this->info = info;
        this->next = NULL;
        this->prev = NULL;
    }
    NodDublu( NodDublu& n )
    {
        this->info = n.info;
        this->next = n.next;
        this->prev = n.prev;
    }
    NodDublu& operator=( NodDublu& n )
    {
        this->setInfo( n.getInfo() );
        this->setNext( n.getNext() );
        this->setPrev( n.getPrev() );
        return *this;
    }
    NodDublu& operator=( int& n )
    {
        this->setInfo( n );
        this->setNext( NULL );
        this->setPrev( NULL );
        return *this;
    }
};

class LDI{
    NodDublu *first, *last;
protected:
    static int cnt;
    int dim;
public:
    virtual void tipLista()
    {
        cout << "Aceasta este o lista dublu inlantuita.\n";
    }
    int getDim()
    {
        return this->dim;
    }
    NodDublu* getFirst()
    {
        return this->first;
    }
    NodDublu* getLast()
    {
        return this->last;
    }
    static void nrListe()
    {
        cout << "Sunt folosite in total " << cnt << " liste.\n";
    }
    LDI( NodDublu *n = NULL )
    {
        ++cnt;
        this->first = this->last = n;
        if( n == NULL )
            dim = 0;
        else
            dim = 1;
    }
    LDI( int info )
    {
        ++cnt;
        dim = 1;
        first = last = new NodDublu( info );
    }
    LDI( LDI& );
    ~LDI();
    void push_front( int info )
    {
        ++dim;
        NodDublu *aux = new NodDublu( info );
        aux->setNext( first );
        if( first != NULL )
            first->setPrev( aux );
        this->first = aux;
        if( last == NULL )
            this->last = aux;
    }
    void push_back( int info )
    {
        ++dim;
        NodDublu *aux = new NodDublu( info );
        aux->setPrev( last );
        if( last != NULL )
            last->setNext( aux );
        this->last = aux;
        if( first == NULL )
            first = aux;
    }
    void pop_back()
    {
        if( this->dim == 1 )
        {
            delete first;
            first = last = NULL;
            --dim;
        }
        else if( this->dim )
        {
            NodDublu *aux = last;
            last = last->getPrev();
            last->setNext( NULL );
            delete aux;
            --dim;
        }
    }
    void pop_front()
    {
        if( this->dim == 1 )
        {
            delete first;
            first = last = NULL;
            --dim;
        }
        else if( this->dim )
        {
            NodDublu *aux = first;
            first = ( NodDublu* ) first->getNext();
            first->setPrev( NULL );
            delete aux;
            --dim;
        }
    }
    void insert( int, int );
    void erase( int );
    void afisare();
    LDI& operator=( LDI& );
    friend ostream& operator<<( ostream&, LDI& );
    friend istream& operator>>( istream&, LDI& );
    LDI& operator+( LDI& );
    LDI& operator+=( LDI& );
    int indexOf( int ); // indexul celui mai mic element mai mic sau egal cu parametrul, lista fiind in ordine crescatoare
};

int LDI::cnt = 0;

int LDI::indexOf( int n )
{
    int i;
    NodDublu *p;
    for( i = 0, p = first; p != NULL && p->getInfo() < n; ++i, p = p->getNext() );
    return i;
}

void LDI::insert( int val, int poz )
{
    if( poz == 0 )
        this->push_front( val );
    else if( poz == dim )
        this->push_back( val );
    else if( poz > 0 && poz < dim )
    {
        ++dim;
        NodDublu *p = this->first;
        int i;
        for( i = 0; i < poz; ++i )
            p = p->getNext();
        NodDublu *aux = new NodDublu( val );
        aux->setNext( p );
        aux->setPrev( p->getPrev() );
        p->getPrev()->setNext( aux );
        p->setPrev( aux );
    }
}

void LDI::erase( int poz )
{
    if( poz == 0 )
        this->pop_front();
    else if( poz == dim - 1 )
        this->pop_back();
    else if( poz > 0 && poz < dim )
    {
        --dim;
        NodDublu *p;
        int i;
        for( p = first, i = 0; i < poz; ++i, p = ( NodDublu* ) p->getNext() );
        p->getPrev()->setNext( p->getNext() );
        p->getNext()->setPrev( p->getPrev() );
        delete p;
    }
}

LDI& LDI::operator+=( LDI& lista )
{
    *this = *this + lista;
    return *this;
}

LDI& LDI::operator+( LDI& lista )
{
    LDI *aux = new LDI( *this );
    for( NodDublu *p = lista.first; p != NULL; p = ( NodDublu* ) p->getNext() )
        aux->push_back( p->getInfo() );
    return *aux;
}

LDI::LDI( LDI& lista )
{
    ++cnt;
    this->dim = lista.dim;
    this->first = this->last = NULL;
    for( NodDublu *p = lista.first; p != NULL; p = ( NodDublu* ) p->getNext() )
        this->push_back( p->getInfo() );
}

LDI& LDI::operator=( LDI& lista )
{
    this->dim = lista.getDim();
    this->first = this->last = NULL;
    for( NodDublu *p = lista.first; p != NULL; p = p->getNext() )
        this->push_back( p->getInfo() );
    return *this;
}

istream& operator>>( istream& in, LDI& lista )
{
    LDI aux;
    int n;
    in >> n;
    for( int i = 0; i < n; ++i )
    {
        int x;
        in >> x;
        aux.push_back( x );
    }
    lista = aux;
    return in;
}

ostream& operator<<( ostream& out, LDI& lista )
{
    for( NodDublu *p = lista.getFirst(); p != NULL; p = p->getNext() )
        out << p->getInfo() << " ";
    out << endl;
    return out;
}

LDI::~LDI()
{
    --cnt;
    while( first != NULL )
    {
        NodDublu *aux = first;
        first = (NodDublu *) first->getNext();
        delete aux;
    }
}

void LDI::afisare()
{
    for( NodDublu *p = last; p != NULL; p = ( NodDublu* ) p->getPrev() )
        cout << p->getInfo() << " ";
    cout << endl;
}

class LSI: public LDI{
    Nod *first, *last;
public:
    void tipLista()
    {
        cout << "Aceasta este o lista simplu inlantuita.\n";
    }
    Nod* getFirst()
    {
        return this->first;
    }
    LSI()
    {
        dim = 0;
        first = last = NULL;
    }
    LSI( int info )
    {
        dim = 1;
        first = last = new Nod( info );
    }
    LSI( LSI& );
    void push_front( int info )
    {
        ++dim;
        Nod *aux = new Nod( info );
        aux->setNext( first );
        this->first = aux;
        if( last == NULL )
            this->last = aux;
    }
    void push_back( int info )
    {
        ++dim;
        Nod *aux = new Nod( info );
        if( last != NULL )
            last->setNext( aux );
        this->last = aux;
        if( first == NULL )
            first = aux;
    }
    void pop_front()
    {
        if( this->dim == 1 )
        {
            delete first;
            first = last = NULL;
            --dim;
        }
        else if( this->dim )
        {
            --dim;
            Nod *aux = first;
            first = first->getNext();
            delete aux;
        }
    }
    void pop_back();
    void insert( int, int );
    void erase( int );
    LSI& operator=( LDI& );
    friend istream& operator>>( istream&, LSI& );
    friend ostream& operator<<( ostream&, LSI& );
};

void LSI::insert( int val, int poz )
{
    if( poz == 0 )
        this->push_front( val );
    else if( poz == dim )
        this->push_back( val );
    else if( poz > 0 && poz < dim )
    {
        ++dim;
        Nod *p = this->first;
        int i;
        for( i = 0; i < poz - 1; ++i )
            p = p->getNext();
        Nod *aux = new Nod( val );
        aux->setNext( p->getNext() );
        p->setNext( aux );
    }
}

void LSI::erase( int poz )
{
    if( poz == 0 )
        this->pop_front();
    else if( poz == dim - 1 )
        this->pop_back();
    else if( poz > 0 && poz < dim )
    {
        --dim;
        Nod *p;
        int i;
        for( p = first, i = 0; i < poz - 1; ++i, p = ( NodDublu* ) p->getNext() );
        Nod *aux = p->getNext();
        p->setNext( aux->getNext() );
        delete aux;
    }
}

void LSI::pop_back()
{
    if( this->dim == 1 )
    {
        delete first;
        --dim;
        first = last = NULL;
    }
    else if( this->dim )
    {
        Nod *aux = last, *p;
        for( p = ( Nod* ) first; p->getNext() != last; p = ( Nod* ) p->getNext() );
        last = p;
        last->setNext( NULL );
        delete aux;
        --dim;
    }
}

istream& operator>>( istream& in, LSI& lista )
{
    LSI aux;
    int n;
    in >> n;
    for( int i = 0; i < n; ++i )
    {
        int x;
        in >> x;
        aux.push_back( x );
    }
    lista = aux;
    return in;
}

ostream& operator<<( ostream& out, LSI& lista )
{
    for( Nod *p = lista.getFirst(); p != NULL; p = p->getNext() )
        out << p->getInfo() << " ";
    out << endl;
    return out;
}

LSI& LSI::operator=( LDI& lista )
{
    this->dim = lista.getDim();
    this->first = this->last = NULL;
    for( Nod *p = lista.getFirst(); p != NULL; p = p->getNext() )
        this->push_back( p->getInfo() );
    return *this;
}

LSI::LSI( LSI& lista )
{
    ++cnt;
    this->dim = lista.getDim();
    this->first = this->last = NULL;
    for( Nod *p = lista.first; p != NULL; p = p->getNext() )
        this->push_back( p->getInfo() );
}

void clear()
{
    for( int i = 0; i < 200; ++i )
        cout << endl;
}

void meniu( LDI& );

void citire( LDI &v )
{
    clear();
    cout << "------------------CITIRE------------------" << endl << endl;
    cout << "Introduceti un numar n, iar apoi un sir de n numere:" << endl;
    cout << endl << " -> ";
    cin.get();
    cin >> v;
    cout << endl << endl << "Lista a fost citita cu succes. Apasati ENTER pentru a continua.";
    cin.get();
    cin.get();
    meniu( v );
}

void afisare( LDI &v )
{
    clear();
    cout << "------------------AFISARE------------------" << endl << endl;
    cout << "Elementele listei sunt: " << v << endl;
    cout << "Apasati ENTER pentru a continua." << endl;
    cin.get();
    cin.get();
    meniu( v );
}

void iesire( LDI &v )
{
    clear();
    cout << "------------------IESIRE------------------" << endl << endl;
    cout << "Sigur doriti sa iesiti?" << endl;
    cout << "1. DA" << endl;
    cout << "2. NU" << endl;
    bool ok = false;
    while( !ok )
    {
        try
        {
            int optiune;
            cout << endl << " -> ";
            cin >> optiune;
            cout << endl;
            if( optiune < 1 || optiune > 2 )
                throw 1;
            else
            {
                ok = true;
                if( optiune == 2 )
                    meniu( v );
            }
        }
        catch (...)
        {
            cout << "Eroare: Nu ati introdus un numar intre 1 si 2. Introduceti alt numar." << endl;
        }
    }
}

void adaugareInceput( LDI &v )
{
    clear();
    cout << "------------------PUSH_FRONT------------------" << endl << endl;
    cout << "Introduceti numarul pe care doriti sa il adaugati la inceputul listei" << endl;
    cout << endl << " -> ";
    int c;
    cin >> c;
    v.push_front( c );
    cout << "Numarul " << c << " a fost adaugat cu succes la inceputul listei. Apasati ENTER pentru a continua.";
    cin.get();
    cin.get();
    meniu( v );
}

void adaugareFinal( LDI &v )
{
    clear();
    cout << "------------------PUSH_BACK------------------" << endl << endl;
    cout << "Introduceti numarul pe care doriti sa il adaugati la finalul listei" << endl;
    cout << endl << " -> ";
    int c;
    cin >> c;
    v.push_back( c );
    cout << "Numarul " << c << " a fost adaugat cu succes la finalul listei. Apasati ENTER pentru a continua.";
    cin.get();
    cin.get();
    meniu( v );
}

void adaugareInsert( LDI &v )
{
    clear();
    cout << "------------------INSERT------------------" << endl << endl;
    cout << "Introduceti un numar si pozitia la care doriti sa il inserati." << endl;
    cout << endl << " -> ";
    int nr, poz;
    cin >> nr >> poz;
    v.insert( nr, poz );
    if( poz >= 0 && poz <= v.getDim() )
        cout << "Numarul " << nr << " a fost adaugat cu succes pe pozitia " << poz << ". Apasati ENTER pentru a continua.";
    else
        cout << "Numarul " << nr << " NU a fost adaugat pe pozitia " << poz << ", deoarece aceasta nu exista. Apasati ENTER pentru a continua.";
    cin.get();
    cin.get();
    meniu( v );
}

void stergereInceput( LDI &v )
{
    clear();
    cout << "------------------POP_FRONT------------------" << endl << endl;
    if( v.getFirst() == NULL )
        cout << "Eroare: Lista este goala. Apasati ENTER pentru a continua.";
    else
    {
        int c = v.getFirst()->getInfo();
        v.pop_front();
        cout << "Numarul " << c << " a fost sters cu succes de la inceputul listei. Apasati ENTER pentru a continua.";
    }
    cin.get();
    cin.get();
    meniu( v );
}

void stergereFinal( LDI &v )
{
    clear();
    cout << "------------------POP_BACK------------------" << endl << endl;
    if( v.getFirst() == NULL )
        cout << "Eroare: Lista este goala. Apasati ENTER pentru a continua.";
    else
    {
        int c = v.getLast()->getInfo();
        v.pop_back();
        cout << "Numarul " << c << " a fost sters cu succes de la finalul listei. Apasati ENTER pentru a continua.";
    }
    cin.get();
    cin.get();
    meniu( v );
}

void stergereErase( LDI &v )
{
    clear();
    cout << "------------------ERASE------------------" << endl << endl;
    if( v.getFirst() == NULL )
        cout << "Eroare: Lista este goala. Apasati ENTER pentru a continua.";
    else
    {
        cout << "Introduceti pozitia de la care doriti sa stergeti." << endl;
        cout << endl << " -> ";
        int poz;
        cin >> poz;
        if( poz >= 0 && poz < v.getDim() )
        {
            v.erase( poz );
            cout << "Numarul de pe pozitia " << poz << " a fost sters cu succes. Apasati ENTER pentru a continua.";
        }
        else
            cout << "EROARE: Pozitie indisponibila. Apasati ENTER pentru a continua.";
    }
    cin.get();
    cin.get();
    meniu( v );
}

void sortare( LDI &v )
{
    clear();
    cout << "------------------SORTARE------------------" << endl << endl;
    cout << "Introduceti un numar n, iar apoi un sir de n numere:" << endl;
    cout << endl << " -> ";
    cin.get();
    int n;
    cin >> n;
    for( int i = 0; i < n; ++i )
    {
        int x;
        cin >> x;
        v.insert( x, v.indexOf( x ) );
    }
    cout << endl << endl << "Lista a fost citita si sortata cu succes. Apasati ENTER pentru a continua.";
    cin.get();
    cin.get();
    meniu( v );
}

void meniu( LDI &v )
{
    clear();
    cout << "---------------------MENIU---------------------" << endl << endl;
    cout << "1. Citeste lista dublu inlantuita" << endl;
    cout << "2. Adauga un element la inceputul listei" << endl;
    cout << "3. Adauga un element la finalul listei" << endl;
    cout << "4. Adauga un element la o anumita pozitie" << endl;
    cout << "5. Sterge un element de la inceputul listei" << endl;
    cout << "6. Sterge un element de la finalul listei" << endl;
    cout << "7. Sterge un element de la o anumita pozitie" << endl;
    cout << "8. Afiseaza lista" << endl;
    cout << "9. Sortare prin inserare directa" << endl;
    cout << "0. Iesire" << endl;
    bool ok = false;
    while( !ok )
    {
        try
        {
            int optiune;
            cout << endl << " -> ";
            cin >> optiune;
            cout << endl;
            if( optiune < 0 || optiune > 9 )
                throw 1;
            else
            {
                ok = true;
                
                if( optiune == 1 )
                    citire( v );
                else if( optiune == 2 )
                    adaugareInceput( v );
                else if( optiune == 3 )
                    adaugareFinal( v );
                else if( optiune == 4 )
                    adaugareInsert( v );
                else if( optiune == 5 )
                    stergereInceput( v );
                else if( optiune == 6 )
                    stergereFinal( v );
                else if( optiune == 7 )
                    stergereErase( v );
                else if( optiune == 8 )
                    afisare( v );
                else if( optiune == 9 )
                    sortare( v );
                else
                    iesire( v );
                    
            }
        }
        catch (...)
        {
            cout << "Eroare: Nu ati introdus un numar intre 0 si 9. Introduceti alt numar." << endl;
        }
    }
}

int main()
{
    LDI v;
    meniu( v );
    return 0;
}