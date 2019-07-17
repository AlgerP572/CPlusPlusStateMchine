/*
 * CapsLockedExtended.cpp:
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
#include "KeyboardStatesTriggersExtended.h"
#include "CapsLockedExtended.h"


CapsLockedExtended::CapsLockedExtended(KeyboardStateModel& stateModel) :
	_stateModel(stateModel)
{
	AddTriggerGuard(KEYBOARDTRIGGERSExtended::CAPSLOCK, &CapsLockedExtended::CapsLockTriggerGuard);
	AddTriggerGuard(KEYBOARDTRIGGERSExtended::ANYKEY, &CapsLockedExtended::AnyKeyTriggerGuard);
}

KEYBOARDSTATESExtended CapsLockedExtended::CapsLockTriggerGuard(KEYBOARDTRIGGERSExtended trigger)
{
	return KEYBOARDSTATESExtended::DEFAULT;
}

KEYBOARDSTATESExtended CapsLockedExtended::AnyKeyTriggerGuard(KEYBOARDTRIGGERSExtended trigger)
{
	if (_stateModel.GetKeyCount() > 0)
	{
		return KEYBOARDSTATESExtended::CAPSLOCKED;
	}
	else
	{
		return KEYBOARDSTATESExtended::NOSTATE;
	}
}

void CapsLockedExtended::ExitAction()
{
	if (_stateModel.GetPressedKey() != 'C')
	{
		_stateModel.DecrementKeyCount();
	}
}