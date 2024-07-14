---
layout: post
title: Kubernetes
date: 2024-03-23
permalink: k8s
draft: true
---

# Auto-uzupełnianie

[https://kubernetes.io/docs/tasks/tools/install-kubectl-linux/#enable-shell-autocompletion](https://kubernetes.io/docs/tasks/tools/install-kubectl-linux/#enable-shell-autocompletion)

---

# Usuwanie ns

Po `kubectl delete ns <NAME>` często namespace jest dalej widoczny, ale ma status *Terminating*. Rozwiązanie problemu:

[https://www.redhat.com/sysadmin/troubleshooting-terminating-namespaces](https://www.redhat.com/sysadmin/troubleshooting-terminating-namespaces)

# Podstawowe komendy

`kubectl get`
`kubectl create`
`kubectl describe`
`kubectl delete`
`kubectl logs`

pod / services / nodes / ns / deployment

* W praktyce nie tworzy się PODów, tylko deployment'y


bash
```
kubectl run hello-kiamol --image=kiamol/ch02-hello-kiamol
```

* Kubectl domyślnie szuka obrazów w Docker Hub


Czeka aż pod hello-kiamol będzie gotowy. 
`kubectl wait --for=condition=Ready pod hello-kiamol` 


`--timeout` domyślnie 30s. Wartość ujemna oznacza czekaj tydzień.

# Debugowanie PODów

`kubectl exec -it <NAME> --- bin/bash`


# `delete`

`kubectl delete --all pods --namespace=foo`
`kubectl delete --all deployments --namespace=foo`


# Service

- Service to w uproszczeniu stały (statyczny) adres IP który może być dołączony do PODa
    - Jeśli POD ginie, Service zostaje
- External Service - coś będzie dostępne z zewnątrz
- Służy jako load-balancer

# Ingress

- Ingress umożliwia korzystanie z domen tekstowych i odpowiada za przekierowywanie żądań do konkretnego Serwisu

# ConfigMap

- ConfigMap służy do trzymania danych konfiguracyjnych aplikacji (bez konieczności trzymania tego w repozytorium razem z kodem aplikacji)
- Niewrażliwe dane tylko
- POD łączy się z ConfigMap i pobiera dane

# Volume

- Miejsce na lokalnej maszynie lub zdalnej
- Zewnętrzne miejsce
- K8S nei oferuje :"data persistance"

# Secrets
    
- Dane do logowania, hasła
- Nie przechowywana w formie tesktowej, ale base64 encoded
- **Mechanizm bezpieczeństwa Secrets nie jest domyślnie uruchomiony**
- Można używać danych z ConfigMaps lub Seckret w POdzie przy użyciu zmiennych środowiskowych lub jako "properties file"

# ReplicaSet

*   eśli POD z aplikacja padanie - aplikacja nie dziala dlatego jesli skonfuijemy Replica na wiecej niz 1 to na innym Nodzie pojawi sie kopia naszej aplikacji (ale obie beda polaczona z tym samym serwisem)

*   To się konfiguruje w Deployment (przepis na PODy)
    
*   Deployment to abstracka na PODy, PODY to absttrackaj dla konenterów

*   Nie da sie zrobic analogicznej kopii \*(replica) dla bazy danych bo bazy danych maja STAN

*   jesli to mialo by dzialac trzeba by zarzadzac jednoczesnym dostepem do fizycznej bazy (2 PODy nie moga jednoczesnei pisac)
    
    *   Z tego powodu komponenty przewoujace dane powinny byc tworzone jako StatefulSet, nie jako Deployment
        
        *   Trudna konfiguracja stad czesta praktyka ejst

# Architektura

## Node

- Node == worker == server
* Na kazdym Nodzie musi byc zainstalowane 3 procesy:

1. Container Runtime Interface (np. Docker lub containerd)
2. Kubelet (proces Kubernetes'a, POD scheduler)
    *   Komunikuje sie zawrowno z kontenreem jak i nodem
    *   Kubelet uruchamia POD z kontenterem w srodku
    *   Przydziela reasrorcy Node'a dla kontenrea (CPU/RAM itd...)
3. Kube Proxy
    - Przekazuje zapytania od Serwisow do pODów
    *   Zapewnia szybka komunikacje, ejsli to mozliwe odpytuje inne mikroserwisy wewnatrz jednego PODa jesli to mozliwe (zeby nie generowac ruchu()

## Master node                
                        
- Monitoruje node'y
- Uruchamia nowe kopie, jeśli jakieś "padną"
- Obsługuje cztery procesy:

1. API server odpowiedzialne za połączenie z klastrem przez terminal/SSH (+ autentykacja)
2. Scheduler
- Rozdziela zadania pomiedzy node'y. Jeśli zadanie polega na stworzeniu nowego POD'a, sprawdza jakich zasobów będzie on potrzebował, sprawdza stan dostępnych node'ów i na tej podstawie dobiera node'a (Kubelet fizycznie uruchamia POD'y)o bierze pod uwage jakie resorucy on bedize ptorzebowal i porownuje ze stanem workerów)
3. Controller manager
- Monitoruje PODy, wykrywa jeśli któreś padną
        
[Kontynuuj oglądanie](https://youtu.be/X48VuDVv0do?t=1829).



kubectl get - wyświetla jeden lub więcej zasobów. Możesz użyć tej komendy, aby uzyskać listę różnych zasobów (np. pods, services, deployments) dostępnych w klastrze.

kubectl describe - wyświetla szczegółowe informacje o określonym zasobie, w tym szczegółowe stany, powiązane zasoby itp.

kubectl create - tworzy zasób z pliku definicji lub ze standardowego wejścia. Przykładem może być uruchomienie nowego poda z określonego pliku YAML.

kubectl apply - stosuje zmianę konfiguracji do zasobu z pliku definicji. Jest to preferowana metoda zarządzania zasobami poprzez deklaratywne pliki konfiguracyjne.

kubectl delete - usuwa zasoby z plików, z stdin lub poprzez podanie selektorów, nazw, identyfikatorów zasobów itd.

kubectl logs - wyświetla dzienniki dla określonych kontenerów w twoich podach, co jest nieocenione do debugowania i monitorowania.

kubectl exec - wykonuje polecenie w kontenerze wewnątrz poda. Jest to przydatne, na przykład, do diagnostyki problemów w uruchomionych aplikacjach.

kubectl scale - zmienia ilość replik danego deploymentu lub replika set na żądaną liczbę, umożliwia szybkie skalowanie usług w górę lub w dół.

kubectl rollout - zarządza procesem wdrażania nowych wersji aplikacji. Do często używanych subkomend należą rollout status, rollout undo i rollout restart.

kubectl config - zarządza konfiguracją kubectl, w tym kontami, kontekstami i przestrzeniami nazw. Dzięki temu możesz łatwo przełączać się między różnymi klastrami i przestrzeniami nazw.

kubectl port-forward - przekierowuje ruch z lokalnego komputera do poda w klastrze, co jest bardzo przydatne do testowania i debugowania.

kubectl proxy - uruchamia serwer proxy między twoim interfejsem a API Kubernetes, umożliwiając bezpieczny dostęp do klastra.


Podłączenie do apisix-etcd-1
kubectl exec -it -n ansys-tsa-dev apisix-etcd-1 -- /bin/bash

Logi
kubectl logs -f -n ansys-tsa-dev apisix-etcd-1

kubectl port-forward svc/apisix-dashboard -n ansys-tsa-dev 9000:http



# Bibliografia

- [TechWorld with Nana - Kubernetes Tutorial for Beginners](https://www.youtube.com/watch?v=X48VuDVv0do)
