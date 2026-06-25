#ifndef FUNCIONES_H
#define FUNCIONES_H

#define MAX_TEXTO 50

/* Tarifas: cambia estos valores si tu profesor pide otros porcentajes */
#define IVA 0.15        /* IVA del 15% (Ecuador) */
#define COMISION 0.05   /* Comision del vendedor: 5% sobre el precio base */

#define ANIO_MIN 1900
#define ANIO_MAX 2027

typedef struct {
    int id;
    char marca[MAX_TEXTO];
    char modelo[MAX_TEXTO];
    int anio;
    char tipo[MAX_TEXTO];
    char estado[MAX_TEXTO];
    float precio;
    int disponible;
} Vehiculo;

typedef struct {
    int id;
    char nombre[MAX_TEXTO];
    char cedula[MAX_TEXTO];
    int edad;
} Cliente;

typedef struct {
    char codigo[MAX_TEXTO];
    char nombre[MAX_TEXTO];
} Vendedor;

void limpiarBuffer();
int leerEntero(char mensaje[]);
float leerFloat(char mensaje[]);
void leerTexto(char mensaje[], char texto[], int tam);
void leerTextoSinEspacios(char mensaje[], char texto[], int tam);
int validarCedula(char cedula[]);
void leerCedula(char mensaje[], char cedula[], int tam);
int leerAnio();

void agregarVehiculo();
void listarVehiculos();
void buscarVehiculos();
void registrarVenta();
void reporteVentas();
void reporteComisiones();

#endif