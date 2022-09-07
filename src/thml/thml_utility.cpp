///////////////////////////////////////////////////////////////////
// Name:        thml_utility.cpp
// Purpose:     Utility functions for working with ThML files.
//              Parse Osis scripture id's.
//              Find and read into a buffer - css, title, dublin core.
//              Write basic ThML header, dublin core, and footer for a new
//              ThML file.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/thml/thml_utility.h"
#include "../../include/string/strparser.h"
#include "../../include/bible/standard_bible.h"

char headerstart[] = "<ThML>\n<ThML.head>\n<electronicEdInfo>\n";
char headerclose[] = "</electronicEdInfo>\n</ThML.head>\n<ThML.body>\n";
char thmlclose[] = "\n</ThML.body>\n</ThML>";
char blankdc[] = "<DC>\n<DC.Title>Untitled</DC.Title>\n<DC.Creator></DC.Creator>\n<DC.Publisher></DC.Publisher>\n<DC.Subject scheme=\"\"></DC.Subject>\n<DC.Date></DC.Date>\n<DC.Type></DC.Type>\n<DC.Format></DC.Format>\n<DC.Identifier scheme=\"\">\n</DC.Identifier>\n<DC.Source></DC.Source>\n<DC.Language></DC.Language>\n<DC.Rights></DC.Rights>\n</DC>\n";

SwOsisId::SwOsisId()
{
    Reset();
};

SwOsisId::~SwOsisId()
{
}

void SwOsisId::Reset()
{
    m_book = 0;
    m_chapter = 0;
    m_verse = 0;
    strcpy(m_versification, "kjv");
}

bool SwOsisId::Parse(const char * id)
{
    if (!id)
        return false;

    SwStrParser strList;
    strList.SetDeliminator('.');
    const char * p = strchr(id, ':');

    if (!p)
        p = id;

    strList.ParseString(p);

    m_book = 0;

    if (strList.GetItems() > 0)
    {
        if (!SwThMLUtility::IdentifyBook(strList.GetItem(0), m_book))
            return false;
    }
    else
        return false;

    if (strList.GetItems() > 1)
    {
        m_chapter = atoi(strList.GetItem(1));

        if (m_chapter < 1)
            return false;
    }
    else
        return true;

    if (strList.GetItems() > 2)
    {
        m_verse = atoi(strList.GetItem(2));

        if (m_verse < 1)
            return false;
    }

    return true;
}

void SwOsisId::SetVersification(const char * versification)
{
    if (!versification || strlen(versification) > 6)
        return;

    strcpy(m_versification, versification);
}

void OsisRef::Reset()
{
    m_start.Reset();
    m_end.Reset();
}

bool OsisRef::Parse(const char * ref)
{
    if (!ref)
        return false;

    if (!m_start.Parse(ref))
        return false;

   const char * p = strchr(ref, '-');

    if (p)
        return m_end.Parse(p + 1);

    return true;
}

