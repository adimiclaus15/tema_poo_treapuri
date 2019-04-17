#include <bits/stdc++.h>
using namespace std;
ifstream f("date.in");
ofstream g("date.out");
class Nod
{
protected:
    int valoare,prioritate;
    Nod *stanga;
    Nod *dreapta;
public:
    Nod()
    {
        this->valoare=0;
        this->prioritate=0;
        this->stanga=NULL;
        this->dreapta=NULL;
    }
    Nod(int valoare)
    {
        this->valoare=valoare;
        this->prioritate=rand()+1;
        this->stanga=NULL;
        this->dreapta=NULL;
    }
    Nod(const Nod &p)
    {
        this->valoare=p.valoare;
        this->prioritate=p.prioritate;
        this->stanga=p.stanga;
        this->dreapta=p.dreapta;
    }
    Nod & operator = (const Nod &p)
    {
        if(this!=&p)
        {

            this->valoare=p.valoare;
            this->prioritate=p.prioritate;
            this->stanga=p.stanga;
            this->dreapta=p.dreapta;
        }
        return *this;
    }
    bool operator < (const Nod &p) const
    {
        if(this->valoare<p.valoare)
        {
            return 1;
        }
        return 0;
    }
    bool operator == (const Nod &p) const
    {
        if(this->valoare==p.valoare)
        {
            return 1;
        }
        return 0;
    }
    bool operator != (const Nod &p) const
    {
        if(this->valoare!=p.valoare)
        {
            return 1;
        }
        return 0;
    }
    ~Nod()
    {
        this->valoare=0;
        this->prioritate=0;
        this->stanga=NULL;
        this->dreapta=NULL;
    }
    friend class Abc;
    friend class Arbore;
    friend class Treap;

};

