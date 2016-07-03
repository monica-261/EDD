#include "menu.h"
#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>

using namespace std;
int elementos = 0;
struct NodoLista *cabeza;
abb raiz;
int altura,nramas,nhoja;
int der,izq;
int nIzq = 0;
int nDer = 0;
string hojas,palabra;
string entrada;
string datos;


menu::menu()
{}

bool menu::isEmpty(){
    return elementos ==0;
}



void menu::inicio()
{
    int exit=0;
    while(exit!=2){
        cout <<"Bienvenido, que desea hacer"<<endl;
        cout <<"1. Ingresar al menu"<<endl;
        cout <<"2. Salir"<<endl;
        cin>>exit;
        switch(exit){
        case 1:
            opcion();
            break;
        case 2:
            break;

        }
    }
    

}

void menu::opcion(){
    int opc;
    int claveArchivo,clave;
    string ruta;
    string nombre;

    while(opc!=11){
        cout<<"***************************"<<endl;
        cout<<"MENU"<<endl;
        cout<<"SELECCIONE UNA OPCION"<<endl;
        cout<<"1.  Ingresar archivo"<<endl;
        cout<<"2.  Busqueda por frecuencia"<<endl;
        cout<<"3.  Calcular datos del arbol"<<endl;
        cout<<"4.  Eliminar lista de palabras"<<endl;
        cout<<"5.  Mostrar recorrido"<<endl;
        cout<<"7.  Mostrar arbol"<<endl;
        cout<<"8.  Mostrar arbol espejo"<<endl;
        cout<<"10. Cambiar datos"<<endl;
        cout<<"11. Regresar"<<endl;
        cout<<"***************************"<<endl;

        cin>>opc;
        switch (opc)
        {
        case 1:
            cout<<"Seleccione ruta de archivo"<<endl;
            cout<<"Ej: /home/monica/Escritorio/ejemplo.txt"<<endl;
            cin>>ruta;
            cout<<"Asignele una clave a su archivo"<<endl;
            cin>>claveArchivo;
            abrirArchivo(ruta,claveArchivo);
            break;

        case 2:
            cout<<"Ingrese el numero de clave de su archivo"<<endl;
            cin>>clave;
            BusquedaFrecuencia(clave);
            break;

        case 3:
            cout<<"Ingrese el numero de clave del archivo"<<endl;
            cin>>clave;
            calcularDatos(clave);
            break;

        case 4:{
            cout<<"Ingrese el numero de clave del archivo"<<endl;
            cin>>clave;
            NodoLista *temp = cabeza;
            while(temp->clave!= clave)
                temp = temp->siguiente;
            if(temp->clave==clave){
                cout<<"Ingrese la cadena de palabras separadas por coma"<<endl;
                cin>>entrada;
                entrada = entrada+' ';
                for(int i=0;i<entrada.length();i++){
                    entrada[i];
                    if(entrada[i]==',' || entrada[i] == ' '){
                        eliminar(temp->arbol,palabra);
                        palabra = "";
                    }
                    else
                        palabra = palabra + entrada[i];
                }
            }
        }
            break;

        case 5:
            cout<<"Ingrese el numero de clave del archivo"<<endl;
            cin>>clave;
            menuRecorrido(clave);
            break;


        case 7:
            cout<<"Ingrese el numero de clave del archivo"<<endl;
            cin>>clave;
            graficar(clave);
            break;

        case 8:
            cout<<"Ingrese el numero de clave del archivo"<<endl;
            cin>>clave;
            graficarEspejo(clave);
            break;

        case 10:
            int archivoDestino;
            cout<<"Ingrese clave del primer archivo"<<endl;
            cin>>clave;
            cout<<"Ingrese clave del archivo destino"<<endl;
            cin>>archivoDestino;
            cambiarDatos(clave,archivoDestino);
            break;

        case 11:
            inicio();
            break;

        }
    }

}

void menu::abrirArchivo(string path,int claveArchivo)
{
    string linea;
    string palabra;
    string cadena;


    ifstream archivo(path);

    if(archivo.is_open())
    {
        while(!archivo.eof())
        {
            getline(archivo,linea);
            cadena = linea+' ';
            for(int i=0;i<cadena.length();i++)
            {
                cadena[i];
                if (cadena[i] == ','|| cadena[i] == ' ')
                {
                    cout  << palabra <<endl;
                    ABB(raiz,palabra);
                    palabra ="";
                }
                else if(cadena[i] != ',')
                {
                    if(cadena[i]!='\n')
                    {
                        if(cadena[i]!= ' ')
                        {
                            palabra = palabra + cadena[i];
                        }
                    }
                }
            }
        }
        archivo.close();
        ListaOrdenada(path,claveArchivo);
        raiz = NULL;
    }else
        cout<<"RUTA NO VALIDA"<<endl;

}

