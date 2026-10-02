#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

class Landmark {
private:
    string name;
    string type;
    int yearBuilt;
public:
    Landmark(string n, string t, int y) : name(n), type(t), yearBuilt(y) {}
    string getName() const { return name; }
    void describe(int indent) const {
        cout << string(indent, ' ') << "- " << name << " (" << type
             << ", " << yearBuilt << ")" << endl;
    }
};

class GeoEntity {
protected:
    string name;
    double area;           
    long long population;
public:
    GeoEntity(string n, double a, long long p) : name(n), area(a), population(p) {}
    virtual ~GeoEntity() {}

    string getName() const { return name; }
    double getArea() const { return area; }
    long long getPopulation() const { return population; }

    virtual string getType() const = 0;                 
    virtual void describe(int indent = 0) const = 0;    

    double getDensity() const { return population / area; }

protected:
    void printHeader(int indent) const {
        cout << string(indent, ' ') << "[" << getType() << "] " << name
             << " | Luas: " << fixed << setprecision(1) << area << " km2"
             << " | Populasi: " << population << endl;
    }
};

class City : public GeoEntity {
private:
    bool coastal;
    vector<Landmark> landmarks;   
public:
    City(string n, double a, long long p, bool c) : GeoEntity(n, a, p), coastal(c) {}

    void addLandmark(string n, string t, int y) { landmarks.emplace_back(n, t, y); }

    string getType() const override { return "Kota"; }
    void describe(int indent = 0) const override {
        printHeader(indent);
        cout << string(indent + 2, ' ') << "Kota pesisir: " << (coastal ? "Ya" : "Tidak")
             << " | Landmark: " << landmarks.size() << endl;
        for (const Landmark& l : landmarks) l.describe(indent + 4);
    }
};


class Country : public GeoEntity {
private:
    string capital;
    vector<City> cities;       
public:
    Country(string n, double a, long long p, string cap)
        : GeoEntity(n, a, p), capital(cap) {}


    void addCity(string n, double a, long long p, bool coastal) {
        cities.emplace_back(n, a, p, coastal);
    }
    City* findCity(const string& n) {
        for (City& c : cities) if (c.getName() == n) return &c;
        return nullptr;
    }
    const vector<City>& getCities() const { return cities; }

    long long getTotalCityPopulation() const {
        long long total = 0;
        for (const City& c : cities) total += c.getPopulation();
        return total;
    }

    string getType() const override { return "Negara"; }
    void describe(int indent = 0) const override {
        printHeader(indent);
        cout << string(indent + 2, ' ') << "Ibu kota: " << capital
             << " | Jumlah kota terdata: " << cities.size()
             << " | Total pop. kota terdata: " << getTotalCityPopulation() << endl;
        for (const City& c : cities) c.describe(indent + 4);
    }
};


class Continent : public GeoEntity {
private:
    vector<Country> countries;  
public:
    Continent(string n, double a, long long p) : GeoEntity(n, a, p) {}

    
    void addCountry(string n, double a, long long p, string capital) {
        countries.emplace_back(n, a, p, capital);
    }
    Country* findCountry(const string& n) {
        for (Country& c : countries) if (c.getName() == n) return &c;
        return nullptr;
    }
    const vector<Country>& getCountries() const { return countries; }

    string getType() const override { return "Benua"; }
    void describe(int indent = 0) const override {
        printHeader(indent);
        cout << string(indent + 2, ' ') << "Jumlah negara terdata: " << countries.size() << endl;
        for (const Country& c : countries) c.describe(indent + 4);
    }
};

int main() {
    
    Continent asia("Asia", 44579000, 4700000000LL);

    asia.addCountry("Indonesia", 1904569, 278000000LL, "Jakarta");
    asia.addCountry("Jepang", 377975, 124000000LL, "Tokyo");


    asia.findCountry("Indonesia")->addCity("Jakarta", 662, 10600000LL, true);
    asia.findCountry("Indonesia")->addCity("Bandung", 167, 2500000LL, false);
    asia.findCountry("Indonesia")->addCity("Surabaya", 351, 2900000LL, true);
    asia.findCountry("Indonesia")->findCity("Jakarta")->addLandmark("Monas", "Monumen", 1975);
    asia.findCountry("Indonesia")->findCity("Bandung")->addLandmark("Gedung Sate", "Bangunan Bersejarah", 1920);

    asia.findCountry("Jepang")->addCity("Tokyo", 2194, 14000000LL, true);
    asia.findCountry("Jepang")->addCity("Osaka", 225, 2700000LL, true);
    asia.findCountry("Jepang")->findCity("Tokyo")->addLandmark("Tokyo Tower", "Menara", 1958);
    asia.findCountry("Jepang")->findCity("Osaka")->addLandmark("Kastil Osaka", "Kastil", 1597);

    cout << "==================================================" << endl;
    cout << "        DATA SEBELUM PENAMBAHAN" << endl;
    cout << "==================================================" << endl;
    asia.describe();

    asia.addCountry("Thailand", 513120, 71000000LL, "Bangkok");
    asia.findCountry("Thailand")->addCity("Bangkok", 1569, 10500000LL, true);
    asia.findCountry("Thailand")->findCity("Bangkok")->addLandmark("Wat Arun", "Kuil", 1700);

    asia.findCountry("Indonesia")->addCity("Yogyakarta", 32.5, 420000LL, false);
    asia.findCountry("Indonesia")->findCity("Yogyakarta")->addLandmark("Malioboro", "Kawasan Wisata", 1758);
    asia.findCountry("Indonesia")->findCity("Bandung")->addLandmark("Gedung Merdeka", "Bangunan Bersejarah", 1895);

    asia.findCountry("Jepang")->addCity("Kyoto", 827, 1450000LL, false);
    asia.findCountry("Jepang")->findCity("Kyoto")->addLandmark("Kinkaku-ji", "Kuil", 1397);

    cout << "\n==================================================" << endl;
    cout << "        DATA SESUDAH PENAMBAHAN" << endl;
    cout << "==================================================" << endl;
    asia.describe();

    cout << "\n==================================================" << endl;
    cout << "        RINGKASAN (POLIMORFISME via GeoEntity*)" << endl;
    cout << "==================================================" << endl;
    vector<const GeoEntity*> all;
    all.push_back(&asia);
    for (const Country& c : asia.getCountries()) {
        all.push_back(&c);
        for (const City& ct : c.getCities()) all.push_back(&ct);
    }
    cout << left << setw(8) << "Tipe" << setw(14) << "Nama"
         << right << setw(14) << "Populasi" << setw(18) << "Kepadatan(/km2)" << endl;
    for (const GeoEntity* g : all) {
        cout << left << setw(8) << g->getType() << setw(14) << g->getName()
             << right << setw(14) << g->getPopulation()
             << setw(18) << fixed << setprecision(1) << g->getDensity() << endl;
    }
    return 0;
}