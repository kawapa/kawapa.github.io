---
layout: post
title: Specjalne funkcje składowe klas
categories: [post]
date: 2022-07-20
permalink: /specjalne-funkcje-skladowe-klasy
nav_exclude: true
---

# Specjalne funkcje składowe klasy
{: .no_toc }

---

1. Destruktor
2. Konstruktor domyślny 
3. Konstruktor kopiujący
4. Kopiujący operator przypisania
* **Żeby zadziałał, obiekt na który kopiujemy musi już istnieć**
* Warto sprawdzić czy nie przypisujemy tego samego obiektu do siebie: *if (this == &other) return;*
5. Konstruktor przenoszący
6. Przenoszący operator przypisania
* **Żeby zadziałał, obiekt na który przenosimy musi już istnieć**
* Warto sprawdzić czy nie przypisujemy tego samego obiektu do siebie: *if (this == &other) return;*

```cpp
class Entity {
  ~Entity() { }
  Entity() { }

  Entity(const Entity& other) { }
  Entity& operator=(const Entity& other) { }
  
  Entity(Entity&& other) { }
  Entity& operator=(Entity&& other) { }
};
```

## Wymuszanie domyślnej implementacji

```cpp
class Entity {
  Entity(int i) { /* ... */ }
  Entity() = default;
  // Wymuszenie domyślnej implementacji bo istnieje inny konstruktor
};
```

## Usunięcie wybranej składowej klasy

```cpp
class Entity {
  Entity(const Entity& other) = delete;
  Entity& operator=(const Entity& other) = delete;
  // Zablokowanie kopiowania dla obiektów klasy Entity
};
```
