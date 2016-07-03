#ifndef MENU_H
#define MENU_H
#include <iostream>
#include <string.h>
#include <stdio.h>

using namespace std;

struct NodoLista{
    string nombre;
    int clave;
    struct NodoLista *siguiente;
    struct NodoArbol *arbol;
};

struct NodoArbol{
    string palabra;
    int frecuencia;
    int fe;
    int subaltura;
    struct NodoArbol *izq,*der;
};

typedef struct NodoArbol *abb;
class menu
{
public:
    menu();

    void inicio();
    void opcion();
    void abrirArchivo(string path,int claveArchivo);
    void ABB(abb &raiz,string palabra);
    void ListaOrdenada(string name,int claveArchivo);
    void BusquedaFrecuencia(int claveArchivo);
    abb nuevoNodo(string palabra);
    bool isEmpty();
    void recorridoIgual(abb arbol,int freq);
    void recorridoMenor(abb arbol,int freq);
    void recorridoMayor(abb arbol,int freq);
    void recorridoMyIgual(abb arbol,int freq);
    void recorridoMnIgual(abb arbol,int freq);
    void calcularDatos(int key);
    int altura(abb arbol);
    int contarRamas(abb arbol,int *rama);
    void auxRama(abb arbol,int ht,int *c);
    int contarHojas(abb arbol,int *hoja);
    void auxHojas(abb arbol,int *c);
    void graficarEspejo(int clave);
    void graphvizEspejo(FILE *file,abb arbol);
    void graficar(int clave);
    void graphviz(FILE *file,abb arbol);
    void menuRecorrido(int clave);
    void preOrden(abb arbol);
    void inOrden(abb arbol);
    void postOrden(abb arbol);
    void eliminar(abb &arbol, string cadena);
    abb Restructurar(abb izq,abb der);
    int esHoja(abb arbol);
    int difNodos(abb arbol);
    void cambiarDatos(int clave, int archivoDestino);
    void leerDatos(abb arbol);

};







#endif // MENU_H
