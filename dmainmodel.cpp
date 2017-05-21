#include "dmainmodel.h"

#include "dview.h"
#include "shadow.h"
#include "simpletriangle.h"
#include "spotlight.h"
#include "modelshow.h"
#include "boundingbox.h"
#include "specular.h"
#include "multitexture.h"


DMainModel::DMainModel()
	: old_view_(NULL)
{
	view_ = new DView();
}


DMainModel::~DMainModel()
{
	proj_map_->clear();
	delete proj_map_;
	mode_map_->clear();
	delete mode_map_;
	view_->disableGL();
	delete view_;
}

void DMainModel::InitModel()
{
	proj_map_ = new QMap<QString,int>();
	proj_map_->insert("model_show", MODELSHOW);
	proj_map_->insert("shadow", SHADOW);
	proj_map_->insert("triangle", TRIANGLES);
	proj_map_->insert("spotlight", SPOTLIGHT);
	proj_map_->insert("bounding_box", BOUNDINGBOX);
	proj_map_->insert("specular", SPECULAR);
	proj_map_->insert("multi_texture", MULTITEXTURE);

	mode_map_ = new QMap<QString, int>();
	mode_map_->insert("fill", MODE_FILL);
	mode_map_->insert("line", MODE_LINE);
	mode_map_->insert("point", MODE_POINT);
}

QList<QString> DMainModel::get_projects()
{
	return proj_map_->keys();
}

QList<QString> DMainModel::get_modes()
{
	return mode_map_->keys();
}

de::DIView * DMainModel::get_view(const QString& name)
{
	old_view_ = view_;

	//restore glEnable() setting
	old_view_->disableGL();

	switch (proj_map_->value(name))
	{
	case MODELSHOW:
		view_ = new ModelShow();
		break;
	case SHADOW:
		view_ = new Shadow();
		break;
	case TRIANGLES:
		view_ = new SimpleTriangle();
		break;
	case SPOTLIGHT:
		view_ = new SpotLight();
		break;
	case BOUNDINGBOX:
		view_ = new BoundingBox();
		break;
	case SPECULAR:
		view_ = new Specular();
		break;
	case MULTITEXTURE:
		view_ = new MultiTexture();
		break;
	default:
		view_ = new ModelShow();
		break;
	}

	// save lasted view w and h
	view_->resizeGL(old_view_->get_w(), old_view_->get_h());

	return view_;
}

void DMainModel::set_polygon_mode(const QString & mode)
{
	switch (mode_map_->value(mode))
	{
	case MODE_LINE:
		view_->set_polygon_mode(MODE_LINE);
		break;
	case MODE_POINT:
		view_->set_polygon_mode(MODE_POINT);
		break;
	case MODE_FILL:
	default:
		view_->set_polygon_mode(MODE_FILL);
		break;
	}
}

void DMainModel::ClearOldView()
{
	delete old_view_;
	old_view_ = NULL;
}
