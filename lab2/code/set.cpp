#include "set.h"
#include "node.h"

int Set::Node::count_nodes = 0;

/*****************************************************
 * Implementation of the member functions             *
 ******************************************************/

 /*
  *  Default constructor :create an empty Set
  */
int Set::get_count_nodes() {
    return Set::Node::count_nodes;
}

/*
 *  Default constructor :create an empty Set
 */
Set::Set() : counter{ 0 } {
    head = new Node(); // Empty Node
    tail = new Node(0, nullptr, head); // Head is it's previous
    head->next = tail; // Here we can tell that head's next is tail == empty.
}

/*
 *  Conversion constructor: convert val into a singleton {val}
 */
Set::Set(int val) : Set{} {  // create an empty list
    // IMPLEMENT before Lab2 HA
    // Implement a Node with value n, previous ptr tail, next ptr head since it's the first.
    // Adds to counter
    insert_node(head, val);
}

/*
 * Constructor to create a Set from a sorted vector of ints
 * Create a Set with all ints in sorted vector list_of_values
 */
Set::Set(const std::vector<int>& list_of_values) : Set{} {  // create an empty list
    // IMPLEMENT before Lab2 HA

    // prevNode points to head (startpoint)
    Node* prevNode = head;
    //foreach loop with e elements through the vector. 
    for (int e : list_of_values)
    {
        insert_node(prevNode, e); // Insert pointer prevNode and the value it points to e in Set.

        prevNode = prevNode->next; // Jumps a step in the Set since a new Node have been added to Set.
        // Meaning it should point to the starting node but to the new node as starting point when
        // adding a new Node next time.
    }
}

/*
 * Copy constructor: create a new Set as a copy of Set S
 * \param S Set to copied
 * Function does not modify Set S in any way
 */
Set::Set(const Set& S) : Set{} {  // create an empty list
    // IMPLEMENT before Lab2 HA

    if (S.is_empty())
    {
        return;
    }

    Node* newN = S.tail->prev;
    // Runs untill we strike the tail of S (endpoint)
    do {
        insert_node(head, newN->value);
        newN = newN->prev; // Jump to previous Node.
    } while (newN != S.head);
}

/*
 * Transform the Set into an empty set
 * Remove all nodes from the list, except the dummy nodes
 */
void Set::make_empty() {
    // IMPLEMENT before Lab2 HA
    while (head->next != tail) {
        remove_node(head->next);
    }
}

/*
 * Destructor: deallocate all memory (Nodes) allocated for the list
 */
Set::~Set() {
    // IMPLEMENT before Lab2 HA
    while (head->next != tail)
    {
        remove_node(head->next);
    }

    delete head;
    delete tail;
}

/*
 * Assignment operator: assign new contents to the *this Set, replacing its current content
 * \param S Set to be copied into Set *this
 * Call by valued is used
 */
Set& Set::operator=(Set S) {
    // IMPLEMENT before Lab2 HA

    counter = S.counter;
    // We can use swap since we only look at the sequence between head and tail, everything else follows along.
    std::swap(head, S.head);
    std::swap(tail, S.tail);

    return *this;
}

/*
 * Test whether val belongs to the Set
 * Return true if val belongs to the set, otherwise false
 * This function does not modify the Set in any way
 */
bool Set::is_member(int val) const {
    // IMPLEMENT before Lab2 HA

    Node* newN = head->next; // Change method to front-to-back since it's more logical here.

    do
    {
        if (newN->value == val) {
            return true;
        }
        newN = newN->next;
    } while (newN != tail);

    return false;
}

/*
 * Test whether Set *this and S represent the same set
 * Return true, if *this has same elemnts as set S
 * Return false, otherwise
 */
bool Set::operator==(const Set& S) const {
    // IMPLEMENT before Lab2 HA
    // Since they equal they should have same counter, otherwise false.
    if (cardinality() != S.cardinality()) {
        return false;
    }
    else if (is_empty() && S.is_empty())
    {
        return true;
    }

    Node* localN = head->next;    // Local set
    Node* newN = S.head->next;

	do {
		if (localN->value != newN->value) {
            return false;
		}

		localN = localN->next;
		newN = newN->next;

	} while (localN != tail || newN != S.tail);

    return true;
}

/*
 * Three-way comparison operator: to test whether *this == S, *this < S, *this > S
 * Return std::partial_ordering::equivalent, if *this == S
 * Return std::partial_ordering::less, if *this < S
 * Return std::partial_ordering::greater, if *this > S
 * Return std::partial_ordering::unordered, otherwise
 */
