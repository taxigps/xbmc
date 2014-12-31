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

#include "InputCodingTableBaiduPY.h"
#include "filesystem/CurlFile.h"
#include "utils/StringUtils.h"
#include "utils/RegExp.h"

CInputCodingTableBaiduPY::CInputCodingTableBaiduPY()
{
  m_codechars = "abcdefghijklmnopqrstuvwxyz";
}

std::wstring CInputCodingTableBaiduPY::UnicodeToWString(const std::string& unicode)
{
  std::wstring result = L"";
  for (unsigned int i = 0; i < unicode.length(); i += 6)
  {
    int c;
    sscanf(unicode.c_str() + i, "\\u%x", &c);
    result += (WCHAR)c;
  }
  return result;
}

bool CInputCodingTableBaiduPY::GetWordListPage(const std::string& strCode, std::vector<std::wstring>& words, bool isFirstPage)
{
  if (isFirstPage)
  {
    words.clear();
    m_api_begin = 0;
    m_api_end = 20;
    m_api_nomore = false;
  }
  else
  {
    if (m_api_nomore)
      return false;
    m_api_begin += 20;
    m_api_end += 20;
  }
  if (!strCode.length())
    return false;

  XFILE::CCurlFile http;
  std::string strUrl, strData;
  strUrl = StringUtils::Format("http://olime.baidu.com/py?input=%s&inputtype=py&bg=%d&ed=%d&result=hanzi&resultcoding=unicode&ch_en=0&clientinfo=web", strCode.c_str(), m_api_begin, m_api_end);
  http.Get(strUrl, strData);

  CRegExp reg;
  reg.RegComp("\\[\"(.+?)\",[^\\]]+\\]");
  int pos = 0;
  int num = 0;
  while ((pos = reg.RegFind(strData.c_str(), pos)) >= 0)
  {
    num++;
    std::string full = reg.GetMatch(0);
    std::string word = reg.GetMatch(1);
    pos += full.length();
    words.push_back(UnicodeToWString(word));
  }
  http.Close();
  if (num < 20)
    m_api_nomore = true;
  return true;
}
