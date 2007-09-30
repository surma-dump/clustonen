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

#ifndef FOOCLUSTONENSERVERFOO
#define FOOCLUSTONENSERVERFOO

#define AUTHOR "Alexander \"crock\" Surma <crock@drebesium.org>"
#define PROGNAME "clustonen-server"
#define VERSION "0.0.1"

#include <cstdio> // Basic I/O
#include <cstdlib> // pid_t
#include <unistd.h> // fork()
#include <argtable2.h> // argument parsing library


#include "ArgumentParser.h"
// #include "ServerSocket.h"

//#include <sys/types.h>


int main(int argc, char** argv) ; // Main Function
void daemonize() ; // Bring server to background

enum EXIT_STATUS
{
	SUCCESS = 0,
	ERROR_UNKNOWN_PARAMETER
} ;

#endif
