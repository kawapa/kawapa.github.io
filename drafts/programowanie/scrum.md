---
layout: post
title: Groovy
permalink: /groovy
---

# Bycie efektywnym członkiem zespołu
Notatki z kursu Linkedin - Being an Effective Team Member.
{: .fs-6 .fw-300 }
---

https://www.linkedin.com/learning/scrum-the-basics/practicing-scrum-in-your-work-environment?autoplay=true&contextUrn=urn%3Ali%3AlyndaLearningPath%3A5ea0a1bc498e26c456a8d9bb

Scrum: The Basics

- W tradycyjnym prowadzeniu projektów zamrażany jest zakres, czas, koszty
- Scrum zamraża czas i koszty (masz do dyspozycji zespół developerów przez 3 miesiące), ale zakres może się zmieniać w trakcie
- Scrum to jedna z metodologii zwinnych (agile)
  - Scrum pomaga zespołom developerskim pracować w skupieniu przez wprowadzeniu ról
    - Product Owner (przypisany w 100% do zespołu, ma wiedzę domenową, przegląda i zatwierdza pracę zespołu, komunikuje się z pozostałymi interesariuszami, ciśnie zespół żeby wziął jak najwięcej roboty na Sprint)
    - Scrum Master (przeciwaga dla PO, chroni zespół przed zbyt dużym obciążeniem, przemawia w interesie zespołu, pomaga zespołowi rozwiązywać codzienne problemy i chroni przed zakłócaniem ich spokoju, dba o procesy)
  - Sprint trwa 2-4 tygodnie
  - Daily Standup
  - Retrospektywna
    - Podsumowanie minionego Sprintu, co było ok, co nie, usprawnienia
- 
- 
- 1. Rozpoczynanie projektu
  - Ustalenie co jest końcowym produktem
    - MVP - Mininum Viable Product (MVP) - produkt po Sprincie który można pokazać klientowi
      - Szybszy feedback
      - Implementowanie w danej chwili tylko najważniejszych rzeczy
    - Nie zawsze jest wymagane dostarczenie MVP na koniec sprintu
  - Dekomponowanie produktu na mniejsze części (zespół musi być zaznajomiony z tym podziałem i rozumieć swoją rolę w całości!)
    - Pogrupowanie podobnych tematycznie zadań
    - Rozbicie ich na mniejsze ficzery
  - 
- 2. Rozbicie zakresu na User stories
  - User Story (historyjka) - szczegółowy przykład użycia aplikacji przez klienta końcowego
    - W takiej formie developerzy dostają zadania
    - PO ustala User Stories
    - Dobry User Story (INVEST)
      - Independent - Jest niezależy - może być dostarczony niezależnie od pozostałych User Stories
      - Negotiable - negocjowalny, może być przedefiniowany lub nawet wycofany
      - Value - dostarcza wartość
      - Estimable - możliwa do ocenienie wielkość w Story Pointsach (musi być na tyle opisowa żeby można było określić czasochłonność)
      - Small - mały na tyle żeby można go było skończyć w 1 spincie
      - Testable - opis musi być na tyle szczegółowy żeby można było napisać testy jednostkowe
    - As a <USER_ROLE>, I want <REQUIREMENT> so that <DESIRED_BENEFIT>
    - User Story może być:
      - Funkcjonalne - ma znaczenia dla klienta końcowego
      - Niefunkcjonalne - funkcjonalność wspierająca, nie dająca bezpośrednio wartości
    - Każde User Story musi mieć kryteria akceptacyjne (Acceptance Criteria (AC))
      - PO ustala AC
        - W przypadku dodawania możliwości tworzenia użytkownika
          - Aplikacja przechwytuje i zapisuje login/pass/phone
          - Aplikacja nie pozwala na podanie nieprawidłowego numeru telefonu
- 3. Ustalenie wytycznych
  - Definition of Done
    - W przeciwieństwie do AC, DoD jest bardziej ogólne - dotyczy wszystkie US
      - Implementacja, zatwierdza wszystkie US ale dodatkowo DoD wymaga:
        - Przetestowania zmian w środkowisku przedprodukcyjnym
        - Przejścia Code Review przynajmniej 2 osób
  - Backlog prioritization
    - Ustalenie priorytetów taskóœ
      - PO może zmieniać priorytety tasków w backlogu (ale nie tych które są już w sprincie)
  - Sprint cadence (długość)
    - Zbyt krótki - zespół się stresuje i cierpi jakość
    - Zbyt długi - rozprężenie
- 4. Szacowanie US
  - Ilość SP to oszacowanie, nie obietnica
- 5. Zaplanowanie kolejności działań i releasu
  - Roadmap - plan co będzie kiedy robione w czasie
  - Release plan - łączy roadmap z poszczególnymi sprintami
- Planowanie Sprint
  - Obecni wszyscy: developerzy, PO, SM
  - PO pokazuje backlog z aktualnymi priorytetami
  - Wszyscy rozumieją US i ACs
  - Pytania i odpowiedzi
  - Na końcu spotkania zespół określa co zrobi dlatego musi być wszystko jasne
  - --
  - Jeśli wszyscy rozumieją US, team przygotowuje listę rzeczy do zrobienia żeby dane story wykonać
    - Task 1: Stworzyć user ID
      - To do 1: Zapisz user Id do bazy - 0.5 h
      - To do 2: XXX - 4 h
      - To do 3: YYY - 2 h
  - Każdy US musi być rozbity na taski, a poszczególne taski muszą mieć określoną pracochłonność w h



## Bibliografia

* [Linkedin Learning - Being an Effective Team Member](https://www.linkedin.com/learning/being-an-effective-team-member)
