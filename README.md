# NTP_clock_TM1640
based on:
- https://wiki.keyestudio.com/Ks0357_Keyestudio_8x16_LED_Matrix_Panel
- https://github.com/maxint-rd/TM16xx
- http://nicuflorica.blogspot.com/2020/02/pseudoceas-pe-2-matrici-de-8x8-leduri.html
- https://www.riyas.org/2013/12/online-led-matrix-font-generator-with.html
- https://learn.sparkfun.com/tutorials/serial-communication/serial-intro

history:
// v.1 - 12-hour format: added hardware switch for DST (Daylight Saving Time) as at https://nicuflorica.blogspot.com/2022/12/ceas-ntp-pe-afisaj-oled-de-096-128x64.html
// v.1a - 12-hour format: changed 5 number
// v.2 - 24-hour format: minute characters smaller than for hours
// v.2.a - 24-hour format: if hours < 10 not show 0 but free space (not 09:34 but  9:34)

