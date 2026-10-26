/* Sortati o lista folosind selectia minimului.

Se poate implementa in mai multe feluri, de exemplu:

 La fiecare pas caut minimul,
il extrag din lista si il inserez in alta lista.

*/
#include<iostream>

using namespace std; 

struct nod
{
    int info;
    nod* next;
};
class Lista{
    public: 

    Lista()
    {
        primul_element=nullptr;
        ultimul_element=nullptr;
    }
        void adaugare_final(int element)
        {
            nod* nou=new nod;
            nou->info= element;
            nou->next=nullptr;
            if(ultimul_element==nullptr)
            {
                ultimul_element=nou;
                primul_element=nou;
            }
            else
            {
                ultimul_element->next=nou;
                ultimul_element=nou;
            }
        }

        void sortare()
        {
            nod* rezultat_primul=nullptr;
            nod* rezultat_ultimul=nullptr;
            while(primul_element!=nullptr)
            {
                nod* mini=primul_element;
                nod* anterior=primul_element;
                nod* anterior_minim=nullptr;
                nod* curent=primul_element->next;

                while(curent!=NULL)
                {
                    if(curent->info < mini->info)
                    {
                        mini=curent;
                        anterior_minim=anterior;
                    }
                    anterior=curent;
                    curent=curent->next;
                }

                if(anterior_minim==nullptr)
                {
                    primul_element=mini->next;
                }
                else
                {
                    anterior_minim->next=mini->next;
                }
                if(mini==ultimul_element)
                {
                    ultimul_element=anterior_minim;
                }

                mini->next=nullptr;

                if(rezultat_ultimul==nullptr)
                {
                    rezultat_primul=mini;
                    rezultat_ultimul=mini;
                }
                else
                {
                    rezultat_ultimul->next=mini;
                    rezultat_ultimul=mini;
                }    
            }
            primul_element=rezultat_primul;
            ultimul_element=rezultat_ultimul;
        }

        void afisare()
        {
            nod* pointer;
            for(pointer=primul_element;pointer!=nullptr;pointer=pointer->next)
            {
                cout<<pointer->info<<" -> ";
            }
            cout<<endl;
        }

        ~Lista()
        {
            cout<<"Clasa Lista este distrusa"<<endl;
        }
        
    private:
        nod* primul_element;
        nod* ultimul_element;
        
};

int main()
{
    Lista L;
    int n, numar;
    cin>>n;
    for(int i=0; i<n; i++)
    {
        cin>>numar;
        L.adaugare_final(numar);
    }
    L.afisare();
    L.sortare();
    L.afisare();
    return 0;
}