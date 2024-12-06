---
title: Paweł Kawalec
layout: home
permalink: /
---

<div class="row">
  <div class="column left">
    <img class="profile-image" src="/docs/assets/me.webp" alt="Me">
  </div>
  <div class="column right">
    <h2>Paweł Kawalec</h2>
    <p>Software Engineer</p>
  </div>
</div>

## Hi there!

I'm a software engineer with over 4 years of proved expertise in designing, testing, and maintaining robust back-end solutions within automotive and gaming sectors.

Before entering the IT sector, I worked as a Product Manager for a Swedish company that manufactures dairy equipment. After a few years, I realized this was not the path I wanted to continue on. I sought a career that would allow me to have a greater impact on the results of my work and better utilize my natural abilities and talents - according to the Gallup report, my leading talent is [Analytical](https://www.strengthsnavigator.com/analytical).

When I'm not coding or blogging, I enjoy spending time with my family, reading, playing sports, and engaging in chess.

Some clients I have worked for:

<div class="slider">
    <div class="slides">
        <div class="slide active">
            <img src="/docs/assets/companies1.png" alt="Nvidia | ZF | Stellantis">
        </div>
        <div class="slide">
            <img src="/docs/assets/companies2.png" alt="Magna | Spyrosoft | Wazdan">
        </div>
    </div>
    <button class="prev" onclick="changeSlide(-1)">&#10094;</button>
    <button class="next" onclick="changeSlide(1)">&#10095;</button>
</div>

---

## Writing

This is a collection of posts as well as short notes on the things I learn daily. These notes cover a wide range of topics, including technologies, personal growth, and life observations. I share these insights publicly as I learn.

Recent posts:

<ul>
  {% assign visible_posts = site.pages %}

  {% assign sorted_posts = visible_posts | sort: 'date' | reverse %}
  {% assign latest_posts = sorted_posts | slice: 0, 5 %}

  {% for post in latest_posts %}
    {% if post.title and post.url != "/" and post.url != "/404" and post.url != "/posts" %}
      <li>
        <a href="{{ post.url }}">{{ post.title }}</a>
      </li>
    {% endif %}
  {% endfor %}
</ul>

If you're interested, you might want to take a look at [all entries](/posts).

---

## Get in touch

I’m open to new challenges and projects. If you’re looking for a consultant, need development assistance, or have any inquiries, don’t hesitate to contact me via [e-mail](mailto:pawel.kawalec@outlook.com) or [LinkedIn](https://www.linkedin.com/in/pawelkawalec/).