#ifndef __SERIALIZER_H__
#define __SERIALIZER_H__

#include <string>
#include <sstream>

/**
* Serializer class: writes a stringstream object in a file. The stringstream is not arbitrary and must follow certain rules.
* Currently, the only accepted file type is xml.
* 
* -classes streams begin and end with the same identifier, which must follow the pattern cx..x{...}cx..x
* -vector streams (1D) begin and end with the same identifier v{...}v
* -vector streams (2D) begin and end with the same identifier v_v{...}v_v
* -scalars don't need any identifier.
*
*/
enum class FileType
{
    XML = 0,
    JSON = 1,
    CSV = 2,
    BIN = 3
};


// This class is exported from the dll
class CSerializer
{
public:
    std::stringstream LoadFromFile(const std::string &path, FileType file_type = FileType::XML);
    void SaveToFile(const std::string &path, const std::stringstream &object_stream, FileType file_type = FileType::XML) const;
};

#endif