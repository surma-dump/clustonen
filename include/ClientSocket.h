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

#ifndef FOOCLIENTSOCKETFOO
#define FOOCLIENTSOCKETFOO

#include "Socket.h"

class ClientSocket : public Socket
{
public:
	ClientSocket(std::string host, int port) ; // Constructor
	virtual ~ClientSocket() ; // Destructor
		
protected:
	void connect(std::string host, int port) ; // Connect Socket to host

private:
} ;

#endif 