#ifndef CLASSES_ADDITIONAL_CLASSES_H_
#define CLASSES_ADDITIONAL_CLASSES_H_

namespace game_objects {
	typedef struct tower_chars {
		const int recoil;
		const int cost;
		const int radius;
		const int damage;
	} tower_chars;

	typedef struct  castle_chars {
		const int profit;
		const int cost;
		const int max_health;
		const int repair_speed;
	} castle_chars;

	typedef struct aura {
		int health = 0;
		int speed = 0;
		int regeneration = 0;
		struct aura& operator +=(aura& other) {
			health += other.health;
			speed += other.speed;
			regeneration += other.regeneration;
			return (*this);
		}
		struct aura& operator -=(aura& other) {
			health -= other.health;
			speed -= other.speed;
			regeneration -= other.regeneration;
			return (*this);
		}
	} aura;


	typedef struct enemy_out {
		const int time;
		const int type;
		enemy_out(int _time, int _type) : time(_time), type(_type) {};
	} enemy_out;
}



#endif