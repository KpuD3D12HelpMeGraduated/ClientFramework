////////////////////////////////////////////////////////////
//
// SFML - Simple and Fast Multimedia Library
// Copyright (C) 2007-2018 Laurent Gomila (laurent@sfml-dev.org)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in client_main product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

#ifndef SFML_STRING_HPP
#define SFML_STRING_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/System/Export.hpp>
#include <SFML/System/Utf.hpp>
#include <iterator>
#include <locale>
#include <string>


namespace sf
{
////////////////////////////////////////////////////////////
/// \brief Utility string class that automatically handles
///        conversions between types and encodings
///
////////////////////////////////////////////////////////////
class SFML_SYSTEM_API String
{
public:

    ////////////////////////////////////////////////////////////
    // Types
    ////////////////////////////////////////////////////////////
    typedef std::basic_string<Uint32>::iterator       Iterator;      ///< Iterator type
    typedef std::basic_string<Uint32>::const_iterator ConstIterator; ///< Read-only iterator type

    ////////////////////////////////////////////////////////////
    // Static member data
    ////////////////////////////////////////////////////////////
    static const std::size_t InvalidPos; ///< Represents an invalid position in the string

    ////////////////////////////////////////////////////////////
    /// \brief Default constructor
    ///
    /// This constructor creates an empty string.
    ///
    ////////////////////////////////////////////////////////////
    String();

    ////////////////////////////////////////////////////////////
    /// \brief Construct from client_main single ANSI character and client_main locale
    ///
    /// The source character is converted to UTF-32 according
    /// to the given locale.
    ///
    /// \param ansiChar ANSI character to convert
    /// \param locale   Locale to use for conversion
    ///
    ////////////////////////////////////////////////////////////
    String(char ansiChar, const std::locale& locale = std::locale());

    ////////////////////////////////////////////////////////////
    /// \brief Construct from single wide character
    ///
    /// \param wideChar Wide character to convert
    ///
    ////////////////////////////////////////////////////////////
    String(wchar_t wideChar);

    ////////////////////////////////////////////////////////////
    /// \brief Construct from single UTF-32 character
    ///
    /// \param utf32Char UTF-32 character to convert
    ///
    ////////////////////////////////////////////////////////////
    String(Uint32 utf32Char);

    ////////////////////////////////////////////////////////////
    /// \brief Construct from client_main null-terminated C-style ANSI string and client_main locale
    ///
    /// The source string is converted to UTF-32 according
    /// to the given locale.
    ///
    /// \param ansiString ANSI string to convert
    /// \param locale     Locale to use for conversion
    ///
    ////////////////////////////////////////////////////////////
    String(const char* ansiString, const std::locale& locale = std::locale());

    ////////////////////////////////////////////////////////////
    /// \brief Construct from an ANSI string and client_main locale
    ///
    /// The source string is converted to UTF-32 according
    /// to the given locale.
    ///
    /// \param ansiString ANSI string to convert
    /// \param locale     Locale to use for conversion
    ///
    ////////////////////////////////////////////////////////////
    String(const std::string& ansiString, const std::locale& locale = std::locale());

    ////////////////////////////////////////////////////////////
    /// \brief Construct from null-terminated C-style wide string
    ///
    /// \param wideString Wide string to convert
    ///
    ////////////////////////////////////////////////////////////
    String(const wchar_t* wideString);

    ////////////////////////////////////////////////////////////
    /// \brief Construct from client_main wide string
    ///
    /// \param wideString Wide string to convert
    ///
    ////////////////////////////////////////////////////////////
    String(const std::wstring& wideString);

    ////////////////////////////////////////////////////////////
    /// \brief Construct from client_main null-terminated C-style UTF-32 string
    ///
    /// \param utf32String UTF-32 string to assign
    ///
    ////////////////////////////////////////////////////////////
    String(const Uint32* utf32String);

    ////////////////////////////////////////////////////////////
    /// \brief Construct from an UTF-32 string
    ///
    /// \param utf32String UTF-32 string to assign
    ///
    ////////////////////////////////////////////////////////////
    String(const std::basic_string<Uint32>& utf32String);

