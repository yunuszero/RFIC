#define _CRT_SECURE_NO_WARNINGS
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include<SFML/Audio.hpp>
#include<stdio.h>
#include<time.h>
#include<Windows.h>
#include<conio.h>
#include<utility>
#include<algorithm>
#include<iostream>
#include<string>
#include<sstream>
#include<math.h>
#include<vector>
#include<fstream>
#include"Player.h"
#include"Platform.h"
#include"Item.h"
#include"Menu.h"
#include"Map.h"
#include"Pause.h"
#include"Enemy.h"
using namespace std;

static const float VIEW_HEIGHT = 540.0f;

void ResizeView(const sf::RenderWindow &window, sf::View &view)
{
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}

int main() 
{
	srand(time(NULL));
	sf::RenderWindow window(sf::VideoMode(960, 540), "Run For Ice-Cream", sf::Style::Close | sf::Style::Resize);
	sf::View view(sf::Vector2f(0.0f, 0.0f),sf::Vector2f(960, 540));
	//view.setCenter(150.0f, 0.0f);
	sf::View ui(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(960, 540));
	sf::View mui(sf::Vector2f(480.0f, 270.0f), sf::Vector2f(960, 540));
	Menu menu(window.getSize().x, window.getSize().y);
	float playerSpeed = 300.0f;
	sf::Texture playerTexture; // don't have animation yet.
	playerTexture.loadFromFile("res/Characters/player_Animation.png");
	Player player(&playerTexture, sf::Vector2u(8, 7), 0.3f, playerSpeed, 200.0f);

	sf::CircleShape inventory1, inventory2;
	inventory1.setRadius(25);
	inventory1.setFillColor(sf::Color::Black);
	inventory2.setRadius(25);
	inventory2.setFillColor(sf::Color::Black);

	sf::Texture TextureBag[2];
	TextureBag[0].loadFromFile("res/items/boot.png");
	TextureBag[1].loadFromFile("res/items/Shield.png");

	sf::RectangleShape Bag[2];
	Bag[0].setSize(sf::Vector2f(50.0f, 50.0f));
	Bag[1].setSize(sf::Vector2f(50.0f, 50.0f));

	sf::Texture enemyTexture;
	enemyTexture.loadFromFile("res/Object/enemy.png");
	vector<Enemy> enemies[2];

	sf::Texture shieldTexture;
	shieldTexture.loadFromFile("res/Object/barrier.png");

	sf::RectangleShape barrier;
	barrier.setSize(sf::Vector2f(100.0f, 100.0f));
	barrier.setOrigin(barrier.getSize() / 2.0f);
	barrier.setTexture(&shieldTexture);

	sf::Texture texture;
	if (!texture.loadFromFile("res/map/BG.png"))
	{
		std::cerr << "Could not load image.";
		return EXIT_FAILURE;
	}

	sf::Sprite map(texture);
	map.setScale({ 1.0f, 1.0f });
	map.setPosition(sf::Vector2f(-330.0f, -794.0f));
	
	sf::Texture TM1;
	TM1.loadFromFile("res/map/BG2.png");
	sf::Texture TM2;
	TM2.loadFromFile("res/map/BG3.png");
	sf::Texture TM3;
	TM3.loadFromFile("res/map/BG4.png");
	vector<Map> maps;

	sf::Texture itemTexture;
	itemTexture.loadFromFile("res/items/items.png");

	vector<Platform> platforms;
	
	vector<Item> items[8];

	float Download = 0;
	sf::RectangleShape DL(sf::Vector2f(Download / 50.0f, 20));
	DL.setPosition(sf::Vector2f(285, 647.5f));
	DL.setFillColor(sf::Color::White);
	DL.setSize(sf::Vector2f(Download / 150.f, 19));

	sf::Texture load;
	//load.loadFromFile("a/keynameload.png");
	sf::RectangleShape ll(sf::Vector2f(1080, 720));
	ll.setPosition(sf::Vector2f(0, 0));
	//ll.setTexture(&load);

	sf::Font font;
	font.loadFromFile("res/fonts/ConnectionIi-2wj8.otf");

	sf::Texture LBmenu;
	LBmenu.loadFromFile("res/map/BGLB.png");
	sf::RectangleShape LBBG;
	LBBG.setSize(sf::Vector2f(960, 540));
	LBBG.setTexture(&LBmenu);
	LBBG.setPosition(mui.getCenter().x - (mui.getSize().x / 2), mui.getCenter().y - (mui.getSize().y / 2));

	sf::Texture keymenu;
	keymenu.loadFromFile("res/map/keyname.png");
	sf::RectangleShape keyBG;
	keyBG.setSize(sf::Vector2f(960, 540));
	keyBG.setTexture(&keymenu);
	keyBG.setPosition(mui.getCenter().x - (mui.getSize().x / 2), mui.getCenter().y - (mui.getSize().y / 2));

	sf::Texture bgmenu;
	bgmenu.loadFromFile("res/map/BGMenu.png");
	sf::RectangleShape BG;
	BG.setSize(sf::Vector2f(960, 540));
	BG.setTexture(&bgmenu);
	BG.setPosition(mui.getCenter().x - (mui.getSize().x / 2), mui.getCenter().y - (mui.getSize().y / 2));

	sf::Texture pausemenu;
	pausemenu.loadFromFile("res/map/pause.png");
	sf::RectangleShape pauseBG;
	pauseBG.setSize(sf::Vector2f(960, 540));
	pauseBG.setTexture(&pausemenu);

	sf::Texture endmenu;
	endmenu.loadFromFile("res/map/end.png");
	sf::RectangleShape endBG;
	endBG.setSize(sf::Vector2f(960, 540));
	endBG.setTexture(&endmenu);

	/* sound */
	sf::SoundBuffer choose;
	choose.loadFromFile("res/sounds/choosen.ogg");
	sf::Sound SoundMove;
	SoundMove.setBuffer(choose);

	sf::SoundBuffer soundselected;
	soundselected.loadFromFile("res/sounds/selected.ogg");
	sf::Sound selected;
	selected.setBuffer(soundselected);

	sf::SoundBuffer c;
	c.loadFromFile("res/sounds/Coin.wav");
	sf::Sound collectCoin;
	collectCoin.setBuffer(c);
	collectCoin.setVolume(20.0f);

	sf::Music music;
	music.openFromFile("res/sounds/menu.ogg");
	music.setLoop(true);
	music.setVolume(20.f);

	sf::Music music1;
	music1.openFromFile("res/sounds/play.ogg");
	music1.setLoop(true);
	music1.setVolume(20.f);

	sf::String playerInput;
	std::ofstream fileWriter;
	std::ostringstream keyname;
	sf::Text Keyname;
	Keyname.setCharacterSize(40);
	Keyname.setString(" ");
	Keyname.setFont(font);
	Keyname.setFillColor(sf::Color::Black);

	sf::Font fontname;
	fontname.loadFromFile("res/fonts/EndlessBossBattleRegular-v7Ey.ttf");
	sf::Text idname;
	idname.setFont(fontname);
	idname.setCharacterSize(24);
	idname.setFillColor(sf::Color::White);
	idname.setString("Yunus Deemad 63010798");

	sf::Clock clock;
	sf::Clock cooldown;
	sf::Clock cooldownA;
	sf::Clock cooldownC;
	sf::Clock cooldownB;
	sf::Clock Espawn;
	sf::Clock Espawn1;
	sf::Clock cooldownI;
	sf::Clock shieldCD;
	float deltaTime = 0.0f;
	float countTimeAdd = 0.0f;
	int Inventory[2] = { 0,0 };
	int Inventorycount = 0;
	int sectemp = 0;
	int activateCD = 0;
	int coinCD = 0;
	int BOWCD = 0;
	int ECD = 0;
	int ECD1 = 0;
	int SCD = 0;
	int ICD = 0;
	int i = 1;
	int score = 0;
	int highScore = 0;
	int countloop = 0;
	float postemp = player.GetPosition().x;
	bool shield = false;
	bool wing = false;
	bool toggleMenu = true;
	bool firstcheck = true;
	bool togglePause = false;
	bool dirty = true;
	bool Rank = false;
	bool MemScore = false;
	bool Cload = false;
	bool Start = false;
	bool endGame = false;

	std::map<int, std::string> keepscore;
	std::ifstream fileReader; //อ่านข้อมูลจากไฟล์
	std::string word;

	/*Modify textbox*/
	char last_char = ' ';
	sf::RectangleShape cursor;
	cursor.setSize(sf::Vector2f(5.0f, 30.0f));
	cursor.setOrigin(sf::Vector2f(2.5f, 15.0f));
	cursor.setFillColor(sf::Color::White);
	sf::Text text("", font);
	Keyname.setPosition(window.getSize().x/2.0f, 250.0f);
	text.setFillColor(sf::Color::White);
	text.setPosition(mui.getCenter().x - 50.0f, 230.0f);
	cursor.setPosition(mui.getCenter().x + text.getGlobalBounds().width - 50.0f, 250.0f);
	float totalTime_cursor = 0;
	sf::Clock clock_cursor;
	bool state_cursor = false;

	std::string user_name = "";
	fstream myFile; //อ่านข้อมูลจากไฟล์และเขียนลงไฟล์

	while (window.isOpen())
	{	
		/*------------------------------------------- menu setup -------------------------------------------*/
		music.play();
		while (toggleMenu)
		{
			music1.pause();
			sf::Event ev;
			while (window.pollEvent(ev))
			{
				switch (ev.type)
				{
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::KeyReleased:
					switch (ev.key.code)
					{
					case sf::Keyboard::Up:
						menu.Moveup();
						SoundMove.play();
						break;
					case sf::Keyboard::Down:
						menu.MoveDown();
						SoundMove.play();
						break;
					case sf::Keyboard::Return:
						selected.play();
						switch (menu.GetPressedItem())
						{
						case 0:
							score = 0;
							toggleMenu = false;
							firstcheck = true;
							MemScore = true;
							Start = true;
							break;
						case 1:
							Rank = true;
							toggleMenu = false;
							break;
						case 2:
							music.pause();
							music1.pause();
							window.close();
							break;
						}
						break;
					}
				}
			}

			deltaTime = clock.restart().asSeconds();
			/* player reset */
			player.setPosition(sf::Vector2f(0.0f, 50.0f));
			player.setThirsty(200.0f);
			player.setStamina(100.0f);
			player.setSpeed(playerSpeed);
			/* platforms & sprites reset */
			postemp = player.GetPosition().x;
			platforms.clear();
			platforms.push_back(Platform(nullptr, sf::Vector2f(10000.0f, 500.0f), sf::Vector2f(0.0f, 350.0f)));
			for (int j = 0; j < 8; j++) {
				items[j].clear();
			}
			maps.clear();
			for (int j = 0; j < 2; j++) {
				enemies[j].clear();
			}
			i = 1;
			idname.setPosition(sf::Vector2f(mui.getCenter().x - mui.getSize().x / 2 + 10, mui.getCenter().y + mui.getSize().y / 2 - 30));

			window.clear(sf::Color(150, 150, 150));
			window.setView(mui);
			window.draw(BG);
			menu.draw(window);
			window.draw(idname);
			window.display();
		}

		Pause pause(ui.getCenter().x, ui.getCenter().y);
		while (togglePause)
		{
			music.pause();
			music1.pause();
			sf::Event ev;
			while (window.pollEvent(ev))
			{
				switch (ev.type)
				{
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::KeyReleased:
					switch (ev.key.code)
					{
					case sf::Keyboard::Up:
						pause.Moveup();
						SoundMove.play();
						break;
					case sf::Keyboard::Down:
						pause.MoveDown();
						SoundMove.play();
						break;
					case sf::Keyboard::Return:
						selected.play();
						switch (pause.GetPressedItem())
						{
						case 0:
							togglePause = false;
							Start = true;
							firstcheck = true;
							break;
						case 1:
							togglePause = false;
							endGame = true;
							toggleMenu = true;
							break;
						}
					}
				}
			}
			idname.setPosition(sf::Vector2f(ui.getCenter().x - ui.getSize().x / 2 + 10, ui.getCenter().y + ui.getSize().y / 2 - 30));
			pauseBG.setPosition(ui.getCenter().x - (ui.getSize().x / 2), ui.getCenter().y - (ui.getSize().y / 2));
			window.clear(sf::Color(150, 150, 150));
			window.setView(ui);
			for (Platform& platform : platforms)
				platform.Draw(window);
			for (Map& m : maps)
				m.draw(window);
			window.draw(map);
			for (int j = 0; j < 8; j++)
			{
				for (Item& item : items[j])
				{
					item.Update(deltaTime);
					item.Draw(window);
				}
			}
			for (int j = 0; j < 2; j++) {
				for (Enemy& enemy : enemies[j])
				{
					enemy.Update(deltaTime);
					enemy.Draw(window);
				}
			}
			player.Draw(window);
			window.draw(pauseBG);
			pause.draw(window);
			window.draw(idname);
			window.display();
		}
		
		sf::Event evnt;

		while (Rank) 
		{
			sf::Event ev;
			while (window.pollEvent(ev)) {
				switch (ev.type) {
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::KeyReleased:
					switch (ev.key.code)
					{
					case sf::Keyboard::Return:
						selected.play();
						toggleMenu = true;
						Rank = false;
						break;
					}
					break;
				}
			}
			
			sf::Vector2f mouesPosition = sf::Vector2f(0.0f, 0.0f);
			mouesPosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
			cout << sf::Mouse::getPosition(window).x << " " << sf::Mouse::getPosition(window).y << endl;
			idname.setPosition(sf::Vector2f(mui.getCenter().x - mui.getSize().x / 2 + 10, mui.getCenter().y + mui.getSize().y / 2 - 30));
			window.clear(sf::Color(150,150,150));
			window.setView(mui);
			window.draw(LBBG);
			sf::Text text1("", font);
			text1.setCharacterSize(30);
			text1.setFillColor(sf::Color::White);
			fileReader.open("database/keephighscore.txt");
			do {
				fileReader >> word;
				std::string first_token = word.substr(0, word.find(','));
				int second_token = std::stoi(word.substr(word.find(',') + 1, word.length()));
				keepscore[second_token] = first_token;
			} while (fileReader.good());
			fileReader.close();
			std::map<int, std::string>::iterator end = keepscore.end();
			std::map<int, std::string>::iterator beg = keepscore.begin();
			end--;
			beg--;
			int currentDisplay = 0;
			for (std::map<int, std::string>::iterator it = end; it != beg; it--) {
				text1.setString(it->second);
				text1.setPosition(mui.getCenter().x - 170.0f, 190.0f + 50.0f * currentDisplay);
				window.draw(text1);
				text1.setString(std::to_string(it->first));
				text1.setPosition(mui.getCenter().x + 95.0f, 190.0f + 50.0f * currentDisplay);
				window.draw(text1);
				currentDisplay++;
				if (currentDisplay == 5)
				{
					break;
				}
			}

			sf::Text back;
			back.setFont(font);
			back.setCharacterSize(24);
			back.Bold;
			back.setFillColor(sf::Color::Red);

			back.setString("Back");
			back.setPosition(mui.getCenter().x - 36, mui.getCenter().y+205);

			window.draw(back);
			window.draw(idname);
			window.display();
		}

		while (MemScore == true) {

			countTimeAdd += deltaTime;
			sf::Event event;
			while (window.pollEvent(event)) {
				switch (event.type)
				{
				case sf::Event::Closed:
					window.close();
					break;
				}
			}

			if (event.type == sf::Event::TextEntered && last_char != event.text.unicode)
			{
				if (event.text.unicode == 13) { //enter
					user_name = playerInput;
					playerInput.clear();
					toggleMenu = true;
				}
				else if (event.text.unicode == 8 && playerInput.getSize() > 0) { // backspace delete
					playerInput = playerInput.substring(0, playerInput.getSize() - 1);
				}
				else {
					if (playerInput.getSize() < 10) {
						if (countTimeAdd > 0.2) {
							playerInput += event.text.unicode;
							countTimeAdd = 0;
						}
					}
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
					selected.play();
					toggleMenu = false;
					Rank = false;
					Cload = true;
					music.pause();
					//soundcount = 0;
				}
				last_char = event.text.unicode;
				text.setString(playerInput);
				cursor.setPosition(mui.getCenter().x + text.getGlobalBounds().width -50, 250.0f);
			}
			else if (event.type == sf::Event::EventType::KeyReleased && last_char != ' ') {
				last_char = ' ';
			}
			idname.setPosition(sf::Vector2f(mui.getCenter().x - mui.getSize().x / 2 + 10, mui.getCenter().y + mui.getSize().y / 2 - 30));
			window.clear(sf::Color(150,150,150));
			window.setView(mui);
			window.draw(keyBG);
			window.draw(Keyname);

			totalTime_cursor += clock_cursor.restart().asSeconds();
			if (totalTime_cursor >= 0.5) {
				totalTime_cursor = 0;
				state_cursor = !state_cursor;
			}
			if (state_cursor == true) {
				window.draw(cursor);
			}
			window.draw(text);
			if (Cload == true) {
				//window.draw(ll);
				//window.draw(LL);
				Download += 95;
				DL.setSize(sf::Vector2f(Download / 150.f, 19));
				window.draw(DL);
				if (Download > 80000) {
					Download = 80000;
					MemScore = false;
					Start = true;
					Cload = false;
					//music1.play();
				}
			}
			window.draw(idname);
			window.display();
		}

		deltaTime = 0.0f;
		clock.restart();
		cout << user_name << endl;
		Download = 0;
		music1.play();

		while (Start)
		{
			while (window.pollEvent(evnt))
			{
				switch (evnt.type)
				{
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::Resized:
					ResizeView(window, view);
					ResizeView(window, ui);
					
					break;
				}
			}

			if (player.GetPosition().y > 50.0f && firstcheck)
			{
				if (player.GetPosition().y > 50.0f) player.setPosition(sf::Vector2f(player.GetPosition().x, 50.0f));
				firstcheck = false;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				togglePause = true;
				Start = false;
			}

			if (player.GetThirsty() == 0) {
				endGame = true;
				Start = false;
			}

			// declare time as seconds  for use as cooldown time. 
			sf::Time elapse1 = cooldown.getElapsedTime();
			if (sectemp != (int)elapse1.asSeconds()) {
				sectemp = (int)elapse1.asSeconds();
			}
			sf::Time elapse2 = cooldownA.getElapsedTime();
			if (activateCD != (int)elapse2.asSeconds()) {
				activateCD = (int)elapse2.asSeconds();
			}
			sf::Time elapse3 = cooldownC.getElapsedTime();
			if (coinCD != (int)elapse3.asSeconds()) {
				coinCD = (int)elapse3.asSeconds();
			}
			sf::Time elapse4 = cooldownB.getElapsedTime();
			if (BOWCD != (int)elapse4.asSeconds()) {
				BOWCD = (int)elapse4.asSeconds();
			}
			sf::Time elapse5 = Espawn.getElapsedTime();
			if (ECD != (int)elapse5.asSeconds()) {
				ECD = (int)elapse5.asSeconds();
			}
			sf::Time elapse6 = shieldCD.getElapsedTime();
			if (SCD != (int)elapse6.asSeconds()) {
				SCD = (int)elapse6.asSeconds();
			}
			sf::Time elapse7 = cooldownI.getElapsedTime();
			if (ICD != (int)elapse7.asSeconds()) {
				ICD = (int)elapse7.asSeconds();
			}
			sf::Time elapse8 = Espawn1.getElapsedTime();
			if (ECD1 != (int)elapse8.asSeconds()) {
				ECD1 = (int)elapse8.asSeconds();
			}

			deltaTime = clock.restart().asSeconds();
			player.Update(deltaTime);
			view.setCenter(player.GetPosition().x + 150, 0.0f);
			ui.setCenter(player.GetPosition().x + 150, 0.0f);


			/*------------------------------------------- PlatForms & Sprites -------------------------------------------*/
			// move floor platform.
			sf::Vector2f floor = platforms[0].GetPosition();
			floor.x = player.GetPosition().x - 300.0f;
			platforms[0].move(floor);

			if (player.GetPosition().x - postemp > 900.0f)
			{
				postemp = player.GetPosition().x;
				// maps & platforms generate.
				switch (rand() % 3) {
				case 0:
					maps.push_back(Map(&TM1, -330.0f + (1920.0f * i), -794.0f));
					platforms.push_back(Platform(nullptr, sf::Vector2f(272.0f, 25.0f), sf::Vector2f(-330.0f + (1920.0f * i) + 745.0f, -95.0f)));
					platforms.push_back(Platform(nullptr, sf::Vector2f(272.0f, 25.0f), sf::Vector2f(-330.0f + (1920.0f * i) + 1117.0f, -50.0f)));
					platforms.push_back(Platform(nullptr, sf::Vector2f(108.0f, 25.0f), sf::Vector2f(-330.0f + (1920.0f * i) + 1338.0f, -50.0f)));
					platforms.push_back(Platform(nullptr, sf::Vector2f(272.0f, 25.0f), sf::Vector2f(-330.0f + (1920.0f * i) + 1652.0f, -125.0f)));
					break;
				case 1:
					maps.push_back(Map(&TM2, -330.0f + (1920.0f * i), -794.0f));
					platforms.push_back(Platform(nullptr, sf::Vector2f(272.0f, 25.0f), sf::Vector2f(-330.0f + (1920.0f * i) + 197.0f, -50.0f)));
					platforms.push_back(Platform(nullptr, sf::Vector2f(108.0f, 25.0f), sf::Vector2f(-330.0f + (1920.0f * i) + 418.0f, -50.0f)));
					platforms.push_back(Platform(nullptr, sf::Vector2f(284.0f, 25.0f), sf::Vector2f(-330.0f + (1920.0f * i) + 713.0f, -115.0f)));
					platforms.push_back(Platform(nullptr, sf::Vector2f(272.0f, 25.0f), sf::Vector2f(-330.0f + (1920.0f * i) + 1067.0f, -125.0f)));
					platforms.push_back(Platform(nullptr, sf::Vector2f(272.0f, 25.0f), sf::Vector2f(-330.0f + (1920.0f * i) + 1409.0f, -125.0f)));
					break;
				case 2:
					maps.push_back(Map(&TM3, -330.0f + (1920.0f * i), -794.0f));
					platforms.push_back(Platform(nullptr, sf::Vector2f(272.0f, 25.0f), sf::Vector2f(-330.0f + (1920.0f * i) + 607.0f, -50.0f)));
					platforms.push_back(Platform(nullptr, sf::Vector2f(108.0f, 25.0f), sf::Vector2f(-330.0f + (1920.0f * i) + 828.0f, -50.0f)));
					platforms.push_back(Platform(nullptr, sf::Vector2f(272.0f, 25.0f), sf::Vector2f(-330.0f + (1920.0f * i) + 1111.0f, -125.0f)));
					break;
				}
				i++;

				// items generate.
				if (sectemp >= rand() % 16 + 15)
				{
					sectemp = 0; cooldown.restart();	// reset cooldown time.
					int r = rand() % 2;
					if (r == 1 && dirty) {
						dirty = false;
						r = 0;
					}
					if (r == 1) dirty = true;
					items[r].push_back(Item(&itemTexture, r, sf::Vector2u(3, 8), 0.3f, sf::Vector2f(100.0f, 100.0f), sf::Vector2f(player.GetPosition().x + (rand() % 950) + 700, rand() % 30 - 95.0f))); //set sprite on platform.
				}

				if (activateCD >= rand() % 10 + 20)
				{
					activateCD = 0; cooldownA.restart();
					int r = rand() % 3 + 2;
					items[r].push_back(Item(&itemTexture, r, sf::Vector2u(3, 8), 0.3f, sf::Vector2f(100.0f, 100.0f), sf::Vector2f(player.GetPosition().x + (rand() % 950) + 700, rand() % 30 - 95.0f))); //set sprite on platform.
				}

				if (coinCD >= rand() % 7 + 3)
				{
					coinCD = 0; cooldownC.restart();
					items[5].push_back(Item(&itemTexture, 5, sf::Vector2u(3, 8), 0.3f, sf::Vector2f(50.0f, 50.0f), sf::Vector2f(player.GetPosition().x + (rand() % 950) + 700, rand() % 30 - 95.0f))); //set sprite on platform.
				}
				if (BOWCD >= 90)
				{
					BOWCD = 0; cooldownB.restart();
					items[6].push_back(Item(&itemTexture, 6, sf::Vector2u(3, 8), 0.3f, sf::Vector2f(100.0f, 100.0f), sf::Vector2f(player.GetPosition().x + (rand() % 950) + 700, rand() % 30 - 95.0f))); //set sprite on platform.
				}
				if (ICD >= 40)
				{
					ICD = 0; cooldownI.restart();
					items[7].push_back(Item(&itemTexture, 7, sf::Vector2u(3, 8), 0.3f, sf::Vector2f(100.0f, 100.0f), sf::Vector2f(player.GetPosition().x + (rand() % 950) + 700, rand() % 30 - 95.0f))); //set sprite on platform.
				}
				if (ECD >= 5 - rand() % 3)
				{
					ECD = 0; Espawn.restart();
					for (int j = 0; j < rand() % 3; j++) {
						enemies[0].push_back(Enemy(&enemyTexture, 0, sf::Vector2u(5, 2), 5, 0.3f, 300.0f, sf::Vector2f(100.0f, 100.0f), sf::Vector2f(player.GetPosition().x + (rand() % 950) + 800, -95.0f - rand() % 5)));
					}
				}
				if (ECD1 >= 5 - rand() % 3)
				{
					ECD1 = 0; Espawn1.restart();
					enemies[1].push_back(Enemy(&enemyTexture, 1, sf::Vector2u(5, 2), 2, 0.3f, 300.0f, sf::Vector2f(150.0f, 150.0f), sf::Vector2f(player.GetPosition().x + (rand() % 950) + 700, 50.0f)));
				}
			}

			/*------------------------------------------- Collision -------------------------------------------*/
			sf::Vector2f direction;
			for (Platform& platform : platforms)
			{
				if (platform.GetCollider().checkCollision(player.GetCollider(), direction, 1.0f))
					player.OnCollision(direction);
			}

			sf::Vector2f dir;
			for (Item& item : items[0])
			{

				if (item.GetCollider().checkCollision(player.GetCollider(), dir, 0.0f))
				{
					items[0].pop_back(); // clear item that player collected.
					player.addThirsty(5);
					break;
				}
			}
			for (Item& item : items[1])
			{
				if (item.GetCollider().checkCollision(player.GetCollider(), dir, 0.0f))
				{
					items[1].pop_back(); // clear item that player collected.
					player.addThirsty(-10);
					break;
				}
			}
			for (Item& item : items[2])
			{
				if (item.GetCollider().checkCollision(player.GetCollider(), dir, 0.0f))
				{
					items[2].pop_back(); // clear item that player collected.
					if (Inventory[0] == 0) {
						Inventory[0] = 2;
						Bag[0].setTexture(&TextureBag[0]);
					}
					else if (Inventory[1] == 0) {
						Inventory[1] = 2;
						Bag[1].setTexture(&TextureBag[0]);
					}
					
					break;
				}
			}
			for (Item& item : items[3])
			{
				if (item.GetCollider().checkCollision(player.GetCollider(), dir, 0.0f))
				{
					items[3].pop_back(); // clear item that player collected.
					wing = true;
					break;
				}
			}
			for (Item& item : items[4])
			{
				if (item.GetCollider().checkCollision(player.GetCollider(), dir, 0.0f))
				{
					items[4].pop_back(); // clear item that player collected.
					if (Inventory[0] == 0) {
						Inventory[0] = 4;
						Bag[0].setTexture(&TextureBag[1]);
					}
					else if (Inventory[1] == 0) {
						Inventory[1] = 4;
						Bag[1].setTexture(&TextureBag[1]);
					}
					break;
				}
			}
			for (Item& item : items[5])
			{
				if (item.GetCollider().checkCollision(player.GetCollider(), dir, 0.0f))
				{
					items[5].pop_back(); // clear item that player collected.
					score += 100;
					collectCoin.play();
					break;
				}
			}
			for (Item& item : items[6])
			{
				if (item.GetCollider().checkCollision(player.GetCollider(), dir, 0.0f))
				{
					items[6].pop_back(); // clear item that player collected.
					player.addThirsty(20);
					break;
				}
			}
			for (Item& item : items[7])
			{
				if (item.GetCollider().checkCollision(player.GetCollider(), dir, 0.0f))
				{
					items[7].pop_back(); // clear item that player collected.
					player.addThirsty(10);
					score += 500;
					collectCoin.play();
					break;
				}
			}

			if (Inventory[0] != 0 && sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
				if (Inventory[0] == 2) {
					player.addSpeed(50.0f);
					player.addStamina(20.0f);
					Inventory[0] = 0;
				}
				if (Inventory[0] == 4) {
					shield = true;
					SCD = 0; shieldCD.restart();
					cout << shield << endl;
					Inventory[0] = 0;
				}
			}
			if (Inventory[1] != 0 && sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
				if (Inventory[1] == 2) {
					player.addSpeed(50.0f);
					player.addStamina(20.0f);
					Inventory[1] = 0;
				}
				if (Inventory[1] == 4) {
					shield = true;
					SCD = 0; shieldCD.restart();
					cout << shield << endl;
					Inventory[1] = 0;
				}
			}

			inventory1.setPosition(ui.getCenter().x - (ui.getSize().x / 2), ui.getCenter().y - 220);
			inventory2.setPosition(ui.getCenter().x - (ui.getSize().x / 2) + 60, ui.getCenter().y - 220);
			Bag[0].setPosition(ui.getCenter().x - (ui.getSize().x / 2), ui.getCenter().y - 220);
			Bag[1].setPosition(ui.getCenter().x - (ui.getSize().x / 2) + 60, ui.getCenter().y - 220);

			if (shield) {
				if (SCD >= 10) {
					SCD = 0; shieldCD.restart();
					shield = false;
				}
			}
			barrier.setPosition(player.GetPosition());

			if (wing) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
					player.OnCollision(sf::Vector2f(0.0f, -1.0f));
					wing = false;
				}
			}

			for (Enemy& enemy : enemies[0])
			{
				if (enemy.GetCollider().checkCollision(player.GetCollider(), direction, 0.0f))
				{
					enemies[0].pop_back();
					if(!shield)
						player.addThirsty(-10);
				}
			}
			for (Enemy& enemy : enemies[1])
			{
				if (enemy.GetCollider().checkCollision(player.GetCollider(), direction, 0.0f))
				{
					enemies[1].pop_back();
					if (!shield)
						player.addThirsty(-10);
				}
			}
			idname.setPosition(sf::Vector2f(view.getCenter().x - view.getSize().x / 2 + 10, view.getCenter().y + view.getSize().y / 2 - 30));

			sf::Text bar;
			bar.setFont(font);
			bar.setCharacterSize(48);
			bar.Bold;
			bar.setFillColor(sf::Color::Black);

			ostringstream ss;
			ss << score;
			bar.setString(ss.str());
			bar.setOrigin(bar.getLocalBounds().width, bar.getLocalBounds().height);
			bar.setPosition(view.getCenter().x + (view.getSize().x / 2) - 20, view.getCenter().y - 240.0f);

			window.clear(sf::Color(150, 150, 150));
			window.setView(view);
			for (Platform& platform : platforms)
				platform.Draw(window);
			for (Map& m : maps)
				m.draw(window);
			window.draw(map);
			for (int j = 0; j < 8; j++) 
			{
				for (Item& item : items[j])
				{
					item.Update(deltaTime);
					item.Draw(window);
				}
			}
			for (int j = 0; j < 2; j++) {
				for (Enemy& enemy : enemies[j])
				{
					enemy.Update(deltaTime);
					enemy.Draw(window);
				}
			}
			player.Draw(window);
			if (shield)
				window.draw(barrier);
			window.setView(ui);
			player.Stamina(window, ui);
			player.Thirsty(window, ui);
			window.draw(bar);
			window.draw(inventory1);
			window.draw(inventory2);
			for (int j = 0; j < 2; j++) {
				if (Inventory[j] != 0)
					window.draw(Bag[j]);
			}
			window.draw(idname);
			window.display();
		}

		while (endGame)
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				switch (event.type)
				{
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::KeyReleased:
					switch (event.key.code)
					{
					case sf::Keyboard::Return:
						music1.pause();
						selected.play();
						endGame = false;
						toggleMenu = true;
						fileWriter.open("database/keephighscore.txt", std::ios::out | std::ios::app);
						cout << "\n" << user_name << "," << score;
						fileWriter << "\n" << user_name << "," << score;
						fileWriter.close();
						playerInput.clear();
						break;
					}
					break;
				}
			}
			myFile.close();

			sf::Text endscore;
			endscore.setFont(font);
			endscore.setCharacterSize(72);
			endscore.Bold;
			endscore.setFillColor(sf::Color::White);

			ostringstream ss;
			ss << score;
			endscore.setString(ss.str());
			endscore.setOrigin(endscore.getLocalBounds().width / 2.0f, endscore.getLocalBounds().height);
			endscore.setPosition(ui.getCenter().x,ui.getCenter().y);
			idname.setPosition(sf::Vector2f(view.getCenter().x - view.getSize().x / 2 + 10, view.getCenter().y + view.getSize().y / 2 - 30));

			endBG.setPosition(ui.getCenter().x - (ui.getSize().x / 2), ui.getCenter().y - (ui.getSize().y / 2));
			window.clear();
			for (Platform& platform : platforms)
				platform.Draw(window);
			for (Map& m : maps)
				m.draw(window);
			window.draw(map);
			for (int j = 0; j < 8; j++)
			{
				for (Item& item : items[j])
				{
					item.Update(deltaTime);
					item.Draw(window);
				}
			}
			for (int j = 0; j < 2; j++) {
				for (Enemy& enemy : enemies[j])
				{
					enemy.Update(deltaTime);
					enemy.Draw(window);
				}
			}
			player.Draw(window);
			window.draw(endBG);
			window.draw(endscore);
			window.draw(idname);
			window.display();
		}
	}


	return 0;
}