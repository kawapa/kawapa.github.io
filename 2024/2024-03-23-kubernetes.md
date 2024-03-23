---
title: Kubernetes
layout: post
date: 2024-03-23
categories: draft
permalink: k8s
search_exclude: false
nav_exclude: true
---
*   [https://kubernetes.io/docs/tasks/tools/install-kubectl-linux/#enable-shell-autocompletion](https://kubernetes.io/docs/tasks/tools/install-kubectl-linux/#enable-shell-autocompletion)
    
*   kubect delete ns
    
    *   [https://www.redhat.com/sysadmin/troubleshooting-terminating-namespaces](https://www.redhat.com/sysadmin/troubleshooting-terminating-namespaces)
        
*   Kurs Helion
    
    *   <a target="_blank" rel="noreferrer" class="contentLink" href="https://helion.pl/kurs/kubernetes-kurs-video-uruchamianie-skalowanie-i-zarzadzanie-aplikacjami-w-kontenerach-piotr-chudzik,vkubpo.htm#format/w">Helion - Kubernetes - Kurs podstawowy</a>
        
    *   <a target="_blank" rel="noreferrer" class="contentLink" href="https://helion.pl/kurs/kubernetes-kurs-video-wdrazanie-zaawansowanych-aplikacji-piotr-chudzik,vkubez.htm#format/w">Helion - Kubernetes - Kurs zaawansowany</a>
        
*   [https://dev.to/stevenmcgown/kubernetes-for-dummies-5hmh](https://dev.to/stevenmcgown/kubernetes-for-dummies-5hmh)
    
*   [https://fx.vc-mp.eu/kubernetes-k3s-1/](https://fx.vc-mp.eu/kubernetes-k3s-1/)
    
*   Komendy
    
    *   Sprawdzenie statusu
        
        *   kubectl get pod
            
        *   kubectl get services
            
        *   kubectl get nodes
            
    *   Tworzenie
        
        *   kubectl create
            
            *   kubectl create
                
                *   Nie ma POD, ale w rzeczywistosci nie tworzymy PODów ręcznie, tworzymy Deployment
                    
            *   kubectl create deployment nginx-depl --image=nginx
                
                *   kubectl get deployment
                    
    *   Usuwanie
        
        *   kubectl delete pod <NAZWA\_PODa>
            
        
*   Kurs K8S
    
    <a target="_blank" rel="noreferrer" class="contentLink" href="https://www.youtube.com/watch?v=X48VuDVv0do">Kubernetes Tutorial for Beginners [FULL COURSE in 4 Hours]</a>
    
    *   Podstawy
        
        *   Service & Ingress
            
            *   Service to w uproszczeniu stały (statyczny) adres IP który może być dołączony do PODa
                
                *   Jeśli POD ginie, Service zostaje
                    
            *   External Service - będzie dostępne z zewnątrz
                
                *   http://<IP>:<PORT>
                    
                    *   Ingress umożliwia korzystanie z domen tekstowych i odpowiada za przekierowywanie żądań do konkretnego Serwisu
                        
            *   Service służy też jako load-balancer
                
        *   ConfigMap & Secrets
            
            *   ConfigMap służy do trzymania danych konfiguracyjnych aplikacji (bez konieczności trzymania tego w repozytorium razem z kodem aplikacji)
                
                *   Niewrażliwe dane tylko
                    
                *   POD łączy się z ConfigMap i pobiera dane
                    
            *   Secrets
                
                *   Dane do logowania, hasła
                    
                *   Nie przechowywana w formie tesktowej, ale base64 encoded
                    
                *   **Mechanizm bezpieczeństwa Sekretów nie jest domyślnie uruchomiony**
                    
            *   Można używać danych z ConfigMaps lub Seckret w POdzie przy użyciu zmiennych środowiskowych lub jako "properties file"
                
        *   Volume
            
            *   Miejsce na lokalnej maszynie lub zdalnej
                
            *   Zewnętrzne miejsce
                
                *   K8S nei oferuje :"data persistance"
                    
        *   JReplicacje
            
            *   eśli POD z aplikacja padanie - aplikacja nie dziala dlatego jesli skonfuijemy Replica na wiecej niz 1 to na innym Nodzie pojawi sie kopia naszej aplikacji (ale obie beda polaczona z tym samym serwisem)
                
                *   To się konfiguruje w Deployment (przepis na PODy)
                    
            *   Deployment to abstracka na PODy, PODY to absttrackaj dla konenterów
                
            *   Nie da sie zrobic analogicznej kopii \*(replica) dla bazy danych bo bazy danych maja STAN
                
                *   jesli to mialo by dzialac trzeba by zarzadzac jednoczesnym dostepem do fizycznej bazy (2 PODy nie moga jednoczesnei pisac)
                    
                    *   Z tego powodu komponenty przewoujace dane powinny byc tworzone jako StatefulSet, nie jako Deployment
                        
                        *   Trudna konfiguracja stad czesta praktyka ejst
                            
    *   Architektura
        
        *   Node == worker ==server
            
            *   na jednym nodzie jest wiele PODów
                
            *   Na kazdym Nodzie musi byc zainstalowane 3 procesy
                
                *   1\. container runtime (np. docker)
                    
                *   2\. kubelet (proces kubernetesa - schedules PODs
                    
                    *   Komunikuje sie zawrowno z kontenreem jak i nodem
                        
                    *   Kubelet uruchamia POD z kontenterem w srodku
                        
                    *   Przydziela reasrorcy Node'a dla kontenrea (CPU/RAM itd...)
                        
                *   3\. Kube Proxy - Przekazuje zapytania od Serwisow do pODów
                    
                    *   Zapewnia szybka komunikacje, ejsli to mozliwe odpytuje inne mikroserwisy wewnatrz jednego PODa jesli to mozliwe (zeby nie generowac ruchu()
                        
        *   master Node
            
            *   Monitoruje Nody, uruchamia nowe kopie jesli jakas padnie,
                
            *   4 procesy
                
                *   1\. API server - umozliwia polaczenie z klustrem przez terminal/ssh
                    
                    *   Odpowiada za autentykacje, wejscie do klustera
                        
                        *   1 miejsce wejscia do klustera
                            
                *   2\. Scheduler - rozdziela zadania pomiedzy Nody (jesli zadanie polega na stwrozeniu nowego PODa, to bierze pod uwage jakie resorucy on bedize ptorzebowal i porownuje ze stanem workerów)
                    
                    *   Scheduler tylko wybiera, to Kublet rzeczywiscie tworzy tworzy PODa
                        
                *   3\. Controller manager
                    
                    *   Monitoruje PODy, wykrywa jeśli któreś padną
                        
                *   [https://youtu.be/X48VuDVv0do?t=1829](https://youtu.be/X48VuDVv0do?t=1829)