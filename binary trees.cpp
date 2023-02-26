#include <iostream>
#include <queue>
#include <vector>

using namespace std;

template < typename T > class Nod {
    T val;
    Nod < T > *st, *dr;
public:
    T getVal() const
    {
        return this->val;
    }
    void setVal( T val = 0 )
    {
        this->val = val;
    }
    Nod < T >* getSt() const
    {
        return this->st;
    }
    void setSt( Nod < T > *st )
    {
        this->st = st;
    }
    Nod < T >* getDr() const
    {
        return this->dr;
    }
    void setDr( Nod < T > *dr )
    {
        this->dr = dr;
    }
    Nod( T val = 0 )
    {
        this->val = val;
        this->st = this->dr = NULL;
    }
    ~Nod()
    {
        this->val = 0;
        this->st = this->dr = NULL;
    }
    Nod < T >& operator=( Nod < T > &n )
    {
        this->val = n.val;
        this->st = n.st;
        this->dr = n.dr;
    }
    friend istream& operator>>( istream&, Nod < T >& );
    friend ostream& operator<<( ostream&, Nod < T >& );
};

template < typename T > istream& operator>>( istream& in, Nod < T > &n )
{
    in >> n.val;
    n.st = n.dr = NULL;
    return in;
}

template < typename T > ostream& operator<<( ostream& out, Nod < T > &n )
{
    out << n.val;
    return out;
}

template < typename T > class ArboreBinar {
protected:
    Nod < T > *rad;
public:
    void setRad( Nod < T > *rad )
    {
        this->rad = rad;
    }
    Nod < T >* getRad() const
    {
        return this->rad;
    }
    ArboreBinar()
    {
        this->rad = NULL;
    }
    virtual Nod < T >* adaugare( Nod < T > *, T );
    virtual void afisareRSD( Nod < T > * ) const;
    virtual Nod < T >* stergere( Nod < T > *, T );
    virtual void citire();
    virtual bool cautare( Nod < T >*, T );
};

template < typename T > bool ArboreBinar < T >::cautare( Nod < T > *nod, T x )
{
    if( !nod )
        return false;
    if( nod->getVal() == x )
        return true;
    return this->cautare( nod->getSt(), x ) || this->cautare( nod->getDr(), x );
}

template < typename T > void ArboreBinar < T >::citire()
{
    this->setRad( NULL );
    int n;
    cin >> n;
    for( int i = 0; i < n; ++i )
    {
        T x;
        cin >> x;
        this->setRad( this->adaugare( this->getRad(), x ) );
    }
}

template < typename T > Nod < T > * ArboreBinar < T >::stergere( Nod < T > *rad, T x )
{
    if( !rad )
        return NULL;
    if( !rad->getSt() && !rad->getDr() )
    {
        if( rad->getVal() == x )
            return NULL;
        return rad;
    }
    Nod < T > *deSters;
    queue < Nod < T >* > q;
    q.push( rad );
    while( !q.empty() )
    {
        deSters = q.front();
        q.pop();
        if( deSters->getSt() )
            q.push( deSters->getSt() );
        if( deSters->getDr() )
            q.push( deSters->getDr() );
    }
    q.push( rad );
    while( !q.empty() )
    {
        Nod < T > *aux = q.front();
        q.pop();
        if( aux->getVal() == x )
            aux->setVal( deSters->getVal() );
        if( aux->getSt() )
        {
            q.push( aux->getSt() );
            if( aux->getSt() == deSters )
                aux->setSt( NULL );
        }
        if( aux->getDr() )
        {
            q.push( aux->getDr() );
            if( aux->getDr() == deSters )
                aux->setDr( NULL );
        }
    }
    return rad;
}

template < typename T > void ArboreBinar < T >::afisareRSD( Nod < T > *nod ) const
{
    if( !nod )
        return;
    cout << nod->getVal() << " ";
    this->afisareRSD( nod->getSt() );
    this->afisareRSD( nod->getDr() );
}

template < typename T > Nod < T > * ArboreBinar < T >::adaugare( Nod < T > *rad, T x )
{
    if( !rad )
    {
        rad = new Nod < T >( x );
        return rad;
    }
    queue < Nod < T >* > q;
    q.push( rad );
    while( !q.empty() )
    {
        Nod < T > *aux = q.front();
        q.pop();
        if( aux->getSt() )
            q.push( aux->getSt() );
        else
        {
            aux->setSt( new Nod < T >( x ) );
            return rad;
        }
        if( aux->getDr() )
            q.push( aux->getDr() );
        else
        {
            aux->setDr( new Nod < T >( x ) );
            return rad;
        }
    }
    return rad;
}

template < typename T > class ArboreBinarDeCautare: public ArboreBinar < T > {
public:
    Nod < T >* adaugare( Nod < T >*, T );
    Nod < T >* celMaiDinStanga( Nod < T > * );
    Nod < T >* stergere( Nod < T >*, T );
    bool cautare( Nod < T >*, T );
    ArboreBinarDeCautare(): ArboreBinar < T >() {}
};

template < typename T > bool ArboreBinarDeCautare < T >::cautare( Nod < T > *nod, T x )
{
    if( !nod )
        return false;
    if( nod->getVal() == x )
        return true;
    if( x < nod->getVal() )
        return this->cautare( nod->getSt(), x );
    return this->cautare( nod->getDr(), x );
}

template < typename T > Nod < T > * ArboreBinarDeCautare < T >::celMaiDinStanga( Nod < T > *nod )
{
    Nod < T > *aux = nod;
    while( aux && aux->getSt() )
        aux = aux->getSt();
    return aux;
}

