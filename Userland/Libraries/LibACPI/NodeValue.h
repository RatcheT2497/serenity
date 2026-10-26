
#pragma once
#include "Definitions.h"
#include "NameString.h"
#include <AK/String.h>
#include <AK/Types.h>
#include <AK/Variant.h>

namespace ACPI {

class Node;

enum class NodeValueType : u8 {
    None,
    Integer,
    String,
    Buffer,
    Package,
    NameString,
    Argument,
    Local,
    DebugObject
};

class NodeValue;
// FIXME: Clean up whatever this is.
union NodeValueData {
protected:
    union Data {
        Local as_local;
        Argument as_argument;
        u64 as_integer;

        ByteBuffer as_buffer;
        Vector<NodeValue> as_package;

        Data(Local local) : as_local(local) {}
        Data(Argument argument) : as_argument(argument) {}
        Data(u64 integer) : as_integer(integer) {}
        Data(ByteBuffer const& buffer) : as_buffer(buffer) {}
        Data(Vector<NodeValue> const& package) : as_package(package) {}
        ~Data() {}
    };

public:
    NodeValueData(Local local) : m_data(local) {}
    NodeValueData(Argument argument) : m_data(argument) {}
    NodeValueData(ByteBuffer const& buffer) : m_data(buffer) {}
    NodeValueData(Vector<NodeValue> const& package) : m_data(package) {}
    NodeValueData(u64 integer) : m_data(integer) {}

    NodeValueData() {}
    NodeValueData(NodeValueData &&v) {
        memcpy(as_inner_data, v.as_inner_data, sizeof(NodeValueData));
    }
    ~NodeValueData() {}

    Data m_data;
    u8 as_inner_data[sizeof(Data)];
};

class NodeValue {
public:
    static NodeValue from_integer(u64 value);
    static NodeValue from_buffer(ByteBuffer const& value);
    static NodeValue from_string(ByteBuffer const& value);
    static NodeValue from_package(Vector<NodeValue> const& value);
    static ErrorOr<NodeValue> from_namestring(NameString const& value);
    static NodeValue from_local(Local value);
    static NodeValue from_argument(Argument value);
    static NodeValue make_debug();

    NodeValue() {}
    NodeValue(NodeValue &value) {
        m_type = value.m_type;
        memcpy(m_data.as_inner_data, value.m_data.as_inner_data, sizeof(NodeValueData));
    }
    NodeValue(NodeValue &&value) {
        m_type = value.m_type;
        memcpy(m_data.as_inner_data, value.m_data.as_inner_data, sizeof(NodeValueData));
    }

    NodeValueType type() const { return m_type; }
    ErrorOr<NameString> as_namestring();
    ErrorOr<u64> as_integer();
    ErrorOr<StringView> as_string_view();
    ErrorOr<ByteBuffer> as_string_raw();
    ErrorOr<Argument> as_argument();
    ErrorOr<Local> as_local();
    ErrorOr<ByteBuffer> as_buffer();

protected:
    NodeValue(NodeValueType type) : m_type(type) {}
    NodeValue(NodeValueType type, Local local) : m_type(type), m_data(local) {}
    NodeValue(NodeValueType type, Argument argument) : m_type(type), m_data(argument) {}
    NodeValue(NodeValueType type, ByteBuffer const& buffer) : m_type(type), m_data(buffer) {}
    NodeValue(NodeValueType type, Vector<NodeValue> const& package) : m_type(type), m_data(package) {}
    NodeValue(NodeValueType type, u64 qword) : m_type(type), m_data(qword) {}

    NodeValueType m_type { NodeValueType::None };
    NodeValueData m_data;
    NameString m_namestring_metadata;
};

}
