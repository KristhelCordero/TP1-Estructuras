#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <thread>
#include <chrono>
#include <atomic>
#include <mutex>
#include <vector>
#include <dirent.h>
#include <cstdlib>
#include <cstdio>
#include <ctime>
using namespace std;

//LISTA BASE
//NOTA PARA KRIS DE KRIS DEL PASADO: REVISAR LOS NEW DE LAS LISTAS QUE ESTÁN DENTRO DE NODOS

struct ListaDoble;
struct BitacoraMovimientos;

//Lista de Clientes(Ordenar por Prioridad*) -----------------------------------------------------------
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
    int buscarPrioridadCliente(string codigoCliente);
};

//Lista de Productos ----------------------------------------------------------------------------------
struct Producto{
    Producto * siguienteProducto, * productoAnterior;
    string codigoProducto;
    int cantidad;
    bool elaborando;

    Producto(string _codigoProducto, int _cantidad){
        codigoProducto=_codigoProducto;
        cantidad=_cantidad;
        elaborando=false;
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
	Producto* borrarAlFinal();
    Producto* revisarProductosFaltantes(ListaDoble* listaArticulos);
    bool exists(string _codigoProducto);
    int cantidadArticulosDistintos();
};

// Cola de Pedidos ------------------------------------------------------------------------------------
struct NodoPedido{
    NodoPedido * siguiente;
    NodoPedido * anterior;
    int numeroPedido;
    string codigoCliente;
    ListaProductos * productos;

    NodoPedido(int _numeroPedido, string _codigoCliente,ListaProductos * _productos){
        numeroPedido=_numeroPedido;
        codigoCliente=_codigoCliente;
        productos=_productos;
    }
};

struct ColaPedidos{
    NodoPedido * primerPedido, * ultimoPedido;
    mutex mtx;

    ColaPedidos(){
        primerPedido=ultimoPedido=NULL;
    }

    bool estaVacia();
    void encolar(int _numeroPedido, string _codigoCliente,ListaProductos * _productos);
    void imprimir();
    int largo();
    NodoPedido * desencolar();
};

struct ColaPedidosPrioridad{
    NodoPedido * primerPedido, * ultimoPedido;
    mutex mtx;

    ColaPedidosPrioridad(){
        primerPedido=ultimoPedido=NULL;
    }

    bool estaVacia();
    void encolar(int _numeroPedido, string _codigoCliente,ListaProductos * _productos);
    void imprimir();
    int largo();
    NodoPedido * desencolar();
};

struct ColaPedidosEspeciales{
    NodoPedido * primerPedido, * ultimoPedido;
    mutex mtx;

    ColaPedidosEspeciales(){
        primerPedido=ultimoPedido=NULL;
    }

    bool estaVacia();
    void encolar(int _numeroPedido, string _codigoCliente,ListaProductos * _productos);
    void imprimir();
    int largo();
    NodoPedido * desencolar();
};

// Lista Doble ----------------------------------------------------------------------------------------
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
    bool encontrarArticulo(string _codigo);
    void actualizarArchivoArticulos();
    int revisarListaArticulos();
    int largo();
    bool encontrarArticuloRepetido(string _codigo);
    int cantidadArticuloBodega(string _codigo);
};

// COLA DE ALISTO -------------------------------------------------------------------------------------
struct ColaAlisto{
    NodoPedido * primerPedido, * ultimoPedido;
    mutex mtx;

    ColaAlisto(){
        primerPedido=ultimoPedido=NULL;
    }

    bool estaVacia();
    void encolar(int _numeroPedido, string _codigoCliente,ListaProductos * _productos);
    void imprimir();
    int largo();
    NodoPedido * desencolar();
};

// ROBOTS ---------------------------------------------------------------------------------------------
struct Robot{
    string codigoRobot;
    string articuloFabrica;
    bool apagado;
    bool esPrioridad;
    bool disponible;
    Robot *siguiente;
    Robot *anterior;

    Robot(string _codigoRobot, string _articuloFabrica, bool _apagado, bool _esPrioridad){
        codigoRobot=_codigoRobot;
        articuloFabrica=_articuloFabrica;
        apagado=_apagado;
        esPrioridad=_esPrioridad;
        disponible=true;
    }

    void imprimir();
};

struct ListaRobots{
    Robot * primerRobot;
    Robot * ultimoRobot;

    ListaRobots(){
		primerRobot=ultimoRobot=NULL;
    }

    void insertarFinal (string _codigoRobot, string _articuloFabrica, bool _apagado, bool _esPrioridad);
    void leerArchivoRobots();
    void imprimir();

};

