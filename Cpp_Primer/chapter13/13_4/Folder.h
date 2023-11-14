#ifndef FOLDER_H
#define FOLDER_H

#include "Version_test.h"

#include <string>
#include <set>

class Folder;

class Message {
	friend void swap(Message&, Message&);
	friend class Folder;
public:
    // folders is implicitly initialized to the empty set 
    explicit Message(const std::string &str = ""): 
		contents(str) { }  

    // copy control to manage pointers to this Message
    Message(const Message&);             // copy constructor
    Message& operator=(const Message&);  // copy assignment
    ~Message();                          // destructor
    Message(Message&&);            // move constructor
    Message& operator=(Message&&); // move assignment

    // add/remove this Message from the specified Folder's set of messages
    void save(Folder&);   
    void remove(Folder&); 
    void debug_print(); // print contents and it's list of Folders, 
                        // printing each Folder as well
private:
    std::string contents;      // actual message text
    std::set<Folder*> folders; // Folders that have this Message

    // utility functions used by copy constructor, assignment, and destructor
    // add this Message to the Folders that point to the parameter
    void add_to_Folders(const Message&);
	void move_Folders(Message*);
    // remove this Message from every Folder in folders
    void remove_from_Folders(); 

    // used by Folder class to add self to this Message's set of Folder's
    void addFldr(Folder *f) { folders.insert(f); }
    void remFldr(Folder *f) { folders.erase(f); }
};
// declaration for swap should be in the same header as Message itself
void swap(Message&, Message&);

class Folder {
	friend void swap(Message&, Message&);
	friend class Message;
public:
    ~Folder(); // remove self from Messages in msgs
    Folder(const Folder&); // add new folder to each Message in msgs
    Folder& operator=(const Folder&); // delete Folder from lhs messages
                                      // add Folder to rhs messages
    Folder(Folder&&);   // move Messages to this Folder 
    Folder& operator=(Folder&&); // delete Folder from lhs messages
                                 // add Folder to rhs messages

#ifdef DEFAULT_FCNS
    Folder() = default; // defaults ok
#else
	Folder() { } // msgs will be default initialized, which is what we want
#endif

    void save(Message&);   // add this message to folder
    void remove(Message&); // remove this message from this folder
    
    void debug_print(); // print contents and it's list of Folders, 
private:
    std::set<Message*> msgs;  // messages in this folder

    void add_to_Messages(const Folder&);// add this Folder to each Message
    void remove_from_Msgs();     // remove this Folder from each Message
    void addMsg(Message *m) { msgs.insert(m); }
    void remMsg(Message *m) { msgs.erase(m); }
	void move_Messages(Folder*); // move Message pointers to point to this Folder
};

#endif
