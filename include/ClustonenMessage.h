#ifndef FOOCLUSTONENMESSAGEFOO
#define FOOCLUSTONENMESSAGEFOO
#include <map> 
#include <string>

/**
 * Represents a message exchanged between e.g clients and server 
 *
 * Messagedata can be defined in the following format:
 * FIELNAME1='FIELDVALUE1';FIELDNAME2='FIELDVALUE2';...
 * If you need to type ' in the Value, you can do this by backslashing it
 */
class ClustonenMessage
{
public:
	ClustonenMessage(); // Constructor
	ClustonenMessage(const std::string& _name, const std::string& _data) ; // Constructs a message with name and data field
	ClustonenMessage(const std::string& pack) ; // Constructs a message out of toString()-string
	virtual ~ClustonenMessage() ; // Destructor
	std::string getName() ; // returns name of the message
	std::string getField(const std::string& field) ; // returns certain field of the data
	std::string getData() ; // returns whole data string
	void setName(const std::string& _name) ; // sets the name
	void setData(const std::string& _data) ; // sets the whole data
	void addData(const std::string& _data) ; // adds new data
	void addField(const std::string& field, const std::string& value) ; // set a single field
	void delField(const std::string& field) ; // deletes a field
	std::string toString() ; // converts the instance into a representing string
protected:
	void parse(const std::string& _data) ; // parses a string and fills values into name and data
private:
	std::string name ;
	std::map<std::string, std::string> data ;
};
#endif
