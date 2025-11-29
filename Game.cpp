#include <iostream>
using namespace std;

class Player
{
	string username = "Unknown";
	int level = 1;
	int points = 0;

public:
	Player() {}

	Player(string _username)
	{
		this->username = _username;
	}

	Player(const Player& p)
	{
		this->username = p.username;
		this->level = p.level;
		this->points = p.points;
	}

	bool operator== (string _username)
	{
		return this->username == _username;
	}

	bool operator<= (const Player& p)
	{
		return this->points <= p.points;
	}

	Player& operator+=(int x)
	{
		this->points += x;

		if (this->points >= this->level * 50)
		{
			this->level++;
			cout << "\n\nLevel Up!";
		}

		return *this;
	}

	Player& operator-=(int x)
	{
		if (this->points > 5)
		{
			this->points -= x;
		}
		else this->points = 0;

		if (this->points < (this->level - 1) * 50)
		{
			this->level--;
			cout << "\n\nLevel Down!";
		}

		return *this;
	}

	friend class Users;
	friend ostream& operator<< (ostream& out, Player& p);
};

ostream& operator<< (ostream& out, Player& p)
{
	out << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
	out << "\nUsername: " << p.username;
	out << "\nLevel: " << p.level;
	out << "\nPoints: " << p.points;
	out << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";

	return out;
}

class Character
{
	string name = "Unknown";
	int health = 100;
	int maxAttackPower = 0;
	double powerBoost = 0; // la 3 ture castigate la rand se activeaza powerBoost

public:
	Character() {}

	Character(string _name, int _maxAttackPower, double _powerBoost)
	{
		this->name = _name;

		if (_maxAttackPower > 0)
		{
			this->maxAttackPower = _maxAttackPower;
		}

		if (_powerBoost > 0)
		{
			this->powerBoost = _powerBoost;
		}
	}

	Character& operator-= (int attack)
	{
		this->health = this->health - attack;

		return *this;
	}

	Character(Character& ch)
	{
		this->name = ch.name;
		this->maxAttackPower = ch.maxAttackPower;
		this->powerBoost = ch.powerBoost;
	}

	friend ostream& operator<<(ostream& out, Character& ch);
	friend int fight(Character player, Character computer);
};

ostream& operator<<(ostream& out, Character& ch)
{
	out << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
	out << "\nName: " << ch.name;
	out << "\nHealth: " << ch.health;
	out << "\nmaxAttackPower: " << ch.maxAttackPower;
	out << "\nPower Boost: " << ch.powerBoost * 100 << "%";
	out << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";

	return out;
}

int fight(Character player, Character computer)
{
	int playerWins = 0;
	int computerWins = 0;

	for(int i=0; i<3; i++)
	{
		int turn = 1;
		while (player.health > 0 && computer.health > 0)
		{
			if (turn % 2 != 0 && playerWins >= computerWins)
			{
				cout << "\n\n" << player.name << " turn!";
				int attack = rand() % player.maxAttackPower + 1;
				computer -= attack;

				cout << "\n------------------------------------------";
				cout << "\nPlayer Health: " << player.health;
				cout << "\nComputer Health: " << computer.health;
			}
			else
			{
				cout << "\n\n" << computer.name << " turn!";
				int attack = rand() % computer.maxAttackPower + 1;
				player -= attack;

				cout << "\n------------------------------------------";
				cout << "\nPlayer Health: " << player.health;
				cout << "\nComputer Health: " << computer.health;
			}

			turn++;
		}

		if (player.health <= 0)
		{
			computerWins++;
			computer.maxAttackPower += computer.powerBoost * computer.maxAttackPower;

			cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
			cout << endl << computer.name << " wins round " << i + 1 <<"!";
			cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
		}
		else 
		{
			playerWins++;
			player.maxAttackPower += player.powerBoost * player.maxAttackPower;
			cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
			cout << endl << player.name << " wins round " << i + 1 << "!";
			cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
		}

		player.health = 100;
		computer.health = 100;

		if (playerWins == 2 || computerWins == 2) break;
	}

	if (playerWins >= 2)
	{
		return 1; // playerul a castigat
	}else return 2; // computerul a castigat
}


class Users
{
	Player** usersList = nullptr;
	int noUsers = 0;
	int listCapacity = 5;

public:
	Users() {}

	Users(const Users& _usersDb)
	{
		if (_usersDb.noUsers > 0)
		{
			this->noUsers = _usersDb.noUsers;
			this->listCapacity = _usersDb.listCapacity;
			this->usersList = new Player * [this->listCapacity];

			for (int i = 0; i < this->noUsers; i++)
			{
				this->usersList[i] = _usersDb.usersList[i];
			}
		}
	}

	Users& operator= (const Users& _usersDb)
	{
		if(this!=&_usersDb)
		{
			if (this->noUsers > 0)
			{
				delete[] this->usersList;

				this->usersList = nullptr;
				this->noUsers = 0;
			}

			if (_usersDb.noUsers > 0)
			{
				this->noUsers = _usersDb.noUsers;
				this->listCapacity = _usersDb.listCapacity;
				this->usersList = new Player * [this->listCapacity];

				for (int i = 0; i < this->noUsers; i++)
				{
					this->usersList[i] = _usersDb.usersList[i];
				}
			}
		}

		return *this;
	}

