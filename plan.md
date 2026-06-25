# Planificación del Proyecto

## Objetivo

Desarrollar un sistema en lenguaje C para gestionar el inventario de vehículos de la concesionaria Ruedas de Oro y registrar ventas con validaciones básicas de entrada.

## Funcionalidades

- Agregar vehículos.
- Listar vehículos.
- Buscar vehículos.
- Registrar ventas.
- Validar la cédula del cliente al momento de registrar una venta.

## Validaciones

- Validar que solo se ingresen números donde corresponda.
- No permitir campos vacíos.
- Validar que el precio sea mayor a 0.
- Validar que el tipo del vehículo sea Auto, Camioneta o SUV.
- Validar que el estado sea Nuevo o Usado.
- Validar que la cédula tenga 10 dígitos y sea válida.
- Validar que la edad del cliente sea mayor a 0.

## Archivos

- main.c
- funciones.c
- funciones.h
- vehiculos.txt
- ventas.txt

## Desarrollo

- Revisar la estructura de datos para vehículos y clientes.
- Crear el menú principal y las opciones del sistema.
- Implementar el ingreso y validación de datos.
- Guardar vehículos y ventas en archivos de texto.
- Verificar búsquedas y registro de ventas.
- Realizar pruebas con datos válidos e inválidos.
- Corregir errores y mejorar mensajes de salida.

## Secuencia de Trabajo

1. Crear el menú principal.
2. Registrar vehículos con validaciones.
3. Listar vehículos almacenados.
4. Buscar vehículos por criterios del cliente.
5. Registrar ventas y desactivar disponibilidad.
6. Validar cédula, edad y demás campos de cliente.
7. Probar el sistema completo con archivos.

## Resultado

El programa permite administrar vehículos, realizar búsquedas según las preferencias del cliente y registrar ventas, manteniendo la información almacenada en archivos y aplicando validaciones de entrada.

## Cambios a implementar

- Archivos a modificar: `funciones.c` (principalmente) y opcionalmente `funciones.h` si se añaden helpers.
- En `listarVehiculos()`: reemplazar los múltiples `printf` por una cabecera de tabla y una línea formateada por vehículo. Ejemplo:

	printf("\n--- LISTA DE VEHICULOS ---\n");
	printf("%-4s %-12s %-12s %-10s %-8s %-12s %-10s\n", "ID", "Marca", "Modelo", "Tipo", "Estado", "Precio", "Disponible");
	printf("%-4d %-12s %-12s %-10s %-8s %-12.2f %-10s\n",
				 v.id, v.marca, v.modelo, v.tipo, v.estado, v.precio,
				 v.disponible == 1 ? "Si" : "No");

- En `buscarVehiculos()`: imprimir una cabecera similar (solo con las columnas que desees mostrar) y usar el mismo formato para cada resultado encontrado. Imprime la cabecera solo si se encuentra al menos un vehículo.

- Notas y pruebas:
	- Ajusta los anchos (`%-12s`, `%-10s`, etc.) según los datos reales para evitar recortes.
	- Mantener las validaciones actuales; solo cambia la forma de salida.
	- Compilar y ejecutar para verificar salida:

```bash
gcc main.c funciones.c -o programa
.\programa
```

Estos cambios mejoran la legibilidad al mostrar la lista y los resultados de búsqueda en formato tabular.