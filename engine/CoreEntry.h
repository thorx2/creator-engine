#pragma once

#include "include/Application.h"
#include "include/Log.h"

extern Creator::Application *Creator::CreateApplication();

int main(int argc, char **argv)
{
    Creator::Log::Init();
    CREATOR_INFO_LOG("Logging system init complete");
    auto app = Creator::CreateApplication();
    CREATOR_INFO_LOG("Core application created");
    app->Run();
    delete app;
    CREATOR_INFO_LOG("Core application deleted");
    return 0;
}