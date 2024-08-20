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
