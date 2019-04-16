eFishery Intern Test

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

Sehingga ini akan memaksa bit ke-5 dari register tersebut menjadi bernilai 1. Nah perintah ini dapat digunakan melalui makro _BV(bit    yang diinginkan) dimana BV adalah kepanjangan dari bit value. sehingga pernyataannya menjadi

                             namaregister |= _BV(5)
                             
sehingga untuk perintah `lockSelectBits = _BV(CS11)` maksudnya pin CS11 akan dipaksa bernilai 1, hasilnya akan disimpan pada             clockSelectBits

- sedangkan pwmperiod merupakan hasil kali bilangan tertentu(tergantung memenuhi cabang yang mana) dengan cycles yang diperoleh
- diakhir percabangan, Input Compare Register (ICR) yang mengukur waktu antara pulsa-pulsa pada pin-pin ICP akan diset nilainya sesuaqi pwmperiod yang didapat
- kemudian register Timer/Counter Control Register tipe B (TRCCR1B) akan menyimpan bit dari clockSelectBits dan _BV(WGM13) (yang dishift / diset 1). Berdasarkan clock clock yang terbentuk dari clock-clock yang terbentuk dari CS10, CS11 dan CS12 yang tersimpan di clockSelectBits itu akan menentukan control apa yang akan dilakukan. seperti  pada gambar
![tccr1b](https://user-images.githubusercontent.com/42448473/51250024-29ff4d00-19d0-11e9-9e80-35e1df7924ad.png)


## 3. void pwm(pin, duty) atau void pwm(pin, duty, microseconds)
- method pwm terdiri dari dua jenis dimana kita bisa memilih apakah akan menyertakan periode Timer atau tidak. Perbedaannya hanyalah : ketika kita menyertakan periode timer, maka method setPeriod akan disertakan dengan paramaternya adalah periode Timer yang sama dengan parameter method ini, kemudian akan dipanggil kembali method pwm dengan dua parameter yaitu pin dan duty
- method ini bertujuan untuk menghasilkan gelombang pwm pada pin tertentu sesuai pin pada parameter yang diset. Pin yang diset akan menentukan bit mana yang akan diset pada register TCCR1A untuk menjadi 1 (apakah COM1A1/COM1B1/COM1C1). Gunanya adalah untuk mengontrol bagaimana Compare Output Pin terhubung dengan Timer1 / mengaktifkan pin output
- parameter duty berupa bilangan int 10 bit yaitu dari 0-1023, dimana 0  (0% duty) dan 1023 (100% duty)


## 4. void setPwmDuty(pin, duty)
- di method ini nilai pwmPeriod akan disimpan sebagai dutycycle, kemudian nilai dutycycle akan dikalikan dengan nilai parameter duty (hasilnya kembali akan disimpan dalam variabel dutycycle), lalu nilai dutycycle akan dishift kanan sebanyak 10 kali.
- Jika pin yang diset adalah pin A Timer1, maka nilai OCR1A akan sama dengan nilai dutyCycle, begitu pula dengan jika pin B maka register OCR1B nilainya akan sama dengan dutycycle


## 5. disablePwm(pin)
- pin output akan dinonaktifkan/ set 0 dengan perintah ~_BV(COM1...1) dimana register TCCR juga akan di 0 kan
