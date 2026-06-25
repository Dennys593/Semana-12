#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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

void leerTextoSinEspacios(char mensaje[], char texto[], int tam) {
    int valido, i;
    do {
        leerTexto(mensaje, texto, tam);
        valido = 1;
        for (i = 0; texto[i] != '\0'; i++) {
            if (texto[i] == ' ') {
                printf("Error: no use espacios. Use guion bajo, ej: Land_Rover\n");
                valido = 0;
                break;
            }
        }
    } while (valido == 0);
}

int leerAnio() {
    int anio;
    char mensaje[60];
    sprintf(mensaje, "Anio del vehiculo (%d-%d): ", ANIO_MIN, ANIO_MAX);

    do {
        anio = leerEntero(mensaje);
        if (anio < ANIO_MIN || anio > ANIO_MAX) {
            printf("Error: ingrese un anio entre %d y %d.\n", ANIO_MIN, ANIO_MAX);
        }
    } while (anio < ANIO_MIN || anio > ANIO_MAX);

    return anio;
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
    if (strcmp(tipo, "sedan") == 0 ||
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
        leerTexto("Tipo camioneta/sedan/SUV: ", tipo, MAX_TEXTO);

        if (validarTipo(tipo) == 0) {
            printf("Error: tipo invalido. Ingrese solo camioneta, sedan o SUV.\n");
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

void escribirEncabezadoVehiculos(FILE *archivo) {
    fprintf(archivo, "%-5s %-15s %-15s %-6s %-12s %-8s %-12s %-5s\n",
            "ID", "MARCA", "MODELO", "ANIO", "TIPO", "ESTADO", "PRECIO", "DISP");
}

void escribirVehiculo(FILE *archivo, Vehiculo v) {
    fprintf(archivo, "%-5d %-15s %-15s %-6d %-12s %-8s %-12.2f %-5d\n",
            v.id, v.marca, v.modelo, v.anio, v.tipo,
            v.estado, v.precio, v.disponible);
}

void escribirEncabezadoVentas(FILE *archivo) {
    fprintf(archivo, "%-5s %-15s %-12s %-5s %-10s %-15s %-12s %-10s %-14s %-10s\n",
            "ID", "CLIENTE", "CEDULA", "EDAD", "COD_VEND", "VENDEDOR",
            "PRECIO", "IVA", "PAGO_CLIENTE", "COMISION");
}

void escribirVenta(FILE *archivo, Cliente c, Vendedor vend, float precioBase) {
    float iva = precioBase * IVA;
    float pagoCliente = precioBase + iva;
    float comision = precioBase * COMISION;

    fprintf(archivo, "%-5d %-15s %-12s %-5d %-10s %-15s %-12.2f %-10.2f %-14.2f %-10.2f\n",
            c.id, c.nombre, c.cedula, c.edad, vend.codigo, vend.nombre,
            precioBase, iva, pagoCliente, comision);
}

int generarId() {
    FILE *archivo = fopen("vehiculos.txt", "r");
    Vehiculo v;
    int ultimoId = 0;
    char encabezado[200];

    if (archivo == NULL) {
        return 1;
    }

    fgets(encabezado, 200, archivo);

    while (fscanf(archivo, "%d %s %s %d %s %s %f %d",
                  &v.id, v.marca, v.modelo, &v.anio, v.tipo,
                  v.estado, &v.precio, &v.disponible) == 8) {
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

    fseek(archivo, 0, SEEK_END);

    if (ftell(archivo) == 0) {
        escribirEncabezadoVehiculos(archivo);
    }

    v.id = generarId();
    v.disponible = 1;

    leerTextoSinEspacios("Marca: ", v.marca, MAX_TEXTO);
    leerTextoSinEspacios("Modelo: ", v.modelo, MAX_TEXTO);
    v.anio = leerAnio();
    leerTipo(v.tipo);
    leerEstado(v.estado);
    v.precio = leerFloat("Precio (sin puntos ni comas, ej: 120000): ");

    escribirVehiculo(archivo, v);

    fclose(archivo);

    printf("Vehiculo agregado correctamente.\n");
}

void listarVehiculos() {
    FILE *archivo = fopen("vehiculos.txt", "r");
    Vehiculo v;
    int hayDatos = 0;
    char encabezado[200];

    if (archivo == NULL) {
        printf("No hay vehiculos registrados.\n");
        return;
    }

    fgets(encabezado, 200, archivo);

    printf("\n--- LISTA DE VEHICULOS ---\n");
    printf("%-4s %-12s %-12s %-6s %-10s %-8s %-12s %-6s\n",
           "ID", "Marca", "Modelo", "Anio", "Tipo", "Estado", "Precio", "Disp");

    while (fscanf(archivo, "%d %s %s %d %s %s %f %d",
                  &v.id, v.marca, v.modelo, &v.anio, v.tipo,
                  v.estado, &v.precio, &v.disponible) == 8) {

        hayDatos = 1;

        printf("%-4d %-12s %-12s %-6d %-10s %-8s %-12.2f %-6s\n",
               v.id, v.marca, v.modelo, v.anio, v.tipo, v.estado, v.precio,
               v.disponible == 1 ? "Si" : "No");
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
    char encabezado[200];
    float presupuesto;
    int encontrados = 0;

    if (archivo == NULL) {
        printf("No hay vehiculos registrados.\n");
        return;
    }

    fgets(encabezado, 200, archivo);

    leerTexto("Marca buscada: ", marca, MAX_TEXTO);
    leerTipo(tipo);
    leerEstado(estado);
    presupuesto = leerFloat("Presupuesto maximo: ");

    while (fscanf(archivo, "%d %s %s %d %s %s %f %d",
                  &v.id, v.marca, v.modelo, &v.anio, v.tipo,
                  v.estado, &v.precio, &v.disponible) == 8) {

        if (strcmp(v.marca, marca) == 0 &&
            strcmp(v.tipo, tipo) == 0 &&
            strcmp(v.estado, estado) == 0 &&
            v.precio <= presupuesto &&
            v.disponible == 1) {

            if (encontrados == 0) {
                printf("\n--- RESULTADOS DE BUSQUEDA ---\n");
                printf("%-4s %-12s %-12s %-6s %-10s %-8s %-12s\n",
                       "ID", "Marca", "Modelo", "Anio", "Tipo", "Estado", "Precio");
            }

            printf("%-4d %-12s %-12s %-6d %-10s %-8s %-12.2f\n",
                   v.id, v.marca, v.modelo, v.anio, v.tipo, v.estado, v.precio);

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
    Vendedor vend;
    int idBuscado;
    int encontrado = 0;
    char encabezado[200];

    if (archivo == NULL || temporal == NULL || ventas == NULL) {
        printf("Error al abrir archivos.\n");

        if (archivo != NULL) fclose(archivo);
        if (temporal != NULL) fclose(temporal);
        if (ventas != NULL) fclose(ventas);

        return;
    }

    fgets(encabezado, 200, archivo);
    escribirEncabezadoVehiculos(temporal);

    fseek(ventas, 0, SEEK_END);

    if (ftell(ventas) == 0) {
        escribirEncabezadoVentas(ventas);
    }

    idBuscado = leerEntero("Ingrese ID del vehiculo a vender: ");

    while (fscanf(archivo, "%d %s %s %d %s %s %f %d",
                  &v.id, v.marca, v.modelo, &v.anio, v.tipo,
                  v.estado, &v.precio, &v.disponible) == 8) {

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

            leerTextoSinEspacios("Codigo del vendedor (ej: V001): ", vend.codigo, MAX_TEXTO);
            leerTextoSinEspacios("Nombre del vendedor (sin espacios, ej: Maria_Lopez): ", vend.nombre, MAX_TEXTO);

            c.id = idBuscado;

            escribirVenta(ventas, c, vend, v.precio);

            float iva = v.precio * IVA;
            float pagoCliente = v.precio + iva;
            float comision = v.precio * COMISION;

            printf("\nVenta registrada correctamente.\n");
            printf("=====================================\n");
            printf("Vehiculo:          %s %s %d\n", v.marca, v.modelo, v.anio);
            printf("Cliente:           %s (CI: %s)\n", c.nombre, c.cedula);
            printf("Vendedor:          %s (%s)\n", vend.nombre, vend.codigo);
            printf("-------------------------------------\n");
            printf("Precio base:       %.2f\n", v.precio);
            printf("IVA (%.0f%%):         %.2f\n", IVA * 100, iva);
            printf("PAGO DEL CLIENTE:  %.2f\n", pagoCliente);
            printf("Comision vendedor: %.2f (%.0f%%)\n", comision, COMISION * 100);
            printf("=====================================\n");
        }

        escribirVehiculo(temporal, v);
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

void reporteVentas() {
    FILE *archivo = fopen("ventas.txt", "r");
    char encabezado[300];
    char linea[300];
    int hayDatos = 0;
    float totalRecaudado = 0;
    float totalComisiones = 0;

    if (archivo == NULL) {
        printf("No hay ventas registradas.\n");
        return;
    }

    fgets(encabezado, sizeof(encabezado), archivo);

    while (fgets(linea, sizeof(linea), archivo) != NULL) {
        char copia[300];
        char *ultimos[4] = {NULL, NULL, NULL, NULL};
        char *token;

        if (linea[0] == '\n') {
            continue;
        }

        if (hayDatos == 0) {
            printf("\n--- REPORTE DE VENTAS ---\n");
            printf("%s", encabezado);
        }

        hayDatos = 1;
        printf("%s", linea);

        /* Los ultimos 4 numeros de la linea son: PRECIO, IVA, PAGO_CLIENTE, COMISION.
           Tomamos los ultimos 4 tokens para que los nombres con espacios no estorben. */
        strcpy(copia, linea);
        token = strtok(copia, " \t\n");
        while (token != NULL) {
            ultimos[0] = ultimos[1];
            ultimos[1] = ultimos[2];
            ultimos[2] = ultimos[3];
            ultimos[3] = token;
            token = strtok(NULL, " \t\n");
        }

        if (ultimos[2] != NULL && ultimos[3] != NULL) {
            totalRecaudado += atof(ultimos[2]);
            totalComisiones += atof(ultimos[3]);
        }
    }

    if (hayDatos == 0) {
        printf("No hay ventas registradas.\n");
    } else {
        printf("-------------------------------------------------------\n");
        printf("Total recaudado (pago de clientes):  %.2f\n", totalRecaudado);
        printf("Total comisiones a vendedores:       %.2f\n", totalComisiones);
    }

    fclose(archivo);
}

typedef struct {
    char codigo[MAX_TEXTO];
    char nombre[MAX_TEXTO];
    int ventas;
    float totalVendido;
    float totalComision;
} ResumenVendedor;

void reporteComisiones() {
    FILE *archivo = fopen("ventas.txt", "r");
    char encabezado[300];
    char linea[300];
    ResumenVendedor vendedores[100];
    int numVendedores = 0;
    int i, hayDatos = 0;

    if (archivo == NULL) {
        printf("No hay ventas registradas.\n");
        return;
    }

    fgets(encabezado, sizeof(encabezado), archivo);

    while (fgets(linea, sizeof(linea), archivo) != NULL) {
        char copia[300];
        char *tok[6] = {NULL, NULL, NULL, NULL, NULL, NULL};
        char *token;
        int k, encontrado;
        float precio, comision;

        if (linea[0] == '\n') {
            continue;
        }

        /* Tomamos los ultimos 6 tokens de la linea:
           COD_VEND, VENDEDOR, PRECIO, IVA, PAGO_CLIENTE, COMISION.
           (Por eso el nombre del vendedor no debe llevar espacios.) */
        strcpy(copia, linea);
        token = strtok(copia, " \t\n");
        while (token != NULL) {
            for (k = 0; k < 5; k++) {
                tok[k] = tok[k + 1];
            }
            tok[5] = token;
            token = strtok(NULL, " \t\n");
        }

        if (tok[0] == NULL || tok[5] == NULL) {
            continue;
        }

        precio = atof(tok[2]);
        comision = atof(tok[5]);
        hayDatos = 1;

        encontrado = -1;
        for (i = 0; i < numVendedores; i++) {
            if (strcmp(vendedores[i].codigo, tok[0]) == 0) {
                encontrado = i;
                break;
            }
        }

        if (encontrado == -1 && numVendedores < 100) {
            encontrado = numVendedores;
            strcpy(vendedores[numVendedores].codigo, tok[0]);
            strcpy(vendedores[numVendedores].nombre, tok[1]);
            vendedores[numVendedores].ventas = 0;
            vendedores[numVendedores].totalVendido = 0;
            vendedores[numVendedores].totalComision = 0;
            numVendedores++;
        }

        if (encontrado >= 0) {
            vendedores[encontrado].ventas++;
            vendedores[encontrado].totalVendido += precio;
            vendedores[encontrado].totalComision += comision;
        }
    }

    fclose(archivo);

    if (hayDatos == 0) {
        printf("No hay ventas registradas.\n");
        return;
    }

    printf("\n--- COMISIONES POR VENDEDOR ---\n");
    printf("%-10s %-15s %-8s %-15s %-15s\n",
           "CODIGO", "VENDEDOR", "VENTAS", "TOTAL_VEND", "TOTAL_COMIS");

    for (i = 0; i < numVendedores; i++) {
        printf("%-10s %-15s %-8d %-15.2f %-15.2f\n",
               vendedores[i].codigo, vendedores[i].nombre,
               vendedores[i].ventas, vendedores[i].totalVendido,
               vendedores[i].totalComision);
    }
}