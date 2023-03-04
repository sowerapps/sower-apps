///////////////////////////////////////////////////////////////////
// Name:        geotrfilewriter.cpp
// Purpose:     Creates a translation file for geo locations.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/utility/geotrfilewriter.h"
#include "../../include/geo/geolocation.h"
#include "../../include/string/string.h"
#include "../../include/string/stringw.h"
#include "../../include/html/html_encoded_char.h"
#include "../../include/filesys/file.h"

void CreateDataListString(SwString & buffer, const char * id)
{
    if (!id)
        return;

    buffer = "";
    buffer = "<datalist id=\"";
    buffer += id;
    buffer += "\">\n";

    for (swUI32 i = 1; i < N_GEO_LOCATIONS; i ++)
    {
        buffer += "<option value=\"";
        buffer += SwGeo::GetData(i).name;
        buffer += "\"/>\n";
    }

    buffer += "</datalist>\n";
}

void CreateGeoTranslationFile(const char * path)
{
    if (!path)
        return;

    SwString buffer, conversion;
    buffer.Size(4096);

    FILE * file = SwFopen(path, FMD_WC);

    if (!file)
        return;

    fputs("<html>\n<head>\n<meta content=\"text/html; charset=utf8\" http-equiv=\"content-type\">\n</head>\n<body>\n", file);
    CreateDataListString(buffer, "String Identifiers");
    buffer += '\n';
    fwrite(buffer, buffer.Strlen(), 1, file);
    fputs("<table border=\"1\" width=\"100%%\">\n<caption>English (US)</caption>\n<tbody>\n", file);

    for (swUI32 i = 1; i < N_GEO_LOCATIONS; i ++)
    {
        SwHtmlEncodedChar::XmlEncodeString(SwGeo::GetData(i).name, conversion);
        sprintf(buffer, "<tr param1=\"0\" param2=\"0\">\n<td>%s</td>\n<td>%s</td>\n</tr>\n", conversion.GetArray(), conversion.GetArray());
        fwrite(buffer, buffer.Strlen(), 1, file);
    }

    fputs("</tbody>\n</table>\n", file);
    fputs("\n</body>\n</html>", file);

    fclose(file);
}
