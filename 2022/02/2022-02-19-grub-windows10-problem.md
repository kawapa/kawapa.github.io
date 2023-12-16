---
layout: post
title: GRUB - Windows 10 nie ładuje się
categories: [post]
date: 2022-02-19
permalink: /grub-windows10-problem
nav_exclude: true
---

# GRUB - Windows 10 nie ładuje się
Podczas rozruchu, po wybraniu systemu operacyjnego Windows, system nie uruchamia się.
{: .fs-6 .fw-300 }

---

## Rozwiązanie krótkoterminowe

**Uwaga!** Po każdej aktualizacji systemu trzeba powtórzyć procedurę.

1. Otwórz plik `/boot/grub/grub.cfg`.
2. Znajdź wpis dotyczący Windows'a, na przykład:

```bash
### BEGIN /etc/grub.d/30_os-prober ###
menuentry 'Windows 10 (loader) (on /dev/sdXX)'
```

3. Po linii `chainloader +1` dopisz: `ntldr /bootmgr`.
4. Zrestartuj komputer.

---

## Rozwiązanie permanentne

1. Zapisz plik `/etc/grub.d/40_custom` w tej samej lokalizacji pod nazwą rozpoczynającą się od `06_`.
2. Skopiuj odpowiednie wpisy `menuentry` z `/boot/grub/grub.cfg` do nowostworzonego pliku.
3. `sudo update-grub`
    * Wpisy pochodzące z pliku `06_` będą pojawiać się zawsze na początku menu GRUB'a 
