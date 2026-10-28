/*
 * Zoo：用多态让不同种类的动物依次叫一次
 * （二）新增 Bird、WolfDog 时只需要继承 Animal，Zoo 类不用修改
 */
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

class Animal {
public:
    explicit Animal(std::string animalName) : name(std::move(animalName)) {
    }

    virtual ~Animal() = default;

    virtual void speak() const = 0;

protected:
    std::string name;
};

class Dog : public Animal {
public:
    explicit Dog(std::string animalName) : Animal(std::move(animalName)) {
    }

    void speak() const override {
        std::cout << name << "：汪汪汪！" << std::endl;
    }
};

class Cat : public Animal {
public:
    explicit Cat(std::string animalName) : Animal(std::move(animalName)) {
    }

    void speak() const override {
        std::cout << name << "：喵喵喵！" << std::endl;
    }
};

class Zoo {
public:
    void add(std::unique_ptr<Animal> animal) {
        animals.push_back(std::move(animal));
    }

    void speakAll() const {
        for (const auto &animal : animals) {
            animal->speak();
        }
    }

private:
    std::vector<std::unique_ptr<Animal>> animals;
};

class Bird : public Animal {
public:
    explicit Bird(std::string animalName) : Animal(std::move(animalName)) {
    }

    void speak() const override {
        std::cout << name << "：叽叽喳喳！" << std::endl;
    }
};

class WolfDog : public Dog {
public:
    explicit WolfDog(std::string animalName) : Dog(std::move(animalName)) {
    }

    void speak() const override {
        std::cout << name << "：嗷呜——！" << std::endl;
    }
};

int main() {
    Zoo zoo;
    zoo.add(std::unique_ptr<Animal>(new Dog("旺财")));
    zoo.add(std::unique_ptr<Animal>(new Cat("咪咪")));
    zoo.add(std::unique_ptr<Animal>(new Bird("小黄")));
    zoo.add(std::unique_ptr<Animal>(new WolfDog("大黄")));

    zoo.speakAll();
    return 0;
}
