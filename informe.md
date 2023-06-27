# Laboratorio 4 : BigBrother FS
## Sistemas Operativos - FAMAF - UNC

### Grupo 17 
- Fernando Alvarado, fernando.alvarado@mi.unc.edu.ar
- Gonzalo Martyn, gonzalo.martyn@mi.unc.edu.ar
- Ivan Ponzio, ivan.ponzio@mi.unc.edu.ar
- Armando Carral, armando.carral@mi.unc.edu.ar

# Preguntas
- Cuando se ejecuta el main con la opción -d, ¿qué se está mostrando en la pantalla?
  -

El flag -d activa el modo debug de la libreria fuse, mostrando informacion del file system montado. Algunas cosas que se muestran son:
* Llamadas a funciones.
* Nodos involucrados.
* Modificaciones del file system en tiempo real.
* etc.

- ¿Hay alguna manera de saber el nombre del archivo guardado en el cluster 157?
  -

En general, el nombre de un archivo no se encuentra en el cluster donde están sus datos, sino en la entrada de directorio del padre.

Se podria hacer algo hardcoreado tratando de levantar la imagen con nuestra implementación de fuse. Dependiendo de si el archivo empieza o no en el cluster en cuestion, se podría buscar en todos los fat_file's si el cluster coincide con el start_cluster de alguno (esto suponiendo que el sistema esta montado con el módulo que implementamos y tenemos acceso a los TAD's). Otra opción es (si tenemos acceso a la FAT) podemos tratar de encontrar y seguir la cadena de clusters que terminan en el cluster en cuestion, con la idea llegar al start_cluster de algún archivo conocido. 


- ¿Dónde se guardan las entradas de directorio? ¿Cuántos archivos puede tener adentro un directorio en FAT32?
  -
Las entradas de directorios se almacenan el cluster de datos del directorio padre. Cada entrada de directorio tiene 32 bytes. En un cluster de 512 bytes entran 16 entradas de directorio.
La cantidad máxima de archivos dentro de un directorio es de 65536 (2**16).

- Cuando se ejecuta el comando como ls -l, el sistema operativo, ¿llama a algún programa de usuario? ¿A alguna llamada al sistema? ¿Cómo se conecta esto con FUSE? ¿Qué funciones de su código se ejecutan finalmente?  
  -
Si, ls es un programa de usuario, la implementación de las funciones de fat-fuse también son un programa que corre en espacio de usuario. También se realizan systems-calls, la principal de ls sería alguna especie de read, necesaria para listar el contenido de un directorio. 

Cuando se realiza una llamada al sistema como *readdir* en un filesystem montado con fuse, se trapea al kernel, el VFS identifica que el volumen sobre el que se quiere realizar la operación está montado con fuse y le pasa el control sobre la llamada al módulo. En el módulo están implementadas las funciones equivalentes a syscalls. Estas realizan la tarea (en user space), devuelven el resultado al kernel a través de la librería fuse (que es parte del VFS) y del kernel se hace un return from trap para volver a espacio de usuario como después de correr una syscall normal.


- ¿Por qué tienen que escribir las entradas de directorio manualmente pero no tienen que guardar la tabla FAT cada vez que la modifican?

Porque la tabla FAT está mapeada en memoria (a través de una llamada a mmap en fat_volume.c), esto nos permite operar sobre la misma sin necesidad de trasladar los cambios inmediatamente al disco.


- Para los sistemas de archivos FAT32, la tabla FAT, ¿siempre tiene el mismo tamaño? En caso de que sí, ¿qué tamaño tiene?
  -
No, va depender del tamaño de la imagen que se esté creando. En la tabla fat se almacenan 4 bytes por cada cluster de datos, por lo que sería un desperdicio de espacio guardar una tabla excesivamente mas grande de lo necesaria.

