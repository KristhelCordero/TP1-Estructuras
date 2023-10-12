#include "Funciones.cpp"

int main(int argc, char const *argv[])
{
    ColaPedidos *cola=new ColaPedidos();
    ColaPedidosPrioridad *colaPrioridad= new ColaPedidosPrioridad();
    cout<<"---------------------------- CLIENTES -------------------------------------"<<endl;
    ListaClientes *listaClientes=new ListaClientes;
    listaClientes->leerArchivoClientes();
    listaClientes->imprimir();
    cout<<"---------------------------- ARTÍCULOS ------------------------------------"<<endl;
    ListaDoble * listaArticulos=new ListaDoble();
    listaArticulos->leerArchivoArticulos();
    listaArticulos->imprimir();
    
    threadPedidos threadPed(cola, colaPrioridad, listaClientes,listaArticulos);
    
    this_thread::sleep_for(chrono::seconds(9));
    threadPed.Terminar();

    // cout<<"---------------------------- COLAS ------------------------------------"<<endl;
    // colaPrioridad->imprimir();
    // cout<<"---------------------------- COLAS ------------------------------------"<<endl;
    // cola->imprimir();
    // ListaRobots *lista= new ListaRobots();
    // lista->leerArchivoRobots();
    // PRUEBA FACTURADOR ----------------------
    ColaFacturacion * colaFacturacion=new ColaFacturacion();
    NodoPedido *tmp=cola->primerPedido;
    NodoPedido *tmp2, *tmp3;
    cout<<"Aqui todo bien"<<endl;
    while(tmp!=nullptr){
        tmp2=cola->desencolar();
        colaFacturacion->encolar(tmp2);
        tmp=tmp->siguiente;
        cout<<"111"<<endl;
    }
    cout<<"AHHHH"<<endl;
    tmp3=colaPrioridad->primerPedido;
    while(tmp3!=NULL){
        tmp3=tmp3->siguiente;
        tmp2=colaPrioridad->desencolar();
        colaFacturacion->encolar(tmp2);
        cout<<"111"<<endl;
    }
    cout<<"No hice ni vrg"<<endl;
    ThreadFacturador facturador(colaFacturacion);
    this_thread::sleep_for(chrono::seconds(9));
    facturador.Terminar();
    return 0;
}
