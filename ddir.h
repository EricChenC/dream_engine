#pragma once

#ifndef DDIR_H
#define DDIR_H

#include <qstring.h>
#include <qbytearray.h>

namespace de {
class DDir
{
public:
	explicit DDir();
	~DDir();

	char* get_dir(const char* path);

private:
	QByteArray byte_path_;
	char* full_path_;

};
}


#endif // !DDIR_H




