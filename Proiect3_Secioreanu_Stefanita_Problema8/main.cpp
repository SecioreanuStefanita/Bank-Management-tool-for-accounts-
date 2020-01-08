#include <iostream>
#include<string.h>
#include<bits/stdc++.h>
using namespace std;


class Cont
{
protected:
    static int nr_conturi;
    int id_cont;
    string nume;
    string data_deschiderii;
    double sold;
    string moneda;
protected:
    int nr_tranzactii_gratuite;
public:
    Cont();
    Cont(int id_cont,string nume,string data_deschiderii,double sold,string moneda,int nr_tranzactii_gratuite);
    virtual ~Cont();
    Cont(Cont const &);
    Cont operator =(Cont const  &);
    friend istream& operator>>(istream&,Cont&);
    friend ostream& operator<<(ostream&,Cont&);
    virtual void afisare(ostream&);
    virtual void retragere(double);
    virtual void depunere(double);


};
 int Cont::nr_conturi=0;
Cont::Cont()
{
    nr_conturi++;
    id_cont=0;
    nume="";
    data_deschiderii="";
    sold=0;
    moneda="";
    nr_tranzactii_gratuite=0;
}
Cont::Cont(int id_cont,string nume,string data_deschiderii,double sold,string moneda,int nr_tranzactii_gratuite)
{
    nr_conturi++;
    this->id_cont=id_cont;
    this->nume=nume;
    this->moneda=moneda;
    this->data_deschiderii=data_deschiderii;
    this->nr_tranzactii_gratuite=nr_tranzactii_gratuite;
    this->moneda=moneda;
    this->sold=sold;
}

Cont::~Cont()
{
    nr_conturi--;
}

Cont::Cont(const Cont&ob)
{
    nr_conturi++;
    nume=ob.nume;
    id_cont=ob.id_cont;
    moneda=ob.moneda;
    data_deschiderii=ob.data_deschiderii;
    sold=ob.sold;
    nr_tranzactii_gratuite=ob.nr_tranzactii_gratuite;
}

Cont Cont::operator=(Cont const &ob)
{
    if(this!=&ob)
    {
    nume=ob.nume;
    id_cont=ob.id_cont;
    moneda=ob.moneda;
    data_deschiderii=ob.data_deschiderii;
    sold=ob.sold;
    nr_tranzactii_gratuite=ob.nr_tranzactii_gratuite;
    }
    return (*this);
}

istream& operator>>(istream& in,Cont& ob)
{
    int id_cont;string nume;string data_deschiderii;double sold;string moneda;int nr_tranzactii_gratuite;
        in>>id_cont;
        in>>nume;
        in>>data_deschiderii;
        in>>sold;
        in>>moneda;
        in>>nr_tranzactii_gratuite;
        nume=ob.nume;
        id_cont=ob.id_cont;
        moneda=ob.moneda;
        data_deschiderii=ob.data_deschiderii;
        sold=ob.sold;
        nr_tranzactii_gratuite=ob.nr_tranzactii_gratuite;

    return in;
}
ostream& operator<<(ostream& out,Cont& ob)
{
     out<<endl;
    out<<"Id :"<<ob.id_cont;
    out<<endl;
    out<<"Nume :"<<ob.nume;
    out<<endl;
    out<<"Data deschiderii contului :"<<ob.data_deschiderii;
        out<<endl;
    out<<"Sold curent :"<<ob.sold<<" "<<ob.moneda;
        out<<endl;
    out<<"Numar de tranzactii gratuite ramase :"<<ob.nr_tranzactii_gratuite;
        out<<endl;

        out<<endl;
        out<<"---------------------------------------------------------------------";
        return out;

}
void Cont::afisare(ostream&out)
{
    out<<(*this);
}


void Cont::depunere(double valuta)
{
    this->sold+=valuta;
}

void Cont::retragere(double valuta)
{
    if(nr_tranzactii_gratuite!=0)
        try
        {
            if(valuta>sold)
                throw 0;
            nr_tranzactii_gratuite--;
            sold-=valuta;
        }
        catch(int exceptie)
        {
            cout<<"Fonduri insuficiente!\n";
        }
    else
        try
        {
            if(valuta+10>sold)
                throw 0;
            sold-=valuta+10;
        }
        catch(int exceptie)
        {
            cout<<"Fonduri insuficiente!";
        }

}

class Cont_economii:public Cont
{
    double rata_dobanzii;
     string istoric;
 public:
    Cont_economii();
    Cont_economii(int id_cont,string nume,string data_deschiderii,double sold,string moneda,int nr_tranzactii_gratuite,double rata_dobanzii,string istoric);
    ~Cont_economii();
    Cont_economii(const Cont_economii&);
    void retragere(double);
    void depunere(double);
    friend istream& operator>>(istream&,Cont_economii&);
    friend ostream& operator<<(ostream&,Cont_economii&);
    void afisare(ostream&);
    Cont_economii operator=(Cont_economii const &);
};

Cont_economii::Cont_economii():Cont()
{
    rata_dobanzii=0;
    istoric="";
}
Cont_economii::Cont_economii(int id_cont,string nume,string data_deschiderii,double sold,string moneda,int nr_tranzactii_gratuite,double rata_dobanzii,string istoric)
:Cont(id_cont,nume,data_deschiderii,sold,moneda,nr_tranzactii_gratuite)
{
    this->rata_dobanzii=rata_dobanzii;
    string temp=to_string(sold);
    this->istoric+="Creare Cont cu suma imprumutata de :";
    this->istoric+=istoric;
}
Cont_economii::~Cont_economii() {}

Cont_economii::Cont_economii(const Cont_economii& ob):Cont(ob)
{
    rata_dobanzii=ob.rata_dobanzii;
    string temp;
    istoric+=" ";
    temp=to_string(sold);
    istoric+= temp;
}

