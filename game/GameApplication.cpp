#include "pch.h"
#include "include/Application.h"

#include "CoreEntry.h"

class GameApplication : public Creator::Application
{
public:
    GameApplication()
    {
    }

    ~GameApplication()
    {
        // CE_LOG_GAME_INFO("Game killed");
    }
};

Creator::Application *Creator::CreateApplication()
{
    return new GameApplication();
}