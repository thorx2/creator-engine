#include "pch.h"

#include "include/LayerManager.h"
#include "include/Layer.h"
#include "include/Event.h"
#include "include/time/CreatorTime.h"
#include <GLFW/glfw3.h>

namespace Creator
{
    LayerManager::LayerManager() : m_LastFrameTime(0)
    {
        m_CurrentLayerIndex = 0;
    }

    LayerManager::~LayerManager()
    {
        for (Layer *layer : m_Layers)
        {
            delete layer;
        }
    }

    void LayerManager::Update()
    {
        float time = glfwGetTime(); // CreatorTime::GetTime();
        CreatorTimer timestep = time - m_LastFrameTime;
        m_LastFrameTime = time;
        for (Layer *layer : m_Layers)
        {
            layer->Update(timestep);
        }
    }

    void LayerManager::OnEvent(Event &event)
    {
        for (auto it = m_Layers.rbegin(); it != m_Layers.rend(); ++it)
        {
            (*it)->OnEvent(event);
            if (event.Handled)
            {
                break;
            }
        }
    }

    void LayerManager::PushToTop(Layer *layer)
    {
        m_Layers.emplace_back(layer);
    }

    void LayerManager::PushLayer(Layer *layer)
    {
        m_Layers.emplace(m_Layers.begin() + m_CurrentLayerIndex, layer);
        ++m_CurrentLayerIndex;
    }

    void LayerManager::PopLayer(Layer *layer)
    {
        auto it = std::find(m_Layers.begin(), m_Layers.begin() + m_CurrentLayerIndex, layer);
        if (it != m_Layers.begin() + m_CurrentLayerIndex)
        {
            layer->Detach();
            m_Layers.erase(it);
            m_CurrentLayerIndex--;
        }
    }

    void LayerManager::PopOverlay(Layer *overlay)
    {
        auto it = std::find(m_Layers.begin() + m_CurrentLayerIndex, m_Layers.end(), overlay);
        if (it != m_Layers.end())
        {
            overlay->Detach();
            m_Layers.erase(it);
        }
    }

}