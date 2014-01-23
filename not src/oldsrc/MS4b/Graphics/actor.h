#ifndef __ACTOR_H_
#define __ACTOR_H_

#include <Library\library.h>
#include <Game\definitions.h>

namespace GS {
namespace InputNS{ class Input; };
namespace GraphicsNS {

	class IActor;

	class ActorManager
	{
		private:
			GS::Game * m_rpGame;

			_GSVECTOR(IActor*) m_actors;

			static bool __sortAlgorithm(void *, void *);

		public:
			_UINT32 init(GS::Game * const a_rpGame);
			void manageDraw();
			bool manageInput(GS::InputNS::Input * const);
			void manageUpdate(const _DOUBLE & a_dt);
			void manageShutdown();

			void manageOnScreenResize();

			void sortActors();

			void addActor(IActor * const);
			void removeActor(IActor * const);
	};

	class IActor : public GS::LibraryNS::IEntry
	{
	public:
		virtual ActorManager* getListedActors() = 0;
		virtual void setMeInFocus() = 0;
		virtual void resetMyFocus() = 0;
		virtual void setMyBaseFocus(const _USHORT &) = 0;
		virtual void resetListFoci() = 0;

		virtual _FLOAT getOpacity() const = 0;
		virtual _BOOL isVisible() const = 0;
		virtual _USHORT getFocus() const = 0;

		//// NOT DEFINED IN ACTORBASE! (Different Per Actor)
		virtual void draw() = 0;
		virtual bool input(GS::InputNS::Input * const) = 0;
		virtual void update(const _DOUBLE &) = 0;
		virtual void onScreenResize() = 0;
	};

	class ActorBase : public IActor
	{
	protected:
		ActorManager			m_actorManager;

		_USHORT					m_baseFocus;
		_USHORT					m_curFocus;
		_BOOL					m_isVisible;
		_FLOAT					m_opacity;
	public:
		ActorManager* getListedActors(){return &m_actorManager;};
		void setMeInFocus(){ m_curFocus = FOCUSVALUE; }
		void resetMyFocus(){ m_curFocus = m_baseFocus; }
		void setMyBaseFocus(const _USHORT & a_focus){ m_baseFocus = a_focus; resetMyFocus(); }
		void resetListFoci(){getListedActors()->sortActors();}

		_USHORT getFocus() const {return m_curFocus;}
		_FLOAT getOpacity() const {return m_opacity;}
		_BOOL isVisible() const {return m_isVisible;}

		virtual void draw() = 0;
		virtual bool input(GS::InputNS::Input * const) = 0;
		virtual void update(const _DOUBLE &) = 0;
		virtual void onScreenResize() = 0;
	};
};
};

#endif