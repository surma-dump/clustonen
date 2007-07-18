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
	ServerSocket p(22001);
	try{p.waitForConnection() ;}
	catch (Exception e) { printf ("%s", e.getMessage().c_str()) ; p.close() ;}
	printf("Other Side: %s\n", p.getOpponent().c_str()) ;
	//try{printf("%s", p.read().c_str()) ;}
	//catch (Exception e) { printf ("%s", e.getMessage().c_str()) ; }
	int d ;
	try{d = p.read() ;}
	catch (Exception e) { printf ("%s", e.getMessage().c_str()) ; p.close() ;}
	const char* m = p.getMessage() ;
	char n[MAXLEN] ;
	memset (n, 0, MAXLEN) ;
	memcpy (n, m, d) ;
	
	n[d]='\0';
	n[d+1]='\0';
	printf("%s", n) ;
	p.close() ;
}
