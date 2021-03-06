#include "graphics/DisplayManager.hpp"

namespace dt {

DisplayManager::DisplayManager() {}

DisplayManager::~DisplayManager() {}

void DisplayManager::Initialize() {}

void DisplayManager::Deinitialize() {}

bool DisplayManager::RegisterCamera(CameraComponent* camera_component) {
    std::string name = camera_component->GetName();

    // Do not add if a CameraComponent of the same name already exists.
    if(mCameras.count(name) != 0)
        return false;

    // Create the render window if this is the first CameraComponent.
    if(mCameras.size() == 0 && ! mOgreRoot->isInitialised())
        _CreateWindow();

    mCameras[name] = camera_component;

    return true;
}

bool DisplayManager::UnregisterCamera(CameraComponent* camera_component) {
    std::string name = camera_component->GetName();

    // Do not remove if the requested CameraComponent hasn't been registered.
    if(mCameras.count(name) != 0)
        return false;

    mCameras.erase(name);

    // Destroy the render window if this is the last CameraComponent.
    if(mCameras.size() == 0 && mOgreRoot->isInitialised())
        _DestroyWindow();

    return true;
}

bool DisplayManager::ActivateCamera(const std::string& name) {
    // TODO: Set active camera
    return false;
}

void DisplayManager::Render() {
    mOgreRoot->renderOneFrame();
    Ogre::WindowEventUtilities::messagePump();
}

void DisplayManager::_CreateWindow() {
    mOgreRoot = std::shared_ptr<Ogre::Root>(new Ogre::Root());

    mOgreRoot->loadPlugin("/usr/lib/OGRE/RenderSystem_GL.so");
    mOgreRenderSystem = mOgreRoot->getRenderSystemByName("OpenGL Rendering Subsystem");
    mOgreRoot->setRenderSystem(mOgreRenderSystem);

    mOgreRoot->initialise(false, "Ducttape Game Engine");
    mOgreRenderWindow = mOgreRoot->createRenderWindow("RenderWindow", 1024, 768, false);
}

void DisplayManager::_DestroyWindow() {
    mOgreRenderWindow->destroy();
    mOgreRenderSystem->shutdown();
    mOgreRoot->shutdown();
}

void DisplayManager::_CreateViewport() {}

}
