#include "ddir.h"

#include <qdir.h>
#include <qstring.h>


namespace de {
DDir::DDir()
{
}

DDir::~DDir()
{
}

char* DDir::get_dir(const char* path)
{
	QDir dir;
	QString media_path = dir.absolutePath() + "/media/" + QString(QLatin1String(path));

	byte_path_ = media_path.toLatin1();
	full_path_ = byte_path_.data();

	return full_path_;
}

}

