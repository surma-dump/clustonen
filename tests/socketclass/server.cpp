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
#include "ClustonenModule.h"
#include "ServerSocket.h"

int main()
{
	printf ("Opening Socket...\n") ;
	ServerSocket *p ;
	try {p = new ServerSocket(22002);}
	catch (Exception e) { printf ("%s", e.getMessage().c_str()) ; exit(1) ;}
	
	printf ("Beginning to listen...\n") ;
	try { p->waitForConnection() ;}
	catch (Exception e) { printf ("%s", e.getMessage().c_str()) ; delete p ; exit(1) ;}

	printf("Other Side: %s\n", p->getOpponent().c_str()) ;
	printf("Sending Hello...\n") ;
	try { p->write("Hello!", 6) ;}
	catch (Exception e) { printf ("%s", e.getMessage().c_str()) ; delete p ;  exit(1) ;}
       
	printf("Reading...\n") ;
	int d ;
	try { d = p->read() ;}
	catch (Exception e) { printf ("%s", e.getMessage().c_str()) ; delete p ; exit(1) ;}

	printf ("Client said: \"%s\"\n", p->getMessage()) ;

	printf ("Sending Bye...\n") ;
	try{ p->write("Bye!", 4) ;}
	catch (Exception e) { printf ("%s", e.getMessage().c_str()) ; delete p ;exit(1) ;}
	p->disconnect() ;
	p->close() ;
	delete  p ;
}
