//------------------------------------------------------------------------------
//
// PROJECT : 3D Globus
//
// FILE    : NStringTool.cpp
//
// VERSION : 1.0
//
// AUTOR   : Martin Steen
//           Imagon GmbH
//
//
//
//------------------------------------------------------------------------------
//
// Inhalt: Implementation von NStringTool
//
//------------------------------------------------------------------------------
// Revisionsgeschichte:
//
// 02.11.2007 erstellt - Martin Steen
// 20.07.2010 erweitert - Martin Steen
//
//------------------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <string.h>


#include <NStringTool.h>

namespace NStringTool
{
//---------------------------------------------------------------------------
//
// Namespace:  NStringTool
// Methode:    Split
//
//---------------------------------------------------------------------------

    int Split(std::string InputString, stringvector* ResultVector, char SplitChar)
    {
        int OldIndex = 0;
        int NewIndex;

        do
        {
            NewIndex = InputString.find(SplitChar, OldIndex);

            if (NewIndex != std::string::npos)
            {
                ResultVector->push_back(InputString.substr(OldIndex, NewIndex - OldIndex));
                OldIndex = NewIndex + 1;
            }
            else
            {
                ResultVector->push_back(InputString.substr(OldIndex, InputString.size() - OldIndex));
            }
        }while (NewIndex != std::string::npos);

        return ResultVector->size();
    }


//---------------------------------------------------------------------------
//
// Namespace:  NStringTool
// Methode:    Split
//
// Splittet einen String in zwei Teile durch das Zeichen SplitChar
//
// Return     true = Zeichen gefunden
//            false = Zeichen NICHT gefunden (kein Ergebnis)
//
//---------------------------------------------------------------------------

    bool Split(std::string InputString, std::string& s1, std::string& s2, char SplitChar)
    {
        bool r;
        int OldIndex = 0;
        int NewIndex;

        NewIndex = InputString.find(SplitChar, OldIndex);

        if (NewIndex != std::string::npos)
        {
            s1 = InputString.substr(OldIndex, NewIndex - OldIndex);
            OldIndex = NewIndex + 1;

            s2 = InputString.substr(OldIndex, InputString.size() - OldIndex);

            r = true;
        }
        else
        {
            r = false;
        }

        return r;
    }


//---------------------------------------------------------------------------
//
// Namespace:  NStringTool
// Methode:    Split
//
//---------------------------------------------------------------------------

    int Split(std::string InputString, stringvector* ResultVector, char SplitChar, const char b0, const char b1)
    {
        int BrackedOpen = 0;
        std::string InputStringTrimmed;

        for (int i = 0; i < InputString.size(); i++)
        {
            char c = InputString.at(i);
            if (c == b0)
            {
                BrackedOpen += 1;
            }
            else
            if (c == b1)
            {
                BrackedOpen -= 1;
            }
            else
            {
                if ((BrackedOpen > 0) && (c == SplitChar))
                {
                    InputStringTrimmed += '*';
                }
                else
                {
                    InputStringTrimmed += c;
                }
            }
        }

        //std::cout << "InputStringTrimmed=" << InputStringTrimmed << std::endl;
        int r = Split(InputStringTrimmed, ResultVector, SplitChar);

        for (stringvector::iterator it = ResultVector->begin(); it != ResultVector->end(); ++it)
        {
            for (int i = 0; i < it->size(); i++)
            {
                if ((*it)[i] == '*')
                {
                    (*it)[i] = SplitChar;
                }
            }
        }
        return r;
    }

//---------------------------------------------------------------------------
//
// Namespace:  NStringTool
// Methode:    Mask
//
//---------------------------------------------------------------------------
    
    std::string Mask(const std::string& inStr, const std::string& maskChars)
    {
        std::string resultStr;
        for (int i = 0; i < inStr.size(); i++)
        {
            if (maskChars.find(inStr[i]) != std::string::npos)
            {
                resultStr += '\\';
            }
            resultStr += inStr[i];
        }
        return resultStr;
    }


//---------------------------------------------------------------------------
//
// Namespace:  NStringTool
// Methode:    Trim
//
//---------------------------------------------------------------------------

    std::string Trim(std::string InStr, const char* trimChars)
    {
        std::string OutStr;
        std::string::size_type StartIndex;
        std::string::size_type EndIndex;

        StartIndex = InStr.find_first_not_of(trimChars);



        if (StartIndex != std::string::npos)
        {
            EndIndex = InStr.find_last_not_of(trimChars);
            if (EndIndex != std::string::npos)
            {
                if (EndIndex >= StartIndex)
                {
                    OutStr = InStr.substr(StartIndex, EndIndex - StartIndex + 1);
                }
            }
        }

        return OutStr;
    }


//---------------------------------------------------------------------------
//
// Namespace:  NStringTool
// Methode:    TrimValid
//
//---------------------------------------------------------------------------

    std::string TrimValid(std::string InStr, const char* validChars)
    {
        std::string OutStr;
        std::string::size_type StartIndex;
        std::string::size_type EndIndex;

        StartIndex = InStr.find_first_of(validChars);



        if (StartIndex != std::string::npos)
        {
            EndIndex = InStr.find_last_of(validChars);
            if (EndIndex != std::string::npos)
            {
                if (EndIndex >= StartIndex)
                {
                    OutStr = InStr.substr(StartIndex, EndIndex - StartIndex + 1);
                }
            }
        }

        return OutStr;
    }


//---------------------------------------------------------------------------
//
// Namespace:  NStringTool
// Methode:    Trim
//
//---------------------------------------------------------------------------

