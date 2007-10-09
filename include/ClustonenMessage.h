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

#ifndef FOOCLUSTONENMESSAGEFOO
#define FOOCLUSTONENMESSAGEFOO
#include <map> 
#include <string>
#include <string.h>
#include <regex.h>
#include "Exception.h" 

#define MAXFIELDNAME 255
#define MAXFIELDVALUE 65535

/**
 * Represents a message exchanged between e.g clients and server 
 *
 * Messagedata can be defined in the following format:
 * FIELDNAME1='FIELDVALUE1';FIELDNAME2='FIELDVALUE2';...
 * If you need to type ' in the Value, you can do this by backslashing it. Backslashes
 * before a Apostroph can be used by backslashing them also.
 */
class ClustonenMessage
{
public:
	ClustonenMessage();
	ClustonenMessage(const ClustonenMessage& msg); 
	ClustonenMessage(std::string& _name, const std::string& _data) ;
	ClustonenMessage(const std::string& pack) ; 
	virtual ~ClustonenMessage() ;

	// returns name of the message 
	std::string getName() const; 

	// returns certain field of the data
	std::string getField(const std::string& field) const;

	// returns whole data string
	std::string getData() const;

	// sets the name
	void setName(const std::string& _name) ; 
	
	// sets the whole data
	void setData(const std::string& _data) ;

	// adds new data
	void addData(const std::string& _data); 

	// set a single field
	void addField(const std::string& field, const std::string& value);

	// deletes a field
	void delField(const std::string& field); 

	// returns number of defined fields
	int getNumFields() const;

	// converts the instance into a representing string
	std::string toString() const;

	// Sets the data using a toString()-string
	void fromString(const std::string& pack);

	// Sets destination
	void setDestination(const std::string& _destination);

	// Sets origin
	void setOrigin(const std::string& _origin);
	
	// Returns destination
	std::string getDestination();

	// Returns origin
	std::string getOrigin();

protected:
	// parses a string and fills values into data
	void parse(const std::string& _data) ;

	// unescapes aprostrophs from the field values
	void unescapeData(std::string& _data);
private:
	std::string name ;
	std::map<std::string, std::string> data ;
	std::string origin, destination ;
};
#endif
