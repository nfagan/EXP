//
//  Target.hpp
//  EXPTask
//
//  Created by Nick Fagan on 12/2/17.
//

#ifndef Target_hpp
#define Target_hpp

#include <EXPGL/Input/InputXY.hpp>
#include <EXPUtil/thread/spinlock.hpp>
#include <memory>
#include <functional>
#include <atomic>
#include <glm/glm.hpp>

namespace EXP {
    class Target
    {
        friend class TargetSet;
    public:
        Target(const std::shared_ptr<InputXY> input_source);
        
        bool InBounds();
        void SetPosition(glm::vec2 position);
        void SetSize(float size);
        void OnBoundsCheck(std::function<bool(Target*)> bounds_function);
        unsigned GetId();
        
    private:
        std::atomic<unsigned> id;
        std::shared_ptr<InputXY> input_source;
        std::function<bool(Target*)> bounds_function;
        glm::vec2 position;
        std::atomic<float> size;
        spinlock position_lock;
        spinlock bounds_function_lock;
        
        glm::vec2 get_position();
        void set_id(unsigned id);
        
        bool bounds_function_circle();
    };
}

#endif /* Target_hpp */
