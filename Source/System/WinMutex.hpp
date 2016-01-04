#ifndef WINMUTEX_H_
# define WINMUTEX_H_

# include				<winnt.h>
# include				<intsafe.h>
# include				<WinBase.h>
# include				<Windows.h>
# include				<processthreadsapi.h>
# include				"../GameEngine/IMutex.hpp"

class WinMutex :		public IMutex
{
private:
	HANDLE				_mutex;
	unsigned int		_locknb;
	DWORD WINAPI		_tid;

public:
	WinMutex()
	{
		this->_locknb = 0;
		this->_tid = -1;
		this->_mutex = CreateMutex(NULL, FALSE, NULL);
	}

	~WinMutex()
	{
		CloseHandle(this->_mutex);
	}

	virtual bool		lock(bool wait = true)
	{
		DWORD			waitResult;
		bool			sameThread = (GetCurrentThreadId() == this->_tid);

		if (this->_tid == -1 || !sameThread)
		{
			if ((waitResult = WaitForSingleObject(this->_mutex, (wait) ? INFINITE : 0)) == WAIT_OBJECT_0)
			{
				this->_status = IMutex::Locked;
				return (true);
			}
		}
		if (sameThread)
			++this->_locknb;
		return (false);
	}

	virtual bool		unlock()
	{
		bool			sameThread = (GetCurrentThreadId() == this->_tid);

		if (this->_tid == -1 || (sameThread && --this->_locknb > 0))
			return (false);

		this->_tid = -1;
		if (this->_status == IMutex::Locked)
		{
			ReleaseMutex(this->_mutex);
			this->_status = IMutex::Unlocked;
		}
		return (true);
	}
};

#endif /* !WINMUTEX_H_ */