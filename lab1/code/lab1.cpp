// lab1.cpp : stable partition
// Iterative and divide-and-conquer

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <format>
#include <functional>
#include <cassert>


/****************************************
 * Declarations                          *
 *****************************************/

// generic class to write an item to a stream
template <typename T>
class Formatter {
public:
    Formatter(std::ostream& os, int width, int per_line)
        : os_{os}, per_line_{per_line}, width_{width} {
    }

    void operator()(const T& t) {
        os_ << std::format("{:{}}", t, width_);
        if (++outputted_ % per_line_ == 0)
            os_ << "\n";
    }

private:
    std::ostream& os_;    // output stream
    const int per_line_;  // number of columns per line
    const int width_;     // column width
    int outputted_{0};    // counter of number of items written to os_
};

/* ************************ */

namespace TND004 {
// Iterative algorithm
// Här ska vi göra en algorithm som körs i linjär tid, för varje sekvens som har n > items.
// Försök att de underliggande konstanterna ska vara så låga som möjligt. Exempelvis 2n steg över 1000n steg.
void stable_partition_iterative(std::vector<int>& V, std::function<bool(int)> p);


// Auxiliary function that performs the stable partition recursively
std::vector<int>::iterator stable_partition(std::vector<int>::iterator first,
                                            std::vector<int>::iterator last,
                                            std::function<bool(int)> p);

// Divide-and-conquer algorithm
void stable_partition(std::vector<int>& V, std::function<bool(int)> p) {
    TND004::stable_partition(std::begin(V), std::end(V), p);  // call auxiliary function
}
}  // namespace TND004

void execute(std::vector<int>& V, const std::vector<int>& res);

bool even(int i);

/****************************************
 * Main:test code                        *
 *****************************************/

int main() {
    /*****************************************************
     * TEST PHASE 1                                       *
     ******************************************************/
    {
        std::cout << "TEST PHASE 1\n\n";

        std::vector<int> seq{1, 2};

        std::cout << "Sequence: ";
        std::copy(std::begin(seq), std::end(seq), std::ostream_iterator<int>{std::cout, " "});

        execute(seq, std::vector<int>{2, 1});

        std::cout << "\nEmpty sequence: ";
        std::vector<int> empty;

        execute(empty, std::vector<int>{});
    }

    /*****************************************************
     * TEST PHASE 2                                       *
     ******************************************************/
    {
        std::cout << "\n\nTEST PHASE 2\n\n";

        std::vector<int> seq{2};

        std::cout << "Sequence: ";
        std::copy(std::begin(seq), std::end(seq), std::ostream_iterator<int>{std::cout, " "});

        execute(seq, std::vector<int>{2});
    }

    /*****************************************************
     * TEST PHASE 3                                       *
     ******************************************************/
    {
        std::cout << "\n\nTEST PHASE 3\n\n";

        std::vector<int> seq{3};

        std::cout << "Sequence: ";
        std::copy(std::begin(seq), std::end(seq), std::ostream_iterator<int>{std::cout, " "});

        execute(seq, std::vector<int>{3});
    }

    /*****************************************************
     * TEST PHASE 4                                       *
     ******************************************************/
    {
        std::cout << "\n\nTEST PHASE 4\n\n";

        std::vector<int> seq{3, 3};

        std::cout << "Sequence: ";
        std::copy(std::begin(seq), std::end(seq), std::ostream_iterator<int>(std::cout, " "));

        execute(seq, std::vector<int>{3, 3});
    }

    /*****************************************************
     * TEST PHASE 5                                       *
     ******************************************************/
    {
        std::cout << "\n\nTEST PHASE 5\n\n";

        std::vector<int> seq{1, 2, 3, 4, 5, 6, 7, 8, 9};

        std::cout << "Sequence: ";
        std::copy(std::begin(seq), std::end(seq), std::ostream_iterator<int>(std::cout, " "));

        execute(seq, std::vector<int>{2, 4, 6, 8, 1, 3, 5, 7, 9});
    }

    /*****************************************************
     * TEST PHASE 6                                       *
     ******************************************************/
    {
        std::cout << "\n\nTEST PHASE 6: test with long sequence loaded from a file\n\n";

        std::ifstream file("../code/test_data.txt");

        if (!file) {
            std::cout << "Could not open test_data.txt!!\n";
            return 0;
        }

        // read the input sequence from file
        std::vector<int> seq{std::istream_iterator<int>{file}, std::istream_iterator<int>()};
        file.close();

        std::cout << "\nNumber of items in the sequence: " << seq.size() << '\n';

        /*std::cout << "Sequence:\n";
        std::for_each(std::begin(seq), std::end(seq), Formatter<int>(std::cout, 8, 5));*/

        // read the result sequence from file
        file.open("../code/test_result.txt");

        if (!file) {
            std::cout << "Could not open test_result.txt!!\n";
            return 0;
        }

        std::vector<int> res{std::istream_iterator<int>{file}, std::istream_iterator<int>()};

        std::cout << "\nNumber of items in the result sequence: " << res.size();

        // display expected result sequence
        // std::for_each(std::begin(res), std::end(res), Formatter<int>(std::cout, 8, 5));

        assert(seq.size() == res.size());

        execute(seq, res);
    }
}

