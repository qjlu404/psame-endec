#define SFML_STATIC
#include <iostream>
#include <vector>
#include <string>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include <Windows.h>
using std::string;
class Program
{
	sf::RenderWindow mWindow;
	sf::RectangleShape topbar;
	sf::Font mtfont;
	sf::Text toptext;
	string msg;
	float toptextpos;
	float topbarpos;
	// 0 = move right
	// 1 = dont move
	// 2 = move left
	short movebar;
	// 0 = move right
	// 1 = dont move
	// 2 = move left
	short movetext;
	void processEvents();
	void update();
	void render();
	void checkmove();
public:
	Program();
	~Program();
	void run();
};
