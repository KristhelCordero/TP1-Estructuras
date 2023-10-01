#include "Estructuras.h"

//COLA ------------------------------------------------
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
		primerPedido=primerPedido->anterior;
		borrado->anterior=NULL;
		primerPedido->siguiente=NULL;
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

//LISTA DOBLE ----------------------------------------
void ListaDoble::insertarInicio(int _dato){
	    if (pn==0)
		    pn=un=new NodoDoble(_dato);
	    else{
		    pn->anterior= new NodoDoble(5);
		    pn->anterior->siguiente=pn;
		    pn=pn->anterior;
	    }
    }

    void ListaDoble::insertarFinal (int _dato){
	    if (pn==0)
		    pn=un=new NodoDoble(_dato);
	    else{
		    un->siguiente= new NodoDoble(5);
		    un->siguiente->anterior=un;
		    un=un->siguiente; 
	    }
    }

    void ListaDoble::imprimirAlReves(){
		NodoDoble * tmp = un;
		while(tmp!=NULL){
			cout<< tmp->dato <<endl; 
			tmp=tmp->anterior;
        }
    }

	NodoDoble * ListaDoble::borrarAlFinal(){
		NodoDoble * borrado=un;
		if (pn!=NULL)
			if (pn==un){
				pn=un=NULL;
        }else{
            un=un->anterior;
				borrado->anterior=NULL;
				un->siguiente=NULL;
        }
        return borrado;
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
		if (primerProducto!=NULL)
			if (primerProducto==ultimoProducto){
				primerProducto=ultimoProducto=NULL;
        }else{
            ultimoProducto=ultimoProducto->productoAnterior;
				borrado->productoAnterior=NULL;
				ultimoProducto->siguienteProducto=NULL;
        }
        return borrado;
	}