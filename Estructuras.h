#include <iostream>
using namespace std;

struct Producto{
    Producto * siguienteProducto;
    Producto * productoAnterior;
    string codigoProducto;
    int cantidad;
};

struct Cliente{
    string codigoCliente;
    string nombreCliente;
    int prioridad;
};

struct ListaProductos{
    Producto * primerProducto;
    Producto * ultimoProducto;
};


struct NodoPedido{
    NodoPedido * siguiente;
    int numeroPedido;
    string codigoCliente;
    ListaProductos productos;
};

struct Cola{
    NodoPedido * primerPedido;

};
