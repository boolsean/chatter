#ifndef payload_h
#define payload_h


class Payload {
public:
    enum TYPE {
        TEXT = 0,
        BLOB,
        UNKNOWN
    };

    virtual TYPE getType() const;

};


#endif
