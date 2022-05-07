#include <GL/glew.h>
#include <GL/glut.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>


#ifndef AML_INPUT_TYPE
#define AML_INPUT_TYPE
namespace aml{
    /**
     * @brief enumerator for different types of input
     * 
     */
    enum InputType{
        /// @brief mousewheel input
        scroll,
        /// @brief cursor movement input
        cursorMove,
        /// @brief key press input
        keyPress,
        /// @brief key up input
        keyUp
    };
}


#endif