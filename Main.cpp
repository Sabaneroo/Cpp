#include <stdlib.h>
#include <iostream>

using namespace std;

class Pila {
   public:
    Pila() : plista(NULL) {}

    void Push(pnodo);
    void Mostrar();
    bool Vacia() { return plista == NULL; }
    pnodo Pop();
    int Size();

    pnodo plista;
};

class Binario{
public:
    pNodoBinario raiz;

    Binario():raiz(NULL){}

    void InsertaNodo(int num);
    void PreordenI();
    void InordenI();
    void PostordenI();

    bool Hh;

    void Borrar(NodoBinario *nodoB, bool);
    void BorrarBalanceado(NodoBinario *r, bool, int eliminar);
    void Equilibrar1(NodoBinario *n, bool);
    void Equilibrar2(NodoBinario *n, bool);
    void InsertarBalanceado(NodoBinario *r, bool, int x);
    void RotacionDobleIzquierda(NodoBinario *n1, NodoBinario *n2);
    void RotacionDobleDerecha(NodoBinario *n1, NodoBinario *n2);
    void RotacionSimpleIzquierda(NodoBinario *n1, NodoBinario *n2);
    void RotacionSimpleDerecha(NodoBinario *n1, NodoBinario *n2);


};



class NodoBinario {
   public:

    NodoBinario(int num, NodoBinario *der = NULL, NodoBinario *izq = NULL, NodoBinario *sig=NULL, NodoBinario *ant=NULL):
        Hizq(izq), Hder(der), valor(num), siguiente(sig), anterior(ant), FB(0) {}


    int valor;
    int FB;
    NodoBinario *Hizq, *Hder, *siguiente, *anterior;

    friend class Pila;
    friend class Binario;

    void InsertaBinario(int num);
};

typedef NodoBinario *pnodo;
typedef NodoBinario *pNodoBinario;

void PreordenR(NodoBinario* R);
void InordenR(NodoBinario* R);
void PostordenR(NodoBinario* R);





void Pila::Push(pnodo v)
{
   if(Vacia()) {
      plista = v;
   }else{
    NodoBinario *aux=plista;
    while(aux->siguiente){
        aux=aux->siguiente;
    }
    aux->siguiente=v;
    v->anterior=aux;

   }
}

pnodo Pila::Pop()
{
    NodoBinario *borrar;
    NodoBinario *salida;
    if(Vacia()){
        cout<<"Pila Vacia"<<endl;
    }else{
    borrar=plista;
    while(borrar->siguiente){
        borrar=borrar->siguiente;
    }
    if(Size()>1){
        salida=borrar;
        borrar->anterior->siguiente=NULL;
        borrar=NULL;
        delete borrar;
    }else{
        salida =plista;
        plista = NULL;
    }
    }
    return salida;
}

int Pila::Size(){
    while(plista && plista->anterior) plista = plista->anterior;
    int cont=0;
    NodoBinario *aux;
    aux=plista;
    while(aux){
        cont++;
        aux=aux->siguiente;
    }
    return cont;
}

void Pila::Mostrar(){
    if(Vacia()){
        cout<<"Vacia";
    }
    NodoBinario *aux = plista;
    while(aux){
        cout<< aux->valor<<" - ";
        aux=aux->siguiente;
    }
}
void NodoBinario::InsertaBinario(int num)
{
    if(num<valor){
        if(Hizq==NULL){
            Hizq = new NodoBinario(num);
        }else{
            Hizq->InsertaBinario(num);
        }
    }else{
        if(Hder==NULL){
            Hder = new NodoBinario(num);
        }else{
            Hder->InsertaBinario(num);
        }
    }
}

void Binario::InsertaNodo(int num)
{
    if(raiz==NULL){
        raiz = new NodoBinario(num);
    }else{
        raiz->InsertaBinario(num);
    }
}

void Binario::PreordenI(){
    NodoBinario *Act = raiz;
    Pila p;
    while(p.Vacia()==false || (Act!=NULL)){
        if(Act!=NULL){
            cout<<Act->valor<<" - ";
            p.Push(Act);
            Act = Act->Hizq;
        }else{
            Act=p.Pop();
            Act=Act->Hder;
        }
    }
}

