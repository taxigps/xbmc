#pragma once

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

#include "InputCodingTable.h"

class CInputCodingTableBaiduPY : public CInputCodingTable
{
public:
  CInputCodingTableBaiduPY();
  virtual ~CInputCodingTableBaiduPY() {}

  virtual bool GetWordListPage(const std::string& strCode, std::vector<std::wstring>& words, bool isFirstPage);
private:
  std::wstring UnicodeToWString(const std::string& unicode);
  int m_api_begin; // baidu api begin num
  int m_api_end;   // baidu api end num
  bool m_api_nomore;
};
