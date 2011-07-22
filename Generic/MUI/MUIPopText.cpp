/*
 * Amiga Generic Set - set of libraries and includes to ease sw development for all Amiga platforms
 * Copyright (C) 2004-2008 Tomasz Wiszkowski Tomasz.Wiszkowski at gmail.com.
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; either version 2.1
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include "MUIPopText.h"
#include <libclass/intuition.h>
#include <libraries/mui.h>
#include <Generic/LibrarySpool.h>
#include <proto/intuition.h>

using namespace GenNS;

MUIPopText::MUIPopText(const char* name, iptr cols, const char** nam) :
   MUIPopString(name, cols, nam)
{
}

MUIPopText::~MUIPopText()
{
}

iptr *MUIPopText::getPopDisplay()
{
   return VGroup,
      StringFrame,
      Child,         muiLabel("", 0, ID_String, 100, Align_Left),
   End;
}

