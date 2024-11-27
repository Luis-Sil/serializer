// Serializer.cpp : Defines the exported functions for the DLL.
//

#include "serializer.h"
#include "XMLProcessor.h"

#include <sstream>
#include <string>

std::stringstream CSerializer::LoadFromFile(const std::string& path, FileType file_type)
{
    //path must not be empty
    if (path.empty())
        return std::stringstream{};

    std::stringstream object_stream{};

    switch (file_type)
    {
    case FileType::XML:
        XMLLoader::LoadFromXML(path, object_stream);
        break;
    case FileType::JSON:
        break;
    default:
        throw std::invalid_argument("Unknown file type.");
        break;
    }

    return object_stream;
}

void CSerializer::SaveToFile(const std::string& path, const std::stringstream& object_stream, FileType file_type) const
{
    //choose saving method according to file type
    switch (file_type)
    {
    case FileType::XML:
        XMLLoader::SaveToXML(path, object_stream);
        break;
    default:
        throw std::invalid_argument("Unknown file type.");
        break;
    }
}