/****************************************
 * Functions definitions                 *
 *****************************************/

bool even(int i) {
    return i % 2 == 0;
}

// Used for testing
void execute(std::vector<int>& V, const std::vector<int>& res) {
    std::vector<int> copy_{V};

    std::cout << "\n\nIterative stable partition\n";
    TND004::stable_partition_iterative(V, even);
    assert(V == res);  // compare with the expected result

    
    // Uncomment for exercise 2
    std::cout << "Divide-and-conquer stable partition\n";
    TND004::stable_partition(copy_, even);
    assert(copy_ == res);  // compare with the expected result
    
}

// Iterative algorithm
void TND004::stable_partition_iterative(std::vector<int>& V, std::function<bool(int)> p) {
    // IMPLEMENT before Lab1 HA

    // Since the function is only called once, which allocates the space in the beginning, S(n) = O(1)

    // Create two vectors for even and odd numbers
    std::vector<int> S1;
	std::vector<int> S2;

    // At most O(n)
    S1.reserve(V.size()); 
    S2.reserve(V.size());

    for (int i : V)
    {
        // Check for even numbers
        if (p(i))
        {
            S1.push_back(i); // O(1) since we used reserver earlier to set the size of the vectors.
        }
        // Check for odd
        else
        {
			S2.push_back(i); // O(1) since we used reserver earlier to set the size of the vectors.
        }
    }

	// Reference Vector V gets cleared and now equals S1. Then we insert S2 from where V ends.
    int i = 0;
    for (int e : S1) // O(n) since it steps through it linearly
    {
        V[i] = e;
        i++;
    }
    for (int e : S2) // O(n) since it steps through it linearly
    {
        V[i] = e;
        i++;
    }
}

// Auxiliary function that performs the stable partition recursively
// Divide-and-conquer algorithm: stable-partition the sub-sequence starting at first and ending
// at last-1. If there are items with property p then return an iterator to the end of the block
// containing the items with property p. If there are no items with property p then return first.
std::vector<int>::iterator TND004::stable_partition(std::vector<int>::iterator first,
                                                    std::vector<int>::iterator last,
                                                    std::function<bool(int)> p) {

	// Since the function is called n amount of times the size of the function will also be allocated n amount of times, which gives S(n) = O(n)

    // Base case for when empty (if-guard)
    if (first == last)
    {
        return first; // O(1)
    }

    // Exercise 2 Implementation 
    std::vector<int>::iterator mid;

    // Takes the first element and then adds all number of elements in the vector divided by two.
    // This gives us the precise midpoint of the sequence.
    // std::next

    // Base case only 1 element in vector.
    if (std::next(first, 1) == last) { // std::next is O(n)
        if (p(*first))
        {
            return last; // If even
        }
        else
        {
            return first; // If odd (slide 9)
        }
    }
    else
    {
        mid = std::next(first, std::distance(first, last) / 2); // O(n)
    }
    //Uses the recursive function stable_partition on the left half and right half of the sequence.
    std::vector<int>::iterator Sl = stable_partition(first, mid, p);    // Best: O(logn), worst: O(n)
    std::vector<int>::iterator Sr = stable_partition(mid, last, p);     // Best: O(logn), worst: O(n)

    // Rotates the left half and right half around the midpoint
    return std::rotate(Sl, mid, Sr);    // Linear O(n)
}

// Linear functions take less time if there is small sequences and log takes less if there is large ones
// Therefor best case for divide and conquer is O(log(n)) (no constant infront) and worst is linear.
// Linear is best for the smaller sequences.
