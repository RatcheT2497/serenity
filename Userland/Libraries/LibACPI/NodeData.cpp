/*
 * Copyright (c) 2025, RatcheT2497 <ratchetnumbers@proton.me>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include "NodeData.h"

namespace ACPI {
NodeData NodeData::from_integer(u64 value)
{
    return NodeData(Type::Integer, value);
}

NodeData NodeData::from_buffer(Buffer value)
{
    return NodeData(Type::Buffer, value);
}

NodeData NodeData::from_string(ByteBuffer value)
{
    return NodeData(Type::String, value);
}

NodeData NodeData::from_package(Vector<NodeData> value)
{
    return NodeData(Type::Package, value);
}

NodeData NodeData::from_namestring(NameString value)
{
    return NodeData (Type::NameString, value);
}

NodeData NodeData::from_local(Local value)
{
    return NodeData(Type::Local, value);
}

NodeData NodeData::from_argument(Argument value)
{
    return NodeData(Type::Argument, value);
}

NodeData NodeData::make_debug()
{
    return NodeData(Type::DebugObject);
}

ErrorOr<u64> NodeData::as_integer()
{
    switch (m_type) {
    case NodeData::Type::Integer:
        return m_data.get<u64>();
    default:
        return Error::from_string_view_or_print_error_and_return_errno("Can not cast given type to integer!"sv, EINVAL);
    }
}

ErrorOr<Buffer*> NodeData::as_buffer_ptr()
{
    if (m_type == NodeData::Type::Buffer)
        return m_data.get_pointer<Buffer>();
    return Error::from_string_view_or_print_error_and_return_errno("Can not cast given type to buffer!"sv, EINVAL);
}

ErrorOr<NameString> NodeData::as_namestring()
{
    if (m_type == NodeData::Type::NameString)
        return m_data.get<NameString>();
    return Error::from_string_view_or_print_error_and_return_errno("Can not cast given type to namestring!"sv, EINVAL);
}

ErrorOr<ByteBuffer> NodeData::as_string_raw()
{
    if (m_type == NodeData::Type::String)
        return m_data.get<ByteBuffer>();
    return Error::from_string_view_or_print_error_and_return_errno("Can not cast given type to string!"sv, EINVAL);
}

ErrorOr<StringView> NodeData::as_string_view()
{
    if (m_type != NodeData::Type::String)
        return Error::from_string_view_or_print_error_and_return_errno("Can not cast given type to string!"sv, EINVAL);

    auto &buffer = m_data.get<ByteBuffer>();
    return StringView(buffer.bytes());
}

ErrorOr<Argument> NodeData::as_argument()
{
    if (m_type != NodeData::Type::Argument)
        return Error::from_string_view_or_print_error_and_return_errno("Can not cast given type to argument!"sv, EINVAL);

    return m_data.get<Argument>();
}

ErrorOr<Local> NodeData::as_local()
{
    if (m_type != NodeData::Type::Local)
        return Error::from_string_view_or_print_error_and_return_errno("Can not cast given type to local!"sv, EINVAL);

    return m_data.get<Local>();
}

ErrorOr<void> NodeData::store(NodeData &source)
{
    if (m_type == Type::Integer)
    {
        auto value = TRY(source.as_integer());
        dbgln("[LibACPI] value to write: {}", value);
        m_data.set(value);
        return {};
    }
    return Error::from_string_view_or_print_error_and_return_errno("Invalid source/target combination for store operation!"sv, EINVAL);
}

ErrorOr<void> NodeData::copy_object(NodeData &source)
{
    (void) source;
    return {};
}

}
