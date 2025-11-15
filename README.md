# Philosophers — Mandatory Part
*(Dining Philosophers Problem with Threads & Mutexes)*

## 1. Proje Açıklaması

Bu proje, klasik **Dining Philosophers** probleminin **C dili**, **threads** ve **mutex** kullanılarak simüle edilmesidir.  
Amaç, bir grup filozofun aynı anda yemek yeme, düşünme ve uyuma döngülerini **deadlock**, **race condition** ve **data race** oluşturmadan yönetmektir.

Her filozofun hayatta kalabilmesi için zamanında yemek yemesi gerekir. Eğer bir filozof `time_to_die` süresi içinde yemek yemeye başlamazsa **ölür** ve simülasyon durur.

## 2. Programın Çalışma Mantığı

- Her filozof bir **thread** olarak temsil edilir.
- Masada, filozof sayısı kadar **fork (çatal)** bulunur.
- Her filozofun:
  - Solunda bir çatal
  - Sağında bir çatal vardır.
- Yemek yemek için bir filozof **iki çatalı birden** eline almalıdır.
- Çatal durumları birer **pthread_mutex_t** ile korunur.
- Filozofların yaşam döngüsü:

  1. Çatal(ları) alır  
  2. Yer  
  3. Çatal(ları) bırakır  
  4. Uyur  
  5. Düşünür  

- Simülasyon şu durumlarda sona erer:
  - Bir filozof ölür.
  - Opsiyonel argüman verildiyse ve **tüm filozoflar belirtilen sayıda yemek yemişse**.

## 3. Kullanım

### 3.1. Derleme

```
make
```

### 3.2. Çalıştırma

```
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

### 3.3. Örnekler

```
./philo 4 800 200 200
./philo 5 800 200 200 5
```

## 4. Argümanlar

| Argüman | Açıklama |
|--------|----------|
| `number_of_philosophers` | Filozof (ve çatal) sayısı |
| `time_to_die` | Bu süre içinde yemek yemeyen filozof ölür |
| `time_to_eat` | Yemek yeme süresi |
| `time_to_sleep` | Uyuma süresi |
| `number_of_times_each_philosopher_must_eat` | (Opsiyonel) Her filozof bu sayıya ulaşırsa simülasyon biter |

## 5. Log Formatı

```
timestamp X has taken a fork  
timestamp X is eating  
timestamp X is sleeping  
timestamp X is thinking  
timestamp X died
```

- Ölüm mesajı **10 ms içinde** yazılmalıdır.
- Mesajlar çakışmamalıdır (mutex ile korunmalıdır).

## 6. Kullanılan Fonksiyonlar

- memset  
- printf  
- malloc / free  
- write  
- usleep  
- gettimeofday  
- pthread_create / pthread_detach / pthread_join  
- pthread_mutex_init / destroy / lock / unlock  

## 7. Kurallar

- **Global değişken yasak.**  
- Tüm malloc bellekleri free edilmelidir.  
- Data race ve deadlock olmamalıdır.  
- Makefile: `NAME`, `all`, `clean`, `fclean`, `re` kurallarını içermelidir.  
- Derleyici: `cc`, flag’ler: `-Wall -Wextra -Werror`.

## 8. Proje Yapısı (Öneri)

```
philo/
├─ Makefile
├─ philo.h
├─ main.c
├─ init.c
├─ threads.c
├─ routine.c
├─ time.c
├─ print.c
└─ utils.c
```

## 9. Test Önerileri

```
./philo 1 800 200 200
./philo 5 600 150 150 3
./philo 200 800 200 200
```
