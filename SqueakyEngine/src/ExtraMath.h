//#pragma once
//#define GLM_ENABLE_EXPERIMENTAL
//#include <glm/glm.hpp>
//#include <glm/ext.hpp>	
//
//
//
//#define WATCH_VEC3(v) std::cout << #v" = " << v.x << " " <<v.y << " " << v.z << std::endl;
//
//
//	class ExtraMath {
//	public:
//		static void Print(const glm::vec3& v);
//
//
//		//static float Angle(const glm::vec2& l, const glm::vec2& r);
//		//static float Angle(const glm::vec3& l, const glm::vec3& r);
//
//		//static glm::vec2 Project( const glm::vec2& length, const glm::vec2& direction);
//		// static glm::vec3 Project(const glm::vec3& length, const glm::vec3& direction);
//
//		// static glm::vec2 Perpendicular(const glm::vec2& len, const glm::vec2& dir);
//		// static glm::vec3 Perpendicular(const glm::vec3& len, const glm::vec3& dir);
//
//		// static glm::vec2 Reflection(const glm::vec2& vec, const glm::vec2& normal);
//		// static glm::vec3 Reflection(const glm::vec3& vec, const glm::vec3& normal);
//
//		 static float MagSqr(const glm::vec2& v);
//		 static float MagSqr(const glm::vec3& v);
//
//		 static glm::mat2 Cut(const glm::mat3& mat,int row,int col);
//		 static glm::mat4 Cut(const glm::mat4& mat, int row, int col);
//		 static glm::mat4 Minor(const  glm::mat4& mat);
//		 static glm::mat2 Minor(const  glm::mat2& mat);
//		 static glm::mat3 Minor(const  glm::mat3& mat);
//		 static glm::mat4 Rot(float p, float y, float r);
//		 static glm::mat3 Rot3x3(float p, float y, float r);
//		 inline static glm::vec3 GetTranslation(glm::mat4x4 mat) { return glm::vec3(mat[3]); }
//		 inline static glm::vec3 GetScale(glm::mat4x4 mat) { return glm::vec3(mat[0][0], mat[1][1], mat[2][2]); }
//
//		 static void Cofactor(float* out, const float* minor,
//			 int rows, int cols);
//		 static glm::mat3 Cofactor(const glm::mat3& mat);
//		 static glm::mat2 Cofactor(const glm::mat2& mat);
//		 static glm::mat4 Cofactor(const glm::mat4& mat);
//	};
//