	Users operator+= (Player* p)
	{
		if (this->noUsers > 0)
		{
			if (this->noUsers == this->listCapacity)
			{
				Player** aux = new Player * [this->listCapacity * 2];

				for (int i = 0; i < this->noUsers; i++)
				{
					aux[i] = this->usersList[i];
				}

				aux[this->noUsers] = p;

				delete[] this->usersList;

				this->listCapacity *= 2;
				this->noUsers++;
				this->usersList = aux;
			}
			else
			{
				this->usersList[this->noUsers++] = p;
			}
		}
		else
		{
			this->usersList = new Player * [this->listCapacity];
			this->usersList[this->noUsers++] = p;
		}

		return *this;
	}

	Player* operator[] (int x) const
	{
		for (int i = 0; i < this->noUsers; i++)
		{
			if (x == i)
			{
				return this->usersList[i];
			}
		}
	}

	int  userExistence(string _username)
	{
		if (this->noUsers > 0)
		{
			for (int i = 0; i < this->noUsers; i++)
			{
				if (*this->usersList[i] == _username)
				{
					return i;
				}
			}

			return -1;
		}
		else return -1;
	}

	void orderByPoints()
	{
		if (this->noUsers > 0)
		{
			for (int i = 0; i < this->noUsers - 1; i++)
			{
				for (int j = i + 1; j < this->noUsers; j++)
				{
					if (*this->usersList[i] <= *this->usersList[j])
					{
						swap(this->usersList[i], this->usersList[j]);
					}
				}
			}
		}
	}

	int getPositionInRanking(string _username)
	{
		for (int i = 0; i < this->noUsers; i++)
		{
			if (*this->usersList[i] == _username)
			{
				return i + 1;
			}
		}
	}

	~Users()
	{
		if (this->noUsers > 0)
		{
			delete[] this->usersList;
			
			this->usersList = nullptr;
			this->noUsers = 0;
		}
	}

	friend ostream& operator<< (ostream& out, Users& us);
};

ostream& operator<< (ostream& out, Users& us)
{
	out << "\n\n----------------------------------------------------------------------------------------";
	out << "\nNumber of Users: " << us.noUsers << endl;
	for (int i = 0; i < us.noUsers; i++)
	{
		out << endl << i + 1 << ".";
		out << *us.usersList[i];
	}
	out << "\n----------------------------------------------------------------------------------------";

	return out;
}

int main()
{
	srand(time(0));

	Users users;
	Player* p = nullptr;

	string username;
	cout << "\n----------------------------------------------------------------------------------------";
	cout << "\nEnter username: ";
	cin >> username;
	
	int index = users.userExistence(username);

	if (index == -1)
	{
		p = new Player(username);
		users += p;
		cout << "\nWelcome " << username << " !";
	}
	else
	{
		p = users[index];
		cout << "\nWelcome back " << username << " !";
	}

	int option;
	cout << "\n\n----------------------------------------------------------------------------------------";
	cout << "\n1. Ranking";
	cout << "\n2. Fight";
	cout << "\n3. Back to Main Menu";
	cout << "\n4. Close Game";
	cout << "\n   Option: ";
	cin >> option;

	while (option != 4)
	{
		if (option == 1)
		{
			users.orderByPoints();
			int rank = users.getPositionInRanking(username);
			cout << "\n\n\n" << username << " is on " << rank<<" !";
			cout << users;
		}

		if (option == 2)
		{			
			Character soldier("Soldier", 20, 0.1);
			Character elf("Elf", 15, 0.2);
			Character wizard("Wizard", 25, 0.3);

			string playersCharacter;
			cout << "\nChoose your character: ";
			cout << soldier;
			cout << elf;
			cout << wizard;
			cout << "\nType your choise: ";
			cin >> playersCharacter;

			cout << "\n\n\nFIGHT!" << endl;
			
			Character* playersChoise = nullptr;
			if (playersCharacter == "soldier")
			{
				playersChoise = new Character(soldier);
			}
			else if (playersCharacter == "elf")
			{
				playersChoise = new Character(elf);
			}else playersChoise = new Character(wizard);

			int attack = rand() % 45;
			Character enemy("Dragon", attack, 0.05);

			int winner = fight(*playersChoise, enemy);
			if (winner == 1)
			{
				cout << "\n\n************************************************";
				cout << "\nWOW! You won!\nReward: +10 Points";
				cout << "\n************************************************";

				*p += 10;
			}
			else
			{
				cout << "\n\n************************************************";
				cout << "\nYou lost! :(\nYou might loose points!";
				cout << "\n************************************************";

				*p -= 5;
			}

			delete playersChoise;
		}

		if (option == 3)
		{
			cout << "\n----------------------------------------------------------------------------------------";
			cout << "\nEnter username: ";
			cin >> username;

			int index = users.userExistence(username);

			if (index == -1)
			{
				p = new Player(username);
				users += p;
				cout << "\nWelcome " << username << " !";
			}
			else
			{
				p = users[index];
				cout << "\nWelcome back " << username << " !";
			}
		}

		cout << "\n\n----------------------------------------------------------------------------------------";
		cout << "\n1. Ranking";
		cout << "\n2. Fight";
		cout << "\n3. Back to Main Menu";
		cout << "\n4. Close Game";
		cout << "\n   Option: ";
		cin >> option;
	}

	cout << "\nTHE END\n";

	return 0;
}