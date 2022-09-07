///////////////////////////////////////////////////////////////////
// Name:        html_encoded_char.cpp
// Purpose:     Handle encoding/decoding of characters for HTML/XML.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/html/html_encoded_char.h"
#include "../../include/string/string.h"

struct ENCODED_CHAR
{
    const char * name;
    const char * value;
};

static const swI16 EncodedCharAlphabeticIdx[] =
{
    0, 8, 9, 11, 13, -1, 20, -1, 21, -1, 26, 27, 28, 29, 31, 40, -1, 44, 45, 47, 50, -1, -1, 55, 56, 58,
    -1, -1, -1, -1, -1, -1,
    59, 73, 77, 89, 96, 109, 115, 118, 122, -1, 133, 134, 149, 155, 165, 180, 193, 194, 208, 226, 235, -1, 244, 245, 246, 249
};

static const ENCODED_CHAR EncodedChars[] =
{
    {"Agrave", "À"}, {"Aacute", "Á"}, {"Acirc", "Â"}, {"Atilde", "Ã"}, {"Auml", "Ä"},
    {"Aring", "Å"}, {"AElig", "Æ"}, {"Alpha", "Α"}, {"Beta", "Β"}, {"Ccedil", "Ç"},
    {"Chi", "Χ"}, {"Delta", "Δ"}, {"Dagger", "‡"}, {"Egrave", "È"}, {"Eacute", "É"},
    {"Ecirc", "Ê"}, {"Euml", "Ë"}, {"ETH", "Ð"}, {"Epsilon", "Ε"}, {"Eta", "Η"},
    {"Gamma", "Γ"}, {"Igrave", "Ì"}, {"Iacute", "Í"}, {"Icirc", "Î"}, {"Iuml", "Ï"},
    {"Iota", "Ι"}, {"Kappa", "Κ"}, {"Lambda", "Λ"}, {"Mu", "Μ"}, {"Ntilde", "Ñ"},
    {"Nu", "Ν"}, {"Ograve", "Ò"}, {"Oacute", "Ó"}, {"Ocirc", "Ô"}, {"Otilde", "Õ"},
    {"Ouml", "Ö"}, {"Oslash", "Ø"}, {"Omicron", "Ο"}, {"Omega", "Ω"}, {"OElig", "Œ"},
    {"Pi", "Π"}, {"Phi", "Φ"}, {"Psi", "Ψ"}, {"Prime", "″"}, {"Rho", "Ρ"},
    {"Sigma", "Σ"}, {"Scaron", "Š"}, {"THORN", "Þ"}, {"Theta", "Θ"}, {"Tau", "Τ"},
    {"Ugrave", "Ù"}, {"Uacute", "Ú"}, {"Ucirc", "Û"}, {"Uuml", "Ü"}, {"Upsilon", "Υ"},
    {"Xi", "Ξ"}, {"Yacute", "Ý"}, {"Yuml", "Ÿ"}, {"Zeta", "Ζ"},
    {"acute", "´"}, {"agrave", "à"}, {"aacute", "á"}, {"acirc", "â"}, {"atilde", "ã"},
    {"auml", "ä"}, {"aring", "å"}, {"aelig", "æ"}, {"alpha", "α"}, {"alefsym", "ℵ"},
    {"ang", "∠"}, {"and", "∧"}, {"asymp", "≈"}, {"amp", "&"}, {"brvbar", "¦"},
    {"beta", "β"}, {"bull", "•"}, {"bdquo", "„"}, {"cent", "¢"}, {"curren", "¤"},
    {"copy", "©"}, {"cedil", "¸"}, {"ccedil", "ç"}, {"chi", "χ"}, {"crarr", "↵"},
    {"cap", "∩"}, {"cup", "∪"}, {"cong", "≅"}, {"clubs", "♣"}, {"circ", "ˆ"},
    {"deg", "°"}, {"divide", "÷"}, {"delta", "δ"}, {"darr", "↓"}, {"dArr", "⇓"},
    {"diams", "♦"}, {"dagger", "†"}, {"egrave", "è"}, {"eacute", "é"}, {"ecirc", "ê"},
    {"euml", "ë"}, {"eth", "ð"}, {"epsilon", "ε"}, {"eta", "η"}, {"exist", "∃"},
    {"empty", "∅"}, {"equiv", "≡"}, {"ensp", " "}, {"emsp", " "}, {"euro", "€"},
    {"frac14", "¼"}, {"frac12", "½"}, {"frac34", "¾"}, {"fnof", "ƒ"}, {"frasl", "⁄"},
    {"forall", "∀"}, {"gamma", "γ"}, {"ge", "≥"}, {"gt", ">"}, {"hellip", "…"},
    {"harr", "↔"}, {"hArr", "⇔"}, {"hearts", "♥"}, {"iexcl", "¡"}, {"iquest", "¿"},
    {"igrave", "ì"}, {"iacute", "í"}, {"icirc", "î"}, {"iuml", "ï"}, {"iota", "ι"},
    {"image", "ℑ"}, {"isin", "∈"}, {"infin", "∞"}, {"int", "∫"}, {"kappa", "κ"},
    {"laquo", "«"}, {"lambda", "λ"}, {"larr", "←"}, {"lArr", "⇐"}, {"lowast", "∗"},
    {"le", "≤"}, {"lceil", "⌈"}, {"lfloor", "⌊"}, {"lang", "⟨"}, {"loz", "◊"},
    {"lt", "<"}, {"lrm", "‎"}, {"lsquo", "‘"}, {"ldquo", "“"}, {"lsaquo", "‹"},
    {"macr", "¯"}, {"micro", "µ"}, {"middot", "·"}, {"mu", "μ"}, {"minus", "−"},
    {"mdash", "—"}, {"nbsp", " "}, {"not", "¬"}, {"ntilde", "ñ"}, {"nu", "ν"},
    {"nabla", "∇"}, {"notin", "∉"}, {"ni", "∋"}, {"ne", "≠"}, {"nsub", "⊄"},
    {"ndash", "–"}, {"ordf", "ª"}, {"ordm", "º"}, {"ograve", "ò"}, {"oacute", "ó"},
    {"ocirc", "ô"}, {"otilde", "õ"}, {"ouml", "ö"}, {"oslash", "ø"}, {"omicron", "ο"},
    {"omega", "ω"}, {"oline", "‾"}, {"or", "∨"}, {"oplus", "⊕"}, {"otimes", "⊗"},
    {"oelig", "œ"}, {"pound", "£"}, {"plusmn", "±"}, {"para", "¶"}, {"pi", "π"},
    {"phi", "φ"}, {"psi", "ψ"}, {"piv", "ϖ"}, {"prime", "′"}, {"part", "∂"},
    {"prod", "∏"}, {"prop", "∝"}, {"perp", "⊥"}, {"permil", "‰"}, {"quot", "\""},
    {"reg", "®"}, {"raquo", "»"}, {"rho", "ρ"}, {"real", "ℜ"}, {"rarr", "→"},
    {"rArr", "⇒"}, {"radic", "√"}, {"rceil", "⌉"}, {"rfloor", "⌋"}, {"rang", "⟩"},
    {"rlm", "‏"}, {"rsquo", "’"}, {"rdquo", "”"}, {"rsaquo", "›"}, {"sect", "§"},
    {"shy", "­"}, {"sup2", "²"}, {"sup3", "³"}, {"sup1", "¹"}, {"szlig", "ß"},
    {"sigmaf", "ς"}, {"sigma", "σ"}, {"sum", "∑"}, {"sim", "∼"}, {"sub", "⊂"},
    {"sup", "⊃"}, {"sube", "⊆"}, {"supe", "⊇"}, {"sdot", "⋅"}, {"spades", "♠"},
    {"scaron", "š"}, {"sbquo", "‚"}, {"times", "×"}, {"thorn", "þ"}, {"theta", "θ"},
    {"tau", "τ"}, {"thetasym", "ϑ"}, {"trade", "™"}, {"there4", "∴"}, {"tilde", "˜"},
    {"thinsp", " "}, {"uml", "¨"}, {"ugrave", "ù"}, {"uacute", "ú"}, {"ucirc", "û"},
    {"uuml", "ü"}, {"upsilon", "υ"}, {"upsih", "ϒ"}, {"uarr", "↑"}, {"uArr", "⇑"},
    {"weierp", "℘"}, {"xi", "ξ"}, {"yen", "¥"}, {"yacute", "ý"}, {"yuml", "ÿ"},
    {"zeta", "ζ"}, {"zwnj", "‌"}, {"zwj", "‍"}
};

