/*Copyright (c) 2013, Artem Kashkanov
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.*/
#include "buttons.h"

void buttons::Setup(void){
	HwButtonsSetup(0);
	ClearAll();//clear all slots
}


void buttons::Clear(void){//clear slots
  for (uint8_t _i = 0; _i < HwButtonsCount(); _i++)
    buttslot[_i] = 0;
}

void buttons:AddSlot(void (*_f)()){//connect only zero slot. Any button call one function

	ClearAll();
	buttslot[0]=_f;
}

void buttons::AddSlot(uint8_t _slot, void (*_f)()){//button for separate function
  if (_slot < HwButtonsCount()){
	buttslot[_slot]=_f;//put function into slot
  }
}

void buttons::Search(void){//Tmanager function
	uint8_t buttonscurrstate = HwButtonsState(0);
	if (buttonscurrstate)//if any button was pressed
		{ //check all buttons slot
		for (uint8_t buttonslot = 0; buttonslot < HwButtonsCount(); buttonslot++)
			{//detect edge only
			if (buttslot[buttonslot]) {
				if (buttonscurrstate == (1 << buttonslot) && !(buttonoldstate&(1 << buttonslot))) 
				{
					(*buttslot[buttonslot])();
				}//call button slot if not NUll
				else{
				//undefined behaviour prevent
				}
			else {
			//we Must check zero slot before default use
				if (buttslot[0]){
					*buttslot[0])();
				}
			}
		}
	}
	buttonoldstate = buttonscurrstate;//save old state
}