#ifndef ANIMATION_H_
# define ANIMATION_H_

# include												<cstddef>
# include												<string>
# include												<map>
# include												<SFML/Graphics/Drawable.hpp>
# include												<SFML/Graphics/Transformable.hpp>
# include												<SFML/Graphics/Texture.hpp>
# include												<SFML/Graphics/VertexArray.hpp>
# include												<SFML/Graphics/RenderTarget.hpp>

# include												"../GameEngine/AnimationEntity.hpp"
# include												"../GameEngine/t2Vector.hpp"

class													Animation : public sf::Drawable, public sf::Transformable
{
	std::string											name;
	sf::VertexArray										animationGrid;
	sf::Texture											*texture;

	std::map<unsigned int, AnimationEntity *>			entities;
	sf::VertexArray										vertices;

	bool												refresh;
	size_t												quadCount;
	
public:
	Animation(std::string const &_name, t2Vector<unsigned int> dimensions, t2Vector<int> position, t2Vector<unsigned int> grid);
	Animation(std::string const &_name, sf::Texture *_texture, t2Vector<unsigned int> dimensions, t2Vector<int> position, t2Vector<unsigned int> grid);
	Animation(std::string const &_name, sf::Texture *, t2Vector<unsigned int> dimensions);
	~Animation();

	void												changeEntity(unsigned int id, unsigned int state, t2Vector<int> position);
	void												changeEntity(AnimationEntity *);
	void												removeEntity(unsigned int id);

	void												setTexture(sf::Texture *);

	void												prepareVertices(); // to call before each draw
	virtual void										draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif /* !ANIMATION_H_ */