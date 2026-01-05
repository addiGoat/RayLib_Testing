#pragma once
#include "raylib.h"
#include <iostream>
#include <algorithm>



class Player {
public:
	explicit Player(int maxHp = 20) : hp(maxHp), maxHp(maxHp) {}



	int weaponDamage = 0;
	bool weaponRecentlyEquipped = false;

	int HP() const { return hp; }
	int maxHP() const { return maxHp; }
	bool IsDead() const { return hp <= 0; }
	int WeaponDamage() const { return weaponDamage; }
	

	// Being replaced by Attack method
	//void Damage(int amount) { 
	//	hp = std::max(0, hp - amount);
	//}

	void Attack(int amount) {

		int monsterDmg = amount;


		// Weapon equipped
		if (weaponDamage != 0) {

			// First attack after equipping weapon
			if (weaponRecentlyEquipped) {
				weaponRecentlyEquipped = false;

				// If attack damage is higher than weapon damage, apply remaining damage to player
				if (amount > weaponDamage) {
					hp = std::max(0, hp - (amount - weaponDamage));
					weaponDamage = amount; return;
				}
			}

			// Subsequent attacks
			else if (!weaponRecentlyEquipped) {

				// If attack damage is higher than or equal to weapon damage, force player to fight barehanded
				if (amount >= weaponDamage) {
					hp = std::max(0, hp - amount); return; // Full damage applied to player
				}
			}
			weaponDamage = amount;
		}


		// No weapon equipped
		else {
			hp = std::max(0, hp - amount);
		}
	}
	void Heal(int amount) {
		hp = std::min(maxHp, hp + amount);
	}
	void Equip(int dmg) {
		weaponDamage = dmg;
		weaponRecentlyEquipped = true;
	}
	void Reset() {
		hp = maxHp;
	}

	void DrawEquippedWeapon() {		

		Color weaponColor = BLUE;
		if (!weaponRecentlyEquipped) weaponColor = RED;
		DrawRectangleRec(weaponRect, weaponColor);

		int weaponFontSize = 22;

		int typeTextW = MeasureText("Weapon", weaponFontSize);

		float cardCenterX = weaponRect.x + weaponRect.width * 0.5f;
		float cardCenterY = weaponRect.y + weaponRect.height;

		float typeTextX = cardCenterX - typeTextW * 0.5f;
		float typeTextY = cardCenterY - weaponFontSize - 10;

		DrawText("Weapon", (int)typeTextX, (int)typeTextY, weaponFontSize, BLACK); // Draw weapon type

		const char* rankText;


		int rankFontSize = 72;
		if (weaponDamage == 14) { rankText = "A"; }
		else rankText = TextFormat("%i", weaponDamage);

		int textW = MeasureText(rankText, rankFontSize);

		float centerX = weaponRect.x + weaponRect.width * 0.5f;
		float centerY = weaponRect.y + weaponRect.height * 0.5f;

		float textX = centerX - textW * 0.5f;
		float textY = centerY - rankFontSize * 0.5f;


		DrawText(rankText, (int)textX, (int)textY, rankFontSize, BLACK); // Draw card rank
		
	}

private:
	int hp;
	int maxHp;

	float weaponIconWidth = 100.0f;
	float weaponIconHeight = 150.0f;

	float weaponIconX = 1280 * 0.5f - weaponIconWidth * 0.5f;
	float weaponIconY = 350.0f;

	Rectangle weaponRect = { weaponIconX, weaponIconY, weaponIconWidth, weaponIconHeight}; // Example weapon rectangle
};