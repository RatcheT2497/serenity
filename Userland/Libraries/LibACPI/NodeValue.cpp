/*
 * Copyright (c) 2025, RatcheT2497 <ratchetnumbers@proton.me>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include "NodeValue.h"

namespace ACPI {

NodeValue NodeValue::from_integer(u64 value)
{
    return NodeValue(NodeValueType::Integer, value);
}

NodeValue NodeValue::from_buffer(ByteBuffer const& value)
{
    return NodeValue(NodeValueType::Buffer, value);
}

NodeValue NodeValue::from_string(ByteBuffer const& value)
{
    return NodeValue(NodeValueType::String, value);
}

NodeValue NodeValue::from_package(Vector<NodeValue> const& value)
{
    return NodeValue(NodeValueType::Package, value);
}

ErrorOr<NodeValue> NodeValue::from_namestring(NameString const& value)
{
    ByteBuffer buffer;
    TRY(buffer.try_resize(4 + ((value.count() - 1) * 5)));

    NameString cloned = value.clone(buffer);
    NodeValue cloned_value(NodeValueType::NameString, buffer);
    cloned_value.m_namestring_metadata = cloned;
    return cloned_value;
}

NodeValue NodeValue::from_local(Local value)
{
    return NodeValue(NodeValueType::Local, value);
}

NodeValue NodeValue::from_argument(Argument value)
{
    return NodeValue(NodeValueType::Argument, value);
}

NodeValue NodeValue::make_debug()
{
    return NodeValue(NodeValueType::DebugObject);
}

ErrorOr<u64> NodeValue::as_integer()
{
    switch (m_type) {
    case NodeValueType::Integer:
        return m_data.m_data.as_integer;
    default:
        return Error::from_string_view_or_print_error_and_return_errno("Can not cast given type to integer!"sv, EINVAL);
    }
}

ErrorOr<ByteBuffer> NodeValue::as_buffer()
{
    if (m_type == NodeValueType::Buffer)
        return m_data.m_buffer;
    return Error::from_string_view_or_print_error_and_return_errno("Can not cast given type to buffer!"sv, EINVAL);
}

ErrorOr<NameString> NodeValue::as_namestring()
{
    if (m_type == NodeValueType::NameString)
        return m_data.m_namestring;
    return Error::from_string_view_or_print_error_and_return_errno("Can not cast given type to namestring!"sv, EINVAL);
}

ErrorOr<ByteBuffer> NodeValue::as_string_raw()
{
    if (m_type == NodeValueType::String)
        return m_data.m_buffer;
    return Error::from_string_view_or_print_error_and_return_errno("Can not cast given type to string!"sv, EINVAL);

}
ErrorOr<StringView> NodeValue::as_string_view()
{
    if (m_type != NodeValueType::String)
        return Error::from_string_view_or_print_error_and_return_errno("Can not cast given type to string!"sv, EINVAL);

    auto &buffer = m_data.m_buffer;
    return StringView(buffer.bytes());
}

ErrorOr<Argument> NodeValue::as_argument()
{
    if (m_type != NodeValueType::Argument)
        return Error::from_string_view_or_print_error_and_return_errno("Can not cast given type to argument!"sv, EINVAL);

    return m_data.m_argument;
}

ErrorOr<Local> NodeValue::as_local()
{
    if (m_type != NodeValueType::Local)
        return Error::from_string_view_or_print_error_and_return_errno("Can not cast given type to local!"sv, EINVAL);

    return m_data.m_local;
}

}
