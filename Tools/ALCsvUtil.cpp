//
//  ALCsvUtil.cpp
//  GameTest-mobile
//
//  Created by Allen on 2018/7/2.
//

#include "ALCsvUtil.h"


ALCsvUtil* ALCsvUtil::_gInstance;

ALCsvUtil::ALCsvUtil():_pCsvMap(nullptr)
{
    _pCsvMap = new CsvMap();
}

ALCsvUtil::~ALCsvUtil()
{
    CC_SAFE_DELETE(_pCsvMap);
}

ALCsvUtil* ALCsvUtil::getInstance()
{
    if (!_gInstance) {
        _gInstance = new ALCsvUtil();
    }
    return _gInstance;
}

void ALCsvUtil::destroyInstance()
{
    if (_gInstance) {
        CC_SAFE_DELETE(_gInstance);
    }
}

bool ALCsvUtil::addFileData(const std::string &rSCsvFilePath)
{
    if (std::string("") == rSCsvFilePath) return false;
    
    
    if (!cocos2d::FileUtils::getInstance()->isFileExist(rSCsvFilePath)) {
        CCLOG("ALCsvUtil::addFileData():  %s file could not be found",rSCsvFilePath.c_str());
        return false;
    }
    cocos2d::Data csvData = cocos2d::FileUtils::getInstance()->getDataFromFile(rSCsvFilePath);
    if (!csvData.getBytes()) {
        CCLOG("ALCsvUtil::addFileData():  %s file is null",rSCsvFilePath.c_str());
        return false;
    }
    StrVec linesVec = split((char*)csvData.getBytes(), '\n');
    StrVec strsVec;
    StrDict dict;
    for (const auto &linesVecIter :linesVec) {
        std::string lineStr(linesVecIter);
        if (lineStr[lineStr.length() - 1] == '\r') {
            lineStr = lineStr.substr(0,lineStr.length() - 1);
        }
        strsVec = split(lineStr, ',');
        dict.push_back(strsVec);
    }
    _pCsvMap->insert(std::make_pair(std::string(rSCsvFilePath), dict));
    return true;
}

void ALCsvUtil::releaseFile(const std::string &rSCsvFilePath)
{
    _pCsvMap->erase(rSCsvFilePath);
}

std::tuple<int,int> ALCsvUtil::getFileRowColNum(const std::string &rSCsvFilePath)
{
    auto dict = getFileDict(rSCsvFilePath);
    int rowNum = (int) dict.size();
    int colNum = (int) (*(dict.begin())).size();
    return std::make_tuple(colNum,rowNum-1);
}

std::string ALCsvUtil::getText(const int &rRow, const int &rCol, const std::string &rSCsvFilePath)
{
    const auto dict = getFileDict(rSCsvFilePath);
    CCASSERT(rRow < dict.size() && rCol < dict.at(rRow).size(), "ALCsvUtil: (row or col) out of range in getObjectAtIndex() ");
    return dict.at(rRow).at(rCol);
}

int ALCsvUtil::getInt(const int &rRow, const int &rCol, const std::string &rSCsvFilePath)
{
    return atoi(getText(rRow, rCol, rSCsvFilePath).c_str());
}

double ALCsvUtil::getDouble(const int &rRow, const int &rCol, const std::string &rSCsvFilePath)
{
    return atof(getText(rRow, rCol, rSCsvFilePath).c_str());
}

StrVec ALCsvUtil::getRowData(const int &rIRow, const std::string &rSCsvFilePath)
{
    auto tRow = std::get<1>(getFileRowColNum(rSCsvFilePath));
    
    if(rIRow > tRow) return StrVec();
    
    return  _pCsvMap->at(rSCsvFilePath).at(rIRow);
}

StrDict &ALCsvUtil::getFileDict(const std::string &rSCsvFilePath)
{
    CCASSERT((_pCsvMap->end() != _pCsvMap->find(rSCsvFilePath) || addFileData(rSCsvFilePath)),"ALCsvUtil: load csvFile file");
    return _pCsvMap->at(rSCsvFilePath);
}

int ALCsvUtil::findValueInWithLine(const std::string &rSValue, const int &rIValueCol, const std::string &rSCsvFilePath)
{
    auto iRowCount = std::get<1>(getFileRowColNum(rSCsvFilePath));
    
    auto ret = -1;
    std::string findValue(rSValue);
    
    for (int iRow = 0; iRow < iRowCount; ++iRow)
    {
        std::string tmpValue = getText(iRow, rIValueCol, rSCsvFilePath);
        if (findValue == tmpValue)
        {
            ret = iRow;
            break;
        }
    }
    return ret;
}

StrVec ALCsvUtil::split(const std::string &rSSrcStr, const char &rSSep)
{
    StrVec strList;
    
    std::string::size_type lastIndex = rSSrcStr.find_first_not_of(rSSep,0);
    std::string::size_type currentIndex = rSSrcStr.find_first_of(rSSep,lastIndex);
    while (std::string::npos != currentIndex || std::string::npos != lastIndex)
    {
        strList.push_back(rSSrcStr.substr(lastIndex,currentIndex - lastIndex));
        lastIndex = rSSrcStr.find_first_not_of(rSSep,currentIndex);
        currentIndex = rSSrcStr.find_first_of(rSSep,lastIndex);
    }
    
    return strList;
}
