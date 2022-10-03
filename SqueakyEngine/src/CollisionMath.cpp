//#include "CollisionMath.h"
//
//#include <glm/trigonometric.hpp>
//
//using namespace glm;
//
//bool CollisionMath::SphereSphereCollisionDetected(PhysicsBody& phyObj1, PhysicsBody& phyObj2)
//{
//
//	float distance = length(phyObj1.GetPos() - phyObj2.GetPos());
//	float radiusSum = phyObj1.GetRadius() + phyObj2.GetRadius();
//	if (distance < radiusSum) {
//		phyObj1.CollisionID(phyObj2);
//		phyObj2.CollisionID(phyObj1);
//		return true;
//	}
//
//	return false;
//}
//
//bool CollisionMath::SpherePlaneCollisionDetected(const PhysicsBody& phyObj1, const Plane& plane)
//{
//
//	return (plane.distance(phyObj1.GetPosition(), phyObj1.GetRadius()) <= 0.001) ? true : false;
//
//
//}
//
//float CollisionMath::SphereAABCollisionDetected(const PhysicsBody& phyObj1, const PhysicsBody& phyObj2)
//{
//	float sqrD = 0;// sqrtf(distance(phyObj1.GetSphere(), phyObj2.GetAAB()));
//	auto check = [&](
//		const float pn,
//		const float bmin,
//		const float bmax) -> double
//	{
//		float out = 0;
//		float v = pn;
//
//		if (v < bmin)
//		{
//			float val = (bmin - v);
//			out += val * val;
//		}
//
//		if (v > bmax)
//		{
//			float val = (v - bmax);
//			out += val * val;
//		}
//
//		return out;
//	};
//
//	sqrD += check(phyObj1.GetPosition().x, -phyObj2.GetAAB().planes[0].w, -phyObj2.GetAAB().planes[3].w);
//	sqrD += check(phyObj1.GetPosition().y, -phyObj2.GetAAB().planes[1].w, -phyObj2.GetAAB().planes[4].w);
//	sqrD += check(phyObj1.GetPosition().z, -phyObj2.GetAAB().planes[2].w, -phyObj2.GetAAB().planes[5].w);
//	//std::cout << (sqrD <= (phyObj1.GetRadius() * phyObj1.GetRadius())) << std::endl;
//	return sqrD;
//	//Collider::RayAABCollisionPoint()
//}
//
//void CollisionMath::SphereSphereCollisionResponse(PhysicsBody& phyObj1, PhysicsBody& phyObj2, float& e)
//{
//
//
//	e > 1 ? e = 1 : e < 0 ? e = 0 : e;
//	if (SphereSphereCollisionDetected(phyObj1, phyObj2)) {
//
//		Vec3 N = normalize(phyObj1.GetPosition() - phyObj2.GetPosition());
//		float p1 = (dot(-phyObj1.GetVelocity(), N));
//		float p2 = (dot(-phyObj2.GetVelocity(), N));
//
//
//
//		float vf1 = ((((phyObj1.GetMass() * p1) + (phyObj2.GetMass() * p2))
//			+ ((phyObj2.GetMass() * e * p2) - (phyObj2.GetMass() * e * p1)))) / (phyObj1.GetMass() + phyObj2.GetMass());
//
//
//		float vf2 = ((((phyObj1.GetMass() * p1) + (phyObj2.GetMass() * p2))
//			+ ((phyObj1.GetMass() * e * p1) - (phyObj1.GetMass() * e * p2)))) / (phyObj1.GetMass() + phyObj2.GetMass());
//
//
//
//		phyObj1.SetVelocity((vf2 - p2) * N);
//		phyObj2.SetVelocity((vf1 - p1) * N);
//	}
//	//return auto	[Vec3((vf2 - p2) * N),Vec3((vf1 - p1) * N)] = f
//
//}
//
//void CollisionMath::SphereStaticSphereCollisionResponse(PhysicsBody& phyObj1, PhysicsBody& phyObj2)
//{
//	if (SphereSphereCollisionDetected(phyObj1, phyObj2)) {
//		Vec3 N = normalize(phyObj1.GetPosition() - phyObj2.GetPosition());
//		Vec3 P = (dot(-phyObj1.GetVelocity(), N) * N);
//		Vec3 V = phyObj1.GetVelocity() + 2.0f * P;
//		phyObj1.SetVelocity(V);
//	}
//}
//
//void CollisionMath::SpherePlaneCollisionResponse(PhysicsBody& phyObj1, const Plane& plane)
//{
//
//	if (SpherePlaneCollisionDetected(phyObj1, plane)) {
//		std::cout << "collide:" << "\n";
//
//		Vec3 N = normalize(plane.xyz());
//		float p1 = (dot(-phyObj1.GetVelocity(), N));
//
//
//		Vec3 fv((phyObj1.GetVelocity() + 2 * (p1)*N));
//		fv.print();
//		phyObj1.SetVelocity(fv);
//	}
//}
//
//
//
//
//void CollisionMath::SphereAABCollisionResponse(PhysicsBody& phyObj1, const PhysicsBody& phyObj2)
//{
//	float sqrd = SphereAABCollisionDetected(phyObj1, phyObj2);
//
//	if (sqrd <= (phyObj1.GetRadius() * phyObj1.GetRadius())) {
//		std::cout << phyObj1.GetName() << "\n";
//		Plane pn;
//
//		Vec3 cntr = phyObj1.GetPosition();
//		float rs = phyObj1.GetRadius();//sphere radius 
//		Vec3 min(phyObj2.GetAAB().planes[0].w, phyObj2.GetAAB().planes[1].w, phyObj2.GetAAB().planes[2].w), max(phyObj2.GetAAB().planes[3].w, phyObj2.GetAAB().planes[4].w, phyObj2.GetAAB().planes[5].w);//aabb min and max
//
//		Vec3 nn(Vec3(fmaxf(min.x, fmin(phyObj1.GetPosition().x, max.x)),
//			fmaxf(min.y, fmin(phyObj1.GetPosition().y, max.y)),
//			fmaxf(min.z, fmin(phyObj1.GetPosition().z, max.z))));
//		Vec3 q;
//		for (size_t i = 0; i < 3; i++)
//		{
//			float v = phyObj1.GetPosition()[i];
//			if (v < min[i]) v = round(min[i]);
//			if (v > max[i]) v = round(max[i]);
//			q[i] = v;
//		}
//
//		float pen = distance(nn, cntr);
//		Vec3 npn = phyObj1.GetPosition() - q;
//		npn.print();
//		Vec3 n = normalize(npn);
//		n.print();
//		/*if ((cntr.x < min.x && cntr.y < min.y)|| (cntr.x > max.x && cntr.y < min.y)) {
//			pn = Plane(normalize(nn-phyObj1.GetPosition()),mag(nn));
//			std::cout << phyObj1.GetName() << "\n";
//			printf("x-y min edge\n");
//		}
//		else if ((cntr.x < min.x && cntr.y > max.y) || (cntr.x > max.x && cntr.y > max.y)) {
//			pn = Plane(normalize(nn - phyObj1.GetPosition()), mag(nn));
//			std::cout << phyObj1.GetName() << "\n";
//			printf("x+y max edge\n");
//		}
//
//		else if ((cntr.z < min.z && cntr.y < min.y) || (cntr.z > max.z && cntr.y < min.y)) {
//			pn = Plane(normalize(nn - phyObj1.GetPosition()), mag(nn));
//			printf("z-y min edge\n");
//		}
//		else if ((cntr.z < min.z && cntr.y > max.y) || (cntr.z > max.z && cntr.y > max.y)) {
//			pn = Plane(normalize(nn - phyObj1.GetPosition()), mag(nn));
//			printf("z+y max edge\n");
//		}
//
//		else if ((cntr.x < min.x && cntr.z < min.z) || (cntr.x > max.x && cntr.z < min.z)) {
//			pn = Plane(normalize(nn - phyObj1.GetPosition()), mag(nn));
//			printf("y-x min edge\n");
//		}
//
//		else if ((cntr.x < min.x && cntr.z > max.z) || (cntr.x > max.x && cntr.z > max.z)) {
//			pn = Plane(normalize(nn - phyObj1.GetPosition()), mag(nn));
//			printf("y+x max edge\n");
//		}
//
//		else {
//			if (fabs(nn.x) >= fabs(nn.y) && fabs(nn.x) >= fabs(nn.z)) {
//				if (nn.x < phyObj1.GetPosition().x) {
//					pn = phyObj2.GetAAB().planes[0];
//					printf("plane-x");
//				}
//				else {
//					pn = phyObj2.GetAAB().planes[3];
//					printf("plane+x");
//				}
//			}
//			else if (fabs(nn.y) >= fabs(nn.z) && fabs(nn.y) >= fabs(nn.z)) {
//				if (nn.y < phyObj1.GetPosition().y) {
//					pn = phyObj2.GetAAB().planes[1];
//					printf("plane-y");
//				}
//				else {
//					pn = phyObj2.GetAAB().planes[4];
//					printf("plane+y");
//				}
//			}
//			else if (fabs(nn.z) >= fabs(nn.x) && fabs(nn.z) >= fabs(nn.y)) {
//				if (nn.z < phyObj1.GetPosition().z) {
//					pn = phyObj2.GetAAB().planes[2];
//					printf("plane-z");
//				}
//				else {
//					pn = phyObj2.GetAAB().planes[5];
//					printf("plane+z");
//				}
//			}
//		}*/
//
//
//
//		Vec3 N = n;
//
//
//		Vec3 P = (dot(-phyObj1.GetVelocity(), N) * N);
//		Vec3 V1 = phyObj1.GetVelocity() + 2.0f * P;
//
//
//		phyObj1.SetVelocity(V1 * 0.9f);
//
//	}
//}
//
//void CollisionMath::ApplyForces(PhysicsBody& phyObj1, float& waterHeight)
//{
//	const float g = 9.81f;
//	const float dragC = 0.4f;
//	const float waterDens = 0.50f; //rho
//	float theta = 2 * acosf(phyObj1.GetMass() / phyObj1.GetRadius());
//	float v = 0.0f;
//	static float pv = 0.0f;
//
//
//	if (phyObj1.GetPosition().y + phyObj1.GetRadius() <= waterHeight) {
//		v = M_PI * powf(phyObj1.GetRadius(), 2.0f) * phyObj1.GetLength();
//		//fully submerged
//		if (pv != 0.0f) {
//			pv = 0.0f;
//			printf("fully submerged\n");
//		}
//	}
//	else if ((phyObj1.GetPosition().y - phyObj1.GetRadius()) <= waterHeight && phyObj1.GetPosition().y >= waterHeight) {
//		v = (1.0f / 2.0f) * powf(phyObj1.GetRadius(), 2.0f) * (theta - sinf(theta) * phyObj1.GetLength());
//		//submerged bellow centre 
//		if (pv != 1.0f) {
//			pv = 1.0f;
//			printf("submerged bellow centre\n");
//		}
//	}
//	else if (phyObj1.GetPosition().y <= waterHeight && phyObj1.GetPosition().y + phyObj1.GetRadius() >= waterHeight) {
//		v = M_PI * powf(phyObj1.GetRadius(), 2) * phyObj1.GetLength() - (1.0f / 2.0f) * powf(phyObj1.GetRadius(), 2) * (theta - sinf(theta) * phyObj1.GetLength());
//		//submerged above centre 
//		if (pv != 2.0f) {
//			pv = 2.0f;
//			printf("submerged above centre\n");
//		}
//	}
//	else if ((phyObj1.GetPosition().y - phyObj1.GetRadius()) >= waterHeight) {
//		v = 0;
//		if (pv != 3.0f) {
//			pv = 3.0f;
//			//not submerged 
//			printf("not submerged\n");
//		}
//	}
//	//std::cout << v << "\n";
//
//	//std::cout << body.GetPosition().y << "\n";
//	//std::cout << waterHeight << "\n";
//	for (int x = 0; x <= abs(phyObj1.GetPosition().y) - waterHeight; ++x) {
//		std::cout << "|";
//	}
//	for (int x = 0; x >= abs(phyObj1.GetPosition().y) - waterHeight; --x) {
//		std::cout << "|";
//	}
//	std::cout << "\n";
//	Vec3 fGrav(0.0f, phyObj1.GetMass() * -g, 0.0f);
//	Vec3 fDrag(dragC * -phyObj1.GetVelocity());
//	Vec3 fBouy(0.0f, waterDens * g * v, 0.0f);
//
//	Vec3 fNet = fGrav + fDrag + fBouy;
//
//	phyObj1.ApplyForce(fNet);
//
//	//float rho = body.GetMass() / v1;
//	//float weight = body.GetMass() * g;
//	//Vec3 drag = -c * body.GetVelocity();
//	//float fb = rho * g * v1;
//
//
//
//
//
//
//}