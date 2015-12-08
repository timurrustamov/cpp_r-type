#ifndef GAMEDATA_H_
# define GAMEDATA_H_

class					GameData
{
	bool				fullscreen;
	bool				mustQuit;

	GameData();
	~GameData();

public:
	static GameData		*getInstance(bool _delete = false);

	void				setFullscreen(bool);
	void				setMustQuit(bool);

	bool				getFullscreen() const;
	bool				getMustQuit() const;
};

#endif /* !GAMEDATA_H_ */