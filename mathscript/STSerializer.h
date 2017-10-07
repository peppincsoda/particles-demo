#ifndef STSERIALIZER_H
#define STSERIALIZER_H

#include "STNode.h"

#include <ostream>

namespace mathscript {

    void SerializeST(STNode& node, std::ostream& os);

    std::string SerializeST(STNode& node);

}

#endif // STSERIALIZER_H
