#include <stdio.h>
#include "funciones.h"

int main() {
    int opcion;

    do {
        printf("\n      SGIC - RUEDAS DE ORO      \n");
        printf("1. Agregar vehiculo\n");
        printf("2. Listar vehiculos\n");
        printf("3. Buscar vehiculos\n");
        printf("4. Registrar venta\n");
        printf("5. Reporte de ventas\n");
        printf("6. Comisiones por vendedor\n");
        printf("7. Salir\n");

        opcion = leerEntero("Seleccione una opcion >> ");

        switch (opcion) {
            case 1:
                agregarVehiculo();
                break;
            case 2:
                listarVehiculos();
                break;
            case 3:
                buscarVehiculos();
                break;
            case 4:
                registrarVenta();
                break;
            case 5:
                reporteVentas();
                break;
            case 6:
                reporteComisiones();
                break;
            case 7:
                printf("Salio del sistema\n");
                break;
            default:
                printf("Opcion invalida. Ingrese una opcion del 1 al 7.\n");
        }

    } while (opcion != 7);

    return 0;
}