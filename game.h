#pragma once
#include "settings.h"
#include "player.h"
#include "meteor.h"
#include <vector>
#include "textobj.h"
#include "bonus.h"

class Game {
private:
	sf::RenderWindow window;
	Player player;
	std::vector<Meteor*> meteorSprites;
	TextObj lives;
	sf::RectangleShape rect;
	std::list<Bonus*> bonusSprites;

	void checkEvents() {
		sf::Event event;
		while (window.pollEvent(event))
			if (event.type == sf::Event::Closed) window.close();
	}

	void update() {
		player.update();
		for (auto& m : meteorSprites) {
			m->update();
		}
		lives.update(std::to_string(player.getLives()));
		for (auto& bonus : bonusSprites) {
			bonus->update();
		}
	}

	void checkCollisions() {
		sf::FloatRect playerHitBox = player.getHitBox();
		auto laserSprites = player.getLasers();
		for (auto& meteor : meteorSprites) {
			//èãðîê ñ ìåòåîðàìè
			sf::FloatRect meteorHitBox = meteor->getHitBox();
			if (meteorHitBox.intersects(playerHitBox)) {
				meteor->spawn();
				player.receiveDamage(meteor->getDamage());
			}
			//ëàçåðû ñ ìåòåîðàìè
			for (auto& laser : (*laserSprites)) {
				sf::FloatRect laserHitBox = laser->getHitBox();
				//ïóëÿ ïîïàëà â ìåòåîð
				if (laserHitBox.intersects(meteorHitBox)) {
					//íà÷èñëåíèå î÷êîâ çà ñáèòûå ìåòåîðû
					meteor->spawn();
					laser->setHit();
					int chance = rand() % BONUS_RANGE;
					if (chance < BONUS_CHANCE) {
						Bonus* bonus = new Bonus(
							(Bonus::BonusType)0, 
							meteor->getPosition()
						);
						bonusSprites.push_back(bonus);
					}
				}
			}

			//áîíóñû ñ èãðîêîì
			for (auto& bonus : bonusSprites) {
				sf::FloatRect bonusHitBox = bonus->getHitBox();
				if (bonusHitBox.intersects(playerHitBox)) {
					bonus->act(player);
					bonus->setDel();
				}
			}
		}
		//óäàëèòü ïîïàâøèå ïóëè (ó êîòîðûõ hit == true)
		(*laserSprites).remove_if([](Laser* laser) {return laser->isHited(); });
		(*laserSprites).remove_if([](Laser* laser) {return laser->offScreen(); });
		bonusSprites.remove_if([](Bonus* bonus) {return bonus->offScreen(); });
		bonusSprites.remove_if([](Bonus* bonus) {return bonus->isToDel(); });
	}

	void draw() {
		window.clear();
		for (auto m : meteorSprites) {
			window.draw(m->getSprite());
		}
		window.draw(rect);
		player.draw(window);
		window.draw(lives.getText());
		for (auto& bonus : bonusSprites) {
			bonus->draw(window);
		}
		window.display();
	}

public:
	Game() : 
		window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE),
		lives(std::to_string(player.getLives()), sf::Vector2f{WINDOW_WIDTH/2,0.f})
	{
		window.setFramerateLimit(FPS);
		meteorSprites.reserve(METEOR_QTY);
		for (int i = 0; i < METEOR_QTY; i++) {
			meteorSprites.push_back(new Meteor());
		}
		rect.setFillColor(sf::Color::Green);
		rect.setSize(sf::Vector2f{ WINDOW_WIDTH, 40.f });
	}

	void play() {
		while (window.isOpen() && player.isAlive())
		{
			checkEvents();
			update();
			checkCollisions();
			draw();
		}
	}
};