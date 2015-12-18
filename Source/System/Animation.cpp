#include				"../GameEngine/t2Vector.hpp"
#include				"ResourcesBank.h"
#include				"Animation.h"
#include				"RTypeException.h"

Animation::Animation(std::string const &_name, t2Vector<unsigned int> dimensions, t2Vector<unsigned int> positions, t2Vector<unsigned int> grid)
	: texture(ResourcesBank::getInstance()->getTexture(_name)), name(_name)
{
	this->vertices.setPrimitiveType(sf::Quads);
	this->vertices.resize(grid.getX() * grid.getY() * 4);

	for (unsigned int x = 0; x < grid.getX(); ++x)
		for (unsigned int y = 0; y < grid.getY(); ++y)
		{
			sf::Vertex	*quad = &this->vertices[(x + y * grid.getX()) * 4];

			quad[0].position = sf::Vector2f(0, 0);
			quad[1].position = sf::Vector2f(dimensions.getX(), 0);
			quad[2].position = sf::Vector2f(dimensions.getX(), dimensions.getY());
			quad[3].position = sf::Vector2f(0, dimensions.getY());
			//for (size_t i = 0; i < 4; ++i)
			//	quad[i].color = sf::Color::Transparent;

			std::cout << dimensions.getX() << std::endl;
			std::cout << dimensions.getY() << std::endl;

			std::cout << positions.getX() + dimensions.getX() * (x % grid.getX()) << std::endl;
			std::cout << positions.getX() + dimensions.getX() * (1 + x % grid.getX()) << std::endl;

			std::cout << positions.getY() + dimensions.getY() * (y % grid.getY()) << std::endl;
			std::cout << positions.getY() + dimensions.getY() * (1 + y % grid.getY()) << std::endl;


			quad[0].texCoords = sf::Vector2f(positions.getX() + dimensions.getX() * (x % grid.getX()), positions.getY() + dimensions.getY() * (y % grid.getY()));
			quad[1].texCoords = sf::Vector2f(positions.getX() + dimensions.getX() * (1 + x % grid.getX()), positions.getY() + dimensions.getY() * (y % grid.getY()));
			quad[2].texCoords = sf::Vector2f(positions.getX() + dimensions.getX() * (1 + x % grid.getX()), positions.getY() + dimensions.getY() * (1 + y % grid.getY()));
			quad[3].texCoords = sf::Vector2f(positions.getX() + dimensions.getX() * (x % grid.getX()), positions.getY() + dimensions.getY() * (1 + y % grid.getY()));
		}
	
	this->state = 0;
}

Animation::~Animation()
{}

void					Animation::setState(unsigned int newState)
{
	if (this->vertices.getVertexCount() / 4 < newState)
		throw RTypeException(newState + " is out of range on animation with texture " + name);
	this->state = newState;
}

void					Animation::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	states.texture = this->texture;

	target.draw(this->vertices, states);
}