---
layout: post
title: Wzorzec projektowy Obserwator
permalink: /XXX
search_exclude: true
---

Obserwator
https://stackoverflow.com/questions/50831570/how-can-i-identify-an-stdfunction-in-a-container-and-remove-it
https://stackoverflow.com/questions/51848507/good-way-to-create-observer-design-pattern-in-c

## 5. Bibliografia

- [Dmitri Nesteruk - Design Patterns in Modern C++ (Udemy)](https://www.udemy.com/course/patterns-cplusplus/)

```
#include <algorithm>
#include <future>
#include <iostream>
#include <thread>
#include <utility>
#include <vector>
#include <chrono>
#include <functional>
#include <unordered_map>


class God {
private:
    std::vector<std::function<void()>> v;

public:
    void register2(std::function<void()> f) {
        v.push_back(f);
    }

    void notify_all() {
        for (auto&& i : v) {
            i();
        }
    }
};

struct obs1{ 
    void notify() { std::cout << "Obs1\n"; }
};

struct obs2{ 
    void notify() { std::cout << "Obs2\n"; }
};

int main() {
    God g;
    obs1 o1;
    obs2 o2;

    g.register2([&]{ o1.notify(); });

    g.notify_all();

    return 0;
}
```