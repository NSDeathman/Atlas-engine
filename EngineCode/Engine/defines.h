#pragma once

#include "stdafx.h"

#define _RELEASE(x)			\
	{						\
		if (x)				\
		{					\
			(x)->Release();	\
			(x) = NULL;		\
		}					\
	}

#define ASSERT(expession, error_message)								\
{																		\
	if (expession == false)												\
	{																	\
		Log->Print(error_message);										\
		MessageBox(NULL, error_message, "Atlas error message", MB_OK);	\
	}																	\
}																		\

#ifdef _DEBUG

#define VERIFY(expession, error_message)                                                                               \
	{                                                                                                                  \
		if (expession == false)                                                                                        \
		{                                                                                                              \
			Log->Print(error_message);                                                                                 \
			MessageBox(NULL, error_message, "Atlas error message", MB_OK);                                             \
		}                                                                                                              \
	}                                                                                                                  \

#else

#define VERIFY(expession, error_message)                                                                               \
	{                                                                                                                  \
		if (expession == false)                                                                                        \
			Log->Print(error_message);                                                                                 \
	}                                                                                                                  \

#endif
