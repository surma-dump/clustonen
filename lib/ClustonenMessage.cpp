#include "ClustonenMessage.h"

/**
 * Standardconstructor
 */
ClustonenMessage::ClustonenMessage()
{
}

/**
 * Constructor with initialization
 * @param name Identifier of the message
 * @param data Data of the message (see class definition)
 */
ClustonenMessage::ClustonenMessage(const std::string& _name, const std::string& _data)
{
	name = _name ;
	parse (_data) ;
}

/**
 * Constructor for a message. Works as the reversion of toString()
 * @param pack String created by toString()
 */
ClustonenMessage::ClustonenMessage(const std::string& pack)
{
	parse (pack) ;
}

/**
 * Destructor
 */
ClustonenMessage::~ClustonenMessage()
{
}

/**
 * Get name of message
 * @returns Name of the message as a string
 */
std::string ClustonenMessage::getName()
{
	return name ;
}

/**
 * get value of a data filed
 * @param field  name of the field
 * @returns value of the field with the name defined above
 */
std::string ClustonenMessage::getField(const std::string& field)
{
	return data[field] ;
}

/**
 * Formats the saved data as a string
 * @returns data as a string
 */
std::string ClustonenMessage::getData()
{
	std::string ret = "" ;
	for (std::map<std::string, std::string>::iterator dataseg=data.begin(); dataseg != data.end(); dataseg++) // Run through every data segment
		ret += dataseg->first+"="+dataseg->second+";" ; // and append it formatted to the string
}

/**
 * Sets the name of the message
 * @param _name New name of the message
 */
void ClustonenMessage::setName(const std::string& _name)
{
	name = _name ;
}

/**
 * Deletes all previously saved data and parses the given string for new data
 * @param _data New data as a string
 */
void ClustonenMessage::setData (const std::string& _data)
{
	parse (_data) ;
}

/**
 * Parses a string for data and adds the result to the previously save data. Already existing keys will be overwritten.
 * @param _data Additional data as a string
 */
void ClustonenMessage::addData (const std::string& _data)
{
	parse(getData() + _data) ; // Get old data and append new one
}

/**
 * Adds a single field with value to the data
 * @param field Name of the field to add
 * @param value Value to assign to the field
 */
void ClustonenMessage::addField(const std::string& field, const std::string& value)
{
	data[field] = value ;
}

/**
 * Deletes a field from the saved data
 * @param field Name of the field to delete
 */
void ClustonenMessage::delField(const std::string& field)
{
	data.erase(field) ;
}

/**
 * Converts the message to a string usable by the 3rd constructor
 * @returns string representing the message
 */
std::string ClustonenMessage::toString()
{
	std::string ret = "name|" ;
	for (std::map<std::string, std::string>::iterator dataseg=data.begin(); dataseg != data.end(); dataseg++) // Run through every data segment
		ret+=dataseg->first+"="+dataseg->second+";" ; // and append it formatted to the string
	return ret ;
}
