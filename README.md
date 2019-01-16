Di library Timer1 ini disediakan dua opsi hardware yaitu berbasis chip  AVR_ATtiny85 dengan ukuran Timer1nya 8 bit
, chip AVR yang Timer1nyas 16 bit dan chip lain yang non-AVR dengan Timer1 juga 16 bit

Karena yang akan diambil contoh adfalah arduino Uno, maka opsi yang digunakan adalah opsi kedua chip AVR dengan Timer1 16 bit.

1. void initialize(microseconds = 1000000)
- paramaeter dari method ini adalah periode Timer yang ingin diset. Secasra default periodenya diset menjadi 1000000 microseconds atau 1 second.
- Method ini adalah method yang harus diinisialisasi sebelum menggunakan method yang lain
- pada method initialize ini, metho setPeriod akan dipanggil dengan parameter yang sama dengan parameter dari method initialize ini sendiri dan Timer control register (TCCRA) yang mengatur hubungan Compare Outpun (OCR) dan Timer1 di set menjadi 0 