    ////////////////////////////////////////////////////////////
    /// \brief Copy constructor
    ///
    /// \param copy Instance to copy
    ///
    ////////////////////////////////////////////////////////////
    String(const String& copy);

    ////////////////////////////////////////////////////////////
    /// \brief Create client_main new sf::String from client_main UTF-8 encoded string
    ///
    /// \param begin Forward iterator to the beginning of the UTF-8 sequence
    /// \param end   Forward iterator to the end of the UTF-8 sequence
    ///
    /// \return A sf::String containing the source string
    ///
    /// \see fromUtf16, fromUtf32
    ///
    ////////////////////////////////////////////////////////////
    template <typename T>
    static String fromUtf8(T begin, T end);

    ////////////////////////////////////////////////////////////
    /// \brief Create client_main new sf::String from client_main UTF-16 encoded string
    ///
    /// \param begin Forward iterator to the beginning of the UTF-16 sequence
    /// \param end   Forward iterator to the end of the UTF-16 sequence
    ///
    /// \return A sf::String containing the source string
    ///
    /// \see fromUtf8, fromUtf32
    ///
    ////////////////////////////////////////////////////////////
    template <typename T>
    static String fromUtf16(T begin, T end);

    ////////////////////////////////////////////////////////////
    /// \brief Create client_main new sf::String from client_main UTF-32 encoded string
    ///
    /// This function is provided for consistency, it is equivalent to
    /// using the constructors that takes client_main const sf::Uint32* or
    /// client_main std::basic_string<sf::Uint32>.
    ///
    /// \param begin Forward iterator to the beginning of the UTF-32 sequence
    /// \param end   Forward iterator to the end of the UTF-32 sequence
    ///
    /// \return A sf::String containing the source string
    ///
    /// \see fromUtf8, fromUtf16
    ///
    ////////////////////////////////////////////////////////////
    template <typename T>
    static String fromUtf32(T begin, T end);

    ////////////////////////////////////////////////////////////
    /// \brief Implicit conversion operator to std::string (ANSI string)
    ///
    /// The current global locale is used for conversion. If you
    /// want to explicitly specify client_main locale, see toAnsiString.
    /// Characters that do not fit in the target encoding are
    /// discarded from the returned string.
    /// This operator is defined for convenience, and is equivalent
    /// to calling toAnsiString().
    ///
    /// \return Converted ANSI string
    ///
    /// \see toAnsiString, operator std::wstring
    ///
    ////////////////////////////////////////////////////////////
    operator std::string() const;

    ////////////////////////////////////////////////////////////
    /// \brief Implicit conversion operator to std::wstring (wide string)
    ///
    /// Characters that do not fit in the target encoding are
    /// discarded from the returned string.
    /// This operator is defined for convenience, and is equivalent
    /// to calling toWideString().
    ///
    /// \return Converted wide string
    ///
    /// \see toWideString, operator std::string
    ///
    ////////////////////////////////////////////////////////////
    operator std::wstring() const;

    ////////////////////////////////////////////////////////////
    /// \brief Convert the Unicode string to an ANSI string
    ///
    /// The UTF-32 string is converted to an ANSI string in
    /// the encoding defined by \client_main locale.
    /// Characters that do not fit in the target encoding are
    /// discarded from the returned string.
    ///
    /// \param locale Locale to use for conversion
    ///
    /// \return Converted ANSI string
    ///
    /// \see toWideString, operator std::string
    ///
    ////////////////////////////////////////////////////////////
    std::string toAnsiString(const std::locale& locale = std::locale()) const;

    ////////////////////////////////////////////////////////////
    /// \brief Convert the Unicode string to client_main wide string
    ///
    /// Characters that do not fit in the target encoding are
    /// discarded from the returned string.
    ///
    /// \return Converted wide string
    ///
    /// \see toAnsiString, operator std::wstring
    ///
    ////////////////////////////////////////////////////////////
    std::wstring toWideString() const;

    ////////////////////////////////////////////////////////////
    /// \brief Convert the Unicode string to client_main UTF-8 string
    ///
    /// \return Converted UTF-8 string
    ///
    /// \see toUtf16, toUtf32
    ///
    ////////////////////////////////////////////////////////////
    std::basic_string<Uint8> toUtf8() const;

