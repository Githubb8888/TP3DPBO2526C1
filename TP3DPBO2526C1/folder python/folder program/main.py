from abc import ABC, abstractmethod


class Landmark:
    def __init__(self, name, type_, year_built):
        self.__name = name
        self.__type = type_
        self.__year_built = year_built

    def get_name(self):
        return self.__name

    def describe(self, indent=0):
        print(" " * indent + f"- {self.__name} ({self.__type}, {self.__year_built})")



class GeoEntity(ABC):
    def __init__(self, name, area, population):
        self._name = name
        self._area = area              
        self._population = population

    def get_name(self):
        return self._name

    def get_area(self):
        return self._area

    def get_population(self):
        return self._population

    def get_density(self):
        return self._population / self._area

    @abstractmethod
    def get_type(self):
        pass

    @abstractmethod
    def describe(self, indent=0):
        pass

    def _print_header(self, indent):
        print(" " * indent + f"[{self.get_type()}] {self._name}"
              f" | Luas: {self._area:.1f} km2 | Populasi: {self._population}")



class City(GeoEntity):
    def __init__(self, name, area, population, coastal):
        super().__init__(name, area, population)
        self.__coastal = coastal
        self.__landmarks = []          
        
    def add_landmark(self, name, type_, year_built):
        self.__landmarks.append(Landmark(name, type_, year_built))

    def get_type(self):
        return "Kota"

    def describe(self, indent=0):
        self._print_header(indent)
        print(" " * (indent + 2) + f"Kota pesisir: {'Ya' if self.__coastal else 'Tidak'}"
              f" | Landmark: {len(self.__landmarks)}")
        for lm in self.__landmarks:
            lm.describe(indent + 4)



class Country(GeoEntity):
    def __init__(self, name, area, population, capital):
        super().__init__(name, area, population)
        self.__capital = capital
        self.__cities = []             

    def add_city(self, name, area, population, coastal):
        self.__cities.append(City(name, area, population, coastal))

    def find_city(self, name):
        for c in self.__cities:
            if c.get_name() == name:
                return c
        return None

    def get_cities(self):
        return self.__cities

    def get_total_city_population(self):
        return sum(c.get_population() for c in self.__cities)

    def get_type(self):
        return "Negara"

    def describe(self, indent=0):
        self._print_header(indent)
        print(" " * (indent + 2) + f"Ibu kota: {self.__capital}"
              f" | Jumlah kota terdata: {len(self.__cities)}"
              f" | Total pop. kota terdata: {self.get_total_city_population()}")
        for c in self.__cities:
            c.describe(indent + 4)



class Continent(GeoEntity):
    def __init__(self, name, area, population):
        super().__init__(name, area, population)
        self.__countries = []          

    
    def add_country(self, name, area, population, capital):
        self.__countries.append(Country(name, area, population, capital))

    def find_country(self, name):
        for c in self.__countries:
            if c.get_name() == name:
                return c
        return None

    def get_countries(self):
        return self.__countries

    def get_type(self):
        return "Benua"

    def describe(self, indent=0):
        self._print_header(indent)
        print(" " * (indent + 2) + f"Jumlah negara terdata: {len(self.__countries)}")
        for c in self.__countries:
            c.describe(indent + 4)



def main():
    
    asia = Continent("Asia", 44579000, 4700000000)

    asia.add_country("Indonesia", 1904569, 278000000, "Jakarta")
    asia.add_country("Jepang", 377975, 124000000, "Tokyo")

    idn = asia.find_country("Indonesia")
    idn.add_city("Jakarta", 662, 10600000, True)
    idn.add_city("Bandung", 167, 2500000, False)
    idn.add_city("Surabaya", 351, 2900000, True)
    idn.find_city("Jakarta").add_landmark("Monas", "Monumen", 1975)
    idn.find_city("Bandung").add_landmark("Gedung Sate", "Bangunan Bersejarah", 1920)

    jpn = asia.find_country("Jepang")
    jpn.add_city("Tokyo", 2194, 14000000, True)
    jpn.add_city("Osaka", 225, 2700000, True)
    jpn.find_city("Tokyo").add_landmark("Tokyo Tower", "Menara", 1958)
    jpn.find_city("Osaka").add_landmark("Kastil Osaka", "Kastil", 1597)

    print("=" * 50)
    print("        DATA SEBELUM PENAMBAHAN")
    print("=" * 50)
    asia.describe()

    
    asia.add_country("Thailand", 513120, 71000000, "Bangkok")
    tha = asia.find_country("Thailand")
    tha.add_city("Bangkok", 1569, 10500000, True)
    tha.find_city("Bangkok").add_landmark("Wat Arun", "Kuil", 1700)

    idn.add_city("Yogyakarta", 32.5, 420000, False)
    idn.find_city("Yogyakarta").add_landmark("Malioboro", "Kawasan Wisata", 1758)
    idn.find_city("Bandung").add_landmark("Gedung Merdeka", "Bangunan Bersejarah", 1895)

    jpn.add_city("Kyoto", 827, 1450000, False)
    jpn.find_city("Kyoto").add_landmark("Kinkaku-ji", "Kuil", 1397)

    print("\n" + "=" * 50)
    print("        DATA SESUDAH PENAMBAHAN")
    print("=" * 50)
    asia.describe()

   
    print("\n" + "=" * 50)
    print("        RINGKASAN (POLIMORFISME via GeoEntity*)")
    print("=" * 50)
    semua = [asia]
    for c in asia.get_countries():
        semua.append(c)
        semua.extend(c.get_cities())

    print(f"{'Tipe':<8}{'Nama':<14}{'Populasi':>14}{'Kepadatan(/km2)':>18}")
    for g in semua:
        print(f"{g.get_type():<8}{g.get_name():<14}{g.get_population():>14}"
              f"{g.get_density():>18.1f}")


if __name__ == "__main__":
    main()