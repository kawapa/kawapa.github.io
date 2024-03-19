---
title: AIDevs - notatki z kursu
layout: post
date: 2024-03-19
categories:
  - post
permalink: aidevs
search_exclude: false
nav_exclude: true
---
# C01L01 — Wprowadzenie do Generative AI

*   Przykładem narzędzia Generatywnego AI to Duże Modele Językowe (Large Language Models, LLM) takie jak rodzina modeli GPT.
    
*   Kurs będzie skupiał się bezpośredniej integracji OpenAI API z kodem aplikacji oraz automatyzacjach.
    

Zjawisko emergencji - ze względu na ilość danych użytych do trenowania modeli językowych, pojawiają się zachowania nieobecne w innych, "mniejszych modelach". Model potrafi coś do czego nie był bezpośrednio trenowany. Stąd wniosek, że wszystkie możliwości modeli z których korzystamy nie są nam jeszcze znane.

Modele świetnie sprawdzają się w:

*   Wcielanie się w różne role co nadaje kontekst interakcji (użyte w trakcie rozmowy słownictwo jest bez problemu rozumiane)
    
*   Transformacje dostarczonych treści. LLM są znacznie lepsze w transformacji niż generowaniu nowych treści.
    
*   Odpowiadanie na pytania na podstawie danych przekazanych jako kontekst (Retrieval-Augmented Generation)
    
*   Tworzenie, edycja, wyjaśnianie i debugowanie kodu
    
*   Natural Language Processing (NLP)
    

**LLMy zwracają dużo lepsze wyniki w przypadku zadań realizowanych na podstawie realizowanego kontekstu, zamiast polegać na podstawowej wiedzy modelu, która może być niepełna lub nieaktualna.** Podczas pracy z Open AI Playground, warto podać kontekst w polu SYSTEM i podkreślić, że generowane odpowiedzi muszą wykorzystywać wiedzę z kontekstu.

Halucynacje - ze względu na brak wiedzy w pewnych obszarach (np. na temat mało znanych bibliotek) model zwraca nie tylko niepoprawną informację, ale wygląda ona tak, jakby była poprawna, przez co trudno na pierwszy rzut oka je zauważyć.

Niedeterministyczna natura modeli - przy ponownych próbach wykonania tych samych instrukcji, wynik może się nieznacznie różnić. Parametr "seed" pozwala na otrzymanie możliwie tych samych rezultatów, ale ciągle jest w fazie beta.

Wprawdzie najnowsze modele są świetne w zadaniach związanych z obliczeniami oraz zadaniami logicznymi, z dwóch wyżej wymienionych powodów nie zaleca się ich stosować do obliczeń, zwłaszcza na dużych liczbach - np. wynik z działania 821^5 zwraca błędny.