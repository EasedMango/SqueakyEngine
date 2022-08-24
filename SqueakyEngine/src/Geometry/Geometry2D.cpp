//#include "Geometry2D.h"
//
//
//
//
//glm::vec2   Rectangle2D::GetMin() const {
//	glm::vec2 p1 = origin;
//	glm::vec2 p2 = origin + size;
//
//	return glm::vec2(fminf(p1.x, p2.x), fminf(p1.y, p2.y));
//}
//
//glm::vec2   Rectangle2D::GetMax() const {
//	glm::vec2 p1 = origin;
//	glm::vec2 p2 = origin + size;
//
//	return glm::vec2(fmaxf(p1.x, p2.x), fmaxf(p1.y, p2.y));
//}
//
//Rectangle2D Rectangle2D::FromMinMax(const glm::vec2& min, const glm::vec2& max)
//{
//	return Rectangle2D(min, max - min);
//}
//
//
//
//
//
//
