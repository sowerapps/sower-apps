///////////////////////////////////////////////////////////////////
// Name:        basic.cpp
// Purpose:     SwRichTextInterface tag handler-s.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../../../include/interface/richtext/richtextinterface.h"
#include "../../../../include/appi/appifa.h"
#include "../../../../include/html/html_css.h"
#include "../../../../include/thml/thml_css.h"
#include "../../../../include/filesys/streambuffer.h"
#include "../../../../include/filesys/file.h"

swUI32 SwRichTextInterface::Onblock(swUI32 node)
{
    if (GetNodeType(node) == NODE_TYPE_BEGIN_TAG)
    {
        if (m_markupType == MARKUP_THML)
            SwThMLCss::GetElementStyle(GetNodeElementIdentifier(node), m_attrList);
        else
            SwHtmlCss::GetElementStyle(GetNodeElementIdentifier(node), m_attrList);
        GetBlockStyle(node);

        if (!m_richAttr.m_display)
        {
            return Onhide(node);
        }

        SetEndStyleFlag(node, BeginBlockStyle(node));
    }
    else if (GetNodeType(node) == NODE_TYPE_UNPAIRED_TAG)
    {
        Paragraph();
    }
    else if (GetNodeType(node) == NODE_TYPE_END_TAG)
    {
        Paragraph();
        EndBlockStyle(node);
    }

    return node;
}

swUI32 SwRichTextInterface::Onhide(swUI32 node)
{
    swUI32 id;

    if (GetNodeType(node) == NODE_TYPE_BEGIN_TAG)
    {
        id = GetNodeMate(node);

        if (id != NODE_ID_INVALID)
            return id;
    }

    return node;
}

swUI32 SwRichTextInterface::Oninline(swUI32 node)
{
    if (GetNodeType(node) == NODE_TYPE_BEGIN_TAG)
    {
        if (m_markupType == MARKUP_THML)
            SwThMLCss::GetElementStyle(GetNodeElementIdentifier(node), m_attrList);
        else
            SwHtmlCss::GetElementStyle(GetNodeElementIdentifier(node), m_attrList);
        GetInlineStyle(node);

        if (!m_richAttr.m_display)
        {
            return Onhide(node);
        }

        SetEndStyleFlag(node, BeginInlineStyle(node));
    }
    else if (GetNodeType(node) == NODE_TYPE_UNPAIRED_TAG)
    {
        if (m_markupType == MARKUP_THML)
            SwThMLCss::GetElementStyle(GetNodeElementIdentifier(node), m_attrList);
        else
            SwHtmlCss::GetElementStyle(GetNodeElementIdentifier(node), m_attrList);
        GetInlineStyle(node);

        if (!m_richAttr.m_display)
        {
            return Onhide(node);
        }

        BeginInlineStyle(node);
    }
    else if (GetNodeType(node) == NODE_TYPE_END_TAG)
    {
        EndInlineStyle(node);
    }

    return node;
}

swUI32 SwRichTextInterface::Onvoid(swUI32 node)
{
    return node;
}

