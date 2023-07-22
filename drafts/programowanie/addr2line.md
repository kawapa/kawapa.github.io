---
layout: post
title: Narzędzie addr2line
permalink: /addr2line
---

# Narzędzie addr2line
{: .no_toc }

---

`cmake -B build -DCMAKE_BUILD_TYPE=Debug`

żeby działało nie może być `link_libraries(-rdynamic)`

`addr2line 0x400968 -e libunwind_backtrace`

## Bibliografia

* https://zoomadmin.com/HowToLinux/LinuxCommand/addr2line
* https://eli.thegreenplace.net/2015/programmatic-access-to-the-call-stack-in-c/
