#include "Funciones.cpp"

int main(int argc, char const *argv[])
{
    // ListaClientes * listaClientes=new ListaClientes();
    // listaClientes->leerArchivoClientes();
    // listaClientes->imprimir();
    ListaDoble * listaArticulos=new ListaDoble();
    listaArticulos->leerArchivoArticulos();
    listaArticulos->imprimir();
    return 0;
}
