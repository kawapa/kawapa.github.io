---
layout: post
title: Groovy
permalink: /groovy
---

# Bycie efektywnym członkiem zespołu
Notatki z kursu Linkedin - Being an Effective Team Member.
{: .fs-6 .fw-300 }
---

- CubeMX
  - Chcemy ustawiać stan diody więc wybieramy PA5 i wybieramy GPIO_Output
  - Chcemy czytać stan przycisku PC13 dlatego ustawiamy GPIO_Input
  - Sprawdzenie stanu przycisku
    - HAL_GPIO_ReadPin(Button_GPIO_Port, Button_Pin) == GPIO_PIN_SET
- HAL
  - Opóźnienie
    - HAL_Delay(delay_time_in_miliseconds);
  - Dioda
    - HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET);
    - HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET);
    - HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_15);
      "Przyjmuje przeciwny stan"


## Bibliografia

* [Linkedin Learning - Being an Effective Team Member](https://www.linkedin.com/learning/being-an-effective-team-member)
