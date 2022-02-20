---
layout: post
title: Idiomy w c++
date: 2021-12-31 06:00:00
permalink: /idiomy
---

## copy-and-swap idiom

```cpp
    // user-defined copy assignment (copy-and-swap idiom)
    A& operator=(A other)
    {
        std::cout << "copy assignment of A\n";
        std::swap(n, other.n);
        std::swap(s1, other.s1);
        return *this;
    }
```

## erase-remove