abb menu::nuevoNodo(string palabra){
    abb nodo = new (struct NodoArbol);
    nodo->palabra = palabra;
    nodo->frecuencia = 1;
    nodo->izq = NULL;
    nodo->der = NULL;
    return nodo;
}

void menu::ABB(abb &raiz, string palabra){
    if(raiz==NULL){
        raiz = nuevoNodo(palabra);

    }else if(strcmp(palabra.c_str(),raiz->palabra.c_str())>=1)
        ABB(raiz->izq,palabra);
    else if(strcmp(palabra.c_str(),raiz->palabra.c_str())<=-1)
        ABB(raiz->der,palabra);
    else{
        cout<<"Palaba Repetida"<<endl;
        raiz->frecuencia++;
    }
}

void menu::ListaOrdenada(string ruta,int claveArchivo){
    string name;
    string path = ruta+' ';
    for (int i=0;i<path.length();i++){
        path[i];
        if(path[i] == ' ')
            cout << name <<endl;
        else if(path[i]=='/')
            name = "";
        else if(path[i]!='/'){
            if(path[i]!=' '){
                name = name + ruta[i];
            }
        }

    }


    if(isEmpty()==true){
        NodoLista *nuevo = new NodoLista();
        nuevo->nombre = name;
        nuevo->clave = claveArchivo;
        nuevo->siguiente = NULL;
        nuevo->arbol = raiz;
        cabeza = nuevo;
    }else{
        NodoLista *aux = cabeza;
        NodoLista *nuevo = new NodoLista();
        nuevo->clave = claveArchivo;
        nuevo->nombre = name;
        nuevo->arbol = raiz;

        if(aux->nombre.compare(name)>0){
            nuevo->siguiente = cabeza;
            cabeza = nuevo;
        }else{
            while(aux->siguiente!=NULL && (aux->siguiente->nombre.compare(name))<0){
                aux = aux->siguiente;
            }
            if(aux->siguiente ==NULL){
                aux->siguiente = nuevo;
            }else{
                NodoLista *aux1 = aux->siguiente;
                aux->siguiente = nuevo;
                nuevo->siguiente = aux1;
            }

        }
    }
    elementos++;
}

void menu::BusquedaFrecuencia(int claveArchivo){
    int numero,fq;
    NodoLista *temp = cabeza;
    while(temp->siguiente!=NULL&&claveArchivo!=temp->clave)
        temp = temp->siguiente;
    if(claveArchivo==temp->clave){
        cout<<"Archivo encontrado"<<endl;
        if(temp->arbol!=NULL){
            while(fq!=6){
                cout<<"*******************************"<<endl;
                cout<<"Ingrese el numero de frecuencia deseada"<<endl;
                cin>>numero;
                cout<<"Como desea efectuar su busqueda"<<endl;
                cout<<"1. Todas las palabras con la frecuencia exacta indicada"<<endl;
                cout<<"2. Con menos frecuencia de la indicada"<<endl;
                cout<<"3. Con mas frecuencia de la indicada"<<endl;
                cout<<"4. Con menor o igual frecuencia que la indicada"<<endl;
                cout<<"5. Con mayor o igual frecuencia que la indicada"<<endl;
                cout<<"6. Regresar "<<endl;
                cin>>fq;
                switch(fq){
                case 1:
                    recorridoIgual(temp->arbol,numero);
                    break;
                case 2:
                    recorridoMenor(temp->arbol,numero);
                    break;
                case 3:
                    recorridoMayor(temp->arbol,numero);
                    break;
                case 4:
                    recorridoMnIgual(temp->arbol,numero);
                    break;
                case 5:
                    recorridoMyIgual(temp->arbol,numero);
                    break;
                case 6:
                default:
                    fq=6;
                    opcion();
                }
            }
        }
    }

    else
        cout<<"Error en clave"<<endl;
}

