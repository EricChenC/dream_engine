#pragma once

#ifndef DMAINMODEL_H
#define DMAINMODEL_H

#include <qlist.h>
#include <qmap.h>

namespace de {
	class DIView;
}

class DMainModel
{
public:
	DMainModel();
	~DMainModel();

	void InitModel();
	QList<QString> get_projects();
	QList<QString> get_modes();

	de::DIView* get_view(const QString& name = "model_show");

	void set_polygon_mode(const QString& mode = "fill");

	void ClearOldView();

private:
	enum Project
	{
		DEFAULT,
		SHADOW,
		TRIANGLES,
		SPOTLIGHT,
		MODELSHOW,
		BOUNDINGBOX,
		SPECULAR,
		MULTITEXTURE
	};

	enum Mode
	{
		MODE_FILL,
		MODE_LINE,
		MODE_POINT
	};

	de::DIView *view_;
	de::DIView *old_view_;
	QMap<QString, int> *proj_map_;
	QMap<QString, int> *mode_map_;

};

#endif // !DMAINMODEL_H


