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

#include <cstdio>
#include <cstdlib>
#include "ClustonenMessage.h"

int main()
{
	ClustonenMessage m("INITAL|FIELD1='VALUE1\\'VALUE1';") ; // Parse a string
	m.setName("UNINITAL") ; // set name of the message
	m.addField("FIELD2", "VALUE2;VALUE2") ; // add a field by hand
	m.addData ("FIELD3='VALUE3';") ; // add a field by parsing a string
	printf("Total: %s\n", m.toString().c_str()) ;
	printf("%s:\n", m.getName().c_str()) ;
	printf("\t%s\n", m.getData().c_str()) ;
	printf("Field 3 says \"%s\"\n", m.getField("FIELD3").c_str()) ;
	m.delField("FIELD2") ; // Delete a field
	printf("Total: %s\n", m.toString().c_str()) ;
}
