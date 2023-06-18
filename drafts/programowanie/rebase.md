# Merge
* `git merge` tworzy nowy commit zawierające zmiany wprowadzone zarówno na jednym jak i drugim branch'u

# Rebase
* W skrócie rebase zmienia commit na podstawie którego został stworzony feature branch
* Rebase wykonujemy z feature-brancha na branch docelowy
	* `git checkout feature`
	* `git rebase master`
		* Mogą pojawić się konflikty
			* git add file
			* git rebase --continue
	* Przesunąć wskaźnik master na najnowszy commita
		* `git checkout master`
		* `git merge feature`
* Łączenie zmian może być:
	* Fast-forward - nie został utworzony żaden dodatkowy commit reprezentujący łączenie zmian - BRAK KONFLIKTÓÓW
	* Albo nie bo są konflikty
 



![[rebase.gif]]

* Nowe commity (z przodu) mają inne SHAz
