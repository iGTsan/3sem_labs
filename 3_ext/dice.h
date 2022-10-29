#ifndef DICE_H
#define DICE_H

#include <iostream>
#include <vector>
#include <ctime>


using namespace std;

int *realloc_array(int *vector, int max_size);


namespace DiceSpace {
    class Dice_vector {
    private:
        int max_size;
        int amount;
        int *dice_vector;

    public:

        Dice_vector(int n);

        Dice_vector(const Dice_vector &vector);

        Dice_vector(Dice_vector &&vector);

        int get_max_size() const;

        int *get_dice_vector() const;

        int get_value(int number) const;

        int get_amount() const;

        void insert_value(int value);

        void throw_dice();

        void insert_dice();

        void remove_dice(int number);

        void remove_all_dices();

        int find_dice(int number) const;

        int sum_all_dices() const;

        int check_for_coincidences() const;

        int operator[](int value);

        int operator*();

        Dice_vector &operator+=(int value);

        Dice_vector operator+(const Dice_vector &vector);

        Dice_vector &operator=(const Dice_vector &vector);

        Dice_vector &operator=(Dice_vector &&vector);

        ~Dice_vector();
    };
}

std::ostream &operator<<(std::ostream &os, const DiceSpace::Dice_vector &vector);

std::istream &operator>>(std::istream &istream, DiceSpace::Dice_vector &vector);


#endif //DICE_H
