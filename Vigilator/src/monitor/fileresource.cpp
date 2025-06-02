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
#include <qDebug>
#include <qfile.h>

FileResource::FileResource(std::string path)
{
    this->path = path;
}

void FileResource::read()
{
    QFile dfile(QString::fromStdString(path));
    if (dfile.exists())
    {
        dfile.open(QIODevice::ReadOnly);
        auto length { dfile.size() };
        data = std::vector<std::byte>(length);
        dfile.read( reinterpret_cast<char*>(data.data()), static_cast<long>(length));
    } else {
       throw path + " does not exist";
    }
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
