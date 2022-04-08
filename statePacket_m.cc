//
// Generated file, do not edit! Created by nedtool 5.4 from statePacket.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wshadow"
#  pragma clang diagnostic ignored "-Wconversion"
#  pragma clang diagnostic ignored "-Wunused-parameter"
#  pragma clang diagnostic ignored "-Wc++98-compat"
#  pragma clang diagnostic ignored "-Wunreachable-code-break"
#  pragma clang diagnostic ignored "-Wold-style-cast"
#elif defined(__GNUC__)
#  pragma GCC diagnostic ignored "-Wshadow"
#  pragma GCC diagnostic ignored "-Wconversion"
#  pragma GCC diagnostic ignored "-Wunused-parameter"
#  pragma GCC diagnostic ignored "-Wold-style-cast"
#  pragma GCC diagnostic ignored "-Wsuggest-attribute=noreturn"
#  pragma GCC diagnostic ignored "-Wfloat-conversion"
#endif

#include <iostream>
#include <sstream>
#include "statePacket_m.h"

namespace omnetpp {

// Template pack/unpack rules. They are declared *after* a1l type-specific pack functions for multiple reasons.
// They are in the omnetpp namespace, to allow them to be found by argument-dependent lookup via the cCommBuffer argument

// Packing/unpacking an std::vector
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::vector<T,A>& v)
{
    int n = v.size();
    doParsimPacking(buffer, n);
    for (int i = 0; i < n; i++)
        doParsimPacking(buffer, v[i]);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::vector<T,A>& v)
{
    int n;
    doParsimUnpacking(buffer, n);
    v.resize(n);
    for (int i = 0; i < n; i++)
        doParsimUnpacking(buffer, v[i]);
}

// Packing/unpacking an std::list
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::list<T,A>& l)
{
    doParsimPacking(buffer, (int)l.size());
    for (typename std::list<T,A>::const_iterator it = l.begin(); it != l.end(); ++it)
        doParsimPacking(buffer, (T&)*it);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::list<T,A>& l)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        l.push_back(T());
        doParsimUnpacking(buffer, l.back());
    }
}

// Packing/unpacking an std::set
template<typename T, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::set<T,Tr,A>& s)
{
    doParsimPacking(buffer, (int)s.size());
    for (typename std::set<T,Tr,A>::const_iterator it = s.begin(); it != s.end(); ++it)
        doParsimPacking(buffer, *it);
}

template<typename T, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::set<T,Tr,A>& s)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        T x;
        doParsimUnpacking(buffer, x);
        s.insert(x);
    }
}

// Packing/unpacking an std::map
template<typename K, typename V, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::map<K,V,Tr,A>& m)
{
    doParsimPacking(buffer, (int)m.size());
    for (typename std::map<K,V,Tr,A>::const_iterator it = m.begin(); it != m.end(); ++it) {
        doParsimPacking(buffer, it->first);
        doParsimPacking(buffer, it->second);
    }
}

template<typename K, typename V, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::map<K,V,Tr,A>& m)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        K k; V v;
        doParsimUnpacking(buffer, k);
        doParsimUnpacking(buffer, v);
        m[k] = v;
    }
}

// Default pack/unpack function for arrays
template<typename T>
void doParsimArrayPacking(omnetpp::cCommBuffer *b, const T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimPacking(b, t[i]);
}

template<typename T>
void doParsimArrayUnpacking(omnetpp::cCommBuffer *b, T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimUnpacking(b, t[i]);
}

// Default rule to prevent compiler from choosing base class' doParsimPacking() function
template<typename T>
void doParsimPacking(omnetpp::cCommBuffer *, const T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimPacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

template<typename T>
void doParsimUnpacking(omnetpp::cCommBuffer *, T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimUnpacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

}  // namespace omnetpp


// forward
template<typename T, typename A>
std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec);

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
inline std::ostream& operator<<(std::ostream& out,const T&) {return out;}

// operator<< for std::vector<T>
template<typename T, typename A>
inline std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec)
{
    out.put('{');
    for(typename std::vector<T,A>::const_iterator it = vec.begin(); it != vec.end(); ++it)
    {
        if (it != vec.begin()) {
            out.put(','); out.put(' ');
        }
        out << *it;
    }
    out.put('}');
    
    char buf[32];
    sprintf(buf, " (size=%u)", (unsigned int)vec.size());
    out.write(buf, strlen(buf));
    return out;
}