static const char * ThMLID [67][3] =
{
//	ThML id		OSIS id		Short Book Title
    "",		    "",			"", // Alignment
    "Gen",		"Gen",		"Genesis",
    "Exod",		"Exod",		"Exodus",
    "Lev",		"Lev",		"Leviticus",
    "Num",		"Num",		"Numbers",
    "Deut",		"Deut",		"Deuteronomy",
    "Josh",		"Josh",		"Joshua",
    "Judg",		"Judg",		"Judges",
    "Ruth",		"Ruth",		"Ruth",
    "iSam",		"1Sam",		"1 Samuel",
    "iiSam",	"2Sam",		"2 Samuel",
    "iKgs",		"1Kgs",		"1 Kings",
    "iiKgs",	"2Kgs",		"2 Kings",
    "iChr",		"1Chr",		"1 Chronicles",
    "iiChr",	"2Chr",		"2 Chronicles",
    "Ezra",		"Ezra",		"Ezra",
    "Neh",		"Neh",		"Nehemiah",
    "Esth",		"Esth",		"Esther",
    "Job",		"Job",		"Job",
    "Ps",		"Ps",		"Psalms",
    "Prov",		"Prov",		"Proverbs",
    "Eccl",		"Eccl",		"Ecclesiastes",
    "Song",		"Song",		"Song of Solomon",
    "Isa",		"Isa",		"Isaiah",
    "Jer",		"Jer",		"Jeremiah",
    "Lam",		"Lam",		"Lamentations",
    "Ezek",		"Ezek",		"Ezekiel",
    "Dan",		"Dan",		"Daniel",
    "Hos",		"Hos",		"Hosea",
    "Joel",		"Joel",		"Joel",
    "Amos",		"Amos",		"Amos",
    "Obad",		"Obad",		"Obadiah",
    "Jonah",	"Jonah",	"Jonah",
    "Mic",		"Mic",		"Micah",
    "Nah",		"Nah",		"Nahum",
    "Hab",		"Hab",		"Habakkuk",
    "Zeph",		"Zeph",		"Zephaniah",
    "Hag",		"Hag",		"Haggai",
    "Zech",		"Zech",		"Zechariah",
    "Mal",		"Mal",		"Malachi",
    "Matt",		"Matt",		"Matthew",
    "Mark",		"Mark",		"Mark",
    "Luke",		"Luke",		"Luke",
    "John",		"John",		"John",
    "Acts",		"Acts",		"Acts",
    "Rom",		"Rom",		"Romans",
    "iCor",		"1Cor",		"1 Corinthians",
    "iiCor",	"2Cor",		"2 Corinthians",
    "Gal",		"Gal",		"Galatians",
    "Eph",		"Eph",		"Ephesians",
    "Phil",		"Phil",		"Philippians",
    "Col",		"Col",		"Colossians",
    "iThess",	"1Thess",	"1 Thessalonians",
    "iiThess",	"2Thess",	"2 Thessalonians",
    "iTim",		"1Tim",		"1 Timothy",
    "iiTim",	"2Tim",		"2 Timothy",
    "Titus",	"Titus",	"Titus",
    "Phlm",		"Phlm",		"Philemon",
    "Heb",		"Heb",		"Hebrews",
    "Jas",		"Jas",		"James",
    "iPet",		"1Pet",	    "1 Peter",
    "iiPet",	"2Pet",	    "2 Peter",
    "iJohn",	"1John",	"1 John",
    "iiJohn",	"2John",	"2 John",
    "iiiJohn",	"3John",	"3 John",
    "Jude",		"Jude",		"Jude",
    "Rev",		"Rev",		"Revelation"
};

SwThMLUtility::SwThMLUtility()
{
}

SwThMLUtility::~SwThMLUtility()
{
}

swI8 SwThMLUtility::IsFileThML(FILE * file)
{
	int n = 0;
	char buff[1024];
	while (n < 10)
	{
		if (!fgets(buff, 1024, file))
			break;

		if (strstr(buff, "<ThML") != NULL)
			return 1;
		if (strstr(buff, "<?thml") != NULL)
			return 2;

		n++;
	}

	return -1;
}

swI8 SwThMLUtility::IsFileThML(const char * path)
{
    if (!path)
        return -1;

    FILE * f = SwFopen(path, FMD_R);

    if (!f)
    {
        return 0;
    }


	int n = 0;
	char buff[1024];
	swI8 status = -1;
	while (n < 10)
	{
		if (!fgets(buff, 1024, f))
			break;

		if (strstr(buff, "<ThML") != NULL)
        {
            status = 1;
            break;
        }

		if (strstr(buff, "<?thml") != NULL)
        {
            status = 2;
            break;
        }


		n++;
	}

	fclose(f);
	return status;
}

bool SwThMLUtility::GetTitle(SwString & buffer, const char * path)
{
    FILE * f = SwFopen(path, FMD_R);

    if (!f)
        return false;

    char s[8192];

    if (!ReadTitle(s, 8192, f, 0))
    {
        fclose(f);
        return false;
    }

    fclose(f);

    SwString temp;
    temp.Size(strlen(s)+ 1);
    swUI8 lastChar = LCH_BREAK;
    SwHtml::Html2Text(s, temp, temp.GetSize(), lastChar, true);
    buffer.Copy(temp);
    buffer.TrimRight(' ');
    return true;
}

bool SwThMLUtility::GetTitleW(SwStringW & buffer, const char * path)
{
    FILE * f = SwFopen(path, FMD_R);

    if (!f)
        return false;

    char s[8192];

    if (!ReadTitle(s, 8192, f, 0))
    {
        fclose(f);
        return false;
    }

    fclose(f);

    SwString temp;
    temp.Size(strlen(s)+ 1);
    swUI8 lastChar = LCH_BREAK;
    SwHtml::Html2Text(s, temp, temp.GetSize(), lastChar, true);
    buffer.Copy(temp);
    buffer.TrimRight(L' ');
    return true;
}

