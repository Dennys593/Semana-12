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

int validarCedula(char cedula[]) {
    int i;
    int suma = 0;
    int digitoVerificador;
    int provincia;

    if (strlen(cedula) != 10) {
        return 0;
    }

    for (i = 0; i < 10; i++) {
        if (cedula[i] < '0' || cedula[i] > '9') {
            return 0;
        }
    }

    provincia = (cedula[0] - '0') * 10 + (cedula[1] - '0');

    if (provincia < 1 || provincia > 24) {
        return 0;
    }

    if (cedula[2] >= '6') {
        return 0;
    }

    for (i = 0; i < 9; i++) {
        int digito = cedula[i] - '0';

        if (i % 2 == 0) {
            digito *= 2;
            if (digito > 9) {
                digito -= 9;
            }
        }

        suma += digito;
    }

    digitoVerificador = 10 - (suma % 10);

    if (digitoVerificador == 10) {
        digitoVerificador = 0;
    }

    return digitoVerificador == (cedula[9] - '0');
}

void leerCedula(char mensaje[], char cedula[], int tam) {
    do {
        leerTexto(mensaje, cedula, tam);

        if (validarCedula(cedula) == 0) {
            printf("Error: cedula invalida. Ingrese una cedula ecuatoriana valida.\n");
        }

    } while (validarCedula(cedula) == 0);
}

int validarTipo(char tipo[]) {
    if (strcmp(tipo, "auto") == 0 ||
        strcmp(tipo, "camioneta") == 0 ||
        strcmp(tipo, "SUV") == 0 ||
        strcmp(tipo, "suv") == 0) {
        return 1;
    }

    return 0;
}

int validarEstado(char estado[]) {
    if (strcmp(estado, "nuevo") == 0 ||
        strcmp(estado, "usado") == 0) {
        return 1;
    }

    return 0;
}

void leerTipo(char tipo[]) {
    do {
        leerTexto("Tipo camioneta/auto/SUV: ", tipo, MAX_TEXTO);

        if (validarTipo(tipo) == 0) {
            printf("Error: tipo invalido. Ingrese solo camioneta, auto o SUV.\n");
        }

    } while (validarTipo(tipo) == 0);
}

void leerEstado(char estado[]) {
    do {
        leerTexto("Estado nuevo/usado: ", estado, MAX_TEXTO);

        if (validarEstado(estado) == 0) {
            printf("Error: estado invalido. Ingrese solo nuevo o usado.\n");
        }

    } while (validarEstado(estado) == 0);
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
    leerTipo(v.tipo);
    leerEstado(v.estado);
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
    leerTipo(tipo);
    leerEstado(estado);
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

        if (archivo != NULL) fclose(archivo);
        if (temporal != NULL) fclose(temporal);
        if (ventas != NULL) fclose(ventas);

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
            leerCedula("Cedula del cliente: ", c.cedula, MAX_TEXTO);
            c.edad = leerEntero("Edad del cliente: ");

            while (c.edad <= 0) {
                printf("Error: edad invalida.\n");
                c.edad = leerEntero("Edad del cliente: ");
            }

            c.id = idBuscado;

                fprintf(ventas, "%d %s %s %d %.2f\n",
                    c.id, c.nombre, c.cedula, c.edad, v.precio);

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