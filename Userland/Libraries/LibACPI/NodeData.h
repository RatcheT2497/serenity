/*
 * Copyright (c) 2025, RatcheT2497 <ratchetnumbers@proton.me>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include "Definitions.h"
#include "NameString.h"
#include <AK/String.h>
#include <AK/Types.h>
#include <AK/Variant.h>
#include <LibWeb/HTML/TagNames.h>

namespace ACPI {

class Buffer {
public:
    Buffer(ByteBuffer buffer)
        : m_buffer(move(buffer))
    {
    }

    ByteBuffer& buffer() { return m_buffer; }

protected:
    ByteBuffer m_buffer;
};

/*
 * CopyObject(src: NodeData, target: NodeData) {
 *     switch target.type {
 *         case LocalX:  Overwrite LocalX.
 *         case NAME:    Overwrite NAME.
 *         case ArgX:    Overwrite ArgX unless ArgX is a reference, in which case overwrite the referenced object.
 *         case IndexOf: Overwrite object stored at index.
 *
 *         case RefOf: 
 *         default: 
 *             Not allowed.
 *     }
 * }
 */
class Node;
class NodeData {
public:
    using DataVariant = Variant<Local, Argument, NameString, ByteBuffer, u64, Buffer, Vector<NodeData>>;
    enum class Type : u8 {
        None,
        Integer, // Name
        String, // Name
        Buffer, // Name
        Package, // Name
        NameString,
        Argument,
        Local,
        DebugObject
    };

    static NodeData from_integer(u64 value);
    static NodeData from_buffer(Buffer value);
    static NodeData from_string(ByteBuffer value);
    static NodeData from_package(Vector<NodeData> value);
    static NodeData from_namestring(NameString value);
    static NodeData from_local(Local value);
    static NodeData from_argument(Argument value);
    static NodeData make_debug();

    NodeData()
        : m_type(Type::None)
        , m_data(0)
    {
    }

    Type type() const { return m_type; }

    ErrorOr<NameString> as_namestring();
    ErrorOr<u64> as_integer();
    ErrorOr<StringView> as_string_view();
    ErrorOr<ByteBuffer> as_string_raw();
    ErrorOr<Argument> as_argument();
    ErrorOr<Local> as_local();
    ErrorOr<Buffer*> as_buffer_ptr();

    ErrorOr<void> store(NodeData &source);
    ErrorOr<void> copy_object(NodeData &source);

protected:
    using InnerData = Variant<Local, Argument, u64, NameString, Buffer, ByteBuffer, Vector<NodeData>>;
    NodeData(Type type)
        : m_type(type)
        , m_data(0)
    {
    }

    Type m_type { Type::None };
    InnerData m_data;

    NodeData(Type type, InnerData data) : m_type(type), m_data(data) {}
};

}
