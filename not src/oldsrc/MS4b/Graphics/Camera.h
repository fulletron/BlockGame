#ifndef __CAMERA_H_
#define __CAMERA_H_

#include "..\..\Game\definitions.h"
#include "openglincludes.h"

namespace GS
{
	class Game;

	namespace WindowNS{class Window;};

	namespace CameraNS {

		class Camera 
		{
		private:
			GS::Game *					m_rpGame;

			// CAMERA DATA
			glm::vec3					m_eyePos;
			glm::vec3					m_lookAt;
			glm::vec3					m_upVec;

			// CAMERA MATRICES
			glm::mat4x4					m_viewMat;
			glm::mat4x4					m_projMat;
			glm::mat4x4					m_viewProjMat;

			/// KYLE :: HOW AM I GOING TO DO A PLANE IN OPENGL? glm::vec3 point, glm::vec3 normal?
			//D3DXPLANE					m_frustumPlanes[6];

			//void __buildWorldFrustumPlanes();

		public:
			Camera(){}
			~Camera(){}

			//D3DXPLANE * getFrustumPlanes();

			glm::vec3 * getEyePos();
			glm::vec3 * getLookAt();
			glm::vec3 * getUpVec();

			_UINT32 init(GS::WindowNS::Window * const a_pWindow);
			void setEyePos(const glm::vec3 & a_eyePos);
			void setLookAt(const glm::vec3 & a_lookAt);
			void setUpVec(const glm::vec3 & a_upVec);

			void shutdown();

		};

		//bool isVisible(const Camera & a_camera, const AABB & box);
		void setCamera(Camera * const a_camera, const glm::vec3 & a_pos, const glm::vec3 & a_lookAt); 

	};

};

#endif