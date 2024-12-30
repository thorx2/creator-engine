#include "pch.h"

#include "include/LayerManager.h"
#include "include/Layer.h"

namespace Creator
{
    LayerManager::LayerManager()
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