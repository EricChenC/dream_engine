#include "dmainmodel.h"

#include "dview.h"
#include "shadow.h"

DMainModel::DMainModel()
	: view_(NULL),
	old_view_(NULL)
{
}


DMainModel::~DMainModel()
{
	proj_map_->clear();
	delete proj_map_;
	delete view_;
}

void DMainModel::InitModel()
{
	proj_map_ = new QMap<QString,int>();
	proj_map_->insert("default", DEFAULT);
	proj_map_->insert("shadow", SHADOW);
}

QList<QString> DMainModel::get_projects()
{
	return proj_map_->keys();
}

de::DIView * DMainModel::get_view(const QString& name)
{
	old_view_ = view_;

	switch (proj_map_->value(name))
	{
	case DEFAULT:
		view_ = new DView();
		break;
	case SHADOW:
		view_ = new Shadow();
		break;
	default:
		view_ = new DView();
		break;
	}

	return view_;
}

void DMainModel::ClearOldView()
{
	delete old_view_;
	old_view_ = NULL;
}
