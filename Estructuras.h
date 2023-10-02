#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

//Lista de Clientes(Ordenar por Prioridad)
struct Cliente{
    string codigoCliente, nombreCliente;
    int prioridad;
    Cliente * siguiente;

    Cliente(string _codigoCliente, string _nombreCliente,int _prioridad){
        codigoCliente=_codigoCliente;
        nombreCliente=_nombreCliente;
        prioridad=_prioridad;
        siguiente=NULL;
    }
    void imprimir();
};

struct ListaClientes{
    Cliente * primerCliente;

    ListaClientes(){
		primerCliente=NULL;
    }
    void imprimir();
    void insertarInicioCliente (string codigoCliente, string nombreCliente,int prioridad);
    void leerArchivoClientes();
    void annadirClienteAlArchivo(string codigoCliente, string nombreCliente,int prioridad);
};

//Lista de Productos
struct Producto{
    Producto * siguienteProducto, * productoAnterior;
    string codigoProducto;
    int cantidad;

    Producto(string _codigoProducto, int _cantidad){
        codigoProducto=_codigoProducto;
        cantidad=_cantidad;
        siguienteProducto=productoAnterior=NULL;
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
struct NodoArticulo{
    string codigo, categoria, ubicacion;
	int cantidad, tiempoFabricacion;
	NodoArticulo * siguiente;
	NodoArticulo * anterior;
    
	NodoArticulo(int _cantidad, string _codigo, string _categoria, string _ubicacion, int _tiempoFabricacion){
		cantidad=_cantidad;
        categoria=_categoria;
        ubicacion=_ubicacion;
        tiempoFabricacion=_tiempoFabricacion;
        codigo=_codigo;
		siguiente= anterior=NULL;
    }

    void imprimir();
};

struct ListaDoble {
	NodoArticulo * primerArticulo, * ultimoArticulo;
	
    ListaDoble(){
		primerArticulo=ultimoArticulo=NULL;
    }

    void insertarInicio(int _cantidad, string _codigo, string _categoria, string _ubicacion, int _tiempoFabricacion);
    void insertarFinal (int _cantidad, string _codigo, string _categoria, string _ubicacion, int _tiempoFabricacion);
	NodoArticulo * borrarAlFinal();
    void leerArchivoArticulos();
    void imprimir();
};