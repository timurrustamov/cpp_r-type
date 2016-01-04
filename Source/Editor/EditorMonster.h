#ifndef EDITOR_MONSTER
# define EDITOR_MONSTER

# include						<string>
# include						"EditorEntity.h"

class							EditorMonster : public EditorEntity
{
	std::string					dll;

public:
	EditorMonster(std::string const &dll);
	EditorMonster(EditorMonster &editorMonster);
	~EditorMonster() {};
};

#endif /* !EDITOR_MONSTER */