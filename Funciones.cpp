#include "Estructuras.h"

string leerYEncolarPedidos(ColaPedidos* cola, ColaPedidosPrioridad* colaPrioridad,string _nombreArchivo,
ListaClientes* listaClientes, ListaDoble* listaArticulos);
string obtenerHoraActual();
string obtenerFechaActual();
string facturarPedido(NodoPedido *pedido, string _nombreArchivo);
bool esInt(string num);
bool esIntRango(string numero, int menorQue, int mayorQue);
int calcularTiempoIda(Producto * producto,ListaDoble * articulos);
string obtenerFechaYHoraActual();
// Hay que cambiar los desencolar por el desencolar que está en colaPedidos

//COLA PEDIDOS-----------------------------------------------------------------------------------------------
void NodoPedido::annadirMovimiento(Movimiento* nuevoMovimiento){
	movimientos->agregarMovimiento(nuevoMovimiento);
}

bool ColaPedidos::estaVacia(){
	// lock_guard<mutex> lock(mtx);
	return primerPedido==NULL;
}

void ColaPedidos::encolar(int _numeroPedido, string _codigoCliente,ListaProductos * _productos){
	// lock_guard<mutex> lock(mtx);
	if(estaVacia())
		primerPedido=ultimoPedido=new NodoPedido(_numeroPedido, _codigoCliente, _productos, new BitacoraMovimientos());
	else{
		ultimoPedido->siguiente= new NodoPedido(_numeroPedido, _codigoCliente, _productos, new BitacoraMovimientos());
		ultimoPedido->siguiente->anterior=ultimoPedido;
		ultimoPedido=ultimoPedido->siguiente; 
    }
	//esto último no está probado
	Movimiento *nuevo= new Movimiento("En cola: ", obtenerFechaYHoraActual());
	ultimoPedido->annadirMovimiento(nuevo);
}

NodoPedido * ColaPedidos::desencolar(){
	// lock_guard<mutex> lock(mtx);
	if (primerPedido == NULL){
        return NULL;  
	}
    NodoPedido* borrado = primerPedido;
    primerPedido = primerPedido->siguiente;
    if (primerPedido != NULL) {
        primerPedido->anterior = NULL;
	}else{
        ultimoPedido = NULL;
	}
    borrado->siguiente = NULL;
    return borrado;
}

void ColaPedidos::imprimir(){
	// lock_guard<mutex> lock(mtx);
	NodoPedido * tmp = primerPedido;
	if (estaVacia()){
		cout<<"Está vacía"<<endl;
	}else{
		while(tmp!=NULL){
			cout<<tmp->numeroPedido<<endl; 
			cout<<tmp->codigoCliente<<endl;
			cout<<"----------------------"<<endl;
			tmp=tmp->siguiente;
    	}
	}
}

int ColaPedidos::largo(){
	// lock_guard<mutex> lock(mtx);
    NodoPedido * tmp = primerPedido;
    int contador=0;
    while(tmp!=NULL){
	    contador++;
	    tmp=tmp->siguiente;
    }
	return contador;
}

//COLA PRIORIDAD -------------------------------------------------------------------------------------------
bool ColaPedidosPrioridad::estaVacia(){
	// lock_guard<mutex> lock(mtx);
	return primerPedido==NULL;
}

void ColaPedidosPrioridad::encolar(int _numeroPedido, string _codigoCliente,ListaProductos * _productos){
	// lock_guard<mutex> lock(mtx);
	if(estaVacia())
		primerPedido=ultimoPedido=new NodoPedido(_numeroPedido, _codigoCliente, _productos, new BitacoraMovimientos());
	else{
		ultimoPedido->siguiente= new NodoPedido(_numeroPedido, _codigoCliente, _productos, new BitacoraMovimientos());
		ultimoPedido->siguiente->anterior=ultimoPedido;
		ultimoPedido=ultimoPedido->siguiente; 
    }
	//esto último no está probado
	ultimoPedido->annadirMovimiento(new Movimiento("En cola de Prioridad: ", obtenerFechaYHoraActual()));
}

NodoPedido * ColaPedidosPrioridad::desencolar(){
	// lock_guard<mutex> lock(mtx);
	if (primerPedido == NULL){
        return NULL;  
	}
    NodoPedido* borrado = primerPedido;
	primerPedido = primerPedido->siguiente;
    if (primerPedido != NULL) {
		primerPedido->anterior = NULL;
	}else{
		ultimoPedido = NULL;
	}
	borrado->siguiente = NULL;
	return borrado;
}

void ColaPedidosPrioridad::imprimir(){
	// lock_guard<mutex> lock(mtx);
	NodoPedido * tmp = primerPedido;
	while(tmp!=NULL){
		cout<<tmp->numeroPedido<<endl; 
		cout<<tmp->codigoCliente<<endl;
		cout<<"----------------------"<<endl;
		tmp=tmp->siguiente;
    }
}

int ColaPedidosPrioridad::largo(){
    // lock_guard<mutex> lock(mtx);
	NodoPedido * tmp = primerPedido;
    int contador=0;
    while(tmp!=NULL){
	    contador++;
	    tmp=tmp->siguiente;
    }
	return contador;
}

//COLA PEDIDOS ESPECIALES -----------------------------------------------------------------------------------
bool ColaPedidosEspeciales::estaVacia(){
	// lock_guard<mutex> lock(mtx);
	return primerPedido==NULL;
}

void ColaPedidosEspeciales::encolar(int _numeroPedido, string _codigoCliente,ListaProductos * _productos){
	// lock_guard<mutex> lock(mtx);
	if(estaVacia())
		primerPedido=ultimoPedido=new NodoPedido(_numeroPedido, _codigoCliente, _productos, new BitacoraMovimientos());
	else{
		ultimoPedido->siguiente= new NodoPedido(_numeroPedido, _codigoCliente, _productos, new BitacoraMovimientos());
		ultimoPedido->siguiente->anterior=ultimoPedido;
		ultimoPedido=ultimoPedido->siguiente; 
    }
	//esto último no está probado
	ultimoPedido->annadirMovimiento(new Movimiento("En cola de pedidos especiales: ", obtenerFechaYHoraActual()));
}

NodoPedido * ColaPedidosEspeciales::desencolar(){
	// lock_guard<mutex> lock(mtx);
	if (primerPedido == NULL){
        return NULL;  
	}
    NodoPedido* borrado = primerPedido;
	primerPedido = primerPedido->siguiente;
    if (primerPedido != NULL) {
		primerPedido->anterior = NULL;
	}else{
		ultimoPedido = NULL;
	}
	borrado->siguiente = NULL;
	return borrado;
}

void ColaPedidosEspeciales::imprimir(){
	// lock_guard<mutex> lock(mtx);
	NodoPedido * tmp = primerPedido;
	while(tmp!=NULL){
		cout<<tmp->numeroPedido<<endl; 
		cout<<tmp->codigoCliente<<endl;
		cout<<"----------------------"<<endl; 
		tmp=tmp->siguiente;
    }
}

