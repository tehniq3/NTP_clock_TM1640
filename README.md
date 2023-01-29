# NTP_clock_TM1640
based on:
- https://wiki.keyestudio.com/Ks0357_Keyestudio_8x16_LED_Matrix_Panel
- https://github.com/maxint-rd/TM16xx
- http://nicuflorica.blogspot.com/2020/02/pseudoceas-pe-2-matrici-de-8x8-leduri.html
- https://www.riyas.org/2013/12/online-led-matrix-font-generator-with.html
- https://learn.sparkfun.com/tutorials/serial-communication/serial-intro

articles:

- https://nicuflorica.blogspot.com/2023/01/ceas-ntp-pe-afisaj-led-16x8-cu-tm1640.html
![real](https://blogger.googleusercontent.com/img/b/R29vZ2xl/AVvXsEgclwSbFn4X2emB1_GxjbP_j2-Eyw0yr3CsjLcpJWfEnYOptpxgf5LL2uywg-UIZ33le9I-aFniOYiInVrVKndiJ7Lb5bjyR-09E4mFQUnRoZyLuPP5y_Bck3NGQtaTqVVe2oBenx31buQIkLCi2y_DCvLXy0B4WFk4UyAUXGr7Rq_mgo7An_ebiDebEA/w200-h150/NTP_clock_TM1640_ora_2.jpg)

- http://nicuflorica.blogspot.com/2023/01/ceas-ntp-pe-afisaj-led-16x8-cu-tm1640-2.html
![real2](https://blogger.googleusercontent.com/img/b/R29vZ2xl/AVvXsEibzZ1A1SEp2dxQV6kIjhqSxvkAQA3AB5ahtiAWR-M13FMoO_MNDiIFsOeE-i8N1wO67ihVEXvlpYqfSHXWceRX7VPql4HIqgVKAeQL1dscvOFObZ-BAL93GI1hozgaYFPPCvseEi8TvKwimss7aLptGP8w2xHYAzk9CPzIePnRw5xcs8HqaPjeVrMozw/w200-h150/NTP_clock2_TM1640_ora_5.jpg)

![schemtic](https://blogger.googleusercontent.com/img/b/R29vZ2xl/AVvXsEhN-gvWEqN1lp_iDNjUhm6MnRrZe4l89Oav4i7Cu5ZJqq5rB1qC1Z1zPcy89loWwRwEudhG3ScdiHWZwMCu64cpdDl4p8oTlJ2w_j1UsMlggDsTvEyFRVIewuhz1Ydk4u48ImQixa1dpOyFsRr3gCMkrnHXqEucWEcXsFDEfFaDaQlSxQJPZcY8Q4puRg/s800/NTP_clock_DST_TM1640_schematic.png)

history:

// v.1 - 12-hour format: added hardware switch for DST (Daylight Saving Time) as at https://nicuflorica.blogspot.com/2022/12/ceas-ntp-pe-afisaj-oled-de-096-128x64.html

// v.1a - 12-hour format: changed 5 number

// v.2 - 24-hour format: minute characters smaller than for hours

// v.2.a - 24-hour format: if hours < 10 not show 0 but free space (not 09:34 but  9:34)

![afisaj](https://wiki.keyestudio.com/images/5/59/KS0357-1.png)
