#pragma once

#ifndef DPLAYERCAMERA_H
#define DPLAYERCAMERA_H

#include <qmatrix4x4.h>
#include <qvector3d.h>
#include <qpoint.h>

namespace de {
class DPlayerCamera
{
public:
	explicit DPlayerCamera();
	~DPlayerCamera();

	void RotateCamera(const QPoint& pos);
	void MoveForward();
	void MoveBack();
	void MoveLeft();
	void MoveRight();
	void MoveUp();
	void MoveDown();
	void UpdateProjectionRatio(const float& ratio);

	const QMatrix4x4 get_m() const;
	const QMatrix4x4 get_v() const;
	const QMatrix4x4 get_p() const;
	const QMatrix4x4 get_mv() const;
	const QMatrix4x4 get_mvp() const;

private:
	float mouse_speed_;
	float horizontal_angle_;
	float vertical_angle_;
	float move_pace_;

	QMatrix4x4 Model_;
	QMatrix4x4 View_;
	QMatrix4x4 Projection_;

	QVector3D view_direction_;
	QVector3D view_right_;

	QVector3D view_position_;
	QVector3D view_center_;
	QVector3D view_up_;

	float projection_angle_;
	float projection_ratio_;
	float projection_near_;
	float projection_far_;

	void UpdateModelMatrix();
	void UpdateViewMatrix();
	void UpdateProjectionMatrix();

};
}

#endif // !DPLAYERCAMERA_H



