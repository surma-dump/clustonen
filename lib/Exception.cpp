#include "Exception.h"

Exception::Exception (std::string _msg)
{
	msg = _msg ;
}

Exception::~Exception ()
{
}

std::string Exception::getMessage()
{
	return msg ;
}