Register_Class(StatePacket)

StatePacket::StatePacket(const char *name, short kind) : ::omnetpp::cPacket(name,kind)
{
    sourceNodes_arraysize = 0;
    this->sourceNodes = 0;
    nodeUtilizations_arraysize = 0;
    this->nodeUtilizations = 0;
}

StatePacket::StatePacket(const StatePacket& other) : ::omnetpp::cPacket(other)
{
    sourceNodes_arraysize = 0;
    this->sourceNodes = 0;
    nodeUtilizations_arraysize = 0;
    this->nodeUtilizations = 0;
    copy(other);
}

StatePacket::~StatePacket()
{
    delete [] this->sourceNodes;
    delete [] this->nodeUtilizations;
}

StatePacket& StatePacket::operator=(const StatePacket& other)
{
    if (this==&other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void StatePacket::copy(const StatePacket& other)
{
    this->targetNode = other.targetNode;
    delete [] this->sourceNodes;
    this->sourceNodes = (other.sourceNodes_arraysize==0) ? nullptr : new ::omnetpp::opp_string[other.sourceNodes_arraysize];
    sourceNodes_arraysize = other.sourceNodes_arraysize;
    for (unsigned int i=0; i<sourceNodes_arraysize; i++)
        this->sourceNodes[i] = other.sourceNodes[i];
    delete [] this->nodeUtilizations;
    this->nodeUtilizations = (other.nodeUtilizations_arraysize==0) ? nullptr : new double[other.nodeUtilizations_arraysize];
    nodeUtilizations_arraysize = other.nodeUtilizations_arraysize;
    for (unsigned int i=0; i<nodeUtilizations_arraysize; i++)
        this->nodeUtilizations[i] = other.nodeUtilizations[i];
}

void StatePacket::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->targetNode);
    b->pack(sourceNodes_arraysize);
    doParsimArrayPacking(b,this->sourceNodes,sourceNodes_arraysize);
    b->pack(nodeUtilizations_arraysize);
    doParsimArrayPacking(b,this->nodeUtilizations,nodeUtilizations_arraysize);
}

void StatePacket::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->targetNode);
    delete [] this->sourceNodes;
    b->unpack(sourceNodes_arraysize);
    if (sourceNodes_arraysize==0) {
        this->sourceNodes = 0;
    } else {
        this->sourceNodes = new ::omnetpp::opp_string[sourceNodes_arraysize];
        doParsimArrayUnpacking(b,this->sourceNodes,sourceNodes_arraysize);
    }
    delete [] this->nodeUtilizations;
    b->unpack(nodeUtilizations_arraysize);
    if (nodeUtilizations_arraysize==0) {
        this->nodeUtilizations = 0;
    } else {
        this->nodeUtilizations = new double[nodeUtilizations_arraysize];
        doParsimArrayUnpacking(b,this->nodeUtilizations,nodeUtilizations_arraysize);
    }
}

const char * StatePacket::getTargetNode() const
{
    return this->targetNode.c_str();
}

void StatePacket::setTargetNode(const char * targetNode)
{
    this->targetNode = targetNode;
}

void StatePacket::setSourceNodesArraySize(unsigned int size)
{
    ::omnetpp::opp_string *sourceNodes2 = (size==0) ? nullptr : new ::omnetpp::opp_string[size];
    unsigned int sz = sourceNodes_arraysize < size ? sourceNodes_arraysize : size;
    for (unsigned int i=0; i<sz; i++)
        sourceNodes2[i] = this->sourceNodes[i];
    for (unsigned int i=sz; i<size; i++)
        sourceNodes2[i] = 0;
    sourceNodes_arraysize = size;
    delete [] this->sourceNodes;
    this->sourceNodes = sourceNodes2;
}

unsigned int StatePacket::getSourceNodesArraySize() const
{
    return sourceNodes_arraysize;
}

const char * StatePacket::getSourceNodes(unsigned int k) const
{
    if (k>=sourceNodes_arraysize) throw omnetpp::cRuntimeError("Array of size %d indexed by %d", sourceNodes_arraysize, k);
    return this->sourceNodes[k].c_str();
}

