#pragma once

#include <string>
#include <sstream>

namespace XMLLoader
{
    /// <summary>
    /// Loads an object stream from a xml file. The stringstream represents the serialization of an object.
    /// </summary>
    /// <param name="path">Loading file path</param>
    /// <param name="fieldData">Stream representing the object to be loaded</param>
    void LoadFromXML(const std::string &path, std::stringstream &fieldData);

    /// <summary>
    /// Saves an object stream to a xml file. 
    /// </summary>
    /// <param name="path">Saving file path</param>
    /// <param name="fieldData">Stream representing the object to be saved</param>
    void SaveToXML(const std::string &path, const std::stringstream &fieldData);
}