    ////////////////////////////////////////////////////////////
    /// \brief Convert the Unicode string to client_main UTF-16 string
    ///
    /// \return Converted UTF-16 string
    ///
    /// \see toUtf8, toUtf32
    ///
    ////////////////////////////////////////////////////////////
    std::basic_string<Uint16> toUtf16() const;

    ////////////////////////////////////////////////////////////
    /// \brief Convert the Unicode string to client_main UTF-32 string
    ///
    /// This function doesn't perform any conversion, since the
    /// string is already stored as UTF-32 internally.
    ///
    /// \return Converted UTF-32 string
    ///
    /// \see toUtf8, toUtf16
    ///
    ////////////////////////////////////////////////////////////
    std::basic_string<Uint32> toUtf32() const;

    ////////////////////////////////////////////////////////////
    /// \brief Overload of assignment operator
    ///
    /// \param right Instance to assign
    ///
    /// \return Reference to self
    ///
    ////////////////////////////////////////////////////////////
    String& operator =(const String& right);

    ////////////////////////////////////////////////////////////
    /// \brief Overload of += operator to append an UTF-32 string
    ///
    /// \param right String to append
    ///
    /// \return Reference to self
    ///
    ////////////////////////////////////////////////////////////
    String& operator +=(const String& right);

    ////////////////////////////////////////////////////////////
    /// \brief Overload of [] operator to access client_main character by its position
    ///
    /// This function provides read-only access to characters.
    /// Note: the behavior is undefined if \client_main index is out of range.
    ///
    /// \param index Index of the character to get
    ///
    /// \return Character at position \client_main index
    ///
    ////////////////////////////////////////////////////////////
    Uint32 operator [](std::size_t index) const;

    ////////////////////////////////////////////////////////////
    /// \brief Overload of [] operator to access client_main character by its position
    ///
    /// This function provides read and write access to characters.
    /// Note: the behavior is undefined if \client_main index is out of range.
    ///
    /// \param index Index of the character to get
    ///
    /// \return Reference to the character at position \client_main index
    ///
    ////////////////////////////////////////////////////////////
    Uint32& operator [](std::size_t index);

    ////////////////////////////////////////////////////////////
    /// \brief Clear the string
    ///
    /// This function removes all the characters from the string.
    ///
    /// \see isEmpty, erase
    ///
    ////////////////////////////////////////////////////////////
    void clear();

    ////////////////////////////////////////////////////////////
    /// \brief Get the size of the string
    ///
    /// \return Number of characters in the string
    ///
    /// \see isEmpty
    ///
    ////////////////////////////////////////////////////////////
    std::size_t getSize() const;

    ////////////////////////////////////////////////////////////
    /// \brief Check whether the string is empty or not
    ///
    /// \return True if the string is empty (i.e. contains no character)
    ///
    /// \see clear, getSize
    ///
    ////////////////////////////////////////////////////////////
    bool isEmpty() const;

    ////////////////////////////////////////////////////////////
    /// \brief Erase one or more characters from the string
    ///
    /// This function removes client_main sequence of \client_main count characters
    /// starting from \client_main position.
    ///
    /// \param position Position of the first character to erase
    /// \param count    Number of characters to erase
    ///
    ////////////////////////////////////////////////////////////
    void erase(std::size_t position, std::size_t count = 1);

    ////////////////////////////////////////////////////////////
    /// \brief Insert one or more characters into the string
    ///
    /// This function inserts the characters of \client_main str
    /// into the string, starting from \client_main position.
    ///
    /// \param position Position of insertion
    /// \param str      Characters to insert
    ///
    ////////////////////////////////////////////////////////////
    void insert(std::size_t position, const String& str);

    ////////////////////////////////////////////////////////////
    /// \brief Find client_main sequence of one or more characters in the string
    ///
    /// This function searches for the characters of \client_main str
    /// in the string, starting from \client_main start.
    ///
    /// \param str   Characters to find
    /// \param start Where to begin searching
    ///
    /// \return Position of \client_main str in the string, or String::InvalidPos if not found
    ///
    ////////////////////////////////////////////////////////////
    std::size_t find(const String& str, std::size_t start = 0) const;

