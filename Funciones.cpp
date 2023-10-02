#include "Estructuras.h"

//COLA PEDIDOS------------------------------------------------
bool ColaPedidos::estaVacia(){
	return primerPedido==0;
}

void ColaPedidos::encolar(int _numeroPedido, string _codigoCliente,ListaProductos _productos){
	if(estaVacia())
		primerPedido=ultimoPedido=new NodoPedido(_numeroPedido, _codigoCliente, _productos);
	else{
		ultimoPedido->siguiente= new NodoPedido(_numeroPedido, _codigoCliente, _productos);
		ultimoPedido->siguiente->anterior=ultimoPedido;
		ultimoPedido=ultimoPedido->anterior; 
    }
}

NodoPedido * ColaPedidos::desencolar(){
	NodoPedido * borrado= primerPedido;
	if(primerPedido==ultimoPedido){
		primerPedido=ultimoPedido=NULL;
	}else{
		primerPedido=primerPedido->siguiente;
		borrado->siguiente=NULL;
		primerPedido->anterior=NULL;
	}
	return borrado;
}

void ColaPedidos::imprimir(){
	NodoPedido * tmp = primerPedido;
	while(tmp!=NULL){
		cout<<tmp->numeroPedido<<endl; 
		tmp=tmp->siguiente;
    }
}

int ColaPedidos::largo(){
    NodoPedido * tmp = primerPedido;
    int contador=0;
    while(tmp!=NULL){
	    contador++;
	    tmp=tmp->siguiente;
    }
	return contador;
}

//LISTA DOBLE ARTICULOS ----------------------------------------
void NodoArticulo::imprimir(){
	cout<<codigo<<endl; 
	cout<<cantidad<<endl; 
	cout<<tiempoFabricacion<<endl;
	cout<<categoria<<endl; 
	cout<<ubicacion<<endl; 
	cout<<"------------"<<endl;
}

void ListaDoble::insertarInicio(int _cantidad, string _codigo, string _categoria, string _ubicacion, int _tiempoFabricacion){
    if (primerArticulo==0)
	    primerArticulo=ultimoArticulo=new NodoArticulo(_cantidad, _codigo, _categoria, _ubicacion, _tiempoFabricacion);
    else{
	    primerArticulo->anterior= new NodoArticulo(_cantidad, _codigo, _categoria, _ubicacion, _tiempoFabricacion);
	    primerArticulo->anterior->siguiente=primerArticulo;
	    primerArticulo=primerArticulo->anterior;
    }
}

void ListaDoble::insertarFinal (int _cantidad, string _codigo, string _categoria, string _ubicacion, int _tiempoFabricacion){
    if (primerArticulo==0)
	    primerArticulo=ultimoArticulo=new NodoArticulo(_cantidad, _codigo, _categoria, _ubicacion, _tiempoFabricacion);
    else{
	    ultimoArticulo->siguiente= new NodoArticulo(_cantidad, _codigo, _categoria, _ubicacion, _tiempoFabricacion);
	    ultimoArticulo->siguiente->anterior=ultimoArticulo;
	    ultimoArticulo=ultimoArticulo->siguiente; 
    }
}

NodoArticulo * ListaDoble::borrarAlFinal(){
	NodoArticulo * borrado=ultimoArticulo;
	if (primerArticulo!=NULL){
		if (primerArticulo==ultimoArticulo){
			primerArticulo=ultimoArticulo=NULL;
    	}else{
        	ultimoArticulo=ultimoArticulo->anterior;
			borrado->anterior=NULL;
			ultimoArticulo->siguiente=NULL;
    	}
	}
    return borrado;
}

void ListaDoble::leerArchivoArticulos(){
	ifstream archivo;
	string texto;
	string codigo, categoria, ubicacion, cantidadS, tiempoS;
	archivo.open("articulos.txt",ios::in);
	
	if (archivo.fail()){
		cout<<"No lei el archivo"<<endl;
		exit(1);
	}else{
		while(getline(archivo, texto)){
			istringstream ss(texto);
			getline(ss,codigo,'\t');
			getline(ss,cantidadS,'\t');
			getline(ss,tiempoS,'\t');
			getline(ss,categoria,'\t');
			getline(ss,ubicacion,'\t');
			insertarFinal(stoi(cantidadS),codigo,categoria,ubicacion,stoi(tiempoS));
		}
		archivo.close();
	}
}

