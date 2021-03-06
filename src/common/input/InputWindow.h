// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
// ******************************************************************
// *
// *  This file is part of the Cxbx project.
// *
// *  Cxbx and Cxbe are free software; you can redistribute them
// *  and/or modify them under the terms of the GNU General Public
// *  License as published by the Free Software Foundation; either
// *  version 2 of the license, or (at your option) any later version.
// *
// *  This program is distributed in the hope that it will be useful,
// *  but WITHOUT ANY WARRANTY; without even the implied warranty of
// *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// *  GNU General Public License for more details.
// *
// *  You should have recieved a copy of the GNU General Public License
// *  along with this program; see the file COPYING.
// *  If not, write to the Free Software Foundation, Inc.,
// *  59 Temple Place - Suite 330, Bostom, MA 02111-1307, USA.
// *
// *  (c) 2019 ergo720
// *
// *  All rights reserved
// *
// ******************************************************************

#pragma once

#include "InputManager.h"
#include "common\Settings.hpp"
#include <Commctrl.h>

#define PROFILE_LOAD   1
#define PROFILE_SAVE   2
#define PROFILE_DELETE 3
#define RUMBLE_SET     4
#define RUMBLE_UPDATE  5
#define RUMBLE_TEST    6
#define RUMBLE_CLEAR   7
#define BUTTON_CLEAR   8

#define XINPUT_DEFAULT 1
#define DINPUT_DEFAULT 2

LRESULT CALLBACK ProfileNameSubclassProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData);


class InputWindow
{
public:
	void Initialize(HWND hwnd, int port_num, int dev_type);
	void InitRumble(HWND hwnd);
	~InputWindow();
	void UpdateDeviceList();
	void BindButton(int ControlID);
	void BindDefault();
	void ClearBindings();
	void UpdateProfile(const std::string& name, int command);
	void UpdateRumble(int command);
	void UpdateCurrentDevice();
	bool IsProfileSaved();


private:
	typedef std::vector<Settings::s_input_profiles>::iterator ProfileIt;
	InputDevice::Input* DetectInput(InputDevice* const Device, int ms);
	void DetectOutput(int ms);
	ProfileIt FindProfile(const std::string& name);
	void LoadProfile(const std::string& name);
	bool SaveProfile(const std::string& name);
	void DeleteProfile(const std::string& name);
	void OverwriteProfile(const std::string& name);
	void LoadDefaultProfile();
	int EnableDefaultButton();

	// xbox device under configuration
	EmuDevice* m_DeviceConfig;
	// handle of the window
	HWND m_hwnd_window;
	// handle of the device list combobox
	HWND m_hwnd_device_list;
	// handle of the profile list combobox
	HWND m_hwnd_profile_list;
	// handle of the rumble window
	HWND m_hwnd_rumble;
	// handle of the rumble combobox
	HWND m_hwnd_rumble_list;
	// handle of the default bindings button
	HWND m_hwnd_default;
	// type of the device
	int m_dev_type;
	// num of buttons of device under configuration
	int m_max_num_buttons;
	// xbox port number the host device attaches to (0 - 3)
	int m_port_num;
	// host device under configuration
	std::string m_host_dev;
	// currently selected rumble control
	std::string m_rumble;
	// indicates if the current profile has unsaved changes
	bool m_bHasChanges;
	// prevent current input attempt to set the previous input at same time
	std::atomic<bool> m_bIsBinding;
};

extern InputWindow* g_InputWindow;
