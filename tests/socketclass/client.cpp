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
#include "ClientSocket.h"

int main()
{
	ClientSocket* p;
	printf ("Opening Socket and connecting to host...\n") ;
	try { p = new ClientSocket ("127.0.0.1", 22002);}
	catch (Exception e) { printf ("%s", e.getMessage().c_str()) ; delete p ; exit(1) ;}

	printf ("Connected: %s...\n", p->getOpponent().c_str());
	printf ("Reading...\n") ;
	try { p->read();}
	catch (Exception e) { printf ("%s", e.getMessage().c_str()) ; delete p ; exit(1) ;}
	printf("Received: \"%s\"\n", p->getMessage()) ;

	printf ("Sending answer...\n") ;
	char msg[] = "This is the client's answer!\0" ;
	try { p->write(msg, strlen(msg)) ;}
	catch (Exception e) { printf ("%s", e.getMessage().c_str()) ; delete p ; exit(1) ;}

	printf ("Reading...\n") ;
	try { p->read();}
	catch (Exception e) { printf ("%s", e.getMessage().c_str()) ; delete p ; exit(1) ;}
	printf("Received: \"%s\"\n", p->getMessage()) ;

	p->close() ;
	delete p ;
}
