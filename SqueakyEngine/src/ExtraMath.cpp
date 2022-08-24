//#include "ExtraMath.h"
//
//
//
//
//
//float ExtraMath::MagSqr(const glm::vec2& v)
//{
//	return glm::dot(v, v);
//}
//float ExtraMath::MagSqr(const glm::vec3& v)
//{
//	return glm::dot(v, v);
//}
//glm::mat2 ExtraMath::Cut(const glm::mat3& mat, int row, int col) {
//	glm::mat2 result;
//	int index = 0;
//
//	for (int i = 0; i < 3; ++i) {
//		for (int j = 0; j < 3; ++j) {
//			if (i == row || j == col) {
//				continue;
//			}
//			int target = index++;
//			int source = 3 * i + j;
//			result[target] = mat[source];
//		}
//	}
//
//	return result;
//};
// glm::mat4 ExtraMath::Cut(const glm::mat4& mat, int row, int col){
//	 glm::mat3 result;
//	 int index = 0;
//
//	 for (int i = 0; i < 4; ++i) {
//		 for (int j = 0; j < 4; ++j) {
//			 if (i == row || j == col) {
//				 continue;
//			 }
//			 int target = index++;
//			 int source = 4 * i + j;
//			 result[target] = mat[source];
//		 }
//	 }
//
//	 return result;
// }
// glm::mat4 ExtraMath::Minor(const  glm::mat4& mat){
// 
//	 glm::mat4 result;
//
//	 for (int i = 0; i < 4; ++i) {
//		 for (int j = 0; j < 4; ++j) {
//			 result[i][j] = glm::determinant(Cut(mat, i, j));
//		 }
//	 }
//
//	 return result;
// }
//
//glm::mat2 ExtraMath::Minor(const glm::mat2& mat) {
//
//	return glm::mat2(
//		mat[1][1], mat[1][0],
//		mat[0][1], mat[0][0]
//	);
//
//};
//glm::mat3 ExtraMath::Minor(const glm::mat3& mat) {
//	glm::mat3 result;
//
//	for (int i = 0; i < 3; ++i) {
//		for (int j = 0; j < 3; ++j) {
//			result[i][j] = glm::determinant(Cut(mat, i, j));
//		}
//	}
//	return result;
//};
//glm::mat4 ExtraMath::Cofactor(const glm::mat4& mat) {
//	glm::mat4 result;
//	Cofactor(glm::value_ptr(result), glm::value_ptr(Minor(mat)), 4, 4);
//	return result;
//}
//
//void ExtraMath::Cofactor(float* out, const float* minor, int rows, int cols) {
//	for (int i = 0; i < rows; ++i) {
//		for (int j = 0; j < cols; ++j) {
//			int t = cols * j + i; // Target index
//			int s = cols * j + i; // Source index
//			float sign = powf(-1.0f, i + j); // + or –
//			out[t] = minor[s] * sign;
//		}
//	}
//}
//glm::mat3 ExtraMath::Cofactor(const glm::mat3& mat) {
//	glm::mat3 result;
//	Cofactor(glm::value_ptr(result), glm::value_ptr(Minor(mat)), 3, 3);
//	return result;
//}
//glm::mat2 ExtraMath::Cofactor(const glm::mat2& mat) {
//	glm::mat2 result;
//	Cofactor(glm::value_ptr(result), glm::value_ptr( Minor(mat)), 2, 2);
//	return result;
//}
//
//
//
//
//glm::mat4 RotX(float x) {
//	return glm::rotate(glm::mat4(1), x, glm::vec3(1, 0, 0));
//}
//glm::mat4 RotY(float y) {
//	return glm::rotate(glm::mat4(1), y, glm::vec3(0, 1, 0));
//}
//glm::mat4 RotZ(float z) {
//	return glm::rotate(glm::mat4(1), z, glm::vec3(0, 0, 1));
//}
// glm::mat4 ExtraMath::Rot(float p, float y, float r) {
//	return RotZ(r) * RotX(p) * RotY(y);
//	
//}
//  glm::mat3 ExtraMath::Rot3x3(float p, float y, float r) {
//	  return RotZ(y) * RotX(p) * RotY(y);
// }
//
////glm/gtx/vector_angle
////float ExtraMath::Angle(const glm::vec2& l, const glm::vec2& r)
////{
////	float m = sqrtf(MagSqr(l) * MagSqr(r));
////	return acos(glm::dot(l, r) / m);
////	
////}
////
////float ExtraMath::Angle(const glm::vec3& l, const glm::vec3& r)
////{
////	float m = sqrtf(MagSqr(l) * MagSqr(r));
////	return acos(glm::dot(l, r) / m);
////
////}
//////glm/gtx/projection
////glm::vec2 ExtraMath::Project(const glm::vec2& length, const glm::vec2& direction)
////{
////	float dot = glm::dot(length, direction);
////	float magSq = MagSqr(direction);
////	return direction * (dot / magSq);
////
////}
////
////glm::vec3 ExtraMath::Project(const glm::vec3& length, const glm::vec3& direction)
////{
////	float dot = glm::dot(length, direction);
////	float magSq = MagSqr(direction);
////	return direction * (dot / magSq);
////
////}
//////glm/gtx/perpendicular
////glm::vec2 ExtraMath::Perpendicular(const glm::vec2& len, const glm::vec2& dir)
////{
////	return len - Project(len, dir);
////}
////
////glm::vec3 ExtraMath::Perpendicular(const glm::vec3& len, const glm::vec3& dir)
////{
////	return len - Project(len, dir);
////}
////glm::vec2 Reflection(const glm::vec2& vec, const glm::vec2& normal) {
////	float d = glm::dot(vec, normal);
////	return vec - normal * (d * 2.0f);
////}
////glm::vec3 Reflection(const glm::vec3& vec, const glm::vec3& normal){
////	float d = glm::dot(vec, normal);
////	return vec - normal * (d * 2.0f);
////	}