swUI32 SwRichTextInterface::Ona(swUI32 node)
{
    SwString buffer;

    if (GetNodeType(node) == NODE_TYPE_BEGIN_TAG)
    {
        if (GetNamedValueFromNode(node, "href", buffer))
        {

            if (m_markupType == MARKUP_THML)
                SwThMLCss::GetElementStyle(GetNodeElementIdentifier(node), m_attrList);
            else
                SwHtmlCss::GetElementStyle(GetNodeElementIdentifier(node), m_attrList);
            GetInlineStyle(node);

            buffer.Insert(0, "href:");
            if (m_moduleId != NODE_ID_INVALID_16 && m_isModule)
            {
                swUI16 managerPos = SwApplicationInterface::GetModuleManager().FindByMID(m_moduleId);
                if (managerPos != NODE_ID_INVALID_16 && SwApplicationInterface::GetModuleManager().GetAt(managerPos))
                {
                    buffer += " identifier:";
                    buffer += SwApplicationInterface::GetModuleManager().GetAt(managerPos)->GetHeader().GetIdentifier();
                }
            } // If m_isModule is false it is a ThML file.
            else if (m_moduleId != NODE_ID_INVALID_16 && !m_isModule)
            {
                char s[100];
                sprintf(s, "%u", m_moduleId);
                buffer += " identifier:";
                buffer += s;
            }

            m_richAttr.SetURL(buffer.GetArray());
            m_richAttr.SetTextColour(*wxBLUE);
            m_richAttr.SetFontUnderlined(true);
            SetEndStyleFlag(node, BeginInlineStyle(node, true));
        }
        else if (GetNamedValueFromNode(node, "name", buffer) || GetNamedValueFromNode(node, "id", buffer))
        {
            m_rich->GetAnchors().Add(buffer, m_rich->GetInsertionPoint());
        }
    }
    else if (GetNodeType(node) == NODE_TYPE_END_TAG)
    {
        EndInlineStyle(node);
    }

    return node;
}

swUI32 SwRichTextInterface::Onbr(swUI32 node)
{
    LineBreak();
    return node;
}

swUI32 SwRichTextInterface::Oncitation(swUI32 node)
{
    SwString buffer;

    if (GetNodeType(node) == NODE_TYPE_BEGIN_TAG)
    {
        if (GetNamedValueFromNode(node, "href", buffer))
        {

            if (m_markupType == MARKUP_THML)
                SwThMLCss::GetElementStyle(GetNodeElementIdentifier(node), m_attrList);
            else
                SwHtmlCss::GetElementStyle(GetNodeElementIdentifier(node), m_attrList);
            GetInlineStyle(node);

            buffer.Insert(0, "citation:");
            m_richAttr.SetURL(buffer.GetArray());
            m_richAttr.SetTextColour(*wxBLUE);
            m_richAttr.SetFontUnderlined(true);
            SetEndStyleFlag(node, BeginInlineStyle(true));
        }
    }
    else if (GetNodeType(node) == NODE_TYPE_END_TAG)
    {
        EndInlineStyle(node);
    }

    return node;
}

swUI32 SwRichTextInterface::Onsync(swUI32 node)
{
    SwString buffer;

    if (GetNodeType(node) == NODE_TYPE_UNPAIRED_TAG)
    {
        if (GetNamedValueFromNode(node, "value", buffer))
        {
            buffer.Insert(0, "strongs:");
            m_rich->BeginURL(buffer.GetArray());
            m_richAttr.SetTextColour(*wxBLUE);
            m_rich->WriteText(&buffer.GetArray()[8]);
            m_rich->EndURL();
        }
    }
    else if (GetNodeType(node) == NODE_TYPE_BEGIN_TAG)
    {
        if (GetNamedValueFromNode(node, "value", buffer))
        {
            buffer.Insert(0, "strongs:");
            m_rich->BeginURL(buffer.GetArray());
            m_richAttr.SetTextColour(*wxBLUE);
        }
    }
    else if (GetNodeType(node) == NODE_TYPE_END_TAG)
    {
        m_rich->EndURL();
    }

    return node;
}

swUI32 SwRichTextInterface::Onterm(swUI32 node)
{
    if (GetNodeType(node) == NODE_TYPE_BEGIN_TAG)
    {
        Paragraph();

        if (m_markupType == MARKUP_THML)
            SwThMLCss::GetElementStyle(GetNodeElementIdentifier(node), m_attrList);
        else
            SwHtmlCss::GetElementStyle(GetNodeElementIdentifier(node), m_attrList);
        GetBlockStyle(node);

        if (!m_richAttr.m_display)
        {
            return Onhide(node);
        }

        SetEndStyleFlag(node, BeginBlockStyle(node));
    }
    else if (GetNodeType(node) == NODE_TYPE_UNPAIRED_TAG)
    {
    }
    else if (GetNodeType(node) == NODE_TYPE_END_TAG)
    {
        EndBlockStyle(node);
    }

    return node;
}

