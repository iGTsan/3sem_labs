#include "dialog.h"
#include "handle.h"
#include "dice.h"

namespace Dialog {
    void throw_dice(Dice_vector &vector) {
        vector.throw_dice();
        cout << "Dices were thrown" << endl;
        display_dice(vector);
    }

    void insert_dice(Dice_vector &vector) {
        vector.insert_dice();
        display_dice(vector);
    }

    void remove_dice(Dice_vector &vector) {
        int number = read_int("number");
        vector.remove_dice(number);
        cout << "Dice was removed" << endl;
        display_dice(vector);
    }

    void remove_all_dices(Dice_vector &vector) {
        vector.remove_all_dices();
        cout << "All dices were removed" << endl;
    }

    void display_dice(Dice_vector &vector) {
        cout << vector;
    }

    void find_dice(Dice_vector &vector) {
        int number = read_int("number");
        cout << vector[number] << " <- Your dice #" << number << endl;
    }

    void sum_all_dices(Dice_vector &vector) {
        cout << *vector << " <- Sum of all dices" << endl;
    }

    void check_for_coincidences(Dice_vector &vector) {
        int check = vector.check_for_coincidences();
        if (check == 1 || vector.get_amount() == 0 || vector.get_amount() == 1) {
            cout << "Coincidences not found" << endl;
        } else {
            cout << "There is at least one coincidence" << endl;
        }
    }

    void insert_with_value(Dice_vector &vector) {
        int value = read_int("value to insert");
        vector += value;
        display_dice(vector);
    }

    void sum_with_group(Dice_vector &vector) {
        int amount = read_int("amount of dices in new group");
        Dice_vector temp_vector(amount);
        for (int i = 0; i < amount; ++i) {
            temp_vector.insert_dice();
        }
        temp_vector.throw_dice();
        cout << "New group: " << endl;
        display_dice(temp_vector);
        cout << "Do you want to add new dices to existing group? (0 - yes, 1 - no)" << endl;
        int check = read_int("yes or no");
        if (check == 1) {
            return;
        }
        Dice_vector a(500);

        a = vector + temp_vector;
        display_dice(a);
    }

    void create_new_group(Dice_vector &vector) {
        int count = read_int("amount of new group of dices");
        vector.remove_all_dices();
        for (int i = 0; i < count; ++i) {
            cout << "Enter element #" << i + 1 << ": ";
            cin >> vector;
            cout << vector;
        }
    }

    void menu() {
        cout << "1. Test []" << endl;
        cout << "2. Test *" << endl;
        cout << "3. Test +=" << endl;
        cout << "4. Test =" << endl;
        cout << "5. Test = and +" << endl;
        cout << "6. Test << and >>" << endl;
        cout << "7. Test copy constructor" << endl;
        cout << "8. Test move constructor" << endl;
        cout << "9. Test move assigment" << endl;
        cout << "0. Exit" << endl;
    }

    void test1(Dice_vector &vector) {
        find_dice(vector);
    }

    void test2(Dice_vector &vector) {
        sum_all_dices(vector);
    }

    void test3(Dice_vector &vector) {
        insert_with_value(vector);
    }

    void test4(Dice_vector &vector) {
        Dice_vector dice_vector(100);
        dice_vector = vector;
        display_dice(dice_vector);
    }

    void test5(Dice_vector &vector) {
        sum_with_group(vector);
    }

    void test6(Dice_vector &vector) {
        create_new_group(vector);
    }

    void test7(Dice_vector &vector) {
        Dice_vector dice_vector(vector);
        cout << dice_vector;
    }

    void test8(Dice_vector &vector) {
        Dice_vector dice_vector(std::move(vector));
        cout << dice_vector;
    }

    void test9(Dice_vector &vector) {
        Dice_vector dice_vector(100);
        dice_vector = std::move(vector);
        cout << dice_vector;
    }

    void test_operators(Dice_vector &vector) {
        void (*foo[])(Dice_vector &) = {nullptr, test1, test2, test3, test4, test5,
                                        test6, test7, test8, test9};
        while (1) {
            menu();
            int number = read_int(">");
            if (number == 0) {
                break;
            }
            foo[number](vector);
        }
    }
}
