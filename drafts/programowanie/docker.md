---
layout: post
title: Docker - podstawowe komendy
permalink: /docker
---


| Komenda                 | Opis                                            |
| :---------------------- | :---------------------------------------------- |
| Nadpisanie `entrypoint` | `docker run -it --entrypoint /bin/bash <IMAGE>` |
| Nadpisanie `CMD`        | `docker run -it /bin/bash <IMAGE>`              |

## Obrazy

| Komenda                       | Opis                             |
| :---------------------------- | :------------------------------- |
| Pobranie obrazu z DockerHub'a | `docker pull <IMAGE>`            |
| Wyświetlenie listy obrazów    | `docker images -a`               |
| Usuwanie obrazu               | `docker rmi <IMAGE>`             |
| Zapis obrazu do pliku         | `docker save <IMAGE> <FILE>.tar` |
| Podgląd warstw obrazu         | `docker history <IMAGE>`         |

## Kontenery

| Komenda                                 | Opis                                    |
| :-------------------------------------- | :-------------------------------------- |
| Lista kontenerów                        | `docker ps`                             |
| Lista kontenerów (również zatrzymanych) | `docker ps -a`                          |
| Filtrowanie listy kontenerów po nazwie  | `docker ps -a -f name=site`             |
| Zmiana nazwy kontenera                  | `docker container rename site site.old` |
| Usuwanie kontenera                      | `docker rm <CONTAINER>`                 |
| Uruchomienie kontenera                  | `docker start <CONTAINER>`              |
| Zatrzymanie kontenera 1                 | `docker stop <CONTAINER>`               |
| Zatrzymanie kontenera 2                 | `docker kill <CONTAINER>`               |
| Skopiowanie pliku do kontenera          | `docker cp <HOST>:<CONTAINER>`          |


### Rzadziej używane

* Sprawdzenie IP kontenera:


sprawdzenie co nasluchuje
`ps aux`


podglad procesow, uzycia procesora itp
docker stats <KONTENRE>

albo

docker top <KONTENER>


Mozna sie komunikowac np poprzez Curl













docker exec -it <KONTENER> /bin/bash		// Wejście do terminala kontenera
											// Kontener musi być uruchomiony
											// docker start <NAZWA_KONTENERA>

docker container diff <KONTENER>		// pokazuje zmiany poczynione wzgledem 
										// oryginalnego obrazu
										
docker container export -o <NAZWA>.tar <KONTENER>	// eksport kontenera do pliku



exit		// Wyjście z kontenera bez zatrzymywania

### Tworzenie kontenera z obrazu

Najczęściej używane flagi dostępne dla komendy `docker run`:
* `-it` - tryb interaktywny (bez tego nie można się komunikować przez terminal)
* `--name <NAME>` - nadanie kontenerowi nazwy
* `--rm` - po zakończeniu pracy kontener zostanie automatycznie usunięty
* `-d` - uruchomienie w tle
* `-v <HOST>:<CONTAINER>` - podpięcie wolemenu
* `-p 8080:8080` - mapuje port do komunikacji ze światem

Przykłady:
* `docker run -it <IMAGE_OR_LAYER> /bin/bash`

### Tworzenie kontenera z Dockerfile

* USER root:root potrzebne do wykonania stepów

`docker build -t hello <PATH_TO_DOCKERFILE>`

## Sieci

* `bridge` - urządzenie warstwy drugiej, które spina różne interfejsy sieciowe
* Można wybrać do którego `bridge`'a wrzucamy sieci danego kontenera

| Wyświetlenie dostępnych sieci | `docker network ls` |

# Wolumeny

Wolumeny służą do współdzielenia danych pomiędzy kontenerami, a także umożliwiają zamontowanie w kontenerze lokalnej śieżki z komputera hosta.

| `docker volume ls` | Podgląd wszystkich wolumenów |

## Plik Dockerfile

* `RUN` tworzy nową warstwę (im więcej warstw, tym większy jest obraz)
  * Można się dostać do plików w poszczególnych warstwach dlatego nie należy trzymać wrażliwych danych w systemie plików

```Dockerfile
# Use the official image as a parent image.
FROM node:current-slim

# Set the working directory.
WORKDIR /usr/src/app

# Copy the file from your host to your current location.
COPY package.json .

# Run the command inside your image filesystem.
RUN npm install

# Add metadata to the image to describe which port the container is listening on at runtime.
EXPOSE 8080

# Run the specified command within the container.
CMD [ "npm", "start" ]

# Copy the rest of your app's source code from your host to your image filesystem.
COPY . .
```