void menu::recorridoIgual(abb arbol, int freq){
    if(arbol!=NULL){
        if(arbol->frecuencia == freq){
            cout<< "Palabra: "+ arbol->palabra<<endl;
            recorridoIgual(arbol->izq,freq);
            recorridoIgual(arbol->der,freq);

        }
        else{
            recorridoIgual(arbol->izq,freq);
            recorridoIgual(arbol->der,freq);

        }


    }
}

void menu::recorridoMnIgual(abb arbol, int freq){
    if(arbol!=NULL){
        if(arbol->frecuencia <= freq){
            cout<< "Palabra: "+ arbol->palabra<<endl;
            recorridoMnIgual(arbol->izq,freq);
            recorridoMnIgual(arbol->der,freq);
        }
        else{
            recorridoMnIgual(arbol->izq,freq);
            recorridoMnIgual(arbol->der,freq);
        }
    }
}

void menu::recorridoMyIgual(abb arbol, int freq){
    if(arbol!=NULL){
        if(arbol->frecuencia >= freq){
            cout<< "Palabra: "+ arbol->palabra<<endl;
            recorridoMyIgual(arbol->izq,freq);
            recorridoMyIgual(arbol->der,freq);
        }
        else{
            recorridoMyIgual(arbol->izq,freq);
            recorridoMyIgual(arbol->der,freq);
        }
    }
}

void menu::recorridoMayor(abb arbol, int freq){
    if(arbol!=NULL){
        if(arbol->frecuencia > freq){
            cout<< "Palabra: "+ arbol->palabra<<endl;
            recorridoMayor(arbol->izq,freq);
            recorridoMayor(arbol->der,freq);


        }
        else{
            recorridoMayor(arbol->izq,freq);
            recorridoMayor(arbol->der,freq);
        }
    }
}

void menu::recorridoMenor(abb arbol, int freq){
    if(arbol!=NULL){
        if(arbol->frecuencia < freq){
            cout<< "Palabra: "+ arbol->palabra<<endl;
            recorridoMenor(arbol->izq,freq);
            recorridoMenor(arbol->der,freq);
        }
        else{
            recorridoMenor(arbol->izq,freq);
            recorridoMenor(arbol->der,freq);
        }
    }
}

void menu::calcularDatos(int key){
    int calcDatos;
    NodoLista *temp = cabeza;
    while(temp->siguiente!=NULL && temp->clave!=key)
        temp = temp->siguiente;
    if(temp->clave==key){
        cout<<"ARCHIVO ENCONTRADO"<<endl;
        if(temp->arbol!=NULL){
            while(calcDatos!=6){
                cout<<"Que datos desea calcular"<<endl;
                cout<<"1. Altura del arbol"<<endl;
                cout<<"2. Cantidad de nodos rama"<<endl;
                cout<<"3. Cantidad de nodos hoja"<<endl;
                cout<<"4. Listar nodos hoja"<<endl;
                cout<<"5. Diferencia entre cantidad ramas izquierda y derecha"<<endl;
                cout<<"6. Regresar"<<endl;
                cin>>calcDatos;
                switch(calcDatos){
                case 1:
                    int h;
                    h = altura(temp->arbol);
                    cout << "La altura es: "<<h<<endl;
                    break;
                case 2:
                    int rama;
                    rama = contarRamas(temp->arbol,&nramas);
                    cout << "Hay " << rama << " ramas"<<endl;
                    break;
                case 3:
                    int hoja;
                    hoja = contarHojas(temp->arbol,&nhoja);
                    cout << "Hay " << hoja << " hojas"<<endl;
                    break;
                case 4:
                    cout << "Las hojas son: " << hojas <<endl;
                    hojas = "";
                    break;
                case 5:
                    int dif;
                    dif = difNodos(temp->arbol);
                    cout << "La diferencia de nodos es: " << nIzq - nDer <<endl;
                    break;

                case 6:
                default:
                    opcion();
                    calcDatos = 6;

                }
            }
        }
    }

}

int menu::altura(abb arbol){
    int hIzq,hDer;
    if(arbol==NULL){
        return -1;
    }else{
        hIzq  = altura(arbol->izq);
        hDer = altura(arbol->der);
        if(hIzq>hDer)
            return hIzq+1;
        else
            return hDer+1;
    }
}

int menu::contarRamas(abb arbol, int *rama){
    *rama = 0;
    auxRama(arbol,0,rama);
    return *rama;
}

void menu::auxRama(abb arbol, int ht, int *c){
    if(arbol->izq)
        auxRama(arbol->izq,ht+1,c);
    if(arbol->der)
        auxRama(arbol->der,ht+1,c);
    if(!esHoja(arbol)&&ht!=0)
        (*c)++;
}

