#ifndef STSERIALIZER_H
#define STSERIALIZER_H

#include "STNode.h"

#include <ostream>

namespace mathscript {

    //! Dump the contents of the AST to the output stream.
    void SerializeST(STNode& node, std::ostream& os);

    //! Dump the contents of the AST to a string.
    std::string SerializeST(STNode& node);

}

#endif // STSERIALIZER_H
