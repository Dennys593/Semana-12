# Plan de mejoras para el proyecto SGIC - RUEDAS DE ORO

## 1. Objetivo
Definir los cambios necesarios para corregir y mejorar el proyecto actual de gestión de vehículos y ventas, tomando en cuenta los archivos revisados: `main.c`, `funciones.c`, `funciones.h` y `vehiculos.txt`.

## 2. Estado actual
- `main.c` contiene el menú principal y llama a las funciones del sistema.
- `funciones.c` implementa la lectura de datos, validación de entrada, manejo de archivos y operaciones de registro/listado/búsqueda/venta.
- `funciones.h` solo tiene parte de las firmas de funciones, falta declarar varias funciones usadas en `funciones.c`.
- `vehiculos.txt` contiene datos de ejemplo con formato tabulado.

## 3. Problemas y mejoras identificadas
1. Prototipos incompletos en `funciones.h`.
2. Validación de tipo de vehículo inconsistente: el mensaje de error menciona "auto" pero la validación solo acepta "sedan".
3. Manejo de espacios en marca/modelo: se exige sin espacios, pero el dato de ejemplo `Land_cruiser` usa guión bajo. Esto está bien, pero debe documentarse o permitirse marcas con espacios.
4. Lectura de archivos con `fscanf` y campos sin espacios es frágil; no maneja valores con espacios ni encabezados complejos.
5. La función `generarId` reabre y lee `vehiculos.txt`; si el archivo no existe devuelve `1`, quizá debería devolver `1` cuando el archivo está vacío.
6. El registro de venta cambia el archivo de vehículos usando un archivo temporal, pero no elimina `temporal.txt` en caso de error parcial.
7. `buscarVehiculos()` obliga a ingresar marca, tipo y estado exactos; podría mejorarse con búsqueda flexible parcial o mayúsculas/minúsculas.
8. No hay un listado de ventas ni comprobación de duplicados en ventas.

## 4. Plan de acciones
1. Completar los prototipos faltantes en `funciones.h`.
2. Ajustar la validación de tipo para aceptar `sedan`, `camioneta`, `SUV` y `suv`, y actualizar el mensaje de error para que sea coherente.
3. Añadir validación de texto y/o permitir espacios en marca y modelo si es necesario.
4. Mejorar lectura/escritura de archivos usando `fgets` + `sscanf` o separadores claros para evitar problemas con espacios y encabezados.
5. Añadir manejo seguro cuando `vehiculos.txt` o `ventas.txt` no existen.
6. Agregar una opción de menú para listar ventas o mostrar historial de ventas.
7. Probar compilación con `gcc -Wall -Wextra` y ejecutar el programa con entradas de ejemplo.
8. Documentar en `plan.md` los cambios realizados y dejar comentarios claros en el código.

## 5. Prioridades
- Alta: firmar correctamente las funciones en el header, corregir validaciones inconsistentes, asegurar que el archivo `vehiculos.txt` se manipula sin perder datos.
- Media: mejorar la búsqueda y el registro de ventas, agregar listado de ventas.
- Baja: refactorizar para soportar marcas/modelos con espacios y mejorar la experiencia de usuario.

## 6. Próximos pasos
1. Actualizar `funciones.h` con todos los prototipos.
2. Corregir `funciones.c` según los puntos anteriores.
3. Compilar y corregir advertencias/errores.
4. Probar manualmente las opciones del menú.
5. Verificar que `vehiculos.txt` conserva los datos y que `ventas.txt` se genera correctamente.
