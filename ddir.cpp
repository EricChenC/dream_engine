#include "ddir.h"

#include <qdir.h>
#include <qstring.h>
#include <qstringlist.h>


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
	QString absolute_path = dir.absolutePath();
	QStringList paths = absolute_path.split("dream_engine_build");

	QString media_path = paths[0] + "dream_engine/media/" + QString(QLatin1String(path));
	byte_path_ = media_path.toLatin1();
	full_path_ = byte_path_.data();

	return full_path_;
}

}

