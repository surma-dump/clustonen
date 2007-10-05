/**
 * Copyright (C) 2007  Alexander Surma <crock@drebesium.org>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as published
 * by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include "ClustonenModule.h"

ClustonenModule::ClustonenModule()
{
}

ClustonenModule::~ClustonenModule()
{
}

/**
 * Sends a message to a someone. Actually passes it on to the MessageManager 
 * who will send it to  the receipient.
 * @param msg Pointer to the message to send
 */
void ClustonenModule::sendMessage(ClustonenMessage *msg)
{
	// TODO
}

void ClustonenModule::setMessageManager(MessageManager *_mm)
{
	mm = _mm ;
}
