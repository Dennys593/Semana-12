#include <stdio.h>
#include <string.h>
#include "funciones.h"

void limpiarBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int leerEntero(char mensaje[]) {
    int numero;
    int valido;

    do {
        printf("%s", mensaje);
        valido = scanf("%d", &numero);

        if (valido != 1) {
            printf("Error: ingrese solo numeros.\n");
            limpiarBuffer();
        }
    } while (valido != 1);

    limpiarBuffer();
    return numero;
}

float leerFloat(char mensaje[]) {
    float numero;
    int valido;

    do {
        printf("%s", mensaje);
        valido = scanf("%f", &numero);

        if (valido != 1 || numero <= 0) {
            printf("Error: ingrese un precio valido mayor a 0.\n");
            limpiarBuffer();
        }
    } while (valido != 1 || numero <= 0);

    limpiarBuffer();
    return numero;
}

void leerTexto(char mensaje[], char texto[], int tam) {
    int valido;
    int i;

    do {
        valido = 1;
        printf("%s", mensaje);
        fgets(texto, tam, stdin);

        if (texto[0] == '\n') {
            printf("Error: el campo no puede estar vacio.\n");
            valido = 0;
        }

    } while (valido == 0);

    i = 0;
    while (texto[i] != '\0') {
        if (texto[i] == '\n') {
            texto[i] = '\0';
        }
        i++;
    }
}

int generarId() {
    FILE *archivo = fopen("vehiculos.txt", "r");
    Vehiculo v;
    int ultimoId = 0;

    if (archivo == NULL) {
        return 1;
    }

    while (fscanf(archivo, "%d %s %s %s %s %f %d",
                  &v.id, v.marca, v.modelo, v.tipo,
                  v.estado, &v.precio, &v.disponible) == 7) {
        ultimoId = v.id;
    }

    fclose(archivo);
    return ultimoId + 1;
}

void agregarVehiculo() {
    FILE *archivo = fopen("vehiculos.txt", "a");
    Vehiculo v;

    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    v.id = generarId();
    v.disponible = 1;

    leerTexto("Marca: ", v.marca, MAX_TEXTO);
    leerTexto("Modelo: ", v.modelo, MAX_TEXTO);
    leerTexto("Tipo camioneta/auto/SUV: ", v.tipo, MAX_TEXTO);
    leerTexto("Estado nuevo/usado: ", v.estado, MAX_TEXTO);
    v.precio = leerFloat("Precio: ");

    fprintf(archivo, "%d %s %s %s %s %.2f %d\n",
            v.id, v.marca, v.modelo, v.tipo,
            v.estado, v.precio, v.disponible);

    fclose(archivo);

    printf("Vehiculo agregado correctamente.\n");
}

void listarVehiculos() {
    FILE *archivo = fopen("vehiculos.txt", "r");
    Vehiculo v;
    int hayDatos = 0;

    if (archivo == NULL) {
        printf("No hay vehiculos registrados.\n");
        return;
    }

    printf("\n--- LISTA DE VEHICULOS ---\n");

    while (fscanf(archivo, "%d %s %s %s %s %f %d",
                  &v.id, v.marca, v.modelo, v.tipo,
                  v.estado, &v.precio, &v.disponible) == 7) {

        hayDatos = 1;

        printf("\nID: %d", v.id);
        printf("\nMarca: %s", v.marca);
        printf("\nModelo: %s", v.modelo);
        printf("\nTipo: %s", v.tipo);
        printf("\nEstado: %s", v.estado);
        printf("\nPrecio: %.2f", v.precio);
        printf("\nDisponible: %s\n", v.disponible == 1 ? "Si" : "No");
    }

    if (hayDatos == 0) {
        printf("No hay vehiculos registrados.\n");
    }

    fclose(archivo);
}

void buscarVehiculos() {
    FILE *archivo = fopen("vehiculos.txt", "r");
    Vehiculo v;

    char marca[MAX_TEXTO];
    char tipo[MAX_TEXTO];
    char estado[MAX_TEXTO];
    float presupuesto;
    int encontrados = 0;

    if (archivo == NULL) {
        printf("No hay vehiculos registrados.\n");
        return;
    }

    leerTexto("Marca buscada: ", marca, MAX_TEXTO);
    leerTexto("Tipo buscado: ", tipo, MAX_TEXTO);
    leerTexto("Estado buscado: ", estado, MAX_TEXTO);
    presupuesto = leerFloat("Presupuesto maximo: ");

    printf("\n--- RESULTADOS DE BUSQUEDA ---\n");

    while (fscanf(archivo, "%d %s %s %s %s %f %d",
                  &v.id, v.marca, v.modelo, v.tipo,
                  v.estado, &v.precio, &v.disponible) == 7) {

        if (strcmp(v.marca, marca) == 0 &&
            strcmp(v.tipo, tipo) == 0 &&
            strcmp(v.estado, estado) == 0 &&
            v.precio <= presupuesto &&
            v.disponible == 1) {

            printf("\nID: %d", v.id);
            printf("\nMarca: %s", v.marca);
            printf("\nModelo: %s", v.modelo);
            printf("\nTipo: %s", v.tipo);
            printf("\nEstado: %s", v.estado);
            printf("\nPrecio: %.2f\n", v.precio);

            encontrados++;
        }
    }

    if (encontrados == 0) {
        printf("No se encontraron vehiculos con esas caracteristicas.\n");
    }

    fclose(archivo);
}

void registrarVenta() {
    FILE *archivo = fopen("vehiculos.txt", "r");
    FILE *temporal = fopen("temporal.txt", "w");
    FILE *ventas = fopen("ventas.txt", "a");

    Vehiculo v;
    Cliente c;
    int idBuscado;
    int encontrado = 0;

    if (archivo == NULL || temporal == NULL || ventas == NULL) {
        printf("Error al abrir archivos.\n");
        return;
    }

    idBuscado = leerEntero("Ingrese ID del vehiculo a vender: ");

    while (fscanf(archivo, "%d %s %s %s %s %f %d",
                  &v.id, v.marca, v.modelo, v.tipo,
                  v.estado, &v.precio, &v.disponible) == 7) {

        if (v.id == idBuscado && v.disponible == 1) {
            encontrado = 1;
            v.disponible = 0;

            leerTexto("Nombre del cliente: ", c.nombre, MAX_TEXTO);
            c.edad = leerEntero("Edad del cliente: ");

            while (c.edad <= 0) {
                printf("Error: edad invalida.\n");
                c.edad = leerEntero("Edad del cliente: ");
            }

            c.id = idBuscado;

            fprintf(ventas, "%d %s %d %.2f\n",
                    c.id, c.nombre, c.edad, v.precio);

            printf("Venta registrada correctamente.\n");
        }

        fprintf(temporal, "%d %s %s %s %s %.2f %d\n",
                v.id, v.marca, v.modelo, v.tipo,
                v.estado, v.precio, v.disponible);
    }

    if (encontrado == 0) {
        printf("Vehiculo no encontrado o no disponible.\n");
    }

    fclose(archivo);
    fclose(temporal);
    fclose(ventas);

    remove("vehiculos.txt");
    rename("temporal.txt", "vehiculos.txt");
}