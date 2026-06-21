#define FUNCIONES_H

#define MAX_TEXTO 50

typedef struct {
    int id;
    char marca[MAX_TEXTO];
    char modelo[MAX_TEXTO];
    char tipo[MAX_TEXTO];
    char estado[MAX_TEXTO];
    float precio;
    int disponible;
} Vehiculo;

typedef struct {
    int id;
    char nombre[MAX_TEXTO];
    int edad;
} Cliente;

void limpiarBuffer();
int leerEntero(char mensaje[]);
float leerFloat(char mensaje[]);
void leerTexto(char mensaje[], char texto[], int tam);

void agregarVehiculo();
void listarVehiculos();
void buscarVehiculos();
void registrarVenta();
