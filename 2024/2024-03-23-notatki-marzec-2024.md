---
title: "Notatki: Marzec 2024"
layout: post
date: 2024-03-23
categories: draft
search_exclude: false
nav_exclude: true
---
Przygotuj post: Marzec 2024

*   JFrog CLI
    
    *   Lista repozytoriów
        
        jfrog rt c show
        
    *   Usunięcie repozytorium
        
        jfrog rt c delete ABC
        
    *   jfrog config add Artifactory --artifactory-url="<a target="_blank" rel="noreferrer" class="contentLink" href="https://artifactory.ocp-sdp.p4avd.fcagroup.com/">https:/free/</a>[artifactory.ocp-sdp.p4avd.fcagroup.com/artifactory](http://artifactory.ocp-sdp.p4avd.fcagroup.com/artifactory)"
        
    *   jfrog rt config
        
        *   Harbor
            
        *   [harbor-registry.itstg.p4avd.fcagroup.com](http://harbor-registry.itstg.p4avd.fcagroup.com)
            
        *   gvx2LPcJYQbKm6hAjmJbcLBAdzKmMQB7
            
*   Kopiowanie przez SSH
    
    *   scp -r [ansys\_tchain-dev-s@USAHSGLPP002.p4avd.fcagroup.com](mailto:ansys_tchain-dev-s@USAHSGLPP002.p4avd.fcagroup.com):/mapr/dp.staging.ah/p4avd-dev/data/store/simulation/data\_driven/jobs/tsa-cdaf294c-09c4-11ed-a259-0a580a090147-1/input/scenarios .
        
*   Łatwe dodawanie nowych repozytoriów w Ubuntu
    
    *   apt install software-properties-common
        
    *   apt-add-repository --yes --update ppa:ansible/ansible
        
*   find /ścieżka/do/katalogu -name "nazwa\_pliku" 2>/dev/null
    
*   Wyłączenie zdalnego cache w bazel
    
    *   Dla pojedynczej komendy przełącznik --noremote\_accept\_cached
        
    *   Dla całego projektu, zakomentuj fragment
        
        *   build --remote\_cache=[http://replace-with-your.host:port](http://replace-with-your.host:port)
            
*   git lfs
    
    *   Git Large File Storage (LFS) replaces large files such as audio samples, videos, datasets, and graphics with text pointers inside Git, while storing the file contents on a remote server like [GitHub.com](http://GitHub.com) or GitHub Enterprise.
        
*   Inaczej się klonuje repozytoria jeśli ma się 2 klucze SSH w jednym serwisie
    
    *   git clone [https://pae:h2xZJ1vwh5sdTDq2aNov@git.spyrosoft.it/medichat/medichat-front-user](https://pae:h2xZJ1vwh5sdTDq2aNov@git.spyrosoft.it/medichat/medichat-front-user)
        
*   Kontenery LXC / LXD
    
    *   LXC containers
        
        *   Przygotowanie
            
            *   sudo apt install lxc
                
            *   Sprawdzenie statusu usługi
                
                *   sudo systemctl status lxc
                    
                    *   Sprawdza status usługi
                        
                    *   sudo systemctl start lxc
                        
        *   Tworzenie kontenrea
            
        *   Komendy
            
            *   sudo lxc-ls --fancy
                
            *   sudo lxc-start --name u1 --daemon
                
            *   sudo lxc-info --name u1
                
            *   sudo lxc-stop --name u1
                
            *   sudo lxc-destroy --name u1
                
    *   LXD containers
        
        *   Komendy Linux
            
            *   lsb\_release -dirc
                
                *   Informacje o systemie
                    
            *   groups
                
                *   Sprawdzenie w jakich grupach jest uzytkownik
                    
        *   Można zrobić zrobić nested LXC cotainers
            
        *   Instalacja LXD
            
            *   sudo apt instal lxc
                
            *   sudo snap install lxd
                
            *   żeby używać lxc bez sudo trzeba dodac swojego uzytkownika do lxc group
                
                *   sudo gpasswd -a kawapa lxd
                    
                *   getent group lxd
                    
                    *   Żeby zmiany weszły w zycie trzeba sie przelogowac lub newgrp lxd
                        
                
            *   Pierwsza konfiguracja
                
                *   lxd init
                    
                
            *   Lista komend
                
                *   lxc help | less
                    
            *   Lista źródeł z których będą pobierane obrazy
                
                *   lxc remote list
                    
            *   Lista obrazów dostępnych loklanie
                
                *   lxc image list
                    
            *   Lista wszystkich obrazów dostępnych ze źródeł
                
                *   lxc image list image:
                    
            *   LIsta aktualnych maszyn/kontenerow
                
                *   lxc list
                    
            *   Tworzenie kontenera
                
                *   lxc launch ubuntu:20.04 <OPCJONALNA\_NAZWA>
                    
            *   Usuwanie
                
                *   lxc stop <NAZWA>
                    
                *   lxc delete <NAZWA>
                    
                
                *   albo lxc detele --force <NAZWA>
                    
                    *   nie trzeba zatrzymywac
                        
            *   Zatrzymyniwae/ uruchamianie
                
                *   lxc start <NAZWA>
                    
                *   lxc stop <NAZWA>
                    
            *   Lista obraxow
                
                *   lxc image list
                    
            *   Kopiowanie kontenerow
                
                *   lxc copy <NAZWA\_1> <NAZWA\_2>
                    
            
            *   Zmiana nazwy kontenera
                
                *   lxc move <NAZWA\_1> <NOWA\_NAZWA>
                    
                    *   Jesli kontenre jest na innym hoście trzeba użyć :
                        
                        *   HOST:NAZWA\_KONTENREA
                            
            *   Wejscie do terminala kontenrea
                
                *   lxc exec <NAZWA> bash
                    
            
            *   Dostep do kontenrea z innego kontenera
                
            *   Ping innego kontenrea
                
                *   Wewnatrz kontenrea mozna uzywac zamiast IP nazway kontenera
                    
                *   ping <INNY\_KONTENRE>
                    
            *   Uruchomienie SSH
                
                *   lxc launch ubuntu:20.04 my
                    
                *   lxc exec <KONTENER> bash
                    
                *   sudo passwd root
                    
                    *   Ustawiamy haslo
                        
                *   vim /etc/ssh/sshd\_config
                    
                *   "PermitRootLogin yes"
                    
                *   "PasswordAuthentication yes"
                    
                *   service sshd restart
                    
                
                *   lxc exec <KONTENER> bash
                    
                *   vim /etc/ssh/sshd\_config
                    
                *   "PasswordAuthentication no"
                    
                *   service sshd restart
                    
                
                *   ssh-copy-id -i ~/.ssh/id\_[rsa.pub](http://rsa.pub) USER@HOST
                    
        *   Komendy
            
            *   image
                
            *   launch
                
            *   start
                
            *   stop
                
            *   delete
                
            *   list
                
            *   exec
                
            
            *   config
                
                *   limits.cpu
                    
                *   limits.memory
                    
                *   security.privliged
                    
                *   security.nesting
                    
            *   info
                
            *   profile
                
            *   copy
                
            *   move
                
            
            *   file
                
            *   snapshot
                
            *   restore
                
*   Code Review
    
    *   Cele CR
        
        *   Wyłapanie błędów w designie kodu
            
            *   Czy ta implementacja dobrze wpasowuje się w istniejący kod?
                
            *   Czy logika stojąca za danym rozwiązaniem jest słuszna i czy uwzględnia corner case'y?
                
                *   Poza happy-pats trzeba uwzględnić także unhappy-paths czyli sytuacje w których użytownik zachowa się inaczej, jakaś zmienna będzie pusta albo jedna z metod w międzyczasie zwróci błąd lub niepoprawny wynik
                    
            *   Czy są wyścigi (programy wielowątkowe)
                
        *   Utrzymanie prostoty i spójności kodu
            
            *   Co tu się dzieje, co ten kod robi?
                
            *   Czy kod wymaga więcej czasu niż powinien żeby go zrozumieć? Czy może jest mylący?
                
            *   Urzymalność kodu
                
            *   Implementacja jest nieutrzymalna jeśli dojdą kolejne warunki
                
        *   Zwalidowanie czy implementacja jest w ogóle potrzebna
            
            *   Dotyczy to raczej luźnych PR, a nie tych które są rzeczywiście połączone z taskami w Jirze
                
                *   Dotyczy to ficzerów, które nie są potrzebne teraz, ale może będą w przyszłości
                    
                    *   Premature optimization - niepotrzebnie rozbudowujemy kod (komplikujemy)
                        
                    *   Przydasię
                        
            *   Najlepsza ilość kodu to 0
                
            *   Może ficzer już jest zaimplementowany?
                
        *   Potwierdzenie że kod robi to co powienien
            
            *   Czy implementacja rozwiązuje wszystkie wymagania opisane w tickecie?
                
            *   Czy jest zachowany styl?
                
            *   Czy są testy? Jeśli nie ma, można takie łatwo stworzyć?
                
            *   Jeśli to bugfix, to czy rozwiązuje on problem?
                
    *   Pytania, które należy sobie zadać podczas CR
        
    *   CR wymaga posiadania procesu, a przynajmniej dokukumentu w
        
    *   Code review powinno być poparte odpowiednim dokumentem (Working Team Agreement) w którym znajdują się odpowiednie wytyczne co do stosowanego:
        
        *   syntax
            
        *   formatting
            
        *   naming convenctions
            
        *   process requirements
            
        *   Inne
            
            *   Lista kroków które nalezy zrobic/sprawdzic podcza CR
                
            *   czy sa testy
                
            *   Minimalna liczba reviewerów
                
            *   nazewnicwtwo branchy
                
            
    *   Dzięki temu podczas CR można się wesprzeć odpowiednim dokumentem
        
*   Ustawienie na sztywno kernela
    
    *   [https://askubuntu.com/questions/216398/set-older-kernel-as-default-grub-entry](https://askubuntu.com/questions/216398/set-older-kernel-as-default-grub-entry)
        
    *   Kopia zapasowa
        
        *   sudo cp /etc/default/grub /etc/default/grub.bak
            
    *   Edycja /etc/default/grub
        
        *   Ustawienie zmiennej GRUB\_DEFAULT="Advanced options for Ubuntu>Ubuntu, with Linux 5.19.0-50-generic"
            
        *   Wartość zmiennej
            
*   Do czego służy _.gitkeep_?
    
*   Vector
    
    std::vecto;;/ r<int> vec(8) tworzy elemeenty wiec push\_back doda 9, 10,11 vec.reserve(8) zarezerwuje rozmiar wiec push bACKI NIE BEDA GO ROZSZERZEAC