# Porządki

`docker system prune`		// Usuwa wszystko nieużywane (sieci, kontenery, obrazy, chache)
`docker image prune`		// Usuwa wszystkie nieużywane obrazy
`docker container prune`	// Usuwa wsystkie zastopowane kontenery

## Dobre praktyki

* Zalecane jest uruchamianie kontenerów w trybie read-only, a w przypadku konieczności edycji plików stosować wolumeny

## Docker bez sudo

https://docs.docker.com/engine/install/linux-postinstall/

## Bibliografia










## Nadpisanie entrypoint
sudo docker run -it --entrypoint /bin/bash [docker_image]


## Nadpisanie CMD

sudo docker run -it /bin/bash [docker_image]



# Obrazy

```dockerfile
docker pull <NAME>					// Pobranie obrazu z oficjalnej bazy

docker images -a					// Lista obrazów
docker rmi <IMAGE>					// Usuwanie obrazu

docker save <OBRAZ> <PLIK>.tar		// Zapis obrazu do pliku

docker history <OBRAZ>				// Podgląd warstw
```

# Kontenery

Kontener nie wykorzystuje Hypervisor'a tylko server deamon i jest to niepełnoprawny system, bez kernela.

```dockerfile
docker ps -a						// Lista

docker ps -a -f name=site			// Filtrowanie wyników (te z nazwą site)

ocker container rename site site.old	// Zmiana nazwy

docker rm --force <KONTENER>			// Usuwanie

docker start <KONTENER>			// Uruchomienie
docker stop <KONTENER>			// Zatrzymanie 1
docker kill <KONTENER>			// Zatrzymanie 2

docker exec -it <KONTENER> /bin/bash		// Wejście do terminala kontenera
											// Kontener musi być uruchomiony
											// docker start <NAZWA_KONTENERA>

docker container diff <KONTENER>		// pokazuje zmiany poczynione wzgledem 
										// oryginalnego obrazu
										
docker container export -o <NAZWA>.tar <KONTENER>	// eksport kontenera do pliku

docker cp <HOST>:<KONTENER>	// Skopiowanie pliku do kontenra

exit		// Wyjście z kontenera bez zatrzymywania
```

#### Tworzenie kontenera z obrazu

```dockerfile
docker run -it <OBRAZ> bin/bash				// Stworzenie kontenera z obrazu

docker run -ti <OBRAZ-LUB-WARSTWA> /bin/bash   // Tworzenie kontenera z konkretnej warstwy
```

Flagi dla `docker run`:

```dockerfile
- it					// iteraktywny (bez tego nie można się komunikować przez terminal)
--name <NAZWA>			// nadanie nazwy
--rm					// po zatrzymaniu kontenera jest on usuwany
-d						// uruchomienie w tle
-v <HOST>:<KONTENER>	// podpięcie wolumin
-p 8080:8080			// ustawienie portu do komunikacji
```

#### Tworzenie kontenera z Dockerfile

```dockerfile
docker build -t hello <ŚCIEŻKA_DO_DOCKERFILE>	// Stworzenie obrazu z Dockerfile
```


Flagi dla `docker build`


```dockerfile
-t		// nadanie nazwy
-v		// montowanie woluminu

(domyślnie tworzy się tag latest)
```

#### Sprawdzenie IP kontenera

Tradycyjnie:

```dockerfile
docker exec -ti <KONTENER> sh
>> ip a
```

Szybciej:

```dockerfile

// LUB

docker inspect site | jq -r .[].NetworkSettings.Network.bridge.IPAddress
```

# Sieci

* `bridge` - urządzenie warstwy drugiej, które spina różne interfejsy sieciowe
* Można wybrać do którego `bridge`'a wrzucamy sieci danego kontenera

```dockerfile
docker network ls		// wyświetlenie dostępnych sieci
```

# Woluminy

```dockerfile
docker volume ls		
```

# Dockerfile

* Każdy RUN tworzy nową warstwę
* Im więcej warstw, tym większy jest obraz



```dockerfile
FROM centos
RUN echo secret > /sercret  	// WARSTWA 1
RUN ...                     	// WARSTWA 2

// można się dostać do plików w poszczególnych warstwach dlatego
// nie ma sensu podawanie hasłą w 1 warstwie i w kolejnej kasowanie
```



```dockerfile
FROM centos:7
COPY ./event-scanner /bin
COPY ../config.json /bin
```



