#include<iostream> 
#include<vector>

using namespace std;
/*
    SSe scot elementele din cedi 2 arbori deja sortate
    prin parcurgere in inordine->crescatori
    se interclaseaza vectorii sortati, -> se pastreaza
    elementele care nu sunt comune 
    vectorul rezultat construieste arborele nou. 
*/
class BST {
    private:
        struct nod
        {
            int info;
            nod* st;  
            nod* dr; 
            nod(int x): info(x), st(nullptr), dr(nullptr) {} 
        };
        nod* radacina;  
        int dim;

        nod* inserareRad(nod* n, int x)
        {
            if(n==nullptr)
           {   
                dim++;
                nod* nou= new nod(x);
                return nou;
            }
            if(x<n->info)
            {
                n->st=inserareRad(n->st,x);
            }
            if(x>n->info)
            {
                n->dr=inserareRad(n->dr,x);
            }

            return n;
        }

        void inordine(nod* n)
        {
            if(n==nullptr)
            {
                return;
            }
            inordine(n->st);
            cout<<" "<<n->info;
            inordine(n->dr);
        }
        
        void stergere_elem(nod* n, vector<int>& v)
        {
            if(n==nullptr)
            {
                return; 
            }
            stergere_elem(n->st,v);

            v.push_back(n->info);

            stergere_elem(n->dr,v);
        }

        nod* construire_arbore(const vector<int>& v, int st, int dr)
        {
            if(st>dr)
            {
                return nullptr;
            }
            int mijl=(st+dr)/2;
            nod* nou=new nod(v[mijl]);
            dim++;

            nou->st=construire_arbore(v,st,mijl-1);
            nou->dr=construire_arbore(v,mijl+1,dr);
            
            return nou;
        }
        void elibereaza(nod* n)
        {
            if(n==nullptr)
                return; 
            
            elibereaza(n->st);
            elibereaza(n->dr);

            delete n;
        }
    public:
        BST()
        {
            radacina=nullptr;
            dim=0;
        }

        void inserare(int x)
        {
            radacina=inserareRad(radacina, x);
        }
       
        void parcurgere_inordine()
        {
            inordine(radacina);
            cout<<endl;
        }

        vector<int> AB_vector()
        {
            vector<int> v;
            stergere_elem(radacina,v);
            return v;
        }
        void din_vector(const vector<int>& v)
        {
            radacina=construire_arbore(v, 0, (int)v.size()-1);
        }
        
        ~BST()
        {
            cout<<"BST a fost distrus"<<endl;
            elibereaza(radacina);
        }
            
};


vector<int> diferenta_simetrica(const vector<int>& a, const vector<int>& b)
{
    vector<int>rezultat;
    size_t i=0,j=0;
    while(i<a.size() && j<b.size())
    {
        if(a[i]>b[j])
        {
            rezultat.push_back(b[j]);
            j++;
        }
    
        else 
        if(a[i]<b[j])   
        {
            rezultat.push_back(a[i]);
            i++;
        }
        else 
        {
            i++;
            j++;
        }
    }
    while(i<a.size())
    {
        rezultat.push_back(a[i]);
        i++;
    }

    while(j<b.size())
    {
        rezultat.push_back(b[j]);
        j++;
    }

    return rezultat;
}


int main()
{
    BST A;
    A.inserare(8);
    A.inserare(3);
    A.inserare(10);
    A.inserare(6);
    A.parcurgere_inordine();
    BST B;
    B.inserare(3);
    B.inserare(5);
    B.inserare(8);
    B.inserare(9);

    vector<int>va= A.AB_vector();
    vector<int>vb= B.AB_vector();
    vector<int> rezultat= diferenta_simetrica(va,vb);

    for(size_t i=0; i< rezultat.size(); i++)
        cout<< rezultat[i]<<" ";
    cout<<endl;

    BST C;
    C.din_vector(rezultat);
    C.parcurgere_inordine();

}
