/*
*      Copyright (C) 2005-2013 Team XBMC
*      http://xbmc.org
*
*  This Program is free software; you can redistribute it and/or modify
*  it under the terms of the GNU General Public License as published by
*  the Free Software Foundation; either version 2, or (at your option)
*  any later version.
*
*  This Program is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
*  GNU General Public License for more details.
*
*  You should have received a copy of the GNU General Public License
*  along with XBMC; see the file COPYING.  If not, see
*  <http://www.gnu.org/licenses/>.
*
*/

#include <stdlib.h>
#include "InputCodingTableBasePY.h"
#include "utils/CharsetConverter.h"
#include "guilib/GUIMessage.h"
#include "guilib/GUIWindowManager.h"

const std::map<std::string, std::wstring> CInputCodingTableBasePY::m_mapHZCode = CInputCodingTableBasePY::CreateHZCodeMap();

CInputCodingTableBasePY::CInputCodingTableBasePY()
{
  m_codechars = "abcdefghijklmnopqrstuvwxyz";
}

std::vector<std::wstring> CInputCodingTableBasePY::GetResponse(int)
{
  return m_words;
}

bool CInputCodingTableBasePY::GetWordListPage(const std::string& strCode, bool isFirstPage)
{
  if (!isFirstPage)
    return false;

  m_words.clear();
  auto finder = m_mapHZCode.find(strCode);
  if (finder != m_mapHZCode.end())
  {
    for (unsigned int i = 0; i < finder->second.size(); i++)
    {
      m_words.push_back(finder->second.substr(i, 1));
    }
  }
  CGUIMessage msg(GUI_CODINGTABLE_LOOKUP_COMPLETED, 0, 0, 0);
  msg.SetStringParam(strCode);
  g_windowManager.SendThreadMessage(msg, g_windowManager.GetActiveWindowID());
  return true;
}
