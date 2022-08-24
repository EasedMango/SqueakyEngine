//#pragma once
//
//#include "ExtraMath.h"
//#include <glm/glm.hpp>
//typedef glm::vec2 Point2D;
//
//typedef struct Line2D {
//	Point2D start;
//	Point2D end;
//
//	inline Line2D() {}
//	inline Line2D(const Point2D& s, const Point2D& e) : start(s), end(e) {}
//	float Length(const Line2D& line);
//	float LengthSq(const Line2D& line);
//	inline float Length() const {
//		return glm::length(end - start);
//	}
//
//	inline float LengthSq() const {
//		return ExtraMath::MagSqr(end - start);
//	}
//} Line2D;
//
//typedef struct Circle {
//	Point2D position;
//	float radius;
//	inline Circle() : radius(1.0f) {}
//	inline Circle(const Point2D& p, float r) : position(p), radius(r) {}
//} Circle;
//
//typedef struct Rectangle2D {
//	Point2D origin;
//	glm::vec2 size;
//
//	inline Rectangle2D() : size(1, 1) {}
//	inline Rectangle2D(const Point2D& o, const glm::vec2& s) : origin(o), size(s) {}
//	glm::vec2   GetMin()const;
//	glm::vec2   GetMax()const;
//	Rectangle2D FromMinMax(const glm::vec2& min, const glm::vec2& max);
//
//} Rectangle2D;
//
//typedef struct OrientedRectangle {
//	Point2D position;
//	glm::vec2 halfExtents;
//	float rotation;
//	inline OrientedRectangle() :
//		halfExtents(1.0f, 1.0f), rotation(0.0f) { }
//	inline OrientedRectangle(const Point2D& p, const glm::vec2& e) :
//		position(p), halfExtents(e), rotation(0.0f) { }
//	inline OrientedRectangle(const Point2D& pos,
//		const glm::vec2& ext, float rot) :
//		position(pos), halfExtents(ext), rotation(rot) { }
//} OrientedRectangle;
//
//
//
