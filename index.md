---
layout: default
title: Strona główna
nav_order: 1
permalink: /
---

# CppDev
{: .fs-9 }

Prywatna baza wiedzy / wiki / [o mnie](o-mnie)
{: .fs-6 .fw-300 }

---

## Lista wpisów

<ul>
  {% for post in site.posts %}
    <li><a href="{{ post.url | relative_url }}">{{ post.title }}</a> - <time class="post-date" datetime="{{ post.date | date:"%Y-%m-%d" }}">
                {% assign m = post.date | date: "%-m" %}
                {{ post.date | date: "%-d" }}
                {% case m %}
                {% when '1' %}stycznia
                {% when '2' %}lutego
                {% when '3' %}marca
                {% when '4' %}kwietnia
                {% when '5' %}maja
                {% when '6' %}czerwca
                {% when '7' %}lipca
                {% when '8' %}sierpnia
                {% when '9' %}września
                {% when '10' %}października
                {% when '11' %}listopada
                {% when '12' %}grudnia
                {% endcase %}
                {{ post.date | date: "%Y" }}
            </time></li>
  {% endfor %}
</ul>
