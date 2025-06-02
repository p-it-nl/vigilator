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
#ifndef FILERESOURCE_H
#define FILERESOURCE_H

#include "resource.h"
#include <string>

class FileResource: public Resource
{
    std::string path;

protected:
    FileResource(std::string path);

    std::vector<std::byte> data;

    void read();

public:
    virtual ~FileResource();

    void clearData();
    std::vector<std::byte> getData();
};

#endif // FILERESOURCE_H
