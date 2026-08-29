#pragma once
#include <cstdint>
#include <cstring>
#include <string>

namespace KODI::UTILS
{

/**
 * \brief 获取 CJK 字符的拼音
 * \param c 输入的宽字符
 * \return 拼音字符串指针（指向静态只读数据），非 CJK 字符返回 nullptr
 */
const char* GetPinyin(wchar_t c) noexcept;

/**
 * \brief 获取 CJK 字符的拼音首字母
 * \param c 输入的宽字符
 * \return 拼音首字母，非 CJK 字符返回 '\0'
 */
inline char GetPinyinInitial(wchar_t c) noexcept
{
    const char* py = GetPinyin(c);
    return py ? py[0] : '\0';
}

} // namespace KODI::UTILS
