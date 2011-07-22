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

#ifndef _GENERIC_MUI_MUITREE_H_
#define _GENERIC_MUI_MUITREE_H_

#include <Generic/GenericMUI.h>
#include <Generic/String.h>
#include <Generic/HookAttrT.h>
#include <Generic/HookT.h>
#include <Generic/VectorT.h>

struct MUIP_NListtree_DisplayMessage;
struct MUIP_NListtree_ConstructMessage;
struct MUIP_NListtree_DestructMessage;

class Hook;

namespace GenNS
{
    class MUITree : public virtual GenericMUI
    {
    protected:
	iptr          *listview;
	iptr          *list;
	bool                    multiselect;
	String                  format;
	HookAttrT<void*, void*> hConstruct;
	HookAttrT<void*, void*> hDestruct;
	HookAttrT<void*, void*> hDisplay;
	HookAttrT<void*, void*> hSelect;
	VectorT<void*>          hSelected;

    protected:
	HookT<MUITree, void*, MUIP_NListtree_ConstructMessage*>     hHkConstruct;
	HookT<MUITree, void*, MUIP_NListtree_DestructMessage*>      hHkDestruct;
	HookT<MUITree, void*, MUIP_NListtree_DisplayMessage*>       hHkDisplay;
	HookT<MUITree, void*, void*>                                hHkSelect;

    protected:
	virtual iptr   doConstruct(void*, MUIP_NListtree_ConstructMessage*);
	virtual iptr   doDestruct(void*, MUIP_NListtree_DestructMessage*);
	virtual iptr   doDisplay(void*, MUIP_NListtree_DisplayMessage*);
	virtual iptr   doSelect(void*, void*);

    public:
	MUITree(const char *format, bool multiselect=false);
	virtual                ~MUITree(); 
	virtual iptr  *getObject();
	virtual void            setConstructHook(const Hook* hook);       // void*, <source>
	virtual void            setDestructHook(const Hook* hook);        // void*, <element>
	virtual void            setDisplayHook(const Hook* hook);         // const char**, <element>
	virtual void            setSelectionHook(const Hook* hook);       // <element> active, void*
	virtual void            setWeight(int weight);

	virtual iptr   addEntry(iptr parent, void* data, bool opened=false);
	virtual void            showObject(void* data, bool expand);
	virtual void            clear();
	virtual VectorT<void*> &getSelectedObjects();

	virtual void            setEnabled(bool enabled);
    };
};

#endif

