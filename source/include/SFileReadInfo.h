#ifndef SFILEREADINFO_H
#define SFILEREADINFO_H

#include <CFileIO.h>

struct SFileReadInfo
{
    SFileReadInfo()
    {
        mFio = NULL;
        mData = NULL;
    }


    CFileIO*		mFio;
    unsigned int	mFilePosition;
    unsigned int	mFileSize;
    void*			mData;
};

#endif
