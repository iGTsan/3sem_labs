#include "dice.h"
#include <iostream>


int *realloc_array(int *vector, int max_size) {
    int *temp_array = new int[max_size + 1];
    for (int i = 0; i < max_size; ++i) {
        temp_array[i] = vector[i];
    }
    delete[]vector;
    return temp_array;
}

namespace DiceSpace {
    Dice_vector::Dice_vector(int n) {
        max_size = n;
        if (max_size < 1) {
            throw ::std::logic_error("Invalid max size");
        }
        amount = 0;
        dice_vector = new int[max_size];
        for (int i = 0; i < max_size; ++i) {
            dice_vector[i] = 0;
        }
        cout << "Constructor was called" << endl;
    }

    Dice_vector::Dice_vector(const Dice_vector &vector) {
        max_size = vector.max_size;
        dice_vector = new int[max_size];
        for (int i = 0; i < max_size; ++i) {
            dice_vector[i] = vector.dice_vector[i];
        }
        amount = vector.amount;

        cout << "Copy constructor was called " << endl;
    }


    Dice_vector::Dice_vector(Dice_vector &&vector) {
        max_size = vector.max_size;
        dice_vector = new int[max_size];
        for (int i = 0; i < max_size; ++i) {
            dice_vector[i] = vector.dice_vector[i];
        }
        amount = vector.amount;

        vector.dice_vector = nullptr;
        vector.amount = 0;
        vector.max_size = 0;

        cout << "Move constructor was called " << endl;
    }

    int Dice_vector::get_max_size() const {
        return max_size;
    }

    int *Dice_vector::get_dice_vector() const {
        return dice_vector;
    }

    int Dice_vector::get_value(int number) const {
        return dice_vector[number];
    }

    void Dice_vector::insert_value(int value) {
        dice_vector[amount - 1] = value;
    }

    int Dice_vector::get_amount() const {
        return amount;
    }

    void Dice_vector::throw_dice() {
        srand(time(NULL));
        for (int i = 0; i < amount; ++i) {
            if (dice_vector[i] != 0) {
                dice_vector[i] = rand() % 6 + 1;
            }
        }
    }

    void Dice_vector::insert_dice() {
        srand(time(NULL));
        if (amount == max_size) {
            dice_vector = realloc_array(dice_vector, max_size);
            dice_vector[max_size] = rand() % 6 + 1;
            max_size++;
        } else {
            dice_vector[amount] = rand() % 6 + 1;
        }
        amount++;
    }

    void Dice_vector::remove_dice(int number) {
        int j = 0;
        if (amount < 1) {
            throw ::std::logic_error("There is no dices");
        }
        if (number < 1 || number > amount) {
            throw ::std::logic_error("Dice not found");
        }
        for (int i = 0; i < max_size; i++) {
            if (i == number - 1) {
                i++;
            }
            dice_vector[j] = dice_vector[i];
            j++;
        }
        dice_vector[max_size - 1] = 0;
        amount--;
    }

    void Dice_vector::remove_all_dices() {
        amount = 0;
        for (int i = 0; i < max_size; ++i) {
            dice_vector[i] = 0;
        }
    }

    int Dice_vector::find_dice(int number) const {
        if (number < 1 || number > amount) {
            throw ::std::logic_error("Dice not found");
        }
        return dice_vector[number - 1];
    }

    int Dice_vector::sum_all_dices() const {
        int sum = 0;
        for (int i = 0; i < amount; ++i) {
            sum = sum + dice_vector[i];
        }
        return sum;
    }

    int Dice_vector::check_for_coincidences() const {
        for (int i = 0; i < amount; ++i) {
            for (int j = 1; j < amount; ++j) {
                if (i == j) {
                    continue;
                }
                if (dice_vector[j] == dice_vector[i]) {
                    return 0;
                }
            }
        }
        return 1;
    }

    Dice_vector::~Dice_vector() {
        cout << "Destructor was called" << endl;
        delete[]dice_vector;
    }

    Dice_vector Dice_vector::operator+(const Dice_vector &vector) {
        Dice_vector temp(this->max_size + vector.amount);
        temp.dice_vector = realloc_array(temp.dice_vector, this->max_size);
        for (int i = 0; i < this->max_size; ++i) {
            temp.dice_vector[i] = this->dice_vector[i];
        }
        for (int i = 0; i < vector.amount; ++i) {
            temp.dice_vector[i + this->amount] = vector.dice_vector[i];
        }
        temp.amount = this->amount + vector.amount;
        for (int i = temp.amount; i < temp.max_size; i++) {
            temp.dice_vector[i] = 0;
        }
        cout << "Overloaded operator + was called " << endl;
        return temp;
    }

    int Dice_vector::operator[](int value) {
        cout << "Overloaded operator [] was called " << endl;
        return this->dice_vector[value - 1];
    }

    int Dice_vector::operator*() {
        cout << "Overloaded operator * was called " << endl;
        return this->sum_all_dices();
    }

    Dice_vector &Dice_vector::operator+=(int value) {
        if (value < 0 || value > 6) {
            throw ::std::invalid_argument("Invalid value (higher than 6 or lower than 1)");
        }
        insert_dice();
        insert_value(value);
        cout << "Overloaded operator += was called " << endl;
        return *this;
    }

    Dice_vector &Dice_vector::operator=(const Dice_vector &vector) {
        if (this != &vector) {
            this->max_size = vector.max_size;
            dice_vector = realloc_array(this->dice_vector, vector.max_size);
            for (int i = 0; i < this->max_size; ++i) {
                dice_vector[i] = vector.dice_vector[i];
            }
            amount = vector.amount;

            cout << "Overloaded operator = (copy assigment) was called " << endl;
        }
        return *this;
    }

    Dice_vector &Dice_vector::operator=(Dice_vector &&vector) {
        if (this != &vector) {
            this->max_size = vector.max_size;
            this->dice_vector = realloc_array(this->dice_vector, vector.max_size);
            for (int i = 0; i < this->max_size; ++i) {
                this->dice_vector[i] = vector.dice_vector[i];
            }
            this->amount = vector.amount;

            vector.dice_vector = nullptr;
            vector.amount = 0;
            vector.max_size = 0;

            cout << "Overloaded operator = (move assigment) was called " << endl;
        }
        return *this;
    }
}

std::ostream &operator<<(std::ostream &ostream, const DiceSpace::Dice_vector &vector) {
    for (int i = 0; i < vector.get_max_size(); ++i) {
        if (vector.get_value(i) != 0) {
            ostream << i + 1 << ": " << "[" << vector.get_value(i) << "]" << endl;
        }
    }
    cout << "Overloaded operator << was called" << endl;
    return ostream;
}

std::istream &operator>>(std::istream &istream, DiceSpace::Dice_vector &vector) {
    int value = 0;
    istream >> value;
    if (value < 1 || value > 6) {
        throw ::std::logic_error("Invalid dice value");
    }
    vector.insert_dice();
    vector.insert_value(value);
    cout << "Overloaded operator >> was called" << endl;
    return istream;
}