void Binario::InordenI(){
    NodoBinario *Act = raiz;
    Pila p;
    bool band=true;
    while(band){

        while(Act!=NULL){
            p.Push(Act);
            Act = Act->Hizq;
        }
        if(!p.Vacia()){
            Act=p.Pop();
            cout<<Act->valor<<" - ";
            Act=Act->Hder;
        }
        if(p.Vacia() & Act==NULL){
            break;
        }
    }
}

void Binario::PostordenI(){
    NodoBinario *Act = raiz;
    Pila p;
    Pila p2;
    while(!p.Vacia() || Act!=NULL){
        if(Act!=NULL){
            p2.Push(new NodoBinario(Act->valor));
            p.Push(Act);
            Act = Act->Hder;
        }else{
            Act=p.Pop();
            Act = Act->Hizq;
        }
    }
    while(!p2.Vacia()){
        NodoBinario *salida=p2.Pop();
        cout<<salida->valor<<" - ";
    }
}

void PreordenR(NodoBinario *R){

    if(R==NULL){
        return;
    }else{
        cout<<R->valor<<" - ";
        PreordenR(R->Hizq);
        PreordenR(R->Hder);
    }
}

void InordenR(NodoBinario *R){

    if(R==NULL){
        return;
    }else{
        InordenR(R->Hizq);
        cout<<R->valor<<" - ";
        InordenR(R->Hder);
    }
}

void PostordenR(NodoBinario *R){

    if(R==NULL){
        return;
    }else{
        PostordenR(R->Hizq);
        PostordenR(R->Hder);
        cout<<R->valor<<" - ";
    }
}

void Binario::Borrar(NodoBinario* D, bool Hh)
{
    NodoBinario *q;
    if(D->Hder !=NULL){
        Borrar(D->Hder, Hh);
        if(Hh){
            Equilibrar2(D, Hh);
        }else{
            q->valor=D->valor;
            q=D;
            D=D->Hizq;
            Hh = true;
        }
    }
}

void Binario::BorrarBalanceado(NodoBinario* raiz, bool Hh, int x)
{
    NodoBinario *q;
    if(raiz!=NULL){
        if(x<raiz->valor){
            BorrarBalanceado(raiz->Hizq, Hh, x);
            if(Hh){
                Equilibrar1(raiz, Hh);
            }
        }else{
            if(x>raiz->valor){
                BorrarBalanceado(raiz->Hder, Hh, x);
                if(Hh){
                    Equilibrar2(raiz, Hh);
                }
            }else{
                q=raiz;
            }
        }

                if(q->Hder==NULL){
                    raiz=q->Hizq;
                    Hh=true;
                }else{
                    if(q->Hizq==NULL){
                        raiz=q->Hder;
                        Hh = true;
                    }else{
                        Borrar(q->Hizq, Hh);
                    }
                    if(Hh){
                        Equilibrar1(raiz, Hh);
                    }
                }
            }
}

void Binario::Equilibrar1(NodoBinario* n, bool Hh){
    NodoBinario *n1;
    switch (n->FB){
        case -1: n->FB = 0;
        break;
        case 0: n->FB = 1;
        Hh = false;
        break;
        case 1: n1 = n->Hder;
        if(n1->FB>=0){
            if(n1->FB=0){
                Hh = false;
                RotacionSimpleDerecha(n, n1);
            }else{
                RotacionDobleDerecha(n, n1);
            }
        }
    }
}

void Binario::Equilibrar2(NodoBinario* n, bool Hh){
    NodoBinario *n1;
    switch (n->FB){
        case 1: n->FB = 0;
        break;
        case 0: n->FB = 1;
        Hh = false;
        break;
        case -1: n1 = n->Hizq;
        if(n1->FB<=0){
            if(n1->FB=0){
                Hh = false;
                RotacionSimpleIzquierda(n, n1);
            }else{
                RotacionDobleIzquierda(n, n1);
            }
        }
    }
}

