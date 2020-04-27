#include "edesignrules.h"

EDesignRules* EDesignRules::pInstance = nullptr;

EDesignRules* EDesignRules::instance()
{
    if (pInstance == nullptr)
        pInstance = new EDesignRules;
    return pInstance;
}

EDesignRules::EDesignRules()
{
    valid = false;
}

bool EDesignRules::parse(QDomElement element)
{
    valid = false;

    if (element.nodeName() == "designrules") {
        this->name = element.attribute("name");

        QDomElement paramElement = element.firstChildElement("param");
        while (!paramElement.isNull()) {
            QString stParamName = paramElement.attribute("name");
            QString stParamValue = paramElement.attribute("value");

            if (stParamName == "rvViaOuter") {
                bool valueParseResult;
                double value = stParamValue.toDouble(&valueParseResult);
                if (valueParseResult)
                    this->rvViaOuter = value;
            } else if (stParamName == "rlMinViaOuter") {
                bool valueParseResult;
                double value = convertSizeTextToMilimeters(stParamValue, &valueParseResult);
                if (valueParseResult)
                    this->rlMinViaOuter = value;
            } else if (stParamName == "rlMaxViaOuter") {
                bool valueParseResult;
                double value = convertSizeTextToMilimeters(stParamValue, &valueParseResult);
                if (valueParseResult)
                    this->rlMaxViaOuter = value;
            } else if (stParamName == "rvViaInner") {
                bool valueParseResult;
                double value = stParamValue.toDouble(&valueParseResult);
                if (valueParseResult)
                    this->rvViaInner = value;
            } else if (stParamName == "rlMinViaInner") {
                bool valueParseResult;
                double value = convertSizeTextToMilimeters(stParamValue, &valueParseResult);
                if (valueParseResult)
                    this->rlMinViaInner = value;
            } else if (stParamName == "rlMaxViaInner") {
                bool valueParseResult;
                double value = convertSizeTextToMilimeters(stParamValue, &valueParseResult);
                if (valueParseResult)
                    this->rlMaxViaInner = value;
            } else if (stParamName == "rvPadTop") {
                bool valueParseResult;
                double value = stParamValue.toDouble(&valueParseResult);
                if (valueParseResult)
                    this->rvPadTop = value;
            } else if (stParamName == "rvPadInner") {
                bool valueParseResult;
                double value = stParamValue.toDouble(&valueParseResult);
                if (valueParseResult)
                    this->rvPadInner = value;
            } else if (stParamName == "rvPadBottom") {
                bool valueParseResult;
                double value = stParamValue.toDouble(&valueParseResult);
                if (valueParseResult)
                    this->rvPadBottom = value;
            } else if (stParamName == "rlMinPadTop") {
                bool valueParseResult;
                double value = convertSizeTextToMilimeters(stParamValue, &valueParseResult);
                if (valueParseResult)
                    this->rlMinPadTop = value;
            } else if (stParamName == "rlMaxPadTop") {
                bool valueParseResult;
                double value = convertSizeTextToMilimeters(stParamValue, &valueParseResult);
                if (valueParseResult)
                    this->rlMaxPadTop = value;
            } else if (stParamName == "rlMinPadInner") {
                bool valueParseResult;
                double value = convertSizeTextToMilimeters(stParamValue, &valueParseResult);
                if (valueParseResult)
                    this->rlMinPadInner = value;
            } else if (stParamName == "rlMaxPadInner") {
                bool valueParseResult;
                double value = convertSizeTextToMilimeters(stParamValue, &valueParseResult);
                if (valueParseResult)
                    this->rlMaxPadInner = value;
            } else if (stParamName == "rlMinPadBottom") {
                bool valueParseResult;
                double value = convertSizeTextToMilimeters(stParamValue, &valueParseResult);
                if (valueParseResult)
                    this->rlMinPadBottom = value;
            } else if (stParamName == "rlMaxPadBottom") {
                bool valueParseResult;
                double value = convertSizeTextToMilimeters(stParamValue, &valueParseResult);
                if (valueParseResult)
                    this->rlMaxPadBottom = value;
            }

            paramElement = paramElement.nextSiblingElement("param");
        }

        valid = true;
    }

    return valid;
}