swUI32 SwHtmlEncodedChar::GetEncodedCharValue(const char * encodedValue, char * dest, swUI32 bufferLen)
{
    int x;
    swUI32 len;

    if (!encodedValue || !dest)
        return 0;

    dest[0] = '\0';

    if (!isalpha(encodedValue[0]))
        return 0;

    if (encodedValue[0] < 'A' || encodedValue[0] > 'z')
        return 0;

    x = EncodedCharAlphabeticIdx[encodedValue[0] - 'A'];

    if (x == -1)
        return 0;

    while (x < N_ENCODED_CHARS)
    {
        if (EncodedChars[x].name[0] > encodedValue[0])
            break;

        if (strcmp(EncodedChars[x].name, encodedValue) == 0)
        {
            len = (swUI32) strlen(EncodedChars[x].value);

            if (len >= bufferLen)
                return 0;

            strcpy(dest, EncodedChars[x].value);

            return len;
        }

        x ++;
    }

    return 0;
}

bool SwHtmlEncodedChar::IsReservedChar(char ch)
{
    if (ch == '<' || ch == '>' || ch == '&')
        return true;

    return false;
}

swUI8 SwHtmlEncodedChar::GetCharSize(char ch)
{
    if (ch == '<' || ch == '>')
        return 4;
    if (ch == '&')
        return 5;
    if (ch == ' ')
        return 6;

    return 1;
}