int ColaPedidosEspeciales::largo(){
    // lock_guard<mutex> lock(mtx);
	NodoPedido * tmp = primerPedido;
    int contador=0;
    while(tmp!=NULL){
	    contador++;
	    tmp=tmp->siguiente;
    }
	return contador;
}

//LISTA DOBLE ARTICULOS -------------------------------------------------------------------------------------
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

void ListaDoble::insertarFinal(int _cantidad, string _codigo, string _categoria, string _ubicacion, int _tiempoFabricacion){
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

bool ListaDoble::encontrarArticulo(string _codigo){
	NodoArticulo * tmp = primerArticulo;
	while(tmp!=NULL){
		if(tmp->codigo==_codigo){
			return true;
		}
		tmp=tmp->siguiente;
    }
	return false;
}
//Falta probar esta función
int ListaDoble::cantidadArticuloBodega(string _codigo){
	NodoArticulo * tmp = primerArticulo;
	while(tmp!=NULL){
		if(tmp->codigo==_codigo){
			return tmp->cantidad;
		}
		tmp=tmp->siguiente;
    }
	return 0;
}

string ListaDoble::encontrarUbicacionArticulo(string _codigo){
	NodoArticulo * tmp = primerArticulo;
	while(tmp!=NULL){
		if(tmp->codigo==_codigo){
			return tmp->ubicacion;
		}
		tmp=tmp->siguiente;
    }
	return NULL;
}
//Falta probar esta función
void ListaDoble::actualizarArchivoArticulos(){
	ofstream archivo;
	archivo.open("articulos.txt",ios::out); //Al ya existir lo va a sobreescribir
	if (archivo.fail()){
		cout<<"No escribí el archivo"<<endl;
		exit(1);
	}else{
		NodoArticulo * tmp = primerArticulo;
		while(tmp!=NULL){
			archivo<<tmp->codigo<<"\t"<<tmp->cantidad<<"\t"<<tmp->tiempoFabricacion<<"\t"<<tmp->categoria<<"\t"<<tmp->ubicacion<<endl;
			tmp=tmp->siguiente;
    	}
		archivo.close();
	}

}

int ListaDoble::largo(){
    // lock_guard<mutex> lock(mtx);
	NodoArticulo * tmp = primerArticulo;
    int contador=0;
    while(tmp!=NULL){
	    contador++;
	    tmp=tmp->siguiente;
    }
	return contador;
}
//Falta probar esta función
bool ListaDoble::encontrarArticuloRepetido(string _codigo){
	NodoArticulo * tmp = primerArticulo;
	int contador=0;
	while(tmp!=NULL){
		if(tmp->codigo==_codigo){
			contador++;
		}
		tmp=tmp->siguiente;
    }
	if (contador>1)
		return true;
	else
		return false;
}
//Falta probar esta función
int ListaDoble::revisarListaArticulos(){
	//Si devuelve 0 todo está bien, si devuelve 1 algo está mal
	string articulos[largo()];
	NodoArticulo * tmp = primerArticulo;
	while(tmp!=NULL){
		if(tmp->cantidad<0){
			return 1;
		}else if (tmp->categoria!="A"&& tmp->categoria!="B" && tmp->categoria!="C"){
			return 1;
		}else if(encontrarArticuloRepetido(tmp->codigo)){
			return 1;
		}
		tmp=tmp->siguiente;
    }
	return 0;
}

int ListaDoble::sacarTiempoFabricacion(string _codigo){
	NodoArticulo * tmp = primerArticulo;
	while(tmp!=NULL){
		if(tmp->codigo==_codigo){
			return tmp->tiempoFabricacion;
		}
		tmp=tmp->siguiente;
    }
	return 0;
}

void ListaDoble::apartarProductos(ListaProductos *listaProductos){
	Producto * tmp = listaProductos->primerProducto;
	NodoArticulo * tmp2 = primerArticulo; 
	while(tmp2!=NULL){
		tmp = listaProductos->primerProducto;
		while (tmp!=NULL){
			if (tmp->codigoProducto==tmp2->codigo){
				tmp2->cantidad=tmp2->cantidad-tmp->cantidad;
			}
			tmp=tmp->siguienteProducto;
		}
		tmp2=tmp2->siguiente;
    }
}

void ListaDoble::annadirProductoAlmacen(int cantProducto, string codigoProducto){
	NodoArticulo * tmp = primerArticulo; 
	while(tmp!=NULL){
		if(tmp->codigo==codigoProducto){
			tmp->cantidad+=cantProducto;
		}
		tmp=tmp->siguiente;
    }
}
//LISTA PRODUCTOS ------------------------------------------------------------------------------------------
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
    // cout<<"Entré..."<<endl;
	if (primerProducto==NULL){ //se cae aqui
		// cout<<"Entré..y."<<endl;
	    primerProducto=ultimoProducto=new Producto(_codigoProducto, _cantidad);
    // cout<<"Entré..y."<<endl;
	}else{
		// cout<<"Entré..x."<<endl;
	    ultimoProducto->siguienteProducto= new Producto(_codigoProducto, _cantidad);
	    ultimoProducto->siguienteProducto->productoAnterior=ultimoProducto;
	    ultimoProducto=ultimoProducto->siguienteProducto; 
		// cout<<"Entré..z."<<endl;
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
//FALTA PROBAR ESTA FUNCION
Producto * ListaProductos::revisarProductosFaltantes(ListaDoble *listaArticulos){
	Producto *tmp=primerProducto;
	while(tmp!=NULL){
		cout<<"Revisar" <<endl;
		if (tmp->cantidad>listaArticulos->cantidadArticuloBodega(tmp->codigoProducto)){
			cout<<"Revisar22" <<endl;
			return tmp; // si devuelve un producto, hay que enviar ese producto a fabricar
		}
		tmp=tmp->siguienteProducto;
	}
	return NULL; //si tmp es NULL no hay ningun producto faltante
}
//FALTA PROBAR ESTA FUNCION
bool ListaProductos::exists(string _codigoProducto){
	Producto * tmp = primerProducto;
    while(tmp!=NULL){
	    if (tmp->codigoProducto==_codigoProducto)
			return true;
	    tmp=tmp->siguienteProducto;
    }
	return false;
}
//FALTA PROBAR ESTA FUNCION
int ListaProductos::cantidadArticulosDistintos(){
	Producto * tmp = primerProducto;
	ListaProductos * listaProvisional= new ListaProductos();
    int contador=0;
    while(tmp!=NULL){
	    if (!listaProvisional->exists(tmp->codigoProducto)) //no se si realmente sea necesario
			listaProvisional->insertarFinalProducto(tmp->codigoProducto,0); //porque puede ser que solo se ingresen productos diferentes
			contador++;
	    tmp=tmp->siguienteProducto;
    }
	return contador;
}

//LISTA CLIENTES -------------------------------------------------------------------------------------------
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
//Falta probar esta función
void ListaClientes::annadirClienteAlArchivo(string codigoCliente, string nombreCliente,int prioridad){
insertarInicioCliente(codigoCliente,nombreCliente,prioridad);
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

int ListaClientes::buscarPrioridadCliente(string codigoCliente){
	Cliente * tmp=primerCliente;
	while (tmp!=NULL){
		if(tmp->codigoCliente==codigoCliente)
			return tmp->prioridad;
		tmp=tmp->siguiente;
	}
	return 0;
}
//------------------ cliente ----------------------
void Cliente::imprimir(){
	cout<<codigoCliente<<endl; 
	cout<<nombreCliente<<endl; 
	cout<<prioridad<<endl; 
	cout<<"------------"<<endl;
}

// COLA DE ALISTO ------------------------------------------------------------------------------------------
bool ColaAlisto::estaVacia(){
	// lock_guard<mutex> lock(mtx);
	return primerPedido==NULL;
}

void ColaAlisto::encolar(NodoPedido *pedido){
	// lock_guard<mutex> lock(mtx);
	if(estaVacia())
		primerPedido=ultimoPedido=pedido;
	else{
		ultimoPedido->siguiente= pedido;
		ultimoPedido->siguiente->anterior=ultimoPedido;
		ultimoPedido=ultimoPedido->siguiente; 
    }
	//esto último no está probado
	Movimiento *nuevo=new Movimiento("En cola de alisto: ",obtenerFechaYHoraActual());
	ultimoPedido->annadirMovimiento(nuevo);
}

NodoPedido * ColaAlisto::desencolar(){
	// lock_guard<mutex> lock(mtx);
	if (primerPedido == NULL){
        return NULL;  
	}
    NodoPedido* borrado = primerPedido;
	primerPedido = primerPedido->siguiente;
    if (primerPedido != NULL) {
		primerPedido->anterior = NULL;
	}else{
		ultimoPedido = NULL;
	}
borrado->siguiente = NULL;
	return borrado;
}

void ColaAlisto::imprimir(){
	// lock_guard<mutex> lock(mtx);
	NodoPedido * tmp = primerPedido;
	while(tmp!=NULL){
		cout<<tmp->numeroPedido<<endl; 
		cout<<tmp->codigoCliente<<endl;
		cout<<"----------------------"<<endl;
		tmp=tmp->siguiente;
    }
}

int ColaAlisto::largo(){
	// lock_guard<mutex> lock(mtx);
    NodoPedido * tmp = primerPedido;
    int contador=0;
    while(tmp!=NULL){
	    contador++;
	    tmp=tmp->siguiente;
    }
	return contador;
}

// COLA ALISTADOOS ---------------------------------------------------------------------------------------
bool ColaAlistadoos::estaVacia(){
	// lock_guard<mutex> lock(mtx);
	return primerPedido==NULL;
}

void ColaAlistadoos::encolar(NodoPedido *pedido){
	// lock_guard<mutex> lock(mtx);
	if(estaVacia())
		primerPedido=ultimoPedido=pedido;
	else{
		ultimoPedido->siguiente= pedido;
		ultimoPedido->siguiente->anterior=ultimoPedido;
		ultimoPedido=ultimoPedido->siguiente; 
    }
	//esto último no está probado
	ultimoPedido->annadirMovimiento(new Movimiento("En cola de empaque: ", obtenerFechaYHoraActual()));
}

NodoPedido * ColaAlistadoos::desencolar(){
	// lock_guard<mutex> lock(mtx);
	if (primerPedido == NULL){
        return NULL;  
	}
    NodoPedido* borrado = primerPedido;
	primerPedido = primerPedido->siguiente;
    if (primerPedido != NULL) {
		primerPedido->anterior = NULL;
	}else{
		ultimoPedido = NULL;
	}
	borrado->siguiente = NULL;
	return borrado;
}

void ColaAlistadoos::imprimir(){
	// lock_guard<mutex> lock(mtx);
	NodoPedido * tmp = primerPedido;
	while(tmp!=NULL){
		cout<<tmp->numeroPedido<<endl; 
		cout<<tmp->codigoCliente<<endl;
		cout<<"----------------------"<<endl;
		tmp=tmp->siguiente;
    }
}

int ColaAlistadoos::largo(){
	// lock_guard<mutex> lock(mtx);
    NodoPedido * tmp = primerPedido;
    int contador=0;
    while(tmp!=NULL){
	    contador++;
	    tmp=tmp->siguiente;
    }
	return contador;
}

// COLA FACTURACION --------------------------------------------------------------------------------------
bool ColaFacturacion::estaVacia(){
	// lock_guard<mutex> lock(mtx);
	return primerPedido==NULL;
}

void ColaFacturacion::encolar(int _numeroPedido, string _codigoCliente, ListaProductos * _productos, BitacoraMovimientos * _bitacora){
	// lock_guard<mutex> lock(mtx);
	if(estaVacia()){ // se cae aqui
		primerPedido=ultimoPedido=new NodoPedido(_numeroPedido, _codigoCliente, _productos, _bitacora);
	}else{
		ultimoPedido->siguiente= new NodoPedido(_numeroPedido, _codigoCliente, _productos, _bitacora);
		ultimoPedido->siguiente->anterior=ultimoPedido;
		ultimoPedido=ultimoPedido->siguiente; 
    }
	//esto último no está probado
	Movimiento *nuevo=new Movimiento("A cola de facturación: ", obtenerFechaYHoraActual());
	ultimoPedido->annadirMovimiento(nuevo);
	
}

NodoPedido * ColaFacturacion::desencolar(){
	// lock_guard<mutex> lock(mtx);
	if (primerPedido == NULL){
        return NULL;  
	}
    NodoPedido* borrado = primerPedido;
	primerPedido = primerPedido->siguiente;
    if (primerPedido != NULL) {
		primerPedido->anterior = NULL;
	}else{
		ultimoPedido = NULL;
	}
borrado->siguiente = NULL;
	return borrado;
}

void ColaFacturacion::imprimir(){
	// lock_guard<mutex> lock(mtx);
	NodoPedido * tmp = primerPedido;
	while(tmp!=NULL){
		cout<<tmp->numeroPedido<<endl; 
		cout<<tmp->codigoCliente<<endl;
		cout<<"----------------------"<<endl;
		tmp=tmp->siguiente;
    }
}

int ColaFacturacion::largo(){
	// lock_guard<mutex> lock(mtx);
    NodoPedido * tmp = primerPedido;
    int contador=0;
    while(tmp!=NULL){
	    contador++;
	    tmp=tmp->siguiente;
    }
	return contador;
}

// LISTA ROBOTS ---------------------------------------------------------------------------------------------
void ListaRobots::insertarFinal(string _codigoRobot, string _articuloFabrica, bool _apagado, bool _esPrioridad){
    if (primerRobot==0)
	    primerRobot=ultimoRobot=new Robot(_codigoRobot, _articuloFabrica, _apagado, _esPrioridad);
    else{
	    ultimoRobot->siguiente= new Robot(_codigoRobot, _articuloFabrica, _apagado, _esPrioridad);
	    ultimoRobot->siguiente->anterior=ultimoRobot;
	    ultimoRobot=ultimoRobot->siguiente; 
    }
}

void Robot::imprimir(){
	cout<<codigoRobot<<endl; 
	cout<<articuloFabrica<<endl; 
	cout<<apagado<<endl;
	cout<<esPrioridad<<endl; 
	cout<<"------------"<<endl;
}

void ListaRobots::imprimir(){
	Robot * tmp = primerRobot;
	while(tmp!=NULL){
		tmp->imprimir();
		tmp=tmp->siguiente;
    }
}

void ListaRobots::leerArchivoRobots(){
	ifstream archivo;
	bool bApagado, bPrioridad;
	string texto,codigoRobot,articulo,apagado,esPrioridad;
	archivo.open("robots.txt",ios::in);
	
	if (archivo.fail()){
		cout<<"No lei el archivo"<<endl;
		exit(1);
	}else{
		while(getline(archivo, texto)){
			istringstream ss(texto);
			getline(ss,codigoRobot,'\t');
			getline(ss,articulo,'\t');
			getline(ss,apagado,'\t');
			if (apagado=="1")
				bApagado=false;
			else
				bApagado=true;
			getline(ss,esPrioridad,'\t');
			if (esPrioridad=="1")
				bPrioridad=true;
			else
				bApagado=false;
			insertarFinal(codigoRobot,articulo,bApagado,bPrioridad);
		}
		archivo.close();
	}
}

int ListaRobots::largo(){
	// lock_guard<mutex> lock(mtx);
    Robot * tmp = primerRobot;
    int contador=0;
    while(tmp!=NULL){
	    contador++;
	    tmp=tmp->siguiente;
    }
	return contador;
}

Robot * ListaRobots::buscarRobot(string _codigoRobot){
	Robot * tmp= primerRobot;
	while (tmp!=NULL){
		if(tmp->codigoRobot==_codigoRobot)
			return tmp;
		tmp=tmp->siguiente;
	}
	return NULL;
}

bool ListaRobots::existsRobot(string _numRobot){
	Robot * tmp= primerRobot;
	while (tmp!=NULL){
		if(tmp->codigoRobot==_numRobot)
			return true;
		tmp=tmp->siguiente;
	}
	return false;
}

void ListaRobots::modificarRobot(string _codigo, int opcion){
	// cout<<"1. Modificar Categoría"<<endl;
	// cout<<"2. Apagar Robot"<<endl;
	// cout<<"3. Encender Robot"<<endl;
	// cout<<"4. Cambiar Prioridad"<<endl;
	// cout<<"5. Imprimir lista de Robots"<<endl;
	Robot * tmp= primerRobot;
	string nuevo;
	unordered_set<string> opciones = {"A", "B", "C", "AB", "BC", "AC", "CB", "CA"};
	bool aceptado=false;
	while (tmp->codigoRobot!=_codigo){
		tmp=tmp->siguiente;
	}
	switch (opcion){
	case 1:
		do{
			cout<<"Ingrese el nuevo artículo que fabricará el robot: "<<endl;
			getline(cin,nuevo);
			if (opciones.count(nuevo)>0){
				aceptado=true;
			}else{
				cout<<"Ese tipo de artículo no existe"<<endl;
			}
		} while (!aceptado);
		tmp->articuloFabrica=nuevo;
		break;
	case 2:
		tmp->apagado=true;
		cout<<"Robot apagado"<<endl;
		break;
	case 3:
		tmp->apagado=false;
		cout<<"Robot Encendido"<<endl;
		break;
	case 4:
		if (tmp->esPrioridad){
			tmp->esPrioridad=false;
		}else{
			tmp->esPrioridad=true;
		}
		cout<<"Prioridad del robot cambiada"<<endl;
		break;
	case 5:
		imprimir();
		break;
	default:
		cout<<"No se seleccionó una opción válida"<<endl;
		break;
	}
}

Robot * ListaRobots::asignarPedidoRobot(string _CodigoProducto){
	string tipoProducto = string(1,_CodigoProducto.at(0));
	Robot * tmp =primerRobot;
	while (tmp!=NULL){
		if((tmp->articuloFabrica==tipoProducto || tmp->articuloFabrica=="Todos")&&(!tmp->apagado)){
			return tmp;
		}	
		tmp=tmp->siguiente;	
	}
	return NULL;
}

// THREAD PEDIDOS -------------------------------------------------------------------------------------------
void threadPedidos::leerArchivosPedidos() {
    while (!terminar) {
        while(pausado){
            this_thread::sleep_for(chrono::milliseconds(2000));
        }
		// cout<<"Entré"<<endl;
        if(direccion=opendir(dir.c_str())){
            while(elementos=readdir(direccion)){
				_nombreArchivo=".\\Pedidos-Clientes\\";
				_nombreArchivo+=elementos->d_name;
				// cout<<_nombreArchivo<<endl;
				if(_nombreArchivo!=".\\Pedidos-Clientes\\." && _nombreArchivo!=".\\Pedidos-Clientes\\.."){
                	// cout<<"Estoy"<<endl;
					nombreArchivo=leerYEncolarPedidos(cola, colaPrioridad,_nombreArchivo, listaClientes, listaArticulos);
                	if(nombreArchivo=="Error"){
						// cout<<"Llegué1"<<endl;
                	    nombreArchivo=".\\Errores\\"+_nombreArchivo.erase(0,19);
						// cout<<nombreArchivo<<endl;
						_nombreArchivo=".\\Pedidos-Clientes\\"+_nombreArchivo;
						// cout<<_nombreArchivo<<endl;
                	    rename(_nombreArchivo.c_str(),nombreArchivo.c_str());
						// cout<<"Llegué4"<<endl;
                	}else{
						// cout<<"Llegué2"<<endl;
						nombreArchivo.erase(0,19);
                	    nombreArchivo=".\\Pedidos-Procesados\\"+nombreArchivo;
						// cout<<nombreArchivo<<endl;
                	    rename(_nombreArchivo.c_str(), nombreArchivo.c_str());
						// cout<<"Llegué 3"<<endl;
                	}
				}
            }
        }
		closedir(direccion);
        this_thread::sleep_for(chrono::seconds(1));
    }
}

// THREAD BALANCEADOR ---------------------------------------------------------------------------------------
// No está probado
void ThreadBalanceador::procesarPedidos(){
	while (!terminar){
		while(apagado){
            this_thread::sleep_for(chrono::milliseconds(2000));
        }
		NodoPedido * pedidoProcesandose=NULL;
		Producto * productoAElaborar=NULL;
		Robot * robotAsignado=NULL;
		int esperarSegundos=0;
		int cantidadFabricar=0;
		Movimiento * nuevo=NULL;
		string fechaInicio;
		cout<<"BALANCEADOR" <<flush<<endl;
		if (!colaEspecial->estaVacia()&&!procesando){
			cout<<"BALANCEADOR cola especial" <<endl;
			pedidoProcesandose=colaEspecial->desencolar();
			cout<<"DESENCOLEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE"<<endl;
			procesando=true;
		}else if (!colaPrioridad->estaVacia()&&!procesando){
			cout<<"BALANCEADOR cola prioridad" <<endl;
			// colaPrioridad->imprimir();
			pedidoProcesandose=colaPrioridad->desencolar(); 
			// colaPrioridad->imprimir();
			procesando=true;
		}else if (!cola->estaVacia()&&!procesando){
			cout<<"BALANCEADOR cola normal" <<endl;
			pedidoProcesandose=cola->desencolar();
			cout<<"DESENCOLEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE"<<endl;
			procesando=true;
		}else{
			cout<<"BALANCEADOR esperando" <<endl;
			procesando=false;
			this_thread::sleep_for(chrono::seconds(5));
		}
		if (procesando){
			cout<<"BALANCEADOR procesando" <<endl;
			pedidoProcesandose->annadirMovimiento(new Movimiento("Balanceador: ", obtenerFechaYHoraActual()));
			do{
				cout<<"BALANCEADOR procesando3" <<endl;
				productoAElaborar=pedidoProcesandose->productos->revisarProductosFaltantes(listaArticulos);
				if (productoAElaborar==NULL){//No hay ningún producto faltante
					cout<<"BALANCEADOR ya elaboré2" <<endl;
					listaArticulos->apartarProductos(pedidoProcesandose->productos);
					colaDeAlisto->encolar(pedidoProcesandose);
					procesando=false;
					cout<<"BALANCEADOR ya elaboré" <<endl;
				}else{
					cout<<"BALANCEADOR aquii en el else de chill" <<endl;
					while(robotAsignado==NULL){
						cout<<"BALANCEADOR robot" <<endl;
						robotAsignado=listaRobots->asignarPedidoRobot(productoAElaborar->codigoProducto);
						this_thread::sleep_for(chrono::seconds(2));
					}
					pedidoProcesandose->annadirMovimiento(new Movimiento("A robot de fabricación "+robotAsignado->codigoRobot,
					obtenerFechaYHoraActual()));
					cantidadFabricar=productoAElaborar->cantidad-listaArticulos->cantidadArticuloBodega(productoAElaborar->codigoProducto);
					fechaInicio=obtenerFechaYHoraActual();
					esperarSegundos=cantidadFabricar*listaArticulos->sacarTiempoFabricacion(productoAElaborar->codigoProducto);
					cout<<"BALANCEADOR elaborando" <<endl;
					this_thread::sleep_for(chrono::seconds(esperarSegundos));
					listaArticulos->annadirProductoAlmacen(cantidadFabricar, productoAElaborar->codigoProducto);
					nuevo=new Movimiento(productoAElaborar->codigoProducto,robotAsignado->codigoRobot,
					to_string(cantidadFabricar),obtenerFechaYHoraActual(),fechaInicio);
					pedidoProcesandose->annadirMovimiento(nuevo);
					cout<<"BALANCEADOR elaborando2" <<endl;
				}
			}while (procesando);
		}
		this_thread::sleep_for(chrono::seconds(10));
	}
}

//THREAD EMPACADOR ------------------------------------------------------------------------------------------
void ThreadEmpacador::empacarPedidos(){
	while (!terminar){
		while(apagado){
            this_thread::sleep_for(chrono::seconds(10));
        }
		if (!colaAlistados->estaVacia()){
			cout<<"Empacando"<<endl;
			NodoPedido *pedido= colaAlistados->desencolar();
			int cantidadSegundos= pedido->productos->cantidadArticulosDistintos();
			this_thread::sleep_for(chrono::seconds(cantidadSegundos));
			colaFacturacion->encolar(pedido->numeroPedido,pedido->codigoCliente,pedido->productos, pedido->movimientos);
		}else{
			cout<<"Empacando esperando"<<flush<<endl;
			this_thread::sleep_for(chrono::seconds(5));
		}
	}
}

//THREAD FABRICADOR -----------------------------------------------------------------------------------------
void ThreadFacturador::facturarPedidos(){
	NodoPedido * pedidoEmpacado;
	while (!terminar){
		while(apagado){
            this_thread::sleep_for(chrono::seconds(10));
        }
		if (!colaFacturacion->estaVacia()){
			pedidoEmpacado=colaFacturacion->desencolar();
			cout<<"Desencolé"<<endl;
		
			pedidoEmpacado->annadirMovimiento(new Movimiento("Finalizado: ", obtenerFechaYHoraActual()));
			cout<<"Añadí el movimiento"<<endl;
			facturarPedido(pedidoEmpacado, to_string(pedidoEmpacado->numeroPedido)+"_"+
			pedidoEmpacado->codigoCliente+"_"+obtenerFechaYHoraActual()+".txt"); //+"_"+obtenerFechaActual()+obtenerHoraActual()
			// cout<<"Facturé"<<endl;
			this_thread::sleep_for(chrono::seconds(1));
		}else{
			this_thread::sleep_for(chrono::seconds(1));
		}
	}
}

//LISTA ALISTADORES -------------------------------------------------------------------------------------------
int ListaAlistadores::largo(){
	int largo=0;
	Alistador* nodo=primerAlistador;
	while(nodo!=NULL){
		largo++;
		nodo=nodo->siguiente;
	}
	return largo;
}

void ListaAlistadores::insertarFinal( bool _apagado, int ID){
    if (primerAlistador==NULL){
	    primerAlistador=ultimoAlistador=new Alistador(_apagado, ID);
	}else{
	    ultimoAlistador->siguiente= new Alistador(_apagado, ID);
	    ultimoAlistador->siguiente->anterior=ultimoAlistador;
	    ultimoAlistador=ultimoAlistador->siguiente; 
    }
}

void ListaAlistadores::ordenarListaPorTiempo() {
    int largo = this->largo();
    for (int i = 0; i < largo - 1; i++) {
        Alistador* temp = primerAlistador;
        Alistador* siguiente = temp->siguiente;

        for (int j = 0; j < largo - i - 1; j++) {
            if (temp->tiempo > siguiente->tiempo) {
                if (temp->anterior) {
                    temp->anterior->siguiente = siguiente;
                } else {
                    primerAlistador = siguiente;
                }

                if (siguiente->siguiente) {
                    siguiente->siguiente->anterior = temp;
                } else {
                    ultimoAlistador = temp;
                }

                temp->siguiente = siguiente->siguiente;
                siguiente->anterior = temp->anterior;

                temp->anterior = siguiente;
                siguiente->siguiente = temp;

                if (temp->anterior) {
                    temp->anterior->siguiente = siguiente;
                } else {
                    primerAlistador = siguiente;
                }

                if (siguiente->siguiente) {
                    siguiente->siguiente->anterior = temp;
                } else {
                    ultimoAlistador = temp;
                }
            }


            temp = siguiente;
            siguiente = temp->siguiente;
        }
    }
}

void ListaAlistadores::mostrarAlistadores() {
    // Ordena la lista por tiempo
    // Recorre la lista ordenada y muestra los alistadores
    Alistador* temp = primerAlistador;
    int orden = 1;
	string estado;

    while (temp!=NULL) {
		if (temp->apagado){estado= "Apagado";}else{estado= "Encendido";}
        std::cout << "Alistador " << orden << ": ID = " << temp->ID <<"\nEstado: "<<estado<<endl;
        temp = temp->siguiente;
        orden++;
    }
}

int ListaAlistadores::tiempoMaximo(){
	Alistador * temp= primerAlistador;
	int tiempoMaximo=0;
	while (temp!=NULL){
		if (temp->tiempo>tiempoMaximo){
			cout<<"hola soy"<<tiempoMaximo<<endl;
			tiempoMaximo=temp->tiempo;
			cout<<"hola soy"<<tiempoMaximo<<endl;
		}
		cout<<"temporal tiempo: "<<temp->tiempo<<endl;
		temp=temp->siguiente;
	}
	cout<<"retorno"<<endl;
	return tiempoMaximo;
}

void ListaAlistadores::resetearTiempos(){
	Alistador * temp= primerAlistador;
	while (temp!=NULL){
		cout<<"Aqui estoy con la cara destapada"<<endl;
		temp->tiempo=0;
		temp= temp->siguiente;
	}
}

void ListaAlistadores::apagarAlistador(int ID){
	Alistador * temp = primerAlistador;
	while (temp!=NULL)
	{
		if (temp->ID==ID){
			temp->apagado=true;
			cout<<"Alistador "<<ID<<" apagado"<<endl;
		}
	}	 
}

void ListaAlistadores::encenderAlistador(int ID){
	Alistador * temp = primerAlistador;
	while (temp!=NULL)
	{
		if (temp->ID==ID){
			temp->apagado=false;
			cout<<"Alistador "<<ID<<" encendido"<<endl;

		}
	}	 
}

bool ListaAlistadores::exist(int ID){
	Alistador*temp=primerAlistador;
	while (temp!=NULL)
	{
		if(temp->ID==ID){
			return true;
		}
		temp=temp->siguiente;
	}
	return false;
	
}

// void Alistador::alistar(NodoPedido * pedido, ColaAlistados * alistados, ListaDoble * articulos){
// 	int tiempo = calcularTiempoIda(pedido, articulos);

// std::this_thread::sleep_for(std::chrono::seconds(tiempo));
// 	alistados->encolar( pedido->numeroPedido, pedido->codigoCliente, pedido->productos);
// 	cout<<"Pedido "<< pedido->numeroPedido <<" alistado. \n"<<
// 	"Alistador: "<<ID<<endl;
// 	std::this_thread::sleep_for(std::chrono::seconds(5));
// }

void ThreadPicking::pasarAlistadoresEncendidosYApagados(){
	Alistador* tempEncendidos= alistadores->primerAlistador; 
	Alistador * tempApagados= alistadoresApagados->primerAlistador;
	while (tempEncendidos!=NULL)
	{
		if (tempEncendidos->apagado){
			apagarAlistador(tempEncendidos->ID);
		}
		tempEncendidos=tempEncendidos->siguiente;
	}
	while (tempApagados!=NULL)
	{
		if (!tempApagados->apagado){
			encenderAlistador(tempApagados->ID);
		}
		tempApagados=tempApagados->siguiente;
	}
	
}

void ThreadPicking::apagarAlistador(int ID){
	Alistador * temp=alistadores->primerAlistador;
	while (temp!=NULL)
	{
		if (temp->ID==ID){
			//pasar alistador con ID igual a la lista alistadoresApagados
			alistadoresApagados->insertarFinal(true, temp->ID);

            if (temp->anterior!=NULL) {
                temp->anterior->siguiente = temp->siguiente;
            } else {
                alistadores->primerAlistador = temp->siguiente;
            }
            if (temp->siguiente!=NULL) {
                temp->siguiente->anterior = temp->anterior;
            } else {
                alistadores->ultimoAlistador = temp->anterior;
            }
            delete temp;
			cout<<"Alistador "<<ID<<" apagado"<<endl;
			break;
		}
		temp= temp->siguiente;
	}
	cout<<"El alistador no existe o no se encuentra apagado"<<endl;
	
}

void ThreadPicking::encenderAlistador(int ID) {
    Alistador* temp = alistadoresApagados->primerAlistador;
    while (temp != NULL) {
        if (temp->ID == ID) {
            // Pasar el alistador con ID igual a la lista de alistadores
            alistadores->insertarFinal(false, temp->ID);

            if (temp->anterior != NULL) {
                temp->anterior->siguiente = temp->siguiente;
            } else {
                alistadoresApagados->primerAlistador = temp->siguiente;
            }
            if (temp->siguiente != NULL) {
                temp->siguiente->anterior = temp->anterior;
            } else {
                alistadoresApagados->ultimoAlistador = temp->anterior;
            }
            delete temp;
            break;
        }
        temp = temp->siguiente;
    }
}

void ThreadPicking::picking(){
	while (!terminar){
		while(apagado){
			this_thread::sleep_for(std::chrono::seconds(5));
		}
		Alistador *alistador=NULL;
		NodoPedido *pedido=NULL;
		Producto *producto=NULL;
		int tiempo=0;
		cout<<"HOLA SOY EL PICKING"<<endl;
		if (!paraAlisto->estaVacia()){
			cout<<"Estoy alistando"<<endl;
			alistador=alistadores->primerAlistador;
			if(pedido==NULL||pedido->alistado){ //alistado empieza com NULL en todos los pedidos
				pedido= paraAlisto->desencolar();
				cout<<"Acabo de desencolar"<<endl;
				producto = pedido->productos->primerProducto;
			}
			while (producto!=NULL && alistador!=NULL){
			//listaordenada por tiempo
				cout<<"Calculo Tiempo"<<endl;
				alistador->tiempo=calcularTiempoIda(producto,articulos);
				cout<<"Calculo Tiempo2"<<endl;
				//alistador->alistar(pedido,alistados, articulos);//
				pedido->annadirMovimiento(new Movimiento(to_string(alistador->ID), producto->codigoProducto,
					articulos->encontrarUbicacionArticulo(producto->codigoProducto),to_string(alistador->tiempo)));
				cout<<"Calculo Tiempo3"<<endl;
				producto=producto->siguienteProducto;
				alistador=alistador->siguiente;
			}
			if (producto==NULL){ pedido->alistado=true;}
			//calcular duracion maxima (y durarla)
			tiempo=alistadores->tiempoMaximo();
			cout<<"Prueba!: "<<tiempo<<endl;
			cout<<"Alistadores desplegados\nProductos listos en: "<<tiempo * 2<<endl;
			std::this_thread::sleep_for(std::chrono::seconds(tiempo));
			//encolar producto

			cout<<"Alistadores regresando..."<<endl;
			//tiempo
			this_thread::sleep_for(std::chrono::seconds(tiempo));
			if (pedido->alistado){
				alistados->encolar(pedido);
				cout<<"Pedido "<<pedido->numeroPedido<< " alistado."<<endl;
				//movimientos??
			}
			cout<<"ordenando"<<endl;
			alistadores->ordenarListaPorTiempo();
			cout<<"ordenando2"<<endl;
			//resetear tiempos
			alistadores->resetearTiempos();
			cout<<"resetear tiempos"<<endl;
			pasarAlistadoresEncendidosYApagados();
			cout<<"cambiarlos de lista"<<endl;
		}else{
			this_thread::sleep_for(std::chrono::seconds(10));
		}
	}	
}

bool ColaAlistadores::estaVacia(){
	// lock_guard<mutex> lock(mtx);
	return primerAlistador==NULL;
}

void ColaAlistadores::encolar(Alistador *alistador){
	// lock_guard<mutex> lock(mtx);
	if(estaVacia()){ // se cae aqui
		primerAlistador=ultimoAlistador=alistador;
	}else{
		ultimoAlistador->siguiente= alistador;
		ultimoAlistador->siguiente->anterior=ultimoAlistador;
		ultimoAlistador=ultimoAlistador->siguiente; 
    }
	//esto último no está probado
	// Movimiento *nuevo=new Movimiento("A empaque: ", obtenerFechaActual()+" "+obtenerHoraActual());
	// ultimoPedido->annadirMovimiento(nuevo);
	
}

Alistador * ColaAlistadores::desencolar(){
	// lock_guard<mutex> lock(mtx);
	Alistador * borrado= primerAlistador;
	if(primerAlistador==ultimoAlistador){
		primerAlistador=ultimoAlistador=NULL;
	}else{
		primerAlistador=primerAlistador->siguiente;
		borrado->siguiente=NULL;
		primerAlistador->anterior=NULL;
	}
	return borrado;
}

void ColaAlistadores::imprimir(){
	// lock_guard<mutex> lock(mtx);
	Alistador * tmp = primerAlistador;
	while(tmp!=NULL){
		cout<<tmp->ID<<endl; 
		cout<<"----------------------"<<endl;
		tmp=tmp->siguiente;
    }
}

//--------------------------------------- FUNCIONES SIN ESTRUCTURA ------------------------------------------
string leerYEncolarPedidos(ColaPedidos* cola, ColaPedidosPrioridad* colaPrioridad,string _nombreArchivo,
ListaClientes* listaClientes, ListaDoble* listaArticulos){
	ifstream archivo;
	string texto, numPedido, codigoCliente, codigoProducto, cantidadP, cont;
	ListaProductos * productos= new ListaProductos();
	archivo.open(_nombreArchivo,ios::in);
	// cout<<"Estoy en leer y encolar"<<endl;
	if (archivo.fail()){
		// cout<<"No lei el archivo"<<endl;
		exit(1);
	}else{
		getline(archivo,numPedido);
		getline(archivo,codigoCliente);
		while(getline(archivo, texto)){
			istringstream ss(texto);
			getline(ss,codigoProducto,'\t');
			if (!listaArticulos->encontrarArticulo(codigoProducto)){
				archivo.close();
				return "Error";
			}
			getline(ss,cantidadP,'\t');
			if (stoi(cantidadP)<1){
				archivo.close();
				return "Error";
			}
			productos->insertarFinalProducto(codigoProducto,stoi(cantidadP));
		}
		// cout<<"Llegué hasta aqui wuuu"<<endl;
		if (listaClientes->buscarPrioridadCliente(codigoCliente)!=10 && listaClientes->buscarPrioridadCliente(codigoCliente)!=0){
			cola->encolar(stoi(numPedido),codigoCliente, productos);
		}else if (listaClientes->buscarPrioridadCliente(codigoCliente)!=0){
			colaPrioridad->encolar(stoi(numPedido),codigoCliente, productos);
		}else{
			archivo.close();
			// cout<<"Aqui pedido2"<<endl;
			return "Error";
		}
		// cout<<"Terminé leer y encolar"<<endl;
		archivo.close();
		return _nombreArchivo;
	}
}

string obtenerHoraActual() {
    auto ahora = chrono::system_clock::now();
    time_t tiempoActual = chrono::system_clock::to_time_t(ahora);
    tm tiempoLocal = *localtime(&tiempoActual);
    char buffer[9];
    sprintf(buffer, "%02d-%02d-%02d", tiempoLocal.tm_hour,
	 tiempoLocal.tm_min, tiempoLocal.tm_sec);
    return string(buffer);
}

string obtenerFechaActual() {
    auto ahora = chrono::system_clock::now();
    time_t tiempoActual = chrono::system_clock::to_time_t(ahora);
    tm tiempoLocal = *localtime(&tiempoActual);
    char buffer[11];
    sprintf(buffer, "%02d-%02d-%04d", tiempoLocal.tm_mday,
	 tiempoLocal.tm_mon + 1, tiempoLocal.tm_year + 1900);
    return string(buffer);
}

string obtenerFechaYHoraActual() {
    string fecha = obtenerFechaActual();
    string hora = obtenerHoraActual();
    return fecha + "_" + hora;
}

string facturarPedido(NodoPedido *pedido, string _nombreArchivo){
	ofstream archivo;
	short contador=0;
	archivo.open(_nombreArchivo,ios::out); //Al ya existir lo va a sobreescribir
	if (archivo.fail()){
		cout<<"No escribí el archivo"<<endl;
		exit(1);
	}
	archivo<<"Pedido: \t"<<pedido->numeroPedido<<endl;
	archivo<<"Cliente: \t"<<pedido->codigoCliente<<endl;
	cout<<"Llegué aqui"<<endl;
	Movimiento * tmpMov=pedido->movimientos->primerMov;
	while (tmpMov!=NULL){
		if (!tmpMov->robot && !tmpMov->alistador){
			archivo<<tmpMov->ubicacion<<"\t"<<tmpMov->info<<endl;
		}
		tmpMov=tmpMov->siguiente;
	}
	cout<<"Otra vez"<<endl;
	tmpMov=pedido->movimientos->primerMov;
	while (tmpMov!=NULL){
		if(tmpMov->robot){ //robot
			archivo<<endl;
			archivo<<"Robots Fábrica"<<endl;
			archivo<<"ARTICULO " << tmpMov->articulo<< "\t Fabricado en "<< 
			tmpMov->fabricadoEn << "/n"<< tmpMov->cantidad<< "unidades"<<
			"\nincio: "<<tmpMov->fechaInicio <<"\nfinal: "<<tmpMov->fechaFinal<<endl;
		}else if (tmpMov->alistador){ //alistador
			if(contador==0){
				archivo<<endl;
				archivo<<"Alisto "<< "\t Alistador "<< tmpMov->numAlistador <<endl;
				contador++;
			}
			archivo<< tmpMov->articulo<< "\t Ubicación: "<<tmpMov->ubicacion <<
			"\tfinal: "<<tmpMov->tiempo<< "s" << endl;
		}
		tmpMov=tmpMov->siguiente;
	}
	cout<<"Aqui también llegué"<<endl;
	archivo.close();
	return "Listo";
}

int calcularTiempoIda(Producto * producto, ListaDoble * articulos){
	string ubicacion=articulos->encontrarUbicacionArticulo(producto->codigoProducto);
	int columna=ubicacion[0]-'A'+1;
	cout<<"Ubicacion:"<<ubicacion<<endl;
	int fila = (ubicacion[1]-'0')*10+(ubicacion[2]-'0');
	cout<<"columna:"<<columna<<endl;
	cout<<"fila:"<<fila<<endl;

	int tiempo =columna+fila;
	cout<<"Tiempo:"<<tiempo<<endl;
	return tiempo;

}

void menuRobots(ListaRobots *robots){ //Esto lo maneja Jota
	string opcion,numRobot;
	bool aceptado=false;
	do{
		cout<<"------------------------------- MENÚ -------------------------------"<<endl;
    	cout<<"1. Modificar Categoría"<<endl;
		cout<<"2. Apagar Robot"<<endl;
		cout<<"3. Encender Robot"<<endl;
		cout<<"4. Cambiar Prioridad"<<endl;
		cout<<"5. Imprimir lista de Robots"<<endl;
		cout<<"Digite la opción que desea: "<<endl;
		getline(cin,opcion);//validaciones

		if (esIntRango(opcion,6,0)){
			aceptado=true;
			cout<<"Ingrese el número del robot: "<<endl;
			getline(cin,numRobot);
			if (robots->existsRobot(numRobot)){
				aceptado=true;
			}else{
				aceptado=false;
				cout<<"El robot que digitó no existe inténtelo de nuevo"<<endl;
			}
		}else{
			cout<<"Ingrese un número entero que se encuentre entre las opciones"<<endl;
			aceptado=false;
		}
	} while (!aceptado);
	robots->modificarRobot(numRobot,stoi(opcion));
}

int menuPrincipal(){
	string opcion;
	cout<<"------------------------------- MENÚ -------------------------------"<<endl;
	cout<<"1: Agregar Pedido"<<endl;
	cout<<"2: Apagar/Encender Balanceador"<<endl;
	cout<<"3: Agregar Cliente"<<endl;
	cout<<"4: Modificar Alistadores"<<endl;
	cout<<"5: Modificar Robots Fabricadores"<<endl;
	cout<<"6: Apagar/Encender Empacador"<<endl;
	cout<<"7: Apagar/Encender Facturador"<<endl;
	cout<<"8: Apagar/Encender Picking"<<endl;	
	cout<<"9: Imprimir Colas"<<endl;
	cout<<"0: Terminar la simulación"<<endl;
	getline(cin,opcion);//validaciones varias
	return stoi(opcion);
}

void menuPedidosEspeciales(ColaPedidosEspeciales * colaEspecial){
	string cantidad, IDcliente, numPedido, producto, cantProducto;
	ListaProductos *productos= new ListaProductos();
	cout<< "Ingrese el ID de cliente: "<<endl; //validar que exista
	getline(cin,IDcliente);
	cout<< "Ingrese el número de pedido: "<<endl;
	getline(cin,numPedido);
	cout<< "¿Cuántos productos desea agregar al pedido? "<<endl;
	getline(cin,cantidad);
	for (size_t i = 0; i < stoi(cantidad); i++){
		cout<< "Ingrese el código del producto: "<<endl;
		getline(cin,producto);
		cout<< "Ingrese la cantidad de producto: "<<endl;
		getline(cin,cantProducto);
		productos->insertarFinalProducto(producto,stoi(cantProducto));
	}
	colaEspecial->encolar(stoi(numPedido),IDcliente,productos);
}

void menuNuevoCliente(ListaClientes * listaClientes){
	string prioridad, codigoCliente, nombre;
	cout<< "Ingrese el código del nuevo cliente: "<<endl; //validar que exista
	getline(cin,codigoCliente);
	cout<< "Ingrese el número de pedido: "<<endl;
	getline(cin,nombre);
	cout<< "Ingrese la prioridad del cliente: "<<endl;
	getline(cin,prioridad);
	listaClientes->annadirClienteAlArchivo(codigoCliente,nombre,stoi(prioridad));
}

void menuAlistadores(ListaAlistadores *encendidos, ListaAlistadores *apagados){
// colocas aqui lo que ocupes, para hacer lo que dice la especificacion de la tp
	string opcion,IDRobot;
	cout<<"------------------------------- MENÚ -------------------------------"<<endl;
	cout<<"1. Apagar Robot"<<endl;
	cout<<"2. Encender Robot"<<endl;
	cout<<"3. Imprimir lista de Alistadores"<<endl;
	getline(cin,opcion);//validaciones
	if(!esInt(opcion)){opcion="0";}//Linea que salva codigos
	switch (stoi(opcion)){
	case 1:
		cout<<"Digite el ID del robot alistador que desea apagar (1-6): "<<flush;
		getline(cin,IDRobot);
		if(esIntRango(IDRobot,7,0)){
			if (encendidos->exist(stoi(IDRobot))){
				encendidos->apagarAlistador(stoi(IDRobot));
			}else{
				cout<<"El alistador"<<IDRobot<<" ya esta apagado"<<endl;
			}
		
		}else{
			cout<< "El ID de alistador ingresado no existe"<<endl;
			}
		break;
	case 2:
		cout<<"Digite el ID del robot alistador que desea encender (1-6): "<<flush;
		getline(cin,IDRobot);

		if(esIntRango(IDRobot,7,0)){
			if (apagados->exist(stoi(IDRobot))){
				apagados->encenderAlistador(stoi(IDRobot));
			}else{
				cout<<"El alistador"<<IDRobot<<" ya esta encendido"<<endl;
			}
		
		}else{
			cout<< "El ID de alistador ingresado no existe"<<endl;
			}
			
		break;
	case 3:
		encendidos->mostrarAlistadores();
		apagados->mostrarAlistadores();

		break;
	default:
		cout<<"No se seleccionó ninguna opción"<<endl;
		break;
	}
}

void menuColas(ColaPedidos * cola, ColaPedidosPrioridad * colaPrioridad, ColaPedidosEspeciales * colaEspecial, 
ColaAlisto *colaAlisto, ColaAlistadoos *colaAlistados, ColaFacturacion *colaFacturacion){
	string opcion;
	cout<<"------------------------------- MENÚ -------------------------------"<<endl;
	cout<<"1: Imprimir cola de pedidos"<<endl;
	cout<<"2: Imprimir cola de pedidos de prioridad"<<endl;
	cout<<"3: Imprimir cola de pedidos especiales"<<endl;
	cout<<"4: Imprimir cola de alisto"<<endl;
	cout<<"5: Imprimir cola de alistados"<<endl;
	cout<<"6: Imprimir cola de facturación"<<endl;
	getline(cin,opcion);
	switch (stoi(opcion)){
	case 1:
		cola->imprimir();
		break;
	case 2:
		colaPrioridad->imprimir();
		break;
	case 3:
		colaEspecial->imprimir();
		break;
	case 4:
		colaAlisto->imprimir();
		break;
	case 5:
		colaAlistados->imprimir();
		break;
	case 6:
		colaFacturacion->imprimir();
		break;
	default:
		cout<<"No se seleccionó ninguna opción"<<endl;
		break;
	}
}

// Validaciones ----------------------------------------------------------------------------------------------
// FALTA PROBAR ESTA FUNCION
bool esInt(string numero) {
    for (char c : numero) {
        if (!isdigit(c)) 
            return false;
	}
	return true;
}
//FALTA PROBAR ESTA FUNCION
bool esIntRango(string numero, int menorQue, int mayorQue){
	return (esInt(numero)&& stoi(numero)<menorQue && stoi(numero)>mayorQue);
}