void Binario::InsertarBalanceado(pNodoBinario ra, bool Hh, int x){
    pNodoBinario n1;

    if(raiz==NULL){
        ra=new NodoBinario(x);
        cout<<ra->valor<<"q as"<<endl;
        Hh = true;
    }else{
        cout<<"q as2"<<endl;
        if(x<ra->valor){
            InsertarBalanceado(ra->Hizq, Hh, x);

        if(Hh){
            switch(ra->valor){
                case 1: ra->FB=0;
                Hh = false;
                break;
                case 0: ra->FB  = -1;
                break;
                case -1: n1=ra->Hizq;
                if(n1->FB =-1){
                    RotacionSimpleIzquierda(ra, n1);
                }else{
                    RotacionDobleIzquierda(ra,n1);
                }
                Hh = false;
                break;
            }
        }
        }else{
            if(x>ra->valor){
                InsertarBalanceado(ra->Hder, Hh, x);

                if(Hh){
                    switch(ra->FB){
                        case -1: ra->FB=0;
                        Hh = false;
                        break;
                        case 0: ra->FB=1;
                        break;
                        case 1:n1=ra->Hder;
                        if(n1->FB=1){
                            RotacionSimpleDerecha(ra, n1);
                        }else{
                            RotacionDobleDerecha(ra, n1);
                        }
                        Hh=false;
                        break;
                    }
                }
            }
        }
    }
}

void Binario::RotacionDobleIzquierda(NodoBinario* n, NodoBinario* n1){
    NodoBinario *n2;
    n2=n1->Hder;
    n->Hizq = n2->Hder;
    n2->Hder=n;
    n1->Hder=n2->Hizq;
    n2->Hizq=n1;

    if(n2->FB==1){
        n1->FB=-1;
    }else{
        n1->FB=0;
    }
    if(n2->FB==-1){
        n->FB=1;
    }else{
        n->FB=0;
    }
    n2->FB=0;
    n=n2;
}

void Binario::RotacionDobleDerecha(NodoBinario* n, NodoBinario* n1){
    NodoBinario *n2;
    n2=n1->Hizq;
    n->Hder = n2->Hizq;
    n2->Hizq=n;
    n1->Hizq=n2->Hder;
    n2->Hder=n1;

    if(n2->FB==1){
        n->FB=-1;
    }else{
        n->FB=0;
    }
    if(n2->FB==-1){
        n1->FB=1;
    }else{
        n1->FB=0;
    }
    n2->FB=0;
    n=n2;
}

void Binario::RotacionSimpleDerecha(NodoBinario* n, NodoBinario* n1){
    n->Hder=n1->Hizq;
    n1->Hizq=n;

    if(n1->FB==1){
        n->FB=0;
        n1->FB=0;
    }else{
        n->FB=1;
        n1->FB=-1;
    }
    n=n1;
}

void Binario::RotacionSimpleIzquierda(NodoBinario* n, NodoBinario* n1){
    n->Hizq=n1->Hder;
    n1->Hder=n;

    if(n1->FB==-1){
        n->FB=0;
        n1->FB=0;
    }else{
        n->FB=-1;
        n1->FB=-1;
    }
    n=n1;
}


int main(){
    Binario B;
    B.InsertaNodo(6);
    B.InsertaNodo(2);
    B.InsertaNodo(7);
    B.InsertaNodo(9);
    B.InsertaNodo(8);
    B.InsertaNodo(4);
    B.InsertaNodo(5);
    B.InsertaNodo(1);
    B.InsertaNodo(3);
    B.InsertaNodo(10);\

    cout<<endl<<"In"<<endl;
    B.InordenI();
    cout<<endl<<"Pre"<<endl;
    B.PreordenI();
    Binario B2;
    B2.InsertaNodo(6);
    B2.InsertaNodo(2);
    B2.InsertaNodo(7);
    B2.InsertaNodo(9);
    B2.InsertaNodo(8);
    B2.InsertaNodo(4);
    B2.InsertaNodo(5);
    B2.InsertaNodo(1);
    B2.InsertaNodo(3);
    B2.InsertaNodo(10);\

    cout<<endl<<"Post"<<endl;
    B2.PostordenI();

    Binario B3;
    B3.InsertarBalanceado(B.raiz, false, 5);
    B3.InsertarBalanceado(B.raiz, B.Hh, 4);
   // B.InsertarBalanceado(B.raiz, false, 6);


    cin.get();

    return (EXIT_SUCCESS);
}

