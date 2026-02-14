#pragma once

#include <memory>

#include "camera.h"
#include "timestep.h"
#include "window.h"
#include "batch_render.h"
#include "events.h"
#include "cells.h"

#define MIN_ZOOM 1.0f
#define MAX_ZOOM 0.2f


class CameraControl
{
private:
    Window* m_Window;

    glm::vec3 m_CameraPosition = { WORLD_X / 2, WORLD_Y / 2, 0.0f };
    float m_CameraSpeed = 1000.0f;

    float m_ResX;
    float m_ResY;
    float m_AspectRatio;

    float m_ZoomLevel = MIN_ZOOM;
    float m_ZoomSpeed = 0.1f;

    Camera m_Camera;

public:
    CameraControl(float m_AspectRatio);
    ~CameraControl();

    float GetAspectRatio();
    void Init(Window* window);
    
    void WindowResize();

    void CamEvents(std::unique_ptr<Events>& events, Timestep ts);

    Camera GetCamera() { return m_Camera; }
    glm::vec2 GetResolution() { return {m_ResX, m_ResY}; }
    glm::vec3 GetCameraPosition() { return m_CameraPosition; }
    float GetZoomLevel() { return m_ZoomLevel; }

private:
    void CheckCameraBounds();
    void MoveCamera(bool isHorz, int direction, Timestep ts);
    void ZoomCamera(int zoomLevel);
};