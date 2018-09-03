//
//  ALCsvUtil.h
//  GameTest-mobile
//
//  Created by Allen on 2018/7/2.
//

/**
 *  CSV 解析工具
 */
#ifndef ALCsvUtil_h
#define ALCsvUtil_h

#include <vector>
#include <map>
#include <string>

typedef std::vector<std::string> StrVec;

typedef std::vector< StrVec > StrDict;

typedef std::map< std::string, StrDict> CsvMap;



class ALCsvUtil
{
public:
    static ALCsvUtil* getInstance();
    
    static void destroyInstance();
    
    /**
     *  add csv file to dict
     *
     *  @param sPath is csv file path
     */
    virtual bool addFileData(const std::string &rSCsvFilePath);
    
    /**
     *  del csv file to dict
     *
     *  @param sPath is csv file path
     */
    virtual void releaseFile(const std::string &rSCsvFilePath);
    
    /**
     *  get some row and some column value from some csv file
     *
     *  @param rRow        is row num
     *  @param rCol        is column num
     *  @param csvFilePath is some csv file
     *
     *  @return some row and some column real TextValue IntValue, DoubleValue,if this pos not be exsit return ""
     */
    virtual std::string getText(const int &rRow, const int &rCol, const std::string &rSCsvFilePath);
    virtual int getInt(const int &rRow, const int &rCol, const std::string &rSCsvFilePath);
    virtual double getDouble(const int &rRow, const int &rCol, const std::string &rSCsvFilePath);
    
    /**
     *  get some file row data
     *
     *  @param iRow          is row num
     *  @param rSCsvFilePath is some csv file
     *
     *  @return some row data
     */
    virtual StrVec getRowData(const int &rIRow, const std::string &rSCsvFilePath);
    
    /**
     *  get csv file row and column save tuple<int, int>
     *
     *  @param rSCsvFilePath csv file path
     *
     *  @return csv file row, column in tuple<int, int>
     */
    virtual std::tuple<int, int> getFileRowColNum(const std::string &rSCsvFilePath);
    
    /**
     *  find dest value in csv file row num
     *
     *  @param rSValue       find value
     *  @param rIValueCol    value column
     *  @param rSCsvFilePath csv file path
     *
     *  @return value in csv row
     */
    virtual int findValueInWithLine(const std::string &rSValue, const int &rIValueCol, const std::string &rSCsvFilePath);
    
    
protected:
    /**
     *  get csv file string vec
     *
     *  @param rSCsvFilePath csv file path
     *
     *  @return csv file strVec
     */
    virtual StrDict &getFileDict(const std::string &rSCsvFilePath);
    
    virtual ~ALCsvUtil();
    
    /**
     *  get csv file string vec
     *
     *  @param rSCsvFilePath csv file path
     *
     *  @return csv file strVec
     */
    /**
     get string vec by split

     @param rSSrcStr content
     @param rSSep  Seperator
     @return std::vector<std::string>
     */
    StrVec split(const std::string &rSSrcStr, const char &rSSep);
    
    
private:
    ALCsvUtil();
    
    ALCsvUtil(const ALCsvUtil &rCsvUtil) = delete;
    
    ALCsvUtil &operator=(const ALCsvUtil &rCsvUtil) = delete;
    
    
private:
    static ALCsvUtil* _gInstance;
    
    CsvMap* _pCsvMap;
};



#endif /* ALCsvUtil_h */