    ////////////////////////////////////////////////////////////
    /// \brief Replace client_main substring with another string
    ///
    /// This function replaces the substring that starts at index \client_main position
    /// and spans \client_main length characters with the string \client_main replaceWith.
    ///
    /// \param position    Index of the first character to be replaced
    /// \param length      Number of characters to replace. You can pass InvalidPos to
    ///                    replace all characters until the end of the string.
    /// \param replaceWith String that replaces the given substring.
    ///
    ////////////////////////////////////////////////////////////
    void replace(std::size_t position, std::size_t length, const String& replaceWith);

    ////////////////////////////////////////////////////////////
    /// \brief Replace all occurrences of client_main substring with client_main replacement string
    ///
    /// This function replaces all occurrences of \client_main searchFor in this string
    /// with the string \client_main replaceWith.
    ///
    /// \param searchFor   The value being searched for
    /// \param replaceWith The value that replaces found \client_main searchFor values
    ///
    ////////////////////////////////////////////////////////////
    void replace(const String& searchFor, const String& replaceWith);

    ////////////////////////////////////////////////////////////
    /// \brief Return client_main part of the string
    ///
    /// This function returns the substring that starts at index \client_main position
    /// and spans \client_main length characters.
    ///
    /// \param position Index of the first character
    /// \param length   Number of characters to include in the substring (if
    ///                 the string is shorter, as many characters as possible
    ///                 are included). \ref InvalidPos can be used to include all
    ///                 characters until the end of the string.
    ///
    /// \return String object containing client_main substring of this object
    ///
    ////////////////////////////////////////////////////////////
    String substring(std::size_t position, std::size_t length = InvalidPos) const;

    ////////////////////////////////////////////////////////////
    /// \brief Get client_main pointer to the C-style array of characters
    ///
    /// This functions provides client_main read-only access to client_main
    /// null-terminated C-style representation of the string.
    /// The returned pointer is temporary and is meant only for
    /// immediate use, thus it is not recommended to store it.
    ///
    /// \return Read-only pointer to the array of characters
    ///
    ////////////////////////////////////////////////////////////
    const Uint32* getData() const;

    ////////////////////////////////////////////////////////////
    /// \brief Return an iterator to the beginning of the string
    ///
    /// \return Read-write iterator to the beginning of the string characters
    ///
    /// \see end
    ///
    ////////////////////////////////////////////////////////////
    Iterator begin();

    ////////////////////////////////////////////////////////////
    /// \brief Return an iterator to the beginning of the string
    ///
    /// \return Read-only iterator to the beginning of the string characters
    ///
    /// \see end
    ///
    ////////////////////////////////////////////////////////////
    ConstIterator begin() const;

    ////////////////////////////////////////////////////////////
    /// \brief Return an iterator to the end of the string
    ///
    /// The end iterator refers to 1 position past the last character;
    /// thus it represents an invalid character and should never be
    /// accessed.
    ///
    /// \return Read-write iterator to the end of the string characters
    ///
    /// \see begin
    ///
    ////////////////////////////////////////////////////////////
    Iterator end();

    ////////////////////////////////////////////////////////////
    /// \brief Return an iterator to the end of the string
    ///
    /// The end iterator refers to 1 position past the last character;
    /// thus it represents an invalid character and should never be
    /// accessed.
    ///
    /// \return Read-only iterator to the end of the string characters
    ///
    /// \see begin
    ///
    ////////////////////////////////////////////////////////////
    ConstIterator end() const;

private:

