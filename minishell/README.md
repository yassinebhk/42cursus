--------------------------------------------------------------------------------------------------
// Actualizar siempre el main para evitar conflictos con actualizaciones ya subidas
git checkout main
git pull origin main
// Crear rama local
git checkout -b yassine
// Hago todos los cambios que necesite . . .
. . .
// Añado cambios y voy haciendo commit según me parezca pertinente
git add *
git commit -m ""
// Por último actualizo mi rama main
git checkout main
git pull origin main
// Resuelvo conflictos con mi rama
git checkout yasin
git merge main
// Resuelvo conflictos manualmente
git checkout main
// Resuelvo conflictos
git rebase yasin // me traigo mis cambios al main
// Si hay conflictos los resuelvo manualmente
// Por ultimo elimino mi rama local y pusheo el main
git branch -d yasin
git push origin main
// Si quiero borrar una rama accidentalmente subida
git push origin --delete yasin

Para funsionar los cambios de nuestra rama a la rama main:

	1 -> git checkout main
	2 -> git merge nombre_nuestra_rama
	3 -> git push origin main

--------------------------------------------------------------------------------------------------
                                          COMPILACIÓN CON VALGRIND
--------------------------------------------------------------------------------------------------

   -> valgrind --suppressions=readline.supp --leak-check=full --show-leak-kinds=all --track-origins=yes -s ./minishell

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


***********************  IMPORTANTE ******************

   -> HACER cd - (me lleva al oldpwd) (cd -- directorio raiz)
   -> cd cuando no es . .. - 
   -> pwd con argumento no valido

COSAS POR HACER
> echo hola | export ejecuta echo en STD_OUT y no export
> las redirecciones tienen fallos en algun punto
    $ cat prueba.txt | tr '$' '~' > prueba.txt
