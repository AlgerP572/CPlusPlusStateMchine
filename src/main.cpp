/*
 * Main.cpp:
 *	Base classes to support a C++ UML state machine.
 *	Copyright (c) 2019 Alger Pike
 ***********************************************************************
 * This file is part of CPlusPLusSateMachine:
 *	https://github.com/AlgerP572/CPlusPlusStateMchine
 *
 *    CPlusPLusSateMachine is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU Lesser General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    CPlusPLusSateMachine is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public License
 *    along with CPlusPLusSateMachine.  If not, see <http://www.gnu.org/licenses/>.
 ***********************************************************************
*/
#include "./SimpleStateMachine/SimpleStateMachine.h"
#include "./KeyboardStateMachine/KeyBoardStateMachine.h"
#include "./KeyboardStateMachineExtended/KeyboardStateModel.h"
#include "./KeyboardStateMachineExtended/KeyBoardStateMachineExtended.h"

void TestSimpleStateMachine();
void TestKeyboardStateMachine();
void TestKeyboardStateMachineExtended();

int main(void)
{	
	TestSimpleStateMachine();
	TestKeyboardStateMachine();
	TestKeyboardStateMachineExtended();
	return 0;
}

void TestSimpleStateMachine()
{
	SimpleStateMachine sm;

	STATES stateNow = sm.GetCurrentState();

	// Init done move to intial state.
	Transition<STATES> transition;
	sm.Trigger(TRIGGERS::DEFAULTENTRY, transition);
	stateNow = sm.GetCurrentState();

	// Self-trigger IDLE to IDLE
	sm.Trigger(TRIGGERS::IDLETRIGGER, transition);
	stateNow = sm.GetCurrentState();

	sm.Trigger(TRIGGERS::FINALTRIGGER, transition);
	stateNow = sm.GetCurrentState();

	sm.Trigger(TRIGGERS::IDLETRIGGER, transition);
	stateNow = sm.GetCurrentState();

	sm.Trigger(TRIGGERS::DEFAULTEXIT, transition);
	stateNow = sm.GetCurrentState();
}

void TestKeyboardStateMachine()
{
	KeyboardStateMachine sm;

	KEYBOARDSTATES stateNow = sm.GetCurrentState();

	Transition<KEYBOARDSTATES> transition;
	sm.Trigger(KEYBOARDTRIGGERS::DEFAULTENTRY, transition);
	stateNow = sm.GetCurrentState();
	if (stateNow != KEYBOARDSTATES::DEFAULT)
		throw "Keyboard state not correct";

	sm.Trigger(KEYBOARDTRIGGERS::ANYKEY, transition);
	stateNow = sm.GetCurrentState();
	if (stateNow != KEYBOARDSTATES::DEFAULT)
		throw "Keyboard state not correct";

	sm.Trigger(KEYBOARDTRIGGERS::CAPSLOCK, transition);
	stateNow = sm.GetCurrentState();
	if (stateNow != KEYBOARDSTATES::CAPSLOCKED)
		throw "Keyboard state not correct";

	sm.Trigger(KEYBOARDTRIGGERS::ANYKEY, transition);
	stateNow = sm.GetCurrentState();
	if (stateNow != KEYBOARDSTATES::CAPSLOCKED)
		throw "Keyboard state not correct";

	sm.Trigger(KEYBOARDTRIGGERS::CAPSLOCK, transition);
	stateNow = sm.GetCurrentState();
	if (stateNow != KEYBOARDSTATES::DEFAULT)
		throw "Keyboard state not correct";
}

void TestKeyboardStateMachineExtended()
{
	KeyboardStateModel stateModel;
	stateModel.SetKeyCount(1000);

	KeyboardStateMachineExtended sm(stateModel);

	KEYBOARDSTATESExtended stateNow = sm.GetCurrentState();

	Transition<KEYBOARDSTATESExtended> transition;
	sm.Trigger(KEYBOARDTRIGGERSExtended::DEFAULTENTRY, transition);
	stateNow = sm.GetCurrentState();
	if (stateNow != KEYBOARDSTATESExtended::DEFAULT)
		throw "Keyboard state not correct";

	while (stateModel.GetKeyCount() > -1)
	{
		stateModel.SetPressedKey('a');
		sm.Trigger(KEYBOARDTRIGGERSExtended::ANYKEY, transition);
		stateNow = sm.GetCurrentState();

		// Hack using 'C' to represent the CAPSLOCK key
		stateModel.SetPressedKey('C');
		sm.Trigger(KEYBOARDTRIGGERSExtended::CAPSLOCK, transition);
		stateNow = sm.GetCurrentState();		
	}

	// Should default exit when count is zero...
	stateNow = sm.GetCurrentState();
	if (stateNow != KEYBOARDSTATESExtended::NOSTATE)
		throw "Keyboard state not correct";
}