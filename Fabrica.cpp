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
    // cout<<"1: Agregar Pedido"<<endl;
	// cout<<"2: Apagar/Encender Balanceador"<<endl;
	// cout<<"3: Agregar Cliente"<<endl;
	// cout<<"4: Modificar Alistadores"<<endl;
	// cout<<"5: Modificar Robots Fabricadores"<<endl;
	// cout<<"6: Apagar/Encender Empacador"<<endl;
	// cout<<"7: Apagar/Encender Facturador"<<endl;
	// cout<<"0: Terminar la simulación"<<endl;
    int opcion=1;
    do{
        opcion=menuPrincipal();
        switch (opcion){
        case 1:
            menuPedidosEspeciales(colaEspecial);
            break;
        case 2:
            if (balanceador.apagado){
                balanceador.Reanudar();
                cout<<"El balanceador ha sido encendido"<<endl;
            }else{
                balanceador.Pausar();
                cout<<"El balanceador ha sido apagado"<<endl;
            }
            break;
        case 3:
            menuNuevoCliente(listaClientes);
            break;
        case 4:
            menuAlistadores(); //Aqui lo que ocupes 
            break;
        case 5:
            menuRobots(listaRobots);
            break;
        case 6:
            
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
