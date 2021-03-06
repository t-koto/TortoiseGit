﻿// TortoiseGit - a Windows shell extension for easy version control

// Copyright (C) 2008-2013, 2015-2016, 2018-2020 - TortoiseGit

// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software Foundation,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
//
#include "stdafx.h"
#include "FetchCommand.h"
#include "AppUtils.h"
#include "MessageBox.h"
#include "GitAdminDir.h"

bool FetchCommand::Execute()
{
	if (!GitAdminDir::IsWorkingTreeOrBareRepo(g_Git.m_CurrentDir))
	{
		CMessageBox::Show(GetExplorerHWND(), IDS_NOGITREPO, IDS_APPNAME, MB_ICONERROR);
		return false;
	}

	if (orgPathList.GetCount() > 1)
	{
		bool retVal = true;
		for (int i = 0; i < orgPathList.GetCount(); ++i)
		{
			auto item = orgPathList[i];
			if (!item.IsWCRoot() || !GitAdminDir::IsBareRepo(item.GetWinPathString()))
			{
				retVal = false;
				continue;
			}
			g_Git.m_CurrentDir = item.GetWinPathString();
			SetCurrentDirectory(g_Git.m_CurrentDir);
			retVal &= CAppUtils::Fetch(GetExplorerHWND(), parser.GetVal(L"remote"));
		}
		return retVal;
	}

	return CAppUtils::Fetch(GetExplorerHWND(), parser.GetVal(L"remote"));
}
