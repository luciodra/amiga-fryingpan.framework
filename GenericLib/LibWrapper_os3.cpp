/*
 * Amiga Generic Set - set of libraries and includes to ease sw development for all Amiga platforms
 * Copyright (C) 2001-2011 Tomasz Wiszkowski Tomasz.Wiszkowski at gmail.com.
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

#include "Library.h"
#include "LibWrapper_os3.h"
#define __NOLIBBASE__
#include <exec/libraries.h>
#include <exec/resident.h>
#include <proto/exec.h>
#include <proto/dos.h>
#include "../LowLevel/Registers.h"

struct LibInitStruct LIB_InitStruct =
{
   (unsigned long)   sizeof(struct Library),
   (void*)           LIB_FuncTable,
   (void*)           NULL,
   (void (*)(void)) &LIB_Init
};

   struct Library      *OurBase  = 0;
   void                *SegList  = 0;

struct Library *LIB_Init(void)
{
   asm volatile ( "move.l a6,%0\n\t"
                  "move.l a0,%1\n\t"
                  "move.l d0,%2\n\t"
                  : "=omg"(SysBase), "=omg"(SegList), "=omg"(OurBase)
                  :
                  : "cc", "memory");
   
   if (true == Lib_SetUp())
      return OurBase;
   
   FreeMem((void*)((ULONG)(OurBase) - OurBase->lib_NegSize), OurBase->lib_NegSize + OurBase->lib_PosSize);
   return 0;
}

uint LIB_Expunge(void)
{
   if (OurBase->lib_OpenCnt)
   {
      OurBase->lib_Flags |= LIBF_DELEXP;
      return 0;
   }

   Lib_CleanUp();

   Forbid();
   Remove(&OurBase->lib_Node);
   Permit();

   FreeMem((void*)((ULONG)(OurBase) - OurBase->lib_NegSize), OurBase->lib_NegSize + OurBase->lib_PosSize);

   return (ULONG)SegList;
}

struct Library *LIB_Open(void)
{
   if (false == Lib_Acquire())
      return 0;
      
   OurBase->lib_Flags &= ~LIBF_DELEXP;
   OurBase->lib_OpenCnt++;
   return OurBase;
}

uint LIB_Close(void)
{
   if (OurBase->lib_OpenCnt == 0)
      return 0;

   Lib_Release();

   if ((--OurBase->lib_OpenCnt) == 0)
   {
      if (OurBase->lib_Flags & LIBF_DELEXP)
         return (LIB_Expunge());
   }
   return 0;
}

uint LIB_Reserved(void)
{
   return 0;
}
