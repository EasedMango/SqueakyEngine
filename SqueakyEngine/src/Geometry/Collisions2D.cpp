//
//#include "Collisions2D.h"
//#include "ExtraMath.h"
//
//#define CMP(x,y) (fabsf((x)-(y)) <= FLT_EPSILON * fmaxf(1.0f,fmaxf(fabsf(x),fabsf(y)))
//
//bool Collisions2D::PointOnLine(const Point2D& point, const Line2D& line)
//{
//	// Find the slope
//	float dy = (line.end.y - line.start.y);
//	float dx = (line.end.x - line.start.x);
//	float M = dy / dx;
//	// Find the Y-Intercept
//	float B = line.start.y - M * line.start.x;
//	// Check line equation
//	return CMP(point.y, M * point.x + B));
//}
//
//bool Collisions2D::PointInCircle(const Point2D& point, const Circle& c)
//{
//	Line2D line(point, c.position);
//	if (line.LengthSq() < c.radius * c.radius) {
//		return true;
//	}
//	return false;
//}
//
//bool Collisions2D::PointInRectangle(const Point2D& point, const Rectangle2D& rectangle)
//{
//	glm::vec2 min = (rectangle).GetMin();
//	glm::vec2 max = (rectangle).GetMax();
//
//	return  min.x <= point.x &&
//		min.y <= point.y &&
//		point.x <= max.x &&
//		point.y <= max.y;
//}
//
//bool Collisions2D::LineCircle(const Line2D& l, const Circle& c) {
//	glm::vec2 ab = l.end - l.start;
//	float t = glm::dot(c.position - l.start, ab) / glm::dot(ab, ab);
//	if (t < 0.0f || t > 1.0f) {
//		return false;
//	}
//	Point2D closestPoint = l.start + ab * t;
//
//	Line2D circleToClosest(c.position, closestPoint);
//	return (circleToClosest).LengthSq() < c.radius * c.radius;
//}
//bool Collisions2D::LineRectangle(const Line2D& l, const Rectangle2D& r) {
//	if (PointInRectangle(l.start, r) ||
//		PointInRectangle(l.end, r)) {
//		return true;
//	}
//
//	glm::vec2 norm = glm::normalize(l.end - l.start);
//	norm.x = (norm.x != 0) ? 1.0f / norm.x : 0;
//	norm.y = (norm.y != 0) ? 1.0f / norm.y : 0;
//	glm::vec2 min = ((r).GetMin() - l.start) * norm;
//	glm::vec2 max = ((r).GetMax() - l.start) * norm;
//
//	float tmin = fmaxf(
//		fminf(min.x, max.x),
//		fminf(min.y, max.y)
//	);
//	float tmax = fminf(
//		fmaxf(min.x, max.x),
//		fmaxf(min.y, max.y)
//	);
//	if (tmax< 0 || tmin>tmax) {
//		return false;
//	}
//	float t = (tmin < 0.0f) ? tmax : tmin;
//	return t > 0.0f && t * t < l.LengthSq();
//}
//
//bool Collisions2D::PointInOrientedRectangle(const Point2D& point, const OrientedRectangle& rectangle)
//{
//	glm::vec2 rotVector = point - rectangle.position;
//	float theta = -glm::radians(rectangle.rotation);
//	glm::mat2 zRotation2x2 = {
//	   cosf(theta), sinf(theta),
//	   -sinf(theta), cosf(theta)
//	};
//	rotVector *= zRotation2x2;
//
//	Rectangle2D localRectangle(Point2D(),
//		rectangle.halfExtents * 2.0f);
//	glm::vec2 localPoint = rotVector + rectangle.halfExtents;
//	return PointInRectangle(localPoint, localRectangle);
//}
//
//bool Collisions2D::LineOrientedRectangle(const Line2D& line,
//	const OrientedRectangle& rectangle) {
//	float theta = glm::radians(rectangle.rotation);
//	glm::mat2 zRotation2x2 = {
//	   cosf(theta), sinf(theta),
//	   -sinf(theta), cosf(theta)
//	};
//	Line2D localLine;
//
//	glm::vec2 rotVector = line.start - rectangle.position;
//	rotVector = glm::vec2(rotVector.x, rotVector.y) * zRotation2x2;
//	localLine.start = rotVector + rectangle.halfExtents;
//
//	rotVector = line.end - rectangle.position;
//	rotVector = glm::vec2(rotVector.x, rotVector.y) * zRotation2x2;
//	localLine.end = rotVector + rectangle.halfExtents;
//
//	Rectangle2D localRectangle(Point2D(),
//		rectangle.halfExtents * 2.0f);
//	return LineRectangle(localLine, localRectangle);
//}