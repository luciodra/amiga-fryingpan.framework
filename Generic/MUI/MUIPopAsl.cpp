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

#include "MUIPopAsl.h"
#include <libclass/dos.h>
#include <libclass/intuition.h>
#include <libclass/muimaster.h>
#include <libraries/mui.h>
#include <Generic/LibrarySpool.h>
#include <libraries/asl.h>
#include <Generic/String.h>
#include <LibC/LibC.h>

#undef String
using namespace GenNS;

MUIPopAsl::MUIPopAsl(const char* name, PopType type) :
   MUIPopup(name)
{
   this->type = type;
   memset(value, 0, sizeof(value));
   hHkBtnHook.Initialize(this, &MUIPopAsl::buttonHandler);
   setButtonCallBack(hHkBtnHook.GetHook());
}

MUIPopAsl::~MUIPopAsl()
{
}

bool MUIPopAsl::onOpen()
{
   bool result = false;

   switch (type)
   {
      case Pop_Dir:
         {
            FileRequester *req;
            iptr tags[] =
            {
               ASLFR_DrawersOnly,      true,
               ASLFR_InitialDrawer,    (iptr)&value,
               ASLFR_DoMultiSelect,    false,
               TAG_DONE,               0
            };

            req = (FileRequester*)MUIMaster->MUI_AllocAslRequest(ASL_FileRequest, (TagItem*)NULL);
            result = MUIMaster->MUI_AslRequest(req, (TagItem*)tags);
            if (result)
            {
               BPTR lock = DOS->Lock(req->fr_Drawer, ACCESS_READ);
               if (0 != lock)
               {
                  DOS->NameFromLock(lock, (char*)&value, sizeof(value));
                  DOS->UnLock(lock);
               }
               else
               {
                  result = false;
               }
            }
            MUIMaster->MUI_FreeAslRequest(req);
         }
         break;

      case Pop_File:
         {
            FileRequester *req;
            iptr tags[] =
            {
               ASLFR_DrawersOnly,      false,
               ASLFR_InitialFile,      (iptr)&value,
               ASLFR_DoMultiSelect,    false,
               TAG_DONE,               0
            };

            req = (FileRequester*)MUIMaster->MUI_AllocAslRequest(ASL_FileRequest, (TagItem*)NULL);
            result = MUIMaster->MUI_AslRequest(req, (TagItem*)tags);
            if (result)
            {
               String name = req->fr_Drawer;
               name.AddPath(req->fr_File);

               BPTR lock = DOS->Lock(name.Data(), ACCESS_READ);
               if (0 != lock)
               {
                  DOS->NameFromLock(lock, (char*)&value, sizeof(value));
                  DOS->UnLock(lock);
               }
               else
               {
                  result = false;
               }
            }
            MUIMaster->MUI_FreeAslRequest(req);
         }
         break;
   };

   if (result != false)
   {
      setValue(value);
   }
 
   update();
   return false;
}

bool MUIPopAsl::onClose()
{
   return true;
}

iptr *MUIPopAsl::getPopDisplay()
{
   return muiString(value, 0, ID_String); 
}

iptr *MUIPopAsl::getPopButton()
{
   return PopButton(MUII_PopDrawer);
}

iptr *MUIPopAsl::getPopObject()
{
   return TextObject, End;
}

void MUIPopAsl::setValue(const void* string)
{
   strncpy(value, (const char*)string, sizeof(value)-1);
   if (string != NULL)
   {
      muiSetText(ID_String, (const char*)string);
   }
   else
   {
      muiSetText(ID_String, (const char*)"");
   }
}

const void *MUIPopAsl::getValue()
{
   return value;
}

iptr MUIPopAsl::buttonHandler(iptr id, void* data)
{
   switch (id)
   {
      case ID_String:
         {
            if (strcmp((const char*)value, (const char*)data))
            {
               strncpy(value, (char*)data, sizeof(value)-1);
               update();
            }
         }
         break;
   }
   return 0;
}