// BITÁCORA DE MOVIMIENTOS ----------------------------------------------------------------------------
struct Movimiento{
    string queHace, fecha, hora, faltantes;//faltantes solo si pasó por un robot
    bool robot; //Si esto es true el formato es diferente
    string articulo, fabricadoEn, cantidad, 
    fechaInicio, horaInicio, fechaFinal, horaFinal;
    bool alistador; //Si esto cambia, su formato es diferente tambien
    string numAlistador, ubicacion, tiempo; //artículo aquii también
    //robot
    Movimiento(string _articulo, string _fabricadoEn, string _cantidad, 
    string _fechaInicio, string _horaInicio, string _fechaFinal, string _horaFinal){
        articulo=_articulo;
        fabricadoEn=_fabricadoEn;
        cantidad=_cantidad;
        fechaInicio=_fechaInicio;
        horaInicio=_horaInicio;
        fechaFinal=_fechaFinal;
        horaFinal=_horaFinal;
        robot=true;
        alistador=false;
    }
    //normal
    Movimiento(string _queHace, string _fecha, string _hora, string _faltantes){
        queHace=_queHace;
        fecha=_fecha;
        hora=_hora;
        faltantes=_faltantes;
        alistador=false;
        robot=false;
    }
    //alistador
    Movimiento(string _numAlistador, string _articulo, string _ubicacion, string _tiempo){
        articulo=_articulo;
        numAlistador=_numAlistador;
        ubicacion=_ubicacion;
        tiempo=_tiempo;
        alistador=true;
        robot=false;
    }
    
};

struct BitacoraMovimientos{
    
};

//------------------------------------------THREADS----------------------------------------------------
struct threadPedidos {
    thread thread; 
    string nombreArchivo, _nombreArchivo;
    string dir=".\\Pedidos-Clientes";
    DIR *direccion;
    dirent *elementos;
    atomic<bool> pausado; 
    atomic<bool> terminar; 
    ColaPedidos* cola;
    ColaPedidosPrioridad *colaPrioridad;
    ListaClientes *listaClientes;
    ListaDoble *listaArticulos;
    mutex mutex;
    // Constructor
    threadPedidos(ColaPedidos *_cola, ColaPedidosPrioridad *_colaPrioridad, ListaClientes *_listaClientes, ListaDoble *_listaArticulos):
    pausado(false), terminar(false), cola(_cola), colaPrioridad(_colaPrioridad), listaClientes(_listaClientes), listaArticulos(_listaArticulos){
        thread = std::thread(threadPedidos::leerArchivosPedidos, this);
    }
    // Función que será ejecutada por el thread
    void leerArchivosPedidos(); 
    void Pausar() {pausado = true;}
    void Reanudar() {pausado = false;}
    void Terminar() {
        terminar = true;
        if (thread.joinable()) {
            thread.join();
        }
    }
    //Destructor
    ~threadPedidos() {Terminar();}
};

// {
//                 unique_lock<std::mutex> lock(mutex);
//                 while (pausado) {
//                     // El thread está en pausa, espera
//                     lock.unlock();
//                     this_thread::sleep_for(chrono::milliseconds(100));
//                     lock.lock();
//                 }
//             }

//BALANCEADOR -----------------------------------------------------------------------------------------
struct ThreadBalanceador{
    thread thread; 
    atomic<bool> apagado; 
    atomic<bool> terminar; 
    ColaPedidos* cola;
    ColaPedidosPrioridad *colaPrioridad;
    ColaPedidosEspeciales *colaEspecial;
    ColaAlisto *colaDeAlisto;
    ListaDoble *listaArticulos;
    bool procesando=false;
    // Constructor
    ThreadBalanceador(ColaPedidos *_cola, ColaPedidosPrioridad *_colaPrioridad, ListaDoble *_listaArticulos, ColaPedidosEspeciales * _colaEspecial):
    apagado(false), terminar(false), cola(_cola), colaPrioridad(_colaPrioridad), listaArticulos(_listaArticulos), colaEspecial(_colaEspecial){
        thread = std::thread(ThreadBalanceador::procesarPedidos, this);
    }
    // Función que será ejecutada por el thread
    void procesarPedidos(); 
    void Pausar() {apagado = true;}
    void Reanudar() {apagado = false;}
    void Terminar() {
        terminar = true;
        if (thread.joinable()) {
            thread.join();
        }
    }
    //Destructor
    ~ThreadBalanceador() {Terminar();}
};

//ROBOTS ----------------------------------------------------------------------------------------------
struct RobotFabricador{
// operar desde el thread la lista de robots
// hacer una función que opere al robot correspondiente
// Necesito: ver donde putas meto las validaciones :)
    void elaborarProducto(Producto * productoAElaborar);
};
