#include "Camera.h"
#include "window.h"
#include "..\..\Game\game.h"

#include "..\..\External\include\glm/gtc/matrix_transform.hpp"
#include "..\..\External\include\glm/gtc/type_ptr.hpp"

namespace GS
{
	namespace CameraNS
	{
		_UINT32 Camera::init(WindowNS::Window * const a_pWindow)
		{
			m_rpGame = a_pWindow->get__m_rpGame();

			//////////////////////////////////////////////////////////////////////////	
			// View and Projection Matrices
			//////////////////////////////////////////////////////////////////////////

			// Initialize View Matrix
			m_lookAt	= glm::vec3(0.0f, 0.0f, 0.0f); // Position camera is viewing
			m_eyePos	= glm::vec3(0.0f, m_lookAt.y -EYE_FORWARD, m_eyePos.z + EYE_HEIGHT);	// Camera position
			m_upVec		= glm::vec3(0.0f, 0.0f, 1.0f);	// Rotational orientation 

			//m_eyePos	= D3DXVECTOR3(0.0f, 3.5f, -10.0f);	// Camera position

			
			m_viewMat = glm::lookAt(
					m_eyePos,
					m_lookAt,
					m_upVec
				);

			_RECT<_INT32> t_windowRect = a_pWindow->get__m_windowScreen()->m_pxRect;

			m_projMat = glm::perspective(
					82.0f,
					(GLfloat)t_windowRect.width / t_windowRect.height, 
					1.0f, 
					70.0f
				);
			/*
			// Easily calculate the view matrix with 3 intuitive vectors
			D3DXMatrixLookAtLH(
				&m_viewMat,	// Returned viewMat
				&m_eyePos,	// Eye Position
				&m_lookAt,	// LookAt Position
				&m_upVec);	// Up Vector

			// Initialize perspective projection matrix, this creates view frustum
			D3DXMatrixPerspectiveFovLH(
				&m_projMat,						// Returned ProjMat
				D3DXToRadian(82.0f),			// Field of View 65 def
				(float)width / (float)height,	// Aspect Ratio
				1.0f,							// Near Plane
				70.0f);						// Far Plane // STANDARDLY IS 70.0f
			*/
			m_viewProjMat = m_viewMat * m_projMat;
			//__buildWorldFrustumPlanes();
			return 0;
		}

		void Camera::shutdown()
		{
		}

		glm::vec3 * Camera::getLookAt()
		{
			return &m_lookAt;
		}

		glm::vec3 * Camera::getEyePos()
		{
			return &m_eyePos;
		}

		glm::vec3 * Camera::getUpVec()
		{
			return &m_upVec;
		}

		void Camera::setEyePos(const glm::vec3 & a_pos)
		{
			m_eyePos.x = a_pos.x;
			m_eyePos.y = a_pos.y;
			m_eyePos.z = a_pos.z;
		}

		void Camera::setLookAt(const glm::vec3 & a_lookAt)
		{
			m_lookAt.x = a_lookAt.x;
			m_lookAt.y = a_lookAt.y;
			m_lookAt.z = a_lookAt.z;
		}

		void Camera::setUpVec(const glm::vec3 & a_upVec)
		{
			m_upVec.x = a_upVec.x;
			m_upVec.y = a_upVec.y;
			m_upVec.z = a_upVec.z;
		}

		/*
		void Camera::__buildWorldFrustumPlanes()
		{
			// Note: Extract the frustum planes in world NS.

			D3DXMATRIX VP = m_viewProjMat;

			D3DXVECTOR4 col0(VP(0,0), VP(1,0), VP(2,0), VP(3,0));
			D3DXVECTOR4 col1(VP(0,1), VP(1,1), VP(2,1), VP(3,1));
			D3DXVECTOR4 col2(VP(0,2), VP(1,2), VP(2,2), VP(3,2));
			D3DXVECTOR4 col3(VP(0,3), VP(1,3), VP(2,3), VP(3,3));

			// Planes face inward.
			m_frustumPlanes[0] = (D3DXPLANE)(col2);        // near
			m_frustumPlanes[1] = (D3DXPLANE)(col3 - col2); // far
			m_frustumPlanes[2] = (D3DXPLANE)(col3 + col0); // left
			m_frustumPlanes[3] = (D3DXPLANE)(col3 - col0); // right
			m_frustumPlanes[4] = (D3DXPLANE)(col3 - col1); // top
			m_frustumPlanes[5] = (D3DXPLANE)(col3 + col1); // bottom

			for(int i = 0; i < 6; i++)
				D3DXPlaneNormalize(&m_frustumPlanes[i], &m_frustumPlanes[i]);
		}
		*/
		/*
		D3DXPLANE * Camera::getFrustumPlanes()
		{
			return &m_frustumPlanes[0];
		}
		*/
		/*
		bool GraphicsNS::isVisible(const Camera & a_camera, const AABB & a_box)
		{
			D3DXPLANE * t_pFrustumPlanes = a_camera.getFrustumPlanes();

			// Test assumes frustum planes face inward.

			D3DXVECTOR3 P;
			D3DXVECTOR3 Q;

			//      N  *Q                    *P
			//      | /                     /
			//      |/                     /
			// -----/----- Plane     -----/----- Plane    
			//     /                     / |
			//    /                     /  |
			//   *P                    *Q  N
			//
			// PQ forms diagonal most closely aligned with plane normal.

			// For each frustum plane, find the box diagonal (there are four main
			// diagonals that intersect the box center point) that points in the
			// same direction as the normal along each axis (i.e., the diagonal 
			// that is most aligned with the plane normal).  Then test if the box
			// is in front of the plane or not.
			for(int i = 0; i < 6; ++i)
			{
				// For each coordinate axis x, y, z...
				for(int j = 0; j < 3; ++j)
				{
					// Make PQ point in the same direction as the plane normal on this axis.
					if( t_pFrustumPlanes[i][j] >= 0.0f )
					{
						P[j] = a_box.minPt[j];
						Q[j] = a_box.maxPt[j];
					}
					else 
					{
						P[j] = a_box.maxPt[j];
						Q[j] = a_box.minPt[j];
					}
				}

				// If box is in negative half NS, it is behind the plane, and thus, completely
				// outside the frustum.  Note that because PQ points roughly in the direction of the 
				// plane normal, we can deduce that if Q is outside then P is also outside--thus we
				// only need to test Q.
				if( D3DXPlaneDotCoord(&t_pFrustumPlanes[i], &Q) < 0.0f  ) // outside
					return false;
			}
			return true;
		}
		*/

		void setCamera(Camera * const a_camera, const glm::vec3 & a_pos, const glm::vec3 & a_lookAt)
		{
		}
	};

};