import gdb
import json


def isRawPointer(value):
    t = "{}".format(value.type)
    # handle pointer of stl container
    if t.startswith("std::") and t.endswith("::pointer"):
        return True
    return value.type.code == gdb.TYPE_CODE_PTR


def handleRawPointer(pointer):
    rawPointerMap = {}
    rawPointerMap["_gdb_address"] = "{}".format(pointer)
    try:
        value = pointer.dereference()
        value = value.fetch_lazy()
        value = handle(value)
        rawPointerMap["_gdb_dereference"] = value
    except Exception:
        rawPointerMap["_gdb_dereference"] = None
    return rawPointerMap


def isStructOrUnion(value):
    code = value.type.code
    return (code == gdb.TYPE_CODE_STRUCT or code == gdb.TYPE_CODE_UNION)


def handleStructOrUnion(instance):
    instanceMap = {}
    for key in instance.type.keys():
        value = instance[key]
        value = handle(value)
        key = "{}".format(key)
        instanceMap[key] = value
    return instanceMap


def isStlVector(gdbValue):
    try:
        return gdbValue.type.tag.startswith("std::vector")
    except Exception:
        return False


def handleStlVector(gdbValue):
    start = gdbValue["_M_impl"]["_M_start"]
    end = gdbValue["_M_impl"]["_M_finish"]
    size = end - start
    vectorMap = {}
    vectorMap["_gdb_vectorSize"] = int(size)
    vectorList = []
    for i in range(size):
        vectorList.append(handle((start + i).dereference()))
    vectorMap["_gdb_vectorList"] = vectorList
    return vectorMap


def isStlList(value):
    pass


def handleStlList(value):
    pass


def handle(gdbValue):
    m = {}
    if isRawPointer(gdbValue):
        m = handleRawPointer(gdbValue)
    elif isStlVector(gdbValue):
        m = handleStlVector(gdbValue)
    elif isStructOrUnion(gdbValue):
        m = handleStructOrUnion(gdbValue)
    else:
        m["_gdb_value"] = "{}".format(gdbValue)
    m["_gdb_type"] = "{}".format(gdbValue.type)
    return m


def gdbPrettyPrint(gdbValue):
    print(json.dumps(handle(gdbValue), indent=2))
