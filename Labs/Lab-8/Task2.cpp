/*
    Task 2:
        Exam room (Leet code 855): https://leetcode.com/problems/exam-room/description/
*/

#include <iostream>
#include <set>

class ExamRoom {
private:
    int n;  // Total number of seats in the exam room
    std::set<int> seats;  // Set to store the indices of occupied seats in ascending order

public:
    // Constructor to initialize the exam room with n seats
    ExamRoom(int n) : n(n) {}

    // Function to seat a student
    int seat() {
        // If no one is seated yet, the first student sits at seat 0
        if (seats.empty()) {
            seats.insert(0);  // Insert seat 0 into the set of occupied seats
            return 0;  // Return the seat number (0 in this case)
        }

        // Initialize variables to find the seat which maximizes the distance from the closest occupied seat
        int maxDist = *seats.begin();  // Distance from seat 0 to the first occupied seat
        int seatToChoose = 0;  // Seat to be chosen, initially set to 0 (in case seat 0 offers max distance)

        // Variable to keep track of the previous occupied seat during iteration
        int prev = -1;

        // Loop through the set of occupied seats to find the largest gap between two consecutive seats
        for (int seat : seats) {
            if (prev == -1) {  // If this is the first occupied seat
                prev = seat;  // Set the current seat as 'prev' and continue to the next iteration
                continue;
            }

            // Calculate the distance between the current seat and the previous seat
            int dist = (seat - prev) / 2;  // Distance is half the gap between two consecutive seats

            // Check if the distance in this gap is larger than the current maximum distance
            if (dist > maxDist) {
                maxDist = dist;  // Update max distance
                seatToChoose = prev + dist;  // Choose the seat in the middle of the gap
            }

            prev = seat;  // Update 'prev' to the current seat for the next iteration
        }

        // Check if the distance from the last occupied seat to the end of the room (seat n-1) is larger than maxDist
        if ((n - 1 - *seats.rbegin()) > maxDist) {
            seatToChoose = n - 1;  // If the gap at the end is the largest, choose the last seat (n-1)
        }

        // Insert the chosen seat into the set of occupied seats
        seats.insert(seatToChoose);

        // Return the seat number where the student will sit
        return seatToChoose;
    }

    // Function to make a student leave the room
    void leave(int p) {
        seats.erase(p);  // Remove seat p from the set of occupied seats
    }

    static void unitTest() {
        ExamRoom examRoom(10);  // Initialize the exam room with 10 seats

        // Test seating and leaving functionality
        std::cout << "Seat 1: " << examRoom.seat() << "\n"; // return 0 (first student sits at seat 0)
        std::cout << "Seat 2: " << examRoom.seat() << "\n"; // return 9 (next student sits at seat 9)
        std::cout << "Seat 3: " << examRoom.seat() << "\n"; // return 4 (next student sits at seat 4, middle between 0 and 9)
        std::cout << "Seat 4: " << examRoom.seat() << "\n"; // return 2 (next student sits at seat 2, middle between 0 and 4)
        examRoom.leave(4);  // Student at seat 4 leaves
        std::cout << "Seat 5: " << examRoom.seat() << "\n"; // return 5 (next student sits at seat 5, middle between 2 and 9)

    }
};

// Main function to demonstrate the functionality
int main() {
    ExamRoom::unitTest();  // Run the unit test
    return 0;
}
