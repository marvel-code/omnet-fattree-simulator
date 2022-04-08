//
// Generated file, do not edit! Created by nedtool 5.4 from policyPacket.msg.
//

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#ifndef __POLICYPACKET_M_H
#define __POLICYPACKET_M_H

#include <omnetpp.h>

// nedtool version check
#define MSGC_VERSION 0x0504
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of nedtool: 'make clean' should help.
#endif



/**
 * Class generated from <tt>policyPacket.msg:16</tt> by nedtool.
 * <pre>
 * packet PolicyPacket
 * {
 *     double proportions[];
 * }
 * </pre>
 */
class PolicyPacket : public ::omnetpp::cPacket
{
  protected:
    double *proportions; // array ptr
    unsigned int proportions_arraysize;

  private:
    void copy(const PolicyPacket& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const PolicyPacket&);

  public:
    PolicyPacket(const char *name=nullptr, short kind=0);
    PolicyPacket(const PolicyPacket& other);
    virtual ~PolicyPacket();
    PolicyPacket& operator=(const PolicyPacket& other);
    virtual PolicyPacket *dup() const override {return new PolicyPacket(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual void setProportionsArraySize(unsigned int size);
    virtual unsigned int getProportionsArraySize() const;
    virtual double getProportions(unsigned int k) const;
    virtual void setProportions(unsigned int k, double proportions);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const PolicyPacket& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, PolicyPacket& obj) {obj.parsimUnpack(b);}


#endif // ifndef __POLICYPACKET_M_H
