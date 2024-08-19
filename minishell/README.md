git checkout main
git pull origin main
git checkout -b yassine
git branch
git add .
git commit -m "Descripción de cambios"
git push origin yassine

---------------------------------------------------------

Error: 

	AddressSanitizer:DEADLYSIGNAL

Solution: 

	Execute-> setarch `uname -m` -R $SHELL