void ListaDoble::imprimir(){
	NodoArticulo * tmp = primerArticulo;
	while(tmp!=NULL){
		tmp->imprimir();
		tmp=tmp->siguiente;
    }
}

//LISTA PRODUCTOS -------------------------
void ListaProductos::insertarInicioProducto(string _codigoProducto, int _cantidad){
    if (primerProducto==NULL)
	    primerProducto=ultimoProducto=new Producto(_codigoProducto, _cantidad);
    else{
	    primerProducto->productoAnterior= new Producto(_codigoProducto, _cantidad);
	    primerProducto->productoAnterior->siguienteProducto=primerProducto;
	    primerProducto=primerProducto->productoAnterior;
    }
}

void ListaProductos::insertarFinalProducto (string _codigoProducto, int _cantidad){
    if (primerProducto==NULL)
	    primerProducto=ultimoProducto=new Producto(_codigoProducto, _cantidad);
    else{
	    ultimoProducto->siguienteProducto= new Producto(_codigoProducto, _cantidad);
	    ultimoProducto->siguienteProducto->productoAnterior=ultimoProducto;
	    ultimoProducto=ultimoProducto->siguienteProducto; 
    }
}

Producto * ListaProductos::borrarAlFinal(){
	Producto * borrado=ultimoProducto;
	if (primerProducto!=NULL){
		if (primerProducto==ultimoProducto){
			primerProducto=ultimoProducto=NULL;
    	}else{
        ultimoProducto=ultimoProducto->productoAnterior;
		borrado->productoAnterior=NULL;
		ultimoProducto->siguienteProducto=NULL;
    	}
	}
    return borrado;
}

//LISTA CLIENTES --------------------------------------
void ListaClientes::insertarInicioCliente (string codigoCliente, string nombreCliente,int prioridad){
    if (primerCliente==NULL)
	    primerCliente=new Cliente (codigoCliente, nombreCliente, prioridad);
    else{
		Cliente * nuevo=new Cliente (codigoCliente, nombreCliente, prioridad);
	    nuevo->siguiente=primerCliente;
	    primerCliente=nuevo;
    }
}

void ListaClientes::imprimir(){
		Cliente * tmp = primerCliente;
		while(tmp!=NULL){
			tmp->imprimir();
			tmp=tmp->siguiente;
        }
    }
//------------------ cliente ----------------------
void Cliente::imprimir(){
	cout<<codigoCliente<<endl; 
	cout<<nombreCliente<<endl; 
	cout<<prioridad<<endl; 
	cout<<"------------"<<endl;
}

void ListaClientes::leerArchivoClientes(){
	ifstream archivo;
	string texto;
	archivo.open("clientes.txt",ios::in);
	string codigo, nombre, sPrioridad;
	int prioridad;
	Cliente * cliente;
	if (archivo.fail()){
		cout<<"No lei el archivo"<<endl;
		exit(1);
	}else{
		while(getline(archivo, texto)){
			istringstream ss(texto);
			getline(ss, codigo, '\t');
    		getline(ss, nombre, '\t');
    		getline(ss, sPrioridad);
			prioridad=stoi(sPrioridad);
			insertarInicioCliente(codigo,nombre,prioridad);
		}
		archivo.close();
	}
}

void ListaClientes::annadirClienteAlArchivo(string codigoCliente, string nombreCliente,int prioridad){
	ofstream archivo;
	archivo.open("clientes.txt",ios::app);
	if (archivo.fail()){
		cout<<"No abrí el archivo"<<endl;
		exit(1);
	}else{
		archivo <<"\n"<<codigoCliente<<"\t"<<nombreCliente<<"\t"<< prioridad;
		archivo.close();
	}
}