swUI32 SwRichTextInterface::Ondef(swUI32 node)
{
    if (GetNodeType(node) == NODE_TYPE_BEGIN_TAG)
    {
        if (m_markupType == MARKUP_THML)
            SwThMLCss::GetElementStyle(GetNodeElementIdentifier(node), m_attrList);
        else
            SwHtmlCss::GetElementStyle(GetNodeElementIdentifier(node), m_attrList);
        GetBlockStyle(node);

        if (!m_richAttr.m_display)
        {
            return Onhide(node);
        }

        SetEndStyleFlag(node, BeginBlockStyle(node));
    }
    else if (GetNodeType(node) == NODE_TYPE_END_TAG)
    {
        EndBlockStyle(node);
    }

    return node;
}

swUI32 SwRichTextInterface::Ontitle(swUI32 node)
{
    swUI8 lastChar = LCH_BREAK;
    SwString buffer;

    if (GetNodeType(node) == NODE_TYPE_BEGIN_TAG)
    {
        m_title.Reset();

        if (GetInnerText(node, buffer))
        {
            m_title.Size(buffer.Strlen() + 1);
            SwHtml::Html2Text(buffer, m_title, m_title.GetSize(), lastChar, true);
        }
    }

    return node;
}

swUI32 SwRichTextInterface::Ondivn(swUI32 node)
{
    if (GetNodeType(node) == NODE_TYPE_BEGIN_TAG ||
            GetNodeType(node) == NODE_TYPE_UNPAIRED_TAG)
    {
        GetTitleBuffer().Reset();
        GetNamedValueFromNode(node, "title", GetTitleBuffer());
    }

    return node;
}

swUI32 SwRichTextInterface::Onfigure(swUI32 node)
{
    wxRichTextTable * table;
    wxRichTextCell * cell;
    SwString buffer;
    swUI32 id;

    if (GetNodeType(node) == NODE_TYPE_BEGIN_TAG)
    {
        id = FindWithInElement(node, 0, THML_IMG, NODE_TYPE_BEGIN_TAG);

        if (id == NODE_ID_INVALID)
        {
            id = FindWithInElement(node, 0, THML_IMG, NODE_TYPE_UNPAIRED_TAG);
        }

        if (id != NODE_ID_INVALID)
        {
            m_richAttr.GetCssAttributes().Add("height", "100%");
            m_richAttr.GetCssAttributes().Add("width", "100%");
            GetBlockStyle(node);
            table = m_rich->WriteTable(1, 1, m_richAttr, m_richAttr);
            cell = table->GetCell(0, 0);
            m_richAttr.SetHeight(CSS_ATTR_HEIGHT, "100%", false);
            m_richAttr.SetWidth(CSS_ATTR_WIDTH, "100%", false);
            cell->SetAttributes(m_richAttr);
            m_rich->SetFocusObject(cell);
        }
    }
    else if (GetNodeType(node) == NODE_TYPE_END_TAG)
    {
        m_rich->SetInsertionPointEnd();
    }

    return node;
}

swUI32 SwRichTextInterface::Onimg(swUI32 node)
{
    SwString src, path;
    SwStreamBuffer stream;
    bool canCopy;
    bool status;

    if (!GetNamedValueFromNode(node, "src", src) &&
            !GetNamedValueFromNode(node, "href", src))
        return node;

    if (m_isModule)
    {
        if (m_rich)
        {
            SwGetFileName(src, path);
            status = SwApplicationInterface::GetModuleManager().LoadMedia(m_moduleId, path, stream, canCopy);

            if (status)
            {
                wxMemoryInputStream wxstream(stream.GetArray(), stream.GetCount());
                wxImage theBitmap;
                if (theBitmap.LoadFile(wxstream, wxBITMAP_TYPE_ANY))
                    m_rich->WriteImage(theBitmap, theBitmap.GetType(), m_richAttr);
            }
        }
    }
    else
    {
        SwGetPathFromRelative(GetBasePath(), src, path);
        if (SwFile::DoesExist(path))
            m_rich->WriteImage(path.GetArray(), wxBITMAP_TYPE_ANY, m_richAttr);
    }

    return node;
}

