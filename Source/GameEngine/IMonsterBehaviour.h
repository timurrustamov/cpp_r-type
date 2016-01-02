#ifndef IMONSTERBEHAVIOUR_H_
# define IMONSTERBEHAVIOUR_H_

# include						<string>


class							IMonsterBehaviour
{
public:
	IMonsterBehaviour			*make(int *, char **);
	virtual void				lateUpdate() = 0;
	virtual void				interact(Object *) = 0;
	virtual void				start(Object * const that) = 0;
	virtual void				parseConfig(std::string) = 0;
	virtual void				onDestroy() = 0;
};

#endif /* !IMONSTERBEHAVIOUR_H_ */