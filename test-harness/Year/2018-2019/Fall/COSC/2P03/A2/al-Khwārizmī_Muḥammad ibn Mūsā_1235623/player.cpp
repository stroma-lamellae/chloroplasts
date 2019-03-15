 /**
     @author al-Khwārizmī Muḥammad ibn Mūsā
     @studentNum  1235623
    */
#ifndef PLAYER_H
#define PLAYER_H
#include <cstdlib>
#include "player.h"

	//check whether or not player is alive
	bool Player::isAlive(){
		if(!this->alive && this->dead<=10){	//adds extra cycle so thread can start if player is dead
			dead++;
		}
		else{
			living(true);
			this->dead = 0;

		}
		return this->alive;

	}
	//sets player's direction, -1 if dead
	void Player::setDirection(int d){
			this->direction = d;
	}
	//sets alive
	void Player::living(bool b){
		this->alive = b;
	}
	//sets a player's move
	void Player::move(int r, int c){
		this->row = r;
		this->col = c;
	}

	void Player::adjustPoints(int points){
		this->score += points;
	}

	void Player::adjustHP(int h){
		this->HP = this->HP + h;
		if(this->HP <= 0){
			living(false);
			this->row = -1;
			this->col = -1;
			this->HP=0;
		}
	}

	char Player::getId(){
		return this->id;
	}

	int Player::fight(){
	        int damage;
	       damage = (rand() % 7 + 1)*-1;
	       return damage;
        }

#endif
