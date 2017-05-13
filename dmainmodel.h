#pragma once

#ifndef DMAINMODEL_H
#define DMAINMODEL_H

#include "diview.h"

#include <qmap.h>
#include <qlist.h>

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
		MODELSHOW
	};

	de::DIView *view_;
	de::DIView *old_view_;
	QMap<QString, int> *proj_map_;

};

#endif // !DMAINMODEL_H


