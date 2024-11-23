/**
 * Copyright (c) p-it
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "fileresource.h"
#include <filesystem>
#include <iostream>
#include <fstream>

FileResource::FileResource(std::string path)
{
    this->path = path;
}

void FileResource::read()
{
    std::ifstream file { path, std::ios::binary };
    if (!file.good()) {
        throw "File with path: " + path + " could not be read!";
    }

    auto length { std::filesystem::file_size(path) };
    data = std::vector<std::byte>(length);
    file.read( reinterpret_cast<char*>(data.data()), static_cast<long>(length));
}

void FileResource::clearData()
{
    data.clear();
}

std::vector<std::byte> FileResource::getData()
{
    return data;
}

FileResource::~FileResource()
{
    data.clear();
}