void Cont_economii::depunere(double valuta)
{
    this->sold=sold+sold*rata_dobanzii;
    this->sold-=valuta;
    if(sold==0){cout<<endl<<"Datorie Achitata";}
    else
    {
        this->istoric+=" Achitat suma in valuare de :";
    string temp=to_string(valuta);
    this->istoric+=temp;
    }
}

void Cont_economii::retragere(double valuta)
{
    cout<<"Nu se mai pot imprumuta bani pana la achitarea datoriei de :";
    cout<<sold+sold*rata_dobanzii;
}

void Cont_economii::afisare(ostream &out)
{    out<<endl;
    this->Cont::afisare(out);
    out<<" Istoricul tranzactiilor este : "<<this->istoric;
        out<<endl;
        out<<"Rata dobanzii este : "<<this->rata_dobanzii;
        out<<endl;
        out<<endl;
         out<<"---------------------------------------------------------------------";
}

ostream& operator<<(ostream& out,Cont_economii& ob)
{
      out<<endl;
     out<<"Id :"<<ob.id_cont;
    out<<endl;
    out<<"Nume :"<<ob.nume;
    out<<endl;
    out<<"Data deschiderii contului :"<<ob.data_deschiderii;
        out<<endl;
    out<<"Sold curent :"<<ob.sold<<" "<<ob.moneda;
        out<<endl;
    out<<" Istoricul tranzactiilor este : "<<ob.istoric;
        out<<endl;
        out<<"Rata dobanzii este : "<<ob.rata_dobanzii;
        out<<endl;
        out<<endl;
         out<<"---------------------------------------------------------------------";
        return out;

}

istream& operator>>(istream& in,Cont_economii& ob)
{
    int id_cont;string nume;string data_deschiderii;double sold;string moneda;int nr_tranzactii_gratuite;
    double rata_dobanzii;string istoric;
        in>>id_cont;
        in>>nume;
        in>>data_deschiderii;
        in>>sold;
        in>>moneda;
        in>>nr_tranzactii_gratuite;
        in>>rata_dobanzii;
        in>>istoric;
        ob.nume=nume;
        ob.id_cont=id_cont;
        ob.moneda=moneda;
        ob.data_deschiderii=data_deschiderii;
        ob.sold=sold;
        ob.nr_tranzactii_gratuite=nr_tranzactii_gratuite;
        ob.istoric=istoric;
        ob.rata_dobanzii=rata_dobanzii;

    return in;
}

template <typename T> class GestionareConturi
{
    vector<T*>Vector_Conturi_Bancare;
    static int index;
     int nr_conturi;
public:
    GestionareConturi(int);
    ~GestionareConturi();
    void adaugare_cont();
    void afisare_conturi_banca();
};

template<typename T> int GestionareConturi<T>::index=0;

template<typename T> GestionareConturi<T>::GestionareConturi(int nr_conturi)
{
    this->nr_conturi=nr_conturi;
    index++;
};
template<typename T> GestionareConturi<T>::~GestionareConturi()
{
    index--;
};
template<typename T>void GestionareConturi<T>::adaugare_cont()
{
    int control;
    int aux=nr_conturi;
    int nr_conturi_AUX=nr_conturi;
    while(aux)
    {
    cout<<"Introduceti date pentru "<<nr_conturi_AUX<<" persoane ;"<<endl;
    cout<<"Tasta 1 pentru cont normal , Tasta 0 pentru cont de economii/imprumut :"<<endl;
    cout<<"Optiunea aleasa este :"<<endl;
    cin>>control;
    if(control==0)

        {
             int id_cont;string nume;string data_deschiderii;double sold;string moneda;int nr_tranzactii_gratuite;
    double rata_dobanzii;string istoric;

        cout<<"Id_cont :";cin>>id_cont;
        cout<<"Nume :";cin>>nume;
        cout<<"Data deschiderii :";cin>>data_deschiderii;
        cout<<"Sold :";cin>>sold;
        cout<<"Moneda :";cin>>moneda;
        cout<<"Numar de tranzactii gratuite";cin>>nr_tranzactii_gratuite;
        cout<<"Rata dobanzii";cin>>rata_dobanzii;
        cout<<"istoric";cin>>istoric;
        Vector_Conturi_Bancare.push_back(new Cont_economii(id_cont,nume,data_deschiderii,sold,moneda,nr_tranzactii_gratuite,rata_dobanzii,istoric));
        aux--;
        }



    if(control==1)
    {
        int id_cont;string nume;string data_deschiderii;double sold;string moneda;int nr_tranzactii_gratuite;
         cout<<"Id_cont :";cin>>id_cont;
        cout<<"Nume :";cin>>nume;
        cout<<"Data deschiderii :";cin>>data_deschiderii;
        cout<<"Sold :";cin>>sold;
        cout<<"Moneda :";cin>>moneda;
        cout<<"Numar de tranzactii gratuite";cin>>nr_tranzactii_gratuite;
         Vector_Conturi_Bancare.push_back(new T(id_cont,nume,data_deschiderii,sold,moneda,nr_tranzactii_gratuite));
        aux--;
    }
    nr_conturi_AUX--;
    if(control==-1)
    {
        break;
    }

    }

}

template<typename T> void GestionareConturi<T>::afisare_conturi_banca()
{
    for(int i=0; i<nr_conturi; i++)
    {
       cout<<(*Vector_Conturi_Bancare[i]);
    }
}

int main()
{


     GestionareConturi<Cont> *Banca1=new GestionareConturi<Cont>(2);
    Banca1->adaugare_cont();
    Banca1->afisare_conturi_banca();

    return 0;
}
