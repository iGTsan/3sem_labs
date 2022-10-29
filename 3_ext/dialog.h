#ifndef DIALOG_H
#define DIALOG_H

#include "dice.h"

using namespace DiceSpace;

namespace Dialog {
    void throw_dice(Dice_vector &vector);

    void insert_dice(Dice_vector &vector);

    void remove_dice(Dice_vector &vector);

    void remove_all_dices(Dice_vector &vector);

    void display_dice(Dice_vector &vector);

    void find_dice(Dice_vector &vector);

    void sum_all_dices(Dice_vector &vector);

    void check_for_coincidences(Dice_vector &vector);

    void insert_with_value(Dice_vector &vector);

    void sum_with_group(Dice_vector &vector);

    void test_operators(Dice_vector &vector);

    void create_new_group(Dice_vector &vector);
}

#endif //DIALOG_H