std::partial_ordering Set::operator<=>(const Set& S) const {

    //They are equal
    bool LhsContainsRhs = true;
    bool RhsContainsLhs = true;

    //Starting after head.
    Node* LhsN = head->next;
    Node* RhsN = S.head->next;

    // Check to see if empty first
    //if (LhsN != tail)
    //{
        while (LhsN != tail && RhsN != S.tail)
        {
            if (LhsN->value < RhsN->value)
            {
                RhsContainsLhs = false;
                LhsN = LhsN->next;
            }
            if (LhsN->value > RhsN->value) // 
            {
                LhsContainsRhs = false;
                RhsN = RhsN->next;
            }
            if (LhsN->value == RhsN->value) // If equal just proceed to next
            {
                LhsN = LhsN->next;
                RhsN = RhsN->next;
            }
        }

        if (RhsContainsLhs && LhsContainsRhs)
        {
			if (LhsN != tail)
			{
				RhsContainsLhs = false;
			}

			if (RhsN != S.tail)
			{
				LhsContainsRhs = false;
			}
        }

        if (RhsContainsLhs && LhsContainsRhs) 
        {
			return std::partial_ordering::equivalent;
        }

        if (RhsContainsLhs && !LhsContainsRhs)
        {
            return std::partial_ordering::less;
        }
        if (!RhsContainsLhs && LhsContainsRhs)
        {
            return std::partial_ordering::greater;
        }
        if (!RhsContainsLhs && !LhsContainsRhs)
        {
            return std::partial_ordering::unordered;
        }

    return std::partial_ordering::unordered;
}

/*
 * Modify Set *this such that it becomes the union of *this with Set S
 * Set *this is modified and then returned
 */
Set& Set::operator+=(const Set& S) {
    Node* p1 = head->next;
    Node* p2 = S.head->next;

    while (p1 != tail && p2 != S.tail) {
        if (p1->value > p2->value) {
			insert_node(p1->prev, p2->value);
            p2 = p2->next;
        }
        else if (p1->value < p2->value) {
            if (p1->next->value < p2->value) {
				p1 = p1->next;
            }
            else {
                insert_node(p1, p2->value);
                p1 = p1->next->next;
			    p2 = p2->next;
            }
        }
        else {
			p1 = p1->next;
            p2 = p2->next;
        }
    }

    while (p2 != S.tail) {
        insert_node(p1, p2->value);
        p2 = p2->next;
    }

    return *this;
}

/*
 * Modify Set *this such that it becomes the intersection of *this with Set S
 * Set *this is modified and then returned
 */
Set& Set::operator*=(const Set& S) {
    // IMPLEMENT

    if (S.is_empty() && is_empty()) {
        return *this;
    }

    Node* localN = tail->prev; 
    Node* newN = S.tail->prev;
    Set resultSet = Set();

    do {
		if (localN->value > newN->value) {
			localN = localN->prev;
		}
		else if (localN->value < newN->value) {
			newN = newN->prev;
		}
        else {
            resultSet.insert_node(resultSet.head, localN->value);
            localN = localN->prev;
            newN = newN->prev;
        }

    } while (localN != head || newN != S.head);

	std::swap(head, resultSet.head);
	std::swap(tail, resultSet.tail);
    counter = resultSet.counter;

    return *this;
}

/*
 * Modify Set *this such that it becomes the Set difference between Set *this and Set S
 * Set *this is modified and then returned
 */
Set& Set::operator-=(const Set& S) {

    Node* newN = S.head->next;
    Node* localN = head->next;  // local set
    //do
    //{
    //    localN = localN->next;
    //    if (S.is_member(localN->prev->value)) {
    //        remove_node(localN->prev);
    //    }

    //} while (localN != tail); // Untill we reached the end of the local set.

    if (S.is_empty() || is_empty()) {
        return *this;
    }
	do {
		if (localN->value > newN->value) {
			newN = newN->next;
		}
		else if (localN->value < newN->value) {
			localN = localN->next;
		}
		else {
			localN = localN->next;
			newN = newN->next;
			remove_node(localN->prev);
		}

	} while (localN != tail && newN != S.tail);

    return *this;
}


/* ******************************************** *
 * Private Member Functions -- Implementation   *
 * ******************************************** */

 /*
  * Insert a new Node storing val after the Node pointed by p
  * \param p pointer to a Node
  * \param val value to be inserted  after position p
  */
void Set::insert_node(Node* p, int val) {
    // IMPLEMENT before Lab2 HA

    // n is a pointer which points to a Node with the regulations set below.
    Node* n = new Node(val, p->next, p);

    // Insert the new node between it's previous and next pointer.
    // Pointer p's next pointer's previous pointer should equal p's next pointer and that should
    // equal pointer n. Which is the pointer that points to the new node.
    // Makes p->next point towards the newly created node n (with the reference adress of n)
    p->next->prev = n;
    p->next = n;

    counter++;
}

/*
 * Remove the Node pointed by p
 * \param p pointer to a Node
 */
void Set::remove_node(Node* p) {
    // IMPLEMENT before Lab2 HA

    // Remove the connections to the node p.
    p->prev->next = p->next;
    p->next->prev = p->prev;

    // Delete the node from the heap.
    delete p;
    counter--;

}

/*
 * Write Set *this to stream os
 */
void Set::write_to_stream(std::ostream& os) const {
    if (is_empty()) {
        os << "Set is empty!";
    }
    else {
        Set::Node* ptr{ head->next };

        os << "{ ";
        while (ptr != tail) {
            os << ptr->value << " ";
            ptr = ptr->next;
        }
        os << "}";
    }
}