### Zamontowanie w obrazie ścieżki z hosta

Volumes
1. Do współdzielenia danych pomiędzy kontenerami
2. Do zamontowania lokalnej ścieżki z hosta kontenerze








```docker
# Use the official image as a parent image.
FROM node:current-slim

# Set the working directory.
WORKDIR /usr/src/app

# Copy the file from your host to your current location.
# COPY package.json .

# Run the command inside your image filesystem.
RUN npm install

# Add metadata to the image to describe which port the container is listening on at runtime.
EXPOSE 8080

# Run the specified command within the container.
CMD [ "npm", "start" ]

# Copy the rest of your app's source code from your host to your image filesystem.
COPY . .
```

# Czyszczenie

```dockerfile
docker system prune		// Usuwa wszystko nieużywane (sieci, kontenery, obrazy, chache)
docker image prune		// Usuwa wszystkie nieużywane obrazy
docker container prune	// Usuwa wsystkie zastopowane kontenery
```

# Inne

* Docker bez `sudo`
  * https://docs.docker.com/engine/install/linux-postinstall/




----
sprawdzenie co nasluchuje
ps aux 
---

DOCKER zmienia firewalla' i dopisuje przekierowania
iptables -t nat -L -n


---

docker run -u 9999:9999 -ti --name aaa --rm <NAZWA_KONT> sh

----

podglad procesow, uzycia procesora itp
docker stats <KONTENRE>

albo

docker top <KONTENER>









----
sprawdzenie co nasluchuje
ps aux 


Mozna sie komunikowac np poprzez Curl
----

DOCKER zmienia firewalla' i dopisuje przekierowania
iptables -t nat -L -n









---
docker run -u 9999:9999 -ti --name aaa --rm <NAZWA_KONT> sh


dobra praktka:
uruchamaiwac kontenre read-only


docker run --read-only -ti --name aaa --rm alpine sh



najczesciej caly katalog jest read only, ale volumin do zmian


-----




---



----


podglad procesow, uzycia procesora itp

docker stats <KONTENRE>



albo

docker top <KONTENER>


----





--------------

# Przygotowanie aplikacji do uruchomienia w kontenerze

portainer.sandbox.dev-http.com/#/stacks



1. Przygotowanie Dockerfile

![Screenshot from 2020-10-20 12-56-15](/home/kawapa/Pictures/Screenshot from 2020-10-20 12-56-15.png)



USER root:root potrzebne do wykonania stepów



CMD - kontener uruchomiony z opcjami -g i daemon ff



2. Commit
3. Push
4. Musi być .gitlab.ci.yml

![Screenshot from 2020-10-20 12-58-50](/home/kawapa/Pictures/Screenshot from 2020-10-20 12-58-50.png)

FAZA BUILD:

* Zbudowano obraz

* Wypchano go do harboura (harbor.dev.int/harbor/sign-in)



FAZA RELEASE:

* pobranie tokena
* wyswietlanie tokena
* za pomoca curla i tokena, majac idenyfikator swarma, posilkujac sie plikiem stack.yml z repo -> robimy deploy stacka Test
  * Stack.yml to konfiguracja usług, stacku aplikacji kontenerowych 
  * Stack ma zapisaną konfirację, jakie usługi są uruchomione
* Stack.yml
  * Labels zawiera m.in pod jaka domena ta apka ma byc dostepna (rule=Host)
  * Pojedyncza usulga site
  * Secrets  

![Screenshot from 2020-10-20 13-06-20](/home/kawapa/Pictures/Screenshot from 2020-10-20 13-06-20.png)



FAZA DESTROY:

* Usunięcie aplikacji (stacka w portainerze)

* Krok manualny, trzeba go wywołać ręcznie
* Niszczenie środowiska z poziomu GitLaba



WYMAGANE:

Zeby wszystko działało GitLab musi potrafić sie komunikować z harbourem i portainerem:

* Hasła do portainera i harboura

* Settings -> CI / CD





---

C++



1. Tylko podczas budowania potrzebne sa zaleznosci
2. Binarka kopiowana jest do kolejnego stage'a
3. ... ktory nie ma wszystkich zaleznosci (goly kontener)



Przekazywanie plikóœ konfiguracyjnych: (config)



```dockerfile
secrets:
	- source ...
	  target: app/report_service/config/config.yaml
```



traefik obsluguje komunikacje





----



docker compose to tak naprawde to konfiguracja stacka w portainerze







kaninko - narzędzie do wysyłania do harboura