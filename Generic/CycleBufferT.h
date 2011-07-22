/*
 * Amiga Generic Set - set of libraries and includes to ease sw development for all Amiga platforms
 * Copyright (C) 2004-2008 Tomasz Wiszkowski Tomasz.Wiszkowski at gmail.com.
 * 
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef __GENERIC_CYCLEBUFFERT_H
#define __GENERIC_CYCLEBUFFERT_H

#include "CycleBuffer.h"

namespace GenNS
{
    template<typename T>
    class CycleBufferT : public CycleBuffer
    {
    public:
	CycleBufferT(uint8 maxidx) :
	    CycleBuffer(maxidx, sizeof(T))
	{
	};

	virtual T*	Alloc()
	{
	    return (T*)CycleBuffer::Alloc();
	}

	virtual void	Send(T* t)
	{
	    CycleBuffer::Send(t);
	}

	virtual T*	Receive()
	{
	    return (T*)CycleBuffer::Receive();
	}

	virtual void	Dispose(T* t)
	{
	    CycleBuffer::Dispose(t);
	}

    };
};

#endif
