---
layout: post
title: Idiomy w C++
date: 2022-07-19 17:00:00
permalink: /idiomy-cpp
---

# Idiomy w C++
{: .no_toc }

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