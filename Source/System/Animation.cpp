#include				"../GameEngine/t2Vector.hpp"
#include				"ResourcesBank.h"
#include				"Animation.h"
#include				"RTypeException.h"

Animation::Animation(std::string const &_name, t2Vector<unsigned int> dimensions, t2Vector<int> position, t2Vector<unsigned int> grid)
	: texture(ResourcesBank::getInstance()->getTexture(_name)), name(_name), refresh(false)
{
	this->animationGrid.setPrimitiveType(sf::Quads);
	this->vertices.setPrimitiveType(sf::Quads);

	this->vertices.resize(0);
	this->animationGrid.resize(grid.getX() * grid.getY() * 4);

	for (unsigned int x = 0; x < grid.getX(); ++x)
		for (unsigned int y = 0; y < grid.getY(); ++y)
		{
			sf::Vertex	*quad = &this->animationGrid[(x + y * grid.getX()) * 4];

			quad[0].position = sf::Vector2f(0, 0);
			quad[1].position = sf::Vector2f(dimensions.getX(), 0);
			quad[2].position = sf::Vector2f(dimensions.getX(), dimensions.getY());
			quad[3].position = sf::Vector2f(0, dimensions.getY());

			quad[0].texCoords = sf::Vector2f(position.getX() + dimensions.getX() * (x % grid.getX()), position.getY() + dimensions.getY() * (y % grid.getY()));
			quad[1].texCoords = sf::Vector2f(position.getX() + dimensions.getX() * (1 + x % grid.getX()), position.getY() + dimensions.getY() * (y % grid.getY()));
			quad[2].texCoords = sf::Vector2f(position.getX() + dimensions.getX() * (1 + x % grid.getX()), position.getY() + dimensions.getY() * (1 + y % grid.getY()));
			quad[3].texCoords = sf::Vector2f(position.getX() + dimensions.getX() * (x % grid.getX()), position.getY() + dimensions.getY() * (1 + y % grid.getY()));
		}

	this->quadCount = this->animationGrid.getVertexCount() / 4;
}

Animation::Animation(std::string const &_name, sf::Texture *_texture, t2Vector<unsigned int> dimensions, t2Vector<int> position, t2Vector<unsigned int> grid)
	: texture(_texture), name(_name), refresh(false)
{
	this->animationGrid.setPrimitiveType(sf::Quads);
	this->vertices.setPrimitiveType(sf::Quads);

	this->vertices.resize(0);
	this->animationGrid.resize(grid.getX() * grid.getY() * 4);

	for (unsigned int x = 0; x < grid.getX(); ++x)
		for (unsigned int y = 0; y < grid.getY(); ++y)
		{
			sf::Vertex	*quad = &this->animationGrid[(x + y * grid.getX()) * 4];

			quad[0].position = sf::Vector2f(0, 0);
			quad[1].position = sf::Vector2f(dimensions.getX(), 0);
			quad[2].position = sf::Vector2f(dimensions.getX(), dimensions.getY());
			quad[3].position = sf::Vector2f(0, dimensions.getY());

			quad[0].texCoords = sf::Vector2f(position.getX() + dimensions.getX() * (x % grid.getX()), position.getY() + dimensions.getY() * (y % grid.getY()));
			quad[1].texCoords = sf::Vector2f(position.getX() + dimensions.getX() * (1 + x % grid.getX()), position.getY() + dimensions.getY() * (y % grid.getY()));
			quad[2].texCoords = sf::Vector2f(position.getX() + dimensions.getX() * (1 + x % grid.getX()), position.getY() + dimensions.getY() * (1 + y % grid.getY()));
			quad[3].texCoords = sf::Vector2f(position.getX() + dimensions.getX() * (x % grid.getX()), position.getY() + dimensions.getY() * (1 + y % grid.getY()));
		}

	this->quadCount = this->animationGrid.getVertexCount() / 4;
}

Animation::Animation(std::string const &_name, sf::Texture *_texture, t2Vector<unsigned int> dimensions)
	: texture(_texture), name(_name), refresh(false)
{
	this->animationGrid.setPrimitiveType(sf::Quads);
	this->vertices.setPrimitiveType(sf::Quads);

	this->vertices.resize(0);
	this->animationGrid.resize(4);

	sf::Vertex	*quad = &this->animationGrid[0];

	quad[0].position = sf::Vector2f(0, 0);
	quad[1].position = sf::Vector2f(dimensions.getX(), 0);
	quad[2].position = sf::Vector2f(dimensions.getX(), dimensions.getY());
	quad[3].position = sf::Vector2f(0, dimensions.getY());

	quad[0].texCoords = sf::Vector2f(0, 0);
	quad[1].texCoords = sf::Vector2f(dimensions.getX(), 0);
	quad[2].texCoords = sf::Vector2f(dimensions.getX(), dimensions.getY());
	quad[3].texCoords = sf::Vector2f(0, dimensions.getY());

	this->quadCount = 1;
}

Animation::~Animation()
{}

void					Animation::changeEntity(unsigned int id, unsigned int state, t2Vector<int> position)
{
	AnimationEntity		*entity;

	if (this->quadCount < state)
		throw RTypeException(state + " is out of range on an animation of " + name);
	try
	{
		entity = this->entities.at(id);
		entity->setState(state);
		entity->setPosition(position);
	}
	catch (const std::out_of_range &)
	{
		this->entities[id] = new AnimationEntity(id, state, position);
	}
	this->refresh = true;
}

void					Animation::changeEntity(AnimationEntity *entity)
{
	if (this->quadCount < entity->getState())
		throw RTypeException(entity->getState() + " is out of range on an animation of " + name);
	try
	{
		this->entities.at(entity->getId());
	}
	catch (const std::out_of_range &)
	{
		this->entities[entity->getId()] = entity;
	}
	this->refresh = true;
}

void					Animation::removeEntity(unsigned int id)
{
	this->entities.erase(id);
	this->refresh = true;
}

void					Animation::setTexture(sf::Texture *_texture)
{
	this->texture = _texture;
}

void					Animation::prepareVertices()
{
	if (!this->refresh) return ;

	sf::Vector2f		entityPosition;
	sf::Vertex			*tileQuad;
	sf::Vertex			*quad;
	unsigned int		i = 0;

	this->vertices.resize(this->entities.size() * 4);
	for (std::map<unsigned int, AnimationEntity *>::const_iterator entity = this->entities.begin(); entity != this->entities.end(); ++entity)
	{
		tileQuad = &this->animationGrid[entity->second->getState() * 4];
		quad = &this->vertices[4 * i++];

		entityPosition.x = entity->second->getPosition().getX();
		entityPosition.y = entity->second->getPosition().getY();

		quad[0].position = tileQuad[0].position + entityPosition;
		quad[1].position = tileQuad[1].position + entityPosition;
		quad[2].position = tileQuad[2].position + entityPosition;
		quad[3].position = tileQuad[3].position + entityPosition;

		quad[0].texCoords = tileQuad[0].texCoords;
		quad[1].texCoords = tileQuad[1].texCoords;
		quad[2].texCoords = tileQuad[2].texCoords;
		quad[3].texCoords = tileQuad[3].texCoords;
	}
}

void					Animation::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	states.texture = this->texture;

	target.draw(this->vertices, states);
}