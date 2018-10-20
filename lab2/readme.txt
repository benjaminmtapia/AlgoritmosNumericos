READ ME
se debe considerar para los resultados:

-los archivos están en formato metodoFUNCION_distanciaDeIntervalo
	ej: dFinitasF1_05 para diferencias finitas con la funcion 1 de intervalos con distancia 0.5

- el código esta estático, y con las distintas funciones comentadas
	está comentado para cambiar los nombres de los archivos y las respectivas llamadas a los distintos metodos
	se recomienda llamar a un metodo solo una vez cada vez que se ejecute el programa

- los vectores y1,y2,y3,y4 son resultados de la funcion 1 mientras que los vectores y11,y22,y33,y44 son los vectores de la funcion 2
	 x1,y1,y11 corresponden a intervalos con distancia de 0.5
	 x2,y2,y11 corresponden a intervalos con distancia de 1
	 x3,y3,y33 corresponden a intervalos con distancia de 5
	 x4,y4,y44 corresponden a intervalos con distancia de 10

-en los gráficos para los casos que no se distingue un metodo entre todos los demás, se adjunto una imagen aparte con ese mátodo unicamente

-hubieron problemas con el calculo de error en diferencias divididas debido a que intervalos del resultado arrojaban nan, debido a que se hacian divisiones por valores muy cercanos a cero
-se hace el resto de las pruebas como la integración respecto a la interpolación por spline cubico debido a que posee el menor error, considerando que no se pudo calcular con exactitud el error de diferencias divididas, pero es sabido que diferencias divididas posee menor error que spline.

-en los archivos erroresf1.txt y errores f2.txt están los errores de los respectivos métodos de interpolación


-Para la mayoría de los cálculos, el intervalo con distancia 0.5 trae problemas y genera varios nan entre resultados válidos, causando problemas en la interpolación con ciertos metodos

-La función 1 trae complicaciones para la mayoría de los calculos debido a su comportamiento exponencial, por lo que algunos metodos de interpolación actuarán mejor que otros, pero el spline cúbico suele ser el que mejor trabaja junto con el de mínimos cuadrados.
