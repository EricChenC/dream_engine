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
	de::DIView* get_view(const QString& name = "model_show");
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

	de::DIView *view_;
	de::DIView *old_view_;
	QMap<QString, int> *proj_map_;

};

#endif // !DMAINMODEL_H