    void Trim(stringvector& sv, const char* trimChars)
    {
        for (int i = 0; i < sv.size(); i++)
        {
            sv[i] = Trim(sv[i], trimChars);
        }
    }


//---------------------------------------------------------------------------
//
// Namespace:  NStringTool
// Methode:    TrimValid
//
//---------------------------------------------------------------------------

    void TrimValid(stringvector& sv, const char* validChars)
    {
        for (int i = 0; i < sv.size(); i++)
        {
            sv[i] = TrimValid(sv[i], validChars);
        }
    }


//---------------------------------------------------------------------------
//
// Namespace:  NStringTool
// Methode:    ReadLine
//
//---------------------------------------------------------------------------

    int ReadLine(std::ifstream& ifile, std::string* Line)
    {
        char ch;
        bool EndLine = false;

        Line->clear();
        do
        {
            ifile.get(ch);
            if (!ifile.eof())
            {
                if (ch != 0x0D)
                {
                    if (ch != 0x0A)
                    {
                        Line->push_back(ch);
                    }
                    else
                    {
                        EndLine = true;
                    }
                }
            }
            else
            {
                EndLine = true;
            }
        }while (!EndLine);
        return true;
    }


//---------------------------------------------------------------------------
//
// Namespace:  NStringTool
// Methode:    RemoveExtension
//
//
//
//---------------------------------------------------------------------------


    std::string RemoveExtension(const std::string& InStr)
    {
        std::string::size_type idx = InStr.rfind('.');

        if (idx == std::string::npos)
        {
            return InStr;
        }
        return InStr.substr(0, idx);
    }


//---------------------------------------------------------------------------
//
// Namespace:  NStringTool
// Methode:    Cut
//
// Schneidet den InStr VOR CutChar ab
//
// Beispiel:
//
//   Aus c:\temp\datei.txt wird c:\temp
//   (Trennzeichen: \)
//
//
//---------------------------------------------------------------------------

    std::string Cut(const std::string& InStr, char CutChar)
    {
        std::string::size_type idx = InStr.rfind(CutChar);

        if (idx == std::string::npos)
        {
            return InStr;
        }
        return InStr.substr(0, idx);
    }


//---------------------------------------------------------------------------
//
// Namespace:  NStringTool
// Methode:    Shorten
//
//
//
//---------------------------------------------------------------------------

    std::string Shorten(const std::string& InString, const std::string Punkte, int Limit)
    {
        std::string OutString;

        if (InString.size() < Limit)
        {
            OutString = InString;
        }
        else
        {
            OutString = InString.substr(0, Limit) + Punkte;
        }
        return OutString;
    }


//---------------------------------------------------------------------------
//
// Namespace:  NStringTool
// Methode:    ShortenUtf8
//
//
//
//---------------------------------------------------------------------------

    std::string ShortenUtf8(const std::string& Utf8String, const std::string Punkte, int Limit)
    {
        int ix = 0;
        std::string OutString;
        bool LimitBreak = false;

        for (int i = 0; (i < Utf8String.size()) && (i < Limit); i++)
        {
            if ((Utf8String[ix] & 0x80) == 0) // 1 stellig
            {
                ix += 1;
            }
            else
            if ((Utf8String[ix] & 0xE0) == 0xC0) // 2 Stellig
            {
                ix += 2;
            }
            else
            if ((Utf8String[ix] & 0xF0) == 0xE0) // 3 Stellig
            {
                ix += 3;
            }
            else
            if ((Utf8String[ix] & 0xF8) == 0xF0) // 4 stellig
            {
                ix += 4;
            }

            if (i >= Limit)
            {
                OutString = Utf8String.substr(0, ix) + Punkte;
                LimitBreak = true;
            }
        }


        if (!LimitBreak)
        {
            OutString = Utf8String;
        }
        return OutString;
    }


//---------------------------------------------------------------------------
//
// Namespace:  NStringTool
// Methode:    First
//
// Liefert die ersten n Zeichen eines String
//
//---------------------------------------------------------------------------

    std::string First(const std::string& InString, int n)
    {
        return InString.substr(n);
    }


//---------------------------------------------------------------------------
//
// Namespace:  NStringTool
// Methode:    Last
//
// Liefert die letzten n Zeichen eines String
//
//---------------------------------------------------------------------------

    std::string Last(const std::string& InString, int n)
    {
        return InString.substr(InString.size() - n, n);
    }


//---------------------------------------------------------------------------
//
// Klasse:    CStringTool
// Methode:   RemoveBlanks
//
// Entfernen von Leerzeichen vom Anfang und Ende des String
//
//---------------------------------------------------------------------------


    bool IsSpace(char c)
    {
        return (c == ' ') || (c == '\t');
    }


    std::string RemoveBlanks(std::string& InputString)
    {
        int StartIndex;
        int EndIndex;
        std::string OutputString = InputString;

        for (StartIndex = 0;
            (StartIndex < InputString.size()) && IsSpace(InputString[StartIndex]);
            StartIndex++)
        {
        }


        for (EndIndex = InputString.size()-1;
            (EndIndex >= 0) && IsSpace(InputString[EndIndex]);
            EndIndex--)
        {
        }

        if ((StartIndex > 0) || (EndIndex < InputString.size()-1))
        {
            if (EndIndex > StartIndex)
            {
                OutputString = InputString.substr(StartIndex, EndIndex - StartIndex);
            }
        }
        return OutputString;
    }




//
// End of namespace NStringTool
//
}
