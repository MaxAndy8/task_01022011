/*�������� ���� �� ��������, ���� ����������� ����.����� ���
��������������� ������� � + � ��� � - �;
����������: ���� �������� �� 1 �� 7.
� ����� ���� ���������� ���� :
����������� � ����������;
����������� ����������;
�������������� �������� =
������� ����� ����� ���� : ���� �������� ������ ����, ��
��������� � �������(� ������� ��������� ���� � ������������
    ������� � ��������� ����������) � ������, �� � ������� ��
    ���������.����, �� �������� � ������� ��������� �� ���������
    ������������ ����������.*/

#include <iostream>
#include <vector>
#include <map>

class Ion {
private:
    int  valency   ;   // ���������� ����
    bool isPositive;   // ���������� ����������� �� ����������� ������

public:
    Ion() : valency(0), isPositive(false) {} // ����������� �� ���������
    // ����������� � ��������� ����������
    Ion(bool isPos, int v) : isPositive(isPos) {
        if (v >= 1 && v <= 7) {
            valency = v;
        }
        else {
            std::cerr << "������� �������� ����������. ������������ ���������� �� 1." << std::endl;
            valency = 1;
        }
    }

    // ����������
    ~Ion() {
        std::cout << "Ion destroyed" << std::endl;
    }

    // ����������� ����������
    Ion(Ion&& other) noexcept : valency(other.valency), isPositive(other.isPositive) {
        other.valency    = 0    ; 
        other.isPositive = false;
        std::cout << "Ion moved" << std::endl;
    }

    // �������������� �������� =
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

    // ����� ��� ��������� ����������
    int getValency() const {
        return valency;
    }

    // ����� ��� �������� ����������� ������
    bool isIonPositive() const {
        return isPositive;
    }

    // ����� ��� �������� ����������� ������
    bool isIonNegative() const {
        return !isPositive;
    }

    // �������������� �������� ��������� ��� ������������ � std::map
    bool operator<(const Ion& other) const {
        return std::tie(isPositive, valency) < std::tie(other.isPositive, other.valency);
    }
    bool isValid() const {
        return (1 <= valency && valency <= 7);
    }

    // �������������� �������� <<
    friend std::ostream& operator<<(std::ostream& os, const Ion& ion) {
        os << "Ion:(" << (ion.isIonPositive() ? "+" : "-") << ion.getValency() << ")";
        return os;
    }
};

int main() {
    system("chcp 1251>nul");

    // ��������� ������ ����
    std::vector<Ion> ions;
    ions.emplace_back(true , 7);
    ions.emplace_back(true , 1);
    ions.emplace_back(false, 2);
    ions.emplace_back(true , 3);
    ions.emplace_back(false, 7);

    std::cout << " * * * * * * * * * * * * * * * * * * * * * * " << std::endl;
    std::cout << "\n����� ����:" << std::endl;
    for (const Ion& ion : ions) {
        std::cout << ion << std::endl;
    }
    std::cout << " * * * * * * * * * * * * * * * * * * * * * * " << std::endl;

    // ��������� ����, �� ��������� � �������
    std::map<Ion, Ion> reactingIons;

    // �������� �� ����� �� �������
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

    // ������ ����, �� �� ��������� � �������
    std::vector<Ion> nonReactingIons;
    for (Ion& ion : ions) {
        if (ion.isValid()) {
            nonReactingIons.push_back(std::move(ion));
        }
    }


    // ���������� ����, �� ��������� � �������
    ions.clear();
    
    std::cout << " * * * * * * * * * * * * * * * * * * * * * * " << std::endl;
    // ���� ����������
    std::cout << "����, �� ��������:" << std::endl;
    for (const auto& pair : reactingIons) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }

    std::cout << "\n����, �� �� ��������:" << std::endl;
    for (const Ion& ion : nonReactingIons) {
        std::cout << ion << std::endl;
    }
    std::cout << " * * * * * * * * * * * * * * * * * * * * * * " << std::endl;
    return 0;
}
