
#include "logicsystem.h"
#include "gamestate.h"
#include "gameentitymanager.h"

#include "SdlInputHandler.h"

#include "OgreRoot.h"
#include "OgreException.h"
#include "OgreConfigFile.h"

#include "OgreRenderWindow.h"
#include "OgreCamera.h"

#include "Hlms/Unlit/OgreHlmsUnlit.h"
#include "Hlms/Pbs/OgreHlmsPbs.h"
#include "OgreHlmsManager.h"
#include "OgreArchiveManager.h"

#include "Compositor/OgreCompositorManager2.h"

#include "Overlay/OgreOverlaySystem.h"

#if OGRE_USE_SDL2
#include <SDL_syswm.h>
#endif

namespace OGraphics
{
	Ogre::uint32 LogicSystem::mCurrentTransformIdx = 1;

	LogicSystem::LogicSystem(IGameState *gameState) :
		BaseSystem(gameState),
		mpGraphicsSystem(0),
		mpGameEntityManager(0),
		mpLogicGameState(0)
	{
		mCurrentTransformIdx = 1;
		//mCurrentTransformIdx is 1, 0 and NUM_GAME_ENTITY_BUFFERS - 1 are taken by GraphicsSytem at startup
		//The range to fill is then [2; NUM_GAME_ENTITY_BUFFERS-1]
		for (Ogre::uint32 i = 2; i<NUM_GAME_ENTITY_BUFFERS - 1; ++i)
			mAvailableTransformIdx.push_back(i);
	}
	//-----------------------------------------------------------------------------------
	LogicSystem::~LogicSystem()
	{
	}
	//-----------------------------------------------------------------------------------
	void LogicSystem::finishFrameParallel(void)
	{
		if (mpGameEntityManager)
			mpGameEntityManager->finishFrameParallel();

		//Notify the GraphicsSystem we're done rendering this frame.
		if (mpGraphicsSystem)
		{
			size_t idxToSend = mCurrentTransformIdx;

			if (mAvailableTransformIdx.empty())
			{
				//Don't relinquish our only ID left.
				//If you end up here too often, Graphics' thread is too slow,
				//or you need to increase NUM_GAME_ENTITY_BUFFERS
				idxToSend = std::numeric_limits<Ogre::uint32>::max();
			}
			else
			{
				//Until Graphics constantly releases the indices we send them, to avoid writing
				//to transform data that may be in use by the other thread (race condition)
				mCurrentTransformIdx = mAvailableTransformIdx.front();
				mAvailableTransformIdx.pop_front();
			}

			this->queueSendMessage(mpGraphicsSystem, Mq::LOGICFRAME_FINISHED, idxToSend);
		}

		BaseSystem::finishFrameParallel();
	}
	//-----------------------------------------------------------------------------------
	void LogicSystem::processIncomingMessage(Mq::MessageId messageId, const void *data)
	{
		switch (messageId)
		{
		case Mq::LOGICFRAME_FINISHED:
		{
			Ogre::uint32 newIdx = *reinterpret_cast<const Ogre::uint32*>(data);
			assert((mAvailableTransformIdx.empty() ||
				newIdx == (mAvailableTransformIdx.back() + 1) % NUM_GAME_ENTITY_BUFFERS) &&
				"Indices are arriving out of order!!!");

			mAvailableTransformIdx.push_back(newIdx);
		}
		break;
		case Mq::GAME_ENTITY_SCHEDULED_FOR_REMOVAL_SLOT:
			mpGameEntityManager->_notifyGameEntitiesRemoved(*reinterpret_cast<const Ogre::uint32*>(
				data));
			break;
		case Mq::SDL_EVENT:
			handleInput(*reinterpret_cast<const SDL_Event*>(data));
			break;
		default:
			break;
		}
	}

	//-----------------------------------------------------------------------------------
	void LogicSystem::handleInput(const SDL_Event& evt)
	{
		// if we don't have a logic game state, there isn't a place to interpret
		// the input that has been piped
		if (!mpLogicGameState)
			return;

		// we trust the graphics thread to have passed us valid input operations
		switch (evt.type)
		{
		case SDL_MOUSEMOTION:
		case SDL_MOUSEWHEEL:
			mpLogicGameState->mouseMoved(evt);
			break;
		case SDL_MOUSEBUTTONDOWN:
			mpLogicGameState->mousePressed(evt.button, evt.button.button);
			break;
		case SDL_MOUSEBUTTONUP:
			mpLogicGameState->mouseReleased(evt.button, evt.button.button);
			break;
		case SDL_KEYDOWN:
			mpLogicGameState->keyPressed(evt.key);
			break;
		case SDL_KEYUP:
			mpLogicGameState->keyReleased(evt.key);
			break;
#ifdef _NOT_ENABLED_INPUT_ 1
		case SDL_TEXTINPUT:
		{
			if (mKeyboardListener)
				mKeyboardListener->textInput(evt.text);

			if (mLogicSystem)
				mGraphicsSystem->queueSendMessage(mLogicSystem, Mq::SDL_EVENT, evt);
		}
		break;
		case SDL_JOYAXISMOTION:
		{
			if (mJoystickListener)
				mJoystickListener->joyAxisMoved(evt.jaxis, evt.jaxis.axis);

			if (mLogicSystem)
				mGraphicsSystem->queueSendMessage(mLogicSystem, Mq::SDL_EVENT, evt);
		}
		break;
		case SDL_JOYBUTTONDOWN:
		{
			if (mJoystickListener)
				mJoystickListener->joyButtonPressed(evt.jbutton, evt.jbutton.button);

			if (mLogicSystem)
				mGraphicsSystem->queueSendMessage(mLogicSystem, Mq::SDL_EVENT, evt);
		}
		break;
		case SDL_JOYBUTTONUP:
		{
			if (mJoystickListener)
				mJoystickListener->joyButtonReleased(evt.jbutton, evt.jbutton.button);

			if (mLogicSystem)
				mGraphicsSystem->queueSendMessage(mLogicSystem, Mq::SDL_EVENT, evt);
		}
		break;
		case SDL_JOYDEVICEADDED:
			//SDL_JoystickOpen(evt.jdevice.which);
			//std::cout << "Detected a new joystick: " << SDL_JoystickNameForIndex(evt.jdevice.which) << std::endl;
			break;
		case SDL_JOYDEVICEREMOVED:
			//std::cout << "A joystick has been removed" << std::endl;
			break;
		case SDL_WINDOWEVENT:
			handleWindowEvent(evt);
			break;
#endif
		default:
			break;
		}
	}
}