class Arbore
{
protected:
    Nod *radacina;
    int nr_noduri;
public:
    Arbore()
    {
        this->nr_noduri=0;
        this->radacina=NULL;
    }
    Arbore(const Arbore &p)
    {
        //this->nr_noduri=p.nr_noduri;
        this->radacina=NULL;
        Copiaza(p.radacina);
    }
    Arbore & operator = (const Arbore &p)
    {
        if(this!=&p)
        {
            Taie();
            Copiaza(p.radacina);
        }
        return *this;
    }
    int Dimensiune()
    {
        return this->nr_noduri;
    }
    void CresteDimensiune()
    {
        this->nr_noduri++;
    }
    void ScadeDimensiune()
    {
        this->nr_noduri--;
    }
    Nod* Cauta(Nod*,int) const;///
    bool Cauta(int) const;///
    virtual Nod* Inserare(Nod*,int);///
    void Inserare(int);///
    virtual Nod* Stergere(Nod*,int);///
    void Stergere(int);///
    void Inordine(Nod*);///
    void Copiaza(Nod*);///
    Nod* Taie(Nod*);///
    void Taie();///
    int Inaltime(Nod*);
    int Inaltime();///
    Nod* Succesor(Nod*);
    void Frunze(Nod*);///
    void Frunze();///
    void Extrage(Nod*,int*,int&);///
    virtual void Prioritati(Nod *r);
    void Prioritati();
    friend istream & operator >> (istream &,Arbore &);///
    friend ostream & operator << (ostream &,Arbore &);///
    virtual ~Arbore()
    {
        Taie();
        this->nr_noduri=0;
    }
    virtual void Mesaj()=0;
};
void Arbore::Prioritati(Nod *r)
{
    if(r!=NULL)
    {
        Prioritati(r->stanga);
        g<<r->valoare<<" "<<r->prioritate<<"\n";
        Prioritati(r->dreapta);
    }
}
void Arbore::Prioritati()
{
    this->Prioritati(this->radacina);
}
Nod* Arbore::Cauta(Nod *r,int val) const
{
    if(r==NULL || r->valoare==val)
    {
        return r;
    }
    if(r->valoare<val)
    {
        return Cauta(r->dreapta,val);
    }
    else
    {
        return Cauta(r->stanga,val);
    }
}
bool Arbore::Cauta(int val) const
{
    if(Cauta(this->radacina,val)!=NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
Nod* Arbore::Inserare(Nod *r,int val)
{
    if(r==NULL)
    {
        r=new Nod(val);
        this->CresteDimensiune();
    }
    else
    {
        if(r->valoare<val)
        {
            r->dreapta=Inserare(r->dreapta,val);
        }
        else
        {
            r->stanga=Inserare(r->stanga,val);
        }
    }
    return r;
}
void Arbore::Inserare(int val)
{
    this->radacina=Inserare(this->radacina,val);
}
void Arbore::Inordine(Nod *r)
{
    if(r!=NULL)
    {
        Inordine(r->stanga);
        g<<r->valoare<<" ";
        Inordine(r->dreapta);
    }
}
void Arbore::Copiaza(Nod *r)
{
    if(r!=NULL)
    {
        this->Inserare(r->valoare);
        Copiaza(r->stanga);
        Copiaza(r->dreapta);
    }
}
Nod* Arbore::Taie(Nod *r)
{
    if(r==NULL)
    {
        return NULL;
    }
    Taie(r->stanga);
    Taie(r->dreapta);
    delete r;
    this->ScadeDimensiune();
    return NULL;
}
void Arbore::Taie()
{
    this->radacina=Taie(this->radacina);
}
istream & operator >> (istream &in,Arbore &arb)
{
    int i,n,x;
    in>>n;
    for(i=1;i<=n;i++)
    {
        in>>x;
        arb.Inserare(x);
    }
    return in;
}
ostream & operator << (ostream &out,Arbore &arb)
{
    arb.Inordine(arb.radacina);
    return out;
}
int Arbore::Inaltime(Nod *r)
{
    if(r==NULL)
    {
        return 0;
    }
    else
    {
        return 1+max(Inaltime(r->stanga),Inaltime(r->dreapta));
    }
}
int Arbore::Inaltime()
{
    return this->Inaltime(this->radacina);
}
void Arbore::Frunze(Nod *r)
{
    if(r!=NULL)
    {
        if(r->dreapta==NULL && r->stanga==NULL)
        {
            g<<r->valoare<<" ";
        }
        Frunze(r->stanga);
        Frunze(r->dreapta);
    }
}
void Arbore::Frunze()
{
    this->Frunze(this->radacina);
}
Nod* Arbore::Succesor(Nod *r)
{
    Nod *p=r;
    while(p->stanga!=NULL)
    {
        p=p->stanga;
    }
    return p;
}
Nod* Arbore::Stergere(Nod *r,int val)
{
    if(r==NULL)
    {
        return r;
    }
    if(val<r->valoare)
    {
        r->stanga=Stergere(r->stanga,val);
    }
    else
    {
        if(val>r->valoare)
        {
            r->dreapta=Stergere(r->dreapta,val);
        }
        else
        {
            if(r->stanga==NULL)
            {
                Nod *p=r->dreapta;
                delete r;
                return p;
            }
            else
            {
                if(r->dreapta==NULL)
                {
                    Nod *p=r->stanga;
                    delete r;
                    return p;
                }
            }
            Nod *p=Succesor(r->dreapta);
            r->valoare=p->valoare;
            r->dreapta=Stergere(r->dreapta,p->valoare);
        }
    }
    return r;
}
void Arbore::Stergere(int val)
{
    this->ScadeDimensiune();
    this->radacina=Stergere(this->radacina,val);
}
void Arbore::Extrage(Nod *r,int *v,int &nr)
{
    if(r!=NULL)
    {
        v[++nr]=r->valoare;
        Extrage(r->stanga,v,nr);
        Extrage(r->dreapta,v,nr);
    }
}


class Abc:public Arbore
{
public:
    Abc(): Arbore() {}
    Abc(const Abc &p): Arbore(p) {}
    Abc operator + (const Abc&);
    Abc operator * (const Abc&);
    Abc operator - (const Abc&);
    ~Abc() {}
    void Mesaj()
    {
        g<<"BST";
    }
};
Abc Abc::operator + (const Abc &p)
{
    Abc rez=*this;
    int v[100005],nr=0,i;
    Extrage(p.radacina,v,nr);
    for(i=1;i<=nr;i++)
    {
        //cout<<v[i]<<" ";
        if(rez.Cauta(v[i])==0)
        {
            rez.Inserare(v[i]);
        }
    }
    return rez;
}
Abc Abc::operator * (const Abc &p)
{
    Abc rez;
    int v[100005],nr=0,i;
    Extrage(p.radacina,v,nr);
    for(i=1;i<=nr;i++)
    {
        //cout<<v[i]<<" ";
        if(this->Cauta(v[i])==1)
        {
            rez.Inserare(v[i]);
        }
    }
    return rez;
}
Abc Abc::operator - (const Abc &p)
{
    Abc rez;
    int v[100005],nr=0,i;
    Extrage(this->radacina,v,nr);
    for(i=1;i<=nr;i++)
    {
        //cout<<v[i]<<" ";
        if(p.Cauta(v[i])==0)
        {
            rez.Inserare(v[i]);
        }
    }
    return rez;
}


class Treap : public Arbore
{
public:
    Treap(): Arbore() {}
    Treap(const Treap &p): Arbore(p) {}
    Nod* Inserare(Nod*,int);///
    void Inserare(int);///
    Nod* Stergere(Nod*,int);///
    void Stergere(int);///
    Nod* RotatieStanga(Nod*);///
    Nod* RotatieDreapta(Nod*);///
    void Prioritati(Nod *r);
    void Prioritati();
    Treap operator + (const Treap&);
    Treap operator * (const Treap&);
    Treap operator - (const Treap&);
    ~Treap() {}
    void Mesaj()
    {
        g<<"Treap";
    }
};
Nod* Treap::RotatieDreapta(Nod *y)
{
    Nod *x=y->stanga;
    Nod *z=x->dreapta;
    x->dreapta=y;
    y->stanga=z;
    return x;
}
Nod* Treap::RotatieStanga(Nod *x)
{
    Nod *y=x->dreapta;
    Nod *z=y->stanga;
    y->stanga=x;
    x->dreapta=z;
    return y;
}
Nod* Treap::Inserare(Nod *r,int val)
{
    if(r==NULL)
    {
        r=new Nod(val);
        this->CresteDimensiune();
    }
    else
    {
        if(r->valoare<val)
        {
            r->dreapta=Inserare(r->dreapta,val);
            if(r->dreapta->prioritate>r->prioritate)
            {
                r=RotatieStanga(r);
            }
        }
        else
        {
            r->stanga=Inserare(r->stanga,val);
            if(r->stanga->prioritate>r->prioritate)
            {
                r=RotatieDreapta(r);
            }
        }
    }
    return r;
}
void Treap::Inserare(int val)
{
    this->radacina=Inserare(this->radacina,val);
}
Nod* Treap::Stergere(Nod *r,int val)
{
    if(r==NULL)
    {
        return r;
    }
    else
    {
        if(val<r->valoare)
        {
            r->stanga=Stergere(r->stanga,val);
        }
        else
        {
            if(val>r->valoare)
            {
                r->dreapta=Stergere(r->dreapta,val);
            }
            else
            {
                if(r->stanga==NULL)
                {
                    Nod *p=r->dreapta;
                    delete r;
                    r=p;
                }
                else
                {
                    if(r->dreapta==NULL)
                    {
                        Nod *p=r->stanga;
                        delete r;
                        r=p;
                    }
                    else
                    {
                        if(r->stanga->prioritate<r->dreapta->prioritate)
                        {
                            r=RotatieStanga(r);
                            r->stanga=Stergere(r->stanga,val);
                        }
                        else
                        {
                            r=RotatieDreapta(r);
                            r->dreapta=Stergere(r->dreapta,val);
                        }
                    }
                }
            }
        }
    }
    return r;
}
void Treap::Stergere(int val)
{
    this->ScadeDimensiune();
    this->Stergere(this->radacina,val);
}
Treap Treap::operator + (const Treap &p)
{
    Treap rez=*this;
    int v[100005],nr=0,i;
    Extrage(p.radacina,v,nr);
    for(i=1;i<=nr;i++)
    {
        //cout<<v[i]<<" ";
        if(rez.Cauta(v[i])==0)
        {
            rez.Inserare(v[i]);
        }
    }
    return rez;
}
Treap Treap::operator * (const Treap &p)
{
    Treap rez;
    int v[100005],nr=0,i;
    Extrage(p.radacina,v,nr);
    for(i=1;i<=nr;i++)
    {
        //cout<<v[i]<<" ";
        if(this->Cauta(v[i])==1)
        {
            rez.Inserare(v[i]);
        }
    }
    return rez;
}
Treap Treap::operator - (const Treap &p)
{
    Treap rez;
    int v[100005],nr=0,i;
    Extrage(this->radacina,v,nr);
    for(i=1;i<=nr;i++)
    {
        if(p.Cauta(v[i])==0)
        {
            rez.Inserare(v[i]);
        }
    }
    return rez;
}
void Treap::Prioritati(Nod *r)
{
    if(r!=NULL)
    {
        Prioritati(r->stanga);
        g<<r->valoare<<" "<<r->prioritate<<"\n";
        Prioritati(r->dreapta);
    }
}
void Treap::Prioritati()
{
    this->Prioritati(this->radacina);
}
int main()
{
    return 0;
}
