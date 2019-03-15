 /**
     @author al-Khwārizmī Muḥammad ibn Mūsā
     @studentNum  1235623
    */

class Player {
	protected:
		bool alive;
		char id;
	public:
		int dead;
		int col;
		int row;
		int direction;
		char *name; //Character name
		int score; //Number of characters in 'data' used as string
		int	HP;
	        //Default constructor: takes a name, defaults to empty stiring
		Player(const char *name="") : id('D'), alive(true), direction(-1), dead(0), row(-1), col(-1), score(0), HP(10){}
		//Player name and id
		Player(char *name,char id) : name(name), id(id), alive(true), direction(-1), dead(0),row(-1), col(-1), score(0), HP(10){}

		Player(const Player &origiinal){}//Copy constructor
		~Player(){}//Destructor
                virtual bool isAlive();
                void living(bool b);
				void setDirection(int d);
                void move(int r, int c);
                void adjustPoints(int points);
                virtual void adjustHP(int h);
			 	virtual  char getId();
                int fight();
};

class Kobold: public Player{
         private:
         	char *name; //Character name
			bool alive;
		 public:
			int dead;  //the kobold dies if he turns 100 and be moved to a new location
			int col;
         	int row;
         	char id;
         	int HP;
                Kobold() :  name("Marvin"), id('K'), alive(true),dead(0), row(-1), col(-1), HP(7){}
            Kobold(const Kobold &original){}//Copy constructor
			bool isAlive(){
				if(this->dead>100){
					this->alive = false;
					this->dead = -1;
				}
				return this->alive;
			}

			char getId(){
				return this->id;
			}

			void adjustHP(int h){
				this->HP +=h;
         		if(this->HP <= 0){
					alive=false;
					this->row = -1;
					this->col = -1;
					this->HP = 0;
         		}
				else{
					alive = true;
				}
			}


};
