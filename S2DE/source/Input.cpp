#include "Input.h"

#include <iostream>
#include <list>

using namespace S2DE;

static std::list<InputBinding*> inputs;


void Input::AddBinding(std::string name, SDL_Keycode binding) {
  inputs.push_back(new InputBinding(name, binding));
}


void Input::SetPress(SDL_Keycode key) {
  std::list<InputBinding*>::iterator it = inputs.begin();
	for (it = inputs.begin(); it != inputs.end(); it++) {
		InputBinding* input = *it;
		if(input->binding == key) input->press = true;
	}
}


void Input::Flush() {
  std::list<InputBinding*>::iterator it = inputs.begin();
	for (it = inputs.begin(); it != inputs.end(); it++) {
		InputBinding* input = *it;
		input->press = false;
	}
}


void Input::CheckRelease() {
  std::list<InputBinding*>::iterator it = inputs.begin();
	for (it = inputs.begin(); it != inputs.end(); it++) {
		InputBinding* input = *it;
    if(input->press && input->release) input->release = false;
    else if (!input->press && !input->release) input->release = true;
	}
}

bool Input::GetPress(std::string name) {
  std::list<InputBinding*>::iterator it = inputs.begin();
	for (it = inputs.begin(); it != inputs.end(); it++) {
		InputBinding* input = *it;
		if(name == input->name) return input->press;
	}
  return false;
}

bool Input::GetClick(std::string name) {
  std::list<InputBinding*>::iterator it = inputs.begin();
	for (it = inputs.begin(); it != inputs.end(); it++) {
		InputBinding* input = *it;
		if(name == input->name) return input->press && input->release;
	}
  return false;
}
