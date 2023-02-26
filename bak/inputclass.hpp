//////////////////////////////////////////////
// Filename: inputclass.hpp               //
////////////////////////////////////////////
#ifndef INPUTCLASS_HPP_INCLUDED
#define INPUTCLASS_HPP_INCLUDED

#include <array>

class InputClass
{
public:
	InputClass() = default;
	InputClass(const InputClass&) = delete;
	~InputClass() = default;


	void Initialize();
	void KeyDown(unsigned int);
	void KeyUp(unsigned int);

	bool IsKeyDown(unsigned int);
private:
	std::array<bool, 256> m_keys;
};

#endif