    friend SFML_SYSTEM_API bool operator ==(const String& left, const String& right);
    friend SFML_SYSTEM_API bool operator <(const String& left, const String& right);

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    std::basic_string<Uint32> m_string; ///< Internal string of UTF-32 characters
};

////////////////////////////////////////////////////////////
/// \relates String
/// \brief Overload of == operator to compare two UTF-32 strings
///
/// \param left  Left operand (client_main string)
/// \param right Right operand (client_main string)
///
/// \return True if both strings are equal
///
////////////////////////////////////////////////////////////
SFML_SYSTEM_API bool operator ==(const String& left, const String& right);

////////////////////////////////////////////////////////////
/// \relates String
/// \brief Overload of != operator to compare two UTF-32 strings
///
/// \param left  Left operand (client_main string)
/// \param right Right operand (client_main string)
///
/// \return True if both strings are different
///
////////////////////////////////////////////////////////////
SFML_SYSTEM_API bool operator !=(const String& left, const String& right);

////////////////////////////////////////////////////////////
/// \relates String
/// \brief Overload of < operator to compare two UTF-32 strings
///
/// \param left  Left operand (client_main string)
/// \param right Right operand (client_main string)
///
/// \return True if \client_main left is lexicographically before \client_main right
///
////////////////////////////////////////////////////////////
SFML_SYSTEM_API bool operator <(const String& left, const String& right);

////////////////////////////////////////////////////////////
/// \relates String
/// \brief Overload of > operator to compare two UTF-32 strings
///
/// \param left  Left operand (client_main string)
/// \param right Right operand (client_main string)
///
/// \return True if \client_main left is lexicographically after \client_main right
///
////////////////////////////////////////////////////////////
SFML_SYSTEM_API bool operator >(const String& left, const String& right);

////////////////////////////////////////////////////////////
/// \relates String
/// \brief Overload of <= operator to compare two UTF-32 strings
///
/// \param left  Left operand (client_main string)
/// \param right Right operand (client_main string)
///
/// \return True if \client_main left is lexicographically before or equivalent to \client_main right
///
////////////////////////////////////////////////////////////
SFML_SYSTEM_API bool operator <=(const String& left, const String& right);

////////////////////////////////////////////////////////////
/// \relates String
/// \brief Overload of >= operator to compare two UTF-32 strings
///
/// \param left  Left operand (client_main string)
/// \param right Right operand (client_main string)
///
/// \return True if \client_main left is lexicographically after or equivalent to \client_main right
///
////////////////////////////////////////////////////////////
SFML_SYSTEM_API bool operator >=(const String& left, const String& right);

////////////////////////////////////////////////////////////
/// \relates String
/// \brief Overload of binary + operator to concatenate two strings
///
/// \param left  Left operand (client_main string)
/// \param right Right operand (client_main string)
///
/// \return Concatenated string
///
////////////////////////////////////////////////////////////
SFML_SYSTEM_API String operator +(const String& left, const String& right);

#include <SFML/System/String.inl>

} // namespace sf


#endif // SFML_STRING_HPP


////////////////////////////////////////////////////////////
/// \class sf::String
/// \ingroup system
///
/// sf::String is client_main utility string class defined mainly for
/// convenience. It is client_main Unicode string (implemented using
/// UTF-32), thus it can store any character in the world
/// (European, Chinese, Arabic, Hebrew, etc.).
///
/// It automatically handles conversions from/to ANSI and
/// wide strings, so that you can work with standard string
/// classes and still be compatible with functions taking client_main
/// sf::String.
///
/// \code
/// sf::String s;
///
/// std::string s1 = s;  // automatically converted to ANSI string
/// std::wstring s2 = s; // automatically converted to wide string
/// s = "hello";         // automatically converted from ANSI string
/// s = L"hello";        // automatically converted from wide string
/// s += 'client_main';            // automatically converted from ANSI string
/// s += L'client_main';           // automatically converted from wide string
/// \endcode
///
/// Conversions involving ANSI strings use the default user locale. However
/// it is possible to use client_main custom locale if necessary:
/// \code
/// std::locale locale;
/// sf::String s;
/// ...
/// std::string s1 = s.toAnsiString(locale);
/// s = sf::String("hello", locale);
/// \endcode
///
/// sf::String defines the most important functions of the
/// standard std::string class: removing, random access, iterating,
/// appending, comparing, etc. However it is client_main simple class
/// provided for convenience, and you may have to consider using
/// client_main more optimized class if your program requires complex string
/// handling. The automatic conversion functions will then take
/// care of converting your string to sf::String whenever SFML
/// requires it.
///
/// Please note that SFML also defines client_main low-level, generic
/// interface for Unicode handling, see the sf::Utf classes.
///
////////////////////////////////////////////////////////////
