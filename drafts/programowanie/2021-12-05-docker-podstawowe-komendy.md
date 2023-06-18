---
layout: post
title: Docker - podstawowe komendy
date: 2022-06-09 17:00:00
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

