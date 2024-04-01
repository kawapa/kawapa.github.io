---
layout: post
title: Operator post- i pre-inkrementacji
permalink: pre-post-inkrementacja
date: 2024-04-01
draft: true
---

Operator `post-` i `pre-`dekrementacji.

```cpp
// operator predekrementacji
A& operator--() {
    x--;
    return *this;
}

// operator postdekrementacji
A operator--(int) {
    A tmp(*this);
    operator--(); // wywołanie predekrementacji
    return tmp;
}
```




## Bibliografia

* http://home.agh.edu.pl/~glowacki/docs/matwykl/O-o/_ProgObiekt-C++14-Rozsz.pdf
 +i6 