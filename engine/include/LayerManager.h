#pragma once

#include <vector>

namespace Creator
{
    // Forward declare the Layer class
    class Layer;
    class Event;

    class LayerManager
    {
    public:
        void PushLayer(Layer *layer);
        void PushToTop(Layer *layer);
        void PopLayer(Layer *layer);
        void PopOverlay(Layer *overlay);

        LayerManager();
        ~LayerManager();

        void Update();

        void OnEvent(Event& event);

    private:
        std::vector<Layer *> m_Layers;
        // Can it be 16? do we need
        uint32_t m_CurrentLayerIndex;
        float m_LastFrameTime;
    };
}