void StatePacket::setSourceNodes(unsigned int k, const char * sourceNodes)
{
    if (k>=sourceNodes_arraysize) throw omnetpp::cRuntimeError("Array of size %d indexed by %d", sourceNodes_arraysize, k);
    this->sourceNodes[k] = sourceNodes;
}

void StatePacket::setNodeUtilizationsArraySize(unsigned int size)
{
    double *nodeUtilizations2 = (size==0) ? nullptr : new double[size];
    unsigned int sz = nodeUtilizations_arraysize < size ? nodeUtilizations_arraysize : size;
    for (unsigned int i=0; i<sz; i++)
        nodeUtilizations2[i] = this->nodeUtilizations[i];
    for (unsigned int i=sz; i<size; i++)
        nodeUtilizations2[i] = 0;
    nodeUtilizations_arraysize = size;
    delete [] this->nodeUtilizations;
    this->nodeUtilizations = nodeUtilizations2;
}

unsigned int StatePacket::getNodeUtilizationsArraySize() const
{
    return nodeUtilizations_arraysize;
}

double StatePacket::getNodeUtilizations(unsigned int k) const
{
    if (k>=nodeUtilizations_arraysize) throw omnetpp::cRuntimeError("Array of size %d indexed by %d", nodeUtilizations_arraysize, k);
    return this->nodeUtilizations[k];
}

void StatePacket::setNodeUtilizations(unsigned int k, double nodeUtilizations)
{
    if (k>=nodeUtilizations_arraysize) throw omnetpp::cRuntimeError("Array of size %d indexed by %d", nodeUtilizations_arraysize, k);
    this->nodeUtilizations[k] = nodeUtilizations;
}

class StatePacketDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    StatePacketDescriptor();
    virtual ~StatePacketDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(StatePacketDescriptor)

StatePacketDescriptor::StatePacketDescriptor() : omnetpp::cClassDescriptor("StatePacket", "omnetpp::cPacket")
{
    propertynames = nullptr;
}

StatePacketDescriptor::~StatePacketDescriptor()
{
    delete[] propertynames;
}

bool StatePacketDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<StatePacket *>(obj)!=nullptr;
}

const char **StatePacketDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *StatePacketDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int StatePacketDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 3+basedesc->getFieldCount() : 3;
}

unsigned int StatePacketDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISARRAY | FD_ISEDITABLE,
        FD_ISARRAY | FD_ISEDITABLE,
    };
    return (field>=0 && field<3) ? fieldTypeFlags[field] : 0;
}

const char *StatePacketDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "targetNode",
        "sourceNodes",
        "nodeUtilizations",
    };
    return (field>=0 && field<3) ? fieldNames[field] : nullptr;
}

int StatePacketDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='t' && strcmp(fieldName, "targetNode")==0) return base+0;
    if (fieldName[0]=='s' && strcmp(fieldName, "sourceNodes")==0) return base+1;
    if (fieldName[0]=='n' && strcmp(fieldName, "nodeUtilizations")==0) return base+2;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *StatePacketDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "string",
        "string",
        "double",
    };
    return (field>=0 && field<3) ? fieldTypeStrings[field] : nullptr;
}

const char **StatePacketDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *StatePacketDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int StatePacketDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    StatePacket *pp = (StatePacket *)object; (void)pp;
    switch (field) {
        case 1: return pp->getSourceNodesArraySize();
        case 2: return pp->getNodeUtilizationsArraySize();
        default: return 0;
    }
}

const char *StatePacketDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    StatePacket *pp = (StatePacket *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string StatePacketDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    StatePacket *pp = (StatePacket *)object; (void)pp;
    switch (field) {
        case 0: return oppstring2string(pp->getTargetNode());
        case 1: return oppstring2string(pp->getSourceNodes(i));
        case 2: return double2string(pp->getNodeUtilizations(i));
        default: return "";
    }
}

bool StatePacketDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    StatePacket *pp = (StatePacket *)object; (void)pp;
    switch (field) {
        case 0: pp->setTargetNode((value)); return true;
        case 1: pp->setSourceNodes(i,(value)); return true;
        case 2: pp->setNodeUtilizations(i,string2double(value)); return true;
        default: return false;
    }
}

const char *StatePacketDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *StatePacketDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    StatePacket *pp = (StatePacket *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}


