#include <iostream>
using namespace std;

//Lista de Clientes(Ordenar por Prioridad)
struct Cliente{
    string codigoCliente;
    string nombreCliente;
    int prioridad;
};

//Lista de Productos
struct Producto{
    Producto * siguienteProducto, * productoAnterior;
    string codigoProducto;
    int cantidad;

    Producto(string _codigoProducto, int _cantidad){
        codigoProducto=_codigoProducto;
        cantidad=_cantidad;
    }
};

struct ListaProductos{
    Producto * primerProducto, * ultimoProducto;

    ListaProductos(){
		primerProducto=ultimoProducto=NULL;
    }

    void insertarInicioProducto(string _codigoProducto, int _cantidad);
    void insertarFinalProducto (string _codigoProducto, int _cantidad);
	Producto * borrarAlFinal();
};

// Cola de Pedidos
struct NodoPedido{
    NodoPedido * siguiente;
    NodoPedido * anterior;
    int numeroPedido;
    string codigoCliente;
    ListaProductos productos;

    NodoPedido(int _numeroPedido, string _codigoCliente,ListaProductos _productos){
        numeroPedido=_numeroPedido;
        codigoCliente=_codigoCliente;
        productos=_productos;
    }
};

struct ColaPedidos{
    NodoPedido * primerPedido, * ultimoPedido;

    ColaPedidos(){
        primerPedido=NULL;
    }

    bool estaVacia();
    void encolar(int _numeroPedido, string _codigoCliente,ListaProductos _productos);
    void imprimir();
    int largo();
    NodoPedido * desencolar();
};

// Lista Doble 
struct NodoDoble{
	int dato;
	NodoDoble * siguiente;
	NodoDoble * anterior;
    
	NodoDoble(int _dato){
		dato=_dato;
		siguiente= anterior=NULL;
    }
};

struct ListaDoble {
	NodoDoble * pn, *un;
	
    ListaDoble(){
		pn=un=NULL;
    }

    void insertarInicio(int _dato);
    void insertarFinal (int _dato);
    void imprimirAlReves();
	NodoDoble * borrarAlFinal();
};