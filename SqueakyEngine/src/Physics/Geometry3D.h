#pragma once
#include <glm/vec3.hpp>
#include <glm/matrix.hpp>
#include <glm/geometric.hpp>
#include "ExtraMath.h"

namespace Geometry {
	//class Geometry3D
	//{

	//public:
	struct Line {
		glm::vec3 start;
		glm::vec3 end;

		inline Line() {}
		inline Line(const glm::vec3& s, const glm::vec3& e) :
			start(s), end(e) { }
		inline float Length(const Line& line) {
			return glm::length(line.start - line.end);
		}
		inline float LengthSq(const Line& line) {
			return ExtraMath::MagSqr(line.start - line.end);
		}
	};
	struct Ray
	{
		glm::vec3 origin;
		glm::vec3 direction;

		inline Ray() : origin(0.f), direction(0.f, 0.f, 1.f) {}
		inline Ray(const glm::vec3& origin_, const glm::vec3& direction_) : origin(origin_), direction(direction_) {
			direction = glm::normalize(direction);
		}

	};
	//using Sphere = Geometry::Sphere;
	struct Sphere {
		glm::vec3 origin;
		float radius;
		inline Sphere() : origin(0.f), radius(0.f) {}
		inline Sphere(const glm::vec3& origin_, const float& rad) : origin(origin_), radius(rad) {
		}

	};

	struct AABB {
		glm::vec3 origin;
		glm::vec3 size;

		inline AABB() : origin(0.f), size(0.f, 0.f, 1.f) {}
		inline AABB(const glm::vec3& origin_, const glm::vec3& size_) : origin(origin_), size(size_) {

		}
		inline AABB(const glm::vec3& min, const glm::vec3& max,bool minMax) {
			origin = (min + max) * 0.5f;
			size = (max - min) * 0.5f;
		}
		inline glm::vec3 GetMin() const {
			glm::vec3 p1 = origin + size;
			glm::vec3 p2 = origin - size;

			return glm::vec3(fminf(p1.x, p2.x),
				fminf(p1.y, p2.y),
				fminf(p1.z, p2.z));
		}
		inline glm::vec3 GetMax() const {
			glm::vec3 p1 = origin + size;
			glm::vec3 p2 = origin - size;

			return glm::vec3(fmaxf(p1.x, p2.x),
				fmaxf(p1.y, p2.y),
				fmaxf(p1.z, p2.z));
		}
	};

	struct OBB {
		glm::vec3 origin;
		glm::vec3 size;
		glm::mat3 orientation;

		inline OBB() : size(1, 1, 1) {}
		inline OBB(const glm::vec3& p, const glm::vec3& s) :
			origin(p), size(s) { }
		inline OBB(const glm::vec3& p, const glm::vec3& s, const glm::mat3& o)
			: origin(p), size(s), orientation(o) { }
	};

	struct Plane {
		glm::vec3 normal;
		float distance;

		inline Plane() : normal(1, 0, 0) { }
		inline Plane(const glm::vec3& n, float d) :
			normal(n), distance(d) { }
		inline float PlaneEquation(const glm::vec3& point) {
			return glm::dot(point, normal) - distance;
		}
	};

	struct Triangle {
		glm::vec3 a;
		glm::vec3 b;
		glm::vec3 c;
		inline Triangle() { }
		inline Triangle(const glm::vec3& p1, const glm::vec3& p2,
			const glm::vec3& p3) : a(p1), b(p2), c(p3) { }
	};
};
