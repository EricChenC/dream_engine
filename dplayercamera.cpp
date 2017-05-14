#include "dplayercamera.h"

#include <qpoint.h>

namespace de {
DPlayerCamera::DPlayerCamera()
{
	mouse_speed_ = 0.005f;
	horizontal_angle_ = 0.0f;
	vertical_angle_ = 0.0f;
	move_pace_ = 0.1f;

	view_position_ = QVector3D(0.0f, 1.0f, -6.0f);
	view_center_ = QVector3D(0.0f, 0.0f, 0.0f);
	view_up_ = QVector3D(0.0f, 1.0f, 0.0f);

	projection_angle_ = 45.0f;
	projection_ratio_ = 4.0f / 3.0f;
	projection_near_ = 0.1f;
	projection_far_ = 1000.0f;

	Model_.setToIdentity();
	UpdateViewMatrix();
	UpdateProjectionMatrix();

	// init camera rotate position 
	RotateCamera(QPoint(0,1));

}

DPlayerCamera::~DPlayerCamera()
{
}

void DPlayerCamera::RotateCamera(const QPoint& pos)
{
	horizontal_angle_ += mouse_speed_ * pos.x();
	vertical_angle_ += mouse_speed_ * pos.y();

	view_direction_ = QVector3D(
		cos(vertical_angle_) * sin(horizontal_angle_),
		sin(vertical_angle_),
		cos(vertical_angle_) * cos(horizontal_angle_)
	);

	view_right_ = QVector3D(
		sin(horizontal_angle_ - 3.14f / 2.0f),
		0,
		cos(horizontal_angle_ - 3.14f / 2.0f)
	);

	view_center_ = view_position_ + view_direction_;
	view_up_ = QVector3D::crossProduct(view_right_, view_direction_);
	UpdateViewMatrix();
}

void DPlayerCamera::MoveForward()
{
	QVector3D direc = view_center_ - view_position_;

	view_position_ += direc * move_pace_;
	view_center_ += direc * move_pace_;
	UpdateViewMatrix();
}

void DPlayerCamera::MoveBack()
{
	QVector3D direc = view_center_ - view_position_;

	view_position_ -= direc * move_pace_;
	view_center_ -= direc * move_pace_;
	UpdateViewMatrix();
}

void DPlayerCamera::MoveLeft()
{
	QVector3D direc = view_center_ - view_position_;
	QVector3D right = QVector3D::crossProduct(direc, view_up_);

	view_position_ -= right * move_pace_;
	view_center_ -= right * move_pace_;
	UpdateViewMatrix();
}

void DPlayerCamera::MoveRight()
{
	QVector3D direc = view_center_ - view_position_;
	QVector3D right = QVector3D::crossProduct(direc, view_up_);

	view_position_ += right * move_pace_;
	view_center_ += right * move_pace_;
	UpdateViewMatrix();
}

void DPlayerCamera::MoveUp()
{
	view_position_ += view_up_.normalized() * move_pace_;
	view_center_ += view_up_.normalized() * move_pace_;
	UpdateViewMatrix();
}

void DPlayerCamera::MoveDown()
{
	view_position_ -= view_up_ * move_pace_;
	view_center_ -= view_up_ * move_pace_;
	UpdateViewMatrix();
}

void DPlayerCamera::UpdateProjectionRatio(const float & ratio)
{
	projection_ratio_ = ratio;
	UpdateProjectionMatrix();
}

const QMatrix4x4& DPlayerCamera::get_m() const
{
	return Model_;
}

const QMatrix4x4& DPlayerCamera::get_v() const
{
	return View_;
}

const QMatrix4x4& DPlayerCamera::get_p() const
{
	return Projection_;
}

const QMatrix4x4& DPlayerCamera::get_mv() const
{
	return View_ * Model_;
}

const QMatrix4x4& DPlayerCamera::get_mvp() const
{
	return Projection_ * View_ * Model_;
}

void DPlayerCamera::UpdateModelMatrix()
{

}

void DPlayerCamera::UpdateViewMatrix()
{
	View_.setToIdentity();
	View_.lookAt(view_position_, view_center_, view_up_);
}

void DPlayerCamera::UpdateProjectionMatrix()
{
	Projection_.setToIdentity();
	Projection_.perspective(projection_angle_, projection_ratio_, projection_near_, projection_far_);
}

}

