#include "Funciones.cpp"

int main(int argc, char const *argv[])
{

    // Movimiento *movimiento= new Movimiento("string1",obtenerFechaYHoraActual());
    // cout<<"hola"<<endl;
    // cout<< movimiento->info<<endl;
    // BitacoraMovimientos *bitacora= new BitacoraMovimientos();
    // bitacora->agregarMovimiento(movimiento);

    // ListaProductos *productos=new ListaProductos();
    // productos->insertarFinalProducto("Hola, soy el codigo",12);
    // NodoPedido *pedido= new NodoPedido(9, "hola soy el otro codigo",productos);
    // string nombre = pedido->numeroPedido +"_"+ pedido->codigoCliente +"_"+ obtenerFechaSYHoraActual();
    // nombre.erase(0, 1);
    // cout<<nombre<<endl;
    // cout<<facturarPedido(pedido, nombre)<<endl;// no me acorde
    ColaPedidos *cola=new ColaPedidos();
    ColaPedidosPrioridad *colaPrioridad= new ColaPedidosPrioridad();
    ColaPedidosEspeciales *colaEspecial= new ColaPedidosEspeciales();
    // // cout<<"---------------------------- CLIENTES -------------------------------------"<<endl;
    ListaClientes *listaClientes=new ListaClientes();
    listaClientes->leerArchivoClientes();
    // // cout<<"---------------------------- ARTÍCULOS ------------------------------------"<<endl;
    ListaDoble * listaArticulos=new ListaDoble();
    listaArticulos->leerArchivoArticulos();
    threadPedidos threadPed(cola, colaPrioridad, listaClientes, listaArticulos);
    ListaRobots *listaRobots= new ListaRobots();
    listaRobots->leerArchivoRobots();
    ColaFacturacion *colaFacturacion=new ColaFacturacion();
    ColaAlistadoos *colaAlistados=new ColaAlistadoos();
    ColaAlisto *colaAlisto= new ColaAlisto();
    ListaAlistadores *alistadores= new ListaAlistadores();
    this_thread::sleep_for(chrono::seconds(1));
    
    // this_thread::sleep_for(chrono::seconds(1));
    ThreadPicking picking(colaAlisto, colaAlistados, listaArticulos, alistadores);
    // this_thread::sleep_for(chrono::seconds(1));
    ThreadEmpacador threadEmpacador(colaFacturacion,colaAlistados);
    ThreadBalanceador balanceador(cola,colaPrioridad,listaArticulos,colaEspecial,listaRobots, colaAlisto);
    // this_thread::sleep_for(chrono::seconds(1));
    ThreadFacturador threadFacturador(colaFacturacion);
    // this_thread::sleep_for(chrono::seconds(1));
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
            // menuAlistadores(alistadores); 
            break;
        case 5:
            menuRobots(listaRobots);
            break;
        case 6:
            if (threadEmpacador.apagado){
                threadEmpacador.Reanudar();
                cout<<"El empacador ha sido encendido"<<endl;
            }else{
                threadEmpacador.Pausar();
                cout<<"El empacador ha sido apagado"<<endl;
            }
            break;
        case 7:
            if (threadFacturador.apagado){
                threadFacturador.Reanudar();
                cout<<"El facturador ha sido encendido"<<endl;
            }else{
                threadFacturador.Pausar();
                cout<<"El facturador ha sido apagado"<<endl;
            }
            break;
        case 8:
            menuColas(cola, colaPrioridad, colaEspecial, colaAlisto, colaAlistados, colaFacturacion);
            break;
        default:
            cout<<"La opción escogida no existe."<<endl;
            break;
        }
    } while (opcion!=0);
    cout<<"Apagando Componentes..."<<endl;
    // //Todos los terminar aqui(creo que para que todo termine tiene que estar todo encendido)
    this_thread::sleep_for(chrono::seconds(10));
    // threadPed.Terminar();
    // colaPrioridad->imprimir();
    // cout<<"*************************************************************************************************" <<endl;
    // cola->imprimir();
    balanceador.Terminar();
    picking.Terminar();
    threadEmpacador.Terminar();
    threadFacturador.Terminar();
    listaArticulos->actualizarArchivoArticulos();
    cout<<"Componentes Apagados..."<<endl;
    cout<<"Simulación terminada..."<<endl;

    return 0;

}
