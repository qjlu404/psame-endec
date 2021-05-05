#include "Chargen.h"
void Program::processEvents()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			mWindow.close();
	}
}

void Program::checkmove()
{
	if (topbarpos > 640.0f || topbarpos < 10.0f)
		movebar = 1;
}
void Program::update()
{

	switch (movebar)
	{
	case 0:
		topbar.move(-10, 0.f);
		topbarpos -= 10;
		break;

	case 1:
		break;

	case 2:
		topbar.move(10, 0);
		topbarpos += 10;
		break;
	}

	switch (movetext)
	{
	case 0:
		toptext.move(-1, 0.f);
		toptextpos -= 1;
		break;

	case 1:
		break;

	case 2:
		toptext.move(1, 0);
		toptextpos += 1;
		break;
	}
}
void Program::render()
{
	mWindow.clear();
	mWindow.draw(topbar);
	mWindow.draw(toptext);
	mWindow.display();
}
// public: 
Program::Program() : mWindow(sf::VideoMode(640, 480), "chargen", sf::Style::Close), topbar(), toptext(), mtfont()
{
	mWindow.setFramerateLimit(75);
	if (!mtfont.loadFromFile("fonts/vcreas.ttf"))
	{
		::ShowWindow(::GetConsoleWindow(), SW_SHOW);
		printf("press enter to continue");
		string a;
		std::getline(std::cin, a);
		::ShowWindow(::GetConsoleWindow(), SW_HIDE);
	}
	topbarpos = 640;
	toptextpos = 1280;
	movebar = 0;
	movetext = 1;
	topbar.setSize(sf::Vector2f(640, 30));
	topbar.setPosition(640, 30);
	topbar.setFillColor(sf::Color::Color(255, 0, 0, 140));
	msg = "This is a test of the emergency Alert System";
	toptext.setString(msg);
	toptext.setFont(mtfont);
	toptext.setCharacterSize(20);
	toptext.setFillColor(sf::Color::White);
	toptext.setOutlineColor(sf::Color::Black);
	toptext.setOutlineThickness(1);
	toptext.setPosition(100, 30);
}
Program::~Program()
{
	mWindow.close();
}
void Program::run()
{
	while (mWindow.isOpen())
	{
		processEvents();
		update();
		render();
	}
}
