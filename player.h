#pragma once
#include <algorithm>

class Player {
public:
	explicit Player(int maxHp = 20) : hp(maxHp), maxHp(maxHp) {}

	int HP() const { return hp; }
	int maxHP() const { return maxHp; }
	bool IsDead() const { return hp <= 0; }

	void Damage(int amount) {
		hp = std::max(0, hp - amount);
	}
	void Heal(int amount) {
		hp = std::min(maxHp, hp + amount);
	}
	void Reset() {
		hp = maxHp;
	}

private:
	int hp;
	int maxHp;
};