bool SwThMLUtility::ReadTitle(char * buffer, swUI32 bufferLen, FILE * file, swUI32 filePos)
{
    int space = bufferLen, bytes;
    char * p1 = buffer;
    bool titleStart = false;

    if (!buffer || !file)
        return false;

    fseek(file, filePos, SEEK_SET);

    while(fgets(p1, space -1, file) && space)
    {
        if (strstr(p1, "<ThML.body"))
            return false;

        if (titleStart == false)
        {
            if (strstr(p1, "<title") || strstr(p1, "<DC.Title"))
                titleStart = true;
            else
                continue;
        }

        if (strstr(p1, "</title") || strstr(p1, "</DC.Title"))
            return true;

        bytes = strlen(p1);
        p1 += bytes;
        space -= bytes;

        if (space <= 1)
            return false;
    }

    return false;
}

bool SwThMLUtility::GetIdentifier(SwString & buffer, const char * path)
{
    FILE * f = SwFopen(path, FMD_R);

    if (!f)
        return false;

    char s[8192];

    if (!ReadIdentifier(s, 8192, f, 0))
    {
        fclose(f);
        return false;
    }

    fclose(f);

    buffer.Size(strlen(s)+ 1);
    swUI8 lastChar = LCH_BREAK;
    SwHtml::Html2Text(s, buffer, buffer.GetSize(), lastChar, true);

    return true;
}

bool SwThMLUtility::ReadIdentifier(char * buffer, swUI32 bufferLen, FILE * file, swUI32 filePos)
{
    int space = bufferLen, bytes;
    char * p1 = buffer;
    bool start = false;

    if (!buffer || !file)
        return false;

    fseek(file, filePos, SEEK_SET);

    while(fgets(p1, space -1, file) && space)
    {
        if (strstr(p1, "<ThML.body"))
            return false;

        if (start == false)
        {
            if (strstr(p1, "<DC.Subject scheme=\"LCCN\"") || strstr(p1, "<DC.Subject scheme=\"lccn\"") ||
                strstr(p1, "<DC.Subject scheme=\"ISBN\"")  || strstr(p1, "<DC.Subject scheme=\"isbn\"") ||
                strstr(p1, "<DC.Subject scheme=\"SWR\"")  || strstr(p1, "<DC.Subject scheme=\"swr\""))
                start = true;
            else
                continue;
        }

        if (strstr(p1, "</"))
            return true;

        bytes = strlen(p1);
        p1 += bytes;
        space -= bytes;

        if (space <= 1)
            return false;
    }

    return false;
}

bool SwThMLUtility::ReadCss(char * buffer, swUI32 bufferLen, FILE * file, swUI32 filePos)
{
    int space = bufferLen, bytes;
    char * p1 = buffer;
    bool start = false;

    if (!buffer || !file)
        return false;

    fseek(file, filePos, SEEK_SET);

    while(fgets(p1, space -1, file) && space)
    {
        if (strstr(p1, "<ThML.body"))
            return false;

        if (start == false)
        {
            if (strstr(p1, "<style type=\"text/css\""))
            {
                start = true;
            }

            continue;
        }

        if (strstr(p1, "</style") != NULL)
        {
            p1[0] = '\0';
            return true;
        }

        bytes = strlen(p1);
        p1 += bytes;
        space -= bytes;

        if (space <= 1)
            return false;
    }

    return false;
}

bool SwThMLUtility::GetDublinCore(SwString & buffer, const char * path)
{
    FILE * f = SwFopen(path, FMD_R);

    if (!f)
        return false;

    buffer.Reset();
    buffer.Size(8192);

    if (!ReadDublinCore(buffer, 8192, f, 0))
    {
        fclose(f);
        return false;
    }

    fclose(f);

    return true;
}

bool SwThMLUtility::ReadDublinCore(char * buffer, swUI32 bufferLen, FILE * file, swUI32 filePos)
{
    int space = bufferLen, bytes;
    char * p1 = buffer;
    bool dcStart = false;

    if (!buffer || !file)
        return false;

    fseek(file, filePos, SEEK_SET);

    while(fgets(p1, space -1, file) && space)
    {
        if (strstr(p1, "<ThML.body"))
            return false;

        if (dcStart == false)
        {
            if (strstr(p1, "<DC"))
                dcStart = true;
            else
                continue;
        }

        if (strstr(p1, "</DC>"))
            return true;

        bytes = strlen(p1);
        p1 += bytes;
        space -= bytes;

        if (space <= 1)
            return false;
    }

    return false;
}

