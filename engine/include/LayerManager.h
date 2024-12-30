#pragma once

#include <vector>

namespace Creator
{
    // Forward declare the Layer class
    class Layer;

    class LayerManager
    {
    public:
        void PushLayer(Layer *layer);
        void PushToTop(Layer *layer);
        void PopLayer(Layer *layer);
        void PopOverlay(Layer *overlay);

        LayerManager();
        ~LayerManager();

    private:
        std::vector<Layer *> m_Layers;
        // Can it be 16? do we need
        uint32_t m_CurrentLayerIndex;
    };
}