#include <iostream>
#include <string>
#include <memory>

class Pet {
    public:
    virtual ~Pet() = default;
    virtual void express () const = 0;
    virtual std::string getName() const = 0;
    virtual int getAge() const = 0;
    virtual int getAgeInHumanYears() const = 0;
};

class Animal: public Pet {
    protected:
    std::string name;
    int age;
    public:
    Animal(std::string name, int age) : name(std::move(name)), age(age) {}
    void happyBirthday() {
        age++;
    }
    std::string getName() const override {
        return name;
    }
    int getAge() const override {
        return age;
    }
    void express () const override = 0;
    int getAgeInHumanYears() const override = 0;
};

class Parrot : public Animal {
    public:
    Parrot(std::string name, int age) : Animal(std::move(name), age) {}
    int getAgeInHumanYears() const override {
        return age * 5;
    }
    void express() const override {
    std::cout << name << ": \"hello!\"\n" <<
        R"(   \
   (o>
\\_//)
 \_/_)
  _|_)" << "\n";
    }
};

class Turtle : public Animal {
    public:
    Turtle(std::string name, int age) : Animal(std::move(name), age) {}
    int getAgeInHumanYears() const override {
        return age * 21 / 4;
    }
    void express() const override {
        std::cout << R"(  _____     ____
 /      \  |  o |
|        |/ ___\|
|_________/
|_|_| |_|_|)" << "\n";
    }
};

class Person {
    protected:
    std::string name;
    std::shared_ptr<Pet> pet;
    public:
    explicit Person(std::string name) : name(std::move(name)), pet(nullptr) {}
    Person(std::string name, std::shared_ptr<Pet> pet) : name(std::move(name)), pet(std::move(pet)) {}

    void setPet(std::shared_ptr<Pet> pet) {
        this->pet = std::move(pet);
    }
    void getPetInfo() const {
        std::cout << "--------------------\n";
        if (pet == nullptr) {
            std::cout << name << ": has no pet yet\n";
        }
        else {
            std::cout<< "Pet for " << name << " is named " << pet->getName()<< "\n";
            std::cout << "Age: " << pet->getAge() << " year(s), about "<< pet->getAgeInHumanYears() << " human years\n";
            std::cout << "And it expresses itself like this:\n";
            pet->express();
        }
        std::cout << "--------------------\n";
    }
};

int main() {
    auto kez = std::make_shared<Parrot>("Kez", 3);
    auto tortilla = std::make_shared<Turtle>("Tortilla", 6);

    Person dima("Dima", kez);
    dima.getPetInfo();

    Person vanya("Vanya", tortilla);
    vanya.getPetInfo();

    Person kirill("Kirill");
    kirill.getPetInfo();

    kirill.setPet(tortilla);
    kirill.getPetInfo();

    tortilla->happyBirthday();
    vanya.getPetInfo();

    return 0;
}