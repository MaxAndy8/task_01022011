/*Напишіть клас із методами, який описуватиме іони.Кожен іон
характеризується зарядом “ + ” або ” - ”;
валентністю: ціле значення від 1 до 7.
В цьому класі передбачте явно :
Конструктор і деструктор;
Конструктор переміщення;
Перевантажений оператор =
Створіть масив таких іонів : потім визначте перелік іонів, які
вступлять в реакцію(в реакцію вступають іони з протилежними
    знаками і однаковою валентністю) і перелік, які в реакцію не
    вступлять.Іони, які вступили в реакцію перемістіть за допомогою
    конструктора переміщення.*/

#include <iostream>
#include <vector>
#include <map>

class Ion {
private:
    int  valency   ;   // Валентність іону
    bool isPositive;   // Позначення позитивного чи негативного заряду

public:
    Ion() : valency(0), isPositive(false) {} // Конструктор по умолчанию
    // Конструктор з перевіркою валентності
    Ion(bool isPos, int v) : isPositive(isPos) {
        if (v >= 1 && v <= 7) {
            valency = v;
        }
        else {
            std::cerr << "Недійсне значення валентності. Встановлення валентності на 1." << std::endl;
            valency = 1;
        }
    }

    // Деструктор
    ~Ion() {
        std::cout << "Ion destroyed" << std::endl;
    }

    // Конструктор переміщення
    Ion(Ion&& other) noexcept : valency(other.valency), isPositive(other.isPositive) {
        other.valency    = 0    ; 
        other.isPositive = false;
        std::cout << "Ion moved" << std::endl;
    }

    // Перевантажений оператор =
    Ion& operator=(Ion&& other) noexcept {
        if (this != &other) {
            valency    = other.valency;
            isPositive = other.isPositive;
            other.valency = 0;
            other.isPositive = false;
        }
        std::cout << "Ion moved with operator=" << std::endl;
        return *this;
    }

    // Метод для отримання валентності
    int getValency() const {
        return valency;
    }

    // Метод для перевірки позитивного заряду
    bool isIonPositive() const {
        return isPositive;
    }

    // Метод для перевірки негативного заряду
    bool isIonNegative() const {
        return !isPositive;
    }

    // Перевантажений оператор порівняння для використання в std::map
    bool operator<(const Ion& other) const {
        return std::tie(isPositive, valency) < std::tie(other.isPositive, other.valency);
    }
    bool isValid() const {
        return (1 <= valency && valency <= 7);
    }

    // Перевантажений оператор <<
    friend std::ostream& operator<<(std::ostream& os, const Ion& ion) {
        os << "Ion:(" << (ion.isIonPositive() ? "+" : "-") << ion.getValency() << ")";
        return os;
    }
};

int main() {
    system("chcp 1251>nul");

    // Створення масиву іонів
    std::vector<Ion> ions;
    ions.emplace_back(true , 7);
    ions.emplace_back(true , 1);
    ions.emplace_back(false, 2);
    ions.emplace_back(true , 3);
    ions.emplace_back(false, 7);

    std::cout << " * * * * * * * * * * * * * * * * * * * * * * " << std::endl;
    std::cout << "\nВхідні Іони:" << std::endl;
    for (const Ion& ion : ions) {
        std::cout << ion << std::endl;
    }
    std::cout << " * * * * * * * * * * * * * * * * * * * * * * " << std::endl;

    // Комбінації іонів, які вступлять в реакцію
    std::map<Ion, Ion> reactingIons;

    // Перевірка на вступ до реакції
    for (Ion& ion : ions) {
        if (ion.isIonPositive() && ion.isValid()) {
            for (Ion& otherIon : ions) {
                if (otherIon.isIonNegative() && otherIon.isValid() && ion.getValency() == otherIon.getValency()) {
                    reactingIons[std::move(ion)] = std::move(otherIon);
                    break;
                }
            }
        }
    }

    // Перелік іонів, які не вступлять в реакцію
    std::vector<Ion> nonReactingIons;
    for (Ion& ion : ions) {
        if (ion.isValid()) {
            nonReactingIons.push_back(std::move(ion));
        }
    }


    // Переміщення іонів, які вступають в реакцію
    ions.clear();
    
    std::cout << " * * * * * * * * * * * * * * * * * * * * * * " << std::endl;
    // Вивід результатів
    std::cout << "Іони, що реагують:" << std::endl;
    for (const auto& pair : reactingIons) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }

    std::cout << "\nІони, що не реагують:" << std::endl;
    for (const Ion& ion : nonReactingIons) {
        std::cout << ion << std::endl;
    }
    std::cout << " * * * * * * * * * * * * * * * * * * * * * * " << std::endl;
    return 0;
}