swUI32 SwRichTextInterface::Onh1h6(swUI32 node)
{
    if (GetNodeType(node) == NODE_TYPE_BEGIN_TAG)
    {
        if (m_markupType == MARKUP_THML)
            SwThMLCss::GetElementStyle(GetNodeElementIdentifier(node), m_attrList);
        else
            SwHtmlCss::GetElementStyle(GetNodeElementIdentifier(node), m_attrList);
        GetBlockStyle(node);

        if (!m_richAttr.m_display)
        {
            return Onhide(node);
        }

        SetEndStyleFlag(node, BeginBlockStyle(node));
    }
    else if (GetNodeType(node) == NODE_TYPE_UNPAIRED_TAG)
    {
        Paragraph();
    }
    else if (GetNodeType(node) == NODE_TYPE_END_TAG)
    {
        Paragraph();
        EndBlockStyle(node);
    }

    return node;
}

swUI32 SwRichTextInterface::Onhr(swUI32 node)
{
    if (GetNodeType(node) == NODE_TYPE_BEGIN_TAG || GetNodeType(node) == NODE_TYPE_UNPAIRED_TAG)
    {
        if (m_markupType == MARKUP_THML)
            SwThMLCss::GetElementStyle(GetNodeElementIdentifier(node), m_attrList);
        else
            SwHtmlCss::GetElementStyle(GetNodeElementIdentifier(node), m_attrList);
        GetBlockStyle(node);

        m_rich->BeginStyle(m_richAttr);
        m_rich->WriteHorizontalRule(m_richAttr);
        Paragraph();
        m_rich->EndStyle();
    }

    return node;
}

swUI32 SwRichTextInterface::Onmeter(swUI32 node)
{
    if (IsThML())
    {
        if (GetNodeType(node) == NODE_TYPE_BEGIN_TAG)
        {
            if (m_markupType == MARKUP_THML)
                SwThMLCss::GetElementStyle(GetNodeElementIdentifier(node), m_attrList);
            else
                SwHtmlCss::GetElementStyle(GetNodeElementIdentifier(node), m_attrList);
            GetBlockStyle(node);
            SetEndStyleFlag(node, BeginBlockStyle(node));
        }
        else if (GetNodeType(node) == NODE_TYPE_END_TAG)
        {
            Paragraph();
            EndBlockStyle(node);
        }
    }

    return node;
}

