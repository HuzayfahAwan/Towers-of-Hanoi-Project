#include <iostream>
#include <vector>
using namespace std;

int main() {
    // initialize the towers as an array of 3 vectors (Tower 0, Tower 1, Tower OR Tower A, Tower B, Tower C)
    vector<int> t[3];
    /* n is the number of discs; the candidate is the smallest ring that was not moved in the previous move, so when you first start off, the
       candidate will always be 1 because 1 is the smallest available ring in the beginning; from is the tower a disc is being moved from, and it 
       will always start off as tower 0 or the first tower; to is the tower you're moving the candidate to, and it is intialized once the nearest 
       and farthest values are determined moves is the number of moves it takes to move all discs from the first tower to the second tower in a way 
       such that when moving the discs -> one disc is being moved at a time and a larger disc is never placed on top of a smaller disc; nearest and 
       farthest are there to reduce redundancy of code in the last if-else statement of the while-loop where you determine which tower will be the 
       new to tower -> if n is odd, then the condition for the last if-else statement would be if (from + 1) else from + 2, but if n is even, then 
       the condition for the last if-else statement would be if (from + 2) else from + 1  -> to remove this redundancy issue, nearest and farthest 
       are there so you could do if (from + nearest) else from + farthest, so no matter if n is even or odd, you can just set the nearest and 
       farthest towers accordingly right after the user enters a value for n.
    */
    int n, from = 0, to, nearest, farthest, candidate, moves = 0;
    cout << "Enter how many rings you want to be moved from the first tower to the second tower: ";
    cin >> n;
    cout << endl;
    /* initializing the 3 towers by adding the number of discs entered by the user into the first vector representing the first tower and then 
       putting a place-holder value in the second and third vectors (towers) -> the place-holder value is n + 1 and you need this place-holder value
       because later when you are determining the new from and to towers, you need that place-holder value in the "empty" tower, so you have a value
       available to compare to; otherwise you would just be comparing to null!
    */
    for (int i = n + 1; i >= 1; i--) {
        t[0].push_back(i);
    }
    t[1].push_back(n + 1);
    t[2].push_back(n + 1);
    candidate = t[from].back(); // initializing the candidate to be the current smallest disc availabe (which will always be the top-most disc of tower 0 at the beginning)
    /* if n is an odd value, the nearest tower is tower 1 or the second tower and the farthest tower is tower 2 or the third tower and the to
       tower is the nearest tower since that's where you should move the first disc on the first move no matter what.
    */
    if (n % 2 == 1) {
        nearest = 1;
        farthest = 2;
        to = nearest;
    } else {  /* if n is an even value, the nearest tower is tower 2 or the third tower and the farthest tower is tower 1 or the second tower
                 and the to tower is the nearest tower since that's where you should move the first disc on the first move no matter what.
              */
        nearest = 2;
        farthest = 1;
        to = nearest;
    }
    // if tower 1 or the second tower has less than n + 1 discs, then you know that there are still leftover discs that need to be moved to tower 1
    while (t[1].size() < (n + 1)) {
        cout << "Move Number " << ++moves << " -> moving disc " << candidate << " from Tower " << (char)(from + 65) << " to Tower " << (char)(to + 65) << endl;
        // pushing or appending the top disc of the from tower onto the to tower
        t[to].push_back(candidate);
        // removing the top disc of the from tower since it has been moved to the to tower
        t[from].pop_back();
        /* determining the new from tower, so you can determine the new candidate or smallest disc available to be moved -> the new from tower 
           obviously cannot be the current to tower because then that would break the rule of not making the candidate a disc that has been moved in
           the previous move, so you write (to + 1) % 3 and (to + 2) % 3 to get the values of the two other towers to compare the top disc values of
           those since one of those has to be the new from tower; whichever tower in the comparison has a smaller top disc value becomes the new from
           tower.
        */
        if (t[(to + 1) % 3].back() < t[(to + 2) % 3].back()) from = (to + 1) % 3;
        else from = (to + 2) % 3;
        // making the new candidate the top disc value of the new from tower
        candidate = t[from].back();
        /* determining the new to tower, so you can determine which tower to move the new candidate to -> the new from tower obviously cannot be the
           new to tower because that just wouldn't make sense, so you write (from + nearest) % 3 and compare that tower's top disc value to the new 
           candidate/disc value and if that that tower's top disc value is greater than the candidate, then you make that tower the to tower and you
           also know that you are allowed to move the candidate there since the rule where you cannot put a larger disc onto a smaller disc would not be 
           broken; otherwise, you would make the (from + farthest) % 3 tower the new to tower (note: you do from + nearest and from + farthest because
           that takes care of both cases when n is either even or odd -> you don't need to have separate while-loops considering when n is even or odd
           because you already took care of that after the user entered n or the number of discs)
        */
        if (t[(from + nearest) % 3].back() > candidate) to = (from + nearest) % 3;
        else to = (from + farthest) % 3;
    }
    return 0;
}