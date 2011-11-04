/*
	enStream defines the interfaces for byte streams.
	
	Use enPrinter for ascii style printing.
*/

#ifndef _enStream
#define	_enStream

class enStreamIn
{
public:
			bool	read	(int& value)										{ return read(&value, sizeof(value)); }
	virtual	bool	read	(void* dst, int dstSize) = 0;
};

class enStreamOut
{
public:
			bool	write	(const int& value)									{ return write(&value, sizeof(value)); }
	virtual	bool	write	(const void* src, int srcSize) = 0;
};

#endif