swUI32 SwRichTextInterface::Onnote(swUI32 node)
{
    SwString buffer;
    swUI32 anchorId;
    wxRichTextAttr attr;

    if (GetNodeType(node) == NODE_TYPE_BEGIN_TAG)
    {
        m_richAttr.Copy(m_rich->GetBasicStyle());
        m_richAttr.SetHtmlAttributes(m_attrList, m_basefontsize, IsTableCell(GetNodeElementIdentifier(node)));

        if (GetNamedValueFromNode(node, "n", buffer))
        {
            anchorId = m_rich->GetAnchors().Find(buffer);

            if (anchorId != NODE_ID_INVALID)
            {
                buffer.Insert(0, "note:");
                m_rich->GetAnchors().SetAnchorTarget(anchorId, m_rich->GetInsertionPoint());
                //Paragraph();
                m_rich->BeginURL(buffer.GetArray());
                attr.SetFlags(wxTEXT_ATTR_EFFECTS);
                attr.SetTextColour(*wxBLUE);
                attr.SetTextEffectFlags(wxTEXT_ATTR_EFFECT_SUPERSCRIPT);
                attr.SetTextEffects(attr.GetTextEffects() | wxTEXT_ATTR_EFFECT_SUPERSCRIPT);
                m_rich->BeginStyle(attr);
                buffer += ' ';
                m_rich->WriteText(&buffer[5]);
                m_rich->EndStyle();
                m_rich->EndURL();
                SetEndStyleFlag(node, BeginBlockStyle(node));
            }
        }
    }
    else if (GetNodeType(node) == NODE_TYPE_UNPAIRED_TAG)
    {
        if (GetNamedValueFromNode(node, "n", buffer))
        {
            m_rich->GetAnchors().Add(buffer, m_rich->GetInsertionPoint(), m_rich->GetInsertionPoint() + buffer.Strlen());
            buffer.Insert(0, "anchor:");
            m_rich->BeginURL(buffer.GetArray());
            attr.SetFlags(wxTEXT_ATTR_EFFECTS);
            attr.SetTextColour(*wxBLUE);
            attr.SetTextEffectFlags(wxTEXT_ATTR_EFFECT_SUPERSCRIPT);
            attr.SetTextEffects(attr.GetTextEffects() | wxTEXT_ATTR_EFFECT_SUPERSCRIPT);
            m_rich->BeginStyle(attr);
            m_rich->WriteText(&buffer[7]);
            m_rich->EndStyle();
            m_rich->EndURL();
        }
    }
    else if (GetNodeType(node) == NODE_TYPE_END_TAG)
    {
        EndBlockStyle(node);
    }

    return node;
}

swUI32 SwRichTextInterface::Onq(swUI32 node)
{
    if (m_rich)
        m_rich->WriteText("\"");

    return node;
}

swUI32 SwRichTextInterface::Onpre(swUI32 node)
{
    if (GetNodeType(node) == NODE_TYPE_BEGIN_TAG)
    {
        if (m_markupType == MARKUP_THML)
            SwThMLCss::GetElementStyle(GetNodeElementIdentifier(node), m_attrList);
        else
            SwHtmlCss::GetElementStyle(GetNodeElementIdentifier(node), m_attrList);
        GetBlockStyle(node);

        if (!m_richAttr.m_display)
        {
            return Onhide(node);
        }

        SetEndStyleFlag(node, BeginBlockStyle(node));
        m_pre = true;
    }
    else if (GetNodeType(node) == NODE_TYPE_END_TAG)
    {
        m_pre = false;
        EndBlockStyle(node);
    }

    return node;
}

swUI32 SwRichTextInterface::Onscripref(swUI32 node)
{
    SwString buffer, version;

    if (GetNodeType(node) == NODE_TYPE_BEGIN_TAG)
    {
        if (GetNamedValueFromNode(node, "passage", buffer))
        {
            buffer.Insert(0, "scripref:");

            if (GetNamedValueFromNode(node, "version", version))
            {
                buffer += " version:";
                buffer += version;
            }

            GetInlineStyle(node);
            m_richAttr.SetURL(buffer.GetArray());
            m_richAttr.SetFontUnderlined(true);

            SetEndStyleFlag(node, BeginInlineStyle(node, true));
        }
    }
    else if (GetNodeType(node) == NODE_TYPE_END_TAG)
    {
        EndInlineStyle(node);
    }

    return node;
}

swUI32 SwRichTextInterface::Onhtml(swUI32 node)
{
    if (GetNodeType(node) == NODE_TYPE_BEGIN_TAG)
    {
        SetMarkupType(MARKUP_HTML);
        SetThML_ElementArray();
    }

    return node;
}

swUI32 SwRichTextInterface::Onthml(swUI32 node)
{
    if (GetNodeType(node) == NODE_TYPE_BEGIN_TAG)
    {
        SetMarkupType(MARKUP_THML);
        SetThML_ElementArray();
    }

    return node;
}
