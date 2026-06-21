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
        printf("5. Salir\n");
        printf("Seleccione una opcion >> ");
        scanf("%d", &opcion);
        limpiarBuffer();

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
                printf("Salio del sistema\n");
                break;
            default:
                printf("Opcion invalida.\n");
        }

    } while (opcion != 5);

    return 0;
}