int menu::contarHojas(abb arbol, int *hoja){
    *hoja = 0;
    auxHojas(arbol,hoja);
    return *hoja;
}

void menu::auxHojas(abb arbol, int *c){
    if(arbol->izq)
        auxHojas(arbol->izq,c);
    if(arbol->der)
        auxHojas(arbol->der,c);
    if(esHoja(arbol)){
        (*c)++;
        hojas = arbol->palabra + hojas;
    }

}

int menu::esHoja(abb arbol){
    return !arbol->der && !arbol->izq;
}

void menu::menuRecorrido(int clave){
    int recorrido;
    NodoLista *temp = cabeza;
    if(temp==NULL){
        cout<<"Error en numero de clave"<<endl;
        opcion();
    }else{
        while(temp->siguiente!=NULL && temp->clave!=clave){
            temp = temp->siguiente;
            if(temp==NULL){
                cout<<"Error en numero de clave"<<endl;
                opcion();
            }
        }

    }
    if(temp->clave==clave){
        while(recorrido!=4){
            cout<<"RECORRIDOS"<<endl;
            cout<<"Seleccione el tipo de recorrido"<<endl;
            cout<<"1. Inorden"<<endl;
            cout<<"2. Preorden"<<endl;
            cout<<"3. Postorden"<<endl;
            cout<<"4. Regresar"<<endl;
            cin>>recorrido;
            switch(recorrido){
            case 1:

                cout<<"INORDEN"<<endl;
                inOrden(temp->arbol);
                break;
            case 2:
                cout<<"PREORDEN"<<endl;
                preOrden(temp->arbol);
                break;
            case 3:
                cout<<"POSTORDEN"<<endl;
                postOrden(temp->arbol);
                break;
            case 4:
            default:
                opcion();
                recorrido=4;
                break;

            }

        }

    }

}

void menu::preOrden(abb arbol){
    if(arbol!=NULL){
        cout<<arbol->palabra<<endl;
        preOrden(arbol->izq);
        preOrden(arbol->der);
    }
}

void menu::inOrden(abb arbol){
    if(arbol!=NULL){
        inOrden(arbol->izq);
        cout<<arbol->palabra<<endl;
        inOrden(arbol->der);
    }
}

void menu::postOrden(abb arbol){
    if(arbol!=NULL){
        postOrden(arbol->izq);
        postOrden(arbol->der);
        cout<<arbol->palabra<<endl;
    }
}

void menu::eliminar(abb &arbol, string palabra){
    if(arbol==NULL)
        return;
    else if(strcmp(palabra.c_str(),arbol->palabra.c_str())>=1)
        eliminar(arbol->izq,palabra);
    else if(strcmp(palabra.c_str(),arbol->palabra.c_str())<=-1)
        eliminar(arbol->der,palabra);
    else{
        abb nodo = arbol;
        arbol = Restructurar(arbol->izq, arbol->der);
        delete nodo;
    }
}

abb menu::Restructurar(abb izq, abb der){
    if(izq == NULL)
        return der;
    if(der == NULL)
        return izq;
    abb medio = Restructurar(izq->der,der->izq);
    izq->der = medio;
    der->izq = izq;
    return der;
}

void menu::graficar(int clave){
    NodoLista *temp = cabeza;
    while(temp->siguiente!=NULL && temp->clave!=clave)
        temp = temp->siguiente;
    if(temp->clave==clave){
        FILE *fp;
        fp = fopen("practica2.dot","w");
        fprintf(fp,"digraph practica2 {\n");
        fprintf(fp,"compound=true;\n");
        fprintf(fp,"\tedge [color=\"black\", dir=fordware]\n");
        fprintf(fp,"graph [ranksep=0.20 nodesep=0.20]\n");
        graphviz(fp,temp->arbol);
        fprintf(fp,"}");
        fclose(fp);
        system("dot practica2.dot -o practica2.png -Tpng");
        system("run-mailcap  ~/Escritorio/Practica2/build-Practica2-Desktop_Qt_5_5_1_GCC_32bit-Debug/practica2.png");
        //        system("nohup display ~/Escritorio/Practica 2/build-Practica2-Desktop_Qt_5_5_1_GCC_32bit-Debug/practica2.png &");

    }
}

