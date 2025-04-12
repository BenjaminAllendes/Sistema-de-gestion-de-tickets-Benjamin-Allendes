# Sistema de gestión de tickets de soporte técnico

Este sistema permite a los usuarios gestionar solicitudes de ayuda mediante tickets. Los usuarios pueden registrar nuevos tickets, asignar y cambiar prioridades, ver la lista de tickets pendientes, procesar el ticket de mayor prioridad, y buscar un ticket por su ID y mostrar su informacion. 

## Cómo compilar y ejecutar

Este sistema ha sido desarrollado en lenguaje C y puede ejecutarse fácilmente utilizando **Visual Studio Code** junto con una extensión para C/C++, como **C/C++ Extension Pack de Microsoft**. Para comenzar a trabajar con el sistema en tu equipo local, sigue estos pasos:

## Requisitos previos:

- Tener instalado Visual Studio Code.
- Instalar la extensión **C/C++** (Microsoft).
- Tener instalado un compilador de C (como gcc). Si estás en Windows, se recomienda instalar MinGW o utilizar el entorno WSL.

## Pasos para compilar y ejecutar:

1. Descarga y descomprime el archivo `.zip` en una carpeta de tu elección.
2. Abre el proyecto en Visual Studio Code
    -Inicia Visual Studio Code.
    -Selecciona `Archivo > Abrir carpeta...` y elige la carpeta donde descomprimiste el proyecto.
3. Compila el código
    - Abre el archivo principal (`gestion-tickets.c`).
    - Abre la terminal integrada (`Terminal > Nueva terminal`).
    - En la terminal, compila el programa con el siguiente comando:
    ```
    gcc *.c -o gestion-tickets
    ```
4. Ejecuta el programa
    - Una vez compilado, puedes ejecutar la aplicación con:`
    ```
    ./gestion_pacientes
    ```
## Funcionalidades

### Funcionando correctamente:
- Registrar tickets con el ID y el problema del usuario, asignandole una prioridad baja y guardando la hora de registro.
- Asignar o modificar la prioridad de tickets registrados.
- Ver la lista de tickets, ordenada por prioridad y hora de registro.
- Procesar el siguiente ticket, respetando el orden de la prioridad.
- Buscar ticket por ID y mostrar su informacion (hora de registro, problema, prioridad).

### Problemas conocidos:
- Al ingresar un ticket tiene que ser estrictamente de 100 caracters como maximo, y su repectivo  problema de 1000 caracteres como maximo. Si no, el programa no va a poder guardar esta informacion correctamente y tendra un error de segmentacion. 

### A mejorar:
- Añadir una manera para evitar añadir IDs y tickets de mayor tamaño que el maximo permitido.
- Implementar una interfaz mas amigable.
- Permitir la edicion de la informacion de tickets.

## Ejemplo de uso
### Paso 1: Registrar un nuevo ticket
Se registra un nuevo ticket, escribiendo el problema a solucionar:
```
Agregar lo que pasa en la consola
```
El sistema registra el ticket con el ID AGREGAR ID con el problema ingresado, se guarda la hora actual de registo y su prioridad es baja.

### Paso 2: Asignar prioridad a un ticket
Tras ver el problema del ticket, un administrador o moderador decide que el ticket requiere atencion prioritaria.
```
CONSOLA
```

#### Paso 3: Ver la lista de tickets
El usuario revisa la lista de espera para ver todos los pacientes y sus prioridades.
```
CONSOLA
```
La lista muestra el ticket ingresado anteriormente, indicando su prioridad, su hora de registro y que es el siguiente ticket en ser atendido

### Paso 4: Atender el siguiente ticket
El ticket con ID IIIIII es procesado y se revisa su solicitud de ayuda.
```
CONSOLA
```
El sistema muestra la informacion guardada y lo elimina del sistema.

### Paso 5: Buscar ticket por ID
mas tarde ewfnhwuhfeuwigfheryiughvuyhuiheriug