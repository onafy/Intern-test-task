Di library Timer1 ini disediakan dua opsi hardware yaitu berbasis chip  AVR_ATtiny85 dengan ukuran Timer1nya 8 bit
, chip AVR yang Timer1nyas 16 bit dan chip lain yang non-AVR dengan Timer1 juga 16 bit

Karena yang akan diambil contoh adfalah arduino Uno, maka opsi yang digunakan adalah opsi kedua chip AVR dengan Timer1 16 bit.

## 1. void initialize(microseconds = 1000000)
- paramaeter dari method ini adalah periode Timer yang ingin diset. Secasra default periodenya diset menjadi 1000000 microseconds atau 1 second.
- Method ini adalah method yang harus diinisialisasi sebelum menggunakan method yang lain
- pada method initialize ini, metho setPeriod akan dipanggil dengan parameter yang sama dengan parameter dari method initialize ini sendiri dan Timer control register (TCCRA) yang mengatur hubungan Compare Outpun (OCR) dan Timer1 di set menjadi 0 

## 2. void setPeriod(microseconds)
- parameter microseconds adalah periode yang diset pada method initialize()
- berdasarkan http://playground.arduino.cc/Code/Timer1 , minimum periode yang bisa diset adalah 1 microseconds dan maksimum 8388480 microseconds atau 8,3 seconds
- di method ini dihitung cycles berdasarkan frekuensi CPU (Arduino UNO = 16MHz atau 0,0625 microseconds) dan periode Timer yang menjadi parameter fungsi ini.
  jika dihitung, dengan perumpamaan periode yang digunakan adalah periode default yaitu 1000000 microseconds maka
  cyclesnya ((0,0625/100000 * 1000000) / 20) = 0,03125
- hasil cycles ini akan dibandingkan dengan TimerResolution (16bit), dimana masing-masing percabangan akan menghitung pwmPeriod dan clockSelectBits
- clockSelectBits = _BV(CS11);
dalam memprogram microcontroller, biasanya ada bit-bit tertentu perlu diset (1) atau diclear (0) pada register IO tertentu. Misal untuk membuat port 5 bernilai 1/high, untuk melakukan itu register akan di OR kan dengan nilai 1 (0000 0001) kemudian dishift 5 kali
ke kiri sehingga menjadi 0010 0000. 
                            namaregister |= ( 1<<5)
Sehingga ini akan memaksa bit ke-5 dari register tersebut menjadi bernilai 1. Nah perintah ini dapat digunakan melalui makro _BV(bit yang diinginkan) dimana BV adalah kepanjangan dari bit value. sehingga pernyataannya menjadi
                            namaregister |= _BV(5)
sehingga untuk perintah clockSelectBits = _BV(CS11) nmaksudnya pin CS11 akan dipaksa bernilai , hasilnya akan disimpan pada clockSelectBits
- sedangkan pwmperiod merupakan hasil kali bilangan tertentu(tergantung memenuhi cabang yang mana) dengan cycles yang diperoleh
- diakhir percabangan, Input Compare Register (ICR) yang mengukur waktu antara pulsa-pulsa pada pin-pin ICP akan diset nilainya sesuaqi pwmperiod yang didapat
- kemudian register Timer/Counter Control Register tipe B (TRCCR1B) akan menyimpan bit dari clockSelectBits dan _BV(WGM13) (yang dishift / diset 1). Berdasarkan clock clock yang terbentuk dari clock-clock yang terbentuk dari CS10, CS11 dan CS12 yang tersimpan di clockSelectBits itu akan menentukan control apa yang akan dilakukan. seperti  pada gambar
![tccr1b](https://user-images.githubusercontent.com/42448473/51250024-29ff4d00-19d0-11e9-9e80-35e1df7924ad.png)


