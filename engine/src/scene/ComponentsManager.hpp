#ifndef DUCTTAPE_ENGINE_SCENE_COMPONENTSMANAGER
#define DUCTTAPE_ENGINE_SCENE_COMPONENTSMANAGER

#include <map>

#include "component/Component.hpp"

namespace dt {

/**
  * Manager to hold all components of a single scene. Thus one component can be assigned to several
  * Nodes, which should result in better performance when cloning Nodes.
  * @see Node
  * @see Scene
  */
class ComponentsManager {
public:
    /**
      * Default constructor.
      */
    ComponentsManager();


    /**
      * Default destructor.
      */
    ~ComponentsManager();


    /**
      * Initializatior.
      */
    void Initialize();


    /**
      * Deinitializator. Destroys all Components.
      */
    void Deinitialize();


    /**
      * Adds a component to the pool.
      * @param component The Component to add.
      */
    void AddComponent(const std::string& node_name, Component<ComponentListener>* component);


    /**
      * Returns a component in the pool with the name given.
      * @param name The name of the Component to search for.
      * @returns A pointer to the component or nullptr if it is not found.
      */
    Component<ComponentListener>* FindComponent(const std::string& name);

    const std::string& GetNodeOfComponent(const std::string& name);

    std::vector<std::shared_ptr<Component<ComponentListener>>> GetComponentsOfNode(const std::string& node_name);

    /**
      * Destroys a component.
      * @param name The component to destroy.
      */
    void DestroyComponent(const std::string& name);

private:
    std::multimap<std::string, std::shared_ptr<Component<ComponentListener> > > mComponents;   //!< The pool of Components.
};

}

#endif
