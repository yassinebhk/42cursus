git checkout main
git pull origin main
git checkout -b yassine
git branch
git add .
git commit -m "Descripción de cambios"
git push origin yassine

Para funsionar los cambios de nuestra rama a la rama main:

	1 -> git checkout main
	2 -> git merge nombre_nuestra_rama
	3 -> git push origin main

---------------------------------------------------------

Error: 

	AddressSanitizer:DEADLYSIGNAL

Solution: 

	Execute-> setarch `uname -m` -R $SHELL

--------------------------------------------------------

NOTAS:

-> Las señales se usan para el manejo de CTRL-C CTRL-D y CTRL-\
-> No interpretar comillas sin cerrar (IMP) o caracteres especiales no especificados en el
   enunciado como \ (barra invertida) o ; (punto y coma).
-> Si me dan ls | , ver si se debe tratar como un error o qué hay que hacer
-> Lo suyo sería leer toda la línea de comandos y a medida que encuentro un caracter que no 
   sea una palabra almacenarlo, siendo lo más restrictivo el pipe. 
   Cuando tengo un único pipe, p.e, habría que hacer que un hijo del padre ejecute la parte
   izquierda del pipe y otro hijo la parte de la derecha.
-> Si tengo echo hola > a > b > c adios, deberían crearse a b y c pero solo habrá contenido
   en c (hola adíos)
   Igual si tengo hola > a > que tal > b adios, se crearían a y b y sólo habrá contenido en b