int SwThMLUtility::ReadDivText(SwString & buffer, FILE * file, swUI32 filePos)
{
    char s[2048];
    swUI32 bytes = 0;
    char * p;
    bool divStart = false;

    if (!file)
        return 0;

    fseek(file, filePos, SEEK_SET);

    while (fgets(s, 2048, file))
    {
        if (divStart == false)
        {
            p = strstr(s, "<div");
            if (p && isdigit(p[4]))
            {
                divStart = true;
                bytes = strlen(s);

                if (buffer.GetSize() < bytes && !buffer.Size(bytes + 1000))
                    return 0;

                buffer = s;
                buffer.SetCount(bytes);
                continue;
            }
            else
                continue;
        }

        p = strstr(s, "<div");

        if (p && isdigit(s[4]))
            return 1;

        bytes += strlen(s);

        if (buffer.GetSize() < bytes && !buffer.Size(bytes + 1000))
            return 0;

        buffer.Strcat(s);
        p = strstr(s, "</div");

        if (p && isdigit(s[5]))
            return 1;
    }

    return 0;
}

void SwThMLUtility::GetSyncValue(const char * source, swUI8 & syncType, swUI16 & syncValue)
{
    SwString buff;

    if (!source)
        return;

    syncType = 0;
    syncValue = 0;

    if (SwThMLParser::GetNamedValue("value", source, buff) == 1)
    {
        if (buff.GetAt(0) == 'g' || buff.GetAt(0) == 'G')
            syncType = SYNC_TYPE_GREEK;
        else if (buff.GetAt(0) == 'h' || buff.GetAt(0) == 'H')
            syncType = SYNC_TYPE_HEBREW;
        else
            return;

        if (isdigit(buff.GetAt(1)))
            syncValue = atoi(buff + 1);
    }
}

bool SwThMLUtility::IdentifyBook(const char * name, swUI8 & book)
{
    if (!name)
        return false;

    for (int i = 0; i < 67; i++)
    {
        if (stricmp(name, ThMLID[i][0]) == 0 || stricmp(name, ThMLID[i][1]) == 0)
        {
            book = i;
            return true;
        }
    }

    return false;
}

const char * SwThMLUtility::GetThMLBookIdString(swUI8 book, bool abbrev)
{
    if (book > 66)
        return "";

    if (abbrev)
        return ThMLID[book][0];

    return ThMLID[book][2];
}

bool SwThMLUtility::ParseScriptureId(const char * id, swUI8 & book, swUI8 & chapter, swUI8 & verse)
{
    if (!id)
        return false;

    book = 0;
    chapter = 0;
    verse = 0;

    SwString buffer;
    buffer.Copy(id);

    char * p = strchr(buffer, '.');

    if (p)
    {
        *p = '\0';
        p++;
    }
    else
        return false;

    if (!IdentifyBook(buffer, book))
    {
        book = SwStandardBible::IdentifyBibleBookName(buffer);

        if (!book)
            return false;
    }

    if (p)
        chapter = atoi(p);
    else
        return false;

    p++;

    p = strchr(p, '.');

    if (p)
    {
        p++;
        verse = atoi(p);
    }

    return true;
}

bool SwThMLUtility::ParseScriptureId(const char * id, SwScriptureRange & sr)
{
    return ParseScriptureId(id, sr.m_book, sr.m_chapter, sr.m_verseStart, sr.m_verseEnd);
}

bool SwThMLUtility::ParseScriptureId(const char * id, swUI8 & book, swUI8 & chapter, swUI8 & verseStart, swUI8 & verseEnd)
{
    if (!id)
        return false;


    book = 0;
    chapter = 0;
    verseStart = 0;
    verseEnd = 0;


    SwString buffer;
    buffer.Copy(id);

    char * p = strchr(buffer, '.');

    if (p)
    {
        *p = '\0';
        p++;
    }
    else
        return false;

    if (!IdentifyBook(buffer, book))
    {
        book = SwStandardBible::IdentifyBibleBookName(buffer);

        if (!book)
            return false;
    }

    if (p)
        chapter = atoi(p);
    else
        return false;

    p++;

    p = strchr(p, '.');

    if (p)
    {
        p++;
        verseStart = atoi(p);
        verseEnd = verseStart;
    }
    else
        return true;

    char * p2, * p3;

    p2 = strrchr(p, '-');
    p3 = strrchr(p, ',');

    if (!p3 && !p2)
        return true;

    if (p3 > p2)
        p2 = p3;

    if (p2)
    {
        p2++;
        verseEnd = atoi(p2);
    }

    return true;
}


bool SwThMLUtility::ParsePassageId(const char * id, swUI8 & book, swUI8 & chapter, swUI8 & verse)
{
    if (!id)
        return false;

    book = 0;
    chapter = 0;
    verse = 0;

    SwString buffer;
    buffer.Copy(id);

    char * p = strchr(buffer, ' ');

    if (p)
    {
        *p = '\0';
        p++;
    }
    else
        return false;

    if (!IdentifyBook(buffer, book))
    {
        book = SwStandardBible::IdentifyBibleBookName(buffer);

        if (!book)
            return false;
    }

    if (p)
        chapter = atoi(p);
    else
        return false;

    p++;

    p = strchr(p, ':');

    if (p)
    {
        p++;
        verse = atoi(p);
    }

    return true;
}

