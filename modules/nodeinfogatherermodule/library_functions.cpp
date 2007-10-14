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

#include "NodeInfoGathererModule.h"

extern "C" const char* get_identifier() // >extern "C"< is needed to prevent symbol mangling
{
	return "NodeInfoGathererModule-v0.0.1-beta" ; // just return the modulename
}

extern "C" ClustonenModule* get_client_module(MessageManager *_mm) // s.a.
{
	return (ClustonenModule*)(new NodeInfoGathererModule(_mm)) ; // just return an initialize module
}

extern "C" ClustonenModule* get_server_module(MessageManager *_mm)
{
	return NULL;
}
