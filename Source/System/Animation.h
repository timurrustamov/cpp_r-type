#ifndef ANIMATION_H_
# define ANIMATION_H_

# include			<SFML/Graphics/Drawable.hpp>
# include			<SFML/Graphics/Transformable.hpp>
# include			<SFML/Graphics/Texture.hpp>
# include			<SFML/Graphics/VertexArray.hpp>
# include			<SFML/Graphics/RenderTarget.hpp>
# include			<string>
# include			"../GameEngine/t2Vector.hpp"

class				Animation : public sf::Drawable, public sf::Transformable
{
	sf::Texture		*texture;
	sf::VertexArray	vertices;

	unsigned int	state;
	std::string		name;

public:
	Animation(std::string const &_name, t2Vector<unsigned int> dimensions, t2Vector<unsigned int> positions, t2Vector<unsigned int> grid);
	~Animation();

	void			setState(unsigned int);
	virtual void	draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif /* !ANIMATION_H_ */