bool SwThMLUtility::ParsePassageId(const char * id, SwScriptureRange & sr)
{
    return ParsePassageId(id, sr.m_book, sr.m_chapter, sr.m_verseStart, sr.m_verseEnd);
}

bool SwThMLUtility::ParsePassageId(const char * id, swUI8 & book, swUI8 & chapter, swUI8 & verseStart, swUI8 & verseEnd)
{
    if (!id)
        return false;


    book = 0;
    chapter = 0;
    verseStart = 0;
    verseEnd = 0;


    SwString buffer;
    buffer.Copy(id);

    char * p = strchr(buffer, ' ');

    if (p)
    {
        *p = '\0';
        p++;
    }
    else
        return false;

    if (!IdentifyBook(buffer, book))
    {
        book = SwStandardBible::IdentifyBibleBookName(buffer);

        if (!book)
            return false;
    }

    if (p)
        chapter = atoi(p);
    else
        return false;

    p++;

    p = strchr(p, ':');

    if (p)
    {
        p++;
        verseStart = atoi(p);
        verseEnd = verseStart;
    }
    else
        return true;

    char * p2, * p3;

    p2 = strrchr(p, '-');
    p3 = strrchr(p, ',');

    if (!p3 && !p2)
        return true;

    if (p3 > p2)
        p2 = p3;

    if (p2)
    {
        p2++;
        verseEnd = atoi(p2);
    }

    return true;
}


const char * SwThMLUtility::WriteOpenHeader(FILE * file)
{
    if (file)
        fputs(headerstart, file);

    return headerstart;
}

const char * SwThMLUtility::WriteCloseHeader(FILE * file)
{
    if (file)
        fputs(headerclose, file);

    return headerclose;
}

const char * SwThMLUtility::WriteDublinCore(FILE * file)
{
    if (file)
        fputs(blankdc, file);

    return blankdc;
}

const char * SwThMLUtility::WriteFooter(FILE * file)
{
    if (file)
        fputs(thmlclose, file);

    return thmlclose;
}

swUI8 SwThMLUtility::IdentifyCategory(const char * ccsubject)
{
    if (!ccsubject)
    {
        return CCEL_UNKNOWN;
    }

	if (strstr(ccsubject, "mysticism"))
		return CCEL_MYSTICISM;
	else if (strstr(ccsubject, "fiction"))
		return CCEL_FICTION;
	else if (strstr(ccsubject, "creed"))
		return CCEL_CREED;
	else if (strstr(ccsubject, "hymn") || strstr(ccsubject, "hymnology"))
		return CCEL_HYMN;
	else if (strstr(ccsubject, "reference"))
		return CCEL_REFERENCE;
	else if (strstr(ccsubject, "early"))
		return CCEL_EARLY;
	else if (strstr(ccsubject, "history"))
		return CCEL_HISTORY;
	else if (strstr(ccsubject, "sermons"))
		return CCEL_SERMON;
	else if (strstr(ccsubject, "bible"))
		return CCEL_BIBLE;
	else if (strstr(ccsubject, "classic"))
		return CCEL_CLASSIC;
    else if (strstr(ccsubject, "biography"))
		return CCEL_BIOGRAPHY;
    else if (strstr(ccsubject, "christian life"))
		return CCEL_CHRISTIANLIFE;
    else if (strstr(ccsubject, "ethics"))
		return CCEL_ETHICS;
    else if (strstr(ccsubject, "science"))
		return CCEL_SCIENCE;
    else if (strstr(ccsubject, "symbols"))
		return CCEL_SYMBOLS;
    else if (strstr(ccsubject, "theology"))
		return CCEL_THEOLOGY;
    else if (strstr(ccsubject, "worship"))
		return CCEL_WORSHIP;

	return CCEL_UNKNOWN;
}

bool SwThMLUtility::CreateInstallPathFromUrl(const char * base, const char * url, char * buffer)
{
    if (!base || !url || !buffer)
    {
        return false;
    }


	const char * start = strstr(url, "//www");
	if (!start)
		return false;

	start += 2;
	start = strchr(start, '/');

	if (!start)
		return 0;

	strcpy(buffer, base);
	strcat(buffer, start);

	char * p = strstr(buffer, "/cache");
	if (p)
	{
		memmove(p, p + 6, strlen(p + 6) + 1);
	}

	return true;
}
