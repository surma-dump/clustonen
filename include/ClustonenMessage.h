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
 * If you need to type ' in the Value, you can do this by backslashing it
 */
class ClustonenMessage
{
public:
	ClustonenMessage(); // Constructor
	ClustonenMessage(const ClustonenMessage& msg); // Copy Constructor
	ClustonenMessage(const std::string& _name, const std::string& _data) ; // Constructs a message with name and data field
	ClustonenMessage(const std::string& pack) ; // Constructs a message out of toString()-string
	virtual ~ClustonenMessage() ; // Destructor
	std::string getName() const; // returns name of the message
	std::string getField(const std::string& field) const; // returns certain field of the data
	std::string getData() const; // returns whole data string
	void setName(const std::string& _name) ; // sets the name
	void setData(const std::string& _data) ; // sets the whole data
	void addData(const std::string& _data) ; // adds new data
	void addField(const std::string& field, const std::string& value) ; // set a single field
	void delField(const std::string& field) ; // deletes a field
	int getNumFields() const ; // returns number of defined fields
	std::string toString() const; // converts the instance into a representing string
	void fromString(const std::string& pack); // Sets the data using a toString()-string
protected:
	void parse(const std::string& _data) ; // parses a string and fills values into data
	void unescapeData(std::string& _data);
private:
	std::string name ;
	std::map<std::string, std::string> data ;
};
#endif
