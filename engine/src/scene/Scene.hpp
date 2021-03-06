#ifndef DUCTTAPE_ENGINE_SCENE_SCENE
#define DUCTTAPE_ENGINE_SCENE_SCENE

#include <string>

#include <boost/ptr_container/ptr_map.hpp>

#include "Node.hpp"

namespace dt {

/**
  * A class to represent a whole scene of the game world.
  */
class Scene : public Node {
public:
    /**
      * Default constructor.
      */
    Scene();

protected:
    bool _IsScene();

private:
    Node mRootNode; //!< The root Node of the Scene.
};

}

#endif
