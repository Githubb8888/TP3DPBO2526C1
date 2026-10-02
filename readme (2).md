Tugas Praktikum 3 DPBO 2026

Janji Saya Bozorov Huseyn (NIM: 2521812) mengerjakan evaluasi Tugas Praktikum 3 dalam mata kuliah Desain dan Pemrograman Berbasis Objek untuk keberkahan-Nya maka saya tidak melakukan kecurangan seperti yang telah dispesifikasikan. Aamiin.

## 2. Diagram Program

## 3. Penjelasan Atribut & Method Kelas

### 3.1 `GeoEntity` (Abstract Parent)
* **Atribut**: `name` (string), `area` (double), `population` (long/int).
* **Method**: Getter (`getName`, `area`, `population`), `getDensity()` (kepadatan), `getType()` (abstrak), `describe()` (abstrak), `printHeader()`.

### 3.2 `Continent` (Child)
* **Atribut**: `countries` (array/vector/list `Country`).
* **Method**: `addCountry()`, `findCountry()`, `getCountries()`, override `getType()` & `describe()`.

### 3.3 `Country` (Child)
* **Atribut**: `capital` (string), `cities` (array/vector/list `City`).
* **Method**: `addCity()`, `findCity()`, `getCities()`, `getTotalCityPopulation()`, override `getType()` & `describe()`.

### 3.4 `City` (Child)
* **Atribut**: `coastal` (bool), `landmarks` (array/vector/list `Landmark`).
* **Method**: `addLandmark()`, override `getType()` & `describe()`.

### 3.5 `Landmark` (Independent Class)
* **Atribut**: `name`, `type`, `yearBuilt`.
* **Method**: `getName()`, `describe()`.

---

## 4. Desain Program

* **Inheritance**: *Hierarchical* (`GeoEntity` diwarisi `Continent`, `Country`, `City`). Menghindari duplikasi kode dan menerapkan polimorfisme pada method `getType()` & `describe()`.
* **Composition**: Relasi *has-a* berlapis (`Continent` $\to$ `Country` $\to$ `City` $\to$ `Landmark`). Objek bagian dibuat di dalam method pemilik (`add...`) sehingga siklus hidupnya diatur oleh pemilik.
* **Array of Object**: Menggunakan `vector`/`list` untuk relasi hierarki serta array polimorfik bertipe `GeoEntity`.
* **Data**: Data awal (Indonesia, Jepang, dll.) ditambah data baru (Thailand, Yogyakarta, dll.) secara statis di `main`.

---

## 5. Alur Program

1. Buat objek `Continent` (Asia).
2. Tambah data awal (Negara, Kota, Landmark).
3. Cetak data awal lewat `asia.describe()` secara berjenjang.
4. Tambah data baru (Thailand, Yogyakarta, Kyoto, dll.).
5. Cetak data sesudah penambahan.
6. Cetak ringkasan polimorfisme dalam bentuk tabel menggunakan array `GeoEntity`.

---

## 6. Cara Menjalankan

**C++**
```bash
cd CPP/Program
g++ -std=c++17 -o geo main.cpp
./geo
```

**Python**
```bash
cd Python/Program
python main.py
