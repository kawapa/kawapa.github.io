---
layout: post
title: "Jekyll"
date: 2022-07-19 16:00:00
permalink: /jekyll
---

# Jekyll
{: .no_toc }

Przydatne komendy i szablony
{: .fs-6 .fw-300 }

---

| Komenda | Opis |
|:--------------|:--------|
| `bundle exec rake preview -v` | Uruchomienie podglądu live |
| `search_exclude: true` | Ukrycie posta w wyszukiwarce |

---

## Szablon posta

```
---
layout: post
title: "Tytul"
date: 2021-12-02 16:00:00
permalink: /tytul
---

# Tytul
{: .no_toc }

2-3 zdania wstępu
{: .fs-6 .fw-300 }

<details close markdown="block">
  <summary>
    Spis treści
  </summary>
  {: .text-delta }
1. TOC
{:toc}
</details>

---

## ROZDZIAŁ 1
```
