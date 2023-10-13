#include "Funciones.cpp"

int main(int argc, char const *argv[])
{
    ColaPedidos *cola=new ColaPedidos();
    ColaPedidosPrioridad *colaPrioridad= new ColaPedidosPrioridad();
    ColaPedidosEspeciales *colaEspecial= new ColaPedidosEspeciales();
    // cout<<"---------------------------- CLIENTES -------------------------------------"<<endl;
    ListaClientes *listaClientes=new ListaClientes();
    listaClientes->leerArchivoClientes();
    // cout<<"---------------------------- ARTÍCULOS ------------------------------------"<<endl;
    ListaDoble * listaArticulos=new ListaDoble();
    listaArticulos->leerArchivoArticulos();
    
    threadPedidos threadPed(cola, colaPrioridad, listaClientes, listaArticulos);
    
    // this_thread::sleep_for(chrono::seconds(9));
    // threadPed.Terminar();
    ListaRobots *listaRobots= new ListaRobots();
    listaRobots->leerArchivoRobots();
    ColaFacturacion *colaFacturacion=new ColaFacturacion();
    ColaAlistadoos *colaAlistados=new ColaAlistadoos();

    // ;
    // this_thread::sleep_for(chrono::seconds(12));
    // threadEmpacador.Terminar();

    // colaFacturacion->imprimir();
    ThreadBalanceador balanceador(cola,colaPrioridad,listaArticulos,colaEspecial);
    ThreadEmpacador threadEmpacador(colaFacturacion,colaAlistados);
    ThreadFacturador ThreadFacturador(colaFacturacion);
    int opcion=1;
    do{
        opcion=menuPrincipal();
        switch (opcion){
        case 1:
            menuPedidosEspeciales(colaEspecial);
            break;
        case 2:
            
            break;
        case 3:
            
            break;
        case 4:
            
            break;
        case 5:
            
            break;
        case 6:
            menuRobots(listaRobots);
            break;
        case 7:
            
            break;
        default:
            cout<<"La opción escogida no existe."<<endl;
            break;
        }
    } while (opcion!=0);
    


    return 0;
}
