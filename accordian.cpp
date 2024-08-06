
/*
    NICOLLE RUIZ QUINTERO
    8974036

*/



#include <iostream>
#include <vector>
#include <tuple>
#include <string>

using namespace std;

string movimientos(vector<tuple<char,char,int>> listaCard){
    tuple <char,char,int> tuplaActual;
    tuple <char,char,int> tuplaIzquierda;
    tuple <char,char,int> tupla3Izquierda;
    int tamanoTup;
    string cantPila;
    for(int i=0;i<listaCard.size();++i){
        tuplaActual=listaCard[i];
        if (i>=3){
            tupla3Izquierda=listaCard[i-3];
        }
        if(i>0){
            tuplaIzquierda=listaCard[i-1];
        }
        
        char numeroActual=get<0>(tuplaActual);
        char letraActual=get<1>(tuplaActual);
        int numero1=get<2>(tuplaActual);

        char numeroAnterior=get<0>(tuplaIzquierda);
        char letraAnterior=get<1>(tuplaIzquierda);
        int numero2=get<2>(tuplaIzquierda);

        char numeroAnterior2=get<0>(tupla3Izquierda);
        char letraAnterior2=get<1>(tupla3Izquierda);
        int numero3=get<2>(tupla3Izquierda);

        if (numeroActual == numeroAnterior2 || letraActual == letraAnterior2 || numeroActual == numeroAnterior2 && letraActual == letraAnterior2) {
                tuple <char,char,int> nuevatupla= make_tuple(numeroActual,letraActual,numero1+numero3);
                listaCard.erase(listaCard.begin()+i);
                listaCard.insert(listaCard.begin()+i,nuevatupla);
        }
        else if (numeroActual == numeroAnterior || letraActual == letraAnterior || numeroActual == numeroAnterior && letraActual == letraAnterior) {
                tuple <char,char,int> nuevatupla= make_tuple(numeroActual,letraActual,numero1+numero3);
                listaCard.erase(listaCard.begin()+i);
                listaCard.insert(listaCard.begin()+i,nuevatupla);
        
            
        }
        tamanoTup= listaCard.size();
        for (auto it = listaCard.begin(); it != listaCard.end(); ++it) {
            int numero = get<2>(*it);
            cantPila += numero;
        }
    }

}

int main (){
    string texto;
    vector<tuple<char,char,int>> listaCard;
    vector<string> resultado;
    int tamano;
    cin>>texto;

    while(texto!="#"){
        string parte;
        for( int i=0; i< texto.size();++i){
            if(i<=26){
                if(texto[i]==' '){
                    char numero = parte[0]; 
                    char letra = parte[1]; 
                    int constante = 1; 

                    listaCard.push_back(make_tuple(numero, letra, constante));
                }
                else{
                    parte += texto[i];
                }
                parte.clear();
            }

            if(i==27){
                string resultados;
                resultados=movimientos(listaCard);
                tamano,resultado.push_back(resultados);
            }
        }
        cout<<"sigo en el ciclo"<<endl;
    }
    cout<< tamano << "piles remaining: ";
    for(int i=0; i<resultado.size();++i){
        cout<<resultado[i]<<" ";
    }
} 