template < typename T > Nod < T > * ArboreBinarDeCautare < T >::stergere( Nod < T > *rad, T x )
{
    if( !rad )
        return rad;
    if( rad->getVal() == x )
    {
        if( !rad->getSt() && !rad->getDr() )
            return NULL;
        if( !rad->getSt() )
        {
            Nod < T > *aux = rad->getDr();
            delete rad;
            return aux;
        }
        if( !rad->getDr() )
        {
            Nod < T > *aux = rad->getSt();
            delete rad;
            return aux;
        }
        Nod < T > *aux = this->celMaiDinStanga( rad->getDr() );
        rad->setVal( aux->getVal() );
        rad->setDr( this->stergere( rad->getDr(), aux->getVal() ) );
    }
    else if( x < rad->getVal() )
        rad->setSt( this->stergere( rad->getSt(), x ) );
    else
        rad->setDr( this->stergere( rad->getDr(), x ) );
    return rad;
}

template < typename T > Nod < T > * ArboreBinarDeCautare < T >::adaugare( Nod < T > *rad, T x )
{
    if( !rad )
    {
        rad = new Nod < T >( x );
        return rad;
    }
    if( x < rad->getVal() )
        rad->setSt( this->adaugare( rad->getSt(), x ) );
    else
        rad->setDr( this->adaugare( rad->getDr(), x ) );
    return rad;
}

vector < ArboreBinar < int > * > arbori;

void meniu();

void clear()
{
    for( int i = 0; i < 500; ++i )
        cout <<"\n";
}

void afiseaza()
{
    clear();
    cout << "Introduceti pozitia arborelui pe care doriti sa il afisati: ";
    int poz;
    cin >> poz;
    if( poz < arbori.size() && poz >= 0 )
        arbori[poz]->afisareRSD( arbori[poz]->getRad() );
    cout << "\nApasati ENTER pentru a continua.";
    cin.get();
    cin.get();
    meniu();
}

void cauta()
{
    clear();
    cout << "Introduceti pozitia arborelui in care doriti sa cautati: ";
    int poz;
    cin >> poz;
    if( poz < arbori.size() && poz >= 0 )
    {
        cout << "\nIntroduceti valoarea nodului pe care doriti sa il cautati:\n";
        int x;
        cin >> x;
        cout << ( arbori[poz]->cautare( arbori[poz]->getRad(), x ) ? "\nNodul a fost gasit." : "\nNodul NU a fost gasit." );
        cout << "\nApasati ENTER pentru a continua.";
        cin.get();
        cin.get();
    }
    meniu();
}

void sterge()
{
    clear();
    cout << "Introduceti pozitia arborelui din care doriti sa stergeti: ";
    int poz;
    cin >> poz;
    if( poz < arbori.size() && poz >= 0 )
    {
        cout << "\nIntroduceti valoarea nodului pe care doriti sa il stergeti:\n";
        int x;
        cin >> x;
        arbori[poz]->setRad( arbori[poz]->stergere( arbori[poz]->getRad(), x ) );
    }
    meniu();
}

void insereaza()
{
    clear();
    cout << "Introduceti pozitia arborelui in care doriti sa inserati: ";
    int poz;
    cin >> poz;
    if( poz < arbori.size() && poz >= 0 )
    {
        cout << "\nIntroduceti valoarea nodului pe care doriti sa il inserati:\n";
        int x;
        cin >> x;
        arbori[poz]->setRad( arbori[poz]->adaugare( arbori[poz]->getRad(), x ) );
    }
    meniu();
}

void citesteArbore()
{
    clear();
    cout << "Introduceti pozitia arborelui pe care doriti sa il cititi: ";
    int poz;
    cin >> poz;
    if( poz < arbori.size() && poz >= 0 )
    {
        cout << "\nIntroduceti un numar n si n valori ale nodurilor arborelui, care vor fi inserate in aceasta ordine:\n";
        arbori[poz]->citire();
    }
    meniu();
}

void stergeArbore()
{
    clear();
    cout << "Introduceti pozitia arborelui pe care doriti sa il stergeti: ";
    int poz;
    cin >> poz;
    if( poz < arbori.size() && poz >= 0 )
        arbori.erase( arbori.begin() + poz );
    meniu();
}

void adaugaArbore()
{
    clear();
    cout << "Alegeti o optiune:\n";
    cout << "1. Arbore binar\n";
    cout << "2. Arbore binar de cautare\n";
    int optiune;
    cin >> optiune;
    if( optiune == 1 )
    {
        ArboreBinar < int > *nou = new ArboreBinar < int >;
        arbori.push_back( nou );
    }
    else if( optiune == 2 )
    {
        ArboreBinarDeCautare < int > *nou = new ArboreBinarDeCautare < int >;
        arbori.push_back( nou );
    }
    meniu();
}

void meniu()
{
    clear();
    cout << "Alegeti o optiune:\n";
    cout << "1. Adauga arbore\n";
    cout << "2. Sterge arbore\n";
    cout << "3. Citeste arbore\n";
    cout << "4. Insereaza in arbore\n";
    cout << "5. Sterge din arbore\n";
    cout << "6. Cauta in arbore\n";
    cout << "7. Afiseaza arbore (preordine)\n";
    cout << "8. Iesire\n";
    int optiune;
    cin >> optiune;
    if( optiune == 1 )
        adaugaArbore();
    else if( optiune == 2 )
        stergeArbore();
    else if( optiune == 3 )
        citesteArbore();
    else if( optiune == 4 )
        insereaza();
    else if( optiune == 5 )
        sterge();
    else if( optiune == 6 )
        cauta();
    else if( optiune == 7 )
        afiseaza();
}

int main()
{
    meniu();
    return 0;
}