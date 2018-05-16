#ifndef __OPENHMI_TYPEDEFINE_H_INCLUDED__
#define __OPENHMI_TYPEDEFINE_H_INCLUDED__
#include <QtCore/qstring.h>
namespace QTDUDU
{	
	typedef				wchar_t		CHAR;

	typedef				char		INT8;
	typedef	unsigned	char		BYTE;
	typedef				short		SHORT;
	typedef	unsigned	short		USHORT;
	typedef				int			INT;
	typedef	unsigned	int			UINT;
	typedef				long		LONG;
	typedef	unsigned	long		ULONG;
	typedef		long	long		LLONG;
	
	typedef				float		FLOAT;
	typedef				double		DOUBLE;
	typedef				bool		BOOLEAN;

    typedef             QString     String;

	/////////////////////////////////////////////
	typedef				CHAR*		PCHAR;

	typedef				INT8*		PINT8;
	typedef				BYTE*		PBYTE;	
	typedef				SHORT*		PSHORT;
	typedef				USHORT*		PUSHORT;
	typedef				INT*		PINT;
	typedef				UINT*		PUINT;
	typedef				LONG*		PLONG;	
	typedef				ULONG*		PULONG;
	typedef				LLONG*		PLLONG;

	typedef				FLOAT*		PFLOAT;
	typedef				DOUBLE*		PDOULBE;
	typedef				BOOLEAN*	PBOOLEAN;

	/////////////////////////////////////////////
	
	/////////////////////////////////////////////
    #define				TRUE		true
    #define				FALSE		false
#ifndef NULL
	#define				NULL		0
#endif
	#define				STRING_NULL		QString()
	/////////////////////////////////////////////

	#define				INVALID_THREAD_ID	0

	/////////////////////////////////////////////
#ifdef OS_QNX
	typedef				INT				SOCKET;
	#define				INVALID_SOCKET	0
#endif

#ifdef OS_LINUX
	typedef				INT				SOCKET;
	#define				INVALID_SOCKET	0
#endif

}

#endif