void menu::graphviz(FILE *file, abb arbol){
    if(arbol == NULL)
        return;
    abb izq = arbol->izq;
    abb der = arbol->der;

    if(arbol->der!=NULL)
        fprintf(file,"\"%s, %d\" -> \"%s, %d\";\n", arbol->palabra.c_str(),arbol->frecuencia,arbol->der->palabra.c_str(), arbol->der->frecuencia);
    if(arbol->izq!=NULL)
        fprintf(file,"\"%s, %d\" -> \"%s, %d\";\n", arbol->palabra.c_str(),arbol->frecuencia,arbol->izq->palabra.c_str(), arbol->izq->frecuencia);
    graphviz(file,izq);
    graphviz(file,der);


}

void menu::graficarEspejo(int clave)
{
    NodoLista *temp = cabeza;
    while(temp->siguiente!=NULL && temp->clave!=clave)
        temp = temp->siguiente;
    if(temp->clave==clave){
        FILE *fp;
        fp = fopen("arbolEspejo.dot","w");
        fprintf(fp,"digraph espejo {\n");
        fprintf(fp,"compound=true;\n");
        fprintf(fp,"\tedge [color=\"black\", dir=fordware]\n");
        fprintf(fp,"graph [ranksep=0.20 nodesep=0.20]\n");
        graphvizEspejo(fp,temp->arbol);
        fprintf(fp,"}");
        fclose(fp);
        system("dot arbolEspejo.dot -o arbolEspejo.png -Tpng");
        system("run-mailcap  ~/Escritorio/Practica2/build-Practica2-Desktop_Qt_5_5_1_GCC_32bit-Debug/arbolEspejo.png");

    }
}

void menu::graphvizEspejo(FILE *file,abb arbol)
{
    if(arbol==NULL){
        return;
    }
    abb izquierdo = arbol->izq;
    abb derecho = arbol->der;
    if(arbol->izq!=NULL)
    {
        fprintf(file,"\"%s, %d\" -> \"%s, %d\";\n", arbol->palabra.c_str(),arbol->frecuencia,arbol->izq->palabra.c_str(), arbol->izq->frecuencia);
    }
    if(arbol->der!=NULL)
    {
        fprintf(file,"\"%s, %d\" -> \"%s, %d\";\n", arbol->palabra.c_str(),arbol->frecuencia,arbol->der->palabra.c_str(), arbol->der->frecuencia);
    }

    graphvizEspejo(file,izquierdo);
    graphvizEspejo(file,derecho);
}

int menu::difNodos(abb arbol){
    int diferencia;

    if(arbol!=NULL){
        if(arbol->izq!=NULL){
            nIzq++;
            difNodos(arbol->izq);
        }
        if(arbol->der!=NULL){
            nDer++;
            difNodos(arbol->der);
        }
    }


}

void menu::leerDatos(abb arbol){
    if(arbol!=NULL){
        leerDatos(arbol->izq);
        datos = datos + arbol->palabra + ',';
        leerDatos(arbol->der);


    }
}

void menu::cambiarDatos(int clave, int archivoDestino){
    NodoLista *temp1 = cabeza;
    NodoLista *temp2 = cabeza;
    int bor;

    while(temp1->siguiente!=NULL&&clave!=temp1->clave)
        temp1 = temp1->siguiente;
    while(temp2->siguiente!=NULL && temp2->clave!=archivoDestino)
        temp2 = temp2->siguiente;

    if(temp1->clave==clave){
        cout<<"ARCHIVO ENCONTRADO"<<endl;
        if(temp2->clave==archivoDestino){
            cout<<"DESTINO ENCONTRADO"<<endl;
            if(temp2->arbol!=NULL && temp1->arbol!=NULL){
                leerDatos(temp1->arbol);
                cout<<datos<<endl;
                string nWord;
                for(int i=0;i<datos.length();i++){
                    datos[i];
                    if(datos[i]!=',')
                        nWord = nWord + datos[i];
                    if(datos[i]==','){
                        if(datos[i+1]==','){
                            ABB(temp2->arbol,nWord);
                            nWord="";
                        }
                        else{
                            ABB(temp2->arbol,nWord);
                            nWord ="";
                        }
                    }

                }
                cout<<"Desea eliminar el arbol origen"<<endl;
                cout<<"1. Si"<<endl;
                cout<<"2. No"<<endl;
                cin>>bor;
                if(bor==1)
                    temp1->arbol == NULL;
            }
        }
    }

}
