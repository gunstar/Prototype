/*
	eiEngine
*/

#ifndef _eiEngine
#define	_eiEngine

#include "enColorC4.h"
#include "enMatrix.h"

/*******************************************************************/

class eiCamera
{
public:
	virtual				~eiCamera		();

	virtual	void		setMatrix		(const enMatrix& mat) = 0;
};

/*******************************************************************/

class eiEntity
{
public:
	virtual				~eiEntity		();

	virtual	void		setMatrix		(const enMatrix& mat) = 0;
};

/*******************************************************************/

class eiInput
{
public:
	virtual	void		eiInput_key		(int key, bool down) = 0;

public:
	enum
	{
		ArrowLeft,
		ArrowRight,
		ArrowUp,
		ArrowDown,
		Home,
		PageUp,
		PageDown
	};
};

/*******************************************************************/

class eiMesh
{
public:
	virtual				~eiMesh			();

	virtual void		clear			() = 0;

	virtual void		drawLine		(const enF3& v0, const enF3& v1) = 0;
	virtual void		drawTriangle	(const enF3& v0, const enF3& v1, const enF3& v2) = 0;

	virtual	void		setColor		(const enColorC4& v0, const enColorC4& v1) = 0;
	virtual	void		setColor		(const enColorC4& v0, const enColorC4& v1, const enColorC4& v2) = 0;
};

/*******************************************************************/

class eiTicker
{
public:
	virtual	void		eiTicker_tick	(float secs) = 0;
};

/*******************************************************************/

class eiEngine
{
public:
	virtual				~eiEngine	();

	virtual	eiCamera*	makeCamera	() = 0;
	virtual	eiEntity*	makeEntity	(eiMesh* mesh) = 0;
	virtual	eiMesh*		makeMesh	() = 0;

	virtual	void		setCamera	(eiCamera* camera) = 0;
	virtual	void		setInput	(eiInput* input) = 0;
	virtual	void		setTicker	(eiTicker* ticker) = 0;

	virtual void		run			() = 0;
};

#endif
