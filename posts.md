---
title: Posts
nav_order: 2
layout: home
permalink: posts
---

# Posts

{% assign visible_posts = site.pages %}

{% assign posts_by_year = visible_posts | group_by_exp: "post", "post.date | date: '%Y'" | reverse %}

{% for year in posts_by_year %}
  <h2>{{ year.name }}</h2>
  <ul>
    {% assign sorted_posts = year.items | sort: 'date' | reverse %}
    {% for post in sorted_posts %}
      {% if post.title and post.url != "/" and post.url != "/404" and post.url != "/posts" %}
        <li>
          <a href="{{ post.url }}">{{ post.title }}</a>
        </li>
      {% endif %}
    {% endfor %}
  </ul>
{% endfor %}