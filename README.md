Tugas Praktikum 3 DPBO 2026

Janji Saya Bozorov Huseyn (NIM: 2521812) mengerjakan evaluasi Tugas Praktikum 3 dalam mata kuliah Desain dan Pemrograman Berbasis Objek untuk keberkahan-Nya maka saya tidak melakukan kecurangan seperti yang telah dispesifikasikan. Aamiin.

GeoEntity (Abstract Parent Class)
Base class for all geographical entities. Cannot be instantiated directly.
Attributes:
name: string representing the entity name.
area: double representing total area in square kilometers ($\text{km}^2$).
population: long or long long representing total population.

Methods:
getName(), getArea(), getPopulation(): attribute getters.
getDensity(): calculates population density as population divided by area.
getType() (Abstract): returns the entity type ("Continent", "Country", or "City").
describe(indent) (Abstract): prints complete data formatted with hierarchical indentation.

Continent (Child of GeoEntity)
Attributes:

countries: array, vector, or list containing Country objects.

Methods:

addCountry(...): instantiates a Country inside the Continent and stores it.
findCountry(name): searches for a country by name.
getCountries(): returns the list of countries.
getType(): override that returns "Continent".
describe(indent): override that prints continent data followed by all its countries.

Country (Child of GeoEntity)
Attributes:

capital: string representing the capital city name.
cities: array, vector, or list containing City objects.

Methods:

addCity(...): instantiates a City inside the Country and stores it.
findCity(name): searches for a city by name.
getCities(): returns the list of cities.
getTotalCityPopulation(): sums up the population of all recorded cities.
getType(): override that returns "Country".
describe(indent): override that prints country data followed by all its cities.

City (Child of GeoEntity)

Attributes:

coastal: boolean value set to true if it is a coastal city.
landmarks: array, vector, or list containing Landmark objects.

Methods:

addLandmark(name, type, year): instantiates a Landmark inside the City.
getType(): override that returns "City".
describe(indent): override that prints city data, coastal status, and landmark list.

Landmark (Independent Class)

Attributes:

name: string representing landmark name.
type: string representing type such as monument, temple, tower, etc.
yearBuilt: integer representing the year of construction.

Methods:

getName(): name getter.
describe(indent): prints a single line of landmark data.

Program Design Rationale
Program Design Rationale

Hierarchical Inheritance
A single parent GeoEntity is inherited by three children simultaneously: Continent, Country, and City. Continents, countries, and cities are all geographical entities sharing common traits like name, area, population, and population density calculations, which centralizes attributes to avoid code duplication. Polymorphism is used where each subclass implements its own type and description methods, and in the summary section of main, all objects are grouped into a single GeoEntity collection and handled uniformly. GeoEntity is abstract to prevent instantiation of generic, unclassified geographical entities.

Composition
A three-tier has-a or part-of relationship is modeled where Continent contains Country, Country contains City, and City contains Landmark. Part objects are created directly within the owner methods such as addCountry, addCity, and addLandmark. In C++, parts are stored by value in vectors, ensuring they are destroyed alongside the owner, while in Python parts belong exclusively to the owner instance. Kota is not a country, but a part of a country, making composition the correct relationship rather than inheritance.

Array of Objects
Three primary arrays and lists manage internal containment including vector of Country in Continent, vector of City in Country, and vector of Landmark in City. Additionally, main features a polymorphic collection of vector of pointers to const GeoEntity in C++ and a list in Python combining continents, countries, and cities.

Dataset
Initial Data includes countries Indonesia and Japan, cities Jakarta, Bandung, Surabaya, Tokyo, Osaka, and landmarks Monas, Gedung Sate, Tokyo Tower, Osaka Castle. Additional Data includes country Thailand, cities Yogyakarta, Kyoto, Bangkok, and landmarks Gedung Merdeka in Bandung, Malioboro, Kinkaku-ji, Wat Arun. Data is static and written directly in main with approximate figures for practice purposes.