swUI32 SwHtmlEncodedChar::CalcEncodedStringSize(const char * source)
{
    swUI32 size = 0, pos = 0;
    bool space = false;

    if (!source)
        return 0;

    while (source[pos] != '\0')
    {
        if (source[pos] == ' ')
        {
            if (!space)
                size += 1;
            else
                size += GetCharSize(source[pos]);

            space = true;
        }
        else
            size += GetCharSize(source[pos]);

        pos ++;
    }

    return size;
}

swUI32 SwHtmlEncodedChar::EncodeString(const char * source, SwString & dest, bool prevSpace)
{
    swUI32 posSrc = 0, posDest = 0;
    bool space = prevSpace;

    if (!source || !dest.Size(CalcEncodedStringSize(source) + 1))
        return 0;

    dest.SetAt(0, '\0');

    while (source[posSrc] != '\0')
    {
        if (source[posSrc] == '<')
        {
            dest.Strcat("&lt;");
            posDest += 4;
        }
        else if (source[posSrc] == '>')
        {
            dest.Strcat("&gt;");
            posDest += 4;
        }
        else if (source[posSrc] == '&')
        {
            dest.Strcat("&amp;");
            posDest += 5;
        }
        else if (source[posSrc] == ' ')
        {
            if (space)
            {
                dest.Strcat("&nbsp;");
                posDest += 6;
            }
            else
            {
                dest.Strcat(" ");
                posDest += 1;
            }

            space = true;
        }
        else
        {
            dest.SetAt(posDest, source[posSrc]);
            dest.SetAt(posDest + 1, '\0');
            posDest ++;
            space = false;
        }

        posSrc ++;
    }

    dest.SetAt(posDest, '\0');
    return posDest;
}

bool SwHtmlEncodedChar::IsXmlReservedChar(char ch)
{
    if (ch == '<' || ch == '>' || ch == '&' || ch == '"' || ch == '\'')
        return true;

    return false;
}

swUI8 SwHtmlEncodedChar::GetXmlCharSize(char ch)
{
    if (ch == '<' || ch == '>')
        return 4;
    if (ch == '&')
        return 5;
    if (ch == '"' || ch == '\'')
        return 6;

    return 1;
}

swUI32 SwHtmlEncodedChar::CalcXmlEncodedStringSize(const char * source)
{
    swUI32 size = 0, pos = 0;

    if (!source)
        return 0;

    while (source[pos] != '\0')
    {
        size += GetXmlCharSize(source[pos]);
        pos ++;
    }

    return size;
}

swUI32 SwHtmlEncodedChar::XmlEncodeString(const char * source, SwString & dest)
{
    swUI32 posSrc = 0, posDest = 0;

    if (!source || !dest.Size(CalcXmlEncodedStringSize(source) + 1))
        return 0;

    dest.SetAt(0, '\0');

    while (source[posSrc] != '\0')
    {
        if (source[posSrc] == '<')
        {
            dest.Strcat("&lt;");
            posDest += 4;
        }
        else if (source[posSrc] == '>')
        {
            dest.Strcat("&gt;");
            posDest += 4;
        }
        else if (source[posSrc] == '&')
        {
            dest.Strcat("&amp;");
            posDest += 5;
        }
        else if (source[posSrc] == '\'')
        {
            dest.Strcat("&apos;");
            posDest += 6;
        }
        else if (source[posSrc] == '"')
        {
            dest.Strcat("&quot;");
            posDest += 6;
        }
        else
        {
            dest.SetAt(posDest, source[posSrc]);
            dest.SetAt(posDest + 1, '\0');
            posDest ++;
        }

        posSrc ++;
    }

    dest.SetAt(posDest, '\0');
    return posDest;
}
