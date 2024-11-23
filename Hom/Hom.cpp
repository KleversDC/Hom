#include <iostream>
using namespace std;
class Human {
private:
    char* name;

public:
    Human() : name(nullptr) {}

    Human(const char* nameInput) {
        int length = 0;
        while (nameInput[length] != '\0') ++length;
        name = new char[length + 1];
        for (int i = 0; i < length; ++i) {
            name[i] = nameInput[i];
        }
        name[length] = '\0';
    }

    Human(const Human& other) {
        if (other.name) {
            int length = 0;
            while (other.name[length] != '\0') ++length;
            name = new char[length + 1];
            for (int i = 0; i < length; ++i) {
                name[i] = other.name[i];
            }
            name[length] = '\0';
        }
        else {
            name = nullptr;
        }
    }

    Human& operator=(const Human& other) {
        if (this != &other) {
            delete[] name;
            if (other.name) {
                int length = 0;
                while (other.name[length] != '\0') ++length;
                name = new char[length + 1];
                for (int i = 0; i < length; ++i) {
                    name[i] = other.name[i];
                }
                name[length] = '\0';
            }
            else {
                name = nullptr;
            }
        }
        return *this;
    }

    ~Human() {
        delete[] name;
    }

    void print() const {
        if (name) {
            cout << "Human: " << name << endl;
        }
        else {
            cout << "Human  unknown :" << endl;
        }
    }
};

class Apartment {
private:
    Human** residents;
    int capacity;
    int count;

public:
    Apartment(int capacityInput) : capacity(capacityInput), count(0) {
        residents = new Human * [capacity];
        for (int i = 0; i < capacity; ++i) {
            residents[i] = nullptr;
        }
    }

    Apartment(const Apartment& other) : capacity(other.capacity), count(other.count) {
        residents = new Human * [capacity];
        for (int i = 0; i < count; ++i) {
            residents[i] = new Human(*other.residents[i]);
        }
        for (int i = count; i < capacity; ++i) {
            residents[i] = nullptr;
        }
    }

    Apartment& operator=(const Apartment& other) {
        if (this != &other) {
            for (int i = 0; i < count; ++i) {
                delete residents[i];
            }
            delete[] residents;

            capacity = other.capacity;
            count = other.count;

            residents = new Human * [capacity];
            for (int i = 0; i < count; ++i) {
                residents[i] = new Human(*other.residents[i]);
            }
            for (int i = count; i < capacity; ++i) {
                residents[i] = nullptr;
            }
        }
        return *this;
    }

    ~Apartment() {
        for (int i = 0; i < count; ++i) {
            delete residents[i];
        }
        delete[] residents;
    }

    bool addResident(const Human& person) {
        if (count < capacity) {
            residents[count++] = new Human(person);
            return true;
        }
        return false;
    }

    void print() const {
        cout << "Apartment with" << count << " residents:" << endl;
        for (int i = 0; i < count; ++i) {
            residents[i]->print();
        }
    }
};

class House {
private:
    Apartment** apartments;
    int apartmentCount;

public:
    House(int apartmentCountInput, int apartmentCapacity) : apartmentCount(apartmentCountInput) {
        apartments = new Apartment * [apartmentCount];
        for (int i = 0; i < apartmentCount; ++i) {
            apartments[i] = new Apartment(apartmentCapacity);
        }
    }

    House(const House& other) : apartmentCount(other.apartmentCount) {
        apartments = new Apartment * [apartmentCount];
        for (int i = 0; i < apartmentCount; ++i) {
            apartments[i] = new Apartment(*other.apartments[i]);
        }
    }

    House& operator=(const House& other) {
        if (this != &other) {
            for (int i = 0; i < apartmentCount; ++i) {
                delete apartments[i];
            }
            delete[] apartments;

            apartmentCount = other.apartmentCount;

            apartments = new Apartment * [apartmentCount];
            for (int i = 0; i < apartmentCount; ++i) {
                apartments[i] = new Apartment(*other.apartments[i]);
            }
        }
        return *this;
    }

    ~House() {
        for (int i = 0; i < apartmentCount; ++i) {
            delete apartments[i];
        }
        delete[] apartments;
    }

    bool addResidentToApartment(int apartmentIndex, const Human& person) {
        if (apartmentIndex >= 0 && apartmentIndex < apartmentCount) {
            return apartments[apartmentIndex]->addResident(person);
        }
        return false;
    }

    void print() const {
        cout << "Hom  " << apartmentCount << " apartments:" << endl;
        for (int i = 0; i < apartmentCount; ++i) {
            cout << "apartments " << i + 1 << ":" << endl;
            apartments[i]->print();
        }
    }
};

int main() {
    House house(3, 2);

    Human john("Ivan");
    Human jane("Olena");
    Human bob("Bogdan");

    house.addResidentToApartment(0, john);
    house.addResidentToApartment(0, jane);
    house.addResidentToApartment(1, bob);

    house.print();
}

