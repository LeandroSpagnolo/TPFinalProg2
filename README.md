# Trabajo Final de Programación 2
### Leandro Spagnolo

*Breve Descripción de lo solicitado*

En este proyecto se solicita analizar una serie de textos escritos por una misma persona. Cada texto está contenido en un archivo diferente, todos agrupados dentro de una carpeta con el nombre del autor. El objetivo es utilizar la información obtenida de estos textos para completar frases escritas por la misma persona en un proceso posterior.

*Implementación*

La implementación consta de dos programas: uno en C y otro en Python. El programa en C invoca internamente al segundo para aprovechar su funcionalidad. De esta manera, para ejecutar el trabajo, solo es necesario ejecutar el programa en C.

*Requisitos*

- Python 3
- Compilador de C

## Programa en C

En la sección del programa ejecutado en C, opté por primero obtener los nombres de los textos del artista seleccionado. Luego, procesarlos uno por uno, escribiendo cada carácter correctamente en el archivo correspondiente en la carpeta "Entradas".

Una de las partes que me resultó más desafiante fue al procesar los textos, especialmente para asegurarme de que las oraciones terminaran en los puntos y los saltos de línea funcionaran correctamente. La elección de utilizar "fgetc" fue crucial, recorriendo los textos caracter por caracter, facilitándome la creación de oraciones al identificar correctamente los puntos finales.

En cuanto a la estandarización de los textos, el descubrimiento de la función "isalnum" me permitió filtrar fácilmente todos los caracteres alfanuméricos y evitar los signos de puntuación. Mantener el carácter anterior fue útil para reducir varios espacios acumulados a uno, facilitando el formateo del texto.

Finalmente, destaco la función "system", mencionada en el enunciado del TP, que permitió obtener fácilmente los nombres de los directorios para determinar la presencia del artista y sus textos.

## Programa en Python

En el programa en Python, la parte más desafiante fue predecir las palabras que cada artista utilizaría en los espacios en blanco. La solución propuesta fue la siguiente:

Cuando se encuentra un espacio en blanco, se analiza la palabra anterior. Si esta palabra está en los textos, se elige la siguiente palabra más común, la que tiene un mayor contador.

En caso de que la palabra anterior no esté en los textos como referencia, se procede con la palabra siguiente y se realiza la misma selección con la palabra más común que la precedería.

Si ni la palabra anterior ni la siguiente se encuentran en los textos del artista, se elige una palabra al azar.

Opté por utilizar un diccionario como base de datos para todas las palabras junto con sus siguientes y anteriores. Por ejemplo, la palabra "te" tendría varias palabras siguientes, como "vi" o "trate", junto con un contador que se incrementa cada vez que esa palabra sigue a "te".

La parte que más me complicó fue que, en el texto correspondiente al archivo en "frases", a veces no detectaba las "_" ya que podían estar seguidas de un punto o coma. Esto se debía a que al usar split(), por ejemplo, _. o _, se interpretaba como una palabra única y no se separaba en la lista.
