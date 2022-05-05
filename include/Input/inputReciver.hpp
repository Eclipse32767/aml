#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>
#include <functional>
#include <unordered_map>
#include <cstdint>


#include <GL/glew.h>
#include <GL/glut.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

#include "result.hpp"

#include "../lib.hpp"
#include "../LowLevelGraphics/window.hpp"

#ifndef AML_INPUT_RECIVER
#define AML_INPUT_RECIVER
namespace aml{
    /*
        class that manage polling of inputs
    */
    class InputReciver{
        private:
            //window is friend class as window holds a GLFWwindow thats needed to scan inputs from
            friend class aml::Window;

            //map containing all key Inputs
            static const size_t keyCount = 316;
            bool keyPressTable[InputReciver::keyCount];
            
            //map containing all mouse button inputs
            static const size_t mouseButtonCount = 8;
            bool mousePressTable[InputReciver::mouseButtonCount];

            //postion of mouse
            glm::vec2 mouseLocation;
            
            //current magnitude of the scrollwheel while scrolling
            glm::vec2 scrollMagnitude = glm::vec2(0,0);

            /*
                glfw key codes start at 32, this is a constant that 
                gets subtracted from each keycode to find its place in keyPresstable
            */
            static const size_t arrayOffset = 32;

            /*
                input callbacks used by the object to poll events from the window.
                all of them are friend functions as they need to access private variables
                of InputReciver to work
            */
            //keyboard callbacks
            static void handleKeyInput(GLFWwindow* window, int key, int scancode, int action, int mods);
            friend void handleKeyInput(GLFWwindow* window, int key, int scancode, int action, int mods);

            //mouse button press callbacks
            static void handleMousePress(GLFWwindow* window,  int button, int action, int mods);
            friend void handleMousePress(GLFWwindow* window,  int button, int action, int mods);
            
            //mouse movement callbacks
            static void handleMouseMovement(GLFWwindow* window, double x, double y);
            friend void handleMouseMovement(GLFWwindow* window, double x, double y);
            
            //scrollwheel callbacks
            static void handleScroll(GLFWwindow* window, double x, double y);
            friend void handleScroll(GLFWwindow* window, double x, double y);

            //gets the input reciver
            static InputReciver* getInputReciver(GLFWwindow* window);
        public:

            /**
             * @brief creates an InputReciver for the selected window
             * 
             * @param window window to poll inputs from
             */
            InputReciver(aml::Window &window);

            //methods for polling inputs

            /**
             * @brief 
             * 
             * @param keycode keycode to check for input 
             * @return true 
             * @return false 
             */
            bool keyPressed(int16_t keycode);

            //checks if a key was pressed only once
            bool keyTriggered(int16_t keycode);

            //checks if a mouse button is pressed
            bool mousePressed(int16_t button);

            //returns the position of the cursor on the window
            glm::vec2 mousePosition();

            //gets mouses scroll
            glm::vec2 scrollAmount();

            //polls for input and fills the inputBuffer
            void pollInput();

    };


}
#endif