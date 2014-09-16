#include "input.h"

Input::Input() {
}

Input::~Input() {
    
}

void Input::onkeypress(int key) {
    this->keyStates[key] = 1;
}

void Input::onkeyup(int key) {
    this->keyStates[key] = 0;
}

void Input::update() {
    
}